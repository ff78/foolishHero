#ifndef _TimeUtil_H_
#define _TimeUtil_H_

#include <stdint.h>
#include <stdio.h>
#include "cocos2d.h"


USING_NS_CC;
class TimeUtil{
public:

//    static int64_t currentTimeMillis();
//    static int currentTimeMillis(int64_t time);
    static std::string timeFormatToYYMMDD(long sec);
    static std::string timeFormatToYMD(long sec);
    static std::string timeFormatToMS(long sec);
    static std::string timeFormatToHMS(long sec);
//    static long get_system_tick();
    static long get_system_tick_s();
    static int timeFormatToDay(long sce);

    
//    static bool currentTimeInToday(int64_t time);
    
    static long getTimeWithTomorrowHour(int deltaDay, int hour);
    
    static bool isGreaterHour(int hour);
    static long leftSec(int hour);
    
    static void setServerTime(std::string timeStr);
    static void updateServerTime(float dt);
    
//    static void splitString(std::vector<std::string> &contentVector,std::string content, std::string pattern);
private:
    static double serverTime;
};

#endif

