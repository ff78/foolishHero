//
//  ProcessUIRequest.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/11.
//

#include "ClientLogic.hpp"
#include "ELProtocol.h"
#include "GameCore.hpp"
#include "SystemLogic.hpp"

void ClientLogic::ProcessUIRequest(void *pMsg)
{
    if (NULL == pMsg)
        return;
    
    E2LProtocol    eProtocol    = *((E2LProtocol*)pMsg);
    if (eProtocol >= e2l_max)
        return;
    //分发到各个协议的处理函数
    if (this->m_UI2LogicFunc[eProtocol] != NULL)
    {
        (this->*m_UI2LogicFunc[eProtocol])(pMsg);
    }
}

void ClientLogic::hasShownBattle(void *pMsg)
{
    ClientLogic::instance()->ChangeState(GAME_STATE_FIGHT);
}

void ClientLogic::BattleDrawBow(void *pMsg)
{
    E2L_DRAW_A_BOW *pMsgInfo = (E2L_DRAW_A_BOW *)pMsg;
    GameCore::instance()->drawMyBow(*pMsgInfo);
}

void ClientLogic::BattleLoose(void *pMsg)
{
    E2L_LOOSE *pMsgInfo = (E2L_LOOSE *)pMsg;
    GameCore::instance()->looseMyArrow(*pMsgInfo);
}
