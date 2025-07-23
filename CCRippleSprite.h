//////////////////////////////////////////////////////////////////////////
//
//
//	ODAO Engine Header File.
//  Copyright (C), ODAO
//-----------------------------------------------------------------------
//  File Name:  CCRippleSprite.h
//  Version:    v0.0.1
//  Created:    17/10/2013 by neo
//  Compilers:  Visual Studio.Net
//  Description:
//-----------------------------------------------------------------------
//  History:
//  http://www.7pmi.com
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "cocos2d.h"
#include "ODEEngine.h"
#include <vector>

using namespace std;

#define RIPPLE_DEFAULT_QUAD_COUNT_X             60
#define RIPPLE_DEFAULT_QUAD_COUNT_Y             40

#define RIPPLE_BASE_GAIN                        0.1f

#define RIPPLE_DEFAULT_RADIUS                   100
#define RIPPLE_DEFAULT_RIPPLE_CYCLE             0.25f
#define RIPPLE_DEFAULT_LIFESPAN                 1.4f

#define RIPPLE_CHILD_MODIFIER                   2.0f


typedef enum
{
    RIPPLE_TYPE_RUBBER,
    RIPPLE_TYPE_GEL,   
    RIPPLE_TYPE_WATER,
} RIPPLE_TYPE;

typedef enum
{
    RIPPLE_CHILD_LEFT,
    RIPPLE_CHILD_TOP,
    RIPPLE_CHILD_RIGHT,
    RIPPLE_CHILD_BOTTOM,
    RIPPLE_CHILD_COUNT
} RIPPLE_CHILD;

USING_NS_CC;

typedef struct _RippleData
{
    bool                    bParent;
    bool                    abChildCreated[4];
    RIPPLE_TYPE             kRippleType;
    CCPoint                 kCenter;
    CCPoint                 kCenterCoordinate;
    ODEFloat32              f32Radius;
    ODEFloat32              f32Strength;
    ODEFloat32              f32Runtime;
    ODEFloat32              f32CurrentRadius;
    ODEFloat32              f32RippleCycle;
    ODEFloat32              f32Lifespan;
} RippleData;

class CCRippleSprite : public CCSprite, public CCTargetedTouchDelegate
{
public:
    static CCRippleSprite* create(const ODEChar8* pcFilename);
    static CCRippleSprite* create(CCRenderTexture* pkRtt, ODEFloat32 f32Scale);
    
    CCRippleSprite();
    virtual ~CCRippleSprite();
    bool initWithFile(const ODEChar8* pcFilename);
    bool initWithRendertexture(CCRenderTexture* pkRtt, ODEFloat32 f32Scale);
    
    void Tesselate();
    void AddRipple(CCPoint kPos, RIPPLE_TYPE eType, ODEFloat32 f32Strength);
    void AddRippleChild(RippleData* pkParent, RIPPLE_CHILD eType);
    void update(ODEFloat32 dt);
    CCTexture2D* SpriteTexture();
    
    virtual void draw();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    bool IsPointInsideSprite(CCPoint kPos);
    bool IsTouchInsideSprite(CCTouch* pkTouch);
       
    CCTexture2D*            m_pkTexture;
    ODEInt32                m_i32QuadCountX;
    ODEInt32                m_i32QuadCountY;
    ODEInt32                m_i32VerticesPrStrip;
    ODEInt32                m_i32BufferSize;
    CCPoint*                m_pkVertice;
    CCPoint*                m_pkTextureCoordinate;
    CCPoint*                m_pkRippleCoordinate;
    bool*                   m_pbEdgeVertice;
    vector<RippleData*>     m_kRippleList;
    
    
    CCPoint kScreenSize;
    ODEFloat32 m_f32ScaleRTT;
    ODEFloat32 m_f32RunTime;
};

