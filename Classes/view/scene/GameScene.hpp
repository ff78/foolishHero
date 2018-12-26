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
    
    float convertDrawAngle(float angle);
    
    CREATE_FUNC(GameScene);
private:
    ActorLayer *actorLayer;
    DragLayer *dragLayer;
    
    bool loosed;
    CC_SYNTHESIZE_READONLY(bool, flipXOpt, FlipXOpt);
    CC_SYNTHESIZE_READONLY(bool, drawBowing, DrawBowing);
    
private:
    cocos2d::EventListenerCustom *bowListener;
    cocos2d::EventListenerCustom *looseListener;
    
};

#endif /* GameScene_hpp */
