//
//  UIManager.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#ifndef UIManager_hpp
#define UIManager_hpp

#include "cocos2d.h"
#include "utils/GameUtils.h"
#include "ELProtocol.h"

class UIManager : public Singleton<UIManager>, public cocos2d::Ref
{
public:
    UIManager();
    
    void processLogicResponse(void *pMsg);
    void (UIManager::*m_Logic2EngineFunc[l2e_max])(void *pMsg);
    
    void showBattleScene(void *pMsg);
    void setupGun(void *pMsg);
    void setupFoo(void *pMsg);
    void drawABow(void *pMsg);
    void loose(void *pMsg);
    
    
    void loop(float dt);
};

#endif /* UIManager_hpp */
