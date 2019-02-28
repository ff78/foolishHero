//
//  GameScene.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "../layer/ActorLayer.hpp"
#include "../layer/DragLayer.hpp"
#include "../layer/CurveLayer.hpp"
#include "../layer/HitEffectLayer.hpp"

class GameScene : public cocos2d::Scene {
public:
    GameScene();
    ~GameScene();
    
    bool init();
    void onEnter();
    void onExit();
    
    void setupView(void *pMsg);
    
    void update(float dt);
    
    void drawBow(cocos2d::EventCustom *event);
    void loose(cocos2d::EventCustom *event);
    void hitHero(cocos2d::EventCustom *event);
    
    float convertDrawAngle(float angle);
    
    void refreshPowerCurve();
    void clearPowerCurve();
//    float power2Velocity(float power);
    
    CREATE_FUNC(GameScene);
private:
    ActorLayer *actorLayer;
    DragLayer *dragLayer;
    CurveLayer *curveLayer;
    HitEffectLayer *effectLayer;
    
    cocos2d::Layer *powerLayer;
    
    bool loosed;
    float bezierT;
    CC_SYNTHESIZE_READONLY(bool, flipXOpt, FlipXOpt);
    CC_SYNTHESIZE_READONLY(bool, drawBowing, DrawBowing);
    
private:
    cocos2d::EventListenerCustom *bowListener;
    cocos2d::EventListenerCustom *looseListener;
    cocos2d::EventListenerCustom *hitListener;
    
};

#endif /* GameScene_hpp */
