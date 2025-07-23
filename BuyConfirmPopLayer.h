#pragma once

#include "GameCommon.h"
#include "Knickknacks.h"

class BuyConfirmPopLayer : public ODUILayerModalExt<BuyConfirmPopLayer>
{
public:

	BuyConfirmPopLayer ();

	virtual ~BuyConfirmPopLayer ();

	virtual bool init ();

	virtual void term ();

	virtual void OnActive(const ODUIUserDataPtr& spData);

	virtual void OnDeactive(const ODUIUserDataPtr& spData);

	virtual bool OnBack();

	virtual void OnMenu();

	virtual void onExit();

	ODE_CREATE_FUNC(BuyConfirmPopLayer);

	typedef ODEMemberDelegate<BuyConfirmPopLayer> FadeDelegate;

	void updateInfo ();

	void createScene ();

protected:

	void OnFadeIn();
	FadeDelegate m_kOnFadeIn;

	void OnFadeOut();
	FadeDelegate m_kOnFadeOut;

	CCLabelTTF* m_text1;

	UIDeclareDelegate(OnClose);
	UIDeclareDelegate(OnCancel);
	UIDeclareDelegate(OnConfirm);

private:

	bool m_bCreateScene;

};


class BuyConfirmPopLayer2 : public ODUILayerModalExt<BuyConfirmPopLayer2>
{
public:

	BuyConfirmPopLayer2 ();

	virtual ~BuyConfirmPopLayer2 ();

	virtual bool init ();

	virtual void term ();

	virtual void OnActive(const ODUIUserDataPtr& spData);

	virtual void OnDeactive(const ODUIUserDataPtr& spData);

	virtual bool OnBack();

	virtual void OnMenu();

	virtual void onExit();

	ODE_CREATE_FUNC(BuyConfirmPopLayer2);

	typedef ODEMemberDelegate<BuyConfirmPopLayer2> FadeDelegate;

	void updateInfo ();

	void createScene ();

protected:

	void OnFadeIn();
	FadeDelegate m_kOnFadeIn;

	void OnFadeOut();
	FadeDelegate m_kOnFadeOut;

	CCLabelTTF* m_text2;

	UIDeclareDelegate(OnClose);
	UIDeclareDelegate(OnCancel);
	UIDeclareDelegate(OnConfirm);

private:

	bool m_bCreateScene;

};
