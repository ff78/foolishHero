//
//  HallScene.cpp
//  foolishHero-mobile
//
//  Created by shangdiwuqing on 2019/2/28.
//

#include "HallScene.hpp"
#include "utils/GameUtils.h"

USING_NS_CC;

void HallScene::onEnter()
{
    Scene::onEnter();
    auto label = Label::create();
    label->setString("结算界面");
    label->setPosition(GameUtils::winSize/2);
    addChild(label);
}
