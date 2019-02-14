//
//  GameCore.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/11.
//

#ifndef GameCore_hpp
#define GameCore_hpp

#include "cocos2d.h"
#include "utils/GameUtils.h"
#include "ELProtocol.h"
#include "Load.h"

enum FIGHT_GAME_STATES
{
    FIGHT_GAME_NONE = 0,
    FIGHT_GAME_INIT = 1,
    FIGHT_GAME_NORMAL = 2,
    FIGHT_GAME_LOAD = 3,
    FIGHT_GAME_PAUSE = 4
};

class GameCore : public Singleton<GameCore>, public Load {
public:
    GameCore();
    ~GameCore();
    
    //改变战斗状态
    void changeGameState(FIGHT_GAME_STATES nextState);
    void enterGameState(FIGHT_GAME_STATES nextState);
    void exitGameState(FIGHT_GAME_STATES state);
    void backGameState();
    
    //根据状态分发逻辑
    void logic(float dt);
    
    void arrangeLoad();
    void load();
    
    void loadHero();
    void loadSpear();
    
    void drawMyBow(E2L_DRAW_A_BOW data);
    void looseMyArrow(E2L_LOOSE data);
    void hitHero(E2L_HIT_HERO data);
    
    float convertDrawAngle(float angle);
protected:
    virtual void onLoadFinish();
private:
    CC_SYNTHESIZE_READONLY(bool, flipXOpt, FlipXOpt);
    CC_SYNTHESIZE_READONLY(FIGHT_GAME_STATES, currState, CurrState);
    CC_SYNTHESIZE_READONLY(FIGHT_GAME_STATES, lastState, LastState);
    CC_SYNTHESIZE_READONLY(FIGHT_GAME_STATES, originState, OriginState);
};

#endif /* GameCore_hpp */
