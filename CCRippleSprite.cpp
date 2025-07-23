//////////////////////////////////////////////////////////////////////////
//
//
//	ODAO Engine Source File.
//  Copyright (C), ODAO
//-----------------------------------------------------------------------
//  File Name:  CCRippleSprite.cpp
//  ODErsion:    v0.0.1
//  Created:    17/10/2013 by neo
//  Compilers:  Visual Studio.Net
//  Description:
//-----------------------------------------------------------------------
//  History:
//  http://www.7pmi.com
//////////////////////////////////////////////////////////////////////////
#include "CCRippleSprite.h"
#include <string>

using namespace std;

CCRippleSprite* CCRippleSprite::create( const ODEChar8* pcFilename )
{
    CCRippleSprite *pkSprite = new CCRippleSprite();
    if (pkSprite && pkSprite->initWithFile(pcFilename)) {
        pkSprite->autorelease();
        return pkSprite;
    }
    else
    {
        delete pkSprite;
        pkSprite = NULL;
        return NULL;
    }
}


CCRippleSprite::CCRippleSprite()
:m_pkTexture(NULL),
m_i32QuadCountX(0),
m_i32QuadCountY(0),
m_i32VerticesPrStrip(0),
m_i32BufferSize(0),
m_pkVertice(NULL),
m_pkTextureCoordinate(NULL),
m_pkRippleCoordinate(NULL),
m_pbEdgeVertice(NULL),
m_f32ScaleRTT(0),
kScreenSize(CCPointZero),
m_f32RunTime(0)
{
    
}
CCRippleSprite::~CCRippleSprite()
{
    RippleData* runningRipple;
    
    free(m_pkVertice);
    free(m_pkTextureCoordinate);
    free(m_pkRippleCoordinate);
    free(m_pbEdgeVertice);
    
    for (int count = 0; count < m_kRippleList.size(); count++)
	{
        runningRipple = m_kRippleList.at(count);
        free(runningRipple);
    }
    
    m_pkTexture->release();
    
    
}
bool CCRippleSprite::initWithFile( const ODEChar8* pcFilename )
{
    bool bRet = true;
    
    do {
        
        if (!CCSprite::init()) {
            bRet = false;
            break;
        }
        
        m_f32ScaleRTT = 1.0f;
        
        m_pkTexture = CCTextureCache::sharedTextureCache()->addImage(pcFilename);
        m_pkTexture->retain();
        
        m_pkVertice = NULL;
        m_pkTextureCoordinate = NULL;

        m_i32QuadCountX = RIPPLE_DEFAULT_QUAD_COUNT_X;
        m_i32QuadCountY = RIPPLE_DEFAULT_QUAD_COUNT_Y;
        this->Tesselate();
        
       kScreenSize = ccp(m_pkTexture->getContentSize().width / m_f32ScaleRTT,
                        m_pkTexture->getContentSize().height / m_f32ScaleRTT);
        
        this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));
       
        
    } while (0);
    
    
    return bRet;


}


void CCRippleSprite::Tesselate()
{
    int vertexPos = 0;
    CCPoint normalized;
   
    free( m_pkVertice );
    free( m_pkTextureCoordinate );
    free( m_pkRippleCoordinate );
    free( m_pbEdgeVertice );

    m_i32VerticesPrStrip = 2 * ( m_i32QuadCountX + 1 );
    
    m_i32BufferSize = m_i32VerticesPrStrip * m_i32QuadCountY;
    
    m_pkVertice = (CCPoint*)malloc(m_i32BufferSize * sizeof(CCPoint));
    m_pkTextureCoordinate = (CCPoint*)malloc(m_i32BufferSize * sizeof(CCPoint));
    m_pkRippleCoordinate = (CCPoint*)malloc(m_i32BufferSize * sizeof(CCPoint));
    m_pbEdgeVertice = (bool*)malloc( m_i32BufferSize * sizeof( bool ) );

    vertexPos = 0;

    for (ODEInt32 y(0); y < m_i32QuadCountY; y ++)
	{
        for (ODEInt32 x(0); x < ( m_i32QuadCountX + 1 ); x ++)
		{
            for (ODEInt32 yy(0); yy < 2; yy ++)
			{
                normalized.x = ( float )x / ( float )m_i32QuadCountX;
                normalized.y = ( float )( y + yy ) / ( float )m_i32QuadCountY;

                m_pkVertice[vertexPos] = ccp(normalized.x * m_pkTexture->getContentSize().width / m_f32ScaleRTT, normalized.y *
                                           m_pkTexture->getContentSize().height / m_f32ScaleRTT );

                m_pkTextureCoordinate[vertexPos] = ccp(normalized.x * m_pkTexture->getMaxS(), m_pkTexture->getMaxT() - normalized.y *
                                                     m_pkTexture->getMaxT());
                m_pbEdgeVertice[ vertexPos ] = (
                                              ( x == 0 ) ||
                                              ( x == m_i32QuadCountX ) ||
                                              ( ( y == 0 ) && ( yy == 0 ) ) ||
                                              ( ( y == ( m_i32QuadCountY - 1 ) ) && ( yy > 0 ) ) );
                vertexPos ++;
                
            }
        }
    }
 
}

void CCRippleSprite::AddRipple( CCPoint kPos, RIPPLE_TYPE eType, ODEFloat32 f32Strength )
{
    RippleData* pkNewRipple;

    pkNewRipple = (RippleData*)malloc( sizeof( RippleData ) );

    pkNewRipple->bParent = true;
    for ( int count = 0; count < 4; count ++ ) pkNewRipple->abChildCreated[ count ] = false;
    pkNewRipple->kRippleType = eType;
    pkNewRipple->kCenter = kPos;
    pkNewRipple->kCenterCoordinate = ccp(kPos.x / m_pkTexture->getContentSize().width * m_pkTexture->getMaxS() / m_f32ScaleRTT ,
                                      m_pkTexture->getMaxT() - (kPos.y / m_pkTexture->getContentSize().height * m_pkTexture->getMaxT()/m_f32ScaleRTT));
    pkNewRipple->f32Radius = RIPPLE_DEFAULT_RADIUS;
    pkNewRipple->f32Strength = f32Strength;
    pkNewRipple->f32Runtime = 0;
    pkNewRipple->f32CurrentRadius = 0;
    pkNewRipple->f32RippleCycle = RIPPLE_DEFAULT_RIPPLE_CYCLE;
    pkNewRipple->f32Lifespan = RIPPLE_DEFAULT_LIFESPAN;

    m_kRippleList.push_back(pkNewRipple);
}

void CCRippleSprite::AddRippleChild( RippleData* pkParent, RIPPLE_CHILD eType )
{
    RippleData* pkNewRipple;
    CCPoint kPos;

    pkNewRipple = (RippleData*)malloc( sizeof(RippleData));
    memcpy( pkNewRipple, pkParent, sizeof(RippleData ));

    pkNewRipple->bParent = false;
    
    switch (eType)
	{
        case RIPPLE_CHILD_LEFT:
            kPos = ccp( -pkParent->kCenter.x, pkParent->kCenter.y );
            break;
        case RIPPLE_CHILD_TOP:
            kPos = ccp( pkParent->kCenter.x, kScreenSize.y + ( kScreenSize.y - pkParent->kCenter.y ) );
            break;
        case RIPPLE_CHILD_RIGHT:
            kPos = ccp( kScreenSize.x + ( kScreenSize.x - pkParent->kCenter.x ), pkParent->kCenter.y );
            break;
        case RIPPLE_CHILD_BOTTOM:
        default:
            kPos = ccp( pkParent->kCenter.x, -pkParent->kCenter.y );
            break;
    }
    
    pkNewRipple->kCenter = kPos;
    pkNewRipple->kCenterCoordinate = ccp(kPos.x / m_pkTexture->getContentSize().width * m_pkTexture->getMaxS(),
                                      m_pkTexture->getMaxT() - (kPos.y / m_pkTexture->getContentSize().height * m_pkTexture->getMaxT()));
    pkNewRipple->f32Strength *= RIPPLE_CHILD_MODIFIER;
    
    pkParent->abChildCreated[eType] = true;

    m_kRippleList.push_back(pkNewRipple);
}

void CCRippleSprite::update( ODEFloat32 dt )
{
    RippleData* pkRipple;
    CCPoint kPos;
    ODEFloat32 f32Distance, f32Correction;

    if ( m_kRippleList.size() == 0 ) return;

    memcpy( m_pkRippleCoordinate, m_pkTextureCoordinate, m_i32BufferSize * sizeof(CCPoint));

    for (ODEInt32 count =(m_kRippleList.size() - 1); count >= 0; count --)
	{
        pkRipple = m_kRippleList[count];
        for (ODEInt32 count(0); count < m_i32BufferSize; count ++)
		{
            if (m_pbEdgeVertice[ count ] == false)
			{
                f32Distance = ccpDistance(pkRipple->kCenter, m_pkVertice[count]);
                if (f32Distance <= pkRipple->f32CurrentRadius)
				{
                    kPos = m_pkRippleCoordinate[ count ];
                    switch (pkRipple->kRippleType)
					{
                        case RIPPLE_TYPE_RUBBER:
                            f32Correction = sinf( 2 * M_PI * pkRipple->f32Runtime / pkRipple->f32RippleCycle );
                            break;
                            
                        case RIPPLE_TYPE_GEL:
                            f32Correction = sinf( 2 * M_PI * ( pkRipple->f32CurrentRadius - f32Distance ) / pkRipple->f32Radius * pkRipple->f32Lifespan / pkRipple->f32RippleCycle );
                            break;
                            
                        case RIPPLE_TYPE_WATER:
                        default: 
                            f32Correction = ( pkRipple->f32Radius * pkRipple->f32RippleCycle / pkRipple->f32Lifespan ) / ( pkRipple->f32CurrentRadius - f32Distance );
                            if (f32Correction > 1.0f) f32Correction = 1.0f;
                            f32Correction *= f32Correction;
                            
                            f32Correction *= sinf( 2 * M_PI * ( pkRipple->f32CurrentRadius - f32Distance ) / pkRipple->f32Radius * pkRipple->f32Lifespan / pkRipple->f32RippleCycle );
                            break;
                            
                    }
                    f32Correction *= 1 - (f32Distance / pkRipple->f32CurrentRadius);
                    f32Correction *= 1 - (pkRipple->f32Runtime / pkRipple->f32Lifespan);
                    f32Correction *= RIPPLE_BASE_GAIN;
                    f32Correction *= pkRipple->f32Strength;

                    f32Correction /= ccpDistance(pkRipple->kCenterCoordinate, kPos);
                    kPos = ccpAdd( kPos, ccpMult(ccpSub( kPos, pkRipple->kCenterCoordinate), f32Correction));

					kPos = ccpClamp(kPos, CCPointZero, ccp( m_pkTexture->getMaxS(), m_pkTexture->getMaxT()));
                    m_pkRippleCoordinate[count] = kPos;
                    
                }
            }
        }
        pkRipple->f32CurrentRadius = pkRipple->f32Radius * pkRipple->f32Runtime / pkRipple->f32Lifespan;
        pkRipple->f32Runtime += dt;
        if (pkRipple->f32Runtime >= pkRipple->f32Lifespan)
		{
            free(pkRipple);
            m_kRippleList.erase(m_kRippleList.begin() + count);
            
        }
		else
		{
         
        }
        
    }
}

CCTexture2D* CCRippleSprite::SpriteTexture()
{
    return m_pkTexture;
}

void CCRippleSprite::draw()
{ 
    if (!this->isVisible()) {
        return;
    }
    
    CC_NODE_DRAW_SETUP();
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);
	
    ccGLBindTexture2D(m_pkTexture->getName() );
    
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, (void*) m_pkVertice);

    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, (m_kRippleList.size() == 0 ) ? m_pkTextureCoordinate : m_pkRippleCoordinate);

    for (ODEInt32 strip(0); strip < m_i32QuadCountY; strip++)
	{
        glDrawArrays(GL_TRIANGLE_STRIP, strip * m_i32VerticesPrStrip, m_i32VerticesPrStrip);
    }
 
}

bool CCRippleSprite::IsPointInsideSprite( CCPoint kPos )
{
    ODEFloat32 f32MaxX = m_pkTexture->getContentSize().width / m_f32ScaleRTT;
    ODEFloat32 f32MaxY = m_pkTexture->getContentSize().height / m_f32ScaleRTT;
    
    if(kPos.x < 0 || kPos.y < 0 ||
       kPos.x > f32MaxX || kPos.y > f32MaxY)
	{
        return false;
    }
    else
	{
        return true;
    }
}

bool CCRippleSprite::IsTouchInsideSprite(CCTouch* pkTouch)
{
    CCPoint kPos;
    kPos = pkTouch->getLocationInView();
    kPos = CCDirector::sharedDirector()->convertToGL(kPos);
    kPos = this->convertToNodeSpace(kPos);
    
    return this->IsPointInsideSprite(kPos);
}

bool CCRippleSprite::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!this->IsTouchInsideSprite(pTouch)) {
        return false;
    }
    
    this->ccTouchMoved(pTouch, pEvent);
    return true;
}


void CCRippleSprite::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint pos;
    pos = pTouch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    pos = this->convertToNodeSpace(pos);
    
   this->AddRipple(pos, RIPPLE_TYPE_WATER, 2.0f);
}


void CCRippleSprite::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}


void CCRippleSprite::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CCRippleSprite::onEnterTransitionDidFinish()
{
    CCSprite::onEnterTransitionDidFinish();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void CCRippleSprite::onExit()
{
    CCSprite::onExit();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}