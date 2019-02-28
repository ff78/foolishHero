//
//  HitEffectLayer.hpp
//  foolishHero-mobile
//
//  Created by shangdiwuqing on 2019/2/28.
//

#ifndef HitEffectLayer_hpp
#define HitEffectLayer_hpp

#include "cocos2d.h"
#include "../actor/Effect.hpp"

class HitEffectLayer : public cocos2d::Layer
{
public:
    bool init();
    
    CREATE_FUNC(HitEffectLayer);
    
    void addHurtNum(bool critType, int num, cocos2d::Vec2 pos);
    
    void addCritFlag(cocos2d::Vec2 pos);
    
    void addMissFlag(cocos2d::Vec2 pos);
    
    void addArmatureEff(std::string resPath, cocos2d::Vec2 pos);
    
    void delEffect(Effect *effect);
    
    void delArmEffect(cocostudio::Armature *, cocostudio::MovementEventType, const std::string &);
};

#endif /* HitEffectLayer_hpp */
