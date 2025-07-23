#include "BreakLineReconnectionHint.h"
#include "LobbyAssistScene.h"
#include "LobbyDownloadSounds.h"


BreakLineReconnectionHint::BreakLineReconnectionHint():ODUILayerModalExt<BreakLineReconnectionHint>("BreakLine_Reconnect")
{
	b_createSc = false;
	UIInitDelegate(BreakLineReconnectionHint,OnCancel);
	UIInitDelegate(BreakLineReconnectionHint,OnYes);
}

BreakLineReconnectionHint::~BreakLineReconnectionHint()
{

}

bool BreakLineReconnectionHint::init()
{
	if(!b_createSc)
	{
		OnCreateSc();
	}
	return ODUILayerModalExt::init();
}

void BreakLineReconnectionHint::OnActive(const ODUIUserDataPtr& spData)
{
	
}

void BreakLineReconnectionHint::OnCreateSc()
{
	b_createSc = true;
	setScale(ui_main_scale);
	CCScale9Sprite * m_pkPanel = CCScale9Sprite::createWithSpriteFrameName ("alert_background.png", CCRect (100, 100, 2, 2));
	m_pkPanel->setPreferredSize (CCSizeMake (743.0f, 483.0f));
	m_pkPanel->setPosition(ccp (ui_w (0.5), ui_h (0.5f)));
	addChild(m_pkPanel);
	
	CCLabelTTF* Title = CCLabelTTF::create(TT("UIText_LobbyLottery_dadoudou_use_Title"),TTF_NAME,ODEFloor(36));
	Title ->setPosition(ccp(m_pkPanel->getContentSize().width/2,m_pkPanel->getContentSize().height-(36)));
	m_pkPanel->addChild(Title);


	ConnetHit = CCLabelTTF::create(TT("BreakLine_connect_hint"),TTF_NAME,ODEFloor(26),CCSizeMake(653,140),kCCTextAlignmentLeft,kCCVerticalTextAlignmentTop);
	ConnetHit->setAnchorPoint(ccp(0.0f,1.0f));
	ConnetHit->setPosition(ccp(47,361));
	ConnetHit->setColor(ccc3(167,168,168));
	m_pkPanel->addChild(ConnetHit);
	CCLabelTTF * connetHint1 = CCLabelTTF::create(TT("BreakLine_connect_hint1"),TTF_NAME,ODEFloor(26));
	connetHint1->setAnchorPoint(ccp(0.0f,0.5f));
	connetHint1->setPosition(ccp(47,165));
	connetHint1->setColor(ccc3(167,168,168));
	m_pkPanel->addChild(connetHint1);

	CCScale9Sprite * backgroundCancel = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel->setOpacity (0);
	CCScale9Sprite * backgroundCancel2 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel2->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	CCSprite * logo = CCSprite::createWithSpriteFrameName ("input_frame_2.png");
	logo->setOpacity (0);
	NormalButtonWithText * m_cancelBtn = ODE_NEW NormalButtonWithText(backgroundCancel, backgroundCancel2, logo, TT ("UIText_LoginCancel"));
	m_cancelBtn->setPosition (ccp (m_pkPanel->boundingBox ().getMidX () - m_cancelBtn->getContentSize ().width / 2, m_pkPanel->boundingBox ().getMinY () + 10 + m_cancelBtn->getContentSize ().height / 2));
	AddWidget("setting_cancel", m_cancelBtn);
	m_cancelBtn->SetTextWithColor (TT ("UIText_LoginCancel"), ccc3 (0xEA, 0xEA, 0xEA));
	UILinkDelegate(m_cancelBtn, OnCancel);

	CCScale9Sprite * backgroundCancel3 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel3->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel3->setOpacity (0);
	CCScale9Sprite * backgroundCancel4 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel4->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel4->setRotationY (180.0f);
	CCSprite * logo2 = CCSprite::createWithSpriteFrameName ("input_frame_2.png");
	logo2->setOpacity (0);
	NormalButtonWithText * m_confirmBtn = ODE_NEW NormalButtonWithText(backgroundCancel3, backgroundCancel4, logo2, TT ("enter_AGame"));
	m_confirmBtn->setPosition (ccp (m_pkPanel->boundingBox ().getMidX () + m_confirmBtn->getContentSize ().width / 2, m_pkPanel->boundingBox ().getMinY () + 10 + m_confirmBtn->getContentSize ().height / 2));
	AddWidget("setting_confirm", m_confirmBtn);
	m_confirmBtn->SetTextWithColor (TT ("enter_AGame"), ccc3 (0x6B, 0xEA, 0x83));
	UILinkDelegate(m_confirmBtn, OnYes);

}

void BreakLineReconnectionHint::SetReConnectParameter(int quiciTime,int GameText,int RomText)
{
    char GameName[128]={0};
	char RomName[128]={0};

	sprintf(GameName,"NewLobby_GameID_%d",GameText);
	sprintf(RomName,"NewLobby_RoomID_%d",RomText);

	m_lastGameID = GameText;
	m_lastServerID = RomText;

	ptime = quiciTime;
    
	time_t rawtime = ptime; 
	struct tm * timeinfo; 
	time ( &rawtime ); 
	timeinfo = localtime ( &rawtime ); 
    int time1 = timeinfo->tm_hour;
	int time2 = timeinfo->tm_min;

	GameID = GameText;

	char QTime[1024] ={0};
	CCLOG ("NewLobby_GameID_%d", GameText);
	CCLOG ("NewLobby_RoomID_%d", RomText);
	if(strcmp (GetConfig (GameName), "none") != 0 && strcmp (GetConfig (RomName), "none") != 0)
    {

  	sprintf(QTime,TT("BreakLine_connect_hint"),time1,time2,GetConfig (GameName),GetConfig (RomName));
  	ConnetHit->setString(QTime);

	CCLog("%s", GetConfig (GameName));
	CCLog("%s", GetConfig (RomName));
 	sprintf(QTime,TT("BreakLine_connect_hint"),time1,time2,GetConfig (GameName),GetConfig (RomName));
	CCLog("%s",QTime);
 	ConnetHit->setString(QTime);

	}
}

void BreakLineReconnectionHint::OnDeactive(const ODUIUserDataPtr& spData)
{

}

void BreakLineReconnectionHint::StartGameInAndroid(int Gameindex)
{
	LobbyGameInfoItemForChannel * channelInfo = g_pkLobbyConnectData->getGameListInfo (Gameindex);
	CCLOG ("[ssssssssssssssss], %s %s", __FUNCTION__, "start game.");

	ODEChar8 url[164] = {0};
	ODEChar8 gamePlayed[100] = {0};
	ODEChar8 packagename[32] = {0};
	ODEChar8 classname[64] = {0};
	ODEChar8 insertFileName[25] = {0};

	strncpy (packagename, channelInfo->GamePackageName, sizeof (channelInfo->GamePackageName));
	strncpy (classname, channelInfo->ActivtyClassName, sizeof (channelInfo->ActivtyClassName));
	strncpy (insertFileName, channelInfo->InsertPackName, sizeof (channelInfo->InsertPackName));
	sprintf (gamePlayed, "NewLobby_GameItems%d_PlayedTimes", Gameindex);

	ODEUInt32 leastTimes = 0;
	ODEUInt32 times = g_pSaveData->ReadParam (gamePlayed, leastTimes);
	g_pSaveData->WriteParam(gamePlayed, times + 1);
	g_pSaveData->Save();

	ODEList< LobbyGameInfoItemForChannel * >::iterator GameIterator = g_pkLobbyConnectData->getGameChannelList ()->Begin();
	ODEList< LobbyGameInfoItemForChannel * >::iterator GameIteratorPos = GameIterator;

	while (GameIterator != g_pkLobbyConnectData->getGameChannelList ()->End ())
	{
		if ((*GameIterator)->nGameID == Gameindex)
		{
			GameIterator ++;
			continue;
		}

		stopGameAlreadyStart ((*GameIterator)->GamePackageName);
		GameIterator ++;
	}

	ODEChar8 userIdBuffer[15] = {0};
	sprintf(userIdBuffer, "%llu", g_pkClientData->GetUserID());
	ODEChar8 userScoreBuffer[15] = {0};
	sprintf(userScoreBuffer, "%lld", g_pkClientData->GetUserScore());
	ODEChar8 coin2AwardBuffer[15] = {0};
	sprintf(coin2AwardBuffer, "%lld", g_pkClientData->GetUserCoin2AwardNum());
	ODEChar8 competeScoreBuffer[15] = {0};
	sprintf(competeScoreBuffer, "%lld", g_pkClientData->GetUserCompeteScore());
	ODEChar8 awardTicketNumBuffer[15] = {0};
	sprintf(awardTicketNumBuffer, "%lld", g_pkClientData->GetUserAwardTicketNum());
	ODEChar8 genderBuffer[5] = {0};
	sprintf(genderBuffer, "%d", g_pkClientData->GetUserGender());
	ODEChar8 phoneRechargePointBuffer[15] = {0};
	sprintf(phoneRechargePointBuffer, "%d", g_pkClientData->GetUserPhoneRechargePoint());
	ODEChar8 siteIdBuffer[15] = {0};
	ODEInt32 currSiteId = g_pSaveData->ReadParam("default_site_id", ODEUInt32(0));
	sprintf(siteIdBuffer, "%d", currSiteId);
	//CCUserDefault * defaultUserData = CCUserDefault::sharedUserDefault(); 
	string currChannelId = g_pkClientData->getChannelId ();
	ODEChar8 lotteryCountBuffer[15] = {0};
	sprintf(lotteryCountBuffer, "%d", g_pkClientData->GetLotteryCount());
	ODEChar8 thirdPartyLogin[15] = {0};
	sprintf(thirdPartyLogin, "%d", g_pkGuanDanGame->m_bLoginThirdParty ? ODEUInt32(1) : ODEUInt32(0));
	ODEChar8 connectIP[16] = {0};
	sprintf (connectIP, "%s", g_pkLobbyConnectData->GetConnectIP ());
	ODEChar8 connectPort[16] = {0};
	sprintf (connectPort, "%d", g_pkLobbyConnectData->GetConnectPort ());
	ODEChar8 speacialAvatar[5] = {0};
	sprintf (speacialAvatar, "%d", g_pkClientData->GetUserHeadIndex ());
	ODEChar8 soundSettingPath[128] = {0};
	ODEChar8 soundSettingFlags[6] = {0};
	ODEChar8 lastGameID[16] = {0};
	sprintf (lastGameID, "%d", m_lastGameID);
	ODEChar8 lastServerID[16] = {0};
	sprintf (lastServerID, "%d", m_lastServerID);

	ODEList < LobbyDownloadContentRspData * > * downloadList = NULL;
	downloadList = g_pkLobbyConnectData->getDownloadContentList ();
	if (downloadList != NULL)
	{
		int setContentID = g_pkLobbyConnectData->getDownloadContentSettingConfig (Gameindex);

		if (setContentID == 0 || setContentID == Gameindex)
		{
			sprintf (soundSettingPath, "%s", "");
		}
		else
		{
			ODEList< LobbyDownloadContentRspData * >::iterator it = downloadList->Begin();
			ODEList< LobbyDownloadContentRspData * >::iterator pos = it;
			while (it != downloadList->End ())
			{
				if ((*it)->nGameID == Gameindex && (*it)->nContentType == DOWNLOADCONTENT_TYPE_SOUND && (*it)->nDownloadContentID == setContentID)
				{
					sprintf (soundSettingPath, "%s", JniHelpGetSettingPath ((*it)->nDownloadContentID,(*it)->szContentDownloadLinks, (*it)->szContentVersion).c_str ());
				}
				it ++;
			}
		}
	}

	sprintf (soundSettingFlags, "%d", strcmp (soundSettingPath, "") == 0 ? 0 : 1);

	ODEChar8 isChannelPack[6] = {0};
	sprintf (isChannelPack, "%d", atoi (TT ("IsChannelPack")));

	ODEChar8 channelRate[10] = {0};
	sprintf (channelRate, "%d", g_pkLobbyConnectData->GetChannelExchangeRate ());
	passLoginInfo(g_pkClientData->GetUserName(), g_pkClientData->GetUserName(true), g_pkClientData->GetUserPassword(), userIdBuffer, userScoreBuffer, coin2AwardBuffer,
		competeScoreBuffer, awardTicketNumBuffer, genderBuffer, phoneRechargePointBuffer, siteIdBuffer, currChannelId.c_str(), 
		lotteryCountBuffer, thirdPartyLogin, connectIP, connectPort, speacialAvatar, soundSettingFlags, soundSettingPath, isChannelPack, channelRate, lastGameID, lastServerID);


	startSingleGame (packagename, classname);
}

void BreakLineReconnectionHint::StartGameInIOS()
{
	g_pLayerManager->PopPopUpLayer();
	//NewLobby* PkNewLobby = (NewLobby*)g_pLayerManager->GetLayer("newLobby");
	//PkNewLobby->LobbyReLoginInIOS(m_lastGameID, m_lastServerID);
	// 			{
	// 				InstallInnerGame (insertFileName);
	// 				//schedule(schedule_selector(LobbyGameButton::checkIsAvilible), 1.5f);
	// 				return ;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			//ChangeGameState (GAME_DOWNLOAD);
	// 		}
	// 	}
	// 	g_pkGuanDanGame->m_bInnerGameStart = true;
}

UIImplementDelegate(BreakLineReconnectionHint,OnCancel,kWidget,u32State)
{
	if(u32State==ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopPopUpLayer();
	}
}

UIImplementDelegate(BreakLineReconnectionHint,OnYes,kWidget,u32State)
{
	if(u32State==ODUIWidget::RELEASED)
	{
		//NewLobby* PkNewLobby = (NewLobby*)g_pLayerManager->GetLayer("newLobby");
#if (GAME_START_IN_LOBBY == 0)	
		g_pLayerManager->PopPopUpLayer();
        StartGameInAndroid(GameID);
#else
		StartGameInIOS();
#endif
		//g_pLayerManager->PopLayer();		
	}
}