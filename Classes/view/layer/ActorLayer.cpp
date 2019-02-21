//
//  ActorLayer.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#include "ActorLayer.hpp"
#include "ELProtocol.h"
#include "EventDefine.h"
#include "GameUtils.h"
#include "logic/ClientLogic.hpp"

USING_NS_CC;

ActorLayer::ActorLayer()
{
    setupHeroListener = EventListenerCustom::create(SETUP_HERO, CC_CALLBACK_1(ActorLayer::setupFoo, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(setupHeroListener, -1);
    hitHeroListener = EventListenerCustom::create(HIT_HERO, CC_CALLBACK_1(ActorLayer::hitHero, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(hitHeroListener, -1);
}

ActorLayer::~ActorLayer()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(setupHeroListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(hitHeroListener);
}

bool ActorLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    maxArrowId = 1;
    return true;
}

void ActorLayer::onEnter()
{
    Layer::onEnter();
    
    scheduleUpdate();
}

void ActorLayer::onExit()
{
    Layer::onExit();
    spearMap.clear();
    unscheduleUpdate();
}

void ActorLayer::setupFoo(cocos2d::EventCustom *event)
{
    L2E_SETUP_FOO data = *static_cast<L2E_SETUP_FOO *>(event->getUserData());
    for (int i = 0; i < 2; i++) {
        if(data.userId[i] == data.myUserId) {
            me = Hero::create();
            //  翻译坐标
            float posx = GameUtils::winSize.width/2 - data.posx[i];
            if (data.flipX) {
                posx = GameUtils::winSize.width/2 + data.posx[i];
            }
            me->setPosition(posx, data.posy[i]);
            me->setFlipX(data.flipX);
            me->setUserId(data.myUserId);
            me->setupView("DemoPlayer.csb");
            addChild(me);
        }else {
            master = Hero::create();
            //  翻译坐标
            float posx = GameUtils::winSize.width/2 + data.posx[i];
            if (data.flipX) {
                posx = GameUtils::winSize.width/2 - data.posx[i];
            }
            master->setPosition(posx, data.posy[i]);
            master->setFlipX(!data.flipX);
            master->setUserId(data.userId[i]);
            master->setupView("DemoPlayer.csb");
            addChild(master);
        }
    }
}

void ActorLayer::adjustBow(float angle, float power)
{
    me->adjustBow(angle, power);
}

void ActorLayer::drawBow(float angle, float power)
{
    me->drawBow(angle, power);
}

void ActorLayer::hitHero(cocos2d::EventCustom *event)
{
    L2E_HIT_HERO data = *static_cast<L2E_HIT_HERO*>(event->getUserData());
    //  找到被击中者，把箭支插到骨骼上
    if (data.hitUserId == me->getUserId()) {
        me->hitBySpear(data);
    } else if (data.hitUserId == master->getUserId()) {
        master->hitBySpear(data);
    }
    //  把箭支设为打断飞行状态，消除它
    if (spearMap.find(data.arrowId) != spearMap.end()) {
        auto arrow = spearMap[data.arrowId];
        if (arrow->getAlive() && arrow->getCurrState() == SPEAR_FLY) {
            arrow->changeState(SPEAR_INTERUPT);
        }
    }
}

void ActorLayer::looseBow(cocos2d::EventCustom *event)
{
    L2E_LOOSE data = *static_cast<L2E_LOOSE *>(event->getUserData());
    auto spear = Spear::create();
    //  给发出的箭支唯一ID
    spear->setArrowId(maxArrowId);
    
    if (data.userId == data.myUserId) {
        float angle = data.drawAngle;
        if (me->getFlipX()) {
            angle = 180-data.drawAngle;
            if (data.drawAngle < 0) {
                angle -= 360;
            }
        }
        me->loose(angle, data.drawPower);
        spear->setOwnerId(data.userId);
        addChild(spear);
        spear->setupWithData(data, me->getFlipX(), me->getPosition());
    }else{
        float angle = data.drawAngle;
        if (!master->getFlipX()) {
            angle = 180-data.drawAngle;
            if (data.drawAngle < 0) {
                angle -= 360;
            }
        }
        master->loose(angle, data.drawPower);
        spear->setOwnerId(data.userId);
        addChild(spear);
        spear->setupWithData(data, master->getFlipX(), master->getPosition());
    }
    
    spearMap[maxArrowId] = spear;
    maxArrowId++;
}

void ActorLayer::testLoose(float dt)
{
//    me->updateAI(dt);
}

void ActorLayer::update(float dt)
{
    // 先把无效箭支删除
    for (auto iter = spearMap.begin(); iter != spearMap.end(); ) {
        if (!(*iter).second->getAlive()) {
            removeChild((*iter).second);
            iter = spearMap.erase(iter);
            
        }else{
            iter++;
        }
    }

    //  箭支的遍历碰撞
    for (auto iter : spearMap) {
        auto arrow = iter.second;
        if (arrow->getCurrState() != SPEAR_FLY) {
            continue;
        }
        
        float arrowAngle = arrow->getSpearAngle();
        Vec2 arrowPos = arrow->getArrowPos();

        if (arrow->getOwnerId() == me->getUserId())
        {
            int hitResult = master->hitCheck(arrowPos, arrowAngle, Size(70, 8));//93,15
            switch(hitResult)
            {
                case 0:
                    break;
                case 1:
                {
                    E2L_HIT_HERO info;
                    info.eProtocol = e2l_hit_hero;
                    info.hitUserId = master->getUserId();
                    info.hurtBone = 1;
                    info.arrowId = arrow->getArrowId();
                    //  转换成无翻转的箭支角度
                    info.arrowAngle = convertArrowAngle(arrowAngle, master);
                    //  转换成相对命中骨骼的角度
                    info.arrowAngle = master->getHitAngle(info.arrowAngle, info.hurtBone);
                    //  转换成无翻转的相对角色的坐标
                    info.arrowPosX = convertHitPos(arrowPos.x, master);
                    info.arrowPosY = arrowPos.y - master->getPositionY();
                    //  转换成相对骨骼的坐标位置
                    auto pos = master->getHitPos(Vec2(info.arrowPosX, info.arrowPosY), info.hurtBone);
                    info.arrowPosX = pos.x;
                    info.arrowPosY = pos.y;
                    ClientLogic::instance()->ProcessUIRequest(&info);
                }
                    break;
            }
        } else {
            int hitResult = me->hitCheck(arrowPos, 180-arrowAngle, Size(93, 15));
            switch(hitResult)
            {
                case 0:
                    break;
                case 1:
                {
                    E2L_HIT_HERO info;
                    info.eProtocol = e2l_hit_hero;
                    info.hitUserId = master->getUserId();
                    info.hurtBone = 1;
                    info.arrowId = arrow->getArrowId();
                    //  转换成无翻转的箭支角度
                    info.arrowAngle = convertArrowAngle(arrowAngle, me);
                    //  转换成相对命中骨骼的角度
                    info.arrowAngle = me->getHitAngle(info.arrowAngle, info.hurtBone);
                    //  转换成无翻转的相对角色的坐标
                    info.arrowPosX = convertHitPos(arrowPos.x, me);
                    info.arrowPosY = arrowPos.y - me->getPositionY();
                    //  转换成相对骨骼的坐标位置
                    auto pos = me->getHitPos(Vec2(info.arrowPosX, info.arrowPosY), info.hurtBone);
                    info.arrowPosX = pos.x;
                    info.arrowPosY = pos.y;
                    ClientLogic::instance()->ProcessUIRequest(&info);
                }
                    break;
            }
        }
    }
}

float ActorLayer::convertArrowAngle(float arrowAngle, Hero *hero)
{
    float sendAngle = arrowAngle;

    if (hero->getFlipX()) {
        if (sendAngle >= 0) {
            sendAngle = 180 - arrowAngle;
        }else{
            sendAngle = -180 - arrowAngle;
        }
    }
    
    return sendAngle;
}

float ActorLayer::convertHitPos(float arrowPosX, Hero *hero)
{
    if (hero->getFlipX()) {
        return hero->getPositionX() - arrowPosX;
    } else {
        return arrowPosX - hero->getPositionX();
    }
}
