//
//  DragLayer.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/19.
//

#include "DragLayer.hpp"
#include "ELProtocol.h"
#include "logic/ClientLogic.hpp"

USING_NS_CC;

DragLayer::DragLayer()
{
    inTouch = false;
    dragDistance = 0;
    dragAngle = 0;
    fingerId = -1;
    startPos = Vec2::ZERO;
    currPos = Vec2::ZERO;
    startC = Vec2(GameUtils::winSize/2) - Vec2(200, 0);
    currC = Vec2(GameUtils::winSize/2) + Vec2(250, 0);
    startRad = 20;
    currRad = 5;
}

DragLayer::~DragLayer()
{
}

bool DragLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(DragLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(DragLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(DragLayer::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(DragLayer::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    bowString = DrawNode::create();
    addChild(bowString);
    
    startCircle = DrawNode::create();
    startCircle->setPosition(startC);
//    startCircle->drawCircle(Vec2::ZERO, startRad, M_PI_2, 50, false, 1.0, 1, Color4F(1, 0, 0, 0.5));
    startCircle->drawSolidCircle(Vec2::ZERO, startRad, M_PI_2, 50, Color4F::RED);
    addChild(startCircle);
    
    currCircle = DrawNode::create();
    currCircle->setPosition(currC);
//    currCircle->drawCircle(Vec2::ZERO, currRad, M_PI_2, 50, false, 1.0, 1, Color4F(1, 0, 0, 0.5));
    currCircle->drawSolidCircle(Vec2::ZERO, currRad, M_PI_2, 50, Color4F::RED);
    addChild(currCircle);
    
    strenPoly = DrawNode::create();
    addChild(strenPoly);
    edge1 = DrawNode::create();
    addChild(edge1);
    edge2 = DrawNode::create();
    addChild(edge2);
    
    //    refreshEdge();
    
    return true;
}

void DragLayer::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
}

void DragLayer::onExit()
{
    Layer::onExit();
    unscheduleUpdate();
}

bool DragLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (fingerId == -1) {
        Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
        startPos = this->convertToNodeSpace(location);
        inTouch = true;
        fingerId = touch->getID();
//        this->hideHint();
        return true;
    }

    return false;
}

void DragLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (touch->getID() != fingerId) {
        return;
    }

    Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
    currPos = this->convertToNodeSpace(location);
    auto distance = startPos.getDistance(currPos);
    if (distance > 30 ) { //拉开大于30，才能开弓
        dragAngle = CC_RADIANS_TO_DEGREES((currPos-startPos).getAngle());
        dragAngle += 180;//反向是箭头角度
        if (dragDistance <= 30) {
//            dragDistance = distance;
            dragDistance = MIN(320, distance);
//            refreshEdge();
            drawABow();
        }else{
//            dragDistance = distance;
            dragDistance = MIN(320, distance);
//            refreshEdge();
        }
    }else{
        if(dragDistance == 0) {//没有开弓过，不要开弓
            dragAngle = 0;
            dragDistance = 0;
//            hideHint();
//            currPos = Vec2::ZERO;
        }else{//回到30以下，不改变角度，保证最短到20
            dragAngle = CC_RADIANS_TO_DEGREES((currPos-startPos).getAngle());
            dragAngle += 180;//反向是箭头角度
            dragDistance = MAX(20,distance);
//            refreshEdge();
        }
    }

}

void DragLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (touch->getID() != fingerId) {
        return;
    }
//    this->hideHint();
    if (dragDistance != 0) {//拉开过，放箭
        loose();
    }
    fingerId = -1;
    dragDistance = 0;
    dragAngle = 0;
    startPos = Vec2::ZERO;
    currPos = Vec2::ZERO;
}

void DragLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (touch->getID() != fingerId) {
        return;
    }
    if (dragDistance != 0) {//拉开过，放箭
        loose();
    }
    fingerId = -1;
    dragDistance = 0;
    dragAngle = 0;
    startPos = Vec2::ZERO;
    currPos = Vec2::ZERO;
}

void DragLayer::drawABow()
{
//    log("拉开弓    角度:%f,  长度:%f", dragAngle, dragDistance);
    E2L_DRAW_A_BOW info;
    info.eProtocol = e2l_draw_bow;
    info.drawAngle = dragAngle;
    info.drawPower = power2Velocity(dragDistance);
    ClientLogic::instance()->ProcessUIRequest(&info);
}

void DragLayer::loose()
{
//    log("放箭    角度:%f,  长度:%f", dragAngle, dragDistance);
    bowString->clear();
    
    E2L_LOOSE info;
    info.eProtocol = e2l_loose;
    info.drawAngle = dragAngle;
    info.drawPower = power2Velocity(dragDistance);
    ClientLogic::instance()->ProcessUIRequest(&info);
}

void DragLayer::update(float dt)
{
    if (startPos != Vec2::ZERO && currPos != Vec2::ZERO) {
        bowString->clear();
        bowString->drawLine(startPos, currPos, Color4F(0, 0, 1, 1));
        startCircle->setPosition(startPos);
        currCircle->setPosition(currPos);
        refreshEdge();
    }else{
        bowString->clear();
        hideHint();
    }
}

float DragLayer::power2Velocity(float power)
{
    float bezT = (power-20)/300;
    float curr = cocos2d::tweenfunc::bezieratFunction(0, 0.2, 1.1, 1, bezT);
    return 20+300*curr;
}

void DragLayer::refreshEdge()
{
    if (startPos == Vec2::ZERO || currPos == Vec2::ZERO) {
        edge1->clear();
        edge2->clear();
        return;
    }
    Vec2 c2c = currPos - startPos;
    float dis = c2c.length();
    if (dis < startRad) {
        radDisAngle = 0;
        return;
    }else{
        currRad = MIN((dis-20), 200)/200*20+5;
//        log("越来越大：%.2f",currRad);
        startRad = 25-MIN((dis-20), 200)/200*20;
//        log("越来越小：%.2f",startRad);
        if (startRad != currRad)
        {
            radDisAngle = CC_RADIANS_TO_DEGREES(asin(abs(startRad - currRad)/dis));
//            log("radDisAngle = %.2f", radDisAngle);
            if (startRad > currRad) {
                radDisAngle = 90 - radDisAngle;
            }else {
                radDisAngle += 90;
            }
        }else{
            radDisAngle = 0;
        }
    }

    float c2cAngle = CC_RADIANS_TO_DEGREES(c2c.getAngle());
    float edge1Angle = c2cAngle+radDisAngle;
    float edge2Angle = c2cAngle-radDisAngle;
//    log("edge1Angle = %.2f", edge1Angle);
//    log("edge2Angle = %.2f", edge2Angle);
    auto edge1StartPos = startPos + Vec2::forAngle(CC_DEGREES_TO_RADIANS(edge1Angle))*startRad;
    auto edge1CurrPos = currPos + Vec2::forAngle(CC_DEGREES_TO_RADIANS(edge1Angle))*currRad;
    auto edge2StartPos = startPos+Vec2::forAngle(CC_DEGREES_TO_RADIANS(edge2Angle))*startRad;
    auto edge2CurrPos = currPos + Vec2::forAngle(CC_DEGREES_TO_RADIANS(edge2Angle))*currRad;
    Vec2 vertices[] = {
        edge1StartPos,
        edge1CurrPos,
        edge2CurrPos,
        edge2StartPos
    };
    strenPoly->clear();
    strenPoly->drawSolidPoly(vertices, 4, Color4F::RED);
    
    auto point1Temp = MIN((dis-20), 200)/200*(edge2CurrPos-edge1CurrPos)+edge1CurrPos;
    auto control1Point = point1Temp.getMidpoint(edge1StartPos);
    auto point2Temp = MIN((dis-20), 200)/200*(edge1CurrPos-edge2CurrPos)+edge2CurrPos;
    auto control2Point = point2Temp.getMidpoint(edge2StartPos);
    edge1->clear();
    edge2->clear();
    edge1->drawQuadBezier(edge1StartPos, control1Point, edge1CurrPos, 50, Color4F::GREEN);
//    edge1->drawLine(edge1StartPos, edge1CurrPos, Color4F::GREEN);
//    edge2->drawLine(edge2StartPos, edge2CurrPos, Color4F::GREEN);
    edge2->drawQuadBezier(edge2StartPos, control2Point, edge2CurrPos, 50, Color4F::GREEN);
    startCircle->clear();
    startCircle->drawSolidCircle(Vec2::ZERO, startRad, M_PI_2, 50, Color4F::RED);
    currCircle->clear();
    currCircle->drawSolidCircle(Vec2::ZERO, currRad, M_PI_2, 50, Color4F::RED);

//    Vec2 c2c = currC - startC;
//    float dis = c2c.length();
////    currRad = 10 + 40*MAX(0, MIN(dis-20,200))/200;
//    if (startRad != currRad)
//    {
//        // todo
//        radDisAngle = CC_RADIANS_TO_DEGREES(asin(abs(startRad - currRad)/dis));
//        log("radDisAngle = %.2f", radDisAngle);
//        if (startRad > currRad) {
//            radDisAngle = 90 - radDisAngle;
//        }else {
//            radDisAngle += 90;
//        }
//    }else{
//        radDisAngle = 0;
//    }
//
//    float c2cAngle = CC_RADIANS_TO_DEGREES(c2c.getAngle());
////    float c2cAngle = dragAngle;
//    float edge1Angle = c2cAngle+radDisAngle;
//    float edge2Angle = c2cAngle-radDisAngle;
//    log("edge1Angle = %.2f", edge1Angle);
//    log("edge2Angle = %.2f", edge2Angle);
//    auto edge1StartPos = startC + Vec2::forAngle(CC_DEGREES_TO_RADIANS(edge1Angle))*startRad;
//    auto edge1CurrPos = currC + Vec2::forAngle(CC_DEGREES_TO_RADIANS(edge1Angle))*currRad;
//    auto edge2StartPos = startC+Vec2::forAngle(CC_DEGREES_TO_RADIANS(edge2Angle))*startRad;
//    auto edge2CurrPos = currC + Vec2::forAngle(CC_DEGREES_TO_RADIANS(edge2Angle))*currRad;
//    edge1->clear();
//    edge2->clear();
//    edge1->drawLine(edge1StartPos, edge1CurrPos, Color4F::GREEN);
//    edge2->drawLine(edge2StartPos, edge2CurrPos, Color4F::GREEN);
//
////    startCircle->setPosition(startPos);
////    currCircle->setPosition(currPos);
}

void DragLayer::hideHint()
{
    strenPoly->clear();
    startCircle->clear();
    currCircle->clear();
    edge1->clear();
    edge2->clear();
}
