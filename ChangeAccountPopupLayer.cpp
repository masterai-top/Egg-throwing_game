#include "ChangeAccountPopupLayer.h"
#include "LobbyAssistScene.h"
#include "LobbyReward.h"
#include "LobbySetting.h"
#include "LobbyLogin.h"
#include "LobbyActive.h"
#include "ChangeHeadImage.h"
#include "Lobbybrowsing.h"
//#include "ClientData.h"
//#include "LobbyChargeMenu.h"
//#include "LobbyPersonalCenter.h"

/**************************************************************************
Copyright:ODAO
 
Author: 
 
Date:   2014-10-22
 
Description: 弹出框
 
**************************************************************************/

//bool ChangeAccountPopupLayer::m_bCreateScene = false;

ChangeAccountPopupLayer::ChangeAccountPopupLayer () : ODUILayerModalExt<ChangeAccountPopupLayer>("ChangeAccountPopupLayer")
	,m_bCreateScene(false)
	, m_ContentMessageStart(NULL)
	, m_ContentMessageEnding(NULL)
	, m_ContentMessageEnding2(NULL)
{
	m_kOnFadeIn.Set(this, &ChangeAccountPopupLayer::OnFadeIn);
	m_kOnFadeOut.Set(this, &ChangeAccountPopupLayer::OnFadeOut);

	UIInitDelegate(ChangeAccountPopupLayer, OnClose);
	UIInitDelegate(ChangeAccountPopupLayer, OnQuit);
	UIInitDelegate(ChangeAccountPopupLayer, OnGetaward);
}

ChangeAccountPopupLayer::~ChangeAccountPopupLayer()
{
	term ();
	m_bCreateScene = false;
}

bool ChangeAccountPopupLayer::init ()
{
	return ODUILayerModalExt<ChangeAccountPopupLayer>::init();
}

void ChangeAccountPopupLayer::OnActive(const ODUIUserDataPtr& spData)
{
	removeCreateData ();

	if (!m_bCreateScene)
		createScene ();

	g_pkNetworkHelper->SendGetPersonalCenterInfo ();

	g_pkNetworkHelper->SendLoginInfoRequest ();

}

void ChangeAccountPopupLayer::createScene ()
{
	m_bCreateScene = true;

	setScale(ui_main_scale);
	
	CCLayerColor* layer = CCLayerColor::create(ccc4(0x00, 0x00, 0x00, 0x3F), ui_w (1.0f), ui_h (1.0f));
	layer->setScale (1 / ui_main_scale);
	addChild (layer);

	m_pkPanel = CCScale9Sprite::createWithSpriteFrameName ("alert_background.png", CCRect (100, 100, 2, 2));
	m_pkPanel->setPreferredSize (CCSizeMake (752.0f, 518.0f));
	addChild(m_pkPanel);
	m_pkPanel->setPosition(ccp (ui_w (0.5), ui_h (0.5f)));    //把图片放到屏幕的中心位置

	CCLabelTTF * m_titleTex = CCLabelTTF::create(TT("TipTitle"), TTF_NAME, ODEFloorf(LOBBY_MAX_TTF_SIZE * g_f32ScaleHD));
	m_titleTex->setPosition ((ccp (m_pkPanel->boundingBox ().getMidX (), m_pkPanel->boundingBox ().getMaxY () - 42)));
	addChild (m_titleTex);

	createQuitContent ();

	CCSprite* close = CCSprite::createWithSpriteFrameName("center_no.png");
	CCScale9Sprite * background = CCScale9Sprite::createWithSpriteFrameName ("top_bar_background.png");
	background->setPreferredSize (CCSizeMake (60, 60));
	background->setOpacity (0);
	CCScale9Sprite * background2 = CCScale9Sprite::createWithSpriteFrameName ("top_bar_background.png");
	background2->setPreferredSize (background->getContentSize ());

	NormalButton* pkCloseBtn = ODE_NEW NormalButton(background, background2, close);
	pkCloseBtn->setPosition (ccp (m_pkPanel->boundingBox ().getMaxX () - pkCloseBtn->getContentSize ().width,m_titleTex->getPositionY ()));
	pkCloseBtn->setContentSize(pkCloseBtn->getContentSize() * 2);
	UILinkDelegate (pkCloseBtn, OnClose);
	pkCloseBtn->setContentSize(pkCloseBtn->getContentSize() * 2);
	pkCloseBtn->SetContentTouchSize (75.0f, 75.0f);
	AddWidget("kCloseBtn", pkCloseBtn);
	pkCloseBtn->setContentSize(pkCloseBtn->getContentSize() * 2);

	CCScale9Sprite * backgroundCancel = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel->setOpacity (0);
	CCScale9Sprite * backgroundCancel2 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel2->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	CCSprite * logo2 = CCSprite::createWithSpriteFrameName ("input_frame_2.png");
	logo2->setOpacity (0);
	NormalButtonWithText * m_quitBtn = ODE_NEW NormalButtonWithText(backgroundCancel, backgroundCancel2, logo2, TT ("UIText_LoginAccept"));
	m_quitBtn->setPosition (ccp (m_pkPanel->boundingBox ().getMidX () - m_quitBtn->getContentSize ().width / 2, m_pkPanel->boundingBox ().getMinY () + 10 + m_quitBtn->getContentSize ().height / 2));
	AddWidget("setting_cancel", m_quitBtn);
	m_quitBtn->SetTextWithColor (TT ("UIText_Receivereward"),  ccc3 (0x6B, 0xEA, 0x83));
	UILinkDelegate(m_quitBtn, OnGetaward);

	CCScale9Sprite * backgroundCancel3 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel3->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel3->setOpacity (0);
	CCScale9Sprite * backgroundCancel4 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel4->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel4->setRotationY (180.0f);
	CCSprite * logo = CCSprite::createWithSpriteFrameName ("input_frame_2.png");
	logo2->setOpacity (0);
	NormalButtonWithText * m_getawardBtn = ODE_NEW NormalButtonWithText(backgroundCancel3, backgroundCancel4, logo, TT ("UIText_LoginCancel"));
	m_getawardBtn->setPosition (ccp (m_pkPanel->boundingBox ().getMidX () + m_getawardBtn->getContentSize ().width / 2, m_pkPanel->boundingBox ().getMinY () + 10 + m_getawardBtn->getContentSize ().height / 2));
	AddWidget("setting_confirm", m_getawardBtn);
	m_getawardBtn->SetTextWithColor (TT ("UITextSettlementExit"), ccc3 (0xEA, 0xEA, 0xEA));
	UILinkDelegate(m_getawardBtn, OnQuit);

	CCSprite * m_line2 = CCSprite::createWithSpriteFrameName ("alert_line2.png");
	m_line2->setFlipY (true);
	m_line2->setScaleY (89 / m_line2->getContentSize ().height);
	m_line2->setPosition (ccp (m_pkPanel->boundingBox ().getMidX (), m_pkPanel->boundingBox ().getMinY () + 8 + m_quitBtn->getContentSize ().height / 2));
	addChild (m_line2);

	CCSprite * m_line1 = CCSprite::createWithSpriteFrameName ("alert_line_1.png");
	m_line1->setScaleX ((m_pkPanel->getContentSize ().width - 16) / m_line1->getContentSize ().width);
	m_line1->setPosition (ccp (m_pkPanel->boundingBox ().getMidX (), m_line2->boundingBox ().getMaxY ()));
	addChild (m_line1);
}

void ChangeAccountPopupLayer::createQuitContent ()
{
	m_QuitMessageTitleStart = CCLabelTTF::create(TT("Playerinformation0"), TTF_NAME, ODEFloorf(LOBBY_MAX_TTF_SIZE * g_f32ScaleHD));
	m_QuitMessageTitleStart->setAnchorPoint (ccp (0.0f, 0.5f));
	m_QuitMessageTitleStart->setPosition (ccp (m_pkPanel->boundingBox ().getMinX () + 70, m_pkPanel->boundingBox ().getMidY () + 130));
	addChild (m_QuitMessageTitleStart);

	m_QuitMessageTitleAccount = CCLabelTTF::create(g_pkClientData->GetUserName (), TTF_NAME, ODEFloorf(LOBBY_MAX_TTF_SIZE * g_f32ScaleHD));

	if (m_QuitMessageTitleAccount->getContentSize ().width >= 360)
	{
		m_QuitMessageTitleAccount = CCLabelTTF::create(g_pkClientData->GetUserName(), TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
	}

	m_QuitMessageTitleAccount->setAnchorPoint (ccp (0.0f, 0.5f));
	m_QuitMessageTitleAccount->setColor (ccc3 (0x5F, 0xD4, 0x4C));
	m_QuitMessageTitleAccount->setPosition (ccp (m_QuitMessageTitleStart->boundingBox ().getMaxX (), m_QuitMessageTitleStart->boundingBox ().getMidY ()));
	addChild (m_QuitMessageTitleAccount);

	m_QuitMessageTitleEnding = CCLabelTTF::create(TT("Playerinformation1"), TTF_NAME, ODEFloorf(LOBBY_MAX_TTF_SIZE * g_f32ScaleHD));
	m_QuitMessageTitleEnding->setAnchorPoint (ccp (0.0f, 0.5f));
	m_QuitMessageTitleEnding->setPosition (ccp (m_QuitMessageTitleAccount->boundingBox ().getMaxX (), m_QuitMessageTitleAccount->boundingBox ().getMidY ()));
	addChild (m_QuitMessageTitleEnding);

	int m_playerTimes = 0;
	int m_sendScore = 0;

	if (g_pkLobbyConnectData->getActiveMsgInfo (10002) != NULL)
	{
		m_ContentMessageStart = CCLabelTTF::create (TT ("ChangeAccountGetScoreInformation"), TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
		m_ContentMessageStart->setAnchorPoint (ccp (0.0f, 0.5f));
		m_ContentMessageStart->setPosition (ccp (m_pkPanel->boundingBox ().getMinX () + 70, m_pkPanel->boundingBox ().getMidY () + 35));
		addChild (m_ContentMessageStart);

		char contentMessage[100] = {0};
		ODESprintf (contentMessage,sizeof (contentMessage), TT ("ChangeAccountPlayTimes"), "----");
		m_ContentMessageContent = CCLabelTTF::create (contentMessage, TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
		m_ContentMessageContent->setAnchorPoint (ccp (0.0f, 0.5f));
		m_ContentMessageContent->setColor (ccc3 (0xFF, 0xAF, 0x32));
		m_ContentMessageContent->setPosition (ccp (m_ContentMessageStart->boundingBox ().getMaxX () + 5, m_ContentMessageStart->boundingBox ().getMidY ()));
		addChild (m_ContentMessageContent);

		m_ContentMessageEnding = CCLabelTTF::create (TT ("ChangeAccountCanGetScore"), TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
		m_ContentMessageEnding->setAnchorPoint (ccp (0.0f, 0.5f));
		m_ContentMessageEnding->setPosition (ccp (m_ContentMessageContent->boundingBox ().getMaxX () + 5, m_ContentMessageContent->boundingBox ().getMidY ()));
		addChild (m_ContentMessageEnding);

		ODESprintf (contentMessage,sizeof (contentMessage), TT ("ChangeAccountCanGetScoreValue"), "------");
		m_ContentMessageEnding2 = CCLabelTTF::create (contentMessage, TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
		m_ContentMessageEnding2->setAnchorPoint (ccp (0.0f, 0.5f));
		m_ContentMessageEnding2->setColor (ccc3 (0xFF, 0xAF, 0x32));
		m_ContentMessageEnding2->setPosition (ccp (m_ContentMessageEnding->boundingBox ().getMaxX () + 5, m_ContentMessageEnding->boundingBox ().getMidY ()));
		addChild (m_ContentMessageEnding2);
	}
	else if (g_pkLobbyConnectData->getActiveMsgInfo (10005) != NULL)
	{
		m_ContentMessageStart = CCLabelTTF::create (TT ("ChangeAccountDoubleChargeInformation"), TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
		m_ContentMessageStart->setAnchorPoint (ccp (0.0f, 0.5f));
		m_ContentMessageStart->setPosition (ccp (m_pkPanel->boundingBox ().getMinX () + 70, m_pkPanel->boundingBox ().getMidY () + 35));
		addChild (m_ContentMessageStart);

		char contentMessage[100] = {0};
		ODESprintf (contentMessage,sizeof (contentMessage), TT ("ChangeAccountDoubleChargeRebackCount"), 5);
		m_ContentMessageContent = CCLabelTTF::create (contentMessage, TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
		m_ContentMessageContent->setAnchorPoint (ccp (0.0f, 0.5f));
		m_ContentMessageContent->setColor (ccc3 (0xFF, 0xAF, 0x32));
		m_ContentMessageContent->setPosition (ccp (m_ContentMessageStart->boundingBox ().getMaxX () + 5, m_ContentMessageStart->boundingBox ().getMidY ()));
		addChild (m_ContentMessageContent);

		m_ContentMessageEnding = CCLabelTTF::create (TT ("ChangeAccountDoubleChargeMessage"), TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
		m_ContentMessageEnding->setAnchorPoint (ccp (0.0f, 0.5f));
		m_ContentMessageEnding->setPosition (ccp (m_ContentMessageContent->boundingBox ().getMaxX () + 5, m_ContentMessageContent->boundingBox ().getMidY ()));
		addChild (m_ContentMessageEnding);
	}
	else
	{
		m_ContentMessageContent = CCLabelTTF::create (TT ("ChangeAccountLastMessage"), TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD), CCSizeMake (650, 250), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
		m_ContentMessageContent->setAnchorPoint (ccp (0.0f, 0.5f));
		m_ContentMessageContent->setPosition (ccp (m_pkPanel->boundingBox ().getMinX () + 70, m_pkPanel->boundingBox ().getMidY () + 35));
		addChild (m_ContentMessageContent);
	}

	m_GetAwardMessageStart = CCLabelTTF::create (TT ("ChangeAccountPopupLayerprompt3"), TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
	m_GetAwardMessageStart->setAnchorPoint (ccp (0.0f, 0.5f));
	m_GetAwardMessageStart->setPosition (ccp (m_pkPanel->boundingBox ().getMinX () + 70, m_pkPanel->boundingBox ().getMidY () - 35));
	addChild (m_GetAwardMessageStart);
	char contentMessage[100] = {0};
	ODESprintf (contentMessage,sizeof (contentMessage), TT ("ChangeAccountCanGetScoreValue"), "-----");
	m_GetAwardMessageEnd = CCLabelTTF::create (contentMessage, TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
	m_GetAwardMessageEnd->setAnchorPoint (ccp (0.0f, 0.5f));
	m_GetAwardMessageEnd->setColor (ccc3 (0xFF, 0xAF, 0x32));
	m_GetAwardMessageEnd->setPosition (ccp (m_GetAwardMessageStart->boundingBox ().getMaxX () + 5, m_GetAwardMessageStart->boundingBox ().getMidY ()));
	addChild (m_GetAwardMessageEnd);

	m_ExitMesssage = CCLabelTTF::create (TT ("ChangeAccountQuitConfirm"), TTF_NAME, ODEFloorf(LOBBY_INFORMATION_TTF_SIZE * g_f32ScaleHD));
	m_ExitMesssage->setAnchorPoint (ccp (0.0f, 0.5f));
	m_ExitMesssage->setPosition (ccp (m_pkPanel->boundingBox ().getMinX () + 70, m_pkPanel->boundingBox ().getMidY () - 115));
	addChild (m_ExitMesssage);
}

void ChangeAccountPopupLayer::removeCreateData ()
{
	m_bCreateScene = false;
	removeAllChildren ();
	m_kWidgetMap.Clear();
	m_kWidgets.BeginIterator();
	while(!m_kWidgets.IsEnd())
	{
		ODUIWidget* pkWidget = m_kWidgets.GetIterNode()->m_tContent;
		m_kWidgets.Next();
		ODE_ASSERT(pkWidget);
		ODE_DELETE(pkWidget);
	}
	m_kWidgets.Clear();
	m_pkLastProcessWidget = NULL;
}

void ChangeAccountPopupLayer::ResetQuitContentData ()
{
	int serialLoginCount = g_pkClientData->GetUserSerialLoginTaskInfo ()->nSerialSignCount;
	int value = 0;
	if (g_pkClientData->GetUserSerialLoginTaskInfo ()->bIsGettedAward)
		serialLoginCount ++;

	for (int i = 0; i < MAX_LOGIN_AWARD; i++)
	{
		CCLOG ("Award Type %d, Award Value %d \n", g_pkClientData->GetUserSerialLoginTaskInfo ()->nLoginPresentType[i], g_pkClientData->GetUserSerialLoginTaskInfo ()->nPresentCount[i]);
	}

	if (serialLoginCount >= 1 && serialLoginCount <= 7)
		value = g_pkClientData->GetUserSerialLoginTaskInfo ()->nPresentCount[serialLoginCount - 1];
	else if (serialLoginCount > 7)
		value = g_pkClientData->GetUserSerialLoginTaskInfo ()->nPresentCount[(serialLoginCount - 1) % 7];
	else
		value = g_pkClientData->GetUserSerialLoginTaskInfo ()->nPresentCount[0];

	char contentMessage[100] = {0};
	char scoreTemp[10] = {0};
	sprintf (scoreTemp, "%d", value);
	ODESprintf (contentMessage,sizeof (contentMessage), TT ("ChangeAccountCanGetScoreValue"), scoreTemp);
	m_GetAwardMessageEnd->setString (contentMessage);
}

void ChangeAccountPopupLayer::ResetContentData ()
{
	int m_playerTimes = 0;
	int m_sendScore = 0;
	LobbyPersonalCenterInfoRsp * m_centerInfo = g_pkClientData->GetPersonalCenterInfo ();
	if (m_centerInfo != NULL)
	{
		if (m_centerInfo->nUserLevel == 0)
		{
			m_playerTimes = 10;
			m_sendScore = 200;
		}
		else
		{
			if (m_centerInfo->nLevelSendScoreTimes >= m_centerInfo->nLevelMaxSendTimes)
			{
				m_playerTimes = 0;
				m_sendScore = 0;
			}
			else
			{
				int arr[4] = {0};
				arr[0] = m_centerInfo->nLevelSendCoin1;arr[1] = m_centerInfo->nLevelSendCoin2;
				arr[2] = m_centerInfo->nLevelSendCoin3;arr[3] = m_centerInfo->nLevelSendCoin4;
				if (m_centerInfo->nLevelSendScoreTimes < 4){
					m_playerTimes = 10;
					m_sendScore = arr[m_centerInfo->nLevelSendScoreTimes];
				}else{
					m_sendScore = 0;
					m_playerTimes = 0;
				}
			}
		}	
	}

	if (g_pkLobbyConnectData->getActiveMsgInfo (10002) != NULL)
	{
		int activeTime = atoi (GetConfig ("NewLobby_Active_Score_Exchange_Gift_10"));
		if(m_playerTimes < activeTime )
			m_playerTimes = activeTime;
		m_sendScore += atoi (GetConfig ("NewLobby_Active_Score_Exchange_Gift_11"));

		if (m_sendScore != 0)
		{
			if (m_ContentMessageStart != NULL)
			{
				m_ContentMessageStart->setString (TT ("ChangeAccountGetScoreInformation"));

				char contentMessage[100] = {0};
				char playTimesTemp[10] = {0};
				sprintf (playTimesTemp, "%d", m_playerTimes);
				ODESprintf (contentMessage,sizeof (contentMessage), TT ("ChangeAccountPlayTimes"), playTimesTemp);
				m_ContentMessageContent->setString (contentMessage);
				m_ContentMessageContent->setPosition (ccp (m_ContentMessageStart->boundingBox ().getMaxX () + 5, m_ContentMessageStart->boundingBox ().getMidY ()));

				if (m_ContentMessageEnding != NULL)
					m_ContentMessageEnding->setString (TT ("ChangeAccountCanGetScore"));

				sprintf (playTimesTemp, "%d", m_sendScore);
				ODESprintf (contentMessage,sizeof (contentMessage), TT ("ChangeAccountCanGetScoreValue"), playTimesTemp);
				if (m_ContentMessageEnding2 != NULL)
					m_ContentMessageEnding2->setString (contentMessage);
			}
		}
	}
	else if (g_pkLobbyConnectData->getActiveMsgInfo (10005) != NULL)
	{
		if (m_ContentMessageStart != NULL)
		{
			m_ContentMessageStart->setString (TT ("ChangeAccountDoubleChargeInformation"));

			char contentMessage[100] = {0};
			ODESprintf (contentMessage,sizeof (contentMessage), TT ("ChangeAccountDoubleChargeRebackCount"), 5);
			m_ContentMessageContent->setString (contentMessage);

			if (m_ContentMessageEnding != NULL)
				m_ContentMessageEnding->setString (TT ("ChangeAccountDoubleChargeMessage"));
		}
	}
	else
	{
		m_ContentMessageContent->setString (TT ("ChangeAccountLastMessage"));
	}
}

void ChangeAccountPopupLayer::OnDeactive(const ODUIUserDataPtr& spData)
{
}

void ChangeAccountPopupLayer::term ()
{
	ODUILayer::term ();
}

bool ChangeAccountPopupLayer::OnBack ()
{
	return true;
}

void ChangeAccountPopupLayer::OnMenu ()
{

}

void ChangeAccountPopupLayer::onExit ()
{
	ODUILayer::onExit();
}

void ChangeAccountPopupLayer::OnFadeIn()
{}

void ChangeAccountPopupLayer::OnFadeOut()
{
	g_pkGuanDanGame->addChangeIndexToQuene(LAYER_MANAGER_QUENE_MAIN_LAYER);
	g_pkGuanDanGame->FadeIn(FADE_IN_TIME);
}

UIImplementDelegate(ChangeAccountPopupLayer, OnClose, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopAllLayers();
	}
}

UIImplementDelegate(ChangeAccountPopupLayer, OnQuit, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		if (javaLanchFromLobby())
		{
			g_pkDirector->end();
		}
		else
		{
			g_pkGuanDanGame->addChangeIndexToQuene(LAYER_MANAGER_QUENE_CHANGE_ACCOUNT);
			g_pkGuanDanGame->FadeIn(FADE_IN_TIME);
		}
	}
}

UIImplementDelegate(ChangeAccountPopupLayer, OnGetaward, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopAllLayers();

		if (g_pLayerManager->GetLayer ("lobby_active") != NULL)
		g_pLayerManager->PushMiddleLayer ("lobby_active");
		else
		{
		g_pLayerManager->AddLayer(LobbyActive::create());
		g_pLayerManager->PushMiddleLayer ("lobby_active");
		}
		
		g_pkGuanDanGame->FadeIn(FADE_IN_TIME);
	}
}