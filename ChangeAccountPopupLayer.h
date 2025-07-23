#pragma once

#include "GameCommon.h"

#include "Knickknacks.h"

class ChangeAccountPopupLayer : public ODUILayerModalExt<ChangeAccountPopupLayer>
{
public:

	ChangeAccountPopupLayer ();

	virtual ~ChangeAccountPopupLayer ();

	virtual bool init ();

	virtual void term ();

	virtual void OnActive(const ODUIUserDataPtr& spData);

	virtual void OnDeactive(const ODUIUserDataPtr& spData);

	virtual bool OnBack();

	virtual void OnMenu();

	virtual void onExit();

	void ResetContentData ();

	void ResetQuitContentData ();

	ODE_CREATE_FUNC(ChangeAccountPopupLayer);

	typedef ODEMemberDelegate<ChangeAccountPopupLayer> FadeDelegate;

	void createScene ();

	void createQuitContent ();

	void removeCreateData ();

protected:

	void OnFadeIn();
	FadeDelegate m_kOnFadeIn;

	void OnFadeOut();
	FadeDelegate m_kOnFadeOut;

	void updateRound();

	UIDeclareDelegate(OnClose);
	UIDeclareDelegate(OnQuit);
	UIDeclareDelegate(OnGetaward);

	CCScale9Sprite * m_pkPanel;

	CCLabelTTF * m_QuitMessageTitleStart;
	CCLabelTTF * m_QuitMessageTitleAccount;
	CCLabelTTF * m_QuitMessageTitleEnding;

	CCLabelTTF * m_ContentMessageStart;
	CCLabelTTF * m_ContentMessageContent;
	CCLabelTTF * m_ContentMessageEnding;
	CCLabelTTF * m_ContentMessageEnding2;

	CCLabelTTF * m_GetAwardMessageStart;
	CCLabelTTF * m_GetAwardMessageEnd;

	CCLabelTTF * m_ExitMesssage;

private:

	bool m_bCreateScene;

};
