#include "ClientData.h"
#include "cocos2d.h"
#include "DataBase64.h"
#include "GameMessage.h"
#include "Knickknacks.h"
//#include "GuanDan/GuanDanData.h"

USING_NS_CC;

string randomBuffer[36] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
	"n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

ClientData::ClientData()
{
	m_tableId=0;
	m_tablename="";
	m_deviceId = "";
	m_matchgame_id=0;
	isKey_back=false;
	isKickout=false;
	m_u64UserId = 0;       
	m_u64Score = 0;        
	m_u64Coin2Award = 0;   
	m_u64CompeteScore = 0; 
	m_u64AwardTicketNum = 0;   
	m_cGender = '0';
	m_uSitDownErrorCode = 0;
	m_u32CreatePRoomErrorCode = 0;
	m_kSelfHeadImagePath = "";
	m_i32LastLoginError = -1;
	m_i32LastRoomLoginError = -1;
	m_i32LastRoomLoginErrorServerID = -1;
	m_i32LastRoomLoginErrorGameID = -1;
	m_bIsQuitGameClientAlert = false;
	m_needSendCaCardNo = false;
	m_bIsNeedNewPlayerGuide = false;
	m_i32PhoneRechargePoint = 0;	
	memset (m_szLastRoomLoginErrorGameName, 0, sizeof (m_szLastRoomLoginErrorGameName));

	m_i32PRoomBaseMultiple = 50;	
	m_i32PRoomBaseAnte = 100;	
	m_i32PRoomMaxAnte = 100000;

	m_bIsDailyTaskDataChange = false;
	

	m_firstBankScore = false;

	m_bankScore = 0;

	m_i32LotteryCount = 0;

	m_u32HuaFeiPoint = 0;

	m_i32SysBroadcastMsgID = 0;

	m_cGameStatus = false;

	is_fastgame = false;

	m_isTuanTuan=false;

	m_isGuanDanGame=false;

	is_agree_basepoint = true;

	join_table_id  = 0;

	join_table_point = 0;

	join_pwtable_num = 0;

	m_bHasEnoughScroce = true;

	m_roomindex = 0;

	m_bLoginAgain = false;

	m_iUnReceivedPkg = 0;

	m_lobbyAlwaysConnectPort = 0;

	m_labaCounts = 0;
	m_isFirstCharge = false;

	m_accountLoginNotSelf = false;

	m_isForeground = true;

	m_netWorkLinkState = -1;

	m_netWorkIsUnlink = false;

	m_needSendLoginMessage = false;

	m_needReSaveUpdateLink = false;

	m_isChannelPackage = false;
	m_channelId = "";

	m_HongbaoCounts = 0;
	m_caiPiaoCount = 0; 

	m_SlotCounts =0;
	m_slotindex =0;
	m_canshowprizelayer =true;

	m_gameAvaliableIp = "";
	m_gameAvaliablePort = 0;
	//掼蛋比赛场
	m_i32MatchRspError=0;
	m_bIsLoginMatchSuc_GD=false;
	//掼蛋私人场
	IsNeedPassWord=0;

	ODEZeroMemory(m_szUserName, sizeof(m_szUserName));
	ODEZeroMemory(m_szPassword, sizeof(m_szPassword));

	ODEZeroMemory(m_lobbyAlwaysConnectIP, sizeof(m_lobbyAlwaysConnectIP));

	ODEZeroMemory(m_szGameTip, sizeof(m_szGameTip));

	ODEZeroMemory(m_lobbyDeviceId, sizeof(m_lobbyDeviceId));

	ODEZeroMemory(&m_UserSerialLoginTaskInfo, sizeof(m_UserSerialLoginTaskInfo));

	ODEZeroMemory(&m_LobbyBankClientAuthenReq, sizeof(m_LobbyBankClientAuthenReq));
	ODEZeroMemory(&m_LobbyBankInfoRsp, sizeof(m_LobbyBankInfoRsp));

	ODEZeroMemory(m_channelDownloadCurrentVersion, sizeof(m_channelDownloadCurrentVersion));
	ODEZeroMemory(m_channelDownloadLimitVersion, sizeof(m_channelDownloadLimitVersion));
	ODEZeroMemory(&m_oEnterMatchFailedInfo, sizeof(m_oEnterMatchFailedInfo));
	
	m_vecAllMatchSimpleInfos_GD.clear();
	m_vecPartInMatchInfos_GD.clear();
	m_currMatchDetailInfo_GD.Clear();

	memset (m_GoldCardAvaliableTime, 0, sizeof (m_GoldCardAvaliableTime));

	m_LastExitNotNormalGameID = 0;
	m_LastExitNotNormalServerID = 0;
	m_LastExitNotNormalScore = 0;
	m_LastGameID = 0;
	m_LastServerID = 0;

	m_CurrentMedalsId = -1;
	m_CurrentMedalsRetCode = 0;
	m_isGuideMode = false;
	m_guanDanGuideRewardCode = 0; 
	m_guanDanGuideRewardCoin = 0;
	m_isInGuanDanGameScene = false;

	m_settingDownloadSkinContentID = 0;
	ODEZeroMemory(m_settingDownloadSkinPath, sizeof(m_settingDownloadSkinPath));
	ODEZeroMemory(m_guanDanGetAwardString, sizeof(m_guanDanGetAwardString));

	//GuanDanData::GetSingletonPtr()->init();

#ifdef SCORE_EXCHANGE_GIFT_MACRO

	memset(&m_gqActivityBaseInfoRsp, 0, sizeof(m_gqActivityBaseInfoRsp));
	m_needUpdateScoreExchangeBaseData = false;
	memset(&m_gqActivityGetAwardRsp, 0, sizeof(m_gqActivityGetAwardRsp));
	m_needUpdateScoreExchangeScoreData = false;

	m_isOpenScoreExchangeGift = false;

#endif // SCORE_EXCHANGE_GIFT_MACRO

	m_roomPeopleCountInfo = CCDictionary::create();
	m_roomPeopleCountInfo->retain();

	m_mapAllGuanDanAwardInfo.clear();
	m_mapGuanDanMatchRankList.clear();
	m_GuanDanranker_info_list.clear();
}

ClientData::~ClientData()
{
	ClearCustomTableInfo();
	ClearGameMessageBuffer();
	ClearGameInstantMessageBuffer();
	ClearDelayMessageBuffer();
	ClearLobbyMessageBuffer();
	ClearUserDailyTaskInfo();

	m_roomPeopleCountInfo->removeAllObjects();
	m_roomPeopleCountInfo->release();
}

void ClientData::SetUserID( ODEUInt64 u64UserId )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_u64UserId = u64UserId;
}

ODEUInt64 ClientData::GetUserID()
{
	return m_u64UserId;
}

void ClientData::SetUserScore( ODEUInt64 u64Score )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_u64Score = u64Score;
}

ODEUInt64 ClientData::GetUserScore()
{
	return m_u64Score;
}

void ClientData::SetUserCoin2AwardNum( ODEUInt64 u64Coin2Award )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_u64Coin2Award = u64Coin2Award;
}

ODEUInt64 ClientData::GetUserCoin2AwardNum()
{
	return m_u64Coin2Award;
}

void ClientData::SetUserCompeteScore( ODEUInt64 u64CompeteScore )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_u64CompeteScore = u64CompeteScore;
}

ODEUInt64 ClientData::GetUserCompeteScore()
{
	return m_u64CompeteScore;
}

void ClientData::SetUserAwardTicketNum( ODEUInt64 u64AwardScore )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_u64AwardTicketNum = u64AwardScore;
}

ODEUInt64 ClientData::GetUserAwardTicketNum()
{
	return m_u64AwardTicketNum;
}

void ClientData::SetUserGender( ODEChar8 cGender )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_cGender = cGender;
}

ODEChar8 ClientData::GetUserGender()
{
	return m_cGender;
}
void ClientData::SetUserHeadIndex( ODEUInt64 u64UserHeadIndex )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_HeadImageIndex = u64UserHeadIndex;
}
ODEUInt64 ClientData::GetUserHeadIndex()
{
	return m_HeadImageIndex;
}

void ClientData::SetUserBuyHeadIndex( ODEUInt64 u64UserBuyHeadIndex )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_BuyHeadIndex = u64UserBuyHeadIndex;
}

ODEUInt64 ClientData::GetUserBuyHeadIndex()
{
	return m_BuyHeadIndex;
}

void ClientData::SetBankScore (long long score)
{
	if (m_firstBankScore)
	{
		m_firstBankScore = false;
		m_bankScore = score;
	}
	else
	{
		m_LobbyBankInfoRsp.llBankCoin = score;
	}
}

long long ClientData::GetBankScore ()
{
	return m_bankScore;
}

void ClientData::SetUserName(const ODEChar8* szUserName)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	strcpy(m_szUserName, szUserName);
}

ODEChar8* ClientData::GetUserName(bool bNickname/*=false*/) 
{ 
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (bNickname && m_bIsSetNickname)
	{
		return m_szNickname;
	}

	return m_szUserName; 
}


void ClientData::SetUserPassword(const ODEChar8* szPassword)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	strcpy(m_szPassword, szPassword);
}

void ClientData::SetUserPhoneRechargePoint(ODEInt32 i32Point)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_i32PhoneRechargePoint = i32Point;
}

ODEInt32 ClientData::GetUserPhoneRechargePoint() 
{
	return m_i32PhoneRechargePoint;
}

void ClientData::SetSitDownErrorCode(ODEUInt32 cbErrorCode)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_uSitDownErrorCode = cbErrorCode;
}

void ClientData::SetPrivateRoomBaseMultiple(ODEInt32 nBaseMultiple)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_i32PRoomBaseMultiple = nBaseMultiple;
}

ODEInt32 ClientData::GetPrivateRoomBaseMultiple() 
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (m_i32PRoomBaseMultiple <= 0) return 1;
	return m_i32PRoomBaseMultiple;
}

void ClientData::SetPrivateRoomBaseAnte(ODEInt32 nBaseAnte)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_i32PRoomBaseAnte = nBaseAnte;
}

void ClientData::SetPrivateRoomMaxAnte(ODEInt32 nMaxAnte)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_i32PRoomMaxAnte = nMaxAnte;
}

void ClientData::SetCreatePrivateRoomErrorCode(ODEUInt32 cbErrorCode)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_u32CreatePRoomErrorCode = cbErrorCode;
}

void ClientData::ClearCustomTableInfo()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (ODEList<tagCustomTableInfo*>::iterator it=m_listCustomTableInfo.Begin(); it!=m_listCustomTableInfo.End(); it++)
	{
		ODE_SAFE_DELETE(*it);
	}
	m_listCustomTableInfo.Clear();
}

void ClientData::SetLastLoginError( ODEInt32 i32ErrorCode )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_i32LastLoginError = i32ErrorCode;
}

ODEInt32 ClientData::GetLastLoginError()
{
	return m_i32LastLoginError;
}

void ClientData::SetLastRoomLoginError( ODEInt32 i32ErrorCode )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_i32LastRoomLoginError = i32ErrorCode;
}

ODEInt32 ClientData::GetLastRoomLoginError()
{
	return m_i32LastRoomLoginError;
}

void ClientData::SetLastRoomLoginErrorServerId( ODEInt32 i32ServerId )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_i32LastRoomLoginErrorServerID = i32ServerId;
}

ODEInt32 ClientData::GetLastRoomLoginErrorServerId()
{
	return m_i32LastRoomLoginErrorServerID;
}

void ClientData::SerLastRoomLoginErrorGameId( ODEInt32 i32GameId )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_i32LastRoomLoginErrorGameID = i32GameId;
}

void ClientData::SetLastRoomLoginErrorGameName (const char * name)
{
	ODESprintf (m_szLastRoomLoginErrorGameName, 40, "%s", name);
}

char * ClientData::GetLastRoomLoginErrorGameName ()
{
	return m_szLastRoomLoginErrorGameName;
}


ODEInt32 ClientData::GetLastRoomLgoinErrorGameId()
{
	return m_i32LastRoomLoginErrorGameID;
}

void ClientData::SetUserSerialLoginTaskInfo(tagUserSerialLoginTaskInfo *pLoginTaskInfo)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	ODEMemoryCopy(&m_UserSerialLoginTaskInfo, pLoginTaskInfo, sizeof(m_UserSerialLoginTaskInfo));
}

void ClientData::ClearGameMessageBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (ODEList<tagGameMessageBuffer*>::iterator it=m_GameMessageBuffer.Begin(); it!=m_GameMessageBuffer.End(); it++)
	{
		ODE_SAFE_DELETE(*it);
	}
	m_GameMessageBuffer.Clear();
}

// 游戏消息缓存
void ClientData::AddGameMessageToBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	tagGameMessageBuffer *pBuffer = new tagGameMessageBuffer;
	if (pBuffer)
	{
		pBuffer->u32GameMessageID = nMsgID;
		pBuffer->u32DataSize = length;
		ODEMemoryCopy(pBuffer->GameMessageData, buffer, length);

		m_GameMessageBuffer.PushBack(pBuffer);
	}
	else
	{
		__CCLOGWITHFUNCTION("!!!!!!!!!!!!!! ADD MESSAGE ERROR! msgId: %x", nMsgID);
	}
}

void ClientData::RemoveFrontGameMessageInBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (m_GameMessageBuffer.Size()<=0) return;

	ODEList<tagGameMessageBuffer*>::iterator it=m_GameMessageBuffer.Begin();

	tagGameMessageBuffer *pGameMessage = *it;

	ODE_SAFE_DELETE(pGameMessage);
	m_GameMessageBuffer.PopFront();

	//if (m_GameMessageBuffer.Size() > 0)
	//{
	//	ODEList<tagGameMessageBuffer*>::iterator it=m_GameMessageBuffer.Begin();

	//	while (it != m_GameMessageBuffer.End())
	//	{
	//		__CCLOGWITHFUNCTION("*************************unHandled message %x", (*it)->u32GameMessageID);

	//		it ++;
	//	}
	//}
}

void ClientData::RemoveFrontOnlyGameMessageInBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (m_OnlyGameMessageBuffer.Size()<=0) return;

	ODEList<tagGameMessageBuffer*>::iterator it=m_OnlyGameMessageBuffer.Begin();

	tagGameMessageBuffer *pGameMessage = *it;

	ODE_SAFE_DELETE(pGameMessage);
	m_OnlyGameMessageBuffer.PopFront();

	if (m_GameMessageBuffer.Size() > 0)
	{
		ODEList<tagGameMessageBuffer*>::iterator it=m_OnlyGameMessageBuffer.Begin();

		while (it != m_OnlyGameMessageBuffer.End())
		{
			__CCLOGWITHFUNCTION("*************************unHandled message %x", (*it)->u32GameMessageID);

			it ++;
		}
	}
}

tagGameMessageBuffer* ClientData::GetFrontGameMessageInBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (m_GameMessageBuffer.Size()<=0) return NULL;

	ODEList<tagGameMessageBuffer*>::iterator it=m_GameMessageBuffer.Begin();

	return (*it);
}

tagGameMessageBuffer* ClientData::GetFrontOnlyGameMessageInBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (m_OnlyGameMessageBuffer.Size()<=0) return NULL;

	ODEList<tagGameMessageBuffer*>::iterator it=m_OnlyGameMessageBuffer.Begin();

	return (*it);
}

void ClientData::ClearGameInstantMessageBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (ODEList<tagGameMessageBuffer*>::iterator it=m_GameInstantMessageBuffer.Begin(); it!=m_GameInstantMessageBuffer.End(); it++)
	{
		ODE_SAFE_DELETE(*it);
	}
	m_GameInstantMessageBuffer.Clear();
}

void ClientData::AddGameInstantMessageToBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	tagGameMessageBuffer *pBuffer = new tagGameMessageBuffer;
	if (pBuffer)
	{
		pBuffer->u32GameMessageID = nMsgID;
		pBuffer->u32DataSize = length;
		ODEMemoryCopy(pBuffer->GameMessageData, buffer, length);

		m_GameInstantMessageBuffer.PushBack(pBuffer);
	}
}

void ClientData::RemoveFrontGameInstantMessageInBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (m_GameInstantMessageBuffer.Size()<=0) return;

	ODEList<tagGameMessageBuffer*>::iterator it=m_GameInstantMessageBuffer.Begin();

	tagGameMessageBuffer *pGameMessage = *it;

	ODE_SAFE_DELETE(pGameMessage);
	m_GameInstantMessageBuffer.PopFront();
}

tagGameMessageBuffer* ClientData::GetFrontGameInstantMessageInBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (m_GameInstantMessageBuffer.Size()<=0) return NULL;

	ODEList<tagGameMessageBuffer*>::iterator it=m_GameInstantMessageBuffer.Begin();

	return (*it);
}

void ClientData::ClearDelayMessageBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (ODEList<tagDelayMessageBuffer*>::iterator it=m_DelayMessageBuffer.Begin(); it!=m_DelayMessageBuffer.End(); it++)
	{
		ODE_SAFE_DELETE(*it);
	}
	m_DelayMessageBuffer.Clear();
}

void ClientData::AddMsgToDelayMessageBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length, ODEUInt32 u32DelayTime/*=0*/)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	tagDelayMessageBuffer *pBuffer = new tagDelayMessageBuffer;
	if (pBuffer)
	{
		pBuffer->u32GameMessageID = nMsgID;
		pBuffer->u32DataSize = length;
		pBuffer->u32TimeDelayTo = time(NULL)+u32DelayTime;
		ODEMemoryCopy(pBuffer->GameMessageData, buffer, length);

		m_DelayMessageBuffer.PushBack(pBuffer);
	}
}

void ClientData::ClearLobbyMessageBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (ODEList<tagGameMessageBuffer*>::iterator it=m_LobbyMessageBuffer.Begin(); it!=m_LobbyMessageBuffer.End(); it++)
	{
		ODE_SAFE_DELETE(*it);
	}
	m_LobbyMessageBuffer.Clear();
}

void ClientData::AddMsgToLobbyMessageBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	tagGameMessageBuffer *pBuffer = new tagGameMessageBuffer;
	if (pBuffer)
	{
		pBuffer->u32GameMessageID = nMsgID;
		pBuffer->u32DataSize = length;
		ODEMemoryCopy(pBuffer->GameMessageData, buffer, length);

		m_LobbyMessageBuffer.PushBack(pBuffer);
	}
}

void ClientData::AddMsgToOnlyGameMessageBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	tagGameMessageBuffer *pBuffer = new tagGameMessageBuffer;
	if (pBuffer)
	{
		pBuffer->u32GameMessageID = nMsgID;
		pBuffer->u32DataSize = length;
		ODEMemoryCopy(pBuffer->GameMessageData, buffer, length);

		m_OnlyGameMessageBuffer.PushBack(pBuffer);
	}
}

void ClientData::ClearOnlyGameMessageBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (ODEList<tagGameMessageBuffer*>::iterator it=m_OnlyGameMessageBuffer.Begin(); it!=m_OnlyGameMessageBuffer.End(); it++)
	{
		ODE_SAFE_DELETE(*it);
	}
	m_OnlyGameMessageBuffer.Clear();
}

void ClientData::ClearUserDailyTaskInfo(bool bClearFinish/*=true*/)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (ODEList<tagUserDailyTaskInfo*>::iterator it=m_listUserDailyTaskDoing.Begin(); it!=m_listUserDailyTaskDoing.End(); it++)
	{
		ODE_SAFE_DELETE(*it);
	}
	m_listUserDailyTaskDoing.Clear();

	if (false == bClearFinish) return;
	for (ODEList<tagUserDailyTaskInfo*>::iterator it=m_listUserDailyTaskFinished.Begin(); it!=m_listUserDailyTaskFinished.End(); it++)
	{
		ODE_SAFE_DELETE(*it);
	}
	m_listUserDailyTaskFinished.Clear();
}

void ClientData::SetDailyTaskDataChangeMark(bool bChange)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_bIsDailyTaskDataChange = bChange;
}

void ClientData::SetUserDailyTaskInfo(tagUserDailyTaskInfo *pUserDailyTaskInfo)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	bool bFind = false;
	for (ODEList<tagUserDailyTaskInfo*>::iterator it=m_listUserDailyTaskDoing.Begin(); it!=m_listUserDailyTaskDoing.End(); it++)
	{
		if ((*it)->nUserID == pUserDailyTaskInfo->nUserID &&
			(*it)->llUserTaskID == pUserDailyTaskInfo->llUserTaskID)
		{
			ODEMemoryCopy(*it, pUserDailyTaskInfo, sizeof(tagUserDailyTaskInfo));

			if ((*it)->nFinishValue == 0) (*it)->bIsNewDailyTask = true;
			else (*it)->bIsNewDailyTask = false;

			bFind = true;
			break;
		}
	}

	if (false == bFind)
	{
		tagUserDailyTaskInfo *pTmp = new tagUserDailyTaskInfo;
		ODEMemoryCopy(pTmp, pUserDailyTaskInfo, sizeof(tagUserDailyTaskInfo));

		if (pTmp->nFinishValue == 0)
		{
			pTmp->bIsNewDailyTask = true;
		}
		else
		{
			pTmp->bIsNewDailyTask = false;
		}

		m_listUserDailyTaskDoing.PushBack(pTmp);
	}

	m_bIsDailyTaskDataChange = true;
}

bool ClientData::UpdateUserDailyTaskInfo(tagUpdateUserDailyTaskProgress *pTaskProgress)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	bool bUpdate = false;
	for (ODEList<tagUserDailyTaskInfo*>::iterator it=m_listUserDailyTaskDoing.Begin(); it!=m_listUserDailyTaskDoing.End(); it++)
	{
		if ((*it)->nUserID == pTaskProgress->nUserID &&
			(*it)->llUserTaskID == pTaskProgress->llUserTaskID)
		{
			(*it)->nFinishValue = pTaskProgress->nFinishValue;
			(*it)->bIsGettedAward = pTaskProgress->bIsGettedAward;
			
			(*it)->bIsNewDailyTask = false;
			
			if ((*it)->nFinishValue >= (*it)->nTargetValue && true == (*it)->bIsGettedAward)
			{
				tagUserDailyTaskInfo *pTaskInfo = *it;
				m_listUserDailyTaskDoing.Erase(it);
				m_listUserDailyTaskFinished.PushFront(pTaskInfo);
			}

			bUpdate = true;
			break;
		}
	}

	ODE_ASSERT(bUpdate);
	if (bUpdate) m_bIsDailyTaskDataChange = true;

	return bUpdate;
}

tagUserDailyTaskInfo* ClientData::GetUserDailyTaskInfo(ODEInt64 i64UserTaskID)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	for (ODEList<tagUserDailyTaskInfo*>::iterator it=m_listUserDailyTaskDoing.Begin(); it!=m_listUserDailyTaskDoing.End(); it++)
	{
		if ((*it)->llUserTaskID == i64UserTaskID)
		{
			return *it;
		}
	}

	for (ODEList<tagUserDailyTaskInfo*>::iterator it=m_listUserDailyTaskFinished.Begin(); it!=m_listUserDailyTaskFinished.End(); it++)
	{
		if ((*it)->llUserTaskID == i64UserTaskID)
		{
			return *it;
		}
	}

	return NULL;
}

void ClientData::setLastLoginIpAndPort(const ODEChar8 * ip, ODEInt32 port, ODEInt32 roomID)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_lastLoginIp = ip;
	m_lastLoginPort = port;
	m_lastLoginRoomID = roomID;
}

ODEChar8* ClientData::getLastLoginIp()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	return m_lastLoginIp.GetString();
}

ODEInt32 ClientData::getLastLoginPort()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	return m_lastLoginPort;
}

ODEInt32 ClientData::getLastLoginRoomID()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	return m_lastLoginRoomID;
}

void ClientData::ClearGameMsgBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	ClearGameMessageBuffer();
	ClearGameInstantMessageBuffer();
	ClearDelayMessageBuffer();
}

void ClientData::SetLotteryCount( ODEInt32 i32Count )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_CMD_LOTTERYCOUNT_CHANGED, (CCObject*)i32Count);
	m_i32LotteryCount = i32Count;
}

void ClientData::SetSysBroadcastMsgID(ODEInt32 i32MsgID)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	m_i32SysBroadcastMsgID = i32MsgID;
}
//类牛牛清空桌子数据
void ClientData::initTablePlayerBaseData()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	while (m_tablePlayerBaseInfo.size() > 0)
	{
		list<LocalTablePlayerInfoDef*>::iterator it = m_tablePlayerBaseInfo.begin();
		delete *it;
		*it = NULL;
		m_tablePlayerBaseInfo.erase(m_tablePlayerBaseInfo.begin());
	}
	while (m_tablePlayerOldBaseInfo.size() > 0)
	{
		LocalTbaleOldPlayerInfoDef* firstData = m_tablePlayerOldBaseInfo.at(0);
		delete firstData;
		firstData = NULL;
		m_tablePlayerOldBaseInfo.erase(m_tablePlayerOldBaseInfo.begin());
	}
}

//类麻将 清空桌子数据

void ClientData::ClearPUSRoomTableInfo()
{
	std::vector<tagPUSTableInfo*>::iterator it =g_pkGuanDanGamePlayerData->m_vPUSTableInfo.begin();
	for (; it!=g_pkGuanDanGamePlayerData->m_vPUSTableInfo.end(); it++)
	{
		tagPUSTableInfo *pTableInfo = *it;
		memset(pTableInfo, 0, sizeof(tagPUSTableInfo));
	}


}

void ClientData::addTablePlayerBaseData(int iUserId, unsigned char gender, unsigned short tableIndex, unsigned short tableNumExtra, char userStatus, int index)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	bool existed = false;

	for (list<LocalTablePlayerInfoDef*>::iterator it = m_tablePlayerBaseInfo.begin(); it != m_tablePlayerBaseInfo.end(); it++)
	{
		if ((*it)->iUserID == iUserId)
		{
			existed = true;
			break;
		}
	}
	if (!existed)
	{
		LocalTablePlayerInfoDef* localData = new LocalTablePlayerInfoDef;
		localData->cGender = gender;
		localData->iCurUserStatus = userStatus;
		localData->iUserID = iUserId;
		localData->tableIndex = tableIndex;
		localData->usTableNumExtra = tableNumExtra;
		localData->headindex = index;

		CCLog("%s id[%d]gender[%d]localData[%d]tableIndex[%d]usTableNumExtra[%d]", __FUNCTION__, localData->iUserID, localData->cGender, localData->iCurUserStatus, localData->tableIndex, localData->usTableNumExtra);
		m_tablePlayerBaseInfo.push_back(localData);
	}

	CCLog("%s m_tablePlayerBaseInfo::count = [%d]", __FUNCTION__, m_tablePlayerBaseInfo.size());
}

void ClientData::addUserHeadIndexInfo(int userid, int index)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	bool existed = false;
	for (list<UserHeadInfo*>::iterator it = m_userheadindexinfo.begin(); it != m_userheadindexinfo.end(); it++)
	{
		if ((*it)->iUserID == userid)
		{
			(*it)->iUserHead = index;
			existed  = true;
			return ;
		}
	}
	if (!existed)
	{
		UserHeadInfo* headinfo = new UserHeadInfo;
		headinfo->iUserID = userid;
		headinfo->iUserHead = index;
		m_userheadindexinfo.push_back(headinfo);
	}
}

void ClientData::addNewUserHeadIndexInfo(int userid, int index)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	bool existed = false;
	for (list<UserHeadInfo*>::iterator it = m_userheadindexinfo.begin(); it != m_userheadindexinfo.end(); it++)
	{
		if ((*it)->iUserID == userid)
		{
			(*it)->iUserHead = index;
			existed  = true;
			return ;
		}
	}

	if (!existed)
	{
		UserHeadInfo* headinfo = new UserHeadInfo;
		headinfo->iUserID = userid;
		headinfo->iUserHead = index;
		m_userheadindexinfo.push_back(headinfo);
	}
}

UserHeadInfo* ClientData::GetUserHeadIndexInfo(int userId)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (list<UserHeadInfo*>::iterator it = m_userheadindexinfo.begin(); it != m_userheadindexinfo.end(); it++)
	{
		if (*it != NULL && (*it)->iUserID == userId)
		{
			return *it;
		}
	}
	return NULL;
}

void ClientData::RemoveUserHeadIndexInfo()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (list<UserHeadInfo*>::iterator it = m_userheadindexinfo.begin(); it != m_userheadindexinfo.end(); it++)
	{
		CC_SAFE_DELETE(*it);
		m_userheadindexinfo.erase(it);
		break;
	} 
}

void ClientData::deleteTabelPlayerBaseData(int userId)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	for (list<LocalTablePlayerInfoDef*>::iterator it = m_tablePlayerBaseInfo.begin(); it != m_tablePlayerBaseInfo.end(); it++)
	{
		if ((*it)->iUserID == userId)
		{
			if ((*it) != NULL)
			{
				delete (*it);
				*it = NULL;
			}

			m_tablePlayerBaseInfo.erase(it);
			break;
		}
	}
	CCLOG("%s m_tablePlayerBaseInfo::count = [%d]", __FUNCTION__, m_tablePlayerBaseInfo.size());
}

void ClientData::updateTablePlayerBaseData(int userId, unsigned short tableNum, unsigned short usTableNumExtra, char userStatus, int iHeadImgIndex)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	LocalTablePlayerInfoDef* pLocalPlayerData = getTablePlayerBaseData(userId);
	if (pLocalPlayerData)
	{
		pLocalPlayerData->tableIndex = tableNum;
		pLocalPlayerData->usTableNumExtra = usTableNumExtra;
		pLocalPlayerData->iCurUserStatus = userStatus;
		pLocalPlayerData->headindex = iHeadImgIndex;
		CCLOG("%s update player table base data with id[%d] success", __FUNCTION__, pLocalPlayerData->iUserID);
	}
	else
	{
		CCLOG("%s can`t find player with id[%d]", __FUNCTION__, userId);
	}
}

LocalTablePlayerInfoDef* ClientData::getTablePlayerBaseData(int userId)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (list<LocalTablePlayerInfoDef*>::iterator it = m_tablePlayerBaseInfo.begin(); it != m_tablePlayerBaseInfo.end(); it++)
	{
		if (*it != NULL && (*it)->iUserID == userId)
		{
			return *it;
		}
	}
	return NULL;
}

void ClientData::addTableOldPlayerData(int userId, unsigned short tableIndex, unsigned short tableNumExtra,int index)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	bool existed = false;

	for (int i(0); i < m_tablePlayerOldBaseInfo.size(); ++i)
	{
		LocalTbaleOldPlayerInfoDef * tempData = m_tablePlayerOldBaseInfo.at(i);
		if (tempData->iUserID == userId)
		{
			existed = true;
		}
	}
	if (!existed)
	{
		LocalTbaleOldPlayerInfoDef * localData = new LocalTbaleOldPlayerInfoDef;
		localData->iUserID = userId;
		localData->tableIndex = tableIndex;
		localData->usTableNumExtra = tableNumExtra;
		localData->headindex = index;

		m_tablePlayerOldBaseInfo.push_back(localData);
		CCLOG("%s userid: [%d], tableindex: [%d], extra: [%d] m_tablePlayerOldBaseInfo::count = [%d]", __FUNCTION__, localData->iUserID, localData->tableIndex, localData->usTableNumExtra, m_tablePlayerOldBaseInfo.size());
	}
	else
	{
		CCLOG("%s player is already in old player list", __FUNCTION__);
	}
}

void ClientData::deleteTableOldPlayerData(bool needClean /* = true */)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	if (m_tablePlayerOldBaseInfo.size() > 0)
	{
		LocalTbaleOldPlayerInfoDef* oldPlayerData = m_tablePlayerOldBaseInfo.at(0);
		if (oldPlayerData != NULL)
		{
			if (needClean)
			{
				delete oldPlayerData;
			}
			else
			{
				CCLOG("%s WARN -- needClean = FLASE", __FUNCTION__);
			}

			oldPlayerData = NULL;
		}
		m_tablePlayerOldBaseInfo.erase(m_tablePlayerOldBaseInfo.begin());
	}
	for (int i(0); i < m_tablePlayerOldBaseInfo.size(); ++i)
	{
		LocalTbaleOldPlayerInfoDef* data = m_tablePlayerOldBaseInfo.at(i);
		CCLOG("%s userId[%d] tableIndex[%d] pos[%d]", __FUNCTION__, data->iUserID, data->tableIndex, data->usTableNumExtra);
	}

	CCLOG("%s m_tablePlayerOldBaseInfo::count = [%d]", __FUNCTION__, m_tablePlayerOldBaseInfo.size());
}

LocalTbaleOldPlayerInfoDef* ClientData::getTableOldPlayerData()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	if (m_tablePlayerOldBaseInfo.size() > 0)
	{
		return m_tablePlayerOldBaseInfo.at(0);
	}
	return NULL;
}

int ClientData::getTableOldPlayerCount()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	return m_tablePlayerOldBaseInfo.size();
}

bool ClientData::getGameStatus()
{
	return m_cGameStatus;
}

void ClientData::setGameStatus( bool cStatus )
{
	m_cGameStatus = cStatus;
}

//设置是否快速游戏

bool ClientData::getFastGame()
{
	return is_fastgame;
}

void ClientData::setFastGame( bool is_fast )
{
	is_fastgame = is_fast;
}

void ClientData::SetNeedNewPlayerGuide(bool bNeed)
{
	m_bIsNeedNewPlayerGuide = bNeed;
}

bool ClientData::IsNeedNewPlayerGuide()
{
	return m_bIsNeedNewPlayerGuide;
}
//设置是否同意底注
bool ClientData::getAgreeBasePoint()
{
	return is_agree_basepoint;
}

void ClientData::setAgreeBasePoint( bool is_agree )
{
	is_agree_basepoint = is_agree;
}

int ClientData::getJoinTableId()
{
	return join_table_id;
}

void ClientData::setJoinTableId( int table_id )
{
	join_table_id = table_id;
}

int ClientData::getJoinTablePoint()
{
	return join_table_point;
}

void ClientData::setJoinTablePoint( int table_id )
{
	join_table_point = table_id;
}

//判断是不是有足够分数进入房间
bool ClientData::getEnoughScroce()
{
	return m_bHasEnoughScroce;
}

void ClientData::setEnoughScroce( bool score_can )
{
	m_bHasEnoughScroce = score_can;
}


//得到当前的roomindex

ODEInt32 ClientData::getRoomIndex()
{
	return m_roomindex;
}

void ClientData::setRoomIndex( ODEInt32 room_index )
{
	m_roomindex = room_index;
}

void ClientData::setLoginAgain( bool bAgain )
{
	m_bLoginAgain = bAgain;
}

bool ClientData::isLoginAgain()
{
	return m_bLoginAgain;
}

void ClientData::checkDeviceCode()
{
	int haveDeviceCode = CCUserDefault::sharedUserDefault()->getIntegerForKey("localsb");

	if (haveDeviceCode == 0)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("localsb", 1);
		CCUserDefault::sharedUserDefault()->flush();

		srand(time(NULL));
		string localCode = "";
		int needCount = 20;
		while (needCount >= 0) {
			int index = CCRANDOM_0_1() * 36;
			localCode.append(randomBuffer[index]);

			needCount --;
		}
		SaveData(localCode);
		//CCLog("%s randomCode[%s]", __FUNCTION__, localCode.c_str());

		CCUserDefault::sharedUserDefault()->setStringForKey("localsbsingledata", localCode);
		CCUserDefault::sharedUserDefault()->flush();
	}

	m_deviceCode = CCUserDefault::sharedUserDefault()->getStringForKey("localsbsingledata");

	ParseData(m_deviceCode);
}

string ClientData::getNewDeviceCode()
{
	return m_deviceCode;
}



void ClientData::getLocalPayEventData()
{
	//获取支付宝统计数据
	parsePayEventCount(PAY_TAOBAO);

	g_pkGuanDanGame->reqSendPayEventToServer(PAY_TAOBAO);
}

void ClientData::clearPayEventCount(int payType)
{
	m_payEventCount[payType] = 0;
	m_paySuccessCount[payType] = 0;
	m_payFailedCount[payType] = 0;
	m_payReturnCount[payType] = 0;
	m_payNetErrorCount[payType] = 0;

	char keyBuffer[30] = {0};
	sprintf(keyBuffer, "paytype_%d_%lld", payType, GetUserID());

	CCUserDefault::sharedUserDefault()->setStringForKey(keyBuffer, "");
	CCUserDefault::sharedUserDefault()->flush();
}

void ClientData::addPayEventCount(int payType)
{
	m_payEventCount[payType]++;

	savePayEventCount(payType);
}

int ClientData::getPayEventCount(int payType)
{
	return m_payEventCount[payType];
}

void ClientData::addPaySuccessCount(int payType)
{
	m_paySuccessCount[payType]++;

	savePayEventCount(payType);
}

int ClientData::getPaySuccessCount(int payType)
{
	return m_paySuccessCount[payType];
}

void ClientData::addPayFailedCount(int payType)
{
	m_payFailedCount[payType]++;

	savePayEventCount(payType);
}

int ClientData::getPayFailedCount(int payType)
{
	return m_payFailedCount[payType];
}

void ClientData::addPayReturnCount(int payType)
{
	m_payReturnCount[payType]++;

	savePayEventCount(payType);
}

int ClientData::getPayReturnCount(int payType)
{
	return m_payReturnCount[payType];
}

void ClientData::addPayNetErrorCount(int payType)
{
	m_payNetErrorCount[payType]++;

	savePayEventCount(payType);
}

int ClientData::getPayNetErrorCount(int payType)
{
	return m_payNetErrorCount[payType];
}

void ClientData::savePayEventCount(int payType)
{
	char keyBuffer[30] = {0};
	sprintf(keyBuffer, "paytype_%d_%lld", payType, GetUserID());
	char valueBuffer[100] = {0};
	sprintf(valueBuffer, "%d;%d;%d;%d;%d;", m_payEventCount[payType], m_paySuccessCount[payType], m_payFailedCount[payType], m_payReturnCount[payType], m_payNetErrorCount[payType]);

	string valueStr = valueBuffer;
	SaveData(valueStr);
	CCUserDefault::sharedUserDefault()->setStringForKey(keyBuffer, valueStr);
	CCUserDefault::sharedUserDefault()->flush();
}

void ClientData::parsePayEventCount(int payType)
{
	char keyBuffer[30] = {0};
	sprintf(keyBuffer, "paytype_%d_%lld", payType, GetUserID());

	string valueStr = CCUserDefault::sharedUserDefault()->getStringForKey(keyBuffer, "");

	m_payEventCount[payType] = 0;
	m_paySuccessCount[payType] = 0;
	m_payFailedCount[payType] = 0;
	m_payReturnCount[payType] = 0;
	m_payNetErrorCount[payType] = 0;

	if (strcmp(valueStr.c_str(), "") != 0)
	{
		ParseData(valueStr);

		int currIndex = 0;
		int lastTagIndex = 0;	
	
		for (int i(0); i < valueStr.length(); ++ i)
		{
			if (valueStr.at(i) == ';')
			{
				if (currIndex == 0)
				{
					m_payEventCount[payType] = atoi(valueStr.substr(lastTagIndex, i).c_str());
				}
				else if (currIndex == 1)
				{
					m_paySuccessCount[payType] = atoi(valueStr.substr(lastTagIndex, i).c_str());
					
				}
				else if (currIndex == 2)
				{
					m_payFailedCount[payType] = atoi(valueStr.substr(lastTagIndex, i).c_str());
				}
				else if (currIndex == 3)
				{
					m_payReturnCount[payType] = atoi(valueStr.substr(lastTagIndex, i).c_str());
				}
				else if (currIndex == 4)
				{
					m_payNetErrorCount[payType] = atoi(valueStr.substr(lastTagIndex, i).c_str());
				}
				else
				{
					break;
				}

				currIndex ++;
				lastTagIndex = i + 1;
			}
		}
	}

}

void ClientData::SetNicknameMark(bool bIsSet)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_bIsSetNickname = bIsSet;
}

void ClientData::SetNickname(const ODEChar8* szNickname)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	strcpy(m_szNickname, szNickname);
}

void ClientData::SetLobbyPasspodVerifyErrorData(LobbyPasspodVerifyErrorRsp *pVerifyError)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	memcpy(&m_LobyPasspodVerifyError, pVerifyError, sizeof(m_LobyPasspodVerifyError));
}


void ClientData::SetAnniversarySendTimes (int times)
{
	m_AnniversarySendTimes = times;
}

int ClientData::GetAnniversarySendTimes ()
{
	return m_AnniversarySendTimes;
}

void ClientData::SetGoldCardAvaliableTime (char * timeStr)
{
	strcpy (m_GoldCardAvaliableTime, timeStr);
}

char * ClientData::GetGoldCardAvaliableTime ()
{
	return m_GoldCardAvaliableTime;
}




int ClientData::getJoinPwTableNum()
{
	return join_pwtable_num;
}

void ClientData::setJoinPwTableNum( int table_num )
{
	join_pwtable_num = table_num;
}

void ClientData::updatePeopleCountWithRoomID(int roomID, int peopleCount)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_roomPeopleCountInfo->setObject(CCInteger::create(peopleCount), roomID);
}

int ClientData::getPoepleCountWithRoomId(int roomID)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	CCInteger* serverId = (CCInteger*)m_roomPeopleCountInfo->objectForKey(roomID);
	if (serverId != NULL)
	{
		return serverId->getValue();
	}
	else
	{
		return 0;
	}
}

void ClientData::addNewBroadcastMsg(GameBroadcastMsg* msg)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	bool findMsg = false;
	for (ODEList<GameBroadcastMsg*>::iterator it = m_broadcastMsgList.Begin(); it != m_broadcastMsgList.End(); it++)
	{
		if ((*it)->msgId == msg->msgId)
		{
			(*it)->msgType = msg->msgType;
			memcpy((*it)->msgContent, msg->msgContent, sizeof((*it)->msgContent));

			CC_SAFE_DELETE(msg);
			msg = NULL;

			findMsg = true;
			break;
		}
	}
	if (!findMsg)
	{
		CCLog("function[%s] line[%d] addNewBroadcastMsg[%d]", __FUNCTION__, __LINE__, msg->msgId);
		bool insertSuccess = false;
		for (ODEList<GameBroadcastMsg*>::iterator it = m_broadcastMsgList.Begin(); it != m_broadcastMsgList.End(); it++)
		{
			if (msg->msgType > (*it)->msgType)
			{
				if (it == m_broadcastMsgList.Begin())
				{
					m_broadcastMsgList.Insert(m_broadcastMsgList.Begin(), msg);
				}
				else
				{
					m_broadcastMsgList.Insert(--it, msg);
				}
				insertSuccess = true;
				break;
			}
		}
		if (!insertSuccess)
		{
			m_broadcastMsgList.PushBack(msg);
		}
	}

	CCLog("function[%s] line[%d] msgCount[%d]", __FUNCTION__, __LINE__, m_broadcastMsgList.Size());
	for (ODEList<GameBroadcastMsg*>::iterator it = m_broadcastMsgList.Begin(); it != m_broadcastMsgList.End(); it++)
	{
		CCLog("function[%s] line[%d] msgId[%d] msgType[%d] msgContent[%s]", __FUNCTION__, __LINE__, (*it)->msgId, (*it)->msgType, ODETools::GBKToUTF8((*it)->msgContent).c_str());
	}
}

void ClientData::deleteBroadcastMsg(int msgId)
{
	for (ODEList<GameBroadcastMsg*>::iterator it = m_broadcastMsgList.Begin(); it != m_broadcastMsgList.End(); it++)
	{
		if ((*it)->msgId == msgId)
		{
			CCLog("function[%s] line[%d] deleteBroadcastMsgId[%d] msgType[%d]", __FUNCTION__, __LINE__, msgId, (*it)->msgType);

			CC_SAFE_DELETE(*it);
			m_broadcastMsgList.Erase(it);
			break;
		} 
	}
}

GameBroadcastMsg* ClientData::getFistBroadcastMsg()
{
	GameBroadcastMsg* msg = *m_broadcastMsgList.Begin();

	m_broadcastMsgList.Erase(m_broadcastMsgList.Begin());
	m_broadcastMsgList.PushBack(msg);

	return msg;
}

int ClientData::getBroadcastMsgCount()
{
	return m_broadcastMsgList.Size();
}

void ClientData::addGameNewBroadcastMsg(GameBroadcastMsg* msg)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (!isInForeground())
	{
		//当程序进入后台的时候最多保留10条非系统公告
		if (m_broadcastGameMsgList.Size() > 10)
		{
			GameBroadcastMsg* msg = *m_broadcastGameMsgList.Begin();

			CC_SAFE_DELETE(msg);
			m_broadcastGameMsgList.Erase(m_broadcastGameMsgList.Begin());
		}
	}

	bool findMsg = false;
	for (ODEList<GameBroadcastMsg*>::iterator it = m_broadcastGameMsgList.Begin(); it != m_broadcastGameMsgList.End(); it++)
	{
		if ((*it)->msgId == msg->msgId)
		{
			(*it)->msgType = msg->msgType;
			memcpy((*it)->msgContent, msg->msgContent, sizeof((*it)->msgContent));

			CC_SAFE_DELETE(msg);
			msg = NULL;

			findMsg = true;
			break;
		}
	}
	if (!findMsg)
	{
		CCLog("function[%s] line[%d] addNewBroadcastMsg[%d]", __FUNCTION__, __LINE__, msg->msgId);
		bool insertSuccess = false;
		for (ODEList<GameBroadcastMsg*>::iterator it = m_broadcastGameMsgList.Begin(); it != m_broadcastGameMsgList.End(); it++)
		{
			if (msg->msgType > (*it)->msgType)
			{
				if (it == m_broadcastGameMsgList.Begin())
				{
					m_broadcastGameMsgList.Insert(m_broadcastGameMsgList.Begin(), msg);
				}
				else
				{
					m_broadcastGameMsgList.Insert(--it, msg);
				}
				insertSuccess = true;
				break;
			}
		}
		if (!insertSuccess)
		{
			m_broadcastGameMsgList.PushBack(msg);
		}
	}

	CCLog("function[%s] line[%d] msgCount[%d]", __FUNCTION__, __LINE__, m_broadcastGameMsgList.Size());
	for (ODEList<GameBroadcastMsg*>::iterator it = m_broadcastGameMsgList.Begin(); it != m_broadcastGameMsgList.End(); it++)
	{
		CCLog("function[%s] line[%d] msgId[%d] msgType[%d] msgContent[%s]", __FUNCTION__, __LINE__, (*it)->msgId, (*it)->msgType, ODETools::GBKToUTF8((*it)->msgContent).c_str());
	}
}

void ClientData::deleteGameBroadcastMsg(int msgId)
{
	for (ODEList<GameBroadcastMsg*>::iterator it = m_broadcastGameMsgList.Begin(); it != m_broadcastGameMsgList.End(); it++)
	{
		if ((*it)->msgId == msgId)
		{
			CCLog("function[%s] line[%d] deleteBroadcastMsgId[%d] msgType[%d]", __FUNCTION__, __LINE__, msgId, (*it)->msgType);

			CC_SAFE_DELETE(*it);
			m_broadcastGameMsgList.Erase(it);
			break;
		} 
	}
}

GameBroadcastMsg* ClientData::getGameFistBroadcastMsg()
{
	GameBroadcastMsg* msg = *m_broadcastGameMsgList.Begin();

	m_broadcastGameMsgList.Erase(m_broadcastGameMsgList.Begin());
	m_broadcastGameMsgList.PushBack(msg);

	return msg;
}

int ClientData::getGameBroadcastMsgCount()
{
	return m_broadcastGameMsgList.Size();
}

#ifdef SCORE_EXCHANGE_GIFT_MACRO

void ClientData::setScoreExchangeGiftBaseInfo(GQActivityBaseInfoRsp * baseInfo, int bufferLength)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	memcpy(&m_gqActivityBaseInfoRsp, baseInfo, bufferLength);
}

void ClientData::setNeedUpdateScoreExchangeGiftBaseData(bool need)
{
	m_needUpdateScoreExchangeBaseData = need;
}

void ClientData::setScoreExchangeGiftScoreInfo(GQActivityGetAwardRsp* getInfo, int bufferLength)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	memcpy(&m_gqActivityGetAwardRsp, getInfo, bufferLength);
}

void ClientData::setNeedUpdateScoreExchangeGiftScoreData(bool need)
{
	m_needUpdateScoreExchangeScoreData = need;
}

#endif // SCORE_EXCHANGE_GIFT_MACRO

void ClientData::setAccountLoginNotSelf(bool notSelf)
{
	m_accountLoginNotSelf = notSelf;
}

bool ClientData::isAccountLoginNotSelf()
{
	return m_accountLoginNotSelf;
}

void GuanDanGamePlayerData::ClearPUSRoomTableInfo()
{
	std::vector<tagPUSTableInfo*>::iterator it = m_vPUSTableInfo.begin();
	for (; it!=m_vPUSTableInfo.end(); it++)
	{
		CC_SAFE_DELETE(*it);
	}
	m_vPUSTableInfo.clear();

	ODEInt32 iTableCount = atoi(GetConfig("GD_AllTableCount"));

	if (iTableCount == 0)
	{
		iTableCount = KESSEN_All_TABLE_COUNT;
	}

	for (int i=0; i < iTableCount; i++)
	{
		tagPUSTableInfo *pTableInfo = new tagPUSTableInfo;
		memset(pTableInfo, 0, sizeof(tagPUSTableInfo));
		m_vPUSTableInfo.push_back(pTableInfo);
	}
}


void ClientData::setIsInForeground(bool foreground)
{
	m_isForeground = foreground;
}

bool ClientData::isInForeground()
{
	return m_isForeground;
}

void ClientData::setNetWorkState(int state)
{
	m_netWorkLinkState = state;
}

int ClientData::getNetWorkState()
{
	return m_netWorkLinkState;
}

void ClientData::setNetWorkUnlink(bool unlink)
{
	m_netWorkIsUnlink = unlink;
}

bool ClientData::isNetWorkUnLink()
{
	return m_netWorkIsUnlink;
}

void ClientData::setIsNeedSendLoginMessage(bool need)
{
	m_needSendLoginMessage = need;
}

bool ClientData::isNeedSendLoginMessage()
{
	return m_needSendLoginMessage;
}

void ClientData::setIsChannelPackage(bool isChannelPackage)
{
	m_isChannelPackage = isChannelPackage;
}

bool ClientData::isChannelPackage()
{
	return m_isChannelPackage;
}

void ClientData::setChannelId(const char* channelId)
{
	m_channelId = channelId;
}

const char* ClientData::getChannelId()
{
	return m_channelId.c_str();
}
//设置机器码
void ClientData::setDeviceId(std::string var)
{
	char buffer[50] = {0};
	sprintf(buffer, "%s", var.c_str());
	md5_str(buffer, strlen(buffer), buffer);
	m_deviceId = buffer;
}

std::string ClientData::getDeviceId()
{
	return m_deviceId;
}


void ClientData::setUpdateCurrentVersion(const char* currVersioin)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	strncpy (m_channelDownloadCurrentVersion, currVersioin, sizeof (m_channelDownloadCurrentVersion));
}

const char* ClientData::getUpdateCurrentVersion()
{
	return m_channelDownloadCurrentVersion;	
}

void ClientData::setUpdateLimitVersion(const char* limitVersion)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	strncpy (m_channelDownloadLimitVersion, limitVersion, sizeof (m_channelDownloadLimitVersion));

	setNeedSaveUpdateLink(true);
}

const char* ClientData::getUpdateLimitVersion()
{
	return m_channelDownloadLimitVersion;
}

void ClientData::setNeedSaveUpdateLink(bool need)
{
	m_needReSaveUpdateLink = need;
}

void ClientData::setPayTypeForIPTV (int type)
{
	m_PayTypeForIPTV = type;
}

int  ClientData::getPayTypeForIPTV ()
{
	return m_PayTypeForIPTV;
}

void ClientData::setPayMountForIPTV (int mount)
{
	m_PayMountForTPTV = mount;
}

int ClientData::getPayMountForIPTV ()
{
	return m_PayMountForTPTV;
}

void ClientData::setAlipayTypeForIPTV (int type)
{
	m_PayAlipayTypeForIPTV = type;
}

int ClientData::getAlipayTypeForIPTV ()
{
	return m_PayAlipayTypeForIPTV;
}

bool ClientData::isNeedSavaUpdateLink()
{
	return m_needReSaveUpdateLink;
}

void ClientData::ResetDataWhenChangeAccount ()
{
	m_isHasSendAnniversaryCoinToday = false;
	m_isVipCustom = 0;
	m_isFirstCharge = false;
	m_u64UserId = 0;       
	m_u64Score = 0;        
	m_u64Coin2Award = 0;   
	m_u64CompeteScore = 0; 
	m_u64AwardTicketNum = 0;  
	m_cGender = '0';
	m_uSitDownErrorCode = 0;
	m_u32CreatePRoomErrorCode = 0;
	m_kSelfHeadImagePath = "";
	m_i32LastLoginError = -1;
	m_i32LastRoomLoginError = -1;
	m_i32LastRoomLoginErrorServerID = -1;
	m_i32LastRoomLoginErrorGameID = -1;
	m_bIsQuitGameClientAlert = false;

	m_i32PhoneRechargePoint = 0;	

	m_firstBankScore = false;
	m_bankScore = 0;

	m_CurrentMedalsId = -1;
	m_CurrentMedalsRetCode = 0;
	m_isGuideMode = false;
	m_isInGuanDanGameScene = false;

	m_i32PRoomBaseMultiple = 50;	
	m_i32PRoomBaseAnte = 100;	
	m_i32PRoomMaxAnte = 100000;

	m_bIsDailyTaskDataChange = false;
	m_bLoginAgain =false;
	m_i32LotteryCount = 0;

	m_u32HuaFeiPoint = 0;

	m_i32SysBroadcastMsgID = 0;

	m_caiPiaoCount = 0;
	m_labaCounts = 0;
	m_AnniversarySendTimes = 0;
	m_SlotCounts =0;
	m_slotindex =0;
	m_canshowprizelayer =true;

	m_Ip6AtomCounts = 0;
	m_IpadCounts = 0;
	m_HongbaoCounts = 0;
	memset (m_ChunJieHuoDongAwardDetail, 0, sizeof (int) * 40);
	m_userSerialNumbers = 0;

	memset (m_LoginToken, 0, sizeof (m_LoginToken));
	memset (m_configVersion, 0, sizeof (m_configVersion));
	memset (&m_userGuidanceInfo, 0, sizeof (m_userGuidanceInfo));

	m_guanDanGuideRewardCode = 0;
	m_guanDanGuideRewardCoin = 0;

	m_LastGameID = 0;
	m_LastServerID = 0;
	m_lastLoginIp = "";
	m_lastLoginPort = 0;
	m_lastLoginRoomID = 0;

	m_LastExitNotNormalGameID = 0;
	m_LastExitNotNormalServerID = 0;
	m_LastExitNotNormalScore = 0;

	memset (m_GoldCardAvaliableTime, 0, sizeof (m_GoldCardAvaliableTime));
	memset (&personalCenterInfo, 0, sizeof (LobbyPersonalCenterInfoRsp));
	memset (&m_RankingInfo, 0, sizeof (LobbyRankingInfoRspData));

	m_headimgID = 0;
	m_BuyHeadIndex = 0;

	m_cGameStatus =0;
    m_appStoreCanResolveOrder = false;
	m_isRefreshCoinByLobby = false;

	m_lLastReceivedUserRecordIndex = 0;
	m_lLastReceivedScoreRecordIndex = 0;

#ifdef SCORE_EXCHANGE_GIFT_MACRO

	memset(&m_gqActivityBaseInfoRsp, 0, sizeof(m_gqActivityBaseInfoRsp));
	m_needUpdateScoreExchangeBaseData = false;
	memset(&m_gqActivityGetAwardRsp, 0, sizeof(m_gqActivityGetAwardRsp));
	m_needUpdateScoreExchangeScoreData = false;

	m_isOpenScoreExchangeGift = false;

#endif // SCORE_EXCHANGE_GIFT_MACRO

	m_isFirstCharge = false;
	m_isVipCustom = 0;
	m_isHasSendAnniversaryCoinToday = false;

	m_bHasNewInviteFriendsRecord = false;
	m_vecInviteScoreRecords.clear();
	m_vecInviteUserRecords.clear();

	m_vecExchangeCodeGetItems.clear();

	ODEZeroMemory(m_szUserName, sizeof(m_szUserName));
	ODEZeroMemory(m_szPassword, sizeof(m_szPassword));
	ODEZeroMemory(m_szNickname, sizeof(m_szNickname));
	

	ODEZeroMemory(m_szGameTip, sizeof(m_szGameTip));

	ODEZeroMemory(&m_UserSerialLoginTaskInfo, sizeof(m_UserSerialLoginTaskInfo));
	
	ODEZeroMemory(&m_LobbyBankClientAuthenReq, sizeof(m_LobbyBankClientAuthenReq));
	ODEZeroMemory(&m_LobbyBankInfoRsp, sizeof(m_LobbyBankInfoRsp));
	ODEZeroMemory(&m_oGameTimesWonInfo, sizeof(m_oGameTimesWonInfo));
	ODEZeroMemory(&m_oTimesWonInfo, sizeof(m_oTimesWonInfo));
	ODEZeroMemory(&m_bHasMailForEachType, sizeof(m_bHasMailForEachType));
	ODEZeroMemory(&m_UserMailListInfo, sizeof(m_UserMailListInfo));
	ODEZeroMemory(&m_oNewMail, sizeof(m_oNewMail));

	ODEZeroMemory(&m_oTimesWonInfo, sizeof(m_oTimesWonInfo));
	ODEZeroMemory(&m_oOneRoundGet5YuanActInfo, sizeof(m_oOneRoundGet5YuanActInfo));

	ODEZeroMemory(&m_oEnterMatchFailedInfo, sizeof(m_oEnterMatchFailedInfo));

	g_pkLobbyConnectData->RemoveAllListData ();
}


void ClientData::setCaiPiaoCount(int count)
{
	m_caiPiaoCount = count;
}

int ClientData::getCaiPiaoCount()
{
	return m_caiPiaoCount;
}

void ClientData::setLabaCounts (int count)
{
	m_labaCounts = count;
}

int ClientData::getLabaCounts ()
{
	return m_labaCounts;
}

void ClientData::setIp6AtomCounts (int counts)
{
	m_Ip6AtomCounts = counts;
}

int ClientData::getIp6AtomCounts ()
{
	return m_Ip6AtomCounts;
}

void ClientData::setIpadAtomCounts (int counts)
{
	m_IpadCounts = counts;
}

int ClientData::getIpadAtomCounts ()
{
	return m_IpadCounts;
}

void ClientData::setHongBaoCounts (int counts)
{
	m_HongbaoCounts = counts;
}

int ClientData::getHongBaoCounts ()
{
	return m_HongbaoCounts;
}

void ClientData::setSlotCounts (int counts)
{
	m_SlotCounts = counts;
}

int ClientData::getSlotCounts ()
{
	return m_SlotCounts;
}

void ClientData::setSlotTargetIndex (int counts)
{
	m_slotindex = counts;
}

int ClientData::getSlotTargetIndex ()
{
	return m_slotindex;
}

void ClientData::setCanShowSlotPrize (bool l_canshowprize)
{
	m_canshowprizelayer = l_canshowprize;
}

bool ClientData::getCanShowSlotPrize ()
{
	return m_canshowprizelayer;
}




void ClientData::setUserSerialNumbers (long long numbers)
{
	m_userSerialNumbers = numbers;
}
long long ClientData::getUserSerailNumbers ()
{
	return m_userSerialNumbers;
}

void ClientData::SetMailListInfo(tagLobbyPlayerMailListInfo *pMailInfo)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	ODEMemoryCopy(&m_UserMailListInfo, pMailInfo, sizeof(m_UserMailListInfo));
}

tagLobbyPlayerMailListInfo* ClientData::GetMailListInfo()
{
	return &m_UserMailListInfo;
}

void ClientData::SetMailHasNewInfo(tagLobbyHasMailInfo* info)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	ODEMemoryCopy(&m_bHasMailForEachType, info, sizeof(tagLobbyHasMailInfo));
}

tagLobbyHasMailInfo* ClientData::GetMailHasNewInfo()
{
	return &m_bHasMailForEachType;
}

void ClientData::SetNewMailInfo(sMail* pMail)
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	ODEMemoryCopy(&m_oNewMail, pMail, sizeof(m_oNewMail));
}

sMail* ClientData::GetNewMailInfo()
{
	return &m_oNewMail;
}

void ClientData::setBagListItemId( int item_id)
{
	m_bagitem_id =item_id;
}

int  ClientData::getBagListItemId()
{
	return m_bagitem_id;
}

int ClientData::getBagListItemNum()
{
	return m_bagitem_num;
}

void ClientData::setBagListItemNum(int item_num)
{
	m_bagitem_num = item_num;
}

void ClientData::SetTimesWonInfo( tagTimesWonInfo* pInfo )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (pInfo->activityType == E_TIMESWON_TYPE_TOTAL)
	{
		//累计胜场
		ODEMemoryCopy(&m_oTimesWonInfo[0], pInfo, sizeof(tagTimesWonInfo));
	}
	else
	{
		//连续胜场
		ODEMemoryCopy(&m_oTimesWonInfo[1], pInfo, sizeof(tagTimesWonInfo));
	}	
}

tagTimesWonInfo* ClientData::GetTimesWonInfo( int iActivityType )
{
	if (E_TIMESWON_TYPE_TOTAL == iActivityType)
	{
		//累胜
		return &m_oTimesWonInfo[0];
	}
	else
	{
		//连胜
		return &m_oTimesWonInfo[1];
	}
}

void ClientData::setGoldCardBtnStatus(bool status)
{
	b_goldONOFF = status; 
}

bool ClientData::getGoldCardBtnStatus()
{
	return b_goldONOFF;
}

const char* ClientData::getExchangeOrderInfo()
{
     return OrderID.c_str();
}

void ClientData::setExchangeOrderInfo(char* ordernum)
{
     OrderID = ordernum;
}

void ClientData::SetIsBuyedHeadImage(int isbuyed)
{
	m_isBuyed = isbuyed;
}

int  ClientData::GetIsBuyedHeadImage ()
{
	return m_isBuyed;
}

void ClientData::SetHasSendAnniversaryCoinToday (bool isSend)
{
	m_isHasSendAnniversaryCoinToday = isSend;
}

bool ClientData::GetHasSendAnniversaryCoinToday ()
{
	return m_isHasSendAnniversaryCoinToday;
}

void ClientData::SetLastGameRecordGameID (int gameID)
{
	m_LastGameID = gameID;
}

int	 ClientData::GetLastGameRecordGameID ()
{
	return m_LastGameID;
}

void ClientData::SetLastGameRecordServerID (int serverID)
{
	m_LastServerID = serverID;
}

int  ClientData::GetLastGameRecordServerID ()
{
	return m_LastServerID;
}

void ClientData::SetLastGameRecordTime (time_t lastTime)
{
	m_LastGameTime = lastTime;
}

time_t  ClientData::GetLastGameRecordTime ()
{
	return m_LastGameTime;
}

void ClientData::SetGameTimesWonInfo( tagGameTimesWonInfo* info )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (info->activityType == 1)
	{
		memcpy(&m_oGameTimesWonInfo[0], info, sizeof(tagGameTimesWonInfo));
	}
	else if (info->activityType == 2)
	{
		memcpy(&m_oGameTimesWonInfo[1], info, sizeof(tagGameTimesWonInfo));
	}
}


tagGameTimesWonInfo* ClientData::GetGameTimesWonInfo( int iActivityType )
{
	if (iActivityType == 1)
	{
		return &m_oGameTimesWonInfo[0];
	}
	else if (iActivityType == 2)
	{
		return &m_oGameTimesWonInfo[1];
	}
	return &m_oGameTimesWonInfo[1];
}

LobbyPersonalCenterInfoRsp * ClientData::GetPersonalCenterInfo ()
{
	return &personalCenterInfo;
}

void ClientData::SetLobbyPersonCenterInfo (LobbyPersonalCenterInfoRsp * info)
{
	memcpy (&personalCenterInfo, info, sizeof (LobbyPersonalCenterInfoRsp));
}

LobbyRankingInfoRspData * ClientData::GetRankingInfo ()
{
	return &m_RankingInfo;
}

void ClientData::SetRankingInfo (LobbyRankingInfoRspData * info)
{
	memcpy (&m_RankingInfo, info, sizeof (tagLobbyRankingInfoRsp));
}

int  ClientData::GetVipCustom ()
{
	return m_isVipCustom;
}

void ClientData::setIsVipCustom (int isVip)
{
	m_isVipCustom = isVip;
}

bool ClientData::GetIsRefreshGetLobby ()
{
	return m_isRefreshCoinByLobby;
}

void ClientData::SetRefreshByLobby (bool bRefresh)
{
	m_isRefreshCoinByLobby = bRefresh;
}

void ClientData::setUserGuidanceInfo (CSGuide2PCRspData * info)
{
	memcpy (&m_userGuidanceInfo, info, sizeof (m_userGuidanceInfo));
}

CSGuide2PCRspData * ClientData::getUserGuidanceInfo ()
{
	return &m_userGuidanceInfo;
}

void ClientData::setMobileActiveNoticeInfo (tagSCMobileActiveNoticeRsp * rsp)
{
	memcpy (&m_mobileActiveNoticeInfo, rsp, sizeof (m_mobileActiveNoticeInfo));
}

tagSCMobileActiveNoticeRsp * ClientData::GetMobileActiveNoticeInfo ()
{
	return &m_mobileActiveNoticeInfo;
}

tagOneRoundGet5YuanActInfo* ClientData::GetOneRoundGet5YuanActInfo()
{
	return &m_oOneRoundGet5YuanActInfo;
}

void ClientData::SetOneRoundGet5YuanActInfo( int type, long long TotalCash, long long challengeCash, long long expendCash, int bindStatus, 
											long long progress2, long long progress3, int coinTicket, string SpreadCode, string strMobile )
{
	m_oOneRoundGet5YuanActInfo.userType = type;
	m_oOneRoundGet5YuanActInfo.TotalCash = TotalCash;
	m_oOneRoundGet5YuanActInfo.challengeCash = challengeCash;
	m_oOneRoundGet5YuanActInfo.expendCash = expendCash;
	m_oOneRoundGet5YuanActInfo.bindStatus = bindStatus;
	m_oOneRoundGet5YuanActInfo.progress2 = progress2;
	m_oOneRoundGet5YuanActInfo.progress3 = progress3;
	m_oOneRoundGet5YuanActInfo.coinTicket = coinTicket;

	strcpy(m_oOneRoundGet5YuanActInfo.SpreadCode, SpreadCode.c_str());
	strcpy(m_oOneRoundGet5YuanActInfo.strMobile, strMobile.c_str());
}

void ClientData::SetOneRoundGet5YuanUserType( int type, int bindStatus )
{
	m_oOneRoundGet5YuanActInfo.userType = type;
	m_oOneRoundGet5YuanActInfo.bindStatus = bindStatus;
}

void ClientData::initRandomLogin()
{
	int count = 0;
	if (g_pkGuanDanGame->m_isAppStoreAuditVersion)
	{
		count = atoi(GetConfig("AppStoreAuditLoginServerCount"));
	}
	else
	{
		count = atoi(GetConfig("LoginServerCount"));
	}
	srand(time(NULL));
	m_randomLoginIndex = rand() % count;
}

const char* ClientData::getRandomLoginIp()
{
	char ipBuffer[50] = {0};
	if (g_pkGuanDanGame->m_isAppStoreAuditVersion)
	{
		sprintf(ipBuffer, "AppStoreAuditLoginServerIp_%d", m_randomLoginIndex);
	}
	else
	{
		sprintf(ipBuffer, "LoginServerIp_%d", m_randomLoginIndex);
	}
	m_randomLoginIp = GetConfig(ipBuffer);

	return m_randomLoginIp.c_str();
}

int ClientData::getRandomLoginPort()
{
	char portBuffer[50] = {0};
	if (g_pkGuanDanGame->m_isAppStoreAuditVersion)
	{
		sprintf(portBuffer, "AppStoreAuditLoginServerPort_%d", m_randomLoginIndex);
	}
	else
	{
		sprintf(portBuffer, "LoginServerPort_%d", m_randomLoginIndex);
	}
	m_randomLoginPort = atoi(GetConfig(portBuffer));

	return m_randomLoginPort;
}

void ClientData::AddExchangeCodeGetItem( tagExchangeCodeItem* info )
{
	tagExchangeCodeItem* info2 = new tagExchangeCodeItem;
	memcpy(info2, info, sizeof(tagExchangeCodeItem));
	m_vecExchangeCodeGetItems.push_back(info2);
}

std::vector<tagExchangeCodeItem*>* ClientData::GetExchangeCodeGetItem()
{
	return &m_vecExchangeCodeGetItems;
}


void ClientData::setExitNotNormalGameID (int gameid) 
{
	m_LastExitNotNormalGameID = gameid;
}
void ClientData::setExitNotNormalServerID (int serverID) 
{
	m_LastExitNotNormalServerID = serverID;
}
void ClientData::setExitNotNormalScore (long long score)
{
	m_LastExitNotNormalScore = score;
}

long long ClientData::getExitNotNormalScore () 
{
	return m_LastExitNotNormalScore;
}
int ClientData::getExitNotNormalGameID () 
{
	return m_LastExitNotNormalGameID;
}
int ClientData::getExitNotNormalServerID () 
{
	return m_LastExitNotNormalServerID;
}

void ClientData::setChunJieHuoDongAwardDetail (int pos, int values)
{
	m_ChunJieHuoDongAwardDetail[pos] = values;
}

int ClientData::getChunJieHuoDongAwardDetail (int pos)
{
	return m_ChunJieHuoDongAwardDetail[pos];
}

int ClientData::getChunJieHuoDongAwardSize ()
{
	int counts = 0;
	for (int i = 0; i < 40; i++)
	{
		if (m_ChunJieHuoDongAwardDetail[i] != 0)
			counts ++;
	}
	return counts;
}

void ClientData::ResetChunJieHuoDongAwardDetail ()
{
	memset (m_ChunJieHuoDongAwardDetail, 0, sizeof (int) * 40);
}

void ClientData::setLoginToken (char * token)
{
	sprintf (m_LoginToken, "%s", token);
}

char * ClientData::getLoginToken ()
{
	return m_LoginToken;
}

void ClientData::setConfigVersion (char * version)
{
	strcpy (m_configVersion, version);
}

char * ClientData::getConfigVersion ()
{
	return m_configVersion;
}

void ClientData::SetBreaklineConnectparam(int serip,int gameid,int entertime)
{
	 server_Ip = serip;
	 Game_ID = gameid;
	 EnterTime = entertime;
}

int ClientData::GetReConnectInfoSerIp()
{
	return server_Ip;
}

int ClientData::GetReConnectInfoGameID()
{
	return Game_ID;
}

int ClientData::GetReConnectInfoEnterTime()
{
	return EnterTime;
}


void ClientData::setSettintDownloadSkinPath (const char * skinPath)
{
	strcpy (m_settingDownloadSkinPath, skinPath);
}

void ClientData::setSettingDownloadSkinContentID (int contentID)
{
	m_settingDownloadSkinContentID = contentID;
}

char * ClientData::getSettingDownloadSkinPath ()
{
	return m_settingDownloadSkinPath;
}

int	   ClientData::getSettingDownloadSkinContentID ()
{
	return m_settingDownloadSkinContentID;
}

void ClientData::setGuanDanGetAwardString (const char * awardText)
{
	strcpy (m_guanDanGetAwardString, awardText);
}

char * ClientData::getGuanDanGetAwardString ()
{
	return m_guanDanGetAwardString;
}

void ClientData::setCurrentUserMedalsId (int medalsId)
{
	m_CurrentMedalsId = medalsId;
}

int ClientData::getCurrentUserMedalsId ()
{
	return m_CurrentMedalsId;
}

void ClientData::setCurrentUseMedalsRetCode (int code)
{
	m_CurrentMedalsRetCode = code;
}

int ClientData::getCurrentUseMedalsRetCode ()
{
	return m_CurrentMedalsRetCode;
}

void ClientData::setIsInGuanDanGameScene (bool isGameScene)
{
	m_isInGuanDanGameScene = isGameScene;
}

bool ClientData::getIsInGuanDanGameScene ()
{
	return m_isInGuanDanGameScene;
}

void ClientData::setIsGuideMode (bool guideMode)
{
	m_isGuideMode = guideMode;
}

bool ClientData::getIsGuideMode ()
{
	return m_isGuideMode;
}

void ClientData::setGuanDanGuideRewardCode (int code)
{
	m_guanDanGuideRewardCode = code;
}

int ClientData::getGuanDanGuideRewardCode ()
{
	return m_guanDanGuideRewardCode;
}

void ClientData::setGuanDanGuideRewardCoin (int coin)
{
	m_guanDanGuideRewardCoin = coin;
}

int ClientData::getGuanDanGuideRewardCoin ()
{
	return m_guanDanGuideRewardCoin;
}

void ClientData::SetHasNewInviFriendsRecord(bool bHasNew)
{
	m_bHasNewInviteFriendsRecord = bHasNew;
}

bool ClientData::HasNewInviFriendsRecord()
{
	return m_bHasNewInviteFriendsRecord;
}

void ClientData::SetInviteFriendsLastReceivedUserRecordIndex(long long recordIndex)
{
	m_lLastReceivedUserRecordIndex = recordIndex;
}
void ClientData::SetInviteFriendsLastReceivedScoreRecordIndex(long long recordIndex)
{
	m_lLastReceivedScoreRecordIndex = recordIndex;
}
long long ClientData::GetInviteFriendsLastReceivedUserRecordIndex()
{
	return m_lLastReceivedUserRecordIndex;
}
long long ClientData::GetInviteFriendsLastReceivedScoreRecordIndex()
{
	return m_lLastReceivedScoreRecordIndex;
}

int ClientData::GetFindPwdBackLastTime()
{
	return m_iFindPwdCutDownLastTime;
}
int ClientData::GetFindPwdBackCurrTime()
{
	return m_iFindPwdCutDownCurrTime;
}
void ClientData::SetFindPwdBackLastTime(int time)
{
	m_iFindPwdCutDownLastTime = time;
}
void ClientData::SetFindPwdBackCurrTime(int time)
{
	m_iFindPwdCutDownCurrTime = time;
}

void ClientData::setNeedSendCaCardNoToServer(bool enable)
{
	m_needSendCaCardNo = enable;
}

bool ClientData::isNeedSendCaCardNoToServer()
{
	return m_needSendCaCardNo;
}

std::vector<tagInviteUserRemaindRecord*>* ClientData::GetInviteFriendsScoreRecord()
{
	return &m_vecInviteScoreRecords;
}

std::vector<tagInviteUserInvitedUserRecord*>* ClientData::GetInviteFriendsUserRecord()
{
	return &m_vecInviteUserRecords;
}

void ClientData::AddInviteFriendsScoreRecord( tagInviteUserRemaindRecord* msg )
{
	tagInviteUserRemaindRecord* info = new tagInviteUserRemaindRecord;
	memcpy(info, msg, sizeof(tagInviteUserRemaindRecord));
	m_vecInviteScoreRecords.push_back(info);
}

void ClientData::ClearInviteFriendsScoreRecord()
{
	for (int i = 0; i < m_vecInviteScoreRecords.size(); ++i)
	{
		tagInviteUserRemaindRecord* pRecord = m_vecInviteScoreRecords.at(i);
		delete pRecord;
	}

	m_vecInviteScoreRecords.clear();
}

void ClientData::AddInviteFriendsUserRecord( tagInviteUserInvitedUserRecord* msg )
{
	tagInviteUserInvitedUserRecord* info = new tagInviteUserInvitedUserRecord;
	memcpy(info, msg, sizeof(tagInviteUserInvitedUserRecord));
	m_vecInviteUserRecords.push_back(info);
}

void ClientData::ClearInviteFriendsUserRecord()
{
	for (int i = 0; i < m_vecInviteUserRecords.size(); ++i)
	{
		tagInviteUserInvitedUserRecord* pRecord = m_vecInviteUserRecords.at(i);
		delete pRecord;
	}

	m_vecInviteUserRecords.clear();
}

void ClientData::checkUnsendPayData(bool showloading)
{
    if (getPayCount() > 0)
    {
        AppStorePayStruct* data = getFirstPayData();
        while (data == NULL && getPayCount() > 0) {
            CCLog("%s FristData == null payCount == %d", __FUNCTION__, getPayCount());
            m_appstoreList.erase(m_appstoreList.begin());
            data = getFirstPayData();
        }
        if (data)
        {
            const char* orderno = data->orderno;
            const char* keyValue = data->kvalue;
            if (showloading)
            {
				g_pkGuanDanGame->ShowLoading();
            }
            g_pkGuanDanGame->VerifyIOSPurchase(data->orderno, data->kvalue);
        }
    }
    else
    {
        CCLog("%s payCount == 0, Threre is no data need to send.", __FUNCTION__);
    }
}

void ClientData::addPayData(AppStorePayStruct* data, bool needSave)
{
    bool dataExisted = false;
    for (vector<AppStorePayStruct*>::iterator it = m_appstoreList.begin(); it != m_appstoreList.end(); it++)
    {
        if (strcmp((*it)->orderno, data->orderno) == 0)
        {
            if (strcmp((*it)->kvalue, data->kvalue) == 0)
            {
                CCLog("%s AppStorePay add OrderNo is normal", __FUNCTION__);
            }
            else
            {
                CCLog("%s AppStorePay add OrderNo is abnormal OldOrderNo[%s] NewOrderNo[%s]", __FUNCTION__, (*it)->orderno, data->orderno);
                
                //memset((*it)->kvalue, 0, sizeof((*it)->kvalue));
                //memcpy((*it)->kvalue, data->kvalue, sizeof((*it)->kvalue));
            }
            dataExisted = true;
            
            delete data;
            data = NULL;
            
            break;
        }
    }
    
    if (!dataExisted)
    {
        m_appstoreList.push_back(data);
    }
    
    if (needSave)
    {
        saveAppStorePayDataToFile();
    }
}

void ClientData::deletePayData(const char *orderno)
{
    bool ordernoExisted = false;
    char tempOrderNo[64] = {0};
    memcpy(tempOrderNo, orderno, 64);
    for (vector<AppStorePayStruct*>::iterator it = m_appstoreList.begin(); it != m_appstoreList.end(); it++)
    {
        if (strcmp((*it)->orderno, tempOrderNo) == 0)
        {
            delete *it;
            *it = NULL;
            m_appstoreList.erase(it);
            
            ordernoExisted = true;
            
            break;
        }
    }
    
    if (!ordernoExisted)
    {
        CCLog("%s AppStorePay add OrderNo is abnormal OrderNo[%s]", __FUNCTION__, tempOrderNo);
    }
    
    saveAppStorePayDataToFile();
}

int ClientData::getPayCount()
{
    return m_appstoreList.size();
}

AppStorePayStruct* ClientData::getFirstPayData()
{
    if (m_appstoreList.size() > 0)
    {
        return m_appstoreList.at(0);
    }
    else
    {
        return NULL;
    }
}

void ClientData::saveAppStorePayDataToFile()
{
    int payCount = m_appstoreList.size();
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("12138_count", payCount);
    CCUserDefault::sharedUserDefault()->flush();
    
    for (int i(0); i < payCount; ++i)
    {
        AppStorePayStruct* data = m_appstoreList.at(i);
        
        if (data)
        {
            const char* orderno = data->orderno;
            const char* keyValue = data->kvalue;
            
            char keyBuffer[20] = {0};
            sprintf(keyBuffer, "12138_%d", i);
            
            char valueBuffer[4096] = {0};
            sprintf(valueBuffer, "%s;%s", orderno, keyValue);
            
            //CCLog("%s index[%d]key[%s]orderno[%s]kvalue[%s]", __FUNCTION__, i, keyBuffer, orderno, keyValue);
            
            string valueStr = valueBuffer;
            SaveData(valueStr);
            
            
            CCUserDefault::sharedUserDefault()->setStringForKey(keyBuffer, valueStr);
            CCUserDefault::sharedUserDefault()->flush();
        }
        else
        {
            CCLog("%s paycash == null", __FUNCTION__);
        }
    }
}

void ClientData::parseAppStorePayDataToCash()
{
    while (m_appstoreList.size() > 0) {
        AppStorePayStruct* tempData = m_appstoreList.at(0);
        if (tempData)
        {
            delete tempData;
            tempData = NULL;
            
            m_appstoreList.erase(m_appstoreList.begin());
        }
    }
    
    int payCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("12138_count");
    
    CCLog("%s Find [%d] unSend Pay Data", __FUNCTION__, payCount);
    
    for (int i(0); i < payCount; ++i)
    {
        char keyBuffer[20] = {0};
        sprintf(keyBuffer, "12138_%d", i);
        
        string valueStr = CCUserDefault::sharedUserDefault()->getStringForKey(keyBuffer, "");
        
        if (valueStr.length() > 0)
        {
            ParseData(valueStr);
            
            int index = valueStr.find(";", 0);
            
            if (index == -1)
            {
                CCLog("%s STRING ERROR : %s %s", __FUNCTION__, keyBuffer, valueStr.c_str());
            }
            else
            {
                char orderBuffer[64] = {0};
                memcpy(orderBuffer, valueStr.substr(0, index).c_str(), 64);
                char keyValueBuffer[4096] = {0};
                memcpy(keyValueBuffer, valueStr.substr(index + 1).c_str(), 4096);
                
                AppStorePayStruct* data = new AppStorePayStruct;
                memset(data->orderno, 0, sizeof(data->orderno));
                memset(data->kvalue, 0, sizeof(data->kvalue));
                memcpy(data->orderno, orderBuffer, sizeof(data->orderno));
                memcpy(data->kvalue, keyValueBuffer, sizeof(data->kvalue));
                
                CCLog("%s index[%d]key[%s]orderno[%s]kvalue[%s]", __FUNCTION__, i, keyBuffer, data->orderno, data->kvalue);
                
                addPayData(data, false);
            }
            
        }
    }
    
}

void ClientData::setCanAppStoreResolveOrder(bool enable) 
{
	m_appStoreCanResolveOrder = enable;
}

bool ClientData::canAppStoreResolveOrder()
{
	return m_appStoreCanResolveOrder;
}

void ClientData::setIsTuanTuan( bool show )
{
	m_isTuanTuan=show;
}

bool ClientData::isTuanTuan()
{
	return m_isTuanTuan;
}

void ClientData::setIsPersonalMatch( bool show )
{
	m_isPersonalMatch=show;
}

bool ClientData::isPersonalMatch()
{
	return m_isPersonalMatch;
}

void ClientData::setPrivateTableID(int tableID)
{
	m_tableId=tableID;
}

int ClientData::getPrivateTableID()
{
	return m_tableId;
}

void ClientData::setPrivatetableName(std::string table_name)
{
	m_tablename=table_name;
}

std::string ClientData::getPrivatetableName()
{
	return m_tablename;
}

void ClientData::SetMatchRspError( ODEInt32 iError )
{
	m_i32MatchRspError=iError;
}

ODEInt32 ClientData::GetMatchRspError()
{
	return m_i32MatchRspError;
}

void ClientData::AddGuanDanMatchSimpleInfo( tagMatchSimpleInfo* info )
{
	tagMatchSimpleInfo* simpleInfo = new tagMatchSimpleInfo;

	simpleInfo->id = info->id;
	simpleInfo->firstAward = info->firstAward;
	simpleInfo->name = info->name;
	simpleInfo->userCount = info->userCount;
	simpleInfo->paramA = info->paramA;
	simpleInfo->paramC = info->paramC;
	simpleInfo->sortId = info->sortId;

	bool bInsert = false;

	for (int i = 0; i < m_vecAllMatchSimpleInfos_GD.size(); ++i)
	{
		tagMatchSimpleInfo* pTemp = m_vecAllMatchSimpleInfos_GD.at(i);

		if (simpleInfo->sortId < pTemp->sortId)
		{
			m_vecAllMatchSimpleInfos_GD.insert(m_vecAllMatchSimpleInfos_GD.begin() + i, simpleInfo);
			bInsert = true;
			break;
		}
	}

	if (! bInsert)
	{
		m_vecAllMatchSimpleInfos_GD.push_back(simpleInfo);
	}
}

std::vector<tagMatchSimpleInfo*>* ClientData::GetAllGuanDanMatchSimpleInfos()
{
	return &m_vecAllMatchSimpleInfos_GD;
}

void ClientData::ClearAllGuanDanMatchSimpleInfo()
{
	for (int i = 0; i< m_vecAllMatchSimpleInfos_GD.size(); ++i)
	{
		tagMatchSimpleInfo* pInfo = m_vecAllMatchSimpleInfos_GD.at(i);

		delete pInfo;
	}

	m_vecAllMatchSimpleInfos_GD.clear();
}

tagMatchSimpleInfo* ClientData::GetGuanDanMatchSimpleInfo( long long matchID )
{
	for (int i = 0; i < m_vecAllMatchSimpleInfos_GD.size(); ++i)
	{
		if (m_vecAllMatchSimpleInfos_GD.at(i)->id == matchID)
		{
			return m_vecAllMatchSimpleInfos_GD.at(i);
		}
	}

	return NULL;
}

std::vector<tagMatchSimpleInfo> ClientData::GetCurrPageGuanDanMatchSimpleInfos( ODEInt32 iRows, ODEInt32 iCols, ODEInt32 iPageIndex )
{
	std::vector<tagMatchSimpleInfo> temp;
	temp.clear();

	int iStartIndex = iPageIndex * (iRows * iCols);

	for (int i = iStartIndex; i < ( iStartIndex + iRows * iCols); ++i)
	{
		if (i < m_vecAllMatchSimpleInfos_GD.size())
		{
			tagMatchSimpleInfo info;
			info.id = m_vecAllMatchSimpleInfos_GD.at(i)->id;
			info.name = m_vecAllMatchSimpleInfos_GD.at(i)->name;
			info.firstAward = m_vecAllMatchSimpleInfos_GD.at(i)->firstAward;
			info.userCount = m_vecAllMatchSimpleInfos_GD.at(i)->userCount;
			info.paramA = m_vecAllMatchSimpleInfos_GD.at(i)->paramA;
			info.paramC = m_vecAllMatchSimpleInfos_GD.at(i)->paramC;
			info.sortId = m_vecAllMatchSimpleInfos_GD.at(i)->sortId;

			temp.push_back(info);
		}		
	}

	return temp;
}

void ClientData::AddPartInGuanDanMatchInfo( tagUserMatchInfo* info )
{
	tagUserMatchInfo* tagInfo = new tagUserMatchInfo;
	memcpy(tagInfo, info, sizeof(tagUserMatchInfo));
	m_vecPartInMatchInfos_GD.push_back(tagInfo);
}

std::vector<tagUserMatchInfo*>* ClientData::GetPartInGuanDanMatchInfos()
{
	return &m_vecPartInMatchInfos_GD;
}

tagUserMatchInfo* ClientData::GetPartInGuanDanMatchInfo( long long matchId )
{
	for (int i = 0; i < m_vecPartInMatchInfos_GD.size(); ++i)
	{
		tagUserMatchInfo* pInfo = m_vecPartInMatchInfos_GD.at(i);

		if (pInfo->id == matchId)
		{
			return pInfo;
		}
	}

	return NULL;
}

void ClientData::SetCurrGuanDanMatchId( long long id )
{
	m_iCurrMatchId_GD = id;
}

long long ClientData::GetCurrGuanDanMatchId()
{
	return m_iCurrMatchId_GD;
}

void ClientData::ClearPartInGuanDanMatchInfo()
{
	for (int i = 0; i< m_vecPartInMatchInfos_GD.size(); ++i)
	{
		tagUserMatchInfo* pInfo = m_vecPartInMatchInfos_GD.at(i);

		delete pInfo;
	}

	m_vecPartInMatchInfos_GD.clear();
}

void ClientData::SetGuanDanCurrMatchLayerDetailInfo( SCGetMatchInfoRsp* info )
{
	m_currMatchDetailInfo_GD.Clear();

	m_currMatchDetailInfo_GD.matchId = info->id;
	m_currMatchDetailInfo_GD.realBeginTime = info->realBeginTime;

	m_currMatchDetailInfo_GD.basicInfo.targetScore = info->basicInfo.targetScore;
	m_currMatchDetailInfo_GD.basicInfo.totalRound = info->basicInfo.totalRound;
	m_currMatchDetailInfo_GD.basicInfo.matchMode = info->basicInfo.matchMode;
	m_currMatchDetailInfo_GD.basicInfo.game = info->basicInfo.game;
	m_currMatchDetailInfo_GD.basicInfo.gameMode = info->basicInfo.gameMode;
	m_currMatchDetailInfo_GD.basicInfo.gameRoom = info->basicInfo.gameRoom;
	m_currMatchDetailInfo_GD.basicInfo.begintime = info->basicInfo.begintime;
	m_currMatchDetailInfo_GD.basicInfo.matchReqs = info->basicInfo.matchReqs;
	m_currMatchDetailInfo_GD.basicInfo.servers = info->basicInfo.servers;
	m_currMatchDetailInfo_GD.basicInfo.paramA = info->basicInfo.paramA;
	m_currMatchDetailInfo_GD.basicInfo.paramC = info->basicInfo.paramC;
	m_currMatchDetailInfo_GD.basicInfo.sortId = info->basicInfo.sortId;

	m_currMatchDetailInfo_GD.stateInfo.curScore = info->stateInfo.curScore;
	m_currMatchDetailInfo_GD.stateInfo.curRound = info->stateInfo.curRound;
	m_currMatchDetailInfo_GD.stateInfo.userCount = info->stateInfo.userCount;

	bool bHasSignedUp = false;

	for (int i = 0; i < m_vecPartInMatchInfos_GD.size(); ++i)
	{
		if (info->id == m_vecPartInMatchInfos_GD.at(i)->id)
		{
			bHasSignedUp = true;
			break;
		}
	}

	m_currMatchDetailInfo_GD.hasSignedUp = bHasSignedUp;

	for (int i = 0; i < m_vecAllMatchSimpleInfos_GD.size(); ++i)
	{
		if (info->id == m_vecAllMatchSimpleInfos_GD.at(i)->id)
		{
			m_currMatchDetailInfo_GD.matchName = m_vecAllMatchSimpleInfos_GD.at(i)->name;
			m_vecAllMatchSimpleInfos_GD.at(i)->userCount = info->stateInfo.userCount;
			break;
		}
	}
}

tagCurrMatchDetailInfo* ClientData::GetGuanDanCurrMatchLayerDetailInfo()
{
	return &m_currMatchDetailInfo_GD;
}

void ClientData::SetLoginGuanDanMatchServerSuc( bool bSuc )
{
	m_bIsLoginMatchSuc_GD=bSuc;
}

bool ClientData::IsLoginGuanDanMatchServerSuc()
{
	return m_bIsLoginMatchSuc_GD;
}

void ClientData::SetGuanDanMatchGame_ID( ODEInt32 id )
{
	m_matchgame_id=id;
}

ODEInt32 ClientData::GetGuanDanMatchGame_ID()
{
	return m_matchgame_id;
}

void ClientData::AddAllGuanDanMatchAwardInfo(/* long long matchId,*/ ODEInt32 pos, std::string strAwardDes )
{
	m_mapAllGuanDanAwardInfo[pos].push_back(strAwardDes);
}

bool ClientData::HasGuanDanMatchAwardInfo( /*long long matchId*/ )
{
	if (/*m_mapAllGuanDanAwardInfo[matchId]*/m_mapAllGuanDanAwardInfo.size() > 0)
	{
		return true;
	}

	return false;
}

map<ODEInt32,vector<string> >* ClientData::GetAllGuanDanMatchAwardInfo()
{
	return &m_mapAllGuanDanAwardInfo;
}

void ClientData::ClearGuanDanMatchAwardList()
{
	m_mapAllGuanDanAwardInfo.clear();
}

void ClientData::SetShowAllGuanDanAwardFromTop( bool bTop )
{
	m_bShowAllGuanDanAwardFromTop = bTop;
}

bool ClientData::IsShowAllGuanDanAwardFromTop()
{
	return m_bShowAllGuanDanAwardFromTop;
}

void ClientData::setGuanDanMatchRankerListInfo( std::vector<RankUserInfo> l_toplist )
{
	m_GuanDanranker_info_list.assign(l_toplist.begin(),l_toplist.end());
}


std::vector<RankUserInfo> * ClientData::getGaunDanMatchRankerListInfo()
{
	return &m_GuanDanranker_info_list;
}

void ClientData::AddGuanDanRankListInfo( int rank, std::string strUserName )
{
	m_mapGuanDanMatchRankList.insert(make_pair(rank,strUserName));
}

void ClientData::ClearGuanDanMatchRankList()
{
	m_mapGuanDanMatchRankList.clear();
}

map<int, string>* ClientData::GetGuanDanMatchRankList()
{
	return &m_mapGuanDanMatchRankList;
}

void ClientData::ClearMatchGameMessageBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	for (ODEList<tagGameMessageBuffer*>::iterator it=m_MatchMessageBuffer.Begin(); it!=m_MatchMessageBuffer.End(); it++)
	{
		ODE_SAFE_DELETE(*it);
	}
	m_MatchMessageBuffer.Clear();
}

void ClientData::AddMsgToMatchMessageBuffer( ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	tagGameMessageBuffer *pBuffer = new tagGameMessageBuffer;
	if (pBuffer)
	{
		pBuffer->u32GameMessageID = nMsgID;
		pBuffer->u32DataSize = length;
		ODEMemoryCopy(pBuffer->GameMessageData, buffer, length);

		m_MatchMessageBuffer.PushBack(pBuffer);
	}
}

tagGameMessageBuffer* ClientData::GetFrontMatchMessageInBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (m_MatchMessageBuffer.Size()<=0) return NULL;

	ODEList<tagGameMessageBuffer*>::iterator it=m_MatchMessageBuffer.Begin();

	return (*it);
}

void ClientData::RemoveFrontMatchMessageInBuffer()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);

	if (m_MatchMessageBuffer.Size()<=0) return;

	ODEList<tagGameMessageBuffer*>::iterator it=m_MatchMessageBuffer.Begin();

	tagGameMessageBuffer *pGameMessage = *it;

	ODE_SAFE_DELETE(pGameMessage);
	m_MatchMessageBuffer.PopFront();

}

void ClientData::SetGuaanDanMatchAwardListInfo( std::vector<pbproto::UserMatchHistory> pAwardLogInfo )
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	m_MatchAwardLogListInfo_GD.insert(m_MatchAwardLogListInfo_GD.end(),pAwardLogInfo.begin(),pAwardLogInfo.end());
}

std::vector<pbproto::UserMatchHistory> ClientData::GetGuanDanMatchAwardListInfo()
{
	return m_MatchAwardLogListInfo_GD;
}

void ClientData::ClearGuanDanMatchAwardLogListInfo()
{
	ODE_AUTO_LOCK_MUTEX(m_kMutex);
	if (m_MatchAwardLogListInfo_GD.size()>0)
	{
		for (std::vector<pbproto::UserMatchHistory>::iterator it=m_MatchAwardLogListInfo_GD.begin(); it!=m_MatchAwardLogListInfo_GD.end();)
		{
			it =m_MatchAwardLogListInfo_GD.erase(it);
		}
	}

	m_MatchAwardLogListInfo_GD.clear();
}

int ClientData::GetGuanDanMatchAwardLogListItemId()
{
	return 1;
}

void ClientData::SetGuanDanMatchAwardLogListItemId( int l_click_item_id )
{

}

void ClientData::setIsMatchGame_GD( bool show )
{
	m_isGuanDanGame=show;
}

bool ClientData::isMatchGame_GD()
{
	return m_isGuanDanGame;
}


void ClientData::setGameAvaliableIpAbdPort(const char* ip, int port)
{
	m_gameAvaliableIp = ip;
	m_gameAvaliablePort = port;
}

const char* ClientData::getGameAvaliableIp()
{
	return m_gameAvaliableIp.c_str();
}

int ClientData::getGameAvaliablePort()
{
	return m_gameAvaliablePort;
}

void ClientData::SetEnterMatchFailedInfo( long long iMatch, int iGameMode, int iGameRoom )
{
	m_oEnterMatchFailedInfo.id = iMatch;
	m_oEnterMatchFailedInfo.iGameId = iGameMode;
	m_oEnterMatchFailedInfo.iServerId = iGameRoom;
}

tagEnterMatchFailed* ClientData::GetEnterMatchFailedInfo()
{
	return &m_oEnterMatchFailedInfo;
}
