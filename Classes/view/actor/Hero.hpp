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
    
//    void initGun();
//    void refreshCurve();
//    void refreshArrow();
//    
//    float calcDurByDis(float distance);
//    void calcControlPos();
    
    void drawBow(float emitAngle, float velocity);
    void loose();

    CREATE_FUNC(Hero);
    
private:
    //曲线3顶点
    cocos2d::Vec2 startPos;
    cocos2d::Vec2 endPos;
    cocos2d::Vec2 controlPos;
    
    //控制三角形3个顶点图
    cocos2d::DrawNode *startPoint;
    cocos2d::DrawNode *endPoint;
    cocos2d::DrawNode *controlPoint;
    
    //控制三角形3条边
    cocos2d::DrawNode *p0p1;
    cocos2d::DrawNode *p0p2;
    cocos2d::DrawNode *p1p2;
    
    cocos2d::Vec2 arrowPos;
    cocos2d::Vec2 arrowTailPos;
    cocos2d::Vec2 arrowHeadPos;
    //切线
    cocos2d::DrawNode *arrow;
    cocos2d::DrawNode *arrowTail;
    cocos2d::DrawNode *arrowHead;
    cocos2d::DrawNode *arrowLine;
    
    //辅助曲线
    cocos2d::DrawNode *bezierCurve;
    
    float bezierT;
    
    float speedx;
    float speedy0;
    float accel;
    float emitAngle;
    float velocity;
    
    float dur;
    float currDur;
    
    CC_SYNTHESIZE(bool, flipX, FlipX);
    CC_SYNTHESIZE(int, curveId, CurveId);
};

#endif /* Hero_hpp */
