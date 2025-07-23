#ifndef __CLIENT_DATA_DEF_H__
#define __CLIENT_DATA_DEF_H__

#include "DataMd5.h"
#include "GameMessage.h"
#include "NetMessage.h"
#include "NetworkDelegate.h"
#include "MainScene.h"
#include "msg_PublicProto.h"
using namespace pbproto;
//��ǰ��վ��
#define _GAME_SITE_ID_  atoi(TT("GameSiteID"))

//��ϷID
#define _GAME_ID_	atoi(TT("GameID"))	

#define _GAME_SERVER_NORMAL_ROOM_ADDRSS_IP_			GetConfig("GD_NormalRoomIp_0")
#define _GAME_SERVER_NORMAL_ROOM_ADDRSS_PORT_		atoi(GetConfig("GD_NormalRoomPort_0"))

#define _GDGAME_SERVER_PRIVATE_ROOM_ADDRSS_IP_		GetConfig("GD_PrivateRoom_Ip_0")
#define _GDGAME_SERVER_PRIVATE_ROOM_ADDRSS_PORT_		atoi(GetConfig("GD_PrivateRoom_Port_0"))

#define _LOGIN_SERVER_ADDRSS_IP_					GetConfig("LoginServerIp")
#define _LOGIN_SERVER_ADDRSS_PORT_					atoi(GetConfig("LoginServerPort"))


//�Զ��忪��������Ϣ
struct tagCustomTableInfo
{
	int								iHostUserID;					//������UserID

	unsigned int					nTableID;						//����ID

	int								iBasePoint;						//��Ϸ������ע
	int								iTableSittedPlayerNum;			//���������µ��������

	char   							szTableNickName[NAME_LEN];		//�����ǳ�
	char 							szTablePasswd[PASSWD_LEN];		//��������
};

struct tagGameMessageBuffer
{
	ODEUInt32			u32GameMessageID;
	ODEUInt32			u32DataSize;
	ODEChar8			GameMessageData[4096];
};

struct tagDelayMessageBuffer
{
	ODEUInt32			u32GameMessageID;
	ODEUInt32			u32DataSize;
	ODEUInt32			u32TimeDelayTo;
	ODEChar8			GameMessageData[4096];
};

#pragma pack(push, 4)

struct tagUserSerialLoginTaskInfo
{
	int					nSerialSignCount;	
	int					nLoginPresentType[MAX_LOGIN_AWARD];	
	int					nPresentCount[MAX_LOGIN_AWARD];
	bool				bIsGettedAward;
	char				tTodayTime[128];
	char				nAwardDetailPerMonth[31];
};

struct tagUserDailyTaskInfo
{
	int						nUserID;
	long long				llUserTaskID;
	int						nTaskTypeID;		//DAILY_TASK_TYPE_ID
	int						nFinishValue;
	int						nTargetValue;
	bool					bIsGettedAward;
	int						nTotalAwardTypeID;
	int						nTotalAwardCount;
	char					szTaskName[256];
	char					szTaskDescription[512];		

	bool					bIsNewDailyTask;
	bool					bIsTipAlmostFinish;
};
#pragma pack(pop)


struct tagUpdateUserDailyTaskProgress
{
	int						nUserID;
	long long				llUserTaskID;
	int						nFinishValue;
	bool					bIsGettedAward;
};

struct tagDrawedLotteryInfo
{
	bool					bInit;
	int						nPresentID;
	int						nPresentType;
	int						nPresentCount;
	char					szDrawedPresentDescribe[128];
};

struct tagLobbyBroadcastMsgItem
{
	int						nMsgID;
	int						nMsgTypeID;
	int						nReserve_1;
	int						nReserve_2;
	int						nReserve_3;
	char					szMsgContext[512];
};

//�走��������ؽṹ��
struct tagMatchAwardInfo
{
	//char	awardType;
	std::string	awardDesc;
	//std::string	awardId;
	//std::string	awardReserve;
};

struct tagMatchSimpleInfo
{
	long long	id;
	std::string	name;
	int			userCount;
	tagMatchAwardInfo firstAward;
	int			paramA;
	int			paramC;
	int			sortId;
};

struct tagUserMatchInfo
{
	long long	id;
	int			score;
	int			rank;
};

struct tagEnterMatchFailed
{
	long long	id;
	int			iGameId;
	int			iServerId;
};

struct tagSignUpMatchFailed
{
	int			iGameId;
	int			iServerId;
};

struct tagMatchSimpleInfoUpdate
{
	long long oldId;
	long long newId;
};

struct tagCurrMatchDetailInfo
{
	tagCurrMatchDetailInfo()
	{
		Clear();
	}

	long long	   matchId;	
	BasicMatchInfo basicInfo;
	MatchStateInfo stateInfo;
	long long	   realBeginTime;

	bool		   hasSignedUp; //�Ƿ��ѱ���������
	string		   matchName; //�ñ�������

	void Clear()
	{
		matchId = 0;
		realBeginTime = 0;
		hasSignedUp = false;
		matchName = "";

		basicInfo.targetScore = 0;
		basicInfo.totalRound = 0;
		basicInfo.matchMode = 0;
		basicInfo.game = 0;
		basicInfo.gameMode = 0;
		basicInfo.gameRoom = 0;
		basicInfo.paramA = 0;
		basicInfo.paramC = 0;
		basicInfo.sortId = 0;

		basicInfo.begintime.clear();
		basicInfo.matchReqs.clear();
		basicInfo.servers.clear();

		stateInfo.curScore = 0;
		stateInfo.curRound = 0;
		stateInfo.userCount = 0;
	}
};
#endif //__CLIENT_DATA_DEF_H__