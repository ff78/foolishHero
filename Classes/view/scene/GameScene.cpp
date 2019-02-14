//
//  GameScene.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#include "GameScene.hpp"
#include "ELProtocol.h"
#include "logic/ClientLogic.hpp"
#include "EventDefine.h"
#include "view/UIManager.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;

GameScene::GameScene()
{
    flipXOpt = false;
    drawBowing = false;
    loosed = false;
    
    bowListener = EventListenerCustom::create(DRAW_BOW, CC_CALLBACK_1(GameScene::drawBow, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(bowListener, -1);
    looseListener = EventListenerCustom::create(LOOSE_ARROW, CC_CALLBACK_1(GameScene::loose, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(looseListener, -1);
}


GameScene::~GameScene()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(bowListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(looseListener);
}

bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    curveLayer = CurveLayer::create();
    addChild(curveLayer);
    
    actorLayer = ActorLayer::create();
    addChild(this->actorLayer);
    
    dragLayer = DragLayer::create();
    addChild(dragLayer);
    

    return true;
}

void GameScene::onEnter()
{
    cocos2d::Scene::onEnter();
    
    scheduleUpdate();
}

void GameScene::onExit()
{
    cocos2d::Scene::onExit();
    unscheduleUpdate();
}

void GameScene::update(float dt)
{
    UIManager::instance()->loop(dt);
    if (drawBowing) {
        float angle = convertDrawAngle(dragLayer->getDragAngle());
        actorLayer->adjustBow(angle, dragLayer->getDragDistance());
        curveLayer->adjustBow(angle, dragLayer->getDragDistance(), actorLayer->getMe()->getCurveId());
    }else if (loosed) {
//        actorLayer->testLoose(dt);
        
        curveLayer->testLoose(dt);
    }
}

void GameScene::setupView(void *pMsg)
{
//    EventCustom event(SETUP_HERO);
//    event.setUserData(pMsg);
//    actorLayer->setupFoo(&event);
}

void GameScene::drawBow(cocos2d::EventCustom *event)
{
    L2E_DRAW_A_BOW info = *static_cast<L2E_DRAW_A_BOW *>(event->getUserData());
    if (info.userId == info.myUserId) {
        drawBowing = true;
        
        curveLayer->createCurve(actorLayer->getMe()->getPositionX(), actorLayer->getMe()->getPositionY());
        actorLayer->getMe()->setCurveId(curveLayer->getMaxCurveId());
        actorLayer->drawBow(info.drawAngle, info.drawPower);
    }
    
}

void GameScene::loose(cocos2d::EventCustom *event)
{
    L2E_LOOSE info = *static_cast<L2E_LOOSE *>(event->getUserData());
    if (info.userId == info.myUserId) {
        drawBowing = false;
        loosed = true;
        
        int curveId = actorLayer->getMe()->getCurveId();
        if (curveId != 0) {
            curveLayer->looseBow(event);
        }
    }
    actorLayer->looseBow(event);
}

float GameScene::convertDrawAngle(float angle)
{
    float sendAngle = angle;
//    if (flipXOpt == true) {//自己设定了翻转，把角度转成180到-180度
//        sendAngle = 180 - angle;
//    } else {
        if (angle > 180) {//没有翻转，把超过180的角度转为负角度
            sendAngle = angle-360;
        }
//    }
    //没翻转时把角度限制在75到-75度，否则角度应在105到180或-105到-180之间
    if (sendAngle >= 0) {
        if (flipXOpt) {
            sendAngle = MAX(105, sendAngle);
        } else {
            sendAngle = MIN(75, sendAngle);
        }
        
    } else {
        if (flipXOpt) {
            sendAngle = MIN(-105, sendAngle);
        } else {
            sendAngle = MAX(-75, sendAngle);
        }
    }
    
    return sendAngle;
}
