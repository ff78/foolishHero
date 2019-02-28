//
//  Effect.hpp
//  foolishHero-mobile
//
//  Created by ff on 2019/2/28.
//

#ifndef Effect_hpp
#define Effect_hpp

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"

class Effect : public cocos2d::Node
{
public:
    bool init();
    
    bool initWithNumber(std::string numImgName, int num, int width, int height);
    
    bool initWithImg(std::string imgName);
    
    CREATE_FUNC(Effect);
private:
    CC_SYNTHESIZE_READONLY(float, scaleRate, ScaleRate)
    CC_SYNTHESIZE(float, originX, OriginX);
    CC_SYNTHESIZE(float, originY, OriginY);
    
    CC_SYNTHESIZE(bool, followY, FollowY);
    
    CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas *, hurtText, HurtText);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite *, flagSpt, FlagSpt);
};
#endif /* Effect_hpp */
