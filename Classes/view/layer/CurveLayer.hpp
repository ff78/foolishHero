//
//  CurveLayer.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/26.
//

#ifndef CurveLayer_hpp
#define CurveLayer_hpp

#include "cocos2d.h"

class CurveLayer : public cocos2d::Layer {
public:
    bool init();
    void onEnter();
    void onExit();
    
    CREATE_FUNC(CurveLayer);
private:
    
};

#endif /* CurveLayer_hpp */
