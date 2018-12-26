//
//  SystemLogic.hpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#ifndef SystemLogic_hpp
#define SystemLogic_hpp

#include "cocos2d.h"
#include "utils/GameUtils.h"
#include "ELProtocol.h"
#include "TLProtocol.h"
#include "CSProtocol.h"
#include "Load.h"

class SystemLogic : public Singleton<SystemLogic>, public Load {
public:
    SystemLogic();
    ~SystemLogic();
    
    void logic(float dt);
    void arrangeLoad();
    void load();
    
    void showBattle();
protected:
    virtual void onLoadFinish();
};
#endif /* SystemLogic_hpp */
