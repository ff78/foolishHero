//
//  Hero.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#ifndef Hero_hpp
#define Hero_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "ELProtocol.h"

enum HERO_STATES
{
    STAND = 0,
    DRAW = 1,
    LOOSE = 2,
    STAB = 3,
    MAX,
};

typedef struct _SHOW_SPEAR_COUNTDOWN
{
    float duration;
    int hurtBone;
}SHOW_SPEAR_COUNTDOWN;

class Hero : public cocos2d::Node
{
public:
    Hero();
    ~Hero();
    
    bool init();
    void onEnter();
    
    void updateState();
    void update(float dt);
    void exitState(HERO_STATES currState);
    void enterState(HERO_STATES nextState);
    void changeState(HERO_STATES nextState);
    void changeActionWithName(int nextAction);
    void doFlag(int nextFlag);
    
    void setupView(std::string res);
    void drawBow(float emitAngle, float velocity);
    void adjustBow(float emitAngle, float velocity);
    void loose(float emitAngle, float velocity);
    
    void back2Stand();
    void getHeadBB();
    void endLoose(spTrackEntry *entry);
    
    int hitCheck(cocos2d::Vec2 arrowCenter, float angle, cocos2d::Size arrowSize);
    cocos2d::Vec2 getHitPos(cocos2d::Vec2 arrowPos, int hurtBone);
    float getHitAngle(float arrowAngle, int hurtBone);
    void hitBySpear(L2E_HIT_HERO data);
    void countDownSpear(float dt);

    CREATE_FUNC(Hero);
    
private:
    cocos2d::Node *player;
    cocostudio::timeline::ActionTimeline *playerAction;
    
    spine::SkeletonAnimation *skeletonNode;
    
    cocos2d::DrawNode *headCollide;
    cocos2d::Rect headRect;
    std::map<int, SHOW_SPEAR_COUNTDOWN> showSpearCountDown;
    const float maxShowSpearDuration = 3;
    
    float originHeadAngle;
    float originArmAngle;
    
    CC_SYNTHESIZE_READONLY(HERO_STATES, currState, CurrState);
    CC_SYNTHESIZE_READONLY(HERO_STATES, lastState, LastState);
    CC_SYNTHESIZE_READONLY(HERO_STATES, originState, OriginState);
    
    CC_SYNTHESIZE(bool, flipX, FlipX);
    CC_SYNTHESIZE(int, curveId, CurveId);
    CC_SYNTHESIZE(int, userId, UserId);
    
};

#endif /* Hero_hpp */
