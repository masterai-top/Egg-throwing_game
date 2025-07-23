#ifndef __BREAK_LINE_RECONNECTION_HINT_H__
#define __BREAK_LINE_RECONNECTION_HINT_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"

class BreakLineReconnectionHint :public ODUILayerModalExt<BreakLineReconnectionHint>
{
public:
	typedef ODEMemberDelegate<BreakLineReconnectionHint,ODUIWidget&,ODEUInt32> UIDelegate;
	BreakLineReconnectionHint();
	~BreakLineReconnectionHint();

	bool init();

	void OnActive(const ODUIUserDataPtr& spData);
	void OnDeactive(const ODUIUserDataPtr& spData);

	void OnCreateSc();

	void StartGameInAndroid (int Gameindex);
	void StartGameInIOS();
	ODE_CREATE_FUNC(BreakLineReconnectionHint);

    void SetReConnectParameter(int quiciTime,int GameText,int RomText);
protected:
	UIDeclareDelegate(OnCancel);
	UIDeclareDelegate(OnYes);

private:
	bool b_createSc;
	//hallState current_state;
	int ptime;
	int GameID;
	CCLabelTTF* ConnetHit;

	int m_lastServerID;
	int m_lastGameID;
};
#endif