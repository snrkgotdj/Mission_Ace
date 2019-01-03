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
, m_pSelCard(nullptr)
, m_pSelCard_2(nullptr)
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
        
        vCardPos.x = m_vCardStartPos.x + iRow * (vCardSize.x + m_vCardPad.x) + pCard->getContentSize().width * 0.5;
        vCardPos.y = m_vCardStartPos.y - iColum * (vCardSize.y + m_vCardPad.y)- pCard->getContentSize().height * 0.5;
        
        pCard->setPosition(vCardPos);
        pCard->setRowCol(iRow, iColum);
        pCard->setDack(true);
        
        m_arrCard[i] = pCard;
        m_pPannel->addChild(m_arrCard[i]);
    }
    
}

bool CDack::isMouseOn(Event *_event)
{
    EventMouse* pMouse = (EventMouse*)_event;
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    
    return isMouseOn(vMousePos);
}

bool CDack::isMouseOn(const Vec2 &_vMousePos)
{
    int iDackPos = m_pBattleDack->getPositionY();
    for(int i = 0; i < 8; ++i)
    {
        Rect rect = m_arrCard[i]->getBoundingBox();
        rect.origin.x += m_vDackPos.x;
        rect.origin.y = m_vDackPos.y + rect.origin.y - m_pPannel->getContentSize().height + iDackPos;
        
        if(rect.containsPoint(_vMousePos))
        {
            m_pSelCard = m_arrCard[i];
            return true;
        }
    }
    return false;
}

bool CDack::isMouseOnSecond(const Vec2 &_vMousePos)
{
    int iDackPos = m_pBattleDack->getPositionY();
    for(int i = 0; i < 8; ++i)
    {
        Rect rect = m_arrCard[i]->getBoundingBox();
        rect.origin.x += m_vDackPos.x;
        rect.origin.y = m_vDackPos.y + rect.origin.y - m_pPannel->getContentSize().height + iDackPos;
        
        if(rect.containsPoint(_vMousePos))
        {
            if(m_pSelCard == m_arrCard[i])
                continue;
            
            m_pSelCard_2 = m_arrCard[i];
            return true;
        }
    }
    return false;
}

void CDack::waveCard()
{
    m_arrCard[0]->setState(CARD_WAVE_LEFT);
    m_arrCard[2]->setState(CARD_WAVE_LEFT);
    m_arrCard[5]->setState(CARD_WAVE_LEFT);
    m_arrCard[7]->setState(CARD_WAVE_LEFT);
    
    m_arrCard[1]->setState(CARD_WAVE_RIGHT);
    m_arrCard[3]->setState(CARD_WAVE_RIGHT);
    m_arrCard[4]->setState(CARD_WAVE_RIGHT);
    m_arrCard[6]->setState(CARD_WAVE_RIGHT);
}

void CDack::stopCard()
{
    for(int i = 0; i < 8; ++i)
    {
        m_arrCard[i]->setState(CARD_END);
    }
}

void CDack::changeCard()
{
    if(!m_pSelCard)
        return;
    if(!m_pSelCard_2)
        return;
    
    Vec2 vSize = m_pSelCard->getContentSize();
    
    int iIdx = m_pSelCard->getIdx();
    int iIdx2 = m_pSelCard_2->getIdx();
    Vec2 vPos1 = m_pSelCard->getPosition();
    Vec2 vPos2 = m_pSelCard_2->getPosition();
    Vec2 vCardPos = getCardPos(m_pSelCard);
    
    m_arrCard[iIdx] = m_pSelCard_2;
    m_arrCard[iIdx2] = m_pSelCard;
    m_pSelCard->setRowCol(iIdx2);
    m_pSelCard_2->setRowCol(iIdx);
    
    m_pSelCard->setPosition(vPos2);
    
    auto action = MoveTo::create(0.12, vCardPos);
    m_pSelCard_2->runAction(action);
}

void CDack::changeCard(CCard *_pCard)
{
    if(!m_pSelCard)
        return;
    if(!_pCard)
        return;
    
    Vec2 vPos = Vec2::ZERO;
    Vec2 vDack = m_pSelCard->getPosition();
    
    vPos.x = m_vDackPos.x + vDack.x;
    vPos.y = m_vDackPos.y + vDack.y - getPannelSize().y;
    
    //위치를 바꾼다
    _pCard->setPosition(vDack);
    m_pSelCard->setPosition(vPos);
    
    //부모와 이별한다.
    _pCard->retain();
    m_pSelCard->retain();
    _pCard->removeFromParent();
    m_pSelCard->removeFromParent();
    m_pBattleDack->subtractCard(_pCard);
    
    //부모를 새로 정한다.
    m_pBattleDack->addChild(m_pSelCard);
    m_pPannel->addChild(_pCard);
    _pCard->release();
    m_pSelCard->release();
    
    //정보를 바꾼다
    int iIdx = m_pSelCard->getIdx();
    _pCard->setRowCol(iIdx);
    m_arrCard[iIdx] = _pCard;
    _pCard->setDack(true);
    m_pSelCard->setDack(false);
    
    m_pBattleDack->setDacktoCard(m_pSelCard);
    m_pSelCard = nullptr;
    m_pSelCard_2 = nullptr;
}

void CDack::resetSelCard()
{
    if(!m_pSelCard)
        return;
    
    Vec2 vPos = getCardPos(m_pSelCard);
    auto action = MoveTo::create(0.08, vPos);
    m_pSelCard->runAction(action);
    
    m_pSelCard = nullptr;
    m_pSelCard_2 = nullptr;
}

Vec2 CDack::getCardPos(CCard* _pCard)
{
    Vec2 vCardPos = Vec2::ZERO;
    Vec2 vSize = _pCard->getContentSize();
    int iIdx = _pCard->getIdx();
    
    vCardPos.x = m_vCardStartPos.x + (iIdx % 4) * (vSize.x + m_vCardPad.x) + vSize.x * 0.5;
    vCardPos.y = m_vCardStartPos.y - (iIdx / 4) * (vSize.y + m_vCardPad.y) - vSize.y * 0.5;
    
    return vCardPos;
}
