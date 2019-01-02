//
//  Dack.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "Dack.hpp"
#include "Card.hpp"
#include "BattleDack.hpp"


CDack::CDack()
: m_pBattleDack(nullptr)
, m_pPannel(nullptr)
, m_arrCard{}
, m_vVisible(Vec2::ZERO)
, m_vDackPos(Vec2::ZERO)
, m_vCardStartPos(Vec2::ZERO)
, m_vCardPad(Vec2::ZERO)
{
    
}

CDack::~CDack()
{
    
}

void CDack::initData()
{
    m_vVisible = Director::getInstance()->getVisibleSize();
    
    m_vDackPos = Vec2(m_vVisible.x * 0.5, m_vVisible.y * 0.95);
    
}

bool CDack::init(CBattleDack *_pBattleDack)
{
    if(!Layer::init())
        return false;
    
    initData();
    m_pBattleDack = _pBattleDack;
    
    m_pPannel = Sprite::create("Dack.png");
    m_pPannel->setAnchorPoint(Vec2(0.f, 1.f));
    m_pPannel->setContentSize(m_pPannel->getContentSize() * 0.7);
    Vec2 vSize = m_pPannel->getContentSize();
    m_vDackPos.x -= vSize.x * 0.5;
    m_pPannel->setPosition(m_vDackPos);
    
    createCard();
    
    this->addChild(m_pPannel);
    
    return true;
}

CDack* CDack::create(CBattleDack* _pBattleDack)
{
    CDack *pRet = new(std::nothrow) CDack();
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

void CDack::createCard()
{
    Vec2 vPannelSize = getPannelSize();
    const Vec2& vVisibleSize = Director::getInstance()->getVisibleSize();
    m_vCardStartPos = Vec2(10, m_pPannel->getContentSize().height * 0.8);
    
    Vec2 vCardPos = Vec2::ZERO;
    Vec2 vCardSize = Vec2::ZERO;
    
    CCard* pCard = nullptr;
    
    for(int i = 0; i < 8; ++i)
    {
        pCard = CCard::create(m_pBattleDack);
        
        vCardSize = pCard->getContentSize();
        
        m_vCardPad.x = (vVisibleSize.x - vCardSize.x * 4 - m_vDackPos.x * 2) * 0.25;
        m_vCardPad.y = m_vCardPad.x * 2;
        
        int iRow = i % 4;
        int iColum = i / 4;
        
        vCardPos.x = m_vCardStartPos.x + iRow * (vCardSize.x + m_vCardPad.x);
        vCardPos.y = m_vCardStartPos.y - iColum * (vCardSize.y + m_vCardPad.y);
        
        pCard->setPosition(vCardPos);
        pCard->setRowCol(iRow, iColum);
        
        m_arrCard[i] = pCard;
        m_pPannel->addChild(m_arrCard[i]);
    }
    
}

bool CDack::isMouseOn(Event *_event)
{
    EventMouse* pMouse = (EventMouse*)_event;
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    int iDackPos = m_pBattleDack->getPositionY();
    for(int i = 0; i < 8; ++i)
    {
        Rect rect = m_arrCard[i]->getBoundingBox();
        rect.origin.x += m_vDackPos.x;
        rect.origin.y = m_vDackPos.y + rect.origin.y - m_pPannel->getContentSize().height + iDackPos;
        
        if(rect.containsPoint(vMousePos))
        {
            int a = 0;
        }
    }
    
    return false;
}
