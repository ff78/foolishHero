//
//  ELProtocol.h
//  owen
//
//  Created by ff on 16/8/9.
//
//

#ifndef ELProtocol_h
#define ELProtocol_h

#include "cocos2d.h"
#include "GameDefine.h"

enum E2LProtocol
{
    e2l_shown_battle,                                   //  已显示战场
    e2l_draw_bow,                                       //  拉开弓
    e2l_loose,                                          //  放箭
    
    e2l_hit_hero,                                       //  击中
    e2l_max
};

enum L2EProtocol
{
    l2e_show_system_load,                               //  显示系统加载
    l2e_update_battle_load,                             //
    
    l2e_show_battle_load,                               //  显示战场加载
    l2e_setup_foo,                                      //  设置玩家位置
    l2e_draw_bow,                                       //  拉开弓
    l2e_loose,                                          //  放箭
    
    l2e_hit_hero,                                       //  击中

    l2e_max
};

typedef struct __L2E_SETUP_FOO
{
    L2EProtocol                 eProtocol;
    
    int                         posx[2];
    int                         posy[2];
    int                         userId[2];
    bool                        flipX;
    
    int                         myUserId;
}L2E_SETUP_FOO;

typedef struct __E2L_DRAW_A_BOW
{
    E2LProtocol                 eProtocol;
    float                       drawAngle;
    float                       drawPower;
}E2L_DRAW_A_BOW;

typedef struct __E2L_LOOSE
{
    E2LProtocol                 eProtocol;
    float                       drawAngle;
    float                       drawPower;
    cocos2d::Vec2               startPos;
    cocos2d::Vec2               controlPos;
    cocos2d::Vec2               endPos;
}E2L_LOOSE;

typedef struct __L2E_DRAW_A_BOW
{
    L2EProtocol                 eProtocol;
    int                         userId;
    int                         myUserId;
    float                       drawAngle;
    float                       drawPower;
}L2E_DRAW_A_BOW;

typedef struct __L2E_LOOSE
{
    L2EProtocol                 eProtocol;
    int                         userId;
    int                         myUserId;
    float                       drawAngle;
    float                       drawPower;
}L2E_LOOSE;


typedef struct __L2E_COMMON
{
    L2EProtocol                 eProtocol;
    
}L2E_COMMON;

typedef struct __L2E_UPDATE_LOAD
{
    L2EProtocol                 eProtocol;
    bool                        isOver;
    int                         step;
    int                         count;
}L2E_UPDATE_LOAD;

typedef struct __E2L_HIT_HERO
{
    E2LProtocol                 eProtocol;
    int                         hitUserId;
    int                         hurtBone;
    float                       arrowAngle;
    float                       arrowPosX;
    float                       arrowPosY;
}E2L_HIT_HERO;

typedef struct __L2E_HIT_HERO
{
    L2EProtocol                 eProtocol;
    int                         hitUserId;
    int                         hurtBone;
    float                       arrowAngle;
    float                       arrowPosX;
    float                       arrowPosY;
    int                         hurtValue;
    int                         critType;
}L2E_HIT_HERO;
#endif /* ELProtocol_h */
