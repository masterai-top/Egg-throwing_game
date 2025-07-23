#ifndef _SERVER_CLIENT_H_
#define _SERVER_CLIENT_H_

//#include "Game/NetMessage.h"

enum
{
    SC_MSG_BEGIN        = 0xE100,
    
    //兑换奖品请求 第一步
	LOBBYCLIENT_LOBBY_EXCHANGE_GIFT_STEP1_REQ,
	LOBBYCLIENT_LOBBY_EXCHANGE_GIFT_STEP1_RSP,
	//兑换奖品请求 第二步
	LOBBYCLIENT_LOBBY_EXCHANGE_GIFT_STEP2_REQ,
	LOBBYCLIENT_LOBBY_EXCHANGE_GIFT_STEP2_RSP,
	
    
    SC_MSG_MOBILE_ACTIVITY_NTF,
    SC_MSG_MOBILE_ACTIVITY_DATA_UPDATE_NTF,
    SC_MSG_MOBILE_ACTIVITY_GET_AWARD_RSP,

	//拉新活动送积分通知
	INVITE_USER_LOBBYSERVER_NOTIFY_USER_MSG,
	INVITE_USER_LOBBYCLIENT_GET_SCORE_RECORD_REQ,
	INVITE_USER_LOBBYCLIENT_GET_SCORE_RECORD_RSP,
	INVITE_USER_LOBBYCLIENT_GET_USER_RECORD_REQ,
	INVITE_USER_LOBBYCLIENT_GET_USER_RECORD_RSP,
	//兑换码
	LOBBYCLIENT_EXCHANGECODE_AWARD_REQ,
	LOBBYCLIENT_EXCHANGECODE_AWARD_RSP,
	
	//  首次登陆消息
	SC_MSG_USER_FIRST_LOGIN_NTF,
    CS_ASK_CONNECTION_INFO_REQ,
    SC_ASK_CONNECTION_INFO_RSP,
	
	// 赢1局送5元活动相关协议
	SC_ACTIVITY20150505_INFO_NTF,
	SC_ACTIVITY20150505_PROGRESS_UPDATE,
	SC_ACTIVITY20150505_GET_AWARD_NTF,
	CS_ACTIVITY20150505_BIND_PHONE_DONE,
	
	// 大厅登陆获得游戏断线信息
	SC_USER_GAME_BREAK_INFO_NTF,

	
	// 大厅请求赢1局送5元活动数据协议
	CS_ACTIVITY20150505_ASK_INFO_REQ,
	SC_ACTIVITY20150505_ASK_INFO_RSP,

	// 统一奖励获得通知
	SC_GET_AWARD_NOTIFY,

	// 请求打开抽奖道具
	CS_USE_LOTTERY_ITEM_REQ,
	SC_USE_LOTTERY_ITEM_RSP,

    // ---------------------------------------------------

    CS_MSG_BEGIN        = 0xE800,

    CS_MSG_MOBILE_ACTIVITY_GET_AWARD_REQ,
    // 玩家分享获得红包
    CS_MSG_SHARE_GET_HONGBAO_REQ,
    SC_MSG_SHARE_GET_HONGBAO_RSP,
    // 玩家红包抽奖
    CS_MSG_GET_HONGBAO_REWARD_REQ,
    SC_MSG_GET_HONGBAO_REWARD_RSP,
    // 登陆游戏发送渠道信息
    CS_MSG_LOGINGAME_CHANNEL_INFO,
    // 通知client上次游戏内断线后的结算信息
    SC_MSG_NOTIFY_LASTGAME_RESULT,
	
	//大厅客户端登陆大厅服务器 （替代之前的登陆协议，增加渠道、游戏id、站点id信息）
	SC_MSG_CLIENT_LOGIN_REQ,
	//游戏客户端登陆大厅服务器
	SC_MSG_GAMECLIENT_LOGIN_REQ,

    // 2015-01-29 新的登陆, 登陆请求协议结构不变,使用新的请求id,
    // 登陆返回使用新的返回结构, 如果登陆失败还是原来的协议,登陆成功返回LOGIN_CLIENT_AUTHEN_RSP
    // LobbyClient <-> LoginServer
    CLIENT_LOGIN_AUTHEN_REQ,        // 请求依旧是 tagLobbyAuthenReq
    CLIENT_LOGIN_NOSITE_AUTHEN_REQ, // 请求依旧是 tagLobbyAuthenWithNoSiteIdReq
    LOGIN_CLIENT_AUTHEN_RSP,        // 有站点的登陆返回 tagLoginClientAuthenRsp
    LOGIN_CLIENT_NOSITE_AUTHEN_RSP, // 无站点的登陆返回 tagLoginClientNoSiteAuthenRsp

	//大厅版本号验证
	CL_CONFIG_VERSION_CHECK_REQ,    //大厅版本号验证
	CL_CONFIG_VERSION_CHECK_RSP,     

	//获取PC引导用户属性 判定是否是参与活动用户
	CS_MSG_GET_FLAGSERIALNUMBER_REQ,
	CS_MSG_GET_FLAGSERIALNUMBER_RSP,

	//获取通知内容
	CS_MSG_GET_GUIDANCE_REQ,
	CS_MSG_GET_GUIDANCE_RSP,
	
	// 比赛场通知消息, 消息协议定义在ClientMatchProto.xml中
	SC_USER_MATCH_INFO_UPDATE,
	SC_MATCH_RESULT_NTF,
	SC_CUR_MATCH_SCORE_NTF,

	CS_MSG_DOWNLOAD_CONTENT_TRY_REQ,
	
	CS_MSG_GET_GUIDANCE2PC_REQ,
	CS_MSG_GET_GUIDANCE2PC_RSP,
	SC_MSG_AGAIN_ENTER_MATCH_INFO_NTF,
	
	//金牌开关的请求
	LOBBYCLIENT_KINGCARD_FLAG_REQ,
	LOBBYCLIENT_KINGCARD_FLAG_RSP,
	//昵称多次修改收费
	CS_MSG_MODIFY_NICKNAME_REQ,
	SC_MSG_MODIFY_NICKNAME_RSP,
	
	//手机端活动通知
	LOBBYCLIENT_ACTIVE_NOTICE_REQ,
	LOBBYCLIENT_ATTICE_NOTICE_RSP,

	//交互道具
	CS_MSG_INTERACTPROPS_REQ,
	SC_MSG_INTERACTPROPS_RSP,

	//魅力值
	CS_MSG_GLAMOURVALUE_REQ,
	SC_MSG_GLAMOURVALUE_RSP,

	// 交互道具消息广播
	SC_MSG_INTERACTPROPS_NTF,
	// 同步自己的魅力值等相关属性信息
	SC_MSG_SELF_AUXILIARY_DATA_NTF,

	//四川麻将星星数量
	SC_MSG_SCMJ_STARNUM_RSP,
	//玩家积分变化时，通知同桌其他玩家
	SC_MSG_NOTIFY_TABLE_PLAYERS_COIN_CHANGE,
    
    //德州扑克的协议
    TP_GET_PAYTIP_RANKING_REQ,
    TP_GET_PAYTIP_RANKING_RSP,          
    TP_GET_CARDTYPE_PROGRESS_REQ,
    TP_GET_CARDTYPE_PROGRESS_RSP,
    TP_GET_CARDTYPE_AWARD_REQ,         
    TP_GET_CARDTYPE_AWARD_RSP,
    TP_GET_MEDAL_PROGRESS_REQ,
    TP_GET_MEDAL_PROGRESS_RSP,          
    TP_GET_MEDAL_AWARD_REQ,           
    TP_GET_MEDAL_AWARD_RSP,
    TP_GET_ACTIVITY_LIST_REQ,      
    TP_GET_ACTIVITY_LIST_RSP,   
	TP_SET_USER_MEDAL_REQ,      
    TP_SET_USER_MEDAL_RSP,
	TP_GET_USER_SET_MEDAL_REQ,
	TP_GET_USER_SET_MEDAL_RSP,

	//德州新手引导领奖
	CS_MSG_GUANDAN_GUIDE_REWARD_REQ,
	SC_MSG_GUANDAN_GUIDE_REWARD_RSP,

	// 登陆游戏发送自己的代理商信息
    CS_MSG_LOGINGAME_AGENT_INFO,

	CS_MSG_GET_RECHARGEPOINT_REQ,
	SC_MSG_GET_RECHAGREPOINT_RSP,

	//获取元宝可以购买的头像
	CS_MSG_GET_YUANBAO_SHOP_REQ,
	SC_MSG_GET_YUANBAO_SHOP_RSP,

	//元宝购买头像
	CS_MSG_BUY_AVATAR_BY_YUANBAO_REQ,
	SC_MSG_BUY_AVATAR_BY_YUANBAO_RSP,

	//拜财神请求香火池和公告
	CS_MSG_BAICAISHEN_GET_SHOWDATA_REQ,
	SC_MSG_BAICAISHEN_GET_SHOWDATA_RSP,

	//拜财神请求香的信息
	CS_MSG_BAICAISHEN_GET_XIANG_INFO_REQ,
	SC_MSG_BAICAISHEN_GET_XIANG_INFO_RSP,

	//拜财神上香的
	CS_MSG_BAICAISHEN_SHANGXIANG_REQ,
	SC_MSG_BAICAISHEN_SHANGXIANG_RSP,

	//聊天相关 
	SC_MSG_CHATLOGIN_NEWINFO_NOTICE,
	CS_MSG_FSHIP_CHATTABLE_REQ,
	SC_MSG_FSHIP_CHATTABLE_RSP,
	CS_MSG_FSHIP_CHATWINDOW_OPEN_REQ,
	CS_MSG_FSHIP_CHATWINDOW_CLOSE_REQ,
	CS_MSG_FSHIP_ADD_FRIEND_REQ,
	SC_MSG_FSHIP_ADD_FRIEND_RSP,
	CS_MSG_FSHIP_SEND_CHAT_REQ,
	SC_MSG_FSHIP_SEND_CHAT_RSP,
	CS_MSG_FSHIP_ADD_FRIEND_ACCEPT_REQ,
	SC_MSG_FSHIP_ADD_FRIEND_ACCEPT_RSP,
	CS_MSG_FSHIP_DELETE_FRIEND_REQ,
	SC_MSG_FSHIP_DELETE_FRIEND_RSP,
	CS_MSG_FSHIP_FRIEND_SEARCH_REQ,
	SC_MSG_FSHIP_FRIEND_SEARCH_RSP,
	SC_MSG_FSHIP_FRIEND_STATUS_CHANGE,
	CS_MSG_FSHIP_INVITE_GAME_REQ,
	SC_MSG_FSHIP_INVITE_GAME_RSP,

	// 防沉迷消息通知
	SC_MSG_ANTI_ADDITION_WARN_NTF,

	// 请求游戏房间列表
	CS_MSG_ASK_ROOM_LIST_REQ,
	SC_ROOM_LIST_NTF,

	// 充值成功通知
	SC_BILLING_INFO_NTF,

	// 请求游戏房间个人数
	CS_MSG_GET_GAME_ONLINE_COUNTS_REQ,
	SC_MSG_GET_GAME_ONLINE_COUNTS_RSP,

	S_MSG_REPORT_ERROR,

	// 汇报自己的TV智能卡号
	CS_MSG_TV_CARD_INFO,

	// 统一下线通知
	SC_MSG_KICK_OUT_NTF,
};

// 设备类型
enum EDeviceType
{
    E_DeviceType_PC = 101,
    E_DeviceType_Android = 102,
    E_DeviceType_IOS = 103,
};


// 来自odao_client_msg.h 中，client与server心跳协议
const unsigned short  MOBILE_KEEP_ALIVE_MSG = 0xB8;   //保持连接消息
typedef struct MobileKeepAlive
{ 
    HEADER;
}MobileKeepAliveDef;

#define 	NAME_LEN			32		//名字长度
#define 	PHONE_LEN			20     	//电话号码  长度
#define		POSTAL_ADDR_LEN		200		//通信地址	长度
#define 	CHANNELID_LEN		32		//渠道信息  长度
#define     TOKEN_LEN           200     //token 长度


#pragma pack(push, 4)

typedef struct tagSCMobileActivityNtf
{
    HEADER;
    long long activityId;   // 活动id
    int activityType;       // 活动类型 1-累积胜场活动 2-连续胜场活动
    int awardRequire;       // 奖励要求的数值
    int curData;            // 当前的数值
    int isAwardDone;        // 0-未领完 1-已领完
}SCMobileActivityNtf;

typedef struct tagSCMobileActivityDataUpdateNtf
{
    HEADER;
    long long activityId;   // 活动id
    int activityType;       // 活动类型 1-累积胜场活动 2-连续胜场活动
    int data;               // 最新的数值
    int awardRequire;       // 奖励要求的数值
    int flag;               // 1-已达到下一个奖励点的领取
}SCMobileActivityDataUpdateNtf;

typedef struct tagCSMobileActivityGetAwardReq
{
    HEADER;
    long long activityId;   // 请求领取奖励的活动id
}CSMobileActivityGetAwardReq;

typedef struct tagSCMobileActivityGetAwardRsp
{
    HEADER;
    int result;             // 领奖结果
    long long activityId;   // 活动id
    int activityType;       // 活动类型 1-累积胜场活动 2-连续胜场活动
    int awardType;          // 1-道具
    long long awardData;    // type=1时表示道具id
    int awardCount;         // 奖励的数量
    int nextAwardRequire;   // 下一个奖励要求的数值
    int isAwardDone;        // 0-未领完 1-已领完
}SCMobileActivityGetAwardRsp;

//兑换奖品请求和返回 第一步
struct LobbyExchangeGiftReq_Step1
{
	HEADER;
	int 	nUserID;
	int 	nExchange_itemType;
	int 	nExchange_itemNum;
	int 	nBeExchange_itemType;
	int 	nBeExchange_itemNum;
	char 	szUserName[NAME_LEN];
};

//以下这些宏用在兑换礼品返回的nError字段中
#define 	EXCHANGE_GIFT_ERR_NO_ERR					0		//无错误
#define		EXCHANGE_GIFT_ERR_BEFORE_TIME				1		//还没到兑奖时间
#define		EXCHANGE_GIFT_ERR_AFTER_TIME				2		//兑奖时间已过
#define		EXCHANGE_GIFT_ERR_NO_ITEMTYPE				3		//找不到兑换物
#define		EXCHANGE_GIFT_ERR_NO_BE_ITEMTYPE			4		//找不到被兑换物
#define		EXCHANGE_GIFT_ERR_NO_ENOUGH_ITEMNUM			5		//兑换物个数不够
#define		EXCHANGE_GIFT_ERR_NO_ENOUGH_BEITEMNUM		6		//被兑换物个数不够
#define		EXCHANGE_GIFT_ERR_EXCHANGE_CLOSE			7		//交换已被关闭
#define		EXCHANGE_GIFT_ERR_NOLEFT_TODAY				8		//今天无兑换了，额度已满
#define		EXCHANGE_GIFT_ERR_NOLEFT_AMOUNT				9		//兑换完了，没剩余了
#define		EXCHANGE_GIFT_ERR_DB_NO_INSERT				10		//数据库插入错误
#define		EXCHANGE_GIFT_ERR_DB_NO_SELECT				11		//数据库查找错误
#define		EXCHANGE_GIFT_ERR_DB_NO_UPDATE				12		//数据库更新错误
#define		EXCHANGE_GIFT_ERR_NO_BIND_PHONE				13		//未绑定手机
#define		EXCHANGE_GIFT_ERR_ARG_ERROR					14		//输入参数错误或其他



struct LobbyExchangeGiftRes_Step1
{
	HEADER;
	int 	nUserID;
	int		nSiteID;
	int 	nLeft;  				//奖品剩余个数
	int 	nError; 				// 0 无错误
	int 	nExchange_itemType;
	int 	nExchange_itemNum;
	int 	nBeExchange_itemType;
	int 	nBeExchange_itemNum;
	char 	szUserName[NAME_LEN];
	char 	szMsgContext[512];
};

//兑换奖品请求和返回 第二步

struct LobbyExchangeGiftReq_Step2
{
	HEADER;
	int 	nUserID;
	int 	nExchange_itemType;
	int 	nExchange_itemNum;
	int 	nBeExchange_itemType;
	int 	nBeExchange_itemNum;
	char 	szUserName[NAME_LEN];
	char	szXingMing[NAME_LEN];
	char	szPhone[PHONE_LEN];
	char 	szMsgAddr[POSTAL_ADDR_LEN];
};

struct LobbyExchangeGiftRes_Step2
{
	HEADER;
	int	 	nUserID;
	int 	nSiteID;
	int 	nLeft;
	int 	nError;
	int		nExchange_itemType;
	int 	nExchange_itemNumLeft;
	int 	nBeExchange_itemType;
	int 	nBeExchange_itemNum;
	char 	szUserName[NAME_LEN];
	char	szXingMing[NAME_LEN];
	char	szMsgContext[512];
};

//拉新活动送积分

enum {
	INVITE_USER_SENDSCORE_LOGIN_1 = 1,
	INVITE_USER_SENDSCORE_LOGIN_2,
	INVITE_USER_SENDSCORE_LOGIN_3,
	INVITE_USER_SENDSCORE_LOGIN_4,
	INVITE_USER_SENDSCORE_LOGIN_5,
	INVITE_USER_SENDSCORE_GAME_10 = 10,
	INVITE_USER_SENDSCORE_GAME_20 = 20,
	INVITE_USER_SENDSCORE_GAME_30 = 30,
	INVITE_USER_SENDSCORE_GAME_60 = 60,
	INVITE_USER_SENDSCORE_BIND = 100,
	INVITE_USER_NEWUSER_LOGIN,
};

//通知有新记录标志
struct InviteUserNofityNewRecordRsp
{
	HEADER;
	int nUserID;
	int nRecord;
};

//客户端请求
struct InviteUserRemaindUserScoreReq
{
	HEADER;
	int nUserID;
	int nPerPage; //这次请求多少个，不大于10
	long long nRecord; //从0开始,后续发送请求时需要上一次请求的nRecord 
};

struct InviteUserRemaindRecord
{
	int nInvitedUserID;
	int nType;
	int nScore;
	int utime;
	int gameTime; //上次达成条件的游戏时间
	int nLogin; //上次达成条件的登陆天数
	char awardTime[20];
	char szInvitedUserName[NAME_LEN];
	char szNickName[NAME_LEN];
	char szContext[256];
};


//服务器返回nCount条记录，nRecod实际上是数据库中的id，用它来排序
struct InviteUserRemaindUserScoreRsp
{
	HEADER;
	int nUserID;
	int nPerPage;
	long long nRecord;
	int nCount;			//服务器返回nCount条记录
	InviteUserRemaindRecord ScoreRecord[1];
};

//请求玩家列表信息
struct InviteUserInvitedUserListReq
{
	HEADER;
	int nUserID;
	int nPerPage;
	long long nRecord;
};

struct InviteUserInvitedUserRecord
{
	int utime;
	char daytime[20];
	char szUserName[NAME_LEN];
	char szNickName[NAME_LEN];
};

struct InviteUserInvitedUserListRsp
{
	HEADER;
	int nUserID;
	int nPerPage;
	long long nRecord;
	int nCount;                    //返回nCount长度的数组，不大于20
	InviteUserInvitedUserRecord UserRecord[1];
};

struct CSShareHongbaoReq
{
	HEADER;
    int devicetype; // 1:android  2:ios
};

struct SCShareHongbaoRsp
{
	HEADER;
    int result; // 0-成功，并获得一个额外红包  -2: 已达当日分享获得红包上限 -1: 活动已经关闭
};

struct CSGetHongbaoRewardReq
{
	HEADER;
    int devicetype; // 1:android  2:ios
};

enum ERewardType
{
    E_Reward_Score      = 1, // 积分
    E_Reward_Prize      = 2, // 奖品劵
    E_Reward_Item       = 3, // 道具
};

enum EItemType
{
	E_Item_ImageQingTianZhu = 1000,
	E_Item_ImageDaHuangFeng = 1001,
	E_Item_ImageBaTianHu = 1002,
	E_Item_ImageXiaoWanXi = 1003,
	E_Item_ImageXiaoXin = 1004, 
	E_Item_LoudSpeaker = 10000,
	E_Item_GoldCard,
	E_Item_HongBao,
	E_Item_IPadAtom,       //预置内容可以调整
	E_Item_IP6Atom =10005, 

	E_Item_CanSaiQuan = 10006,
	E_Item_SlotMatchine_Num = 10007,

	E_Item_10YuanPhoneAtom = 50001,
	E_Item_20YuanPhoneAtom,
	E_Item_30YuanPhoneAtom,
	E_Item_100YuanJingdongAtom,



};
struct HongbaoReward
{
    int type;       // ERewardType
    int val;        // 道具id, 
    int count;      // 数量
    int reserve;    // 保留字段，如果道具有时限，则表示时限(小时)
};
struct SCGetHongbaoRewardRsp
{
	HEADER;
    int result;     // 0-成功 -1:没有红包道具 -2:红包数量不足 -3:数据库操作失败
    int count;      // 奖励个数
    HongbaoReward reward[0];
};

struct SCGetAwardNotify
{
	HEADER;
    int count;      // 奖励个数
	int awardFrom;  // 奖励来源
    HongbaoReward reward[0];
};

struct CSMsgLoginGameChannelInfo
{
	HEADER;
    char channel[32];
};

struct SCLastGameResult
{
	HEADER;
    long long score;
    int gameid;
    int serverid;
};

enum {
	ERR_ExCode_NO_FIND = 1, //找不到该兑换码
	ERR_ExCode_USED, //已经使用过了
	ERR_ExCode_Delete, //被管理员删除，紧急处理吗
	ERR_ExCode_Time_Bef, //还没到开始兑换时间
	ERR_ExCode_Time_Aft, //最晚兑换时间已经过期
	ERR_ExCode_Accounts_Once, //同一账号使用同一批次的兑换码只能兑换一次，
};

enum 
{
	EXCHANGE_CODE_ITEM_TYPE_1 = 1, //积分
	EXCHANGE_CODE_ITEM_TYPE_2,	   //奖品券
	EXCHANGE_CODE_ITEM_TYPE_3,     //道具
	EXCHANGE_CODE_ITEM_TYPE_4,     //银券通
};

struct LobbyExchangeCodeReq
{
	HEADER;
	int nOSID;
	char szExCode[64];
};

struct ExchangeCodeItem
{
	int nType;
	int nItemID;
	int nItemNum;
};

struct LobbyExchangeCodeRsp
{
	HEADER;
	int nError;
	int nSuccess;  //==1:成功
	int nCount;
	ExchangeCodeItem items[1];
};

typedef struct tagCSClientLoginReq
{
	HEADER;
	int 			nUserID;
	int 			nGameID;
	int 			nSiteID;
	char 			szUserName[NAME_LEN];
	char 			szNickName[NAME_LEN];
	char 			szChannelID[CHANNELID_LEN];
    char            token[TOKEN_LEN];
}CSClientLoginReq;

typedef struct tagCSGameClientLoginReq
{
    HEADER;
	int 			nUserID;
	int 			nGameID;
	int 			nSiteID;
	char 			szUserName[NAME_LEN];
	char 			szNickName[NAME_LEN];
	char 			szChannelID[CHANNELID_LEN];
}CSGameClientLoginReq;

typedef struct tagLoginClientAuthenRsp
{
    HEADER;
    ODEUInt32   ulUserID;                       //用户ID
    long long       nScore;                         //用户银子
    ODEUInt32   ulCoin2Award;                   //银券通
    ODEUInt32   ulCompeteScore;                 //参赛券
    ODEUInt32   ulAwardScore;                   //奖品券
    unsigned char   ucGender;                       //用户性别

	unsigned char   ucIsSetNickname;				//是否设置了昵称
	char			szNickname[NAME_LEN];			//玩家昵称
	//0918 孤獨的巧克力添加 是否首次充值标志
	int				uFirstCharge;					// 1 代表为首充用户
	int				uVipForAnnivesary;				// 0 不是VIP用户 98 黄金会员  99白金会员
	int				nSendTimes;
	int				nHeadImage;						//设置头像索引
	long long		nBankScore;						//银行积分
	int				LastGameID;						//上次登陆的游戏ID
	int				LastServerID;					//上次登陆的房间ID
    char            token[TOKEN_LEN];
} LoginClientAuthenRsp;

typedef struct tagLoginClientNoSiteAuthenRsp
{
    HEADER;
	ODEUInt32   ulUserID;                       //用户ID
	long long       nScore;                         //用户银子
	ODEUInt32   ulCoin2Award;                   //银券通
	ODEUInt32   ulCompeteScore;                 //参赛券
	ODEUInt32   ulAwardScore;                   //奖品券
	unsigned char   ucGender;                       //用户性别
	int				siteId;

	unsigned char   ucIsSetNickname;				//是否设置了昵称
	char			szNickname[NAME_LEN];			//玩家昵称
	//0918 孤獨的巧克力添加 是否首次充值标志
	int				uFirstCharge;					// 1 代表为首充用户
	//1031  周年庆VIP标识
	int				uVipForAnnivesary;				// 0 不是VIP用户 98 黄金会员  99白金会员
	int				nSendTimes;
	int				nHeadImage;						//设置头像索引
	long long		nBankScore;						//银行积分
	int				LastGameID;						//上次登陆的游戏ID
	int				LastServerID;					//上次登陆的房间ID
    char            token[TOKEN_LEN];
} LoginClientNoSiteAuthenRsp;

typedef struct tagCLConfigVersionCheckReq
{
	HEADER;
	int			   nGameID;
}CLConfigVersionCheckReq;

typedef struct tagCLConfigVersionCheckRsp
{
	Header;
	char		   szConfigVersion[32];
	int			   nResult;
}CLConfigVersionCheckRsp;

typedef struct tagCSGetUserSerialNumsberReq
{
	Header;
	int			nUserID;
}CSGetUserSerialNumsberReq;

typedef struct tagCSGetUserSerialNumsberRsp
{
	Header;
	int			nUserID;
	long long	SerialNumbers;
}CSGetUserSerialNumsberRsp;

typedef struct tagCSGetUserGuidanceInfoReq
{
	Header;
	int			nUserID;
}CSGetUserGuidanceInfoReq;

typedef struct tagCSGetUserGuidanceInfoRsp
{
	Header;
	int			nUserID;
	int			AddGameCoin;
	int			AddNums;
	int			NoticeNums;
	int			SiteID;
	char		szActivityID[32];
}CSGetUserGuidanceInfoRsp;

typedef struct tagCSDownloadContentTryReq
{
	Header;
	int			nUserID;
	int			nGameID;
	int			nContentID;
}CSDownloadContentTryReq;

//PC引导流程
typedef struct tagCSGuide2PCReq
{
	Header;
	int				nUserID;
	int				nSiteID;
}CSGuide2PCReqData;

typedef struct tagCSGuide2PCRsp
{
	Header;
	int				nUserID;
	int				nSiteID;
	int				nNoticeNums;
	char			nDownloadImage[64];
	char			nNoticeLinks[128];
	int				nResult;
}CSGuide2PCRspData;


typedef struct tagLobbyDownloadContentReq
{
	Header;
	int						nUserID;
	int						nSiteID;
	int						nGameID;
	char					szChannelID[32];
}LobbyDownloadContentReqData;

typedef struct tagLobbyDownloadContentRsp
{
	int						nDownloadContentID;                         //download id
	int						nContentArea;								//content area	
	int						nContentType;								//contentType
	int						nHotTips;									//hot tips
	int						nGameID;									//game id
	int						nContentSize;								//content size
	int						nContentCounts;								//content counts
	char					szContentVersion[10];						//content version
	char					szContentTitle[28];							//content title
	char					szContentDownloadLinks[164];				//content http links
}LobbyDownloadContentRspData;

//设置使用音效id
typedef struct tagLobbySetDownloadContentReq
{
	Header;
	int						nUserID;
	int						nSiteID;
	int						nGameID;
	int						nContentID;
	char					szChannelID[32];
	char					szContentSettingString[512];
}LobbySetDownloadContentReqData;

typedef struct tagLobbySetDownloadContentRsp
{
	Header;
	int						nUserID;
	char					szContentID[512];
	ODEInt32					nResult;
}LobbySetDownloadContentRspData;


//金牌的开关请求
typedef struct tagCSKingCardFlagReq
{
	Header;
	int	ModifyOrReq;      // 0是请求 非0表示修改
	// 注意使用1个比特位来表示对应特殊牌的开关
	// 修改时，第0个比特位固定为1, 第1个比特位开始分别表示 金牌、美女牌 的开关情况
};

typedef struct tagSCKingCardFlagRsp
{
	Header;
	int curStat;         //当前的状态 0是未使用，1是使用
};

struct tagLobbyGetLoginInfoReq
{
	Header;
	int							nUserID;
	int							nGameID;
	char						szLoginMachineSerial[33];
};

//用于修改昵称收费
enum {
	MOD_NICKNAME_ERR_NOMONEY = 1,			//身上的钱不够 			
	MOD_NICKNAME_ERR_NICKNAME_EXIST	= 2, 	//该昵称已经存在
	MOD_NICKNAME_ERR_NO_RIGHT_LEN = 3, 		//昵称长度不合法
	MOD_NICKNAME_ERR_CONTAIN_FORBIDSTR = 4,	//昵称中存在不合法字符	
	MOD_NICKNAME_ERR_IN_GAME =5,
};

typedef struct tagCSModifyNickNameReq
{
	Header;
	char szNickName[NAME_LEN];
}CSModifyNickNameReq;

typedef struct tagSCModifyNickNameRsp
{
	Header;
	int ret;
}SCModifyNickNameRsp;

typedef struct tagSCUserFirstLoginNtf
{
	Header;
}SCUserFirstLoginNtf;


typedef struct tagSCMobileActiveNoticeReq
{
	Header;
	int  	nSizeID;
	char 	szChannelID[32];
};

typedef struct tagSCMobileActiveNoticeRsp
{
	Header;
	char    activeImage[200];
	int 	imageSize;
	int		noticeType;
};

typedef struct tagCSAskConnectionInfoReq
{
	Header;
};

typedef struct tagSCAskConnectionInfoRsp
{
	Header;
    char ip[32];
    int port;
};

typedef struct tagSCActivity20150505InfoNotify
{
	Header;
	int userType; 			// 玩家类型           1:被邀请的新注册用户  2:老用户
	int remainTime; 		// 剩余挑战次数
	int curActivityType; 	// 活动进度(总进度)   0:活动尚未开始，等待用户绑定手机    1:进行赢1局得5元活动  2:进行7局赢5局活动 3:全部活动已完成
	int gameProgressWin;	// 当前挑战游戏内的活动进度(7局赢5局获胜数)
	int gameProgressPlay;	// 当前挑战游戏内的活动进度(7局赢5局总玩数)
}SCActivity20150505InfoNotify;

typedef struct tagSCActivity20150505ProgressUpdate
{
	// 这个消息只通知 7局赢5局的活动进度
	// 注意：挑战成功后还会收到 SCActivity20150505GetAwardNotify 这个消息通知
	Header;
	int curChallengeResult;		// 当前的挑战结果 0:未完成  1:失败 2:成功
	int remainTime;				// 剩余挑战次数
	int gameProgressWin;		// 当前挑战游戏内的活动进度(7局赢5局获胜数)
	int gameProgressPlay;		// 当前挑战游戏内的活动进度(7局赢5局总玩数)
}SCActivity20150505ProgressUpdate;

typedef struct tagSCActivity20150505GetAwardNotify
{
	Header;
	int activityType; // 获得奖励的活动   1:进行赢1局得5元活动  2:进行7局赢5局活动
	int cashCount;	  // 活动活动的现金数 
	int nextActivityType; // 下一步要进行的活动 1:进行赢1局得5元活动  2:进行7局赢5局活动 3:全部活动已完成
}SCActivity20150505GetAwardNotify;

typedef struct tagCSActivity20150505BindPhoneDone
{
	// 如果是在斗地主房间内绑定了手机，要发这个消息上来
	// 服务器检查是否真的绑定成功，如果绑定成功，
	// SCActivity20150505GetAwardNotify 消息通知绑定后获得奖励及下一个活动.
	// 注意老用户绑手机没有奖励
	Header;
}CSActivity20150505BindPhoneDone;

typedef struct tagSCBreakGameInfoNotify
{
	Header;
	int gameId;
	int serverId;
	int enterTime; // 进入房间时间
}SCBreakGameInfoNotify;


struct CSUseLotteryItemReq
{
	HEADER;
    int devicetype; // 1:android  2:ios
};
struct SCUseLotteryItemRsp
{
	HEADER;
    int result;     // 0-成功 -1:没有抽奖道具 -2:积分不足以打开抽奖道具 -3:数据库操作失败 
    int count;      // 奖励个数
    HongbaoReward reward[0];
};

typedef struct tagCSActivity20150505AskInfoReq
{
	HEADER;
} CSActivity20150505AskInfoReq;

typedef struct tagSCActivity20150505AskInfoRsp
{
	HEADER;
	int isBindPhone; 	// 是否绑定手机
	int userType;		// 玩家类型           1:被邀请的新注册用户  2:老用户
	int remainTime; 	// 剩余挑战次数
	int curActivityType;// 活动进度(总进度)   0:活动尚未开始，等待用户绑定手机    1:进行赢1局得5元活动  2:进行7局赢5局活动 3:全部活动已完成
	int cashChallenge;	// 挑战获得的现金
	int cashSpread;		// 推广获得的现金
} SCActivity20150505AskInfoRsp;

//一个玩家请求赞另外一个玩家
typedef struct tagOnePraiseAnotherReq
{
	HEADER;
	int						fromUserId;			//谁准备赞玩家
	int						toUserId;			//哪个玩家被赞了
}OnePraiseAnotherReq;

//服务器广播某个玩家被另外的玩家赞了，这个玩家被赞了总共多少次
typedef struct tagOnePraiseAnotherRsp
{
	HEADER;
	int						errorCode;			//操作结果	0：成功 1：失败
	int						fromUserId;			//谁准备赞玩家
	int						toUserId;			//哪个玩家被赞了
	ODEUInt32			totalPraiseCount;	//被赞的玩家总共被赞的次数
}OnePraiseAnotherRsp;

//一个玩家吐槽另外一个玩家
typedef struct tagOneRidiculeAnotherReq
{
	HEADER;
	int						fromUserId;			//谁准备吐槽玩家
	int						toUserId;			//哪个玩家被吐槽了
}OneRidiculeAnotherReq;

//服务器返回吐槽玩家的结果
typedef struct tagOneRidiculeAnotherRsp
{
	HEADER;
	int						errorCode;			//操作结果	0：成功 >=1：失败
	int						fromUserId;			//谁准备吐槽玩家
	int						toUserId;			//哪个玩家被吐槽了	
	ODEUInt32			totalRidiculeCount;	//被吐槽的玩家总共被吐槽的次数
}OneRidiculeAnotherRsp;


typedef struct tagLobbyChannelInfoFailedRsp
{
	HEADER;
	int						nUserID;
	int						nLoadType;
}LobbyChannelInfoFailedRsp;

typedef struct tagCSInteractPropsReq
{
	HEADER;
	int propsID;
	char toChair;
} CSInteractPropsReq;

typedef struct tagSCInteractPropsRsp
{
	HEADER;
	int propsID;
	char toChair;
	char sucOrNot;      //成功与否，0是成功，非0是错误码
}SCInteractPropsRsp;

typedef struct tagSCInteractPropsNotify
{
	HEADER;
	int propsID;
	char fromChair;
	char toChair;
} SCInteractPropsNotify;

typedef struct tagCSGlamourValueReq
{
	HEADER;
	char chair;
} CSGlamourValueReq;

typedef struct tagSCGlamourValueRsp
{
	HEADER;
	char chair; //查看某个座位的玩家的魅力值
	int  glamourValue;
} SCGlamourValueRsp;

enum
{
	E_AuxiliaryData_Glamour, // 魅力值

	E_AuxiliaryData_Count = 10,
};
typedef struct tagSelfAuxiliaryDataNotify
{
	HEADER;
	int auxiData[E_AuxiliaryData_Count];
} SelfAuxiliaryDataNotify;


typedef struct tagGuanDanGuideRewardReq
{
	HEADER;
	int userID;
	char deviceID[64];
}GuanDanGuideRewardReq;

typedef struct tagGuanDanGuideRewardRsp
{
	HEADER;
	int returnCode;
	int score;
}GuanDanGuideRewardRsp;

typedef struct tagGetRechagePointReq
{
	HEADER;
	int userID;
}GetRechagePointReq;

typedef struct tagGetRechagePointRsp
{
	HEADER;
	int returnCode;
	int rechargePoint;
}GetRechagePointRsp;

typedef struct tagCSMsgTVCardInfo
{
	HEADER;
	int userID;
	char card[32];
} CSMsgTVCardInfo;

typedef struct tagSCMsgKickOutNtf
{
	HEADER;
	int reason; // ErrorCode.xml
} SCMsgKickOutNtf;

#pragma pack(pop)

#endif

