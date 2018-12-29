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
    
    //控制三角形
    startPos = Vec2::ZERO;
    controlPos = Vec2::ZERO;
    endPos = Vec2::ZERO;
    
    //切线
    arrowPos = Vec2::ZERO;
    arrowHeadPos = Vec2::ZERO;
    arrowTailPos = Vec2::ZERO;
    
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
