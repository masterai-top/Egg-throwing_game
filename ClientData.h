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
	//����ͷ������
	void SetUserHeadIndex(ODEUInt64 u64UserHeadIndex);
	//��ȡͷ������
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

	//�Զ��忪����غ���
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

	//����Ƿ��߳�
	bool isKickout;

	bool isKey_back;

	//��Ϸ��Ϣ����
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

	//��������Ϸ��Ϣ����
	void ClearMatchGameMessageBuffer();
	void AddMsgToMatchMessageBuffer(ODEInt32 nMsgID, ODEChar8 *buffer, ODEInt32 length);
	tagGameMessageBuffer* GetFrontMatchMessageInBuffer();
	void RemoveFrontMatchMessageInBuffer();
	
	//ÿ������
	void ClearUserDailyTaskInfo(bool bClearFinish=true);
	void SetUserDailyTaskInfo(tagUserDailyTaskInfo *pUserDailyTaskInfo);
	bool UpdateUserDailyTaskInfo(tagUpdateUserDailyTaskProgress *pTaskProgress);
	bool IsDailyTaskDataChange() {return m_bIsDailyTaskDataChange;}
	void SetDailyTaskDataChangeMark(bool bChange);
	ODEList<tagUserDailyTaskInfo*>* GetUserDailyTaskDoingList() { return &m_listUserDailyTaskDoing; }
	ODEList<tagUserDailyTaskInfo*>* GetUserDailyTaskFinishedList() { return &m_listUserDailyTaskFinished; }
	tagUserDailyTaskInfo *GetUserDailyTaskInfo(ODEInt64 i64UserTaskID);

	//�������һ�ε�¼�ķ����ip�Ͷ˿ں�
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

	
	//��Ʊ�������
	void setCaiPiaoCount(int count);
	int getCaiPiaoCount();

	//���ȸ������
	void setLabaCounts (int count);
	int getLabaCounts ();

	void setIp6AtomCounts (int counts);
	int getIp6AtomCounts ();

	void setIpadAtomCounts (int counts);
	int getIpadAtomCounts ();

	void setHongBaoCounts (int counts);
	int getHongBaoCounts ();

	//�ϻ�������
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

	//������vip�ͻ��ִ���
	void SetAnniversarySendTimes (int times);
	int GetAnniversarySendTimes ();

	ODE_SYNTHESIZE(ODEUInt32, m_u32HuaFeiPoint, HuaFeiPoint)

	//��������б���Ϣ
	void initTablePlayerBaseData();
	//��������б���Ϣ_majiang
	void ClearPUSRoomTableInfo();

	//AppStore��ֵ��¼���
    //��ʼ����Ƿ���û�з��͵ĳ�ֵ��Ϣ
    void checkUnsendPayData(bool showloading = false);
    //��Ӷ�����¼
    void  addPayData(AppStorePayStruct* data, bool needSave = true);
    //ɾ��������¼
    void  deletePayData(const char* orderno);
    //��ȡ��¼��û������ĸ���
    int   getPayCount();
    //��ȡ��һ����¼
    AppStorePayStruct* getFirstPayData();
    //�����ݱ��浽����
    void saveAppStorePayDataToFile();
    //�ӱ��ض�ȡ���ݵ�����
    void parseAppStorePayDataToCash();
    //�жϱ����Ƿ���Դ�������Ϣ(��ĳЩ����£����ز��������������ţ��������ż�����Ϊ�����Ŵ�ʱ�Ѿ����浽�����ļ�����)
    void setCanAppStoreResolveOrder(bool enable);
    bool canAppStoreResolveOrder();


	//������������Ϣ
	void addTablePlayerBaseData(int iUserId, unsigned char gender, unsigned short tableIndex, unsigned short tableNumExtra, char userStatus, int index);
	//������ͷ����Ϣ
	void RemoveUserHeadIndexInfo();
	void addUserHeadIndexInfo(int iUserid, int index);
	void addNewUserHeadIndexInfo(int iUserid, int index);
	UserHeadInfo* GetUserHeadIndexInfo(int userid);

	//�������idɾ��ĳ�����������Ϣ
	void deleteTabelPlayerBaseData(int userId);
	//�������������Ϣ
	void updateTablePlayerBaseData(int userId, unsigned short tableNum, unsigned short usTableNumExtra, char userStatus, int iHeadImgIndex);
	//������ҵ�id��ȡ��ҵ�������Ϣ
	LocalTablePlayerInfoDef* getTablePlayerBaseData(int userId);

	//�����Ҿɵ�������Ϣ
	void addTableOldPlayerData(int userId, unsigned short tableIndex, unsigned short tableNumExtra ,int index);
	//ɾ����һ���ɵ����������Ϣ
	void deleteTableOldPlayerData(bool needClean = true);
	//��ȡ��һ���ɵ������Ϣ
	LocalTbaleOldPlayerInfoDef* getTableOldPlayerData();
	//��ȡ�ɵ������Ϣ�ĸ���
	int getTableOldPlayerCount();

	bool  getGameStatus();
	void setGameStatus(bool cStatus);


	bool  getFastGame();
	void setFastGame(bool is_fast);

	//�Ƿ�������ת��
	void setIsTuanTuan(bool show);
	bool isTuanTuan();
	//�Ƿ��Ǳ�����
	void setIsMatchGame_GD(bool show);
	bool isMatchGame_GD();

	void SetNeedNewPlayerGuide(bool bNeed);
	bool IsNeedNewPlayerGuide();
	/*���ٵ�¼���*/
	bool  getAgreeBasePoint();
	void setAgreeBasePoint(bool is_fast);

	int  getJoinTableId();
	void setJoinTableId(int table_id);

	int  getJoinTablePoint();
	void setJoinTablePoint(int table_id);

	bool  getEnoughScroce();
	void setEnoughScroce(bool score_can);

	/*���ٵ�¼���end*/

	int  getJoinPwTableNum();
	void setJoinPwTableNum(int table_num);
	
	ODEInt32 getRoomIndex();
	void setRoomIndex( ODEInt32 room_index );

	void setLoginAgain(bool bAgain);
	bool isLoginAgain();

	//�û���һ�ΰ�װ��ʱ�����ɵ��豸��
	void checkDeviceCode();
	string getNewDeviceCode();

	int getPlayerCountWhoHasSitDown();

#ifdef SCORE_EXCHANGE_GIFT_MACRO
	//���û��ֻ������Ϣ
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

	//�Լ��Ƿ����׳��û�
	bool  isFirstCharge() {return m_isFirstCharge;}
	void setIsFirstCharge(bool firstCharge) {m_isFirstCharge = firstCharge;}

	//�ж��û��Ƿ���VIP�û�
	int  GetVipCustom ();
	void setIsVipCustom (int isVip);

	bool GetIsRefreshGetLobby ();
	void SetRefreshByLobby (bool bRefresh);

	/**
	* ͳ�Ƴ�ֵ������� 
	* ���ÿ��֧����ʽ�������˵��֧���Ĵ�����֧���ɹ��Ĵ�����֧��ʧ�ܵĴ�����֧�������е�����ذ�ť�Ĵ����Լ�֧���������������Ĵ���
	* �����ļ��ķ�ʽ���ؼ���Ϊ paytype+�»���+֧������+�»���+���ID��
	* ��Ӧ��ֵΪ ֧������+֧���ɹ�����+֧��ʧ�ܴ���+������ذ�ť����+����������,����֮��ʹ�÷ָ����ֿ���Ȼ��ʹ��Base64����
	*/

	/**
	* ��ȡ��ֵͳ�����ݣ��л��˺�֮��Ҫ����һ��
	*/
	void getLocalPayEventData();

	/**
	* ���֧���Ĵ���(����������ɹ�������ʧ�ܴ���),���ͳɹ�һ��֮�󣬵���һ��
	* @param payType ֧������
	*/
	void clearPayEventCount(int payType);

	/**
	* �����һ��֧����ť
	* @param payType ֧������
	*/
	void addPayEventCount(int payType);

	/**
	* ��ȡ�����֧����ť�Ĵ���
	* @param payType ֧������
	*/
	int getPayEventCount(int payType);

	/**
	* ֧���ɹ���һ��
	* @param payType ֧������
	*/
	void addPaySuccessCount(int payType);

	/**
	* ��ȡ֧���ɹ��Ĵ���
	* @param payType ֧������
	*/
	int getPaySuccessCount(int payType);

	/**
	* ֧��ʧ����һ��
	* @param payType ֧������
	*/
	void addPayFailedCount(int payType);

	/**
	* ��ȡ֧��ʧ�ܵĴ���
	* @param payType ֧������
	*/
	int getPayFailedCount(int payType);

	/**
	* ֧��ʱ�������ذ�ťһ��
	* @param payType ֧������
	*/
	void addPayReturnCount(int payType);

	/**
	* ��ȡ֧����ʱ�������ذ�ť�Ĵ���
	* @param payType ֧������
	*/
	int getPayReturnCount(int payType);

	/**
	* ֧��ʱ���������
	* @param payType ֧������
	*/
	void addPayNetErrorCount(int payType);

	/**
	* ��ȡ֧����ʱ���������Ĵ���
	* @param payType ֧������
	*/
	int getPayNetErrorCount(int payType);

	/**
	* ���滺�����ݵ������ļ����Զ����ã�������������
	*/
	void savePayEventCount(int payType);

	/**
	* �ӱ����ļ���ȡ���ݵ����棬�Զ����ã�������������
	*/
	void parsePayEventCount(int payType);

	/*** ͳ�Ƴ�ֵ������� End   */

	//����ĳ�������Ӧ������
	void updatePeopleCountWithRoomID(int roomID, int peopleCount);
	int getPoepleCountWithRoomId(int roomID);

	//�����µĹ㲥��Ϣ(ר����������ϵͳ��Ϣ)
	void addNewBroadcastMsg(GameBroadcastMsg* msg);
	//ɾ���㲥��Ϣ(ר����������ϵͳ��Ϣ)
	void deleteBroadcastMsg(int msgId);
	//��ȡ��һ����Ϣ(ר����������ϵͳ��Ϣ)
	GameBroadcastMsg* getFistBroadcastMsg();
	//��ȡ�㲥��Ϣ������(ר����������ϵͳ��Ϣ)
	int getBroadcastMsgCount();

	//�����µĹ㲥��Ϣ(ר�����������ϵͳ��Ϣ���������Ϣ)
	void addGameNewBroadcastMsg(GameBroadcastMsg* msg);
	//ɾ���㲥��Ϣ(ר�����������ϵͳ��Ϣ���������Ϣ)
	void deleteGameBroadcastMsg(int msgId);
	//��ȡ��һ����Ϣ(ר�����������ϵͳ��Ϣ���������Ϣ)
	GameBroadcastMsg* getGameFistBroadcastMsg();
	//��ȡ�㲥��Ϣ������(ר�����������ϵͳ��Ϣ���������Ϣ)
	int getGameBroadcastMsgCount();

	//�����쳣��ʾ
	void setUnReceivedPackageCount(ODEInt32 iNum) {m_iUnReceivedPkg = iNum;}
	ODEInt32 getUnReceivedPackageCount(){return m_iUnReceivedPkg;}

	//���´��������Ķ˿ں�ip
	void setLobbyAlwaysConnectIpAndPort(const char* ip, int port) {strcpy(m_lobbyAlwaysConnectIP, ip); m_lobbyAlwaysConnectPort = port;}
	const char* getLobbyAlwaysConnectIp() {return m_lobbyAlwaysConnectIP;}
	int getLobbyAlwaysConnectPort() {return m_lobbyAlwaysConnectPort;}

	//���´Ӵ������������豸��
	//void setDeviceId(const char* deviceId) {strcpy(m_lobbyDeviceId, deviceId);}
	//const char* getDeviceId() {return m_lobbyDeviceId;}
	CC_PROPERTY(std::string, m_deviceId, DeviceId);


	//��Ϸ�м�¼�˺��Ƿ�����ص�½
	void setAccountLoginNotSelf(bool notSelf);
	bool isAccountLoginNotSelf();

	//���õ�ǰ�ͻ����ں�̨������ǰ̨��״̬
	void setIsInForeground(bool foreground);
	//�жϵ�ǰ�ͻ������ں�̨������ǰ̨
	bool isInForeground();

	//��Ϸ�м�¼����״̬
	void setNetWorkState(int state);
	int getNetWorkState();
	//��Ϸ�м�¼�����Ƿ�Ͽ�����
	void setNetWorkUnlink(bool unlink);
	bool isNetWorkUnLink();

	//�Ƿ���Ե�����ذ�ť
	void SetCanGoBack(bool bCan){m_bCanGoBack = bCan;};
	bool IsCanGoBack(){return m_bCanGoBack;};

	//��ҵ�¼�ɹ�֮����Ҫ�����Լ��ĵ�¼��Ϣ��������
	void setIsNeedSendLoginMessage(bool need);
	bool isNeedSendLoginMessage();

	//�����Ƿ���������
	void setIsChannelPackage(bool isChannelPackage);
	bool isChannelPackage();

	//��������ID
	void setChannelId(const char* channelId);
	const char* getChannelId();

	void setUpdateCurrentVersion(const char* currVersioin);
	const char* getUpdateCurrentVersion();

	//���ÿͻ��˸��µ���Ͱ汾��
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



	//�ʼ����
	void SetMailListInfo(tagLobbyPlayerMailListInfo *pMailInfo);
	tagLobbyPlayerMailListInfo* GetMailListInfo();
	void SetMailHasNewInfo(tagLobbyHasMailInfo* info);
	tagLobbyHasMailInfo* GetMailHasNewInfo();
	void SetNewMailInfo(sMail* pMail);
	sMail* GetNewMailInfo();

	//��������ʤ��ʤ�
	void SetTimesWonInfo(tagTimesWonInfo* pInfo);
	tagTimesWonInfo* GetTimesWonInfo(int iActivityType);

	//�����н����Ƿ�ʹ��
	void setGoldCardBtnStatus(bool status);
	bool getGoldCardBtnStatus();

	const char* getExchangeOrderInfo();
	void  setExchangeOrderInfo(char* ordernum);

	//��¼����itemid
	void setBagListItemId( int item_id);
	int  getBagListItemId();
	void setBagListItemNum(int item_num);
	int getBagListItemNum();

	//����Ƿ����ͷ��
	void SetIsBuyedHeadImage(int isbuyed);
	int  GetIsBuyedHeadImage ();

	void SetHasSendAnniversaryCoinToday (bool isSend);
	bool GetHasSendAnniversaryCoinToday ();

	//����ϴε���Ϸ��¼
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

	//һ��Ӯ5�ֻ
	void SetOneRoundGet5YuanActInfo(int type, long long TotalCash, long long challengeCash, long long expendCash, int bindStatus, long long progress2, 
	long long progress3, int coinTicket, string SpreadCode, string strMobile);
	tagOneRoundGet5YuanActInfo* GetOneRoundGet5YuanActInfo();
	void SetOneRoundGet5YuanUserType(int type, int bindStatus);

	//�����������ļ��е�¼���ĸ�����ȡip�Լ��˿ں�
	void initRandomLogin();
	const char* getRandomLoginIp();
	int	getRandomLoginPort();

	//�һ���
	void AddExchangeCodeGetItem(tagExchangeCodeItem* info);
	std::vector<tagExchangeCodeItem*>* GetExchangeCodeGetItem();

	//�쳣�˳�
	void setExitNotNormalGameID (int gameid) ;
	void setExitNotNormalServerID (int serverID) ;
	void setExitNotNormalScore (long long score);

	long long getExitNotNormalScore ();
	int getExitNotNormalGameID ();
	int getExitNotNormalServerID ();

	//���ں���齱
	void setChunJieHuoDongAwardDetail (int pos, int values);
	int getChunJieHuoDongAwardDetail (int pos);
	int getChunJieHuoDongAwardSize ();
	void ResetChunJieHuoDongAwardDetail ();

	//��½TOKEN
	void setLoginToken (char * token);
	char * getLoginToken ();

	//�����ļ��汾��
	void setConfigVersion (char * version);
	char * getConfigVersion ();

	void SetBreaklineConnectparam(int serip,int gameid,int entertime);

	int GetReConnectInfoSerIp();
	int GetReConnectInfoGameID();
    int GetReConnectInfoEnterTime();

	//Ƥ������
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
	
	//�Ƿ����µ�������ѵļ�¼
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

	//�һ����뵹��ʱ
	int GetFindPwdBackLastTime();
	int GetFindPwdBackCurrTime();
	void SetFindPwdBackLastTime(int time);
	void SetFindPwdBackCurrTime(int time);
    

	//�Ƿ���Ҫ�������ܿ���
	void setNeedSendCaCardNoToServer(bool enable);
	bool isNeedSendCaCardNoToServer();

	//�走������Start


	//��������¼
	void SetMatchRspError(ODEInt32 iError);
	ODEInt32 GetMatchRspError();

	//��ǰ����������id
	void SetCurrGuanDanMatchId(long long id);
	long long GetCurrGuanDanMatchId();

	void AddGuanDanMatchSimpleInfo(tagMatchSimpleInfo* info);
	std::vector<tagMatchSimpleInfo*>* GetAllGuanDanMatchSimpleInfos();
	void ClearAllGuanDanMatchSimpleInfo();
	tagMatchSimpleInfo* GetGuanDanMatchSimpleInfo(long long matchID);
	std::vector<tagMatchSimpleInfo> GetCurrPageGuanDanMatchSimpleInfos(ODEInt32 iRows, ODEInt32 iCols, ODEInt32 iPageIndex);

	//�Ѳ�������Ľ�����Ϣ
	void AddPartInGuanDanMatchInfo(tagUserMatchInfo* info);
	std::vector<tagUserMatchInfo*>* GetPartInGuanDanMatchInfos();
	tagUserMatchInfo* GetPartInGuanDanMatchInfo( long long matchId);
	void ClearPartInGuanDanMatchInfo();

	//������������ϸ��Ϣ
	void SetGuanDanCurrMatchLayerDetailInfo(SCGetMatchInfoRsp* info);
	tagCurrMatchDetailInfo* GetGuanDanCurrMatchLayerDetailInfo();
	


	void SetLoginGuanDanMatchServerSuc(bool bSuc);
	bool IsLoginGuanDanMatchServerSuc();

	//��¼�����������
	void SetGuanDanMatchGame_ID(ODEInt32 id);
	ODEInt32 GetGuanDanMatchGame_ID();

	//�������еĽ�����Ϣ
	void AddAllGuanDanMatchAwardInfo( /*long long matchId, */ODEInt32 pos, std::string strAwardDes);
	bool HasGuanDanMatchAwardInfo(/*long long matchId*/);
	map<ODEInt32, std::vector<std::string> >* GetAllGuanDanMatchAwardInfo();
	void SetShowAllGuanDanAwardFromTop(bool bTop);
	bool IsShowAllGuanDanAwardFromTop();

	//��Ϸ�����ǻ�ȡ�������������а�
	void  setGuanDanMatchRankerListInfo(std::vector<RankUserInfo> l_toplist);  
	std::vector<RankUserInfo> *getGaunDanMatchRankerListInfo();

	//�走�������������������б�
	void AddGuanDanRankListInfo(int rank, std::string strUserName);
	void ClearGuanDanMatchRankList();
	map<int, string>* GetGuanDanMatchRankList();
	//�走��������
	void SetGuaanDanMatchAwardListInfo(std::vector<pbproto::UserMatchHistory> pAwardLogInfo);
	std::vector<pbproto::UserMatchHistory> GetGuanDanMatchAwardListInfo();
	void ClearGuanDanMatchAwardLogListInfo();

	int GetGuanDanMatchAwardLogListItemId();
	void SetGuanDanMatchAwardLogListItemId(int l_click_item_id);
	void ClearGuanDanMatchAwardList();
	//���������ʧ��
	void SetEnterMatchFailedInfo(long long iMatch, int iGameMode, int iGameRoom);
	tagEnterMatchFailed* GetEnterMatchFailedInfo();

	//������Ϸ���õ�ip�Ͷ˿�
	void setGameAvaliableIpAbdPort(const char* ip, int port);
	const char* getGameAvaliableIp();
	int getGameAvaliablePort();
	//����˽�˳�״̬
	void setIsPersonalMatch( bool show );
	bool isPersonalMatch();
	int IsNeedPassWord;
	//��ȡ˽�˳�����id
	void setPrivateTableID(int tableID);
	int getPrivateTableID();
	int m_tableId;
	//��ȡ˽�˳���������
	void setPrivatetableName(std::string table_name);
	std::string getPrivatetableName();
	std::string m_tablename;

private:
	ODEThread::Mutex m_kMutex;

private:
	tagEnterMatchFailed				m_oEnterMatchFailedInfo;
	//���������صĿ��õķ����ip�Ͷ˿�
	string							m_gameAvaliableIp;
	int								m_gameAvaliablePort;

	ODEInt32  m_matchgame_id;
	//�������������
	ODEInt32						m_i32MatchRspError;
	//������������Ϣ
	std::vector<tagMatchSimpleInfo*> m_vecAllMatchSimpleInfos_GD;
	std::vector<tagUserMatchInfo*>   m_vecPartInMatchInfos_GD;

	tagCurrMatchDetailInfo			 m_currMatchDetailInfo_GD;
	bool							 m_bIsLoginMatchSuc_GD;
	std::vector<pbproto::UserMatchHistory>			m_MatchAwardLogListInfo_GD;

	//�������еĽ�����Ϣ
	map<ODEInt32, std::vector<std::string> >  m_mapAllGuanDanAwardInfo;

	bool							m_bShowAllGuanDanAwardFromTop;
	map<int, string>				m_mapGuanDanMatchRankList;

	std::vector<RankUserInfo>	    m_GuanDanranker_info_list;

	ODEChar8			m_szUserName[NAME_LEN_LOCAL];			//�û���
	ODEChar8			m_szPassword[PASSWD_LEN_LOCAL];		//����

	ODEUInt64			m_u64UserId;                    //�û�ID
	ODEUInt64			m_u64Score;                     //�û�����
	ODEUInt64			m_u64Coin2Award;                //��ȯͨ
	ODEUInt64			m_u64CompeteScore;              //����ȯ
	ODEUInt64			m_u64AwardTicketNum;            //��Ʒȯ
	ODEChar8			m_cGender;                      //�û��Ա�

	ODEInt32			m_i32PhoneRechargePoint;		//���ѵ�
	ODEInt32			m_i32LotteryCount;				//���Ƴ齱����

	ODEInt32			m_i32PRoomBaseMultiple;			//˽�˳���������
	ODEInt32			m_i32PRoomBaseAnte;				//˽�˳�������ע
	ODEInt32			m_i32PRoomMaxAnte;				//˽�˳�����ע

	ODEUInt32			m_uSitDownErrorCode;
	ODEUInt32			m_u32CreatePRoomErrorCode;

	std::string			m_kSelfHeadImagePath;

	ODEInt32			m_i32LastLoginError;
	ODEInt32			m_i32LastRoomLoginError;
	ODEInt32			m_i32LastRoomLoginErrorServerID;
	ODEInt32			m_i32LastRoomLoginErrorGameID;
	ODEChar8			m_szLastRoomLoginErrorGameName[40];
	
	ODEChar8			m_szGameTip[2048];

	//��������������
	LobbyConnectData	m_lobbyConnectData;

	//��������ip�˿�
	char				m_lobbyAlwaysConnectIP [16];
	int					m_lobbyAlwaysConnectPort;

	//�Ӵ�����ȡ���豸��
	char				m_lobbyDeviceId[33];

	ODEStringA			m_lastLoginIp;
	ODEInt32			m_lastLoginPort;
	ODEInt32			m_lastLoginRoomID;

	int									m_HeadImageIndex;				//ͷ������

	//��������������ϵ������Լ����еĴ��
	LobbyBankClientAuthenSuccessRsp m_LobbyBankInfoRsp;
	//�������ж����������Լ����д������ĸ�����֤
	LobbyBankClientAuthenReq m_LobbyBankClientAuthenReq;

	// �Զ���������Ϣ�б�
	ODEList<tagCustomTableInfo*>		m_listCustomTableInfo;	

	// ��Ϸ��Ϣ���壺 ������Щ���Ⱥ�������Ϣ�������ĳ����Ϸ�׶���ɺ����Ӧ����Ϣ�����绺����洢�������ƺͳ�����Ϣ���ȷ��ƹ�����ɺ���ܴ��������Ϣ��
	ODEList<tagGameMessageBuffer*>		m_GameMessageBuffer;	
	// ��Ϸ��ʱ��Ϣ���壺������Щ���Լ�ʱ�������Ϣ���������йܡ����������ġ�
	ODEList<tagGameMessageBuffer*>		m_GameInstantMessageBuffer;	
	// ��ʱ��Ϣ���趨�Ӻ�һ��ʱ���ٴ������Ϣ
	ODEList<tagDelayMessageBuffer*>		m_DelayMessageBuffer;	
	// ������Ϸ����
	ODEList<tagGameMessageBuffer*>		m_LobbyMessageBuffer;	

	ODEList<tagGameMessageBuffer*>      m_OnlyGameMessageBuffer;
	//��������Ϸ��Ϣ����
	ODEList<tagGameMessageBuffer*>		m_MatchMessageBuffer;	

	tagUserSerialLoginTaskInfo			m_UserSerialLoginTaskInfo;

	// ÿ��������Ϣ
	bool								m_bIsDailyTaskDataChange;
	ODEList<tagUserDailyTaskInfo*>		m_listUserDailyTaskDoing;	
	ODEList<tagUserDailyTaskInfo*>		m_listUserDailyTaskFinished;
	
	bool								m_bIsQuitGameClientAlert;

	ODEInt32							m_i32SysBroadcastMsgID;
	ODEList<tagLobbyBroadcastMsgItem*>	m_lstLobbyBroadcastMsg;

	
	//�Ƿ���Ե�����䰴ť
	bool								m_canEnterRoom;

	//�Ƿ���е���ͨ��ţţ
	bool								m_isInTongbiNiuniu;


	//����ڿͻ�����Ϸ״̬
	bool                                m_cGameStatus;

	//�Ƿ���ٵ�¼
	bool                                is_fastgame;

	//�Ƿ������走����ת����
	bool                                m_isTuanTuan;  

	//�ж��Ƿ�Ϊ�走˽�˳�
	bool                                m_isPersonalMatch;

	//�Ƿ����走������
	bool                                m_isGuanDanGame;

	//�Ƿ���Ҫ������������
	bool								m_bIsNeedNewPlayerGuide;

	//�Ƿ�ͬ���ע
	bool                          is_agree_basepoint;

	//����id
	int                             join_table_id;
	//����id
	int                             join_table_point;
	//���ܷ���id��¼
	int                             join_pwtable_num;
	//���ϻ����Ƿ񹻽��뷿��
	bool                          m_bHasEnoughScroce;

	//�Ƿ��Ƕ�������
	bool                                m_bLoginAgain;

	long long						m_iCurrMatchId_GD;

	//����ǳ�
	bool								m_bIsSetNickname;
	ODEChar8							m_szNickname[NAME_LEN];

	//passpod��֤ʧ�ܻ�Ӧ
	LobbyPasspodVerifyErrorRsp			m_LobyPasspodVerifyError;

	//����ÿ�����ӵ���һ�����Ϣ���Ƿ��迴������Ϸ����
	list<LocalTablePlayerInfoDef*>	m_tablePlayerBaseInfo;

	//����ÿ��������ҵ�ͷ����Ϣ
	list<UserHeadInfo *>  m_userheadindexinfo;
	// 
	//����ÿ��������ҵľɵ���Ϣ������֮�������Ƴ���
	vector<LocalTbaleOldPlayerInfoDef*> m_tablePlayerOldBaseInfo;
	//��ǰ��room index
	ODEInt32 m_roomindex;

	//�������ɵ�Ψһ��־�������°�װ�ͻ��˵�ʱ�����������
	string                              m_deviceCode;

	//���������ļ��еĵ�¼���ĸ�����ȡip�Ͷ˿ں�
	int                                 m_randomLoginIndex;
	string                              m_randomLoginIp;
	int                                 m_randomLoginPort;

	//�һ���
	std::vector<tagExchangeCodeItem*>  m_vecExchangeCodeGetItems;

#ifdef SCORE_EXCHANGE_GIFT_MACRO

	//���ֻ���Ʒ�Ļ�����������
	GQActivityBaseInfoRsp m_gqActivityBaseInfoRsp;
	bool				 m_needUpdateScoreExchangeBaseData;

	//���ֻ���Ʒ�ý�����
	GQActivityGetAwardRsp m_gqActivityGetAwardRsp;
	bool                 m_needUpdateScoreExchangeScoreData;

	//��Ը����������б����Ϸ���ж��Ƿ����˻��ֻ���(�������Ҫ�Ļ����Բ���)
	bool				 m_isOpenScoreExchangeGift;
#endif // SCORE_EXCHANGE_GIFT_MACRO

	//���淿���Ӧ������
	CCDictionary*					m_roomPeopleCountInfo;

	//��Ϸ�л���Ĺ㲥��Ϣ(ר����������ϵͳ��Ϣ)
	ODEList<GameBroadcastMsg*>			m_broadcastMsgList;
	//��Ϸ�л���Ĺ㲥��Ϣ(ר�������������ϵͳ��Ϣ���������Ϣ)
	ODEList<GameBroadcastMsg*>			m_broadcastGameMsgList;
	
	//�Ƿ����׳��û�
	bool				m_isFirstCharge;

	//������ϲ�Ʊ�ĸ���
	int									m_caiPiaoCount;

	//������ϵ����ȸ���
	int					m_labaCounts;

	//��������VIP��һ��ִ���
	int									m_AnniversarySendTimes;
	//���ڻ���iphone6��Ƭ��Ŀ
	int									m_HongbaoCounts;
	int									m_Ip6AtomCounts;
	int									m_IpadCounts;
	bool                                b_goldONOFF;

	////�һ��õ��Ķ����ţ���ʱ�ȴ�����
	string OrderID;

	//�ϻ�������
	int									m_SlotCounts;

	int									m_slotindex;

	bool								m_canshowprizelayer; //�ǲ���Ҫ��ʾ��������

	//δ�յ��������ذ��ĸ���
	ODEInt32			m_iUnReceivedPkg;

	//��Ϸ��������¼����Ƿ��˺�����ص�½
	bool							m_accountLoginNotSelf;

	//�жϵ�ǰ�ͻ����ں�̨������ǰ̨
	bool							m_isForeground;

	//��Ϸ��������¼��ǰ������״̬(����������)
	int								m_netWorkLinkState;
	//��Ϸ��������¼����Ͽ����ӵ�״̬
	bool							m_netWorkIsUnlink;

	//�Ƿ���Ե�����ذ�ť
	bool				m_bCanGoBack;

	//��ҵ�¼�ɹ�֮����Ҫ�����Լ��ĵ�¼��Ϣ��������
	bool							m_needSendLoginMessage;

	//�����Ƿ���������
	bool							m_isChannelPackage;

	//��������ID(��Ϸ��ʹ����ϷID��������ȡ)
	string							m_channelId;

	//�Ƿ���Ҫ���±����������
	bool							m_needReSaveUpdateLink;

	char							m_channelDownloadCurrentVersion[16];
	char							m_channelDownloadLimitVersion[16];

	/************************************************************************/
	/*                 ͳ�Ƴ�ֵ�������,����������Ӧ��֧������                      */
	/************************************************************************/
	//���֧������
	int m_payEventCount[50];
	//֧���ɹ�����
	int m_paySuccessCount[50];
	//֧��ʧ�ܴ���
	int m_payFailedCount[50];
	//������ذ�ť�Ĵ���
	int m_payReturnCount[50];
	//�������Ĵ���
	int m_payNetErrorCount[50];

	CSGuide2PCRspData  m_userGuidanceInfo;

	tagSCMobileActiveNoticeRsp m_mobileActiveNoticeInfo;

	char								m_GoldCardAvaliableTime[128];

	tagOneRoundGet5YuanActInfo m_oOneRoundGet5YuanActInfo;

	//PC����� �û����ʶ �����������������
	long long							m_userSerialNumbers;

	//�ʼ����
	tagLobbyPlayerMailListInfo			m_UserMailListInfo;
	tagLobbyHasMailInfo					m_bHasMailForEachType;
	sMail								m_oNewMail;

	//��������ʤ��ʤ�
	tagTimesWonInfo						m_oTimesWonInfo[2];

	//����btnid
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
	//��ʤ��ʤ�
	tagGameTimesWonInfo				m_oGameTimesWonInfo[2];
	//����������Ϣ
	LobbyPersonalCenterInfoRsp personalCenterInfo;
	//���а���Ϣ
	LobbyRankingInfoRspData m_RankingInfo;

	//�Ƿ���VIP�û�
	int				m_isVipCustom;

	//�Ƿ��ǵ�һ�λ�ȡ��������Ϣ
	bool			m_firstBankScore;

	bool			m_isRefreshCoinByLobby;
	//���л���
	long long		m_bankScore;

	//����������Ϣ 
	int server_Ip; // ������IP��
	int Game_ID;   // �����Ǿֵ���ϷID;
	int EnterTime;  //�����Ǿֽ������ӵ�ʱ��

	//�Ƿ����µ�������ѵļ�¼
	bool							m_bHasNewInviteFriendsRecord;
	std::vector<tagInviteUserRemaindRecord*> m_vecInviteScoreRecords;
	std::vector<tagInviteUserInvitedUserRecord*> m_vecInviteUserRecords;
	long long						m_lLastReceivedUserRecordIndex;
	long long						m_lLastReceivedScoreRecordIndex;;
	//�һ�����
	int								m_iFindPwdCutDownCurrTime;
	int								m_iFindPwdCutDownLastTime;

	//Ƥ������
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

	//����AppStore��ҳ�ֵ�ļ�¼
    //������ & ������Ϣ
    vector<AppStorePayStruct*>          m_appstoreList;
	//���AppStore��ֵ�쳣�������������Ѿ�����ǿͻ��˻�û���յ��ɹ�����Ϣ��ʱ������ٴ�������Ϸ�ͻ��˻������յ���Ϣ�������ʱ��ͻ���һЩ���ݻ�û�г�ʼ����û���������ͳ�ֵ��������Ϣ�����ǵķ����������Ի��Ȱ����ݱ��浽�����ļ����У����������ʾʱ��Ϊ��˵�����ǿ��Դ�������Ϣ��
	bool                                m_appStoreCanResolveOrder;

	bool							m_needSendCaCardNo;
};

#define g_pkClientData ClientData::GetSingletonPtr()
#define g_pkLobbyConnectData g_pkClientData->GetLobbyConnectData ()
#define g_pkGuanDanGamePlayerData GuanDanGamePlayerData::GetSingletonPtr ()
#define g_pkGuanDanActiveData GuanDanGameActiveData::GetSingletonPtr ()

#endif //_CLIENT_DATA_H_