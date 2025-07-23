//////////////////////////////////////////////////////////////////////////
//
//
//	ODAO Engine Header File.
//  Copyright (C), ODAO
//-----------------------------------------------------------------------
//  File Name:  CCShake.h
//  Version:    v0.0.1
//  Created:    17/10/2013 by neo
//  Compilers:  Visual Studio.Net
//  Description:
//-----------------------------------------------------------------------
//  History:
//  http://www.7pmi.com
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "ODEEngine.h"
#include "cocos2d.h"
USING_NS_CC;

class ODEShakeAction : public cocos2d::CCActionInterval
{
public:
	ODEShakeAction();

	static ODEShakeAction *create(ODEFloat32 f32Duration, ODEFloat32 f32Strength);

	static ODEShakeAction *createWithStrength(ODEFloat32 f32Duration, ODEFloat32 f32Strength_x, ODEFloat32 f32Strength_y);

	bool initWithDuration(ODEFloat32 f32Duration, ODEFloat32 f32Strength_x, ODEFloat32 f32Strength_y);

protected:

	void startWithTarget(cocos2d::CCNode *pTarget);
	void update(ODEFloat32 time);
	void stop(void);

	CCPoint m_kStartPosition;

	ODEFloat32 m_f32Strength_x, m_f32Strength_y;
};
