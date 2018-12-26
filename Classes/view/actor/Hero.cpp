//
//  Hero.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#include "Hero.hpp"
#include "GameDefine.h"

USING_NS_CC;

Hero::Hero()
{
    
}

Hero::~Hero()
{
    
}

bool Hero::init()
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


    return true;
}

void Hero::onEnter()
{
    Node::onEnter();
}

void Hero::initGun()
{
//    startPos = getPosition();
//    controlPos = startPos;
//    endPos = startPos;
}

void Hero::updateState()
{
    
}

void Hero::updateAI(float dt)
{
    currDur += dt;
    currDur = MIN(currDur, dur);
    bezierT += dt;
    bezierT = MAX(0, MIN(1, bezierT));
//    log("bezierT:%f", bezierT);
//    Vec2 arrowNor = (arrowTailPos-arrowHeadPos).getNormalized();
//    float angle1 = CC_RADIANS_TO_DEGREES(arrowNor.getAngle());
//    log("角度1 angle1:%f", angle1);
    refreshArrow();
//    Vec2 arrowNor2 = (arrowTailPos-arrowHeadPos).getNormalized();
//    float angle2 = CC_RADIANS_TO_DEGREES(arrowNor2.getAngle());
//    log("角度2 angle2:%f", angle2);
//
//    float ratio = (angle2-angle1)/dt;
//    log("时间角度比：%f",ratio);
}

void Hero::changeState(int nextState)
{
    
}

void Hero::enterState(int nextState)
{
    
}

void Hero::exitState(int currState)
{
    
}

void Hero::changeActionWithName(int nextAction)
{
    
}

void Hero::doFlag(int nextFlag)
{
    
}

void Hero::refreshCurve()
{
    startPoint->setPosition(startPos);
    endPoint->setPosition(endPos);
    controlPoint->setPosition(controlPos);
    
    p0p1->clear();
    p0p2->clear();
    p1p2->clear();
    p0p1->drawLine(startPos, controlPos, Color4F(0,1,0,1));
    p0p2->drawLine(startPos, endPos,Color4F(0,1,0,1));
    p1p2->drawLine(controlPos, endPos,Color4F(0,1,0,1));
    
    bezierCurve->clear();
    bezierCurve->drawQuadBezier(startPos, controlPos, endPos, 50, Color4F(1, 0, 0, 1));
}

void Hero::refreshArrow()
{
    arrowPos.x = pow((1-bezierT), 2) * startPos.x + 2*bezierT*(1-bezierT) * controlPos.x + pow(bezierT, 2)*endPos.x;
    arrowPos.y = pow((1-bezierT), 2) * startPos.y + 2*bezierT*(1-bezierT) * controlPos.y + pow(bezierT, 2)*endPos.y;

    arrow->setPosition(arrowPos);

    arrowTailPos.x = (1-bezierT) * startPos.x + bezierT * controlPos.x;
    arrowTailPos.y = (1-bezierT) * startPos.y + bezierT * controlPos.y;
    arrowHeadPos.x = (1-bezierT) * controlPos.x + bezierT * endPos.x;
    arrowHeadPos.y = (1-bezierT) * controlPos.y + bezierT * endPos.y;

    arrowLine->clear();
    arrowLine->drawLine(arrowTailPos, arrowHeadPos, Color4F(0,1,0,1));
    arrowTail->setPosition(arrowTailPos);
    arrowHead->setPosition(arrowHeadPos);
//    Vec2 arrowNor = (arrowTailPos-arrowHeadPos).getNormalized();
//    log("刷新角度 angle:%f",CC_RADIANS_TO_DEGREES(arrowNor.getAngle()));f
}

float Hero::calcDurByDis(float distance)
{
    float t1 = (abs(speedy0) + sqrt(pow(speedy0, 2) - 2 * accel * distance)) /accel;
    
    float t2 = (abs(speedy0) - sqrt(pow(speedy0, 2) - 2 * accel * distance)) /accel;
    
    return MIN(abs(t1), abs(t2));
}

void Hero::calcControlPos()
{
    //正弦定理：一条边的长度/此边所对角的正弦值,等于另一条边的长度/这条边所对角的正弦值.即A/Sina=B/Sinb=C/Sinc
    auto vecC = Vec2(startPos - endPos);
    float lineC = startPos.getDistance(endPos);
    //起始点向量
    auto vecStart = Vec2(speedx, speedy0);
    auto velocityEndY = speedy0 + accel * dur;
    auto vecEnd = Vec2(-speedx, -velocityEndY);
    
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

    controlPos.y = sin(CC_DEGREES_TO_RADIANS(emitAngle))*lineA;
    controlPos.x = cos(CC_DEGREES_TO_RADIANS(emitAngle))*lineA;

}

void Hero::drawBow(float emitAngle, float velocity)
{
//    log("drawBow, emitAngle:%f", emitAngle);
    this->emitAngle = emitAngle;
    this->velocity = velocity/10;
    this->accel = -Accel/10;
    this->speedx = cos(CC_DEGREES_TO_RADIANS(emitAngle))*this->velocity;
    this->speedy0 = sin(CC_DEGREES_TO_RADIANS(emitAngle))*this->velocity;
    
    float distance = getPositionY() + startPos.y - GroundY;
    bezierT = 0.5;
    
    float dur1 = abs(speedy0/accel);
    if (speedy0 < 0) {
        dur1 = 0;
    }
    float dur2 = calcDurByDis(distance);
    dur = dur1*2 + dur2;
    endPos = Vec2(startPos.x+speedx * dur, -distance);
    calcControlPos();
    
    refreshCurve();
    refreshArrow();
}

void Hero::loose()
{
//    endPos = Vec2::ZERO;
//    controlPos = Vec2::ZERO;
//
//    endPoint->clear();
//    controlPoint->clear();
//
//    p0p1->clear();
//    p1p2->clear();
//    p0p2->clear();
//
//    bezierCurve->clear();
//
//    arrowPos = Vec2::ZERO;
//    arrowTailPos = Vec2::ZERO;
//    arrowHeadPos = Vec2::ZERO;
//
//    arrowLine->clear();
//    arrow->setPosition(arrowPos);
//    arrowTail->setPosition(arrowTailPos);
//    arrowHead->setPosition(arrowHeadPos);
    bezierT = 0;
    log("总时间：%f", dur);
}
