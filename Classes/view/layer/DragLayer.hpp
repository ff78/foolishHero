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
    
    void refreshEdge();
    void hideHint();
    
    CREATE_FUNC(DragLayer);
private:
    cocos2d::Vec2 startPos;
    cocos2d::Vec2 currPos;
    
    cocos2d::Vec2 startC;
    cocos2d::Vec2 currC;
    float startRad;
    float currRad;
    float radDisAngle;
    cocos2d::Vec2 startEdge1;
    cocos2d::Vec2 currEdge1;
    cocos2d::Vec2 startEdge2;
    cocos2d::Vec2 currEdge2;
    cocos2d::Vec2 control1;
    cocos2d::Vec2 control2;
    cocos2d::DrawNode *startCircle;
    cocos2d::DrawNode *currCircle;
    cocos2d::DrawNode *edge1;
    cocos2d::DrawNode *edge2;
    cocos2d::DrawNode *strenPoly;
    
    int fingerId;
    cocos2d::DrawNode *bowString;

    CC_SYNTHESIZE_READONLY(bool, inTouch, InTouch);
    CC_SYNTHESIZE_READONLY(float, dragDistance, DragDistance);
    CC_SYNTHESIZE_READONLY(float, dragAngle, DragAngle);
    
};

#endif /* DragLayer_hpp */
