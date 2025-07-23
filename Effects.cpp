#include "Effects.h"
#include "MainScene.h"
#include "GameSaveData.h"
#include "GameJNIPlatform.h"
#include "GuanDanLayer/GuanDanResource.h"
using namespace std;

StartEffects::StartEffects()
{
	createAnimation ();
}

StartEffects::~StartEffects()
{
	CC_SAFE_RELEASE(m_brakeAnimate);
	CC_SAFE_RELEASE(m_jumpAnimate);
	CC_SAFE_RELEASE(m_shineAnimate);
	CC_SAFE_RELEASE(m_rollingAnimate);
	CC_SAFE_RELEASE(m_swingAnimate);
	CC_SAFE_RELEASE(m_particleAnimate);
}

void StartEffects::createAnimation ()
{
	setScale(ui_main_scale);
	createWords ();
	createRunAnimation ();
	createBrakeAnimation ();
	createJumpAnimation ();
	createBigJumpAnimation ();
	createRollingAnimation ();
	createSwingAnimation ();
	createParticleAnimation ();
	createLights ();

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("image/loginkessen.plist");  
	CCTextureCache::sharedTextureCache()->removeTextureForKey("image/loginkessen.png");

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("image/particle.plist");  
	CCTextureCache::sharedTextureCache()->removeTextureForKey("image/particle.png");
}

void StartEffects::createWords ()
{
	ODEChar8 acBuffer[32];
	for (ODEInt32 i(0); i < 8; ++i)
	{
		ODESprintf(acBuffer, 32, "image/word_%d.png", i);
		pkWord[i] = CCSprite::create(acBuffer);
		if( i< 4)
		{
			pkWord[i]->setPosition(ccp(-145.0f + i * 35.0f, -130.0f * ui_height_scale / ui_main_scale));
		}
		if( i >= 4)
		{
			pkWord[i]->setPosition(ccp(-145.0f + i * 35.0f + 25.0f, -130.0f * ui_height_scale / ui_main_scale));
		}
		addChild(pkWord[i]);
		pkWordColor = pkWord[i]->getColor();
		pkWord[i]->setVisible(false);

		CCTextureCache::sharedTextureCache()->removeTextureForKey(acBuffer);
	}
}

void StartEffects::createRunAnimation ()
{
	m_runStartSpirte = CCSprite::create("image/kessen_circlerun_0.png");
	m_runStartSpirte->setPosition(ccp(-190.0f, -120.0f * ui_height_scale / ui_main_scale));
	addChild(m_runStartSpirte);

	m_runAnimation = CCAnimation::create();  
	char spriteFrameName[100] = {0};
	for (int i = 0; i < 30; i++)
	{
		sprintf (spriteFrameName, "image/kessen_circlerun_%d.png", i % 10);
		m_runAnimation->addSpriteFrameWithFileName(spriteFrameName);
		CCTextureCache::sharedTextureCache()->removeTextureForKey(spriteFrameName);
	}
	m_runAnimation->setDelayPerUnit(0.033f);
	m_runAnimate = CCAnimate::create (m_runAnimation);

}

void StartEffects::createBrakeAnimation ()
{
	m_spriteBatchNode = CCSpriteBatchNode::create("image/loginkessen.png");
	m_spriteFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
	m_spriteFrameCache->addSpriteFramesWithFile("image/loginkessen.plist");

	m_brakeStartSprite = CCSprite::createWithSpriteFrameName("kessen_runbrake_0.png");
	m_brakeStartSprite->setPosition(ccp(200.0f, -120.0f * ui_height_scale / ui_main_scale));
	m_brakeStartSprite->setVisible(false);
	m_spriteBatchNode->addChild(m_brakeStartSprite);
	addChild (m_spriteBatchNode);

	CCArray * animFrames = CCArray::createWithCapacity(35);
	char str[100] = {0};
	for(ODEInt32 i = 0; i < 35; i++)
	{
		sprintf(str, "kessen_runbrake_%d.png", i);
		animFrames->addObject(m_spriteFrameCache->spriteFrameByName(str));
	}
	CCAnimation* m_brakeAnimation = CCAnimation::createWithSpriteFrames(animFrames, 0.033f);
	m_brakeAnimation->setDelayPerUnit(0.033f);
	m_brakeAnimate = CCAnimate::create(m_brakeAnimation);
	m_brakeAnimate->retain ();
}

void StartEffects::createJumpAnimation ()
{
	m_jumpStartSprite = CCSprite::createWithSpriteFrameName("kessen_jump_0.png");
	m_jumpStartSprite->setPosition(ccp(200.0f, -120.0f * ui_height_scale / ui_main_scale));
	m_jumpStartSprite->setVisible(false);
	m_spriteBatchNode->addChild(m_jumpStartSprite);

	CCArray * animFrames = CCArray::createWithCapacity(13);
	char spriteFrameName[100] = {0};
	for(ODEInt32 i = 0; i < 13; i++)
	{
		sprintf(spriteFrameName, "kessen_jump_%d.png", i);
		animFrames->addObject(m_spriteFrameCache->spriteFrameByName (spriteFrameName));
	}
	CCAnimation* m_jumpAnimation = CCAnimation::createWithSpriteFrames(animFrames, 0.033f);
	m_jumpAnimation->setDelayPerUnit(0.033f);
	m_jumpAnimate = CCAnimate::create(m_jumpAnimation);
	m_jumpAnimate->retain ();
}

void StartEffects::createBigJumpAnimation ()
{
	m_shineStartSprite = CCSprite::createWithSpriteFrameName("kessen_jump_13.png");
	m_shineStartSprite->setPosition(ccp(230.0f, -120.0f * ui_height_scale / ui_main_scale));
	m_shineStartSprite->setVisible(false);
	m_spriteBatchNode->addChild(m_shineStartSprite);

	CCArray * animFrames2 = CCArray::createWithCapacity(10);
	char spriteFramesName[100] = {0};
	for(ODEInt32 i = 13; i < 23; i++)
	{
		sprintf(spriteFramesName, "kessen_jump_%d.png", i);
		animFrames2->addObject(m_spriteFrameCache->spriteFrameByName (spriteFramesName));
	}
	CCAnimation* m_shineAnimation = CCAnimation::createWithSpriteFrames(animFrames2, 0.033f);
	m_shineAnimation->setDelayPerUnit(0.033f);
	m_shineAnimate = CCAnimate::create(m_shineAnimation);
	m_shineAnimate->retain ();
}

void StartEffects::createRollingAnimation ()
{
	m_rollingStartSprite = CCSprite::createWithSpriteFrameName("kessen_jump_23.png");
	m_rollingStartSprite->setPosition(ccp(25.0f, 235 * ui_height_scale / ui_main_scale));
	m_rollingStartSprite->setVisible(false);
	m_spriteBatchNode->addChild(m_rollingStartSprite);

	CCArray * animFrames2 = CCArray::createWithCapacity(7);
	char spriteFramesName[100] = {0};
	for(ODEInt32 i = 23; i < 30; i++)
	{
		sprintf(spriteFramesName, "kessen_jump_%d.png", i);
		animFrames2->addObject(m_spriteFrameCache->spriteFrameByName (spriteFramesName));
	}
	CCAnimation* m_rollingAnimation = CCAnimation::createWithSpriteFrames(animFrames2, 0.033f);
	m_rollingAnimation->setDelayPerUnit(0.033f);
	m_rollingAnimate = CCAnimate::create(m_rollingAnimation);
	m_rollingAnimate->retain ();
}

void StartEffects::createSwingAnimation ()
{
	m_swingStartSprite = CCSprite::createWithSpriteFrameName("kessen_jump_30.png");
	m_swingStartSprite->setPosition(ccp(0.0f, 210.0f * ui_height_scale / ui_main_scale));
	m_swingStartSprite->setVisible(false);
	m_spriteBatchNode->addChild(m_swingStartSprite);

	CCArray * animFrames2 = CCArray::createWithCapacity(8);
	char spriteFramesName[100] = {0};
	for(ODEInt32 i = 30; i < 38; i++)
	{
		sprintf(spriteFramesName, "kessen_jump_%d.png", i);
		animFrames2->addObject(m_spriteFrameCache->spriteFrameByName (spriteFramesName));
	}
	CCAnimation* m_swingAnimation = CCAnimation::createWithSpriteFrames(animFrames2, 0.033f);
	m_swingAnimation->setDelayPerUnit(0.033f);
	m_swingAnimate = CCAnimate::create(m_swingAnimation);
	m_swingAnimate->retain ();
}

void StartEffects::createParticleAnimation ()
{
	int skinType = g_pSaveData->ReadParam("skin_type", 0U);
	if (skinType == 2)
	{
		m_particleBatchNode = CCSpriteBatchNode::create("image/particle2.png");
		m_particleFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
		m_particleFrameCache->addSpriteFramesWithFile("image/particle2.plist");
	}
	else
	{
		m_particleBatchNode = CCSpriteBatchNode::create("image/particle.png");
		m_particleFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
		m_particleFrameCache->addSpriteFramesWithFile("image/particle.plist");
	}

	m_particleStartSprite = CCSprite::createWithSpriteFrameName("particle_0.png");
	m_particleStartSprite->setPosition(ccp(0.0f, 200.0f * ui_height_scale / ui_main_scale));
	m_particleStartSprite->setVisible(false);
	m_particleBatchNode->addChild(m_particleStartSprite);
	addChild(m_particleBatchNode);

	CCArray* animFrames3 = CCArray::createWithCapacity(18);
	char spriteFrames[100] = {0};
	for(ODEInt32 i = 0; i < 18; i++)
	{
		if (i < 8)
			sprintf(spriteFrames, "particle_%d.png", i);
		else
			sprintf(spriteFrames, "floatparticle_%d.png", i - 8);
		animFrames3->addObject(m_particleFrameCache->spriteFrameByName (spriteFrames));
	}
	CCAnimation* m_particleAnimation = CCAnimation::createWithSpriteFrames(animFrames3, 0.033f);
	m_particleAnimation->setDelayPerUnit(0.033f);
	m_particleAnimate = CCAnimate::create(m_particleAnimation);
	m_particleAnimate->retain ();
}

void StartEffects::createLights ()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	char activeTexName[100] = {0};
	int skinType = g_pSaveData->ReadParam("skin_type", 0U);
	if (skinType == 2)
	{
		sprintf (activeTexName, "image/toplight_2.png");
	}
	else
	{
		sprintf (activeTexName, "image/toplight.png");
	}

	m_pkLightL = CCSprite::create(activeTexName);
	m_pkLightL->setAnchorPoint (ccp (1.0f, 1.0f));
	m_pkLightL->setPosition (ccp (0.0f, 0.0f + 360.0f * ui_height_scale / ui_main_scale));
	addChild(m_pkLightL, -1);
	m_pkLightL->setVisible(false);
	m_pkLightR = CCSprite::create(activeTexName);
	m_pkLightR->setFlipX(true);
	m_pkLightR->setAnchorPoint (ccp (0.0f, 1.0f));
	m_pkLightR->setPosition (ccp (0.0f, 0.0f + 360.0f * ui_height_scale / ui_main_scale));
	addChild(m_pkLightR, -1);
	m_pkLightR->setVisible(false);

	CCTextureCache::sharedTextureCache()->removeTextureForKey(activeTexName);
}

void StartEffects::RunAnimationEnd ()
{
	m_runStartSpirte->setVisible (false);
	m_brakeStartSprite->setVisible (true);
	CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(StartEffects::BrakeAnimationEnd));
	m_brakeStartSprite->runAction(CCSequence::create(CCSpawn::create (m_brakeAnimate, NULL), pkCall, NULL));
}

void StartEffects::BrakeAnimationEnd ()
{
	m_brakeStartSprite->setVisible (false);
	m_jumpStartSprite->setVisible(true);
	CCJumpTo* plJumpTo_1 = CCJumpTo::create(0.433f, ccp(230.0f, -120.0f * ui_height_scale / ui_main_scale), 10, 1);
	CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(StartEffects::JumpAnimationEnd));
	m_jumpStartSprite->runAction(CCSequence::create(CCSpawn::create (plJumpTo_1, m_jumpAnimate, NULL), pkCall, NULL));
}

void StartEffects::JumpAnimationEnd ()
{
	m_jumpStartSprite->setVisible (false);
	m_shineStartSprite->setVisible(true);
	CCJumpTo* plJumpTo_2 = CCJumpTo::create(0.333f, ccp(25.0f, 235 * ui_height_scale / ui_main_scale), 25, 1);
	CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(StartEffects::BigJumpAnimationEnd));
	m_shineStartSprite->runAction(CCSequence::create(CCSpawn::create (plJumpTo_2, m_shineAnimate, NULL), pkCall, NULL));
}

void StartEffects::BigJumpAnimationEnd ()
{
	m_shineStartSprite->setVisible (false);
	m_rollingStartSprite->setVisible (true);
	CCMoveTo* plJumpTo_2 = CCMoveTo::create(0.233f, ccp(0.0f, 210 * ui_height_scale / ui_main_scale));
	CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(StartEffects::RollingAnimationEnd));
	CCCallFunc* pkCallJumEnd = CCCallFunc::create(this, callfunc_selector(StartEffects::JumpEnd));
	m_rollingStartSprite->runAction(CCSequence::create(CCSpawn::create (CCSequence::create(plJumpTo_2, pkCallJumEnd, NULL), m_rollingAnimate, NULL), pkCall, NULL));
}

void StartEffects::JumpEnd ()
{
	int contentid = 0;
	int gameid = atoi (TT ("GameID"));
	std::string readfilename = "";
	//g_pkGuanDanGame->GetSkinTypeValue (gameid, contentid, readfilename);
	if (contentid != 2666001)
	{
		return ;
	}

	CCParticleSystemQuad* m_emitter4 = CCParticleSystemQuad::create("image/emitter/lobby_exploding1.plist");
	m_emitter4->setPosition(ccp(-300, -120.0f * ui_height_scale / ui_main_scale));
	addChild(m_emitter4, 1001);

	CCParticleSystemQuad* m_emitter2 = CCParticleSystemQuad::create("image/emitter/lobby_exploding2.plist");
	m_emitter2->setPosition(ccp(-75, 0 * ui_height_scale / ui_main_scale));
	addChild(m_emitter2, 1001);

	CCParticleSystemQuad* m_emitter3 = CCParticleSystemQuad::create("image/emitter/lobby_exploding3.plist");
	m_emitter3->setPosition(ccp(75, -85 * ui_height_scale / ui_main_scale));
	addChild(m_emitter3, 1001);

	CCParticleSystemQuad* m_emitter = CCParticleSystemQuad::create("image/emitter/lobby_exploding4.plist");
	m_emitter->setPosition(ccp(280.0f, -120.0f * ui_height_scale / ui_main_scale));
	addChild(m_emitter, 1001);
}

void StartEffects::RollingAnimationEnd ()
{
	m_pkLightL->setVisible(true);
	m_pkLightR->setVisible(true);
	m_particleStartSprite->setVisible (true);
	m_swingStartSprite->setVisible (true);
	m_rollingStartSprite->setVisible (false);

	for (int i = 0; i < 4; i ++)
	{
		line [i] = CCSprite::create("image/line.png");
		line [i]->setAnchorPoint (ccp (0.5f, 0.0f));
		line [i]->setPosition(ccp(0.0f + 5.0f, (200.0f - line [i]->getContentSize ().height / 2) * ui_height_scale / ui_main_scale));
		addChild(line [i]);
		CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(StartEffects::ParticleAnimationEnd));
		CCScaleTo * action1 = CCScaleTo::create(0.20f, 1.5f, 1.5f);
		CCFadeOut * action3 = CCFadeOut::create(0.20f);
		line [i]->runAction(CCSequence::create (action1, action3, pkCall, NULL));
	}

	CCTextureCache::sharedTextureCache()->removeTextureForKey("image/line.png");
	m_particleStartSprite->runAction(CCSequence::create(CCSpawn::create (m_particleAnimate, NULL), NULL));
	m_swingStartSprite->runAction (m_swingAnimate);
}


void StartEffects::ParticleAnimationEnd ()
{
	for (int i = 0; i < 4; i ++)
	{
		line [i]->setVisible (false);
	}
}

void StartEffects::Play()
{
	if (!m_runStartSpirte->numberOfRunningActions())
	{
		Reset(0.0f);
		CCFadeIn* pkFadeIn = CCFadeIn::create(1.0f);
		CCFadeOut* pkFadeOut = CCFadeOut::create(1.0f);

		CCMoveTo* plMoveTo = CCMoveTo::create(1.0f, ccp(200.0f, -120.0f * ui_height_scale / ui_main_scale));	
		m_runStartSpirte->runAction(plMoveTo);


		CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(StartEffects::RunAnimationEnd));
		m_runStartSpirte->runAction(CCSequence::create(CCSpawn::create (plMoveTo, m_runAnimate, NULL), pkCall, NULL));

		schedule(schedule_selector(StartEffects::ShowWord), 0.11f);
	}
}

void StartEffects::Reset( ODEFloat32 f32Delta )
{
	unscheduleAllSelectors();
	stopAllActions();
	m_runStartSpirte->setPosition(ccp(-190.0f, -120.0f * ui_height_scale / ui_main_scale));
	m_i32WordCount = -1;

	for (ODEInt32 i(0); i < 8; ++i)
	{
		pkWord[i]->setColor(ccc3(255, 255, 255));
		pkWord[i]->setVisible(false);
	}
}


void StartEffects::ShowWord( ODEFloat32 f32Delta )
{
	if(m_i32WordCount >= 0 && m_i32WordCount < 8 )
	{
		pkWord[m_i32WordCount]->setVisible(true);
	}
	else if (m_i32WordCount == 8 )
	{
		unschedule(schedule_selector(StartEffects::ShowWord));
	}
	m_i32WordCount++;
}

ODEUInt32 StartEffects::NumberOfRunningActions()
{
	return m_runStartSpirte->numberOfRunningActions();
}

GoldCardBuyEffects::GoldCardBuyEffects ()
{
	m_spriteBatchNode = CCSpriteBatchNode::create("image/texturePack/GoldCardBuy.png");
	m_spriteFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
	m_spriteFrameCache->addSpriteFramesWithFile("image/texturePack/GoldCardBuy.plist");

	m_effectStart = CCSprite::createWithSpriteFrameName("gold_card_start.png");
	m_effectStart2 = CCSprite::createWithSpriteFrameName("gold_card_start2.png");
	m_effectStart2->setScaleX (0.2f);

	addChild (m_effectStart2);
	addChild (m_effectStart);
	
	createAnimation ();
	createDisAnimation ();

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("image/texturePack/GoldCardBuy.plist");  
	CCTextureCache::sharedTextureCache()->removeTextureForKey("image/texturePack/GoldCardBuy.png");
}

GoldCardBuyEffects::~GoldCardBuyEffects ()
{
	CC_SAFE_RELEASE(m_shineAnimate);
	CC_SAFE_RELEASE(m_disAnimate);
}

void GoldCardBuyEffects::createAnimation ()
{
	m_shineSprite = CCSprite::createWithSpriteFrameName("gold_card_shine_0.png");
	m_shineSprite->setVisible(false);
	m_spriteBatchNode->addChild(m_shineSprite);
	addChild (m_spriteBatchNode);

	CCArray * animFrames = CCArray::createWithCapacity(14);
	char spriteFrameName[100] = {0};
	for(ODEInt32 i = 0; i <= 13; i++)
	{
		sprintf(spriteFrameName, "gold_card_shine_%d.png", i);
		animFrames->addObject(m_spriteFrameCache->spriteFrameByName (spriteFrameName));
	}
	CCAnimation* m_shineAnimation = CCAnimation::createWithSpriteFrames(animFrames, 0.125f);
	m_shineAnimation->setDelayPerUnit(0.125f);
	m_shineAnimate = CCAnimate::create(m_shineAnimation);
	m_shineAnimate->retain ();
}

void GoldCardBuyEffects::createDisAnimation ()
{
	m_disSprite = CCSprite::createWithSpriteFrameName("gold_card_dis_1.png");
	m_disSprite->setVisible(false);
	m_spriteBatchNode->addChild(m_disSprite);

	CCArray * animFrames = CCArray::createWithCapacity(6);
	char spriteFrameName[100] = {0};
	for(ODEInt32 i = 1; i <= 6; i++)
	{
		sprintf(spriteFrameName, "gold_card_dis_%d.png", i);
		animFrames->addObject(m_spriteFrameCache->spriteFrameByName (spriteFrameName));
	}
	CCAnimation* m_disAnimation = CCAnimation::createWithSpriteFrames(animFrames, 0.125f);
	m_disAnimation->setDelayPerUnit(0.125f);
	m_disAnimate = CCAnimate::create(m_disAnimation);
	m_disAnimate->retain ();
}

void GoldCardBuyEffects::Play ()
{
	if (!m_effectStart->numberOfRunningActions())
	{
		CCScaleTo* pkScale = CCScaleTo::create(0.125f, 0.2f, 1.0f);
		CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(GoldCardBuyEffects::ScalePath1End));
		m_effectStart->runAction (CCSequence::create(pkScale, pkCall, NULL));
	}
}

void GoldCardBuyEffects::ScalePath1End ()
{
	m_effectStart->setVisible (false);
	m_effectStart2->setVisible (true);
	CCScaleTo* pkScale = CCScaleTo::create(0.125f, 1.0f, 1.0f);
	CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(GoldCardBuyEffects::ScalePath2End));
	m_effectStart2->runAction (CCSequence::create(pkScale, pkCall, NULL));
}
	
void GoldCardBuyEffects::ScalePath2End ()
{
	m_shineSprite->setVisible (true);
	CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(GoldCardBuyEffects::ShineAnimationEnd));
	m_shineSprite->runAction(CCSequence::create(m_shineAnimate, pkCall, NULL));
}

void GoldCardBuyEffects::ShineAnimationEnd ()
{
	m_shineSprite->setVisible (false);
	CCFadeOut* tink = CCFadeOut::create(0.125f);
	CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(GoldCardBuyEffects::TinkAnimationEnd));
	m_effectStart2->runAction(CCSequence::create(tink, pkCall, NULL));
}

void GoldCardBuyEffects::TinkAnimationEnd ()
{
	m_effectStart2->setVisible (false);
	m_disSprite->setVisible (true);
	CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(GoldCardBuyEffects::DisAniamtionEnd));
	m_disSprite->runAction(CCSequence::create(m_disAnimate, pkCall, NULL));
}

void GoldCardBuyEffects::DisAniamtionEnd ()
{
	m_disSprite->setVisible (false);
	g_pLayerManager->PopAllLayers ();
	g_pkGuanDanGame->Toast (TT ("LobbyBuy_Items_GoldCard_Success"));
}

HeadImageBuyEffects::HeadImageBuyEffects()
{
	//setScale(ui_main_scale);

	m_spriteBatchNode = CCSpriteBatchNode::create("image/texturePack/bottom_btns_effect.png");
	m_spriteFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
	m_spriteFrameCache->addSpriteFramesWithFile("image/texturePack/bottom_btns_effect.plist");

	createAnimation ();

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("image/texturePack/bottom_btns_effect.plist");  
	CCTextureCache::sharedTextureCache()->removeTextureForKey("image/texturePack/bottom_btns_effect.png");
}

HeadImageBuyEffects::~HeadImageBuyEffects()
{
    CC_SAFE_RELEASE(BuyAnimate);
}

void HeadImageBuyEffects::createAnimation()
{
	pkAnima = CCSprite::createWithSpriteFrameName("buy_0.png");
	//pkAnima->setScale(ui_main_scale + 0.5*ui_main_scale);
	pkAnima->setVisible(true);
	m_spriteBatchNode->addChild(pkAnima);
	addChild (m_spriteBatchNode);

	CCArray * animFrames = CCArray::createWithCapacity(7);
	char spriteFrameName[100] = {0};
	for(ODEInt32 i = 0; i < 7; i++)
	{
		sprintf(spriteFrameName, "buy_%d.png", i);
		animFrames->addObject(m_spriteFrameCache->spriteFrameByName (spriteFrameName));
	}
	CCAnimation* buyAnima = CCAnimation::createWithSpriteFrames(animFrames, 0.125f);
	buyAnima->setDelayPerUnit(0.1f);
	BuyAnimate = CCAnimate::create(buyAnima);
	BuyAnimate->retain ();
}

void HeadImageBuyEffects::Play()
{
	if (!pkAnima->numberOfRunningActions())
	{
		CCCallFunc* pkCall = CCCallFunc::create(this, callfunc_selector(HeadImageBuyEffects::EffectEnd));
		pkAnima->runAction (CCSequence::create(BuyAnimate, pkCall, NULL));
	}
}

void HeadImageBuyEffects::EffectEnd()
{
	pkAnima->setVisible(false);
	//g_pLayerManager->PopLayer ();
}

ShunZiEffects::ShunZiEffects()
{
	setScale(ui_main_scale);

	CCSpriteBatchNode* pkBatchNode = CCSpriteBatchNode::create(g_pkGuanDanGame->GetImagePath("game_can_remove", false) + ".pvr.ccz");
	addChild(pkBatchNode, 2);

	pkCloudL = CCSprite::createWithSpriteFrameName("shunzi_yun_l.png");
	pkCloudL->setPosition(ccp(-220.0f, -20.0f));
	pkBatchNode->addChild(pkCloudL, 2);

	pkCloudR =  CCSprite::createWithSpriteFrameName("shunzi_yun_r.png");
	pkCloudR->setPosition(ccp(220.0f, 20.0f));
	pkBatchNode->addChild(pkCloudR, 2);

	pkFont =  CCSprite::createWithSpriteFrameName("shunzi_zi.png");
	pkFont->setPosition(ccp(0.0f, 30.0f));
	pkBatchNode->addChild(pkFont, 3);

	CCSprite* pkRainbowSprite = CCSprite::createWithSpriteFrameName("shunzi_caihong.png");
	pkRainbowProgress = CCProgressTimer::create(pkRainbowSprite);
	pkRainbowProgress->setPosition(ccp(0.0f, 75.0f));
	pkRainbowProgress->setType(kCCProgressTimerTypeBar);
	pkRainbowProgress->setMidpoint(CCPointZero);
	pkRainbowProgress->setBarChangeRate(ccp(1.0f,0));
	pkRainbowProgress->setPercentage(0);
	addChild(pkRainbowProgress,1);

	Reset(0.0f);
}

ShunZiEffects::~ShunZiEffects()
{

}

void ShunZiEffects::Play()
{
	if (!g_pSaveData->ReadParam("special_effect", ODEUInt32(1)))
	{
		return;
	}
	Reset(0.0f);
	CCProgressTo* pkProgressTo = CCProgressTo::create(0.2f, 100.0f);
	pkRainbowProgress->runAction(pkProgressTo);

	CCMoveTo* pkLMoveIn = CCMoveTo::create(0.2f, ccp(-170.0f, -20.0f));
	CCFadeIn* pkFadeIn = CCFadeIn::create(0.2f);
	pkCloudL->runAction(CCSpawn::create(pkLMoveIn, pkFadeIn, NULL));
	CCMoveTo* pkRMoveIn = CCMoveTo::create(0.2f, ccp(170.0f, 20.0f));
	pkCloudR->runAction(CCSpawn::create(pkRMoveIn, pkFadeIn->copy()->autorelease(), NULL));

	CCMoveTo* pkFontMoveIn = CCMoveTo::create(0.3f, ccp(0.0f, 0.0f));
	pkFont->runAction(CCSpawn::create(pkFontMoveIn, pkFadeIn->copy()->autorelease(), NULL));

	CCSprite* pkStar = CCSprite::createWithSpriteFrameName("shunzi_star.png");
	CCParticleSnow* m_emitter = CCParticleSnow::create();
	pkRainbowProgress->addChild(m_emitter, 10);
	m_emitter->setPosition(ccp(200.0f, 210.0f));
	m_emitter->setLife(0.3f);
	m_emitter->setLifeVar(1.0f);
	m_emitter->setStartSize(30.0f);
	m_emitter->setStartSizeVar(10.0f);
	m_emitter->setGravity(ccp(0,-10));
	m_emitter->setAutoRemoveOnFinish(true);
	m_emitter->setSpeed(120);
	m_emitter->setSpeedVar(30);
	m_emitter->setDuration(0.8f);
	m_emitter->setStartSpin(0.0f);
	m_emitter->setStartSpinVar(90.0f);
	m_emitter->setEndSpin(360.0f);
	m_emitter->setPosVar(ccp(250.0f, 0.0f));
	m_emitter->setTotalParticles(80.0f);

	ccColor4F startColor = m_emitter->getStartColor();
	startColor.r = 0.9f;
	startColor.g = 0.9f;
	startColor.b = 0.9f;
	m_emitter->setStartColor(startColor);

	ccColor4F startColorVar = m_emitter->getStartColorVar();
	startColorVar.b = 0.1f;
	m_emitter->setStartColorVar(startColorVar);

	m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());
	m_emitter->setTextureWithRect(pkStar->getTexture(), pkStar->getTextureRect());

	scheduleOnce(schedule_selector(ShunZiEffects::Reset), 0.8f);
}

void ShunZiEffects::Reset( ODEFloat32 f32Delta )
{
	unscheduleAllSelectors();
	stopAllActions();
	pkRainbowProgress->setPercentage(0.0f);
	pkCloudL->setPosition(ccp(-220.0f, -20.0f));
	pkCloudL->setOpacity(0);
	pkCloudR->setPosition(ccp(220.0f, 20.0f));
	pkCloudR->setOpacity(0);
	pkFont->setPosition(ccp(0.0f, 30.0f));
	pkFont->setOpacity(0);
}

void ShunZiEffects::exitWithClean()
{
	unscheduleAllSelectors();
	pkCloudL->stopAllActions();
	pkCloudR->stopAllActions();
	pkFont->stopAllActions();
	stopAllActions();
}

BobEffects::BobEffects(bool isDouble)
{
	setScale(ui_main_scale);

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache(); 
	char strPlist[64] = {0}; 
	char strPng[64] = {0}; 
	sprintf(strPlist,"%s", landlord_effects3_plist); 
	sprintf(strPng,"%s", landlord_effects3); 
	cache->addSpriteFramesWithFile(strPlist, strPng);

	CCArray *animFrames =CCArray::create(); 
	ODEChar8 acBuffer[64];
	for (ODEInt32 i(1); i <= 16; ++i)
	{
		ODESprintf(acBuffer, 64, "1%04d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(acBuffer);
		animFrames->addObject(frame); 
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 1.0f / 16.0f);
	m_pkBob = CCSprite::createWithSpriteFrameName("10001.png");
	m_pkBob->setScale(1.8f);
	m_pkBob->setPositionY(ODUILayer::Height() / ui_main_scale);
	addChild(m_pkBob,9);
	pkAni = CCAnimate::create(animation);
	pkAni->retain();

	if (isDouble)
	{
		m_pkDoubleText = CCSprite::createWithSpriteFrameName("double_eff.png");
	}else
	{
		m_pkDoubleText = CCSprite::create(LANDLORD_IMAGE_PATH_HD"/rogue/fourfold.png");
	}

	m_pkDoubleText->setPositionY(180.0f * ui_height_scale);
	addChild(m_pkDoubleText, 8);

	SetVisible(false);
}

BobEffects::~BobEffects()
{
	CC_SAFE_RELEASE(pkAni);
}

void BobEffects::Play()
{
	if (!g_pSaveData->ReadParam("special_effect", ODEUInt32(1)))
	{
		if (g_pSaveData->ReadParam("shark", ODEUInt32(1)))
		{
			//ODEShakeAction* pkShake = ODEShakeAction::create(0.8f, 3.5f);

			//if (g_pkTbnnGamePlayerData->m_bIsSingleGameMode)
			//{
			//	if (g_pLayerManager->GetLayer("single_game")->IsActive())
			//	{
			//		SingleGame* pkTemp = (SingleGame*)g_pLayerManager->GetLayer("single_game");
			//		pkTemp->runAction(pkShake);
			//	}
			//	ShakeBody();
			//} 
			//else
			//{
			//	if (g_pLayerManager->GetLayer("game")->IsActive())
			//	{
			//		Game* pkTemp = (Game*)g_pLayerManager->GetLayer("game");
			//		pkTemp->runAction(pkShake);
			//	}
			//	ShakeBody();
			//}
		}
		return;
	}
	if (!m_pkBob->numberOfRunningActions())
	{
		SetVisible(true);
		m_pkBob->setVisible(true);
		m_pkDoubleText->setVisible(false);
		CCMoveTo* pkMoveDown = CCMoveTo::create(0.5f, ccp(0.0f, 0.0f));
		CCEaseBackOut* pkEase = CCEaseBackOut::create(pkMoveDown);
		m_pkBob->runAction(CCSpawn::createWithTwoActions(pkEase, pkAni));
		unscheduleAllSelectors();
		scheduleOnce(schedule_selector(BobEffects::Reset), 3.15f);
		scheduleOnce(schedule_selector(BobEffects::Bomb), 0.4f);
	}
}

void BobEffects::Reset( ODEFloat32 f32Delta )
{
	SetVisible(false);
	m_pkBob->setPositionY(ODUILayer::Height() / ui_main_scale);
}

void BobEffects::Bomb( ODEFloat32 f32Delta )
{
	if (g_pSaveData->ReadParam("shark", ODEUInt32(1)))
	{
		//ODEShakeAction* pkShake = ODEShakeAction::create(0.8f, 3.5f);

		//if (g_pkTbnnGamePlayerData->m_bIsSingleGameMode)
		//{
		//	if (g_pLayerManager->GetLayer("single_game")->IsActive())
		//	{
		//		SingleGame* pkTemp = (SingleGame*)g_pLayerManager->GetLayer("single_game");
		//		pkTemp->runAction(pkShake);
		//	}
		//} 
		//else
		//{
		//	if (g_pLayerManager->GetLayer("game")->IsActive())
		//	{
		//		Game* pkTemp = (Game*)g_pLayerManager->GetLayer("game");
		//		pkTemp->runAction(pkShake);
		//	}
		//}
	}
	scheduleOnce(schedule_selector(BobEffects::ShowText), 1.0f);
}

void BobEffects::ShowText( ODEFloat32 f32Delta )
{
	if (g_pSaveData->ReadParam("special_effect", ODEUInt32(1)))
	{
		m_pkBob->setVisible(false);
		m_pkDoubleText->setVisible(true);
		m_pkDoubleText->setOpacity(255);
		m_pkDoubleText->runAction(CCRepeat::create(CCSequence::create(CCScaleTo::create(0.20f, 2.2f, 2.2f), CCScaleTo::create(0.20f, 1.2f, 1.2f), CCDelayTime::create(0.3f), CCFadeOut::create(0.3f),  NULL), 1));
		//m_pkDoubleText->runAction(CCRepeat::create(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.3f, 2.0f, 2.0f), CCTintTo::create(0.3f, 128, 128, 128), NULL), CCSpawn::create(CCScaleTo::create(0.3f, 1.5f, 1.5f), CCTintTo::create(0.3f, 255, 255, 255), NULL), NULL), 1));
	}
}

void BobEffects::exitWithClean()
{
	m_pkBob->stopAllActions();
	unscheduleAllSelectors();
}