#include "FanHelper.h"

FanHelper::FanHelper (ODEFloat32 x, ODEFloat32 y, ODEFloat32 radius)
{
	m_ControlPointSize = 0;
	memset (m_pointArray, 0, sizeof (m_pointArray));
	SetCenterX (x);
	SetCenterY (y);
	SetFanRadius (radius);
	SetFanCenter (ccp (x, y));
	AddControlPoint (ccp (x, y));
}

FanHelper::~FanHelper ()
{
}

cocos2d::CCPoint FanHelper::GetFanCenter () const
{
	return m_FanCenter;
}

void FanHelper::SetFanCenter (cocos2d::CCPoint point)
{
	m_FanCenter = ccp (point.x, point.y);
}

ODEFloat32 FanHelper::GetCenterX () const
{
	return m_CenterX;
}

void FanHelper::SetCenterX (ODEFloat32 x)
{
	m_CenterX = x;
}
	
ODEFloat32 FanHelper::GetCenterY () const
{
	return m_CenterY;
}

void FanHelper::SetCenterY (ODEFloat32 y)
{
	m_CenterY = y;
}

ODEFloat32 FanHelper::GetFanRadius () const
{
	return m_FanRadius;
}

void FanHelper::SetFanRadius (ODEFloat32 radius)
{
	m_FanRadius = radius;
}

ODEFloat32 FanHelper::GetFanAngle () const
{
	return m_FanAngle;
}

void FanHelper::UpdateAngle (ODEFloat32 angle)
{
	SetFanAngle (angle);
	m_pointArray[m_ControlPointSize++] = GetCirclePoint (angle);
}

void FanHelper::AddControlPoint (cocos2d::CCPoint  point)
{
	m_pointArray[m_ControlPointSize++] = point;
}

cocos2d::CCPoint * FanHelper::GetControlPointArray ()
{
	return m_pointArray;
}

ODEInt32 FanHelper::GetControlPointSizes ()
{
	return  m_ControlPointSize;
}

void FanHelper::SetFanAngle (ODEFloat32 angle)
{
	m_FanAngle = angle;
}

cocos2d::CCPoint FanHelper::GetCirclePoint (ODEFloat32 angle)
{
	return ccp (sin(angle / 180 * PI) * m_FanRadius, cos(angle / 180 * PI) * m_FanRadius);
}