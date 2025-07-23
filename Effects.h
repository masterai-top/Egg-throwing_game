#pragma once

#include "ODEEngine.h"
#include "cocos2d.h"
#include "GameCommon.h"

USING_NS_CC;


class ShunZiEffects : public ODUIWidget
{
public:
	typedef ODEMemberDelegate<ShunZiEffects, ODUIWidget&, ODEUInt32> UIDelegate;

	ShunZiEffects();

	virtual ~ShunZiEffects();

	void Play();

	void Reset(ODEFloat32 f32Delta);

	void exitWithClean();

private:
	CCProgressTimer* pkRainbowProgress;

	CCSprite* pkCloudL;
	CCSprite* pkCloudR;
	CCSprite* pkFont;
};

class BobEffects : public ODUIWidget
{
public:
	typedef ODEMemberDelegate<BobEffects, ODUIWidget&, ODEUInt32> UIDelegate;

	BobEffects(bool isDouble);

	virtual ~BobEffects();

	void Play();

	void Reset(ODEFloat32 f32Delta);

	void Bomb(ODEFloat32 f32Delta);

	void ShowText(ODEFloat32 f32Delta);

	void exitWithClean();

private:
	CCSprite* m_pkBob;
	CCAnimate* pkAni;
	CCSprite* m_pkDoubleText;
};

class StartEffects : public ODUIWidget
{
public:
	typedef ODEMemberDelegate<StartEffects, ODUIWidget&, ODEUInt32> UIDelegate;

	StartEffects();

	virtual ~StartEffects();

	void Play();

	void Reset(ODEFloat32 f32Delta);

	void ShowWord(ODEFloat32 f32Delta);

	void ClearKessenEffect();

	ODEUInt32 NumberOfRunningActions();

	void createAnimation ();

	void createWords ();

	void createRunAnimation ();

	void createBrakeAnimation ();

	void createJumpAnimation ();

	void createBigJumpAnimation ();

	void createRollingAnimation ();

	void createSwingAnimation ();

	void createParticleAnimation ();

	void createLights ();

	void RunAnimationEnd ();

	void BrakeAnimationEnd ();

	void JumpAnimationEnd ();

	void BigJumpAnimationEnd ();

	void RollingAnimationEnd ();

	void ParticleAnimationEnd ();

	void JumpEnd ();

private:

	CCSpriteBatchNode * m_spriteBatchNode;
	CCSpriteFrameCache * m_spriteFrameCache;

	CCSpriteBatchNode * m_particleBatchNode;
	CCSpriteFrameCache * m_particleFrameCache;

	ccColor3B  pkWordColor;
	CCSprite * pkWord[8];

	CCSprite * m_runStartSpirte;
	CCAnimation * m_runAnimation;
	CCAnimate * m_runAnimate;

	CCSprite * m_brakeStartSprite;
	CCAnimate * m_brakeAnimate;
	
	CCSprite * m_jumpStartSprite;
	CCAnimate * m_jumpAnimate;

	CCSprite * m_shineStartSprite;
	CCAnimate * m_shineAnimate;

	CCSprite * m_rollingStartSprite;
	CCAnimate * m_rollingAnimate;

	CCSprite * m_swingStartSprite;
	CCAnimate * m_swingAnimate;

	CCSprite * m_particleStartSprite;
	CCAnimate * m_particleAnimate;

	CCSprite* m_pkLightL;
	CCSprite* m_pkLightR;

	CCSprite*  line [4];

	ODEInt32 m_i32WordCount;
};


class GoldCardBuyEffects : public ODUIWidget
{
public:
	typedef ODEMemberDelegate<GoldCardBuyEffects, ODUIWidget&, ODEUInt32> UIDelegate;

	GoldCardBuyEffects();

	virtual ~GoldCardBuyEffects();

	void Play();

	void createAnimation ();

	void createDisAnimation ();

	void ScalePath1End ();
	
	void ScalePath2End ();

	void ShineAnimationEnd ();

	void TinkAnimationEnd ();

	void DisAniamtionEnd ();

private:

	CCSpriteBatchNode * m_spriteBatchNode;
	CCSpriteFrameCache * m_spriteFrameCache;

	CCSprite * m_effectStart;
	CCSprite * m_effectStart2;
	CCLayerColor* effectBackground;

	CCSprite * m_shineSprite;
	CCAnimate * m_shineAnimate;

	CCSprite * m_disSprite;
	CCAnimate * m_disAnimate;
};


class HeadImageBuyEffects : public ODUIWidget
{
public:
	typedef ODEMemberDelegate<HeadImageBuyEffects, ODUIWidget&, ODEUInt32> UIDelegate;

	HeadImageBuyEffects();

	virtual ~HeadImageBuyEffects();

	void Play();

	void createAnimation();

	void EffectEnd();


private:

	CCSpriteBatchNode * m_spriteBatchNode;
	CCSpriteFrameCache * m_spriteFrameCache;

	CCSprite* pkAnima;
	CCAnimate* BuyAnimate;
};
