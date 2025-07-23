#include "BuyHeadImage.h"
#include "LobbyAssistScene.h"
#include "ScoreNotEnoughPopupLayer.h"
#include "BuyConfirmPopLayer.h"
/**************************************************************************
Copyright:ODAO
 
Author: 
 
Date:   2014-10-24
 
Description:购买头像
 
**************************************************************************/

//bool BuyHeadImage::m_bCreateScene = false;

BuyHeadImage::BuyHeadImage () : ODUILayerModalExt<BuyHeadImage>("BuyHeadImage")
	,m_bCreateScene(false)
{
	m_kOnFadeIn.Set(this, &BuyHeadImage::OnFadeIn);
	m_kOnFadeOut.Set(this, &BuyHeadImage::OnFadeOut);
	
	UIInitDelegate(BuyHeadImage, OnClose);
	UIInitDelegate(BuyHeadImage, OnBuy1);
	UIInitDelegate(BuyHeadImage, OnBuy2);
	UIInitDelegate(BuyHeadImage, OnUse);

}

BuyHeadImage::~BuyHeadImage()
{
	term ();
	m_bCreateScene = false;
}

bool BuyHeadImage::init ()
{
	return ODUILayerModalExt<BuyHeadImage>::init();
}

void BuyHeadImage::OnActive(const ODUIUserDataPtr& spData)
{
	if (!m_bCreateScene)
		createScene ();

	//updateInfo(ODEFloat32 u32Delta);
	timevaluesec = g_pkLobbyConnectData->getUserItemsAvilableTime(g_pkClientData->GetUserBuyHeadIndex());

	updateInfo();
	/*unschedule(schedule_selector(BuyHeadImage::updateInfo));
	schedule(schedule_selector(BuyHeadImage::updateInfo),15.0f);*/

}

void BuyHeadImage::createScene ()
{
	m_bCreateScene = true;

	setScale(ui_main_scale);

	CCLayerColor* layer = CCLayerColor::create(ccc4(0x00, 0x00, 0x00, 0x3F), ui_w (1.0f), ui_h (1.0f));
	layer->setScale (1 / ui_main_scale);
	addChild (layer);

	CCScale9Sprite * m_pkPanel = CCScale9Sprite::create ("image/active/national_rule_background.png",CCRect (0, 0, 42, 154), CCRect (21, 77, 1, 1));
	m_pkPanel->setPreferredSize (CCSizeMake (752.0f, 518.0f));
	addChild(m_pkPanel);
	m_pkPanel->setPosition(ccp (ui_w (0.5), ui_h (0.5f)));

	CCLabelTTF * m_titleTex = CCLabelTTF::create(TT("UIText_BuyHeadImage"), TTF_NAME, ODEFloorf(LOBBY_MAX_TTF_SIZE * g_f32ScaleHD));
	m_titleTex->setPosition ((ccp (m_pkPanel->boundingBox ().getMidX (), m_pkPanel->boundingBox ().getMaxY () - 42)));
	addChild (m_titleTex);

	CCSprite* close = CCSprite::createWithSpriteFrameName("center_no.png");
	CCScale9Sprite * background = CCScale9Sprite::createWithSpriteFrameName ("top_bar_background.png");
	background->setPreferredSize (CCSizeMake (60, 60));
	background->setOpacity (0);
	CCScale9Sprite * background2 = CCScale9Sprite::createWithSpriteFrameName ("top_bar_background.png");
	background2->setPreferredSize (background->getContentSize ());

	NormalButton* pkCloseBtn = ODE_NEW NormalButton(background, background2, close);
	pkCloseBtn->setPosition (ccp (m_pkPanel->boundingBox ().getMaxX () - pkCloseBtn->getContentSize ().width,m_titleTex->getPositionY ()));
	UILinkDelegate (pkCloseBtn, OnClose);
	pkCloseBtn->setContentSize(pkCloseBtn->getContentSize() * 2);
	pkCloseBtn->SetContentTouchSize (75.0f, 75.0f);
	AddWidget("kCloseBtn", pkCloseBtn);

	CCLabelTTF* label = CCLabelTTF::create(TT("UITest_BuyHeadBiaoTi"), TTF_NAME, 25.0f);
	label->setAnchorPoint(ccp(0.0f, 0.5f));
	label->setColor(ALERT_LABEL_TEXT_COLOR);
	label->setPosition(ccp(m_pkPanel->boundingBox ().getMinX () + 30, m_pkPanel->boundingBox ().getMidY() + 150));
	addChild(label);

	CCSprite* m_pLine1 = CCSprite::create("image/xian01.png");
	m_pLine1->setScaleX ((m_pkPanel->getContentSize ().width - 20)/ m_pLine1->getContentSize ().width);
	m_pLine1->setPosition(ccp(m_pkPanel->boundingBox ().getMidX (), m_pkPanel->boundingBox ().getMidY() + 120));
	addChild(m_pLine1);

	label1 = CCLabelTTF::create("", TTF_NAME, 25.0f);
	label1->setAnchorPoint(ccp(0.0f, 0.5f));
	label1->setColor(ALERT_LABEL_TEXT_COLOR);
	label1->setPosition(ccp(m_pkPanel->boundingBox ().getMinX () + 70, m_pkPanel->boundingBox ().getMidY() + 50));
	addChild(label1);

	CCScale9Sprite * textBuy1 =CCScale9Sprite::createWithSpriteFrameName ("text_button_background.png", CCRect (6, 6, 2, 2));
	textBuy1->setPreferredSize (CCSizeMake (150 , 40 ));
	CCScale9Sprite * textPressBuy1 =CCScale9Sprite::createWithSpriteFrameName ("text_button_background.png", CCRect (6, 6, 2, 2));
	textPressBuy1->setPreferredSize (textBuy1->getContentSize ());
	textPressBuy1->setColor (ColorLevelDiv2 (textPressBuy1->getColor ()));
	CCLabelTTF * BuyTTF1 = CCLabelTTF::create(TT("UIText_Buy"), TTF_NAME, ODEFloorf(LOBBY_NORMAL_TTF_SIZE * g_f32ScaleHD ));
	BuyTTF1->setColor(ALERT_LABEL_TEXT_COLOR);
	TextButton * buyBtn1 = new TextButton (textBuy1, textPressBuy1, BuyTTF1);
	buyBtn1->setPosition (ccp(m_pkPanel->boundingBox ().getMidX () + 200, m_pkPanel->boundingBox ().getMidY() + 50 ));
	AddWidget ("buy_Btn2", buyBtn1);
	UILinkDelegate(buyBtn1, OnBuy1);
	
	label2 = CCLabelTTF::create("", TTF_NAME, 25.0f);
	label2->setAnchorPoint(ccp(0.0f, 0.5f));
	label2->setColor(ALERT_LABEL_TEXT_COLOR);
	label2->setPosition(ccp(m_pkPanel->boundingBox ().getMinX () + 70, m_pkPanel->boundingBox ().getMidY() - 50));
	addChild(label2);

	CCScale9Sprite * textBuy2 =CCScale9Sprite::createWithSpriteFrameName ("text_button_background.png", CCRect (6, 6, 2, 2));
	textBuy2->setPreferredSize (CCSizeMake (150, 40 ));
	CCScale9Sprite * textPressBuy2 =CCScale9Sprite::createWithSpriteFrameName ("text_button_background.png", CCRect (6, 6, 2, 2));
	textPressBuy2->setPreferredSize (textBuy2->getContentSize ());
	textPressBuy2->setColor (ColorLevelDiv2 (textPressBuy2->getColor ()));
	CCLabelTTF * BuyTTF2 = CCLabelTTF::create(TT("UIText_Buy"), TTF_NAME, ODEFloorf(LOBBY_NORMAL_TTF_SIZE * g_f32ScaleHD ));
	BuyTTF2->setColor(ALERT_LABEL_TEXT_COLOR);
	TextButton * buyBtn2 = new TextButton (textBuy2, textPressBuy2, BuyTTF2);
	buyBtn2->setPosition (ccp(m_pkPanel->boundingBox ().getMidX () + 200, m_pkPanel->boundingBox ().getMidY() - 50));
	AddWidget ("buy_Btn2", buyBtn2);
	UILinkDelegate(buyBtn2, OnBuy2);

	CCSprite* m_pLine2 = CCSprite::create("image/xian01.png");
	m_pLine2->setScaleX ((m_pkPanel->getContentSize ().width -20)/ m_pLine2->getContentSize ().width);
	m_pLine2->setPosition(ccp(m_pkPanel->boundingBox ().getMidX (), m_pkPanel->boundingBox ().getMidY() - 120));
	addChild(m_pLine2);

	CCScale9Sprite * textUse =CCScale9Sprite::createWithSpriteFrameName ("text_button_background.png", CCRect (6, 6, 2, 2));
	textUse->setPreferredSize (CCSizeMake (150, 40 ));
	CCScale9Sprite * texPressUse =CCScale9Sprite::createWithSpriteFrameName ("text_button_background.png", CCRect (6, 6, 2, 2));
	texPressUse->setPreferredSize (textUse->getContentSize ());
	texPressUse->setColor (ColorLevelDiv2 (texPressUse->getColor ()));
	CCLabelTTF * UseTTF = CCLabelTTF::create(TT("UITest_Use"), TTF_NAME, ODEFloorf(LOBBY_NORMAL_TTF_SIZE * g_f32ScaleHD ));
	UseTTF->setColor(ALERT_LABEL_TEXT_COLOR);
	TextButton * UsetBtn = new TextButton (textUse, texPressUse, UseTTF);
	UsetBtn->setPosition (ccp(m_pkPanel->boundingBox ().getMidX () + 200, m_pkPanel->boundingBox ().getMidY() - 170));
	AddWidget ("use_Btn", UsetBtn);
	UILinkDelegate(UsetBtn, OnUse);

	label3 = CCLabelTTF::create("", TTF_NAME, 25.0f);
	label3->setAnchorPoint(ccp(0.0f, 0.5f));
	label3->setColor(ALERT_LABEL_TEXT_COLOR);
	label3->setPosition(ccp(m_pkPanel->boundingBox ().getMinX () + 70, m_pkPanel->boundingBox ().getMidY() - 170));
	addChild(label3);
	
}

void BuyHeadImage::OnDeactive(const ODUIUserDataPtr& spData)
{
	CCTextureCache::sharedTextureCache()->removeTextureForKey("image/active/national_rule_background.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("image/xian01.png");
	m_pkLastProcessWidget = NULL;
}

void BuyHeadImage::term ()
{
	ODUILayer::term ();
}

bool BuyHeadImage::OnBack ()
{
	return true;
}

void BuyHeadImage::OnMenu ()
{

}

void BuyHeadImage::onExit ()
{
	ODUILayer::onExit();
}

void BuyHeadImage::updateInfo ()
{ 

	/*struct tm *localptm; 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	time_t timep;  
	time(&timep);  
	localptm = localtime(&timep); 

	long long tmTime = timep;
#else  
	struct cc_timeval now;  
	CCTime::gettimeofdayCocos2d(&now, NULL); 
	long long tmTime = now.tv_sec;
	localptm = localtime(&now.tv_sec); 
#endif*/

	time_t time_valuesec  = timevaluesec;
	tm *ptm = localtime(&time_valuesec);

	int timevalueyear = ptm->tm_year + 1900;
	//int time_valueyear = localptm->tm_year + 1900;

	int timevaluemonth = ptm->tm_mon + 1;
	//int time_valuemonth = localptm->tm_mon + 1;

	int timevalueday = ptm->tm_mday;
	//int time_valueday = localptm->tm_mday;

	int timevaluehour = ptm->tm_hour;
	//int time_valuehour = localptm->tm_hour;

	int timevalueminute = ptm->tm_min;
	//int time_valueminute = localptm->tm_min;

	int timevaluesecond = ptm->tm_sec;
	//int time_valuesecond = localptm->tm_sec;

	char m_timeValueBuffer[100] = {0};
	if(g_pkLobbyConnectData->getUserItemsInfo(g_pkClientData->GetUserBuyHeadIndex()) )
	{
		//if(tmTime < timevaluesec)
		//{
			sprintf(m_timeValueBuffer,TT("UIText_RemainTime"), timevalueyear, timevaluemonth, timevalueday, timevaluehour, timevalueminute);
		//}
		/*else
		{
			g_pkGuanDanGame->Toast(TT("UITest_HeadImageExpire"));
			g_pkNetworkHelper->SendGetItemsInfoReq();
			if(g_pkClientData->GetUserHeadIndex() == g_pkClientData->GetUserBuyHeadIndex())
			{
				g_pkClientData->SetHeadIndex(100);
				g_pkGuanDanGame->PushCommand(CMD_SET_IMAGE_SUCCESS);
			}	
		}*/
		//timevaluesec = timevaluesec - 1;
	}
	else
	{
		sprintf(m_timeValueBuffer,TT("UIText_RemainTime_Not_Buy"), 0, 0, 0, 0);
	}
	label3->setString(m_timeValueBuffer);

	int index = g_pkClientData->GetUserBuyHeadIndex();
	int price = g_pkLobbyConnectData->getOnSaleItemsListInfo(index)->nPrice;
	int salerate = g_pkLobbyConnectData->getOnSaleItemsListInfo(index)->nSaleRate;
	char m_labelbuffer1[100] = {0};
	sprintf(m_labelbuffer1, TT("UIText_BuyDayNum1"), price * salerate / 300);
	label1->setString(m_labelbuffer1);

	char m_labelbuffer2[100] = {0};
	sprintf(m_labelbuffer2, TT("UIText_BuyDayNum2"), price * salerate / 100);
	label2->setString(m_labelbuffer2);
}


void BuyHeadImage::OnFadeIn()
{

}

void BuyHeadImage::OnFadeOut()
{
	g_pkGuanDanGame->addChangeIndexToQuene(LAYER_MANAGER_QUENE_MAIN_LAYER);
	g_pkGuanDanGame->FadeIn(FADE_IN_TIME);
}

UIImplementDelegate(BuyHeadImage, OnClose, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopLayer();
	}
}

UIImplementDelegate(BuyHeadImage, OnBuy1, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopLayer();

		if (g_pLayerManager->GetLayer ("BuyConfirmPopLayer") != NULL)
			g_pLayerManager->PushLayer ("BuyConfirmPopLayer");
		else
		{
			g_pLayerManager->AddLayer(BuyConfirmPopLayer::create());
			g_pLayerManager->PushLayer ("BuyConfirmPopLayer");
		}
	}
}

UIImplementDelegate(BuyHeadImage, OnBuy2, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopLayer();

		if (g_pLayerManager->GetLayer ("BuyConfirmPopLayer2") != NULL)
			g_pLayerManager->PushLayer ("BuyConfirmPopLayer2");
		else
		{
			g_pLayerManager->AddLayer(BuyConfirmPopLayer2::create());
			g_pLayerManager->PushLayer ("BuyConfirmPopLayer2");
		}
	}
}

UIImplementDelegate(BuyHeadImage, OnUse, kwidget, u32State)
{
	if(u32State == ODUIWidget::RELEASED)
	{
		int headindex = g_pkClientData->GetUserBuyHeadIndex();
		int isbuyed = g_pkLobbyConnectData->getUserItemsInfo(headindex);
		if(isbuyed == 1)
		{
			int kong = g_pkClientData->GetUserHeadIndex();
			if((headindex) != kong)
			{
				if(IsNetwork())
				{
					g_pkGuanDanGame->ShowLoading(true);
					if (g_pkNetworkHelper->GetLobbyAlwaysConnectDelegate () && g_pkNetworkHelper->GetLobbyAlwaysConnectDelegate ()->IsConnect())
					{
						g_pkNetworkHelper->SendSetHeadImage(headindex);
					}
					else
					{
						g_pkGuanDanGame->Toast(TT("UITest_ConnectServerFaild"));
						g_pLayerManager->PopLayer();
					}
				}
				else
				{
					g_pkGuanDanGame->Toast(TT("UIText_ConnetNetworkFaild"));
				}
			}
			else
			{
				g_pkGuanDanGame->Toast(TT("UITest_HeadImageIsUsing"));
			}
		}	
		else
		{
			g_pkGuanDanGame->Toast((TT("UITest_HeadImageNotBuyed")));
		}
	}
}
