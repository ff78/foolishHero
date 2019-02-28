//
//  ActorLayer.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#ifndef ActorLayer_hpp
#define ActorLayer_hpp

#include "cocos2d.h"
#include "../actor/Hero.hpp"
#include "../actor/Spear.hpp"

class ActorLayer: public cocos2d::Layer {
    
public:
    ActorLayer();
    ~ActorLayer();
    
    void onExit();
    void onEnter();
    bool init();
    
    void setupFoo(cocos2d::EventCustom *event);
    void looseBow(cocos2d::EventCustom *event);
    void hitHero(cocos2d::EventCustom *event);
    void reliveFoo(cocos2d::EventCustom *event);
    void adjustBow(float angle, float power);
    void drawBow(float angle, float power);
    void testLoose(float dt);
    
    void update(float dt);
    float convertHitPos(float arrowPosX, Hero *hero);
    float convertArrowAngle(float arrowAngle, Hero *hero);
//    float power2Velocity(float power);
    CREATE_FUNC(ActorLayer);
    
private:
    std::map<int, Spear *> spearMap;
    cocos2d::EventListenerCustom *setupHeroListener;
    cocos2d::EventListenerCustom *hitHeroListener;
    cocos2d::EventListenerCustom *reliveHeroListener;
    
    CC_SYNTHESIZE_READONLY(int, maxArrowId, MaxArrowId);
    CC_SYNTHESIZE_READONLY(Hero *, me, Me);
    CC_SYNTHESIZE_READONLY(Hero *, master, Master);
};

#endif /* ActorLayer_hpp */
