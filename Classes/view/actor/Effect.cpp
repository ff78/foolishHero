//
//  Effect.cpp
//  foolishHero-mobile
//
//  Created by ff on 2019/2/28.
//

#include "Effect.hpp"
#include "utils/GameUtils.h"
#include "EventDefine.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool Effect::init()
{
    if (!Node::init()) {
        return false;
    }
    scaleRate = 1;
    return true;
}

bool Effect::initWithNumber(std::string numImgName, int num, int width, int height)
{
    hurtText = TextAtlas::create("0123456789", numImgName, width, height, "0");
    hurtText->setString(Convert2String(num));
    addChild(hurtText);
    return true;
}

bool Effect::initWithImg(std::string imgName)
{
    flagSpt = Sprite::create(imgName);
    addChild(flagSpt);
    return true;
}
