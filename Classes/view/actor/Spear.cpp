//
//  Spear.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#include "Spear.hpp"
#include "ELProtocol.h"
#include "EventDefine.h"

USING_NS_CC;
using namespace cocostudio;

Spear::Spear()
{
    currState = MAX;
    originState = MAX;
    lastState = MAX;
}

Spear::~Spear()
{
    
}

bool Spear::init()
{
    if (!Node::init()) {
        return false;
    }
    //曲线
    bezierT = 0;
    currDur = 0;
    bezierCurve = DrawNode::create();
    bezierCurve->clear();
    addChild(bezierCurve);
    
    //控制三角形
    startPos = Vec2::ZERO;
    controlPos = Vec2::ZERO;
    endPos = Vec2::ZERO;
    
    p0p1 = DrawNode::create();
    p0p2 = DrawNode::create();
    p1p2 = DrawNode::create();
    p0p1->clear();
    p0p2->clear();
    p1p2->clear();
    addChild(p0p1);
    addChild(p0p2);
    addChild(p1p2);
    
    startPoint = DrawNode::create();
    startPoint->setPosition(startPos);
    startPoint->clear();
    startPoint->drawCircle(Vec2::ZERO, 20, M_PI_2, 50, false, 1.0, 1, Color4F(1, 0, 0, 0.5));
    addChild(startPoint);
    endPoint = DrawNode::create();
    endPoint->setPosition(endPos);
    endPoint->clear();
    endPoint->drawCircle(Vec2::ZERO, 20, M_PI_2, 50, false, 1.0, 1, Color4F(1, 0, 0, 0.5));
    addChild(endPoint);
    controlPoint = DrawNode::create();
    controlPoint->setPosition(controlPos);
    controlPoint->clear();
    controlPoint->drawCircle(Vec2::ZERO, 20, M_PI_2, 50, false, 1.0, 1, Color4F(1, 0, 0, 0.5));
    addChild(controlPoint);
    
    //切线
    arrowPos = Vec2::ZERO;
    arrowHeadPos = Vec2::ZERO;
    arrowTailPos = Vec2::ZERO;
    
    arrowLine = DrawNode::create();
    arrowLine->clear();
    addChild(arrowLine);
    arrow = DrawNode::create();
    arrow->clear();
    arrow->drawPoint(Vec2::ZERO, 4, Color4F(1, 1, 1, 1));
    addChild(arrow);
    arrowHead = DrawNode::create();
    arrowHead->clear();
    arrowHead->drawPoint(Vec2::ZERO, 4, Color4F(0, 0, 1, 1));
    addChild(arrowHead);
    arrowTail = DrawNode::create();
    arrowTail->clear();
    arrowTail->drawPoint(Vec2::ZERO, 4, Color4F(0, 0, 1, 1));
    addChild(arrowTail);
    
    spt = Sprite::create("baobingjianbody.png");
    spt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    addChild(spt);
    
    
    return true;
}

void Spear::onEnter()
{
    Node::onEnter();
    changeState(INCASE);
}

void Spear::onExit()
{
    
}

void Spear::setupWithData(cocos2d::EventCustom *event)
{
//    L2E_EMIT_SPEAR info = *static_cast<L2E_EMIT_SPEAR *>(event->getUserData());
//
//    this->emitAngle = info.angle;
//    this->emitSpeed = info.speed;
//    this->startPos =  Vec2(info.emitPosX, info.emitPosY);
}

void Spear::logic(float dt)
{
    
}

void Spear::changeState(SPEAR_STATES nextState)
{
    if(currState == nextState)
        return;
    log("change spear state from %d to %d", currState, nextState);
    exitState(currState);
    lastState    = currState;
    currState    = nextState;
    enterState(nextState);
}

void Spear::enterState(SPEAR_STATES nextState)
{
    switch (nextState) {
        case INCASE:
            bezierT = 0;
            currDur = 0;
            spt->setVisible(false);
            break;
            
        default:
            break;
    }
}

void Spear::exitState(SPEAR_STATES currState)
{
    
}

void Spear::drawBow(float emitAngle, float velocity)
{
    
}
