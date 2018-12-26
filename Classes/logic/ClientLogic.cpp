//
//  ClientLogic.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#include "ClientLogic.hpp"
#include "SystemLogic.hpp"
#include "GameCore.hpp"
#include "view/UIManager.hpp"

ClientLogic::ClientLogic()
{
    m_eLastState = GAME_STATE_NONE;
    m_eState = GAME_STATE_NONE;
    
    //    delayFunc.clear();
    
    memset(m_UI2LogicFunc, 0, sizeof(m_UI2LogicFunc));
    memset(m_LogicStateFunc, 0, sizeof(m_LogicStateFunc));
    
    m_UI2LogicFunc[e2l_shown_battle] = &ClientLogic::hasShownBattle;
    m_UI2LogicFunc[e2l_draw_bow] = &ClientLogic::BattleDrawBow;
    m_UI2LogicFunc[e2l_loose] = &ClientLogic::BattleLoose;
    
    m_LogicStateFunc[GAME_STATE_INIT] = &ClientLogic::onStateInit;
    m_LogicStateFunc[GAME_STATE_FIGHT] = &ClientLogic::onStateFight;
    m_LogicStateFunc[GAME_STATE_HALL] = &ClientLogic::onStateHall;
}
void ClientLogic::mainLoop(float dt)
{
//    TimeUtil::updateServerTime(dt);
    if (this->m_LogicStateFunc[m_eState] == nullptr) {
        return;
    }
    (this->*m_LogicStateFunc[m_eState])(dt);
}

//改变游戏状态
void ClientLogic::ChangeState(E_GAME_STATE eState)
{
    if(m_eState == eState)
        return;
    exitGameMode(m_eState);
    m_eLastState    = m_eState;
    m_eState        = eState;
    enterGameMode(eState);
}

//进入游戏状态前的准备处理
bool ClientLogic::enterGameMode(E_GAME_STATE next)
{
    switch(next)
    {
        case GAME_STATE_LOGO:
        {
//            SystemLogic::instance()->showLogo();
        }
            break;
        case GAME_STATE_INIT:
        {
            SystemLogic::instance()->arrangeLoad();
        }
            break;
        case GAME_STATE_FIGHT:
        {            
            GameCore::instance()->changeGameState(FIGHT_GAME_LOAD);
        }
            break;
        case GAME_STATE_HALL:
        {
            SystemLogic::instance()->showBattle();
        }
            break;
        default:
            break;
    }
    return true;
}

//离开游戏状态的结束处理
void ClientLogic::exitGameMode(E_GAME_STATE currMode)
{
    switch (currMode) {
            
        default:
            break;
    }
}

void ClientLogic::onStateFight(float dt)
{
    GameCore::instance()->logic(dt);
}

void ClientLogic::onStateHall(float dt)
{
    SystemLogic::instance()->logic(dt);
}

void ClientLogic::onStateInit(float dt)
{
    SystemLogic::instance()->load();
}

//发送结构体通知给显示层
void ClientLogic::pass2Engine(void *pMsg)
{
    UIManager::instance()->processLogicResponse(pMsg);
}

