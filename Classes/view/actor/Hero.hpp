//
//  Hero.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#ifndef Hero_hpp
#define Hero_hpp

#include "cocos2d.h"

class Hero : public cocos2d::Node
{
public:
    Hero();
    ~Hero();
    
    bool init();
    void onEnter();
    
    void updateState();
    void updateAI(float dt);
    void exitState(int currState);
    void enterState(int nextState);
    void changeState(int nextState);
    void changeActionWithName(int nextAction);
    void doFlag(int nextFlag);
    
    void drawBow(float emitAngle, float velocity);
    void loose(float emitAngle, float velocity);

    CREATE_FUNC(Hero);
    
private:
    
    CC_SYNTHESIZE(bool, flipX, FlipX);
    CC_SYNTHESIZE(int, curveId, CurveId);
};

#endif /* Hero_hpp */
