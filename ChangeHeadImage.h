#pragma once

#include "GameCommon.h"
#include "LobbyAssistScene.h"

enum PersonalHeaderStatus
{
	PersonalHeaderStatus_None = -1,
	PersonalHeaderStatus_Ready = 0,
	PersonalHeaderStatus_NotBuy,
	PersonalHeaderStatus_InUse,
	PersonalHeaderStatus_Buyed,
	PersonalHeaderStatus_Max,
};
class PersonalHeaderImageButton : public ODUIButton 
{
public:
	PersonalHeaderImageButton (cocos2d::CCNode* pkNormal, cocos2d::CCNode* pkPressed, cocos2d::CCNode* pkDisable, cocos2d::CCNode * pkHeaderImage, int headerIndex, int status);
	~PersonalHeaderImageButton ();
	void SetPersonalHeaderStatus (int status);
	int GetPersonalHeaderStatus ();
	void SetPersonalHeaderIndex (int index);
	int GetPersonalHeaderIndex ();
	void OnEvent(ODUIWidget& kWidget, ODEUInt32 u32State);
private:
	int m_personalHeaderStatus;
	int m_personalHeaderIndex;
	cocos2d::CCSprite * m_inUserSprite;
	CCScale9Sprite * m_inUserBackgroundSprite;
	cocos2d::CCSprite * m_notBuySprite;
	cocos2d::CCSprite * m_headerImage;
};
#define MAX_HEADER_IMAGE_NUMS_PER_BAR 5
#define DEFAULT_HEADER_IMAGE_SPACE_SIZE 4
#define DEFAULT_HEADER_IMAGE_WIDTH 120.0f
#define DEFAULT_HEADER_IMAGE_HEIGHT 120.0f
class PersonalHeaderImageBar : public ODUIWidget
{
public:
	PersonalHeaderImageBar (float x, float y);
	~PersonalHeaderImageBar ();
	void addPersonalHeaderImageButton (PersonalHeaderImageButton * ImageButton);
	void SetBarIndex (int index);
	int GetBarIndex ();
	bool isFull ();
	int getImageButtonCounts ();
	ODEVector <PersonalHeaderImageButton *> m_PersonalHeaderImageButtons;
private:
	float m_width;
	float m_height;
	int m_personalBarIndex;
	CCNode * m_baseBackgroundNode;
	void removePersonalImageButton ();
};
class PersonalHeaderImageList : public ODUIScrollView
{
public:
	typedef ODEMemberDelegate<PersonalHeaderImageList, ODUIWidget&, ODEUInt32> UIDelegate;
	PersonalHeaderImageList(ODEFloat32 w, ODEFloat32 h);
	virtual ~PersonalHeaderImageList();
	ODEInt32 GetBarCount ();
	void setHeaderImageStatus (int headerImageIndex, int status);
	void resetHeaderImagesForReady (int headerImageIndex, int status = PersonalHeaderStatus_InUse);
	int getPersonalHeaderImageButtonCount ();
	bool hasEmptyBar ();
	void addPersonalHeaderButton (PersonalHeaderImageButton * button);
	void removeAllButton ();
protected:
	float m_buttonPositionY;
	ODEUInt32 addPersonalHeaderImageBar(PersonalHeaderImageBar * buttonAdd);
	struct Item
	{
		Item();
		PersonalHeaderImageBar* m_pkButton;
		UIDelegate m_kDelegate;
	};
	ODEVector<Item> m_kButtonArray;
	ODEFloat32 m_fWidth;
	ODEFloat32 m_fHeight;
};
class ChangeHeadImage : public ODUILayerModalExt<ChangeHeadImage>
{
public:

	ChangeHeadImage ();

	virtual ~ChangeHeadImage ();

	virtual bool init ();

	virtual void term ();

	virtual void OnActive(const ODUIUserDataPtr& spData);

	virtual void OnDeactive(const ODUIUserDataPtr& spData);

	virtual bool OnBack();

	virtual void OnMenu();

	virtual void onExit();

	void createPersonalBtnsList ();

	void resetPersonalBtnsStatus ();



	void reloadPeronalBtns ();




	void runanimation();

	/*virtual void BuyAnimationStart();

	virtual void BuyAnimationEnd();

	virtual void ShowBuySuccess();*/

	ODE_CREATE_FUNC(ChangeHeadImage);

	typedef ODEMemberDelegate<ChangeHeadImage> FadeDelegate;

	void createScene ();

	/*void createPageNode(int m_node_nums);

	void createPageNode2(int m_pernode_nums);

	void UpdatePageNode (ODEFloat32 u32Delta) ;

	void UpdatePageNode2 (ODEFloat32 u32Delta) ;*/


	//PersonalCenter* PC;

protected:

	void OnFadeIn();
	FadeDelegate m_kOnFadeIn;

	void OnFadeOut();
	FadeDelegate m_kOnFadeOut;

	//UIDeclareDelegate(OnConfirm);

	UIDeclareDelegate(OnClose);


private:

	PersonalHeaderImageList  * headerImageList;
	bool m_bCreateScene;
	CCSprite * logoyes;
	CCScale9Sprite * m_pkPanel;
	CCSprite * m_lineArea2;
	CCSprite * m_lineArea1;
	CCSprite* pkAnima;
	CCSprite* pkHead;
	//CCAnimation* buyAnima;
	CCLayerColor* layer;

	//HeadImageBuyEffects* m_Effect;
	

	

};

class LobbyHeadImageBuySuccessEffect : public ODUILayerModalExt<LobbyHeadImageBuySuccessEffect>
{
public:

	LobbyHeadImageBuySuccessEffect();

	virtual ~LobbyHeadImageBuySuccessEffect();

	virtual bool init();

	virtual void OnActive(const ODUIUserDataPtr& spData);

	virtual void OnDeactive(const ODUIUserDataPtr& spData);

	virtual bool OnBack();

	virtual void term();

	ODE_CREATE_FUNC(LobbyHeadImageBuySuccessEffect);

	void createScene ();

	void CreateAnimation();

	void BuyAnimationStart();

	void BuyAnimationEnd();

	void ShowBuySuccess();

	bool  m_bCreateScene ;
private:
	HeadImageBuyEffects* m_Effect;
	CCSprite* pkAnima;
	CCSprite* pkHead;
	CCAnimation* buyAnima;

};

