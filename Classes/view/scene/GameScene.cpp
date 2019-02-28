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
    
    bezierT = 0;
    
    bowListener = EventListenerCustom::create(DRAW_BOW, CC_CALLBACK_1(GameScene::drawBow, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(bowListener, -1);
    looseListener = EventListenerCustom::create(LOOSE_ARROW, CC_CALLBACK_1(GameScene::loose, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(looseListener, -1);
    hitListener = EventListenerCustom::create(HIT_HERO, CC_CALLBACK_1(GameScene::hitHero, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(hitListener, -1);
}


GameScene::~GameScene()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(bowListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(looseListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(hitListener);
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
    
    powerLayer = Layer::create();
    addChild(powerLayer);
    
    effectLayer = HitEffectLayer::create();
    addChild(effectLayer);
    
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
    if (actorLayer->getMe() == nullptr || actorLayer->getMe()->getCurrState() == DIE) {
        return;
    }
    if (drawBowing) {

//        if (bezierT < 1.0) {
//            float curr = cocos2d::tweenfunc::bezieratFunction(0, 2, 0.5, 1, bezierT);
//            log("%.3f", curr);
//
//            bezierT += 0.01;
//            bezierT = MIN(bezierT, 1.1);
//        }

        float angle = convertDrawAngle(dragLayer->getDragAngle());
        float vel = dragLayer->power2Velocity(dragLayer->getDragDistance());

        actorLayer->adjustBow(angle, vel);
        float curveAngle = angle;
        if (actorLayer->getMe()->getFlipX()) {
            curveAngle = 180-angle;
        }
        curveLayer->adjustBow(curveAngle, vel, actorLayer->getMe()->getCurveId());
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
    refreshPowerCurve();
    L2E_DRAW_A_BOW info = *static_cast<L2E_DRAW_A_BOW *>(event->getUserData());
    if (info.userId == info.myUserId) {
        if (actorLayer->getMe() == nullptr || actorLayer->getMe()->getCurrState() == DIE) {
            return;
        }
        drawBowing = true;
        auto guntipPos = actorLayer->getMe()->getGuntipPos();
        if(actorLayer->getMe()->getFlipX()){
            guntipPos.x = -guntipPos.x;
        }
        curveLayer->createCurve(guntipPos.x + actorLayer->getMe()->getPositionX(), guntipPos.y+actorLayer->getMe()->getPositionY());
        actorLayer->getMe()->setCurveId(curveLayer->getMaxCurveId());
        
//        float vel = power2Velocity(info.drawPower);
        actorLayer->drawBow(info.drawAngle, info.drawPower);
    }
    
}

void GameScene::loose(cocos2d::EventCustom *event)
{
    clearPowerCurve();
    L2E_LOOSE info = *static_cast<L2E_LOOSE *>(event->getUserData());
    if (info.userId == info.myUserId) {
        if (actorLayer->getMe() == nullptr || actorLayer->getMe()->getCurrState() == DIE) {
            return;
        }
        drawBowing = false;
        loosed = true;
        
        int curveId = actorLayer->getMe()->getCurveId();
        if (curveId != 0) {
            curveLayer->looseBow(event);
        }
    }
    actorLayer->looseBow(event);
}

void GameScene::hitHero(cocos2d::EventCustom *event)
{
    L2E_HIT_HERO data = *static_cast<L2E_HIT_HERO*>(event->getUserData());
    Hero *man;
    if (actorLayer->getMe() != nullptr && data.hitUserId == actorLayer->getMe()->getUserId()) {
        man = actorLayer->getMe();
    }else if (actorLayer->getMaster() != nullptr || data.hitUserId == actorLayer->getMaster()->getUserId()) {
        man = actorLayer->getMaster();
    }else{
        return;
    }
    int fontPosX = (man->getFlipX()?1:-1)*80;
    fontPosX += rand()%15;
    fontPosX += man->getPositionX();
    int fontPosY = man->getPositionY();
    
    effectLayer->addHurtNum(data.critType, data.hurtValue, Vec2(fontPosX, fontPosY));
    if (data.hurtBone == 1) {
        int imgPosX = (man->getFlipX()?-1:1)*30;
        imgPosX += man->getPositionX();
        effectLayer->addCritFlag(Vec2(imgPosX, fontPosY));
    }
    
}

float GameScene::convertDrawAngle(float angle)
{
    float sendAngle = angle;
    if (actorLayer->getMe()->getFlipX()) {//自己设定了翻转，把角度转成180到-180度
        sendAngle = 180 - angle;
    }else{
        if (angle > 180) {
            sendAngle = angle-360;
        }
        
    }
    //没翻转时把角度限制在75到-75度，否则角度应在105到180或-105到-180之间
    if (sendAngle >= 0) {
        if (actorLayer->getMe()->getFlipX()) {
            sendAngle = MIN(75, sendAngle);
//            sendAngle = MAX(105, sendAngle);
        } else {
            sendAngle = MIN(75, sendAngle);
        }
        
    } else {
        if (actorLayer->getMe()->getFlipX()) {
//            sendAngle = MIN(-105, sendAngle);
            sendAngle = MAX(-75, sendAngle);
        } else {
            sendAngle = MAX(-75, sendAngle);
        }
    }
    
    return sendAngle;
}

void GameScene::refreshPowerCurve()
{
    auto maxAxis = DrawNode::create();
    maxAxis->drawLine(Vec2(0, 500), Vec2(GameUtils::winSize.width, 500), Color4F::GREEN);
    powerLayer->addChild(maxAxis);
    for (int i = 0; i < 500; i++) {
        auto powerNode = DrawNode::create();
        float curr = cocos2d::tweenfunc::bezieratFunction(0, 0.2, 1.1, 1, i*0.002);
        powerNode->drawPoint(Vec2(i, curr*500), 1, Color4F::YELLOW);
        powerLayer->addChild(powerNode);
    }
}

void GameScene::clearPowerCurve()
{
    powerLayer->removeAllChildren();
}

//float GameScene::power2Velocity(float power)
//{
//    float bezT = (power-20)/300;
//    float curr = cocos2d::tweenfunc::bezieratFunction(0, 0.2, 1.1, 1, bezT);
//    return 20+300*curr;
//}

