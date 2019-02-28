//
//  HitEffectLayer.cpp
//  foolishHero-mobile
//
//  Created by shangdiwuqing on 2019/2/28.
//

#include "HitEffectLayer.hpp"
USING_NS_CC;

bool HitEffectLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    return true;
}

void HitEffectLayer::addHurtNum(bool critType, int num, Vec2 pos)
{
    auto hurtNum = Effect::create();

    int fontWidth;
    int fontHeight;
    std::string fontPath = "hurt/";
    if (critType == 1) {
        fontPath += "McritNum.png";
        fontWidth = 73;
        fontHeight = 77;
    }else{
        fontPath += "MhurtNum.png";
        fontWidth = 41;
        fontHeight = 44;
    }
    hurtNum->initWithNumber(fontPath, abs(num), fontWidth, fontHeight);
    
    hurtNum->setPosition(Vec2(pos.x, pos.y+150));
    addChild(hurtNum);
    
    auto scale = ScaleTo::create(0.1, 1.5);
    auto scale2 = ScaleTo::create(0.1, 0.6);
    
    auto scale3 = ScaleTo::create(0.8, 0.3);
    auto fade = FadeOut::create(0.5);
    auto move = MoveBy::create(0.8, Vec2(0, 100));
    auto eMove = EaseExponentialOut::create(move);
    
    auto phase = Spawn::create(scale3, fade, eMove, NULL);
    auto func = CallFunc::create(CC_CALLBACK_0(HitEffectLayer::delEffect, this, hurtNum));
    hurtNum->runAction(Sequence::create(scale, scale2, phase, func, NULL));
}

void HitEffectLayer::addCritFlag(Vec2 pos)
{
    auto crit = Effect::create();
    crit->initWithImg("hurt/timg.png");
    crit->setPosition(Vec2(pos.x+20, pos.y+200));
    addChild(crit);
    
    auto scale = ScaleTo::create(0.1, 2);
    auto scale2 = ScaleTo::create(0.1, 1);
    auto fade = FadeOut::create(0.2);
    auto func = CallFunc::create(CC_CALLBACK_0(HitEffectLayer::delEffect, this, crit));
    crit->runAction(Sequence::create(scale, scale2, fade, func, NULL));
}

void HitEffectLayer::delEffect(Effect *effect)
{
    effect->stopAllActions();
    removeChild(effect);
}
