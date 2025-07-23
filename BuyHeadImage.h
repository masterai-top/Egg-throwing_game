#pragma once

#include "GameCommon.h"
#include "LobbyAssistScene.h"

class BuyHeadImage : public ODUILayerModalExt<BuyHeadImage>
{
public:

	BuyHeadImage ();

	virtual ~BuyHeadImage ();

	virtual bool init ();

	virtual void term ();

	virtual void OnActive(const ODUIUserDataPtr& spData);

	virtual void OnDeactive(const ODUIUserDataPtr& spData);

	virtual bool OnBack();

	virtual void OnMenu();

	virtual void onExit();

	virtual void updateInfo();

	//virtual void BuySuccess(ODEFloat32 f32Delta);

	ODE_CREATE_FUNC(BuyHeadImage);

	typedef ODEMemberDelegate<BuyHeadImage> FadeDelegate;

	void createScene ();

protected:

	void OnFadeIn();
	FadeDelegate m_kOnFadeIn;

	void OnFadeOut();
	FadeDelegate m_kOnFadeOut;

	ODUIButton* headimagebutton[6];
	ODUIButton* headimagebuttonD[4];

	CCLabelTTF* label1;
	CCLabelTTF* label2;

	CCLabelTTF* label3;

	//UIDeclareDelegate(OnConfirm);

	UIDeclareDelegate(OnClose);
	UIDeclareDelegate(OnBuy1);
	UIDeclareDelegate(OnBuy2);
	UIDeclareDelegate(OnUse);

private:

	bool m_bCreateScene;	
	long long timevaluesec;
	struct cc_timeval now;
	//int time_sec ;
	//int time_valuesec;
	//struct tm * localptm;

};