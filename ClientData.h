#ifndef _CLIENT_DATA_H_
#define _CLIENT_DATA_H_

#include "ODEEngine.h"
#include "ClientDataDef.h"
#include <string>
#include <map>
#include "lobby_bank_client_msg.h"
#include "BankInfoDef.h"
#include "lobbyConnectData.h"
#include "ClientServerMsg.h"
#include "GuanDanClientData.h"
#include "GuanDanData.h"
#include "msg_ClientMatchProto.h"
using namespace match;

class ClientData : public ODESingleton<ClientData>
{
public:
	ClientData();

	virtual ~ClientData();

	void SetUserID(ODEUInt64 u64UserId);

	ODEUInt64 GetUserID();

	void SetUserScore(ODEUInt64 u64Score);

	ODEUInt64 GetUserScore();

	void SetUserCoin2AwardNum(ODEUInt64 u64Coin2Award);

	ODEUInt64 GetUserCoin2AwardNum();

	void SetUserCompeteScore(ODEUInt64 u64CompeteScore);

	ODEUInt64 GetUserCompeteScore();

	void SetUserAwardTicketNum(ODEUInt64 u64AwardScore);

	ODEUInt64 GetUserAwardTicketNum();

	void SetUserGender(ODEChar8 cGender);

	ODEChar8 GetUserGender();
	//设置头像索引
	void SetUserHeadIndex(ODEUInt64 u64UserHeadIndex);
	//获取头像索引
	ODEUInt64 GetUserHeadIndex();

	void SetUserBuyHeadIndex(ODEUInt64 u64UserHeadIndex);
	ODEUInt64 GetUserBuyHeadIndex();

	void SetBankScore (long long score);
	long long GetBankScore ();

	void SetUserName(const ODEChar8* szUserName);
	void SetUserPassword(const ODEChar8* szPassword);

	ODEChar8* GetUserName(bool bNickname=false);
	ODEChar8* GetUserPassword() { return m_szPassword; }

	void SetUserPhoneRechargePoint(ODEInt32 i32Point);
	ODEInt32 GetUserPhoneRechargePoint();

	void SetSitDownErrorCode(ODEUInt32 cbErrorCode);
	ODEUInt32 GetSitDownErrorCode() {return m_uSitDownErrorCode;}

	//自定义开桌相关函数
	void SetPrivateRoomBaseMultiple(ODEInt32 nBaseMultiple);
	ODEInt32 GetPrivateRoomBaseMultiple();
	void SetPrivateRoomBaseAnte(ODEInt32 nBaseAnte);
	ODEInt32 GetPrivateRoomBaseAnte() {return m_i32PRoomBaseAnte;}
	void SetPrivateRoomMaxAnte(ODEInt32 nMaxAnte);
	ODEInt32 GetPrivateRoomMaxAnte() {return m_i32PRoomMaxAnte;}

	void SetCreatePrivateRoomErrorCode(ODEUInt32 cbErrorCode);
	ODEUInt32 GetCreatePrivateRoomErrorCode() {return m_u32CreatePRoomErrorCode;}

	void ClearCustomTableInfo();
	ODEList<tagCustomTableInfo*>* GetCustomTableInfoList() { return &m_listCustomTableInfo; }

	void SetLastLoginError(ODEInt32 i32ErrorCode);
	ODEInt32 GetLastLoginError();

	void SetLastRoomLoginError(ODEInt32 i32ErrorCode);
	ODEInt32 GetLastRoomLoginError();
	void SetLastRoomLoginErrorServerId(ODEInt32 i32ServerId);
	ODEInt32 GetLastRoomLoginErrorServerId();
	void SerLastRoomLoginErrorGameId(ODEInt32 i32GameId);
	ODEInt32 GetLastRoomLgoinErrorGameId();

	void SetLastRoomLoginErrorGameName (const char * name);
	char * GetLastRoomLoginErrorGameName (); 

	void SetUserSerialLoginTaskInfo(tagUserSerialLoginTaskInfo *pLoginTaskInfo);
	tagUserSerialLoginTaskInfo * GetUserSerialLoginTaskInfo() {return &m_UserSerialLoginTaskInfo;}

	ODEChar8 *GetGameTipPtr() { return m_szGameTip; }
	LobbyConnectData * GetLobbyConnectData () {return & m_lobbyConnectData;}
	LobbyBankClientAuthenSuccessRsp * getBankClientAuthenSuccessRsq() {return &m_LobbyBankInfoRsp;}
	LobbyBankClientAuthenReq * getBankerClientAuthenReq() {return &m_LobbyBankClientAuthenReq;}

	//玩家是否被踢出
	bool isKickout;

	bool isKey_back;

	//游戏消息缓冲
	void ClearGameMessageBuffer();
	void AddGameMessageToBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length);
	void RemoveFrontGameMessageInBuffer();
	tagGameMessageBuffer* GetFrontGameMessageInBuffer();

	void ClearGameInstantMessageBuffer();
	void AddGameInstantMessageToBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length);
	void RemoveFrontGameInstantMessageInBuffer();
	tagGameMessageBuffer* GetFrontGameInstantMessageInBuffer();

	void ClearDelayMessageBuffer();
	void AddMsgToDelayMessageBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length, ODEUInt32 u32DelayTime=0);
	ODEList<tagDelayMessageBuffer*>* GetDelayMessageBufferPtr() {return &m_DelayMessageBuffer;}

	void ClearLobbyMessageBuffer();
	void AddMsgToLobbyMessageBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length);
	ODEList<tagGameMessageBuffer*>* GetLobbyMessageBufferPtr() {return &m_LobbyMessageBuffer;}

	void ClearOnlyGameMessageBuffer();
	void AddMsgToOnlyGameMessageBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length);
	ODEList<tagGameMessageBuffer*>* GetOnlyGameMessageBufferPtr() {return &m_OnlyGameMessageBuffer;}
	tagGameMessageBuffer* GetFrontOnlyGameMessageInBuffer();
	void RemoveFrontOnlyGameMessageInBuffer();

	//比赛服游戏消息缓存
	void ClearMatchGameMessageBuffer();
	void AddMsgToMatchMessageBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length);
	tagGameMessageBuffer* GetFrontMatchMessageInBuffer();
	void RemoveFrontMatchMessageInBuffer();
	
	//每日任务
	void ClearUserDailyTaskInfo(bool bClearFinish=true);
	void SetUserDailyTaskInfo(tagUserDailyTaskInfo *pUserDailyTaskInfo);
	bool UpdateUserDailyTaskInfo(tagUpdateUserDailyTaskProgress *pTaskProgress);
	bool IsDailyTaskDataChange() {return m_bIsDailyTaskDataChange;}
	void SetDailyTaskDataChangeMark(bool bChange);
	ODEList<tagUserDailyTaskInfo*>* GetUserDailyTaskDoingList() { return &m_listUserDailyTaskDoing; }
	ODEList<tagUserDailyTaskInfo*>* GetUserDailyTaskFinishedList() { return &m_listUserDailyTaskFinished; }
	tagUserDailyTaskInfo *GetUserDailyTaskInfo(ODEInt64 i64UserTaskID);

	//保存最忌一次登录的房间的ip和端口号
	void setLastLoginIpAndPort(const ODEChar8 * ip, ODEInt32 port, ODEInt32 roomID);
	ODEChar8 * getLastLoginIp();
	ODEInt32 getLastLoginPort();
	ODEInt32 getLastLoginRoomID();

	void ClearGameMsgBuffer();

	void SetQuitGameClientAlert(bool bQuitGame) {m_bIsQuitGameClientAlert=bQuitGame;}
	bool IsQuitGameClientAlert() {return m_bIsQuitGameClientAlert;}

	void setIsInTongbiNiuniu(bool isInTongbiNiuniu) {m_isInTongbiNiuniu = isInTongbiNiuniu;}
	bool isInTongbiNiuniu() {return m_isInTongbiNiuniu;}

	void setCanEnterRoom(bool canEnterRoom) {m_canEnterRoom = canEnterRoom;}
	bool canEnterRoom() {return m_canEnterRoom;}

	void SetLotteryCount(ODEInt32 i32Count);
	ODEInt32 GetLotteryCount() {return m_i32LotteryCount;}

	void SetSysBroadcastMsgID(ODEInt32 i32MsgID);
	ODEInt32 GetSysBroadcastMsgID() {return m_i32SysBroadcastMsgID;}
	
	ODEList<tagLobbyBroadcastMsgItem*>* GetLobbyBroadcastMsgList() { return &m_lstLobbyBroadcastMsg; }

	void SetNicknameMark(bool bIsSet);
	bool IsSetNickname() {return m_bIsSetNickname;}
	void SetNickname(const ODEChar8* szNickname);
	ODEChar8* GetNickname() { return m_szNickname; }

	void SetLobbyPasspodVerifyErrorData(LobbyPasspodVerifyErrorRsp *pVerifyError);
	LobbyPasspodVerifyErrorRsp* GetLobbyPasspodVerifyErrorData() {return &m_LobyPasspodVerifyError;}
	void ResetDataWhenChangeAccount ();

	
	//彩票个数相关
	void setCaiPiaoCount(int count);
	int getCaiPiaoCount();

	//喇叭个数相关
	void setLabaCounts (int count);
	int getLabaCounts ();

	void setIp6AtomCounts (int counts);
	int getIp6AtomCounts ();

	void setIpadAtomCounts (int counts);
	int getIpadAtomCounts ();

	void setHongBaoCounts (int counts);
	int getHongBaoCounts ();

	//老虎机次数
	void setSlotCounts (int counts);
	int getSlotCounts ();

	void setSlotTargetIndex (int counts);
	int getSlotTargetIndex ();

	void setCanShowSlotPrize (bool l_canshowprize);

	bool getCanShowSlotPrize ();

	void setUserSerialNumbers (long long numbers);
	long long getUserSerailNumbers ();

	void SetGoldCardAvaliableTime (char * timeStr);
	char * GetGoldCardAvaliableTime ();

	//周年庆vip送积分次数
	void SetAnniversarySendTimes (int times);
	int GetAnniversarySendTimes ();

	ODE_SYNTHESIZE(ODEUInt32, m_u32HuaFeiPoint, HuaFeiPoint)

	//清空桌子列表信息
	void initTablePlayerBaseData();
	//清空桌子列表信息_majiang
	void ClearPUSRoomTableInfo();

	//AppStore充值记录相关
    //开始检测是否有没有发送的充值信息
    void checkUnsendPayData(bool showloading = false);
    //添加订单记录
    void  addPayData(AppStorePayStruct* data, bool needSave = true);
    //删除订单记录
    void  deletePayData(const char* orderno);
    //获取记录中没有请求的个数
    int   getPayCount();
    //获取第一条记录
    AppStorePayStruct* getFirstPayData();
    //把数据保存到本地
    void saveAppStorePayDataToFile();
    //从本地读取数据到缓存
    void parseAppStorePayDataToCash();
    //判断本地是否可以处理订单消息(在某些情况下，本地不能立即处理订单号，但不用着急，因为订单号此时已经保存到本地文件当中)
    void setCanAppStoreResolveOrder(bool enable);
    bool canAppStoreResolveOrder();


	//添加玩家桌子信息
	void addTablePlayerBaseData(int iUserId, unsigned char gender, unsigned short tableIndex, unsigned short tableNumExtra, char userStatus, int index);
	//添加玩家头像信息
	void RemoveUserHeadIndexInfo();
	void addUserHeadIndexInfo(int iUserid, int index);
	void addNewUserHeadIndexInfo(int iUserid, int index);
	UserHeadInfo* GetUserHeadIndexInfo(int userid);

	//根绝玩家id删除某个玩家桌子信息
	void deleteTabelPlayerBaseData(int userId);
	//更新玩家桌子信息
	void updateTablePlayerBaseData(int userId, unsigned short tableNum, unsigned short usTableNumExtra, char userStatus, int iHeadImgIndex);
	//根据玩家的id获取玩家的桌子信息
	LocalTablePlayerInfoDef* getTablePlayerBaseData(int userId);

	//添加玩家旧的桌子信息
	void addTableOldPlayerData(int userId, unsigned short tableIndex, unsigned short tableNumExtra ,int index);
	//删除第一个旧的玩家桌子信息
	void deleteTableOldPlayerData(bool needClean = true);
	//获取第一个旧的玩家信息
	LocalTbaleOldPlayerInfoDef* getTableOldPlayerData();
	//获取旧的玩家信息的个数
	int getTableOldPlayerCount();

	bool  getGameStatus();
	void setGameStatus(bool cStatus);


	bool  getFastGame();
	void setFastGame(bool is_fast);

	//是否是团团转场
	void setIsTuanTuan(bool show);
	bool isTuanTuan();
	//是否是比赛场
	void setIsMatchGame_GD(bool show);
	bool isMatchGame_GD();

	void SetNeedNewPlayerGuide(bool bNeed);
	bool IsNeedNewPlayerGuide();
	/*快速登录相关*/
	bool  getAgreeBasePoint();
	void setAgreeBasePoint(bool is_fast);

	int  getJoinTableId();
	void setJoinTableId(int table_id);

	int  getJoinTablePoint();
	void setJoinTablePoint(int table_id);

	bool  getEnoughScroce();
	void setEnoughScroce(bool score_can);

	/*快速登录相关end*/

	int  getJoinPwTableNum();
	void setJoinPwTableNum(int table_num);
	
	ODEInt32 getRoomIndex();
	void setRoomIndex( ODEInt32 room_index );

	void setLoginAgain(bool bAgain);
	bool isLoginAgain();

	//用户第一次安装的时候生成的设备号
	void checkDeviceCode();
	string getNewDeviceCode();

	int getPlayerCountWhoHasSitDown();

#ifdef SCORE_EXCHANGE_GIFT_MACRO
	//设置积分换奖活动信息
	GQActivityBaseInfoRsp* getScoreExchangeGiftBaseInfo() {return &m_gqActivityBaseInfoRsp;}
	void setScoreExchangeGiftBaseInfo(GQActivityBaseInfoRsp * baseInfo, int bufferLength);
	bool isNeedUpdateScoreExchangeGiftBaseData() {return m_needUpdateScoreExchangeBaseData;}
	void setNeedUpdateScoreExchangeGiftBaseData(bool need);

	GQActivityGetAwardRsp* getScoreExchangeGiftScoreInfo() {return &m_gqActivityGetAwardRsp;}
	void setScoreExchangeGiftScoreInfo(GQActivityGetAwardRsp* getInfo, int bufferLength);
	bool isNeedUpdateScoreExchangeGiftScoreData() {return m_needUpdateScoreExchangeScoreData;}
	void setNeedUpdateScoreExchangeGiftScoreData(bool need);

	bool isOpenScoreExchangeGift() {return m_isOpenScoreExchangeGift;}
	void setOpenScoreExchangeGift(bool open) {m_isOpenScoreExchangeGift = open;}

#endif // SCORE_EXCHANGE_GIFT_MACRO

	//自己是否是首充用户
	bool  isFirstCharge() {return m_isFirstCharge;}
	void setIsFirstCharge(bool firstCharge) {m_isFirstCharge = firstCharge;}

	//判断用户是否是VIP用户
	int  GetVipCustom ();
	void setIsVipCustom (int isVip);

	bool GetIsRefreshGetLobby ();
	void SetRefreshByLobby (bool bRefresh);

	/**
	* 统计充值相关内容 
	* 针对每种支付方式，保存了点击支付的次数、支付成功的次数、支付失败的次数、支付过程中点击返回按钮的次数以及支付过程中网络出错的次数
	* 保存文件的方式：关键字为 paytype+下划线+支付类型+下划线+玩家ID，
	* 对应的值为 支付次数+支付成功次数+支付失败次数+点击返回按钮次数+网络出错次数,数字之间使用分隔符分开，然后使用Base64加密
	*/

	/**
	* 获取充值统计数据，切换账号之后要调用一次
	*/
	void getLocalPayEventData();

	/**
	* 清空支付的次数(点击次数、成功次数、失败次数),发送成功一次之后，调用一次
	* @param payType 支付类型
	*/
	void clearPayEventCount(int payType);

	/**
	* 点击了一次支付按钮
	* @param payType 支付类型
	*/
	void addPayEventCount(int payType);

	/**
	* 获取点击了支付按钮的次数
	* @param payType 支付类型
	*/
	int getPayEventCount(int payType);

	/**
	* 支付成功了一次
	* @param payType 支付类型
	*/
	void addPaySuccessCount(int payType);

	/**
	* 获取支付成功的次数
	* @param payType 支付类型
	*/
	int getPaySuccessCount(int payType);

	/**
	* 支付失败了一次
	* @param payType 支付类型
	*/
	void addPayFailedCount(int payType);

	/**
	* 获取支付失败的次数
	* @param payType 支付类型
	*/
	int getPayFailedCount(int payType);

	/**
	* 支付时候点击返回按钮一次
	* @param payType 支付类型
	*/
	void addPayReturnCount(int payType);

	/**
	* 获取支付的时候点击返回按钮的次数
	* @param payType 支付类型
	*/
	int getPayReturnCount(int payType);

	/**
	* 支付时候网络错误
	* @param payType 支付类型
	*/
	void addPayNetErrorCount(int payType);

	/**
	* 获取支付的时候网络出错的次数
	* @param payType 支付类型
	*/
	int getPayNetErrorCount(int payType);

	/**
	* 保存缓存数据到本地文件，自动调用，不必主动调用
	*/
	void savePayEventCount(int payType);

	/**
	* 从本地文件读取数据到缓存，自动调用，不必主动调用
	*/
	void parsePayEventCount(int payType);

	/*** 统计充值相关内容 End   */

	//更新某个房间对应的人数
	void updatePeopleCountWithRoomID(int roomID, int peopleCount);
	int getPoepleCountWithRoomId(int roomID);

	//增加新的广播消息(专门用来保存系统消息)
	void addNewBroadcastMsg(GameBroadcastMsg* msg);
	//删除广播消息(专门用来保存系统消息)
	void deleteBroadcastMsg(int msgId);
	//获取第一条消息(专门用来保存系统消息)
	GameBroadcastMsg* getFistBroadcastMsg();
	//获取广播消息的条数(专门用来保存系统消息)
	int getBroadcastMsgCount();

	//增加新的广播消息(专门用来保存除系统消息外的其他消息)
	void addGameNewBroadcastMsg(GameBroadcastMsg* msg);
	//删除广播消息(专门用来保存除系统消息外的其他消息)
	void deleteGameBroadcastMsg(int msgId);
	//获取第一条消息(专门用来保存除系统消息外的其他消息)
	GameBroadcastMsg* getGameFistBroadcastMsg();
	//获取广播消息的条数(专门用来保存除系统消息外的其他消息)
	int getGameBroadcastMsgCount();

	//网络异常提示
	void setUnReceivedPackageCount(ODEInt32 iNum) {m_iUnReceivedPkg = iNum;}
	ODEInt32 getUnReceivedPackageCount(){return m_iUnReceivedPkg;}

	//更新大厅长连的端口和ip
	void setLobbyAlwaysConnectIpAndPort(const char* ip, int port) {strcpy(m_lobbyAlwaysConnectIP, ip); m_lobbyAlwaysConnectPort = port;}
	const char* getLobbyAlwaysConnectIp() {return m_lobbyAlwaysConnectIP;}
	int getLobbyAlwaysConnectPort() {return m_lobbyAlwaysConnectPort;}

	//更新从大厅传过来的设备号
	//void setDeviceId(const char* deviceId) {strcpy(m_lobbyDeviceId, deviceId);}
	//const char* getDeviceId() {return m_lobbyDeviceId;}
	CC_PROPERTY(std::string, m_deviceId, DeviceId);


	//游戏中记录账号是否在异地登陆
	void setAccountLoginNotSelf(bool notSelf);
	bool isAccountLoginNotSelf();

	//设置当前客户端在后台还是在前台的状态
	void setIsInForeground(bool foreground);
	//判断当前客户端是在后台还是在前台
	bool isInForeground();

	//游戏中记录网络状态
	void setNetWorkState(int state);
	int getNetWorkState();
	//游戏中记录网络是否断开连接
	void setNetWorkUnlink(bool unlink);
	bool isNetWorkUnLink();

	//是否可以点击返回按钮
	void SetCanGoBack(bool bCan){m_bCanGoBack = bCan;};
	bool IsCanGoBack(){return m_bCanGoBack;};

	//玩家登录成功之后需要发送自己的登录信息到服务器
	void setIsNeedSendLoginMessage(bool need);
	bool isNeedSendLoginMessage();

	//大厅是否是渠道包
	void setIsChannelPackage(bool isChannelPackage);
	bool isChannelPackage();

	//设置渠道ID
	void setChannelId(const char* channelId);
	const char* getChannelId();

	void setUpdateCurrentVersion(const char* currVersioin);
	const char* getUpdateCurrentVersion();

	//设置客户端更新的最低版本号
	void setUpdateLimitVersion(const char* limitVersion);
	const char* getUpdateLimitVersion();

	void setNeedSaveUpdateLink(bool need);
	bool isNeedSavaUpdateLink();

	 void setPayTypeForIPTV (int type);
	 int  getPayTypeForIPTV ();

	 void setPayMountForIPTV (int mount);
	 int getPayMountForIPTV ();

	 void setAlipayTypeForIPTV (int type);
	 int getAlipayTypeForIPTV ();



	//邮件相关
	void SetMailListInfo(tagLobbyPlayerMailListInfo *pMailInfo);
	tagLobbyPlayerMailListInfo* GetMailListInfo();
	void SetMailHasNewInfo(tagLobbyHasMailInfo* info);
	tagLobbyHasMailInfo* GetMailHasNewInfo();
	void SetNewMailInfo(sMail* pMail);
	sMail* GetNewMailInfo();

	//斗地主连胜累胜活动
	void SetTimesWonInfo(tagTimesWonInfo* pInfo);
	tagTimesWonInfo* GetTimesWonInfo(int iActivityType);

	//背包中金牌是否使用
	void setGoldCardBtnStatus(bool status);
	bool getGoldCardBtnStatus();

	const char* getExchangeOrderInfo();
	void  setExchangeOrderInfo(char* ordernum);

	//记录背包itemid
	void setBagListItemId( int item_id);
	int  getBagListItemId();
	void setBagListItemNum(int item_num);
	int getBagListItemNum();

	//玩家是否购买过头像
	void SetIsBuyedHeadImage(int isbuyed);
	int  GetIsBuyedHeadImage ();

	void SetHasSendAnniversaryCoinToday (bool isSend);
	bool GetHasSendAnniversaryCoinToday ();

	//玩家上次的游戏记录
	void SetLastGameRecordGameID (int gameID);
	int	 GetLastGameRecordGameID ();

	void SetLastGameRecordServerID (int serverID);
	int  GetLastGameRecordServerID ();

	void SetLastGameRecordTime (time_t serverID);
	time_t  GetLastGameRecordTime ();

	void SetGameTimesWonInfo( tagGameTimesWonInfo* info );
	tagGameTimesWonInfo* GetGameTimesWonInfo( int iActivityType );

	LobbyPersonalCenterInfoRsp * GetPersonalCenterInfo ();
	void SetLobbyPersonCenterInfo (LobbyPersonalCenterInfoRsp * info);

	LobbyRankingInfoRspData * GetRankingInfo ();
	void SetRankingInfo (LobbyRankingInfoRspData * info);

	void setUserGuidanceInfo (CSGuide2PCRspData * info);
	CSGuide2PCRspData * getUserGuidanceInfo ();

	void setMobileActiveNoticeInfo (tagSCMobileActiveNoticeRsp * rsp);
	tagSCMobileActiveNoticeRsp * GetMobileActiveNoticeInfo ();

	//一局赢5局活动
	void SetOneRoundGet5YuanActInfo(int type, long long TotalCash, long long challengeCash, long long expendCash, int bindStatus, long long progress2, 
	long long progress3, int coinTicket, string SpreadCode, string strMobile);
	tagOneRoundGet5YuanActInfo* GetOneRoundGet5YuanActInfo();
	void SetOneRoundGet5YuanUserType(int type, int bindStatus);

	//根根据配置文件中登录服的个数获取ip以及端口号
	void initRandomLogin();
	const char* getRandomLoginIp();
	int	getRandomLoginPort();

	//兑换码
	void AddExchangeCodeGetItem(tagExchangeCodeItem* info);
	std::vector<tagExchangeCodeItem*>* GetExchangeCodeGetItem();

	//异常退出
	void setExitNotNormalGameID (int gameid) ;
	void setExitNotNormalServerID (int serverID) ;
	void setExitNotNormalScore (long long score);

	long long getExitNotNormalScore ();
	int getExitNotNormalGameID ();
	int getExitNotNormalServerID ();

	//春节红包抽奖
	void setChunJieHuoDongAwardDetail (int pos, int values);
	int getChunJieHuoDongAwardDetail (int pos);
	int getChunJieHuoDongAwardSize ();
	void ResetChunJieHuoDongAwardDetail ();

	//登陆TOKEN
	void setLoginToken (char * token);
	char * getLoginToken ();

	//配置文件版本号
	void setConfigVersion (char * version);
	char * getConfigVersion ();

	void SetBreaklineConnectparam(int serip,int gameid,int entertime);

	int GetReConnectInfoSerIp();
	int GetReConnectInfoGameID();
    int GetReConnectInfoEnterTime();

	//皮肤设置
	void setSettintDownloadSkinPath (const char * skinPath);
	void setSettingDownloadSkinContentID (int contentID);

	char * getSettingDownloadSkinPath ();
	int	   getSettingDownloadSkinContentID ();

	void setGuanDanGetAwardString (const char * awardText);
	char * getGuanDanGetAwardString ();

	void setCurrentUserMedalsId (int MedalsID);
	int  getCurrentUserMedalsId ();

	void setCurrentUseMedalsRetCode (int code);
	int getCurrentUseMedalsRetCode ();

	void setIsInGuanDanGameScene (bool isGameScene);
	bool getIsInGuanDanGameScene ();

	void setIsGuideMode (bool guideMode);
	bool getIsGuideMode ();

	void setGuanDanGuideRewardCode (int code);
	int getGuanDanGuideRewardCode ();

	void setGuanDanGuideRewardCoin (int coin);
	int getGuanDanGuideRewardCoin ();
	
	//是否有新的邀请好友的记录
	void SetHasNewInviFriendsRecord(bool bHasNew);
	bool HasNewInviFriendsRecord();
	void AddInviteFriendsScoreRecord(tagInviteUserRemaindRecord* info);
	std::vector<tagInviteUserRemaindRecord*>* GetInviteFriendsScoreRecord();
	void ClearInviteFriendsScoreRecord();
	void AddInviteFriendsUserRecord(tagInviteUserInvitedUserRecord* info);
	std::vector<tagInviteUserInvitedUserRecord*>* GetInviteFriendsUserRecord();
	void ClearInviteFriendsUserRecord();
	void SetInviteFriendsLastReceivedUserRecordIndex(long long recordIndex);
	void SetInviteFriendsLastReceivedScoreRecordIndex(long long recordIndex);
	long long GetInviteFriendsLastReceivedUserRecordIndex();
	long long GetInviteFriendsLastReceivedScoreRecordIndex();

	//找回密码倒计时
	int GetFindPwdBackLastTime();
	int GetFindPwdBackCurrTime();
	void SetFindPwdBackLastTime(int time);
	void SetFindPwdBackCurrTime(int time);
    

	//是否需要发送智能卡号
	void setNeedSendCaCardNoToServer(bool enable);
	bool isNeedSendCaCardNoToServer();

	//掼蛋比赛场Start


	//比赛场登录
	void SetMatchRspError(ODEInt32 iError);
	ODEInt32 GetMatchRspError();

	//当前比赛的真正id
	void SetCurrGuanDanMatchId(long long id);
	long long GetCurrGuanDanMatchId();

	void AddGuanDanMatchSimpleInfo(tagMatchSimpleInfo* info);
	std::vector<tagMatchSimpleInfo*>* GetAllGuanDanMatchSimpleInfos();
	void ClearAllGuanDanMatchSimpleInfo();
	tagMatchSimpleInfo* GetGuanDanMatchSimpleInfo(long long matchID);
	std::vector<tagMatchSimpleInfo> GetCurrPageGuanDanMatchSimpleInfos(ODEInt32 iRows, ODEInt32 iCols, ODEInt32 iPageIndex);

	//已参与比赛的进度信息
	void AddPartInGuanDanMatchInfo(tagUserMatchInfo* info);
	std::vector<tagUserMatchInfo*>* GetPartInGuanDanMatchInfos();
	tagUserMatchInfo* GetPartInGuanDanMatchInfo( long long matchId);
	void ClearPartInGuanDanMatchInfo();

	//单个比赛的详细信息
	void SetGuanDanCurrMatchLayerDetailInfo(SCGetMatchInfoRsp* info);
	tagCurrMatchDetailInfo* GetGuanDanCurrMatchLayerDetailInfo();
	


	void SetLoginGuanDanMatchServerSuc(bool bSuc);
	bool IsLoginGuanDanMatchServerSuc();

	//记录所点击比赛场
	void SetGuanDanMatchGame_ID(ODEInt32 id);
	ODEInt32 GetGuanDanMatchGame_ID();

	//所有排行的奖励信息
	void AddAllGuanDanMatchAwardInfo( /*long long matchId, */ODEInt32 pos, std::string strAwardDes);
	bool HasGuanDanMatchAwardInfo(/*long long matchId*/);
	map<ODEInt32, std::vector<std::string> >* GetAllGuanDanMatchAwardInfo();
	void SetShowAllGuanDanAwardFromTop(bool bTop);
	bool IsShowAllGuanDanAwardFromTop();

	//游戏结束是获取到比赛场的排行榜
	void  setGuanDanMatchRankerListInfo(std::vector<RankUserInfo> l_toplist);  
	std::vector<RankUserInfo> *getGaunDanMatchRankerListInfo();

	//掼蛋比赛场单个比赛排行列表
	void AddGuanDanRankListInfo(int rank, std::string strUserName);
	void ClearGuanDanMatchRankList();
	map<int, string>* GetGuanDanMatchRankList();
	//掼蛋奖励排行
	void SetGuaanDanMatchAwardListInfo(std::vector<pbproto::UserMatchHistory> pAwardLogInfo);
	std::vector<pbproto::UserMatchHistory> GetGuanDanMatchAwardListInfo();
	void ClearGuanDanMatchAwardLogListInfo();

	int GetGuanDanMatchAwardLogListItemId();
	void SetGuanDanMatchAwardLogListItemId(int l_click_item_id);
	void ClearGuanDanMatchAwardList();
	//进入比赛场失败
	void SetEnterMatchFailedInfo(long long iMatch, int iGameMode, int iGameRoom);
	tagEnterMatchFailed* GetEnterMatchFailedInfo();

	//设置游戏可用的ip和端口
	void setGameAvaliableIpAbdPort(const char* ip, int port);
	const char* getGameAvaliableIp();
	int getGameAvaliablePort();
	//设置私人场状态
	void setIsPersonalMatch( bool show );
	bool isPersonalMatch();
	int IsNeedPassWord;
	//获取私人场桌子id
	void setPrivateTableID(int tableID);
	int getPrivateTableID();
	int m_tableId;
	//获取私人场桌子名称
	void setPrivatetableName(std::string table_name);
	std::string getPrivatetableName();
	std::string m_tablename;

private:
	ODEThread::Mutex m_kMutex;

private:
	tagEnterMatchFailed				m_oEnterMatchFailedInfo;
	//服务器返回的可用的房间的ip和端口
	string							m_gameAvaliableIp;
	int								m_gameAvaliablePort;

	ODEInt32  m_matchgame_id;
	//比赛服错误代码
	ODEInt32						m_i32MatchRspError;
	//比赛场基本信息
	std::vector<tagMatchSimpleInfo*> m_vecAllMatchSimpleInfos_GD;
	std::vector<tagUserMatchInfo*>   m_vecPartInMatchInfos_GD;

	tagCurrMatchDetailInfo			 m_currMatchDetailInfo_GD;
	bool							 m_bIsLoginMatchSuc_GD;
	std::vector<pbproto::UserMatchHistory>			m_MatchAwardLogListInfo_GD;

	//所有排行的奖励信息
	map<ODEInt32, std::vector<std::string> >  m_mapAllGuanDanAwardInfo;

	bool							m_bShowAllGuanDanAwardFromTop;
	map<int, string>				m_mapGuanDanMatchRankList;

	std::vector<RankUserInfo>	    m_GuanDanranker_info_list;

	ODEChar8			m_szUserName[NAME_LEN_LOCAL];			//用户名
	ODEChar8			m_szPassword[PASSWD_LEN_LOCAL];		//密码

	ODEUInt64			m_u64UserId;                    //用户ID
	ODEUInt64			m_u64Score;                     //用户银子
	ODEUInt64			m_u64Coin2Award;                //银券通
	ODEUInt64			m_u64CompeteScore;              //参赛券
	ODEUInt64			m_u64AwardTicketNum;            //奖品券
	ODEChar8			m_cGender;                      //用户性别

	ODEInt32			m_i32PhoneRechargePoint;		//话费点
	ODEInt32			m_i32LotteryCount;				//翻牌抽奖次数

	ODEInt32			m_i32PRoomBaseMultiple;			//私人场基础倍数
	ODEInt32			m_i32PRoomBaseAnte;				//私人场基础底注
	ODEInt32			m_i32PRoomMaxAnte;				//私人场最大底注

	ODEUInt32			m_uSitDownErrorCode;
	ODEUInt32			m_u32CreatePRoomErrorCode;

	std::string			m_kSelfHeadImagePath;

	ODEInt32			m_i32LastLoginError;
	ODEInt32			m_i32LastRoomLoginError;
	ODEInt32			m_i32LastRoomLoginErrorServerID;
	ODEInt32			m_i32LastRoomLoginErrorGameID;
	ODEChar8			m_szLastRoomLoginErrorGameName[40];
	
	ODEChar8			m_szGameTip[2048];

	//大厅长连接数据
	LobbyConnectData	m_lobbyConnectData;

	//大厅长连ip端口
	char				m_lobbyAlwaysConnectIP [16];
	int					m_lobbyAlwaysConnectPort;

	//从大厅获取的设备号
	char				m_lobbyDeviceId[33];

	ODEStringA			m_lastLoginIp;
	ODEInt32			m_lastLoginPort;
	ODEInt32			m_lastLoginRoomID;

	int									m_HeadImageIndex;				//头像索引

	//个人银行玩家身上的银子以及银行的存款
	LobbyBankClientAuthenSuccessRsp m_LobbyBankInfoRsp;
	//个人银行对身上银子以及银行存款操作的个人认证
	LobbyBankClientAuthenReq m_LobbyBankClientAuthenReq;

	// 自定义桌子信息列表
	ODEList<tagCustomTableInfo*>		m_listCustomTableInfo;	

	// 游戏消息缓冲： 缓冲那些有先后次序的消息，必须等某个游戏阶段完成后才响应的消息，比如缓冲里存储两个发牌和出牌消息，等发牌过程完成后才能处理出牌消息。
	ODEList<tagGameMessageBuffer*>		m_GameMessageBuffer;	
	// 游戏即时消息缓冲：缓冲那些可以即时处理的消息，比如像托管、催牌这样的。
	ODEList<tagGameMessageBuffer*>		m_GameInstantMessageBuffer;	
	// 延时消息：设定延后一段时间再处理的消息
	ODEList<tagDelayMessageBuffer*>		m_DelayMessageBuffer;	
	// 大厅游戏缓冲
	ODEList<tagGameMessageBuffer*>		m_LobbyMessageBuffer;	

	ODEList<tagGameMessageBuffer*>      m_OnlyGameMessageBuffer;
	//比赛服游戏消息缓存
	ODEList<tagGameMessageBuffer*>		m_MatchMessageBuffer;	

	tagUserSerialLoginTaskInfo			m_UserSerialLoginTaskInfo;

	// 每日任务信息
	bool								m_bIsDailyTaskDataChange;
	ODEList<tagUserDailyTaskInfo*>		m_listUserDailyTaskDoing;	
	ODEList<tagUserDailyTaskInfo*>		m_listUserDailyTaskFinished;
	
	bool								m_bIsQuitGameClientAlert;

	ODEInt32							m_i32SysBroadcastMsgID;
	ODEList<tagLobbyBroadcastMsgItem*>	m_lstLobbyBroadcastMsg;

	
	//是否可以点击房间按钮
	bool								m_canEnterRoom;

	//是否进行的是通比牛牛
	bool								m_isInTongbiNiuniu;


	//玩家在客户端游戏状态
	bool                                m_cGameStatus;

	//是否快速登录
	bool                                is_fastgame;

	//是否是在掼蛋团团转场次
	bool                                m_isTuanTuan;  

	//判断是否为掼蛋私人场
	bool                                m_isPersonalMatch;

	//是否是掼蛋比赛场
	bool                                m_isGuanDanGame;

	//是否需要弹出新手引导
	bool								m_bIsNeedNewPlayerGuide;

	//是否同意底注
	bool                          is_agree_basepoint;

	//桌子id
	int                             join_table_id;
	//桌子id
	int                             join_table_point;
	//加密房间id记录
	int                             join_pwtable_num;
	//身上积分是否够进入房间
	bool                          m_bHasEnoughScroce;

	//是否是断线重入
	bool                                m_bLoginAgain;

	long long						m_iCurrMatchId_GD;

	//玩家昵称
	bool								m_bIsSetNickname;
	ODEChar8							m_szNickname[NAME_LEN];

	//passpod验证失败回应
	LobbyPasspodVerifyErrorRsp			m_LobyPasspodVerifyError;

	//保存每个桌子的玩家基本信息，是否需看具体游戏而定
	list<LocalTablePlayerInfoDef*>	m_tablePlayerBaseInfo;

	//保存每个桌子玩家的头像信息
	list<UserHeadInfo *>  m_userheadindexinfo;
	// 
	//保存每个桌子玩家的旧的信息，处理之后立马移除掉
	vector<LocalTbaleOldPlayerInfoDef*> m_tablePlayerOldBaseInfo;
	//当前的room index
	ODEInt32 m_roomindex;

	//本地生成的唯一标志符，重新安装客户端的时候会重新生成
	string                              m_deviceCode;

	//根据配置文件中的登录服的个数获取ip和端口号
	int                                 m_randomLoginIndex;
	string                              m_randomLoginIp;
	int                                 m_randomLoginPort;

	//兑换码
	std::vector<tagExchangeCodeItem*>  m_vecExchangeCodeGetItems;

#ifdef SCORE_EXCHANGE_GIFT_MACRO

	//积分换奖品的基本缓存数据
	GQActivityBaseInfoRsp m_gqActivityBaseInfoRsp;
	bool				 m_needUpdateScoreExchangeBaseData;

	//积分换奖品得奖数据
	GQActivityGetAwardRsp m_gqActivityGetAwardRsp;
	bool                 m_needUpdateScoreExchangeScoreData;

	//针对个别有桌子列表的游戏，判断是否开启了积分换奖(如果不需要的话可以不用)
	bool				 m_isOpenScoreExchangeGift;
#endif // SCORE_EXCHANGE_GIFT_MACRO

	//保存房间对应的人数
	CCDictionary*					m_roomPeopleCountInfo;

	//游戏中缓存的广播消息(专门用来保存系统消息)
	ODEList<GameBroadcastMsg*>			m_broadcastMsgList;
	//游戏中缓存的广播消息(专门用来保存除了系统消息外的其他消息)
	ODEList<GameBroadcastMsg*>			m_broadcastGameMsgList;
	
	//是否是首充用户
	bool				m_isFirstCharge;

	//玩家身上彩票的个数
	int									m_caiPiaoCount;

	//玩家身上的喇叭个数
	int					m_labaCounts;

	//周年庆送VIP玩家积分次数
	int									m_AnniversarySendTimes;
	//春节活动玩家iphone6碎片数目
	int									m_HongbaoCounts;
	int									m_Ip6AtomCounts;
	int									m_IpadCounts;
	bool                                b_goldONOFF;

	////兑换得到的订单号，暂时先存这里
	string OrderID;

	//老虎机次数
	int									m_SlotCounts;

	int									m_slotindex;

	bool								m_canshowprizelayer; //是不是要显示奖励界面

	//未收到心跳返回包的个数
	ODEInt32			m_iUnReceivedPkg;

	//游戏中用来记录玩家是否账号在异地登陆
	bool							m_accountLoginNotSelf;

	//判断当前客户端在后台还是在前台
	bool							m_isForeground;

	//游戏中用来记录当前的网络状态(网络连接上)
	int								m_netWorkLinkState;
	//游戏中用来记录网络断开连接的状态
	bool							m_netWorkIsUnlink;

	//是否可以点击返回按钮
	bool				m_bCanGoBack;

	//玩家登录成功之后需要发送自己的登录信息到服务器
	bool							m_needSendLoginMessage;

	//大厅是否是渠道包
	bool							m_isChannelPackage;

	//设置渠道ID(游戏中使用游戏ID请从这里获取)
	string							m_channelId;

	//是否需要重新保存更新链接
	bool							m_needReSaveUpdateLink;

	char							m_channelDownloadCurrentVersion[16];
	char							m_channelDownloadLimitVersion[16];

	/************************************************************************/
	/*                 统计充值相关内容,数组索引对应你支付类型                      */
	/************************************************************************/
	//点击支付次数
	int m_payEventCount[50];
	//支付成功次数
	int m_paySuccessCount[50];
	//支付失败次数
	int m_payFailedCount[50];
	//点击返回按钮的次数
	int m_payReturnCount[50];
	//网络出错的次数
	int m_payNetErrorCount[50];

	CSGuide2PCRspData  m_userGuidanceInfo;

	tagSCMobileActiveNoticeRsp m_mobileActiveNoticeInfo;

	char								m_GoldCardAvaliableTime[128];

	tagOneRoundGet5YuanActInfo m_oOneRoundGet5YuanActInfo;

	//PC引导活动 用户活动标识 （可适用于其他活动）
	long long							m_userSerialNumbers;

	//邮件相关
	tagLobbyPlayerMailListInfo			m_UserMailListInfo;
	tagLobbyHasMailInfo					m_bHasMailForEachType;
	sMail								m_oNewMail;

	//斗地主连胜累胜活动
	tagTimesWonInfo						m_oTimesWonInfo[2];

	//背包btnid
	int				m_bagitem_id;
	int				m_bagitem_num;
	int									m_BuyHeadIndex;
	int									m_isBuyed;
	int									m_headimgID;
	int									m_LastGameID;
	int									m_LastServerID;
	int									m_LastExitNotNormalGameID;
	int									m_LastExitNotNormalServerID;
	long long							m_LastExitNotNormalScore;
	char								m_LoginToken[200];
	char								m_configVersion[32];
	int									m_ChunJieHuoDongAwardDetail[40];
	bool								m_isHasSendAnniversaryCoinToday;
	time_t								m_LastGameTime;
	//连胜累胜活动
	tagGameTimesWonInfo				m_oGameTimesWonInfo[2];
	//个人中心信息
	LobbyPersonalCenterInfoRsp personalCenterInfo;
	//排行榜信息
	LobbyRankingInfoRspData m_RankingInfo;

	//是否是VIP用户
	int				m_isVipCustom;

	//是否是第一次获取到银行信息
	bool			m_firstBankScore;

	bool			m_isRefreshCoinByLobby;
	//银行积分
	long long		m_bankScore;

	//断线重入消息 
	int server_Ip; // 服务器IP？
	int Game_ID;   // 掉线那局的游戏ID;
	int EnterTime;  //掉线那局进入桌子的时间

	//是否有新的邀请好友的记录
	bool							m_bHasNewInviteFriendsRecord;
	std::vector<tagInviteUserRemaindRecord*> m_vecInviteScoreRecords;
	std::vector<tagInviteUserInvitedUserRecord*> m_vecInviteUserRecords;
	long long						m_lLastReceivedUserRecordIndex;
	long long						m_lLastReceivedScoreRecordIndex;;
	//找回密码
	int								m_iFindPwdCutDownCurrTime;
	int								m_iFindPwdCutDownLastTime;

	//皮肤设置
	char							m_settingDownloadSkinPath[256];
	int								m_settingDownloadSkinContentID;

	char							m_guanDanGetAwardString[256];

	int								m_CurrentMedalsId;

	int								m_CurrentMedalsRetCode;

	bool							m_isGuideMode;

	int								m_guanDanGuideRewardCode;

	int								m_guanDanGuideRewardCoin;

	bool							m_isInGuanDanGameScene;

	int								m_PayTypeForIPTV;
	
	int								m_PayMountForTPTV;

	int								m_PayAlipayTypeForIPTV;

	//保存AppStore玩家充值的记录
    //订单号 & 链接信息
    vector<AppStorePayStruct*>          m_appstoreList;
	//针对AppStore充值异常的情况，当玩家已经付款但是客户端还没有收到成功的消息的时候，玩家再次启动游戏客户端会首先收到消息，但这个时候客户端一些内容还没有初始化，没法立即发送充值订单等信息给我们的服务器，所以会先把数据保存到本地文件当中，加上这个标示时是为了说明我们可以处理订单消息了
	bool                                m_appStoreCanResolveOrder;

	bool							m_needSendCaCardNo;
};

#define g_pkClientData ClientData::GetSingletonPtr()
#define g_pkLobbyConnectData g_pkClientData->GetLobbyConnectData ()
#define g_pkGuanDanGamePlayerData GuanDanGamePlayerData::GetSingletonPtr ()
#define g_pkGuanDanActiveData GuanDanGameActiveData::GetSingletonPtr ()

#endif //_CLIENT_DATA_H_