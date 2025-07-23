#include "AppDelegate.h"
#include "ODEEngine.h"
#include "MainScene.h"
#include "SoundSystem.h"
#include "GameSaveData.h"
#include "NetworkDelegate.h"
#include "ClientData.h"
#include "PayNotify.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	SoundSystem::Destory();
	GameSaveData::Destory();
	NetworkTickThread::Destory();
	ClientData::Destory();
	GuanDanGamePlayerData::Destory();
	GuanDanGameActiveData::Destory();
	ODETerm();
	 BuyNotify::sharedConfig()->onExit();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	pDirector->setProjection(kCCDirectorProjection2D);

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	ODEInit();

	ODE_NEW SoundSystem;
	ODE_NEW GameSaveData;
	ODE_NEW NetworkTickThread;
	ODE_NEW ClientData;
	ODE_NEW GuanDanGamePlayerData;
	ODE_NEW GuanDanGameActiveData;

	ODE_NEW GuanDanData;

	GuanDanData::GetSingletonPtr()->init();

	BuyNotify::sharedConfig();
    // create a scene. it's an autorelease object
	CCScene *pScene = MainScene::create();
	g_pkClientData->SetCanGoBack(false);
	g_pkClientData->setIsInForeground(true);
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {

	//如果玩家在游戏中，则发送离开桌子的消息;
	if(g_pLayerManager->IsExitInMiddleLayer("guandanGame") && !g_pkGuanDanData->GetIsNeedGuideInGD() && g_pLayerManager->GetCurrentMainLayer()!=NULL)
	{
		g_pkNetworkHelper->SendGameServerPlayerLeaveTableMsg(TPL_GAME_CLIENT_LEAVE);
		g_pkGuanDanGame->addChangeIndexToQuene(LAYER_MANAGER_QUENE_BACK);

		g_pkClientData->ClearGameMessageBuffer();
	}
	else if (g_pLayerManager->IsExitInMiddleLayer("guandanGame") && g_pkGuanDanData->GetIsNeedGuideInGD())
	{
		g_pkGuanDanGame->addChangeIndexToQuene(LAYER_MANAGER_QUENE_BACK);
	}

#if ANDROID_IPTV_CONTROL_USE == 0
	//g_pkClientData->SetNeedNewPlayerGuide(false);//新手引导的关闭
	g_pkGuanDanData->SetIsNeedGuideInGD(false);
#endif	

	g_pkNetworkHelper->CloseGameServerSocket();
    CCDirector::sharedDirector()->stopAnimation();
	g_pkGuanDanGame->m_isKeepLoopConnect = false;
	g_pkClientData->setIsInForeground(false);
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	if (g_pSoundSystem)
		g_pSoundSystem->Pause();

	
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
	if (g_pkGuanDanGame)
		g_pkGuanDanGame->m_isKeepLoopConnect = true;
	if (g_pkClientData)
		g_pkClientData->setIsInForeground(true);
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	if (g_pSoundSystem)
		g_pSoundSystem->Resume();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (g_pkGuanDanGame)
		g_pkGuanDanGame->Restore();
#endif
}
