#include "ChangeHeadImage.h"
#include "LobbyAssistScene.h"
#include "BuyHeadImage.h"
#include "LobbyPersonalCenter.h"

PersonalHeaderImageButton::PersonalHeaderImageButton (cocos2d::CCNode* pkNormal, cocos2d::CCNode* pkPressed, cocos2d::CCNode* pkDisable, cocos2d::CCNode * pkHeaderImage, int headerIndex, int status)
	:ODUIButton (pkNormal, pkPressed, pkDisable), m_headerImage (NULL),  m_inUserSprite (NULL), m_notBuySprite (NULL), m_inUserBackgroundSprite (NULL), m_personalHeaderStatus (PersonalHeaderStatus_None), m_personalHeaderIndex (0)
{
	addChild (pkHeaderImage, 3);
	SetPersonalHeaderStatus (status);
	SetPersonalHeaderIndex (headerIndex);
	if (headerIndex < 1000)
	{
		pkHeaderImage->setAnchorPoint (ccp (0.5f, 0.0f));
		pkHeaderImage->setPosition (ccp (m_pkNormal->boundingBox ().getMidX (), m_pkNormal->boundingBox ().getMinY () + 2.5f));
	}
}
PersonalHeaderImageButton::~PersonalHeaderImageButton ()
{
}
void PersonalHeaderImageButton::SetPersonalHeaderStatus (int status)
{
	if (m_personalHeaderStatus == status)
		return ;
	if (m_inUserSprite != NULL)
		removeChild (m_inUserSprite);
	if (m_notBuySprite != NULL)
		removeChild (m_notBuySprite);
	if (m_inUserBackgroundSprite != NULL)
		removeChild (m_inUserBackgroundSprite);
	m_personalHeaderStatus = status;
	switch (m_personalHeaderStatus)
	{
	case PersonalHeaderStatus_Ready:
		break;
	case PersonalHeaderStatus_NotBuy:
		m_notBuySprite = CCSprite::create ("image/personalCenter/head_cannot_use.png");
		m_notBuySprite->setAnchorPoint (ccp (0.0f, 1.0f));
		m_notBuySprite->setPosition (ccp (m_pkNormal->boundingBox ().getMinX (), m_pkNormal->boundingBox ().getMaxY ()));
		addChild (m_notBuySprite, 3);
        CCTextureCache::sharedTextureCache()->removeTextureForKey("image/personalCenter/head_cannot_use.png");
		break;
	case PersonalHeaderStatus_InUse:
		m_inUserBackgroundSprite = CCScale9Sprite::create("image/personalCenter/personalCenterPress.png");
		m_inUserBackgroundSprite->setPreferredSize (CCSizeMake (124, 124));
		addChild (m_inUserBackgroundSprite, 3);
		m_inUserSprite = CCSprite::create ("image/personalCenter/center_yes.png");
		m_inUserSprite->setAnchorPoint (ccp (1.0f, 0.0f));
		m_inUserSprite->setPosition (ccp (m_pkNormal->boundingBox ().getMaxX (), m_pkNormal->boundingBox ().getMinY ()));
		addChild (m_inUserSprite, 3);
        CCTextureCache::sharedTextureCache()->removeTextureForKey("image/personalCenter/personalCenterPress.png");
		break;
	case PersonalHeaderStatus_Buyed:
		m_notBuySprite = CCSprite::create ("image/personalCenter/head_can_use.png");
		m_notBuySprite->setAnchorPoint (ccp (0.0f, 1.0f));
		m_notBuySprite->setPosition (ccp (m_pkNormal->boundingBox ().getMinX (), m_pkNormal->boundingBox ().getMaxY ()));
		addChild (m_notBuySprite, 3);
		CCTextureCache::sharedTextureCache()->removeTextureForKey("image/personalCenter/head_can_use.png");
		break;
	default:
		break;
	}
}
int PersonalHeaderImageButton::GetPersonalHeaderStatus ()
{
	return m_personalHeaderStatus;
}
void PersonalHeaderImageButton::SetPersonalHeaderIndex (int index)
{
	if (m_personalHeaderIndex == index)
		return ;
	if (m_headerImage != NULL)
		removeChild (m_headerImage);
	m_personalHeaderIndex = index;
}
int PersonalHeaderImageButton::GetPersonalHeaderIndex ()
{
	return m_personalHeaderIndex;
}
void PersonalHeaderImageButton::OnEvent(ODUIWidget& kWidget, ODEUInt32 u32State)
{
	if(u32State == RELEASED)
	{
		switch (GetPersonalHeaderStatus ())
		{
		case PersonalHeaderStatus_Buyed:
			/*if(IsNetwork())
			{
				g_pkGuanDanGame->ShowLoading(true);
				if (g_pkNetworkHelper->GetLobbyAlwaysConnectDelegate () && g_pkNetworkHelper->GetLobbyAlwaysConnectDelegate ()->IsConnect())
				{
					g_pkNetworkHelper->SendSetHeadImage(GetPersonalHeaderIndex ());
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
			break;*/
			if (g_pLayerManager->GetLayer ("BuyHeadImage") != NULL)
			{
				g_pkClientData->SetUserBuyHeadIndex(GetPersonalHeaderIndex ());
				g_pLayerManager->PushLayer ("BuyHeadImage");
			}
			else
			{
				g_pkClientData->SetUserBuyHeadIndex(GetPersonalHeaderIndex ());
				g_pLayerManager->AddLayer (BuyHeadImage::create ());
				g_pLayerManager->PushLayer ("BuyHeadImage");
			}
			break;
		case PersonalHeaderStatus_InUse:
			g_pkGuanDanGame->Toast(TT("UITest_HeadImageIsUsing"));
			break;
		case PersonalHeaderStatus_NotBuy:
			if (g_pLayerManager->GetLayer ("BuyHeadImage") != NULL)
			{
				g_pkClientData->SetUserBuyHeadIndex(GetPersonalHeaderIndex ());
				g_pLayerManager->PushLayer ("BuyHeadImage");
			}
			else
			{
				g_pkClientData->SetUserBuyHeadIndex(GetPersonalHeaderIndex ());
				g_pLayerManager->AddLayer (BuyHeadImage::create ());
				g_pLayerManager->PushLayer ("BuyHeadImage");
			}
			break;
		case PersonalHeaderStatus_Ready:
			if(IsNetwork())
			{
				g_pkGuanDanGame->ShowLoading(true);
				if (g_pkNetworkHelper->GetLobbyAlwaysConnectDelegate () && g_pkNetworkHelper->GetLobbyAlwaysConnectDelegate ()->IsConnect())
				{
					g_pkNetworkHelper->SendSetHeadImage(GetPersonalHeaderIndex ());
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
			break;
		default:
			break;
		};
	}
}
PersonalHeaderImageBar::PersonalHeaderImageBar (float x, float y) : m_width (x), m_height (y)
{
	m_baseBackgroundNode =  CCLayerColor::create(ccc4(0x00, 0x00, 0x00, 0x00), m_width, m_height);
	addChild (m_baseBackgroundNode);
	m_PersonalHeaderImageButtons.Clear ();
	setContentSize (ccp (x, y));
}
PersonalHeaderImageBar::~PersonalHeaderImageBar ()
{
	removePersonalImageButton ();
}
void PersonalHeaderImageBar::removePersonalImageButton ()
{
	removeChild (m_baseBackgroundNode);
	for (int i = 0; i < m_PersonalHeaderImageButtons.Size(); ++i)
	{
		removeChild (m_PersonalHeaderImageButtons.At (i));
		delete m_PersonalHeaderImageButtons.At (i);
	}
	m_PersonalHeaderImageButtons.Clear();
}
void PersonalHeaderImageBar::SetBarIndex (int index)
{
	m_personalBarIndex = index;
}
int PersonalHeaderImageBar::GetBarIndex ()
{
	return m_personalBarIndex;
}
bool PersonalHeaderImageBar::isFull ()
{
	if (getImageButtonCounts () >= MAX_HEADER_IMAGE_NUMS_PER_BAR)
		return true;
	else
		return false;
}
int PersonalHeaderImageBar::getImageButtonCounts ()
{
	return m_PersonalHeaderImageButtons.Size ();
}
void PersonalHeaderImageBar::addPersonalHeaderImageButton (PersonalHeaderImageButton * ImageButton)
{
	m_PersonalHeaderImageButtons.PushBack (ImageButton);
	for (int i = 0; i < m_PersonalHeaderImageButtons.Size(); ++i)
	{
		PersonalHeaderImageButton * buttons = m_PersonalHeaderImageButtons.At(i);
		buttons->setPosition (ccp (m_baseBackgroundNode->boundingBox ().getMinX () + (10 + DEFAULT_HEADER_IMAGE_WIDTH + DEFAULT_HEADER_IMAGE_SPACE_SIZE) * i + (DEFAULT_HEADER_IMAGE_WIDTH + DEFAULT_HEADER_IMAGE_SPACE_SIZE) / 2.0f, m_baseBackgroundNode->boundingBox ().getMidY () - (DEFAULT_HEADER_IMAGE_HEIGHT + DEFAULT_HEADER_IMAGE_SPACE_SIZE) / 2.0f));
	}
	AddChild (ImageButton);
}
PersonalHeaderImageList::Item::Item()
{
	m_pkButton = NULL;
}
PersonalHeaderImageList::PersonalHeaderImageList(ODEFloat32 w, ODEFloat32 h)
	: ODUIScrollView(w * ui_main_scale, h * ui_main_scale,
	"scroll_bean.png", "scroll_bean_ext.png", 3.0f * g_f32ScaleHD)
	,m_fWidth(w)
	,m_fHeight(h)
{
	setContentSize (CCSizeMake (w * ui_main_scale, h  * ui_main_scale));
	setAnchorPoint(ccp(0.5f,1.0f));	
	SetScrollBarColor(ccc3(191,194,225));
	m_buttonPositionY = -245.0f * ui_height_scale;
}
PersonalHeaderImageList::~PersonalHeaderImageList()
{
}
ODEUInt32 PersonalHeaderImageList::addPersonalHeaderImageBar (PersonalHeaderImageBar * buttonAdd)
{
	ODEUInt32 u32Res = m_kButtonArray.Size();
	PersonalHeaderImageBar * pkEvent = buttonAdd;
	Item contentList;
	contentList.m_pkButton = buttonAdd;
	ODEUInt32 u32Row = u32Res;
	pkEvent->SetBarIndex(u32Res);
	pkEvent->setPosition(ccp(22.0f * ui_main_scale, m_buttonPositionY - pkEvent->getContentSize ().height * ui_main_scale));
	AddChild(pkEvent);
	m_buttonPositionY -= pkEvent->getContentSize ().height * ui_main_scale;
	m_kButtonArray.PushBack (contentList);
	return u32Res;
}
void PersonalHeaderImageList::resetHeaderImagesForReady (int headerImageIndex, int status)
{
	for (int i = 0; i < m_kButtonArray.Size(); ++i)
	{
		Item& contentList = m_kButtonArray.At(i);
		for (int j = 0; j < contentList.m_pkButton->m_PersonalHeaderImageButtons.Size (); j++)
		{
			PersonalHeaderImageButton * button = (PersonalHeaderImageButton *)(contentList.m_pkButton->m_PersonalHeaderImageButtons.At(j));
			if (button->GetPersonalHeaderStatus () == PersonalHeaderStatus_InUse)
			{
				if (button->GetPersonalHeaderIndex () < 1000)
				{
					button->SetPersonalHeaderStatus (PersonalHeaderStatus_Ready); 
				}
				else
				{
					button->SetPersonalHeaderStatus (PersonalHeaderStatus_Buyed);
				}
			}
			if (button->GetPersonalHeaderIndex () == headerImageIndex)
			{
				button->SetPersonalHeaderStatus (status);
			}
		}
	}
}
void PersonalHeaderImageList::setHeaderImageStatus (int headerImageIndex, int status)
{
	for (int i = 0; i < m_kButtonArray.Size(); ++i)
	{
		Item& contentList = m_kButtonArray.At(i);
		for (int j = 0; j < contentList.m_pkButton->m_PersonalHeaderImageButtons.Size (); j++)
		{
			PersonalHeaderImageButton * button = (PersonalHeaderImageButton *)(contentList.m_pkButton->m_PersonalHeaderImageButtons.At(j));
			if (button->GetPersonalHeaderIndex () == headerImageIndex)
			{
				button->SetPersonalHeaderStatus (status);
			}
		}
	}
}
int PersonalHeaderImageList::getPersonalHeaderImageButtonCount ()
{
	int counts = 0;
	for (int i = 0; i < m_kButtonArray.Size(); ++i)
	{
		Item& contentList = m_kButtonArray.At(i);
		counts += contentList.m_pkButton->m_PersonalHeaderImageButtons.Size ();
	}
	return counts;
}
bool PersonalHeaderImageList::hasEmptyBar ()
{
	if (GetBarCount () == 0)
		return false;
	if (getPersonalHeaderImageButtonCount () % MAX_HEADER_IMAGE_NUMS_PER_BAR == 0 && getPersonalHeaderImageButtonCount () == GetBarCount () * MAX_HEADER_IMAGE_NUMS_PER_BAR)
		return false;
	else
		return true;
}
void PersonalHeaderImageList::addPersonalHeaderButton (PersonalHeaderImageButton * button)
{
	if (!hasEmptyBar ())
	{
		PersonalHeaderImageBar * imageBar = ODE_NEW  PersonalHeaderImageBar ((DEFAULT_HEADER_IMAGE_WIDTH + DEFAULT_HEADER_IMAGE_SPACE_SIZE) * MAX_HEADER_IMAGE_NUMS_PER_BAR * 2 + (MAX_HEADER_IMAGE_NUMS_PER_BAR + 1) * 10.0f, DEFAULT_HEADER_IMAGE_HEIGHT + 20.0f);
		imageBar->setScale (ui_main_scale);
		addPersonalHeaderImageBar(imageBar);
		imageBar->addPersonalHeaderImageButton (button);
	}
	else
	{
		int counts = GetBarCount ();
		Item& contentList = m_kButtonArray.At(counts - 1);
		contentList.m_pkButton->addPersonalHeaderImageButton (button);
	}
}
ODEInt32 PersonalHeaderImageList::GetBarCount ()
{
	return m_kButtonArray.Size ();
}
void PersonalHeaderImageList::removeAllButton()
{
	for (int i = 0; i < m_kButtonArray.Size(); ++i)
	{
		Item& contentList = m_kButtonArray.At(i);
		removeChild (contentList.m_pkButton);
		delete contentList.m_pkButton;
	}
	m_kButtonArray.Clear();
}
/**************************************************************************
Copyright:ODAO
 
Author: 
 
Date:   2014-10-24
 
Description:更换头像
 
**************************************************************************/

//bool ChangeHeadImage::m_bCreateScene = false;


ChangeHeadImage::ChangeHeadImage () : ODUILayerModalExt<ChangeHeadImage>("changeHeadImage")
    , m_bCreateScene(false)
	,headerImageList(NULL)
{
	m_kOnFadeIn.Set(this, &ChangeHeadImage::OnFadeIn);
	m_kOnFadeOut.Set(this, &ChangeHeadImage::OnFadeOut);

	UIInitDelegate(ChangeHeadImage, OnClose);

}

ChangeHeadImage::~ChangeHeadImage()
{
	term ();
	m_bCreateScene = false;
}

bool ChangeHeadImage::init ()
{
	return ODUILayerModalExt<ChangeHeadImage>::init();
}

void ChangeHeadImage::OnActive(const ODUIUserDataPtr& spData)
{
	if (!m_bCreateScene)
        createScene ();
	createPersonalBtnsList ();
}
void ChangeHeadImage::createPersonalBtnsList ()
{
	headerImageList = ODE_NEW PersonalHeaderImageList (720.0f , 400);
	int maxFreeCounts = 18;
	int iStart = 0;
	int iHeaderIndex = 0;
	char acBufferHeadName[100] = {0};

	if (g_pkClientData->GetUserHeadIndex () == 0)
	{
		if (g_pkClientData->GetUserGender () == 0)
		{
			g_pkClientData->SetUserHeadIndex (100);
		}
		else
		{
			g_pkClientData->SetUserHeadIndex (107);
		}
	}

	for (int i = 1000; i <= MAX_HEADER_IMAGE_INDEX; i++)
	{
		if (g_pkLobbyConnectData->getOnSaleItemsListInfo (i) != NULL)
		{
			if (g_pkLobbyConnectData->getUserItemsInfo (i) != 0)
			{
				CCScale9Sprite *  ebackground = CCScale9Sprite::create("image/personalCenter/personalCenterNormal.png");
				ebackground->setPreferredSize (CCSizeMake (124, 124));
				CCScale9Sprite * ebackground2 = CCScale9Sprite::create("image/personalCenter/personalCenterNormal.png");
				ebackground2->setPreferredSize (CCSizeMake (124, 124));
				ebackground2->setColor (ColorLevelDiv2 (ebackground2->getColor ()));
				iHeaderIndex = i + iStart;
				sprintf(acBufferHeadName, "image/personalCenter/LobbyBigheadimage_man_%d.png", i);
				if (!CCFileUtils::sharedFileUtils ()->isFileExist (acBufferHeadName))
					continue;
				CCSprite * headerImage = CCSprite::create (acBufferHeadName);
				headerImage->setScale ((DEFAULT_HEADER_IMAGE_WIDTH) / headerImage->getTextureRect ().size.width);
				int states = PersonalHeaderStatus_Buyed;
				if (g_pkClientData->GetUserHeadIndex () == i)
					states = PersonalHeaderStatus_InUse;
				PersonalHeaderImageButton * imageButton = ODE_NEW PersonalHeaderImageButton (ebackground, ebackground2, NULL, headerImage, iHeaderIndex, states);
				headerImageList->addPersonalHeaderButton (imageButton);
    }
		}
	}
	iStart = 96;
	for (int i = 0; i < 18; i++)
	{
		CCScale9Sprite *  ebackground = CCScale9Sprite::create("image/personalCenter/personalCenterNormal.png");
		ebackground->setPreferredSize (CCSizeMake (124, 124));
		CCScale9Sprite * ebackground2 = CCScale9Sprite::create("image/personalCenter/personalCenterNormal.png");
		ebackground2->setPreferredSize (CCSizeMake (124, 124));
		ebackground2->setColor (ColorLevelDiv2 (ebackground2->getColor ()));
		iHeaderIndex = i + iStart;
		sprintf(acBufferHeadName, "image/personalCenter/LobbyBigheadimage_man_%d.png", iHeaderIndex);
		CCSprite * headerImage = CCSprite::create (acBufferHeadName);
		headerImage->setScale ((DEFAULT_HEADER_IMAGE_WIDTH) / headerImage->getTextureRect ().size.width);
		int status = PersonalHeaderStatus_Ready;
		if (g_pkClientData->GetUserHeadIndex () == iHeaderIndex)
			status = PersonalHeaderStatus_InUse;
    else
			status = PersonalHeaderStatus_Ready;
		PersonalHeaderImageButton * imageButton = ODE_NEW PersonalHeaderImageButton (ebackground, ebackground2, NULL, headerImage, iHeaderIndex, status);
		headerImageList->addPersonalHeaderButton (imageButton);
	}
	iStart = 0;
	for (int i = 1000; i <= MAX_HEADER_IMAGE_INDEX; i++)
    {
		if (g_pkLobbyConnectData->getOnSaleItemsListInfo (i) != NULL)
		{
			if (g_pkLobbyConnectData->getUserItemsInfo (i) == 0)
			{
				CCScale9Sprite *  ebackground = CCScale9Sprite::create("image/personalCenter/personalCenterNormal.png");
				ebackground->setPreferredSize (CCSizeMake (124, 124));
				CCScale9Sprite * ebackground2 = CCScale9Sprite::create("image/personalCenter/personalCenterNormal.png");
				ebackground2->setPreferredSize (CCSizeMake (124, 124));
				ebackground2->setColor (ColorLevelDiv2 (ebackground2->getColor ()));
				iHeaderIndex = i + iStart;
				sprintf(acBufferHeadName, "image/personalCenter/LobbyBigheadimage_man_%d.png", i);
				if (!CCFileUtils::sharedFileUtils ()->isFileExist (acBufferHeadName))
					continue;
				CCSprite * headerImage = CCSprite::create (acBufferHeadName);
				headerImage->setScale ((DEFAULT_HEADER_IMAGE_WIDTH) / headerImage->getTextureRect ().size.width);
				int states = PersonalHeaderStatus_NotBuy;
				PersonalHeaderImageButton * imageButton = ODE_NEW PersonalHeaderImageButton (ebackground, ebackground2, NULL, headerImage, iHeaderIndex, states);
				headerImageList->addPersonalHeaderButton (imageButton);
			}
		}
	}
	headerImageList->ScrollToTop();
	headerImageList->setPosition(ccp(ui_w(0.5f), ui_h(0.5f) + 175.0f * ui_main_scale));
	AddWidget("personal_center_image_list", headerImageList);
}
void ChangeHeadImage::resetPersonalBtnsStatus ()
{
	if (headerImageList != NULL)
		headerImageList->resetHeaderImagesForReady  (g_pkClientData->GetUserHeadIndex ());
}
void ChangeHeadImage::reloadPeronalBtns ()
{
	DisableTouch ();

	if (headerImageList != NULL)
	{
		removeChild (headerImageList);
		headerImageList = NULL;
	}

	EnableTouch ();

	createPersonalBtnsList ();
}

void ChangeHeadImage::createScene ()
{
	m_bCreateScene = true;

	//CCLayerColor* layer = CCLayerColor::create(ccc4(0x00, 0x00, 0x00, 0x3F), ui_w (1.0f), ui_h (1.0f));
	//addChild (layer);

	headerImageList = NULL;
	m_pkPanel = CCScale9Sprite::create ("image/active/national_rule_background.png",CCRect (0, 0, 42, 154), CCRect (21, 77, 1, 1));
	m_pkPanel->setPreferredSize (CCSizeMake (750.0f, 550.0f));
	m_pkPanel->setScale(ui_main_scale);
	addChild(m_pkPanel);
	m_pkPanel->setPosition(ccp (ui_w (0.5), ui_h (0.5f)));

	CCLabelTTF * m_titleTex = CCLabelTTF::create(TT("UIText_ChangeHeadImage"), TTF_NAME, ODEFloorf(LOBBY_MAX_TTF_SIZE * g_f32ScaleHD*ui_main_scale));
	m_titleTex->setPosition ((ccp (m_pkPanel->boundingBox ().getMidX (), m_pkPanel->boundingBox ().getMaxY () - 42 *ui_main_scale)));
	addChild (m_titleTex);

	CCSprite* close = CCSprite::createWithSpriteFrameName("center_no.png");
	close->setScale(ui_main_scale);
	CCScale9Sprite * background = CCScale9Sprite::createWithSpriteFrameName ("top_bar_background.png");
	background->setPreferredSize (CCSizeMake (60, 60));
	background->setScale(ui_main_scale);
	background->setOpacity (0);
	CCScale9Sprite * background2 = CCScale9Sprite::createWithSpriteFrameName ("top_bar_background.png");
	background2->setPreferredSize (background->getContentSize ()*ui_main_scale);

	NormalButton* pkCloseBtn = ODE_NEW NormalButton(background, background2, close);
	pkCloseBtn->setPosition (ccp (m_pkPanel->boundingBox ().getMaxX () - pkCloseBtn->getContentSize ().width*ui_main_scale,m_titleTex->getPositionY ()));
	UILinkDelegate (pkCloseBtn, OnClose);
	pkCloseBtn->setContentSize(pkCloseBtn->getContentSize() * 2);
	pkCloseBtn->SetContentTouchSize (75.0f, 75.0f);
	AddWidget("kCloseBtn", pkCloseBtn);
}



void ChangeHeadImage::OnDeactive(const ODUIUserDataPtr& spData)
{
	CCTextureCache::sharedTextureCache()->removeTextureForKey("image/personalCenter/dian02.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("image/personalCenter/dian01.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("image/active/national_rule_background.png");

	if (headerImageList != NULL)
	{
		removeChild (headerImageList);
        CC_SAFE_DELETE(headerImageList);
		headerImageList = NULL;
	}

	char acBufferHeadName[256] = {0};
	
	for (int i = 96; i <= 113; i++)
	{
		sprintf(acBufferHeadName, "image/personalCenter/LobbyBigheadimage_man_%d.png", i);
		CCTextureCache::sharedTextureCache()->removeTextureForKey(acBufferHeadName);
	}

	for (int i = 1000; i <= MAX_HEADER_IMAGE_INDEX; i++)
	{
		sprintf(acBufferHeadName, "image/personalCenter/LobbyBigheadimage_man_%d.png", i);
		CCTextureCache::sharedTextureCache()->removeTextureForKey(acBufferHeadName);
	}

	g_pkGuanDanGame->ClearBackgroundTask ();

}

void ChangeHeadImage::term ()
{
	ODUILayer::term ();
}

bool ChangeHeadImage::OnBack ()
{
	return true;
}

void ChangeHeadImage::OnMenu ()
{
}

void ChangeHeadImage::onExit ()
{
	ODUILayer::onExit();
}

void ChangeHeadImage::runanimation()
{
	if (g_pLayerManager->GetLayer ("headimage_buy_success_effect") != NULL)
		g_pLayerManager->PushLayer ("headimage_buy_success_effect");
	else
	{
		g_pLayerManager->AddLayer(LobbyHeadImageBuySuccessEffect::create());
		g_pLayerManager->PushLayer ("headimage_buy_success_effect");
	}
}

void ChangeHeadImage::OnFadeIn()
{
}

void ChangeHeadImage::OnFadeOut()
{
	g_pkGuanDanGame->addChangeIndexToQuene(LAYER_MANAGER_QUENE_MAIN_LAYER);;
	g_pkGuanDanGame->FadeIn(FADE_IN_TIME);
}

UIImplementDelegate(ChangeHeadImage, OnClose, kWidget, u32State)
{
	if (u32State == ODUIWidget::RELEASED)
	{
		g_pLayerManager->PopAllLayers();
	}
}

//bool LobbyHeadImageBuySuccessEffect::m_bCreateScene = false;
LobbyHeadImageBuySuccessEffect::LobbyHeadImageBuySuccessEffect() : ODUILayerModalExt("headimage_buy_success_effect")
	,m_bCreateScene(false)
{
	//m_Effect = NULL;
	createScene();
	
}

LobbyHeadImageBuySuccessEffect::~LobbyHeadImageBuySuccessEffect()
{
	term();
	m_bCreateScene = false;
}

bool LobbyHeadImageBuySuccessEffect::init()
{
	return ODUILayerModalExt<LobbyHeadImageBuySuccessEffect>::init();
}

void LobbyHeadImageBuySuccessEffect::OnActive( const ODUIUserDataPtr& spData )
{
	CreateAnimation();
}

void LobbyHeadImageBuySuccessEffect::createScene ()
{
	m_bCreateScene = true;
	CCLayerColor* layer = CCLayerColor::create(ccc4(0x00, 0x00, 0x00, 0x7F), ui_w (1.0f), ui_h (1.0f));
	layer->setScale (1 / ui_main_scale);
	addChild (layer);
	
}

void LobbyHeadImageBuySuccessEffect::CreateAnimation()
{
	m_Effect = NULL;

	if(pkHead != NULL)
	{
		removeChild(pkHead);
		pkHead = NULL;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	char buyheadbuffer[100] = {0};
	sprintf(buyheadbuffer, "image/personalCenter/LobbyBigheadimage_man_%lld.png", g_pkClientData->GetUserBuyHeadIndex());

	if (cocos2d::CCFileUtils::sharedFileUtils()->isFileExist(buyheadbuffer))
	{
		pkHead = CCSprite::create(buyheadbuffer);
		pkHead->setPosition(ccp(size.width/2, size.height/2));
		//pkHead->setOpacity(0);
		addChild(pkHead);
		CCTextureCache::sharedTextureCache()->removeTextureForKey(buyheadbuffer);

		pkHead->setScale (0);
		CCScaleTo* scaleTo;
		CCScaleTo* scaleTo2;
		scaleTo = CCScaleTo::create(0.15f, 1.0f * 120.0f / 230.0f   +  1.0f * 120.0f / 230.0f);
		scaleTo2= CCScaleTo::create(0.15f, 1.0f * 120.0f / 230.0f  +  0.5f * 120.0f / 230.0f);

		CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(LobbyHeadImageBuySuccessEffect::BuyAnimationStart));
		pkHead->runAction (CCSequence::create (CCDelayTime::create (0.3F), scaleTo, scaleTo2, CCDelayTime::create(0.5), pkCall, NULL));
	}
	else
	{
		g_pLayerManager->PopLayer ();
	}
}

void LobbyHeadImageBuySuccessEffect::BuyAnimationStart()
{
	CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(LobbyHeadImageBuySuccessEffect::BuyAnimationEnd));


	if (m_Effect != NULL)
	{
		m_Effect->removeFromParent();
		ODE_DELETE(m_Effect);
	}
	m_Effect = new HeadImageBuyEffects ();
	m_Effect->setPosition(ui_ccp(0.5f, 0.5f));
	m_Effect->setScale (ui_main_scale);
	addChild(m_Effect);
	m_Effect->Play ();
	pkHead->runAction(CCSequence::create(CCDelayTime::create(1.0), pkCall, NULL));
}

void LobbyHeadImageBuySuccessEffect::BuyAnimationEnd()
{
	CCActionInterval* fadeout = CCFadeOut::create(0.3);
	CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(LobbyHeadImageBuySuccessEffect::ShowBuySuccess));
	pkHead->runAction(CCSequence::create(fadeout, pkCall, NULL));
}

void LobbyHeadImageBuySuccessEffect::ShowBuySuccess()
{
	pkHead->setVisible(false);
	g_pkGuanDanGame->Toast(TT("UITextTouXiangGouMaiSuccess"));
	g_pLayerManager->PopLayer();
}


void LobbyHeadImageBuySuccessEffect::OnDeactive( const ODUIUserDataPtr& spData )
{
}

bool LobbyHeadImageBuySuccessEffect::OnBack()
{
	return false;
}

void LobbyHeadImageBuySuccessEffect::term()
{
	ODUILayer::term();
}