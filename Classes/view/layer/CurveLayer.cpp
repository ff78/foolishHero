//
//  CurveLayer.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/26.
//

#include "CurveLayer.hpp"
#include "ELProtocol.h"
#include "EventDefine.h"
#include "GameUtils.h"

USING_NS_CC;

bool CurveLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    maxCurveId = 100000;
    return true;
}

void CurveLayer::onEnter()
{
    Layer::onEnter();
    setupHeroListener = EventListenerCustom::create(SETUP_HERO, CC_CALLBACK_1(CurveLayer::setupFoo, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(setupHeroListener, -1);
//    looseListener = EventListenerCustom::create(LOOSE_ARROW, CC_CALLBACK_1(CurveLayer::looseBow, this));
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(looseListener, -1);
}

void CurveLayer::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(setupHeroListener);
//    Director::getInstance()->getEventDispatcher()->removeEventListener(looseListener);
}

void CurveLayer::createCurve(float x, float y)
{
    maxCurveId++;
    maxCurveId %= INT_MAX;
    maxCurveId = MAX(100000, maxCurveId);
    
    auto curve = SpearCurve::create();
    curve->setTag(maxCurveId);
    curve->setStartpos(x, y, maxCurveId);
    addChild(curve);
}

void CurveLayer::removeCurve(int curveId)
{
    if (getChildByTag(curveId) == nullptr) {
        return;
    }
    
    removeChildByTag(curveId);
}

void CurveLayer::setupFoo(cocos2d::EventCustom *event)
{
    L2E_SETUP_FOO data = *static_cast<L2E_SETUP_FOO *>(event->getUserData());
    for (int i = 0; i < 2; i++) {
        if(data.userId[i] == data.myUserId) {
            float posx = GameUtils::winSize.width/2 - data.posx[i];
            if (data.flipX) {
                posx = GameUtils::winSize.width/2 + data.posx[i];
            }
            createCurve(posx, data.posy[i]);
            break;
        }
    }
}

void CurveLayer::adjustBow(float angle, float power, int curveId)
{
    if (getChildByTag(curveId) == nullptr) {
        return;
    }
    
    auto curve = (SpearCurve*)getChildByTag(curveId);
    curve->drawBow(angle, power);
}

void CurveLayer::looseBow(cocos2d::EventCustom *event)
{
    L2E_LOOSE data = *static_cast<L2E_LOOSE *>(event->getUserData());
    if (data.userId == data.myUserId) {
        if (getChildByTag(maxCurveId) == nullptr) {
            return;
        }
        
        ((SpearCurve*)getChildByTag(maxCurveId))->loose();
    }
}

void CurveLayer::testLoose(float dt)
{
    if (getChildByTag(maxCurveId) == nullptr) {
        return;
    }
    
    ((SpearCurve*)getChildByTag(maxCurveId))->update(dt);
}
