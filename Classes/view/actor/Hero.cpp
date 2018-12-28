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
    
    curveId = 0;

    return true;
}

void Hero::onEnter()
{
    Node::onEnter();
}

void Hero::updateState()
{
    
}

void Hero::updateAI(float dt)
{

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


void Hero::drawBow(float emitAngle, float velocity)
{
    
}

void Hero::loose()
{

}
