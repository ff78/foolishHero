//
//  Spear.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#ifndef Spear_hpp
#define Spear_hpp

#include "cocos2d.h"
#include "ELProtocol.h"
#include "cocoStudio/CocoStudio.h"

enum SPEAR_STATES
{
    SPEAR_INCASE = 0,
    SPEAR_DRAW = 1,
    SPEAR_FLY = 2,
    SPEAR_STAB = 3,
    SPEAR_MAX,
};

class Spear : public cocos2d::Node
{
public:
    Spear();
    ~Spear();
    
    bool init();
    void onEnter();
    void onExit();

    void setupWithData(L2E_LOOSE data, bool flipX, cocos2d::Vec2 pos);

    void exitState(SPEAR_STATES currState);
    void enterState(SPEAR_STATES nextState);
    void changeState(SPEAR_STATES nextState);

    
    void refreshArrow();
    
    float calcDurByDis(float distance);
    void calcControlPos();
    
    void drawBow(float emitAngle, float velocity);
    void update(float dt);
    
    void disappear();
    
    CREATE_FUNC(Spear);
    
private:
    cocos2d::Sprite *spt;
    
    //曲线3顶点
    cocos2d::Vec2 startPos;
    cocos2d::Vec2 endPos;
    cocos2d::Vec2 controlPos;
    
    cocos2d::Vec2 arrowTailPos;
    cocos2d::Vec2 arrowHeadPos;
    
    float bezierT;
    
    float speedx;
    float speedy0;
    float accel;
    float emitAngle;
    float velocity;
    
    float dur;
    float currDur;
    
    CC_SYNTHESIZE_READONLY(float, alive, Alive);
    CC_SYNTHESIZE(int, ownerId, OwnerId);
    CC_SYNTHESIZE_READONLY(cocos2d::Vec2, arrowPos, ArrowPos);
    CC_SYNTHESIZE_READONLY(float, spearAngle, SpearAngle);
    CC_SYNTHESIZE_READONLY(SPEAR_STATES, currState, CurrState);
    CC_SYNTHESIZE_READONLY(SPEAR_STATES, lastState, LastState);
    CC_SYNTHESIZE_READONLY(SPEAR_STATES, originState, OriginState);
    
};

#endif /* Spear_hpp */
