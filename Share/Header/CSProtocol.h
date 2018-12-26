//
//  CSProtocol.h
//  owen
//
//  Created by ff on 16/8/9.
//
//

#ifndef CSProtocol_h
#define CSProtocol_h

enum C2SProtocol
{
    c2s_check_connect,              //  请求检查是否联网
    c2s_exit_app,                   //  请求关闭应用
    c2s_pay,
    c2s_recharge,                   //  充值请求
    c2s_cash_benefit_code,          //  救济金兑奖
    c2s_link_to_netgame,            //  跳转网页
    c2s_share,                      //  分享
    c2s_umeng_track,                //  友盟统计自定义事件
    c2s_umeng_exchange,             //  友盟统计订单充值事件
    c2s_umeng_buy,                  //  友盟统计购买道具事件
    c2s_umeng_use,                  //  友盟统计消耗道具事件
    c2s_umeng_user_level,           //  友盟统计玩家等级
    c2s_umeng_enter_stage_level,    //  友盟统计进入关卡
    c2s_umeng_finish_stage_level,   //  友盟统计通过关卡
    c2s_umeng_fail_stage_level,     //  友盟统计未通过关卡
    
    c2s_server_time_req,            //  获得服务器时间
    
    c2s_ad_free_diamond,            //  免费钻石视频广告
    c2s_ad_sweep_item,              //  升阶物品视频广告
    c2s_ad_start_stage,             //  免体力挑战关卡视频广告
    c2s_ad_new_tower,               //  新罪恶之塔关卡插屏广告
    c2s_ad_new_stage,               //  每3关插屏广告
    c2s_max
};

enum S2CProtocol
{
    s2c_exit,                       //  退出
    s2c_check_connect,              //  返回联网状态
    s2c_pay,
    s2c_recharge,                   //  充值结果
    
    s2c_cash_benefit_code,          //  兑奖结果
    s2c_share,                      //  分享结果
    
    s2c_server_time_ack,            //  返回服务器时间
    
    s2c_ad_free_diamond,            //  视频广告放完发放免费钻石
    s2c_ad_sweep_item,              //  视频广告放完发放升阶物品
    s2c_ad_start_stage,             //  视频广告放完免体力挑战关卡
    
    s2c_max
};

typedef struct __C2S_COMMON
{
    C2SProtocol                     eProtocol;
}C2S_COMMON;//  通用请求

typedef struct __S2C_COMMON
{
    S2CProtocol                     eProtocol;
}S2C_COMMON;//  通用回复

typedef struct __C2S_CHECK_CONNECT
{
    C2SProtocol                     eProtocol;
}C2S_CHECK_CONNECT;//  请求检查是否联网

typedef struct __S2C_CHECK_CONNECT
{
    S2CProtocol                     eProtocol;
    bool                            result;
}S2C_CHECK_CONNECT;//  返回联网状态

typedef struct __C2S_EXIT_APP
{
    C2SProtocol                     eProtocol;
}C2S_EXIT_APP;//  请求关闭应用

typedef struct __S2C_EXIT_APP
{
    S2CProtocol                     eProtocol;
}S2C_EXIT_APP;

typedef struct __C2S_PAY
{
    C2SProtocol                     eProtocol;
    int                             payId;
    std::string                     orderId;
    int                             price;
    std::string                     name;
}C2S_PAY;

typedef struct __S2C_PAY
{
    S2CProtocol                     eProtocol;
    int                             packageId;
    std::string                     payId;
    bool                            success;
}S2C_PAY;

typedef struct __C2S_UMENG_TRACK
{
    C2SProtocol                             eProtocol;
    std::string                             eventName;
    int                                     count;
    std::map<std::string, std::string>      attrMap;
}C2S_UMENG_TRACK;

typedef struct __C2S_UMENG_EXCHANGE
{
    C2SProtocol                             eProtocol;
    std::string                             orderId;
    double                                  price;
    std::string                             currencyType;
    double                                  count;
    int                                     channel;
}C2S_UMENG_EXCHANGE;

typedef struct __C2S_UMENG_BUY
{
    C2SProtocol                             eProtocol;
    std::string                             itemName;
    double                                  price;
    int                                     count;
}C2S_UMENG_BUY;

typedef struct __C2S_UMENG_USE
{
    C2SProtocol                             eProtocol;
    std::string                             itemName;
    double                                  price;
    int                                     count;
}C2S_UMENG_USE;

typedef struct __C2S_UMENG_USER_LEVEL
{
    C2SProtocol                             eProtocol;
    int                                     level;
}C2S_UMENG_USER_LEVEL;

typedef struct __C2S_UMENG_STAGE_LEVEL
{
    C2SProtocol                             eProtocol;
    std::string                             stageName;
}C2S_UMENG_STAGE_LEVEL;

typedef struct __S2C_SERVER_TIME
{
    S2CProtocol                             eProtocol;
    bool                                    success;
    std::string                             timeStr;
}S2C_SERVER_TIME;

typedef struct __C2S_AD_SWEEP_ITEM
{
    C2SProtocol                             eProtocol;
    int                                     itemTag;
}C2S_AD_SWEEP_ITEM;

typedef struct __S2C_AD_SWEEP_ITEM
{
    S2CProtocol                             eProtocol;
    int                                     itemTag;
}S2C_AD_SWEEP_ITEM;



#endif /* CSProtocol_h */
