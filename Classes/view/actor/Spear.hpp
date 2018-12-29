//
//  Spear.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#ifndef Spear_hpp
#define Spear_hpp

#include "cocos2d.h"
#include "cocoStudio/CocoStudio.h"

enum SPEAR_STATES
{
    INCASE = 0,
    DRAW = 1,
    FLY = 2,
    STAB = 3,
    MAX,
};

class Spear : public cocos2d::Node
{
public:
    Spear();
    ~Spear();
    
    bool init();
    void onEnter();
    void onExit();

    void setupWithData(cocos2d::EventCustom *event);

    void exitState(SPEAR_STATES currState);
    void enterState(SPEAR_STATES nextState);
    void changeState(SPEAR_STATES nextState);

    
    void refreshArrow();
    
    float calcDurByDis(float distance);
    void calcControlPos();
    
    void drawBow(float emitAngle, float velocity);
    void logic(float dt);
    
    CREATE_FUNC(Spear);
    
private:
    cocos2d::Sprite *spt;
    
    //曲线3顶点
    cocos2d::Vec2 startPos;
    cocos2d::Vec2 endPos;
    cocos2d::Vec2 controlPos;
    
    cocos2d::Vec2 arrowPos;
    cocos2d::Vec2 arrowTailPos;
    cocos2d::Vec2 arrowHeadPos;
    
    float bezierT;
    
//    float speedx;
//    float speedy0;
//    float accel;
//    float emitAngle;
//    float velocity;
    
    float dur;
    float currDur;
    
    CC_SYNTHESIZE(int, ownerId, OwnerId);
    
    CC_SYNTHESIZE_READONLY(SPEAR_STATES, currState, CurrState);
    CC_SYNTHESIZE_READONLY(SPEAR_STATES, lastState, LastState);
    CC_SYNTHESIZE_READONLY(SPEAR_STATES, originState, OriginState);
    
};

#endif /* Spear_hpp */
