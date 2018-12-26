//
//  SystemLogic.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#include "SystemLogic.hpp"
#include "ClientLogic.hpp"
#include "utils/StringData.h"

USING_NS_CC;

SystemLogic::SystemLogic()
{
    
}

SystemLogic::~SystemLogic()
{
    
}

void SystemLogic::logic(float dt)
{

}

void SystemLogic::arrangeLoad()
{
    L2E_COMMON info;
    info.eProtocol = l2e_show_system_load;
    ClientLogic::instance()->pass2Engine(&info);
}

void SystemLogic::load()
{
//    L2E_UPDATE_LOAD info;
//    info.eProtocol = l2e_update_system_load;
//    info.isOver = false;
//    info.step = 0;
//    info.count = (int)m_vecLoadFunc.size();
    int result = Load::load();
    if (result != -1) {
//        info.step = result;
        //更新加载界面
//        ClientLogic::instance()->pass2Engine(&info);
    }else{
        onLoadFinish();
    }
}

void SystemLogic::onLoadFinish()
{
    Load::onLoadFinish();
    ClientLogic::instance()->ChangeState(GAME_STATE_HALL);
}

void SystemLogic::showBattle()
{
//    L2E_COMMON info;
//    info.eProtocol = l2e_show_battle;
//    ClientLogic::instance()->pass2Engine(&info);
}
