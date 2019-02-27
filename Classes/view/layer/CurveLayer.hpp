//
//  CurveLayer.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/26.
//

#ifndef CurveLayer_hpp
#define CurveLayer_hpp

#include "cocos2d.h"
#include "../actor/SpearCurve.hpp"

class CurveLayer : public cocos2d::Layer {
public:
    bool init();
    void onEnter();
    void onExit();
    
    void createCurve(float x, float y);
    void removeCurve(int curveId);
    
    void setupFoo(cocos2d::EventCustom *event);
    void looseBow(cocos2d::EventCustom *event);
    void adjustBow(float angle, float power, int curveId);
    
    void testLoose(float dt);
    
    CREATE_FUNC(CurveLayer);
private:
    cocos2d::EventListenerCustom *setupHeroListener;
//    cocos2d::EventListenerCustom *looseListener;
    
    CC_SYNTHESIZE_READONLY(int, maxCurveId, MaxCurveId);
    
};

#endif /* CurveLayer_hpp */
