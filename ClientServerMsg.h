#ifndef _SERVER_CLIENT_H_
#define _SERVER_CLIENT_H_

//#include "Game/NetMessage.h"

enum
{
    SC_MSG_BEGIN        = 0xE100,
    
    //�һ���Ʒ���� ��һ��
	LOBBYCLIENT_LOBBY_EXCHANGE_GIFT_STEP1_REQ,
	LOBBYCLIENT_LOBBY_EXCHANGE_GIFT_STEP1_RSP,
	//�һ���Ʒ���� �ڶ���
	LOBBYCLIENT_LOBBY_EXCHANGE_GIFT_STEP2_REQ,
	LOBBYCLIENT_LOBBY_EXCHANGE_GIFT_STEP2_RSP,
	
    
    SC_MSG_MOBILE_ACTIVITY_NTF,
    SC_MSG_MOBILE_ACTIVITY_DATA_UPDATE_NTF,
    SC_MSG_MOBILE_ACTIVITY_GET_AWARD_RSP,

	//���»�ͻ���֪ͨ
	INVITE_USER_LOBBYSERVER_NOTIFY_USER_MSG,
	INVITE_USER_LOBBYCLIENT_GET_SCORE_RECORD_REQ,
	INVITE_USER_LOBBYCLIENT_GET_SCORE_RECORD_RSP,
	INVITE_USER_LOBBYCLIENT_GET_USER_RECORD_REQ,
	INVITE_USER_LOBBYCLIENT_GET_USER_RECORD_RSP,
	//�һ���
	LOBBYCLIENT_EXCHANGECODE_AWARD_REQ,
	LOBBYCLIENT_EXCHANGECODE_AWARD_RSP,
	
	//  �״ε�½��Ϣ
	SC_MSG_USER_FIRST_LOGIN_NTF,
    CS_ASK_CONNECTION_INFO_REQ,
    SC_ASK_CONNECTION_INFO_RSP,
	
	// Ӯ1����5Ԫ����Э��
	SC_ACTIVITY20150505_INFO_NTF,
	SC_ACTIVITY20150505_PROGRESS_UPDATE,
	SC_ACTIVITY20150505_GET_AWARD_NTF,
	CS_ACTIVITY20150505_BIND_PHONE_DONE,
	
	// ������½�����Ϸ������Ϣ
	SC_USER_GAME_BREAK_INFO_NTF,

	
	// ��������Ӯ1����5Ԫ�����Э��
	CS_ACTIVITY20150505_ASK_INFO_REQ,
	SC_ACTIVITY20150505_ASK_INFO_RSP,

	// ͳһ�������֪ͨ
	SC_GET_AWARD_NOTIFY,

	// ����򿪳齱����
	CS_USE_LOTTERY_ITEM_REQ,
	SC_USE_LOTTERY_ITEM_RSP,

    // ---------------------------------------------------

    CS_MSG_BEGIN        = 0xE800,

    CS_MSG_MOBILE_ACTIVITY_GET_AWARD_REQ,
    // ��ҷ����ú��
    CS_MSG_SHARE_GET_HONGBAO_REQ,
    SC_MSG_SHARE_GET_HONGBAO_RSP,
    // ��Һ���齱
    CS_MSG_GET_HONGBAO_REWARD_REQ,
    SC_MSG_GET_HONGBAO_REWARD_RSP,
    // ��½��Ϸ����������Ϣ
    CS_MSG_LOGINGAME_CHANNEL_INFO,
    // ֪ͨclient�ϴ���Ϸ�ڶ��ߺ�Ľ�����Ϣ
    SC_MSG_NOTIFY_LASTGAME_RESULT,
	
	//�����ͻ��˵�½���������� �����֮ǰ�ĵ�½Э�飬������������Ϸid��վ��id��Ϣ��
	SC_MSG_CLIENT_LOGIN_REQ,
	//��Ϸ�ͻ��˵�½����������
	SC_MSG_GAMECLIENT_LOGIN_REQ,

    // 2015-01-29 �µĵ�½, ��½����Э��ṹ����,ʹ���µ�����id,
    // ��½����ʹ���µķ��ؽṹ, �����½ʧ�ܻ���ԭ����Э��,��½�ɹ�����LOGIN_CLIENT_AUTHEN_RSP
    // LobbyClient <-> LoginServer
    CLIENT_LOGIN_AUTHEN_REQ,        // ���������� tagLobbyAuthenReq
    CLIENT_LOGIN_NOSITE_AUTHEN_REQ, // ���������� tagLobbyAuthenWithNoSiteIdReq
    LOGIN_CLIENT_AUTHEN_RSP,        // ��վ��ĵ�½���� tagLoginClientAuthenRsp
    LOGIN_CLIENT_NOSITE_AUTHEN_RSP, // ��վ��ĵ�½���� tagLoginClientNoSiteAuthenRsp

	//�����汾����֤
	CL_CONFIG_VERSION_CHECK_REQ,    //�����汾����֤
	CL_CONFIG_VERSION_CHECK_RSP,     

	//��ȡPC�����û����� �ж��Ƿ��ǲ����û�
	CS_MSG_GET_FLAGSERIALNUMBER_REQ,
	CS_MSG_GET_FLAGSERIALNUMBER_RSP,

	//��ȡ֪ͨ����
	CS_MSG_GET_GUIDANCE_REQ,
	CS_MSG_GET_GUIDANCE_RSP,
	
	// ������֪ͨ��Ϣ, ��ϢЭ�鶨����ClientMatchProto.xml��
	SC_USER_MATCH_INFO_UPDATE,
	SC_MATCH_RESULT_NTF,
	SC_CUR_MATCH_SCORE_NTF,

	CS_MSG_DOWNLOAD_CONTENT_TRY_REQ,
	
	CS_MSG_GET_GUIDANCE2PC_REQ,
	CS_MSG_GET_GUIDANCE2PC_RSP,
	SC_MSG_AGAIN_ENTER_MATCH_INFO_NTF,
	
	//���ƿ��ص�����
	LOBBYCLIENT_KINGCARD_FLAG_REQ,
	LOBBYCLIENT_KINGCARD_FLAG_RSP,
	//�ǳƶ���޸��շ�
	CS_MSG_MODIFY_NICKNAME_REQ,
	SC_MSG_MODIFY_NICKNAME_RSP,
	
	//�ֻ��˻֪ͨ
	LOBBYCLIENT_ACTIVE_NOTICE_REQ,
	LOBBYCLIENT_ATTICE_NOTICE_RSP,

	//��������
	CS_MSG_INTERACTPROPS_REQ,
	SC_MSG_INTERACTPROPS_RSP,

	//����ֵ
	CS_MSG_GLAMOURVALUE_REQ,
	SC_MSG_GLAMOURVALUE_RSP,

	// ����������Ϣ�㲥
	SC_MSG_INTERACTPROPS_NTF,
	// ͬ���Լ�������ֵ�����������Ϣ
	SC_MSG_SELF_AUXILIARY_DATA_NTF,

	//�Ĵ��齫��������
	SC_MSG_SCMJ_STARNUM_RSP,
	//��һ��ֱ仯ʱ��֪ͨͬ���������
	SC_MSG_NOTIFY_TABLE_PLAYERS_COIN_CHANGE,
    
    //�����˿˵�Э��
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

	//�������������콱
	CS_MSG_GUANDAN_GUIDE_REWARD_REQ,
	SC_MSG_GUANDAN_GUIDE_REWARD_RSP,

	// ��½��Ϸ�����Լ��Ĵ�������Ϣ
    CS_MSG_LOGINGAME_AGENT_INFO,

	CS_MSG_GET_RECHARGEPOINT_REQ,
	SC_MSG_GET_RECHAGREPOINT_RSP,

	//��ȡԪ�����Թ����ͷ��
	CS_MSG_GET_YUANBAO_SHOP_REQ,
	SC_MSG_GET_YUANBAO_SHOP_RSP,

	//Ԫ������ͷ��
	CS_MSG_BUY_AVATAR_BY_YUANBAO_REQ,
	SC_MSG_BUY_AVATAR_BY_YUANBAO_RSP,

	//�ݲ����������غ͹���
	CS_MSG_BAICAISHEN_GET_SHOWDATA_REQ,
	SC_MSG_BAICAISHEN_GET_SHOWDATA_RSP,

	//�ݲ������������Ϣ
	CS_MSG_BAICAISHEN_GET_XIANG_INFO_REQ,
	SC_MSG_BAICAISHEN_GET_XIANG_INFO_RSP,

	//�ݲ��������
	CS_MSG_BAICAISHEN_SHANGXIANG_REQ,
	SC_MSG_BAICAISHEN_SHANGXIANG_RSP,

	//������� 
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

	// ��������Ϣ֪ͨ
	SC_MSG_ANTI_ADDITION_WARN_NTF,

	// ������Ϸ�����б�
	CS_MSG_ASK_ROOM_LIST_REQ,
	SC_ROOM_LIST_NTF,

	// ��ֵ�ɹ�֪ͨ
	SC_BILLING_INFO_NTF,

	// ������Ϸ���������
	CS_MSG_GET_GAME_ONLINE_COUNTS_REQ,
	SC_MSG_GET_GAME_ONLINE_COUNTS_RSP,

	S_MSG_REPORT_ERROR,

	// �㱨�Լ���TV���ܿ���
	CS_MSG_TV_CARD_INFO,

	// ͳһ����֪ͨ
	SC_MSG_KICK_OUT_NTF,
};

// �豸����
enum EDeviceType
{
    E_DeviceType_PC = 101,
    E_DeviceType_Android = 102,
    E_DeviceType_IOS = 103,
};


// ����odao_client_msg.h �У�client��server����Э��
const unsigned short  MOBILE_KEEP_ALIVE_MSG = 0xB8;   //����������Ϣ
typedef struct MobileKeepAlive
{ 
    HEADER;
}MobileKeepAliveDef;

#define 	NAME_LEN			32		//���ֳ���
#define 	PHONE_LEN			20     	//�绰����  ����
#define		POSTAL_ADDR_LEN		200		//ͨ�ŵ�ַ	����
#define 	CHANNELID_LEN		32		//������Ϣ  ����
#define     TOKEN_LEN           200     //token ����


#pragma pack(push, 4)

typedef struct tagSCMobileActivityNtf
{
    HEADER;
    long long activityId;   // �id
    int activityType;       // ����� 1-�ۻ�ʤ��� 2-����ʤ���
    int awardRequire;       // ����Ҫ�����ֵ
    int curData;            // ��ǰ����ֵ
    int isAwardDone;        // 0-δ���� 1-������
}SCMobileActivityNtf;

typedef struct tagSCMobileActivityDataUpdateNtf
{
    HEADER;
    long long activityId;   // �id
    int activityType;       // ����� 1-�ۻ�ʤ��� 2-����ʤ���
    int data;               // ���µ���ֵ
    int awardRequire;       // ����Ҫ�����ֵ
    int flag;               // 1-�Ѵﵽ��һ�����������ȡ
}SCMobileActivityDataUpdateNtf;

typedef struct tagCSMobileActivityGetAwardReq
{
    HEADER;
    long long activityId;   // ������ȡ�����Ļid
}CSMobileActivityGetAwardReq;

typedef struct tagSCMobileActivityGetAwardRsp
{
    HEADER;
    int result;             // �콱���
    long long activityId;   // �id
    int activityType;       // ����� 1-�ۻ�ʤ��� 2-����ʤ���
    int awardType;          // 1-����
    long long awardData;    // type=1ʱ��ʾ����id
    int awardCount;         // ����������
    int nextAwardRequire;   // ��һ������Ҫ�����ֵ
    int isAwardDone;        // 0-δ���� 1-������
}SCMobileActivityGetAwardRsp;

//�һ���Ʒ����ͷ��� ��һ��
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

//������Щ�����ڶһ���Ʒ���ص�nError�ֶ���
#define 	EXCHANGE_GIFT_ERR_NO_ERR					0		//�޴���
#define		EXCHANGE_GIFT_ERR_BEFORE_TIME				1		//��û���ҽ�ʱ��
#define		EXCHANGE_GIFT_ERR_AFTER_TIME				2		//�ҽ�ʱ���ѹ�
#define		EXCHANGE_GIFT_ERR_NO_ITEMTYPE				3		//�Ҳ����һ���
#define		EXCHANGE_GIFT_ERR_NO_BE_ITEMTYPE			4		//�Ҳ������һ���
#define		EXCHANGE_GIFT_ERR_NO_ENOUGH_ITEMNUM			5		//�һ����������
#define		EXCHANGE_GIFT_ERR_NO_ENOUGH_BEITEMNUM		6		//���һ����������
#define		EXCHANGE_GIFT_ERR_EXCHANGE_CLOSE			7		//�����ѱ��ر�
#define		EXCHANGE_GIFT_ERR_NOLEFT_TODAY				8		//�����޶һ��ˣ��������
#define		EXCHANGE_GIFT_ERR_NOLEFT_AMOUNT				9		//�һ����ˣ�ûʣ����
#define		EXCHANGE_GIFT_ERR_DB_NO_INSERT				10		//���ݿ�������
#define		EXCHANGE_GIFT_ERR_DB_NO_SELECT				11		//���ݿ���Ҵ���
#define		EXCHANGE_GIFT_ERR_DB_NO_UPDATE				12		//���ݿ���´���
#define		EXCHANGE_GIFT_ERR_NO_BIND_PHONE				13		//δ���ֻ�
#define		EXCHANGE_GIFT_ERR_ARG_ERROR					14		//����������������



struct LobbyExchangeGiftRes_Step1
{
	HEADER;
	int 	nUserID;
	int		nSiteID;
	int 	nLeft;  				//��Ʒʣ�����
	int 	nError; 				// 0 �޴���
	int 	nExchange_itemType;
	int 	nExchange_itemNum;
	int 	nBeExchange_itemType;
	int 	nBeExchange_itemNum;
	char 	szUserName[NAME_LEN];
	char 	szMsgContext[512];
};

//�һ���Ʒ����ͷ��� �ڶ���

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

//���»�ͻ���

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

//֪ͨ���¼�¼��־
struct InviteUserNofityNewRecordRsp
{
	HEADER;
	int nUserID;
	int nRecord;
};

//�ͻ�������
struct InviteUserRemaindUserScoreReq
{
	HEADER;
	int nUserID;
	int nPerPage; //���������ٸ���������10
	long long nRecord; //��0��ʼ,������������ʱ��Ҫ��һ�������nRecord 
};

struct InviteUserRemaindRecord
{
	int nInvitedUserID;
	int nType;
	int nScore;
	int utime;
	int gameTime; //�ϴδ����������Ϸʱ��
	int nLogin; //�ϴδ�������ĵ�½����
	char awardTime[20];
	char szInvitedUserName[NAME_LEN];
	char szNickName[NAME_LEN];
	char szContext[256];
};


//����������nCount����¼��nRecodʵ���������ݿ��е�id������������
struct InviteUserRemaindUserScoreRsp
{
	HEADER;
	int nUserID;
	int nPerPage;
	long long nRecord;
	int nCount;			//����������nCount����¼
	InviteUserRemaindRecord ScoreRecord[1];
};

//��������б���Ϣ
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
	int nCount;                    //����nCount���ȵ����飬������20
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
    int result; // 0-�ɹ��������һ��������  -2: �Ѵﵱ�շ����ú������ -1: ��Ѿ��ر�
};

struct CSGetHongbaoRewardReq
{
	HEADER;
    int devicetype; // 1:android  2:ios
};

enum ERewardType
{
    E_Reward_Score      = 1, // ����
    E_Reward_Prize      = 2, // ��Ʒ��
    E_Reward_Item       = 3, // ����
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
	E_Item_IPadAtom,       //Ԥ�����ݿ��Ե���
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
    int val;        // ����id, 
    int count;      // ����
    int reserve;    // �����ֶΣ����������ʱ�ޣ����ʾʱ��(Сʱ)
};
struct SCGetHongbaoRewardRsp
{
	HEADER;
    int result;     // 0-�ɹ� -1:û�к������ -2:����������� -3:���ݿ����ʧ��
    int count;      // ��������
    HongbaoReward reward[0];
};

struct SCGetAwardNotify
{
	HEADER;
    int count;      // ��������
	int awardFrom;  // ������Դ
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
	ERR_ExCode_NO_FIND = 1, //�Ҳ����öһ���
	ERR_ExCode_USED, //�Ѿ�ʹ�ù���
	ERR_ExCode_Delete, //������Աɾ��������������
	ERR_ExCode_Time_Bef, //��û����ʼ�һ�ʱ��
	ERR_ExCode_Time_Aft, //����һ�ʱ���Ѿ�����
	ERR_ExCode_Accounts_Once, //ͬһ�˺�ʹ��ͬһ���εĶһ���ֻ�ܶһ�һ�Σ�
};

enum 
{
	EXCHANGE_CODE_ITEM_TYPE_1 = 1, //����
	EXCHANGE_CODE_ITEM_TYPE_2,	   //��Ʒȯ
	EXCHANGE_CODE_ITEM_TYPE_3,     //����
	EXCHANGE_CODE_ITEM_TYPE_4,     //��ȯͨ
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
	int nSuccess;  //==1:�ɹ�
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
    ODEUInt32   ulUserID;                       //�û�ID
    long long       nScore;                         //�û�����
    ODEUInt32   ulCoin2Award;                   //��ȯͨ
    ODEUInt32   ulCompeteScore;                 //����ȯ
    ODEUInt32   ulAwardScore;                   //��Ʒȯ
    unsigned char   ucGender;                       //�û��Ա�

	unsigned char   ucIsSetNickname;				//�Ƿ��������ǳ�
	char			szNickname[NAME_LEN];			//����ǳ�
	//0918 �ª����ɿ������ �Ƿ��״γ�ֵ��־
	int				uFirstCharge;					// 1 ����Ϊ�׳��û�
	int				uVipForAnnivesary;				// 0 ����VIP�û� 98 �ƽ��Ա  99�׽��Ա
	int				nSendTimes;
	int				nHeadImage;						//����ͷ������
	long long		nBankScore;						//���л���
	int				LastGameID;						//�ϴε�½����ϷID
	int				LastServerID;					//�ϴε�½�ķ���ID
    char            token[TOKEN_LEN];
} LoginClientAuthenRsp;

typedef struct tagLoginClientNoSiteAuthenRsp
{
    HEADER;
	ODEUInt32   ulUserID;                       //�û�ID
	long long       nScore;                         //�û�����
	ODEUInt32   ulCoin2Award;                   //��ȯͨ
	ODEUInt32   ulCompeteScore;                 //����ȯ
	ODEUInt32   ulAwardScore;                   //��Ʒȯ
	unsigned char   ucGender;                       //�û��Ա�
	int				siteId;

	unsigned char   ucIsSetNickname;				//�Ƿ��������ǳ�
	char			szNickname[NAME_LEN];			//����ǳ�
	//0918 �ª����ɿ������ �Ƿ��״γ�ֵ��־
	int				uFirstCharge;					// 1 ����Ϊ�׳��û�
	//1031  ������VIP��ʶ
	int				uVipForAnnivesary;				// 0 ����VIP�û� 98 �ƽ��Ա  99�׽��Ա
	int				nSendTimes;
	int				nHeadImage;						//����ͷ������
	long long		nBankScore;						//���л���
	int				LastGameID;						//�ϴε�½����ϷID
	int				LastServerID;					//�ϴε�½�ķ���ID
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

//PC��������
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

//����ʹ����Чid
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


//���ƵĿ�������
typedef struct tagCSKingCardFlagReq
{
	Header;
	int	ModifyOrReq;      // 0������ ��0��ʾ�޸�
	// ע��ʹ��1������λ����ʾ��Ӧ�����ƵĿ���
	// �޸�ʱ����0������λ�̶�Ϊ1, ��1������λ��ʼ�ֱ��ʾ ���ơ���Ů�� �Ŀ������
};

typedef struct tagSCKingCardFlagRsp
{
	Header;
	int curStat;         //��ǰ��״̬ 0��δʹ�ã�1��ʹ��
};

struct tagLobbyGetLoginInfoReq
{
	Header;
	int							nUserID;
	int							nGameID;
	char						szLoginMachineSerial[33];
};

//�����޸��ǳ��շ�
enum {
	MOD_NICKNAME_ERR_NOMONEY = 1,			//���ϵ�Ǯ���� 			
	MOD_NICKNAME_ERR_NICKNAME_EXIST	= 2, 	//���ǳ��Ѿ�����
	MOD_NICKNAME_ERR_NO_RIGHT_LEN = 3, 		//�ǳƳ��Ȳ��Ϸ�
	MOD_NICKNAME_ERR_CONTAIN_FORBIDSTR = 4,	//�ǳ��д��ڲ��Ϸ��ַ�	
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
	int userType; 			// �������           1:���������ע���û�  2:���û�
	int remainTime; 		// ʣ����ս����
	int curActivityType; 	// �����(�ܽ���)   0:���δ��ʼ���ȴ��û����ֻ�    1:����Ӯ1�ֵ�5Ԫ�  2:����7��Ӯ5�ֻ 3:ȫ��������
	int gameProgressWin;	// ��ǰ��ս��Ϸ�ڵĻ����(7��Ӯ5�ֻ�ʤ��)
	int gameProgressPlay;	// ��ǰ��ս��Ϸ�ڵĻ����(7��Ӯ5��������)
}SCActivity20150505InfoNotify;

typedef struct tagSCActivity20150505ProgressUpdate
{
	// �����Ϣֻ֪ͨ 7��Ӯ5�ֵĻ����
	// ע�⣺��ս�ɹ��󻹻��յ� SCActivity20150505GetAwardNotify �����Ϣ֪ͨ
	Header;
	int curChallengeResult;		// ��ǰ����ս��� 0:δ���  1:ʧ�� 2:�ɹ�
	int remainTime;				// ʣ����ս����
	int gameProgressWin;		// ��ǰ��ս��Ϸ�ڵĻ����(7��Ӯ5�ֻ�ʤ��)
	int gameProgressPlay;		// ��ǰ��ս��Ϸ�ڵĻ����(7��Ӯ5��������)
}SCActivity20150505ProgressUpdate;

typedef struct tagSCActivity20150505GetAwardNotify
{
	Header;
	int activityType; // ��ý����Ļ   1:����Ӯ1�ֵ�5Ԫ�  2:����7��Ӯ5�ֻ
	int cashCount;	  // �����ֽ��� 
	int nextActivityType; // ��һ��Ҫ���еĻ 1:����Ӯ1�ֵ�5Ԫ�  2:����7��Ӯ5�ֻ 3:ȫ��������
}SCActivity20150505GetAwardNotify;

typedef struct tagCSActivity20150505BindPhoneDone
{
	// ������ڶ����������ڰ����ֻ���Ҫ�������Ϣ����
	// ����������Ƿ���İ󶨳ɹ�������󶨳ɹ���
	// SCActivity20150505GetAwardNotify ��Ϣ֪ͨ�󶨺��ý�������һ���.
	// ע�����û����ֻ�û�н���
	Header;
}CSActivity20150505BindPhoneDone;

typedef struct tagSCBreakGameInfoNotify
{
	Header;
	int gameId;
	int serverId;
	int enterTime; // ���뷿��ʱ��
}SCBreakGameInfoNotify;


struct CSUseLotteryItemReq
{
	HEADER;
    int devicetype; // 1:android  2:ios
};
struct SCUseLotteryItemRsp
{
	HEADER;
    int result;     // 0-�ɹ� -1:û�г齱���� -2:���ֲ����Դ򿪳齱���� -3:���ݿ����ʧ�� 
    int count;      // ��������
    HongbaoReward reward[0];
};

typedef struct tagCSActivity20150505AskInfoReq
{
	HEADER;
} CSActivity20150505AskInfoReq;

typedef struct tagSCActivity20150505AskInfoRsp
{
	HEADER;
	int isBindPhone; 	// �Ƿ���ֻ�
	int userType;		// �������           1:���������ע���û�  2:���û�
	int remainTime; 	// ʣ����ս����
	int curActivityType;// �����(�ܽ���)   0:���δ��ʼ���ȴ��û����ֻ�    1:����Ӯ1�ֵ�5Ԫ�  2:����7��Ӯ5�ֻ 3:ȫ��������
	int cashChallenge;	// ��ս��õ��ֽ�
	int cashSpread;		// �ƹ��õ��ֽ�
} SCActivity20150505AskInfoRsp;

//һ���������������һ�����
typedef struct tagOnePraiseAnotherReq
{
	HEADER;
	int						fromUserId;			//˭׼�������
	int						toUserId;			//�ĸ���ұ�����
}OnePraiseAnotherReq;

//�������㲥ĳ����ұ������������ˣ������ұ������ܹ����ٴ�
typedef struct tagOnePraiseAnotherRsp
{
	HEADER;
	int						errorCode;			//�������	0���ɹ� 1��ʧ��
	int						fromUserId;			//˭׼�������
	int						toUserId;			//�ĸ���ұ�����
	ODEUInt32			totalPraiseCount;	//���޵�����ܹ����޵Ĵ���
}OnePraiseAnotherRsp;

//һ������²�����һ�����
typedef struct tagOneRidiculeAnotherReq
{
	HEADER;
	int						fromUserId;			//˭׼���²����
	int						toUserId;			//�ĸ���ұ��²���
}OneRidiculeAnotherReq;

//�����������²���ҵĽ��
typedef struct tagOneRidiculeAnotherRsp
{
	HEADER;
	int						errorCode;			//�������	0���ɹ� >=1��ʧ��
	int						fromUserId;			//˭׼���²����
	int						toUserId;			//�ĸ���ұ��²���	
	ODEUInt32			totalRidiculeCount;	//���²۵�����ܹ����²۵Ĵ���
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
	char sucOrNot;      //�ɹ����0�ǳɹ�����0�Ǵ�����
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
	char chair; //�鿴ĳ����λ����ҵ�����ֵ
	int  glamourValue;
} SCGlamourValueRsp;

enum
{
	E_AuxiliaryData_Glamour, // ����ֵ

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

