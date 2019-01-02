//
//  Card.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "Card.hpp"
using namespace std;

CCard::CCard()
    : m_tSize(Size::ZERO)
    , m_iRow(-1)
, m_iCol(-1)
,m_eCardState(CARD_END)
, m_iOpacity(255)
{
    
}

CCard::~CCard()
{
    
}

void CCard::initData()
{
    m_tSize = Size(120, 160);
    
    m_iCost = random(1, 9);
    
    char str[25] = {};
    sprintf(str, "Card_%d.png", m_iCost);
    m_strName = str;
}

bool CCard::init(CBattleDack *_pBattleDack)
{
    initData();
    
    if(!Sprite::initWithFile(m_strName))
        return false;
    
    _pBattleDack = _pBattleDack;
    setAnchorPoint(Vec2(0, 1));
    
    setContentSize(m_tSize);
    
    return true;
}

CCard* CCard::create(CBattleDack* _pBattleDack)
{
    CCard *pRet = new(std::nothrow) CCard();
    if (pRet && pRet->init(_pBattleDack))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

void CCard::update(float _fDelta)
{
    
    switch((int)m_eCardState)
    {
    case CARD_DISABLE :
            cardDisable(_fDelta);
        break;
        
    }
    
}

void CCard::cardDisable(float _fDelta)
{
    m_iOpacity -= _fDelta * 255;
    
    if(m_iOpacity <= 0)
    {
        m_iOpacity = 0;
        this->unscheduleUpdate();
    }
    
        
    setOpacity(m_iOpacity);
    
}

void CCard::disAble()
{
    m_eCardState = CARD_DISABLE;
    this->scheduleUpdate();
}
