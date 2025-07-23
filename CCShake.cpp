//////////////////////////////////////////////////////////////////////////
//
//
//	ODAO Engine Source File.
//  Copyright (C), ODAO
//-----------------------------------------------------------------------
//  File Name:  CCShake.cpp
//  ODErsion:    v0.0.1
//  Created:    17/10/2013 by neo
//  Compilers:  Visual Studio.Net
//  Description:
//-----------------------------------------------------------------------
//  History:
//  http://www.7pmi.com
//////////////////////////////////////////////////////////////////////////
#include "CCShake.h"

ODEShakeAction::ODEShakeAction() : m_f32Strength_x(0), m_f32Strength_y(0)
{
}

ODEShakeAction *ODEShakeAction::create( ODEFloat32 f32Duration, ODEFloat32 f32Strength )
{
	return createWithStrength(f32Duration, f32Strength, f32Strength);
}

ODEShakeAction *ODEShakeAction::createWithStrength(ODEFloat32 f32Duration, ODEFloat32 f32Strength_x, ODEFloat32 f32Strength_y)
{
	ODEShakeAction *pRet = new ODEShakeAction();

	if (pRet && pRet->initWithDuration(f32Duration, f32Strength_x, f32Strength_y))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}


	return pRet;
}

bool ODEShakeAction::initWithDuration(ODEFloat32 f32Duration, ODEFloat32 f32Strength_x, ODEFloat32 f32Strength_y)
{
	if (CCActionInterval::initWithDuration(f32Duration))
	{
		m_f32Strength_x = f32Strength_x;
		m_f32Strength_y = f32Strength_y;

		return true;
	}

	return false;
}

static ODEFloat32 fgRangeRand( ODEFloat32 min, ODEFloat32 max )
{
	ODEFloat32 rnd = ((ODEFloat32)rand() / (ODEFloat32)RAND_MAX);
	return rnd * (max - min) + min;
}

void ODEShakeAction::update(ODEFloat32 dt)
{
	ODEFloat32 randx = fgRangeRand( -m_f32Strength_x, m_f32Strength_x ) * dt;
	ODEFloat32 randy = fgRangeRand( -m_f32Strength_y, m_f32Strength_y ) * dt;

	m_pTarget->setPosition( ccpAdd(m_kStartPosition, ccp( randx, randy)));
}

void ODEShakeAction::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget( pTarget );

	m_kStartPosition=pTarget->getPosition();
}

void ODEShakeAction::stop(void)
{
	this->getTarget()->setPosition( m_kStartPosition);

	CCActionInterval::stop();
}