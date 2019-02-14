//
//  ClientLogic.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#ifndef ClientLogic_hpp
#define ClientLogic_hpp

#include "utils/GameUtils.h"
#include "ELProtocol.h"
#include "CSProtocol.h"
#include "TLProtocol.h"

enum E_GAME_STATE
{
    GAME_STATE_NONE,
    GAME_STATE_INIT,
    GAME_STATE_LOGO,
    GAME_STATE_FIGHT,

    GAME_STATE_HALL,
    GAME_STATE_MAX,
};

class ClientLogic : public Singleton<ClientLogic>
{
public:
    ClientLogic();
    
    void mainLoop(float dt);
    
    void (ClientLogic::*m_UI2LogicFunc[e2l_max])(void *pMsg);
    void (ClientLogic::*m_Service2ClientFunc[s2c_max])(void *pMsg);
    void (ClientLogic::*m_Time2ClientFunc[t2l_max])(void *pMsg);
    void (ClientLogic::*m_LogicStateFunc[GAME_STATE_MAX])(float dt);
    
    void ChangeState(E_GAME_STATE eState);
    
    //向显示层发送结构体消息
    void pass2Engine(void *pMsg);
    //处理显示层请求，实现见ProcessUIRequest.cpp
    void ProcessUIRequest(void *pMsg);
    
//    //向服务层发送结构体消息
//    void pass2Service(void *pMsg);
//    //处理服务层响应，实现见ProcessServerResponse.cpp
//    void ProcessServiceResponse(void *pMsg);
//    
//    //向计时层发送结构体消息
//    void pass2Time(void *pMsg);
//    //处理计时层响应，实现见ProcessTimeResponse.cpp
//    void ProcessTimeResponse(void *pMsg);
    
    void hasShownBattle(void *pMsg);
private:
    bool enterGameMode(E_GAME_STATE next);
    void exitGameMode(E_GAME_STATE currMode);
    void onStateFight(float dt);
    void onStateHall(float dt);
    void onStateInit(float dt);

    void BattleDrawBow(void *pMsg);
    void BattleLoose(void *pMsg);
    void BattleHitHero(void *pMsg);
    
    void test();
private:
    E_GAME_STATE m_eLastState;
    E_GAME_STATE m_eState;
    E_GAME_STATE cacheGameMode;
    
    //    std::vector<std::function<void()>> delayFunc;
};
#endif /* ClientLogic_hpp */
