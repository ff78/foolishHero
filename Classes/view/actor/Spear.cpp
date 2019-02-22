//
//  Spear.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#include "Spear.hpp"
#include "EventDefine.h"

USING_NS_CC;
using namespace cocostudio;

Spear::Spear()
{
    currState = SPEAR_MAX;
    originState = SPEAR_MAX;
    lastState = SPEAR_MAX;
    spearAngle = 0;
    arrowId = -1;
    alive = true;
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
    spt->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(spt);

    return true;
}

void Spear::onEnter()
{
    Node::onEnter();
    changeState(SPEAR_INCASE);
}

void Spear::onExit()
{
    Node::onExit();
    currState = SPEAR_MAX;
    originState = SPEAR_MAX;
    lastState = SPEAR_MAX;
    spearAngle = 0;
}

void Spear::setupWithData(L2E_LOOSE data, bool flipX, cocos2d::Vec2 pos)
{
    float angle = data.drawAngle;
    if (flipX) {
        angle = 180-data.drawAngle;
        if (data.drawAngle < 0) {
            angle -= 360;
        }
    }
    this->emitAngle = angle;
    this->startPos =  pos;

    setPosition(pos);
    setScaleX(flipX?-1:1);
    drawBow(data.drawAngle, data.drawPower);
    
    changeState(SPEAR_FLY);
}

void Spear::update(float dt)
{
    switch(currState)
    {
        case SPEAR_FLY:
        {
            currDur += dt*50;//太慢，尝试放大50倍
            currDur = MIN(currDur, dur);
            bezierT = currDur/dur;
            bezierT = MAX(0, MIN(1, bezierT));
            log("----------------分割线------------------");
            log("currDur:%.2f", currDur);
            log("bezierT:%.2f", bezierT);
            
            refreshArrow();
            if (bezierT >= 1.0) {
                bezierT = 0;
                changeState(SPEAR_STAB);
            }
        }
            break;
            
    }
}

void Spear::changeState(SPEAR_STATES nextState)
{
    if(currState == nextState)
        return;
//    log("change spear state from %d to %d", currState, nextState);
    exitState(currState);
    lastState    = currState;
    currState    = nextState;
    enterState(nextState);
}

void Spear::enterState(SPEAR_STATES nextState)
{
    switch (nextState) {
        case SPEAR_INCASE:
        {
            alive = true;
            bezierT = 0;
            currDur = 0;
            spearAngle = 0;
            spt->setVisible(false);
        }
            break;
        case SPEAR_FLY:
        {
            alive = true;
            bezierT = 0;
            currDur = 0;
            spearAngle = emitAngle;
            spt->setVisible(true);
            scheduleUpdate();
        }
            break;
            
        case SPEAR_STAB:
        {
            bezierT = 0;
            currDur = 0;
            unscheduleUpdate();
            auto delay = DelayTime::create(5);
            auto fadeOut = FadeOut::create(0.5);
            auto removeFunc = CallFunc::create(CC_CALLBACK_0(Spear::disappear, this));
            auto seq = Sequence::create(delay, fadeOut, removeFunc, NULL);
            runAction(seq);
        }
            break;
        case SPEAR_INTERUPT:
        {
            alive = false;
            spt->setVisible(false);
            bezierT = 0;
            currDur = 0;
            unscheduleUpdate();
        }
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
    this->emitAngle = emitAngle;
    this->velocity = velocity/10;
    this->accel = -Accel/10;
    this->speedx = cos(CC_DEGREES_TO_RADIANS(emitAngle))*this->velocity;
    this->speedy0 = sin(CC_DEGREES_TO_RADIANS(emitAngle))*this->velocity;
    
    float distance = startPos.y - GroundY;
    
    float dur1 = abs(speedy0/accel);
    if (speedy0 < 0) {
        dur1 = 0;
    }
    float dur2 = calcDurByDis(distance);
    dur = dur1*2 + dur2;
    endPos = Vec2(startPos.x+speedx * dur, GroundY);
    calcControlPos();
}

float Spear::calcDurByDis(float distance)
{
    float t1 = (abs(speedy0) + sqrt(pow(speedy0, 2) - 2 * accel * distance)) /accel;
    
    float t2 = (abs(speedy0) - sqrt(pow(speedy0, 2) - 2 * accel * distance)) /accel;
    
    return MIN(abs(t1), abs(t2));
}

void Spear::calcControlPos()
{
    //正弦定理：一条边的长度/此边所对角的正弦值,等于另一条边的长度/这条边所对角的正弦值.即A/Sina=B/Sinb=C/Sinc
    auto vecC = Vec2(endPos- startPos);
    float lineC = startPos.getDistance(endPos);
    //起始点向量
    auto vecStart = Vec2(speedx, speedy0);
    auto velocityEndY = speedy0 + accel * dur;
    auto vecEnd = Vec2(speedx, velocityEndY);
    
    //    log("start: %f, %f", speedx, speedy0);
    //    log("end: %f, %f", -speedx,-velocityEndY);
    //两速度向量夹角即角C
    
    //    Vec2 normalStart = vecStart.getNormalized();
    //    float angleC = acos(normalStart.dot(vecEnd.getNormalized()));
    float angleC = CC_RADIANS_TO_DEGREES(acos(vecStart.getNormalized().dot(vecEnd.getNormalized())));
    //    log("速度夹角：%f", angleC);
    
    float angleA = CC_RADIANS_TO_DEGREES(acos(vecC.getNormalized().dot(vecEnd.getNormalized())));
    //    log("最终速度与落点夹角：%f", angleA);
    
    float lineA = lineC * sin(CC_DEGREES_TO_RADIANS(angleA)) / sin(CC_DEGREES_TO_RADIANS(angleC));
    
    controlPos.y = sin(CC_DEGREES_TO_RADIANS(emitAngle))*lineA+startPos.y;
    controlPos.x = cos(CC_DEGREES_TO_RADIANS(emitAngle))*lineA+startPos.x;
    
}

void Spear::refreshArrow()
{
    arrowPos.x = pow((1-bezierT), 2) * startPos.x + 2*bezierT*(1-bezierT) * controlPos.x + pow(bezierT, 2)*endPos.x;
    arrowPos.y = pow((1-bezierT), 2) * startPos.y + 2*bezierT*(1-bezierT) * controlPos.y + pow(bezierT, 2)*endPos.y;
    
    setPosition(arrowPos);
    
    arrowTailPos.x = (1-bezierT) * startPos.x + bezierT * controlPos.x;
    arrowTailPos.y = (1-bezierT) * startPos.y + bezierT * controlPos.y;
    arrowHeadPos.x = (1-bezierT) * controlPos.x + bezierT * endPos.x;
    arrowHeadPos.y = (1-bezierT) * controlPos.y + bezierT * endPos.y;
    
    Vec2 arrowNor = (arrowHeadPos-arrowTailPos).getNormalized();
    spearAngle = CC_RADIANS_TO_DEGREES(arrowNor.getAngle());
//    log("刷新角度 angle:%f", spearAngle);
    spt->setRotation(-spearAngle);
    
}

void Spear::disappear()
{
    alive = false;
//    removeFromParent();
}
