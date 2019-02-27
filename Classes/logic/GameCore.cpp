//
//  GameCore.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/11.
//

#include "GameCore.hpp"
#include "ELProtocol.h"
#include "GameDefine.h"
#include "ClientLogic.hpp"
#include "utils/TimeUtil.h"

USING_NS_CC;

GameCore::GameCore() :
currState(FIGHT_GAME_NONE),
lastState(FIGHT_GAME_NONE),
originState(FIGHT_GAME_NONE)
{
    flipXOpt = false;
}

GameCore::~GameCore()
{
    currState = FIGHT_GAME_NONE;
    lastState = FIGHT_GAME_NONE;
    originState = FIGHT_GAME_NONE;
}

void GameCore::changeGameState(FIGHT_GAME_STATES nextState)
{
    if(currState == nextState)
        return;
    log("change state from %d to %d", currState, nextState);
    exitGameState(currState);
    lastState    = currState;
    currState        = nextState;
    enterGameState(nextState);
}

void GameCore::enterGameState(FIGHT_GAME_STATES nextState)
{
    switch (nextState) {
        case FIGHT_GAME_LOAD:
        {
            arrangeLoad();
        }
            break;
        case FIGHT_GAME_INIT:
        {

        }
            break;
        default:
            break;
    }
}

void GameCore::exitGameState(FIGHT_GAME_STATES state)
{
    switch (state) {
        default:
            break;
    }
}

void GameCore::backGameState()
{
    exitGameState(currState);
    currState = lastState;
    log("back to currState: %d", currState);
}

void GameCore::logic(float dt)
{
    switch (currState) {
        case FIGHT_GAME_LOAD:
        {
            load();
        }
            break;
        case FIGHT_GAME_NORMAL:
        {
//            battleField->update(dt);
        }
            break;
        default:
            break;
    }
    
}

void GameCore::arrangeLoad()
{
    addLoadFunc(Load::LoadFunc(&GameCore::loadHero));
    
    L2E_COMMON info;
    info.eProtocol = l2e_show_battle_load;
    ClientLogic::instance()->pass2Engine(&info);
}

void GameCore::load()
{
    L2E_UPDATE_LOAD info;
    info.eProtocol = l2e_update_battle_load;
    info.isOver = false;
    info.step = 0;
    info.count = (int)m_vecLoadFunc.size();
    int result = Load::load();
    if (result != -1) {
        info.step = result;
        //更新加载界面
        ClientLogic::instance()->pass2Engine(&info);
    }else{
        onLoadFinish();
    }
}

void GameCore::onLoadFinish()
{
    Load::onLoadFinish();
    
    changeGameState(FIGHT_GAME_NORMAL);
}

void GameCore::loadHero()
{
    L2E_SETUP_FOO info;
    info.eProtocol = l2e_setup_foo;
//    float posx[2] = {-GameUtils::winSize.width/4, GameUtils::winSize.width/4};
//    int userId[2] = {101, 778};
    srand((unsigned int)(TimeUtil::get_system_tick_s()));
    float posx[2] = {GameUtils::winSize.width/4, GameUtils::winSize.width/4};
    int userId[2] = {101, 778};
    for (int i = 0; i < 2; i++) {
        info.posx[i] = posx[i] + rand()%50;
        info.posy[i] = ceil(rand()%3+1)*GameUtils::winSize.height/8;
    }
    memcpy(info.userId, userId, sizeof(int)*2);
    info.myUserId = 101;
    
    info.flipX = flipXOpt;
    ClientLogic::instance()->pass2Engine(&info);
}

void GameCore::drawMyBow(E2L_DRAW_A_BOW data)
{
    float sendAngle = convertDrawAngle(data.drawAngle);
    //此处应改为向服务器发送，再等待服务器广播
    L2E_DRAW_A_BOW info;
    info.eProtocol = l2e_draw_bow;
    info.userId = 101;
    info.myUserId = 101;
    info.drawAngle = sendAngle;
    info.drawPower = data.drawPower;
    ClientLogic::instance()->pass2Engine(&info);
    
    L2E_DRAW_A_BOW info2;
    info2.eProtocol = l2e_draw_bow;
    info2.userId = 778;
    info2.myUserId = 101;
    info2.drawAngle = sendAngle;
    info2.drawPower = data.drawPower;
    ClientLogic::instance()->pass2Engine(&info2);
}

void GameCore::looseMyArrow(E2L_LOOSE data)
{
    float sendAngle = convertDrawAngle(data.drawAngle);
    //此处应改为向服务器发送，再等待服务器广播
    L2E_LOOSE info;
    info.eProtocol = l2e_loose;
    info.userId = 101;
    info.myUserId = 101;
    info.drawAngle = sendAngle;
    info.drawPower = data.drawPower;
    ClientLogic::instance()->pass2Engine(&info);
    
    L2E_LOOSE info2;
    info2.eProtocol = l2e_loose;
    info2.userId = 778;
    info2.myUserId = 101;
    info2.drawAngle = sendAngle;
    info2.drawPower = data.drawPower;
    ClientLogic::instance()->pass2Engine(&info2);
}

void GameCore::hitHero(E2L_HIT_HERO data)
{
//    float sendAngle = convertDrawAngle(data.arrowAngle);
    //此处应改为向服务器发送，再等待服务器广播
    L2E_HIT_HERO info;
    info.eProtocol = l2e_hit_hero;
    info.hitUserId = data.hitUserId;
    info.hurtBone = data.hurtBone;
    info.arrowId = data.arrowId;
    info.arrowAngle = data.arrowAngle;
    info.arrowPosX = data.arrowPosX;
    info.arrowPosY = data.arrowPosY;
    info.hurtValue = 153;
    info.critType = 0;
    ClientLogic::instance()->pass2Engine(&info);
}

float GameCore::convertDrawAngle(float angle)
{
    float sendAngle = angle;
    if (flipXOpt == true) {//自己设定了翻转，把角度转成180到-180度
        sendAngle = 180 - angle;
    } else {
        if (angle > 180) {//没有翻转，把超过180的角度转为负角度
            sendAngle = angle-360;
        }
    }
    //把角度限制在75到-75度
    if (sendAngle >= 0) {
        sendAngle = MIN(75, sendAngle);
    } else {
        sendAngle = MAX(-75, sendAngle);
    }
    
    return sendAngle;
}
