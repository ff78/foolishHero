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
            drawABow();
        }else{
//            dragDistance = distance;
            dragDistance = MIN(320, distance);
        }
    }else{
        if(dragDistance == 0) {//没有开弓过，不要开弓
            dragAngle = 0;
            dragDistance = 0;
//            currPos = Vec2::ZERO;
        }else{//回到30以下，不改变角度，保证最短到20
            dragAngle = CC_RADIANS_TO_DEGREES((currPos-startPos).getAngle());
            dragAngle += 180;//反向是箭头角度
            dragDistance = MAX(20,distance);
        }
    }

}

void DragLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
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
    }else{
        bowString->clear();
    }
}

float DragLayer::power2Velocity(float power)
{
    float bezT = (power-20)/300;
    float curr = cocos2d::tweenfunc::bezieratFunction(0, 0.2, 1.1, 1, bezT);
    return 20+300*curr;
}
