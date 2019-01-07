//
//  Card_Use.cpp
//  UIMaking
//
//  Created by cd-someone on 03/01/2019.
//

#include "Card_Use.hpp"
#include "Card.hpp"
#include "BattleDack.hpp"
#include "Dack.hpp"

CCardUse::CCardUse()
:m_pCard(nullptr)
,m_pUseButton(nullptr)
,m_eState(USE_END)
{
    
}

CCardUse::~CCardUse()
{
    
}

bool CCardUse::init(CCard* _pCard)
{
    if(!Sprite::initWithFile("Card_Use.png"))
        return false;
    
    m_pCard = _pCard;
    
    Vec2 vSize = this->getContentSize();
    Vec2 vPos = _pCard->getPosition();
    this->setAnchorPoint(Vec2(0.5, 0.65));
    this->setPosition(vPos);
    
    m_pUseButton = Sprite::create("Use.png");
    m_pUseButton->setAnchorPoint(Vec2(0.5, 0.5));
    m_pUseButton->setPosition(Vec2(vSize.x * 0.5, vSize.y * 0.2));
    
    this->addChild(m_pUseButton);
    this->setTag(CARD_USE_TAG);
    
    auto event = EventListenerMouse::create();
    event->onMouseDown = CC_CALLBACK_1(CCardUse::OnMouseTouch, this);
    event->onMouseMove = CC_CALLBACK_1(CCardUse::OnMouseMove, this);
    event->onMouseUp = CC_CALLBACK_1(CCardUse::OnMouseUp, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
    
    this->scheduleUpdate();
    return true;
}

CCardUse* CCardUse::create(CCard* _pCard)
{
    CCardUse *pRet = new(std::nothrow) CCardUse();
    if (pRet && pRet->init(_pCard))
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

void CCardUse::update(float _fDelta)
{
    switch ((int)m_eState)
    {
        case USE_SCALE_DOWN:
            buttonScaleDown(_fDelta);
            break;
            
        case USE_SCALE_ORIGIN:
            buttonScaleOrigin(_fDelta);
            break;
    }
}

void CCardUse::OnMouseTouch(Event *_event)
{
    EventMouse* pMouse = (EventMouse*)_event;
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    
    Rect rect = m_pUseButton->getBoundingBox();
    rect.origin+= this->getBoundingBox().origin;
    rect.origin.y += m_pCard->getBattleDack()->getPositionY();
    if(rect.containsPoint(vMousePos))
    {
        m_eState = USE_SCALE_DOWN;
    }
}

void CCardUse::OnMouseMove(Event *_event)
{
    m_eState = USE_SCALE_ORIGIN;
}

void CCardUse::OnMouseUp(Event *_event)
{
    CBattleDack* pBattleDack = m_pCard->getBattleDack();
    if(m_eState != USE_SCALE_DOWN)
    {
        m_pCard->returnCard(false);
    }
    
    else
    {
        pBattleDack->disableCard(m_pCard);
        pBattleDack->moveCard(m_pCard);
        m_pCard->enableTouch();
        pBattleDack->getDack()->waveCard();
    }
}

void CCardUse::buttonScaleDown(float _fDelta)
{
    float fScale = m_pUseButton->getScale();
    
    fScale -= _fDelta * 2;
    if(fScale <= 0.85)
    {
        fScale = 0.85;
    }
    
    m_pUseButton->setScale(fScale);
}

void CCardUse::buttonScaleOrigin(float _fDelta)
{
    float fScale = m_pUseButton->getScale();
    
    fScale += _fDelta * 2;
    
    if(fScale >= 1)
    {
        fScale = 1;
        m_eState = USE_END;
    }
    
    m_pUseButton->setScale(fScale);
}
