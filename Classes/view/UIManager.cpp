//
//  UIManager.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#include "UIManager.hpp"
#include "logic/ClientLogic.hpp"
#include "EventDefine.h"
#include "scene/GameScene.hpp"
#include "scene/HallScene.hpp"

USING_NS_CC;


UIManager::UIManager()
{
    memset(m_Logic2EngineFunc, 0, sizeof(m_Logic2EngineFunc));
    m_Logic2EngineFunc[l2e_show_battle_load] = &UIManager::showBattleScene;
    m_Logic2EngineFunc[l2e_setup_foo] = &UIManager::setupFoo;
    m_Logic2EngineFunc[l2e_loose] = &UIManager::loose;
    m_Logic2EngineFunc[l2e_draw_bow] = &UIManager::drawABow;
    m_Logic2EngineFunc[l2e_hit_hero] = &UIManager::hitHero;
    m_Logic2EngineFunc[l2e_relive_hero] = &UIManager::reliveHero;
    m_Logic2EngineFunc[l2e_show_round_end] = &UIManager::showRoundEnd;
    
}

void UIManager::loop(float dt)
{
    ClientLogic::instance()->mainLoop(dt);
}

void UIManager::processLogicResponse(void *pMsg)
{
    if (NULL == pMsg)
        return;
    
    L2EProtocol    eProtocol    = *((L2EProtocol*)pMsg);
    if (eProtocol >= l2e_max)
        return;
    if (this->m_Logic2EngineFunc[eProtocol] != NULL)
    {
        (this->*m_Logic2EngineFunc[eProtocol])(pMsg);
    }
}

void UIManager::showBattleScene(void *pMsg)
{
    auto scene = GameScene::create();
    if (Director::getInstance()->getRunningScene() != nullptr) {
        Director::getInstance()->replaceScene(scene);
    }else{
        Director::getInstance()->runWithScene(scene);
    }
    scene->setupView(pMsg);
}

void UIManager::setupGun(void *pMsg)
{
    EventCustom event(CREATE_GUN);
    event.setUserData(pMsg);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void UIManager::setupFoo(void *pMsg)
{
    EventCustom event(SETUP_HERO);
    event.setUserData(pMsg);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void UIManager::drawABow(void *pMsg)
{
    EventCustom event(DRAW_BOW);
    event.setUserData(pMsg);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void UIManager::loose(void *pMsg)
{
    EventCustom event(LOOSE_ARROW);
    event.setUserData(pMsg);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void UIManager::hitHero(void *pMsg)
{
    EventCustom event(HIT_HERO);
    event.setUserData(pMsg);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void UIManager::reliveHero(void *pMsg)
{
    EventCustom event(RELIVE_HERO);
    event.setUserData(pMsg);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void UIManager::showRoundEnd(void *pMsg)
{
    auto scene = HallScene::create();
    if (Director::getInstance()->getRunningScene() != nullptr) {
        Director::getInstance()->replaceScene(scene);
    }else{
        Director::getInstance()->runWithScene(scene);
    }
}
