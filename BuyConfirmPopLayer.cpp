#include "ChangeAccountPopupLayer.h"
#include "LobbyAssistScene.h"
#include "LobbyReward.h"
#include "LobbySetting.h"
#include "LobbyLogin.h"
#include "BuyConfirmPopLayer.h"
#include "LobbyChargeMenu.h"
#include "ScoreNotEnoughPopupLayer.h"
/**************************************************************************
Copyright:ODAO
 
Author: 
 
Date:   2014-10-22
 
Description: 购买确认提示弹出框
 
**************************************************************************/

//bool BuyConfirmPopLayer::m_bCreateScene = false;
//bool BuyConfirmPopLayer2::m_bCreateScene = false;

BuyConfirmPopLayer::BuyConfirmPopLayer () : ODUILayerModalExt<BuyConfirmPopLayer>("BuyConfirmPopLayer")
	,m_bCreateScene(false)
{
	//m_kOnFadeIn.Set(this, &BuyConfirmPopLayer::OnFadeIn);
	//m_kOnFadeOut.Set(this, &BuyConfirmPopLayer::OnFadeOut);
	UIInitDelegate(BuyConfirmPopLayer, OnClose);
	UIInitDelegate(BuyConfirmPopLayer, OnCancel);
	UIInitDelegate(BuyConfirmPopLayer, OnConfirm );
}

BuyConfirmPopLayer::~BuyConfirmPopLayer()
{
	term ();
	m_bCreateScene = false;
}

bool BuyConfirmPopLayer::init ()
{
	return ODUILayerModalExt<BuyConfirmPopLayer>::init();
}

void BuyConfirmPopLayer::OnActive(const ODUIUserDataPtr& spData)
{
	if (!m_bCreateScene)
		createScene ();

	updateInfo();



}

void BuyConfirmPopLayer::createScene ()
{
	m_bCreateScene = true;

	setScale(ui_main_scale);
	//使屏幕变灰
	CCLayerColor* layer = CCLayerColor::create(ccc4(0x00, 0x00, 0x00, 0x3F), ui_w (1.0f), ui_h (1.0f));
	layer->setScale (1 / ui_main_scale);
	addChild (layer);

	CCScale9Sprite * m_pkPanel = CCScale9Sprite::createWithSpriteFrameName ("alert_background.png", CCRect (100, 100, 2, 2));
	m_pkPanel->setPreferredSize (CCSizeMake (700.0f, 450.0f));
	addChild(m_pkPanel);
	m_pkPanel->setPosition(ccp (ui_w (0.5), ui_h (0.5f)));    //把图片放到屏幕的中心位置

	CCLabelTTF * m_titleTex = CCLabelTTF::create(TT("TipTitle"), TTF_NAME, ODEFloorf(LOBBY_TITLE_TTF_SIZE * g_f32ScaleHD));
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

	CCScale9Sprite * backgroundCancel = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel->setOpacity (0);
	CCScale9Sprite * backgroundCancel2 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel2->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	CCSprite * logo = CCSprite::createWithSpriteFrameName ("input_frame_2.png");
	logo->setOpacity (0);
	NormalButtonWithText * m_canaelBtn = ODE_NEW NormalButtonWithText(backgroundCancel, backgroundCancel2, logo, TT ("UITextSettlementExit"));
	m_canaelBtn->setPosition(ccp (m_pkPanel->boundingBox ().getMidX () - m_canaelBtn->getContentSize ().width / 2, m_pkPanel->boundingBox ().getMinY () + 10 + m_canaelBtn->getContentSize ().height / 2));	
	AddWidget("ChangeAccountPopupLayer_quit", m_canaelBtn);
	m_canaelBtn->SetTextWithColor (TT ("Cancel"), ccc3 (155, 160, 175));
	UILinkDelegate(m_canaelBtn, OnCancel);

	CCScale9Sprite * backgroundCancel3 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel3->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel3->setOpacity (0);
	CCScale9Sprite * backgroundCancel4 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel4->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel4->setRotationY (180.0f);
	CCSprite * logo2 = CCSprite::createWithSpriteFrameName ("input_frame_2.png");
	logo2->setOpacity (0);
	NormalButtonWithText * m_getchargeBtn = ODE_NEW NormalButtonWithText(backgroundCancel3, backgroundCancel4, logo2, TT ("UIText_Receivereward"));
	m_getchargeBtn->setPosition(ccp (m_pkPanel->boundingBox ().getMidX () + m_getchargeBtn->getContentSize ().width / 2, m_pkPanel->boundingBox ().getMinY () + 10 + m_getchargeBtn->getContentSize ().height / 2));
	AddWidget("ChangeAccountPopupLayer_getaward", m_getchargeBtn);
	m_getchargeBtn->SetTextWithColor (TT ("Confirm"), ccc3 (51, 177, 77));
	UILinkDelegate(m_getchargeBtn, OnConfirm);

	m_text1 = CCLabelTTF::create("", TTF_NAME, ODEFloorf(LOBBY_NORMAL_TTF_SIZE * g_f32ScaleHD));
	m_text1->setColor(ccc3(255.0f, 255.0f, 255.0f));
	m_text1->setPosition(ccp (m_pkPanel->boundingBox ().getMidX (),m_pkPanel->boundingBox().getMidY()));
	addChild(m_text1);

	CCSprite * m_line2 = CCSprite::createWithSpriteFrameName ("alert_line2.png");
	m_line2->setFlipY (true);
	m_line2->setScaleY (89 / m_line2->getContentSize ().height);
	m_line2->setPosition (ccp (m_pkPanel->boundingBox ().getMidX (), m_pkPanel->boundingBox ().getMinY () + 8 + m_canaelBtn->getContentSize ().height / 2));
	addChild (m_line2);

	CCSprite * m_line1 = CCSprite::createWithSpriteFrameName ("alert_line_1.png");
	m_line1->setScaleX ((m_pkPanel->getContentSize ().width - 16) / m_line1->getContentSize ().width);
	m_line1->setPosition (ccp (m_pkPanel->boundingBox ().getMidX (), m_line2->boundingBox ().getMaxY ()));
}

void BuyConfirmPopLayer::OnDeactive(const ODUIUserDataPtr& spData)
{
	m_pkLastProcessWidget = NULL;
}

void BuyConfirmPopLayer::term ()
{
	ODUILayer::term ();
}

bool BuyConfirmPopLayer::OnBack ()
{
	return true;
}

void BuyConfirmPopLayer::OnMenu ()
{

}

void BuyConfirmPopLayer::onExit ()
{
	ODUILayer::onExit();
}


void BuyConfirmPopLayer::updateInfo ()
{
	int index = g_pkClientData->GetUserBuyHeadIndex();
	int price = g_pkLobbyConnectData->getOnSaleItemsListInfo(index)->nPrice;
	int salerate = g_pkLobbyConnectData->getOnSaleItemsListInfo(index)->nSaleRate;
	char m_labelbuffer1[100] = {0};
	sprintf(m_labelbuffer1, TT("UITextBuyHeadImageConfirm_1"), price * salerate / 300);
	m_text1->setString(m_labelbuffer1);
}


void BuyConfirmPopLayer::OnFadeIn()
{}

void BuyConfirmPopLayer::OnFadeOut()
{
	g_pkGuanDanGame->addChangeIndexToQuene(LAYER_MANAGER_QUENE_MAIN_LAYER);
	g_pkGuanDanGame->FadeIn(FADE_IN_TIME);
}

UIImplementDelegate(BuyConfirmPopLayer, OnClose, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopLayer();
	}
}

UIImplementDelegate(BuyConfirmPopLayer, OnCancel, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopLayer();
	}
}

UIImplementDelegate(BuyConfirmPopLayer, OnConfirm, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		int index = g_pkClientData->GetUserBuyHeadIndex();
		int price = g_pkLobbyConnectData->getOnSaleItemsListInfo(index)->nPrice;
		int salerate = g_pkLobbyConnectData->getOnSaleItemsListInfo(index)->nSaleRate;
		if(g_pkClientData->GetUserScore() < price * salerate / 300)
		{
			g_pLayerManager->PopLayer();
			if (g_pLayerManager->GetLayer ("ScoreNotEnoughPopupLayer") != NULL)
				g_pLayerManager->PushLayer ("ScoreNotEnoughPopupLayer");
			else
			{
				g_pLayerManager->AddLayer(ScoreNotEnoughPopupLayer::create());
				g_pLayerManager->PushLayer ("ScoreNotEnoughPopupLayer");
			}
		}
		else
		{
			if(IsNetwork())
			{
				g_pkGuanDanGame->ShowLoading(true);
				if (g_pkNetworkHelper->GetLobbyAlwaysConnectDelegate () && g_pkNetworkHelper->GetLobbyAlwaysConnectDelegate ()->IsConnect())
				{
					g_pkNetworkHelper->SendBuyHeadImage(index,price * salerate / 300);
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
			g_pLayerManager->PopLayer();
		}
	}
}

BuyConfirmPopLayer2::BuyConfirmPopLayer2 () : ODUILayerModalExt<BuyConfirmPopLayer2>("BuyConfirmPopLayer2")
	,m_bCreateScene(false)
{
	UIInitDelegate(BuyConfirmPopLayer2, OnClose);
	UIInitDelegate(BuyConfirmPopLayer2, OnCancel);
	UIInitDelegate(BuyConfirmPopLayer2, OnConfirm );
}

BuyConfirmPopLayer2::~BuyConfirmPopLayer2()
{
	term ();
	m_bCreateScene = false;
}

bool BuyConfirmPopLayer2::init ()
{
	return ODUILayerModalExt<BuyConfirmPopLayer2>::init();
}

void BuyConfirmPopLayer2::OnActive(const ODUIUserDataPtr& spData)
{
	if (!m_bCreateScene)
		createScene ();

	updateInfo();
}

void BuyConfirmPopLayer2::createScene ()
{
	m_bCreateScene = true;

	setScale(ui_main_scale);
	//使屏幕变灰
	CCLayerColor* layer = CCLayerColor::create(ccc4(0x00, 0x00, 0x00, 0x3F), ui_w (1.0f), ui_h (1.0f));
	layer->setScale (1 / ui_main_scale);
	addChild (layer);

	CCScale9Sprite * m_pkPanel = CCScale9Sprite::createWithSpriteFrameName ("alert_background.png", CCRect (100, 100, 2, 2));
	m_pkPanel->setPreferredSize (CCSizeMake (752.0f, 518.0f));
	addChild(m_pkPanel);
	m_pkPanel->setPosition(ccp (ui_w (0.5), ui_h (0.5f)));    //把图片放到屏幕的中心位置

	CCLabelTTF * m_titleTex = CCLabelTTF::create(TT("TipTitle"), TTF_NAME, ODEFloorf(LOBBY_TITLE_TTF_SIZE * g_f32ScaleHD));
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
	AddWidget("kCloseBtn", pkCloseBtn);

	CCScale9Sprite * backgroundCancel = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel->setOpacity (0);
	CCScale9Sprite * backgroundCancel2 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel2->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	CCSprite * logo = CCSprite::createWithSpriteFrameName ("input_frame_2.png");
	logo->setOpacity (0);
	NormalButtonWithText * m_canaelBtn = ODE_NEW NormalButtonWithText(backgroundCancel, backgroundCancel2, logo, TT ("UITextSettlementExit"));
	m_canaelBtn->setPosition(ccp (m_pkPanel->boundingBox ().getMidX () - m_canaelBtn->getContentSize ().width / 2, m_pkPanel->boundingBox ().getMinY () + 10 + m_canaelBtn->getContentSize ().height / 2));	
	AddWidget("ChangeAccountPopupLayer_quit", m_canaelBtn);
	m_canaelBtn->SetTextWithColor (TT ("Cancel"), ccc3 (155, 160, 175));
	UILinkDelegate(m_canaelBtn, OnCancel);

	CCScale9Sprite * backgroundCancel3 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel3->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel3->setOpacity (0);
	CCScale9Sprite * backgroundCancel4 = CCScale9Sprite::createWithSpriteFrameName ("alert_cancel.png", CCRect (10, 10, 2, 2));
	backgroundCancel4->setPreferredSize (CCSizeMake ((m_pkPanel->getContentSize ().width - 20) / 2, 89));
	backgroundCancel4->setRotationY (180.0f);
	CCSprite * logo2 = CCSprite::createWithSpriteFrameName ("input_frame_2.png");
	logo2->setOpacity (0);
	NormalButtonWithText * m_getchargeBtn = ODE_NEW NormalButtonWithText(backgroundCancel3, backgroundCancel4, logo2, TT ("UIText_Receivereward"));
	m_getchargeBtn->setPosition(ccp (m_pkPanel->boundingBox ().getMidX () + m_getchargeBtn->getContentSize ().width / 2, m_pkPanel->boundingBox ().getMinY () + 10 + m_getchargeBtn->getContentSize ().height / 2));
	AddWidget("ChangeAccountPopupLayer_getaward", m_getchargeBtn);
	m_getchargeBtn->SetTextWithColor (TT ("Confirm"), ccc3 (51, 177, 77));
	UILinkDelegate(m_getchargeBtn, OnConfirm);

	m_text2 = CCLabelTTF::create("", TTF_NAME, ODEFloorf(LOBBY_NORMAL_TTF_SIZE * g_f32ScaleHD));
	m_text2->setColor(ccc3(255.0f, 255.0f, 255.0f));
	m_text2->setPosition(ccp (m_pkPanel->boundingBox ().getMidX (),m_pkPanel->boundingBox().getMidY()));
	addChild(m_text2);

	CCSprite * m_line2 = CCSprite::createWithSpriteFrameName ("alert_line2.png");
	m_line2->setFlipY (true);
	m_line2->setScaleY (89 / m_line2->getContentSize ().height);
	m_line2->setPosition (ccp (m_pkPanel->boundingBox ().getMidX (), m_pkPanel->boundingBox ().getMinY () + 8 + m_canaelBtn->getContentSize ().height / 2));
	addChild (m_line2);

	CCSprite * m_line1 = CCSprite::createWithSpriteFrameName ("alert_line_1.png");
	m_line1->setScaleX ((m_pkPanel->getContentSize ().width - 16) / m_line1->getContentSize ().width);
	m_line1->setPosition (ccp (m_pkPanel->boundingBox ().getMidX (), m_line2->boundingBox ().getMaxY ()));
}

void BuyConfirmPopLayer2::OnDeactive(const ODUIUserDataPtr& spData)
{

}

void BuyConfirmPopLayer2::term ()
{
	ODUILayer::term ();
}

bool BuyConfirmPopLayer2::OnBack ()
{
	return true;
}

void BuyConfirmPopLayer2::OnMenu ()
{

}

void BuyConfirmPopLayer2::onExit ()
{
	ODUILayer::onExit();
}


void BuyConfirmPopLayer2::updateInfo ()
{
	int index = g_pkClientData->GetUserBuyHeadIndex();
	int price = g_pkLobbyConnectData->getOnSaleItemsListInfo(index)->nPrice;
	int salerate = g_pkLobbyConnectData->getOnSaleItemsListInfo(index)->nSaleRate;
	char m_labelbuffer2[100] = {0};
	sprintf(m_labelbuffer2, TT("UITextBuyHeadImageConfirm_2"), price * salerate/100);
	m_text2->setString(m_labelbuffer2);
}


void BuyConfirmPopLayer2::OnFadeIn()
{}

void BuyConfirmPopLayer2::OnFadeOut()
{
	g_pkGuanDanGame->addChangeIndexToQuene(LAYER_MANAGER_QUENE_MAIN_LAYER);
	g_pkGuanDanGame->FadeIn(FADE_IN_TIME);
}

UIImplementDelegate(BuyConfirmPopLayer2, OnClose, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopLayer();
	}
}

UIImplementDelegate(BuyConfirmPopLayer2, OnCancel, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopLayer();
	}
}

UIImplementDelegate(BuyConfirmPopLayer2, OnConfirm, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		int index = g_pkClientData->GetUserBuyHeadIndex();
		int price = g_pkLobbyConnectData->getOnSaleItemsListInfo(index)->nPrice;
		int salerate = g_pkLobbyConnectData->getOnSaleItemsListInfo(index)->nSaleRate;
		if(g_pkClientData->GetUserScore() < price * salerate / 100)
		{
			g_pLayerManager->PopLayer();
			if (g_pLayerManager->GetLayer ("ScoreNotEnoughPopupLayer") != NULL)
				g_pLayerManager->PushLayer ("ScoreNotEnoughPopupLayer");
			else
			{
				g_pLayerManager->AddLayer(ScoreNotEnoughPopupLayer::create());
				g_pLayerManager->PushLayer ("ScoreNotEnoughPopupLayer");
			}
		}
		else
		{
			if(IsNetwork())
			{
				g_pkGuanDanGame->ShowLoading(true);
				if (g_pkNetworkHelper->GetLobbyAlwaysConnectDelegate () && g_pkNetworkHelper->GetLobbyAlwaysConnectDelegate ()->IsConnect())
				{
					g_pkNetworkHelper->SendBuyHeadImage(index,price * salerate / 100);
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
			g_pLayerManager->PopLayer();
		}
	}
}