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
}

void ActorLayer::onExit()
{
    Layer::onExit();
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
            addChild(me);
        }else {
            master = Hero::create();
            float posx = GameUtils::winSize.width/2 + data.posx[i];
            if (data.flipX) {
                posx = GameUtils::winSize.width/2 - data.posx[i];
            }
            master->setPosition(posx, data.posy[i]);
            master->setFlipX(!data.flipX);
            addChild(master);
        }
    }

//    me->initGun();
}

void ActorLayer::adjustBow(float angle, float power)
{
    me->drawBow(angle, power);
}

void ActorLayer::looseBow(cocos2d::EventCustom *event)
{
    L2E_LOOSE data = *static_cast<L2E_LOOSE *>(event->getUserData());
    if (data.userId == data.myUserId) {
        me->loose();
        float angle = data.drawAngle;
        if (me->getFlipX()) {
            angle = 180-data.drawAngle;
            if (data.drawAngle < 0) {
                angle -= 360;
            }
        }
    }else{
        float angle = data.drawAngle;
        if (!master->getFlipX()) {
            angle = 180-data.drawAngle;
            if (data.drawAngle < 0) {
                angle -= 360;
            }
        }
    }
}

void ActorLayer::testLoose(float dt)
{
    me->updateAI(dt);
}
