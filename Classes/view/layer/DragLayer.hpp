//
//  DragLayer.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/19.
//

#ifndef DragLayer_hpp
#define DragLayer_hpp

#include "cocos2d.h"

class DragLayer : public cocos2d::Layer
{
public:
    DragLayer();
    ~DragLayer();
    
    bool init();
    void onEnter();
    void onExit();
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event *event);
    
    void drawABow();
//    void cancelDraw();
    void loose();
    
    void update(float dt);
    
    float power2Velocity(float power);
    
    CREATE_FUNC(DragLayer);
private:
    cocos2d::Vec2 startPos;
    cocos2d::Vec2 currPos;
    int fingerId;
    cocos2d::DrawNode *bowString;
    CC_SYNTHESIZE_READONLY(bool, inTouch, InTouch);
    CC_SYNTHESIZE_READONLY(float, dragDistance, DragDistance);
    CC_SYNTHESIZE_READONLY(float, dragAngle, DragAngle);
    
};

#endif /* DragLayer_hpp */
