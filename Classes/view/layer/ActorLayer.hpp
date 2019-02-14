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
    void adjustBow(float angle, float power);
    void drawBow(float angle, float power);
    void testLoose(float dt);
    
    void update(float dt);
    
    CREATE_FUNC(ActorLayer);
    
private:
    std::vector<Spear *> spearVec;
    cocos2d::EventListenerCustom *setupHeroListener;
    
    CC_SYNTHESIZE_READONLY(Hero *, me, Me);
    CC_SYNTHESIZE_READONLY(Hero *, master, Master);
};

#endif /* ActorLayer_hpp */
