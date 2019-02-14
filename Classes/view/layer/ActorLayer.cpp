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
}

ActorLayer::~ActorLayer()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(setupHeroListener);
}

bool ActorLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
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
    unscheduleUpdate();
}

void ActorLayer::setupFoo(cocos2d::EventCustom *event)
{
    L2E_SETUP_FOO data = *static_cast<L2E_SETUP_FOO *>(event->getUserData());
    for (int i = 0; i < 2; i++) {
        if(data.userId[i] == data.myUserId) {
            me = Hero::create();
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

void ActorLayer::looseBow(cocos2d::EventCustom *event)
{
    L2E_LOOSE data = *static_cast<L2E_LOOSE *>(event->getUserData());
    auto spear = Spear::create();
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
    
    spearVec.push_back(spear);
}

void ActorLayer::testLoose(float dt)
{
//    me->updateAI(dt);
}

void ActorLayer::update(float dt)
{
    for (auto iter = spearVec.begin(); iter != spearVec.end(); ) {
        if (!(*iter)->getAlive()) {
            removeChild((*iter));
            iter = spearVec.erase(iter);
            
        }else{
            iter++;
        }
    }

    for (auto arrow : spearVec) {
        if (arrow->getCurrState() != SPEAR_FLY) {
            continue;
        }
        
        float arrowAngle = arrow->getSpearAngle();
        Vec2 arrowPos = arrow->getArrowPos();

        if (arrow->getOwnerId() == me->getUserId())
        {
            int hitResult = master->hitCheck(arrowPos, 180-arrowAngle, Size(93, 15));
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
                    info.arrowAngle = arrowAngle;
                    info.arrowPosX = arrowPos.x;
                    info.arrowPosY = arrowPos.y;
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
                    info.arrowAngle = arrowAngle;
                    info.arrowPosX = arrowPos.x;
                    info.arrowPosY = arrowPos.y;
                    ClientLogic::instance()->ProcessUIRequest(&info);
                }
                    break;
            }
        }
    }
}
