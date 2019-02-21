//
//  EventDefine.h
//  owen
//
//  Created by ff on 16/8/9.
//
//

#ifndef EventDefine_h
#define EventDefine_h

#define EMIT_SPEAR                                      "EMIT_SPEAR"

#define CREATE_BULLET                                   "CREATE_BULLET"
typedef struct __CREATE_BULLET_DATA
{
    std::string res;
    float scale;
    float speed;
    int bulletType;
    int bulletSkillId;
    bool through;
    float distPosX;
    float bulletWidth;
    float bulletHeight;
    bool calAngel;
    
    int baseAttack;
    int baseCritRatio;
    int comboFactor;
    
    int ownerType;
    float srcX;
    float srcY;
    bool flipX;
}CREATE_BULLET_DATA;

#define CREATE_GUN                                      "CREATE_GUN"

#define SETUP_HERO                                      "SETUP_HERO"
#define DRAW_BOW                                        "DRAW_BOW"
#define LOOSE_ARROW                                     "LOOSE_ARROW"
#define HIT_HERO                                        "HIT_HERO"


#endif /* EventDefine_h */
