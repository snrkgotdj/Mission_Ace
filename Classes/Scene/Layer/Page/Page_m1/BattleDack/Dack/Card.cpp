//
//  Card.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "Card.hpp"
#include "Dack.hpp"
#include "BattleDack.hpp"
#include "Page_m1.hpp"
#include "Layer_Main.hpp"
#include "SelectScene.h"

using namespace std;

CCard::CCard()
: m_pBattleDack(nullptr)
, m_pCardSel(nullptr)
, m_vBeforePos(Vec2::ZERO)
, m_tSize(Size::ZERO)
, m_iRow(-1)
, m_iCol(-1)
, m_eCardState(CARD_END)
, m_iOpacity(255)
, m_fSizeUpScale(1.15)
, m_bLeft(true)

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
    
    m_pBattleDack = _pBattleDack;
    setAnchorPoint(Vec2(0.5, 0.5));
    
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
    case CARD_DISABLE :             cardDisable(_fDelta);       break;
    case CARD_ENABLE :              cardEnable(_fDelta);        break;
    case CARD_WAVE_LEFT :           cardWave(_fDelta);          break;
    case CARD_WAVE_RIGHT :          cardWave(_fDelta);          break;
    case CARD_SIZEUP :              cardSizeUp(_fDelta);        break;
    case CARD_SIZEDOWN :            cardSizeDown(_fDelta);      break;
    case CARD_END :                 cardEnd();                  break;
        
    }
    
}

void CCard::setState(CARD_STATE _eState)
{
    m_eCardState = _eState;
    switch((int)_eState)
    {
        case CARD_WAVE_LEFT:    m_bLeft = true;     this->scheduleUpdate();     break;
        case CARD_WAVE_RIGHT:   m_bLeft = false;    this->scheduleUpdate();     break;
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

void CCard::cardEnable(float _fDelta)
{
    m_iOpacity += _fDelta * 255;
    
    if(m_iOpacity >= 255)
    {
        m_iOpacity = 255;
        this->unscheduleUpdate();
    }
    
    setOpacity(m_iOpacity);
}

void CCard::cardWave(float _fDelta)
{
    Vec3 vRot = getRotation3D();
    float fTurn = 0.5;
    if(true == m_bLeft)
    {
        vRot.z -= _fDelta * 15;
        if(vRot.z <= -fTurn)
        {
            vRot.z = -fTurn;
            m_bLeft = false;
        }
    }
    else if(false == m_bLeft)
    {
        vRot.z += _fDelta * 10;
        if(vRot.z >= fTurn)
        {
            vRot.z = fTurn;
            m_bLeft = true;
        }
    }
    
    this->setRotation3D(vRot);
}

void CCard::cardSizeUp(float _fDelta)
{
    cardWave(_fDelta);
    
    float fScale = this->getScale();
    fScale += _fDelta * 0.5;
    if(fScale >= m_fSizeUpScale)
    {
        fScale = m_fSizeUpScale;
    }
    
    this->setScale(fScale);
}

void CCard::cardSizeDown(float _fDelta)
{
    cardWave(_fDelta);
    
    float fScale = this->getScale();
    fScale -= _fDelta * 0.5;
    if(fScale <= 1.0)
    {
        fScale = 1.0;
    }
    
    this->setScale(fScale);
}

void CCard::cardEnd()
{
    this->setRotation3D(Vec3::ZERO);
    this->setScale(1);
    unscheduleUpdate();
}


void CCard::disable()
{
    m_iOpacity = 255;
    m_eCardState = CARD_DISABLE;
    this->scheduleUpdate();
}

void CCard::enable()
{
    m_iOpacity = 0;
    m_eCardState = CARD_ENABLE;
    this->scheduleUpdate();
}

void CCard::enableTouch()
{
    auto touch = EventListenerMouse::create();
    touch->onMouseDown = CC_CALLBACK_1(CCard::OnMouseTouch, this);
    touch->onMouseMove = CC_CALLBACK_1(CCard::OnMouseMove, this);
    touch->onMouseUp = CC_CALLBACK_1(CCard::OnMouseUp, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
}

void CCard::OnMouseTouch(Event *_event)
{
    const Rect& rect = this->getBoundingBox();
    EventMouse* pMouse = (EventMouse*)_event;
    CDack* pDack = m_pBattleDack->getDack();
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    m_vBeforePos = vMousePos;
    
    if(pDack->isMouseOn(_event))
    {
        // 덱의 카드를 클릭했다
        m_pCardSel = pDack->getSelCard();
        
    }
    
    else if(rect.containsPoint(vMousePos))
    {
        //현재 선택한 카드를 클릭했다.
        m_pCardSel = this;
    }
    else
    {
        // 전혀 다른데를 클릭했다.
        m_pBattleDack->renewCardPos();
        m_pBattleDack->enableCard();
        _eventDispatcher->pauseEventListenersForTarget(this);
        ((CSelectScene*)m_pBattleDack->getPage()->getMainLayer()->getScene())->setTouchNext(true);
    }
}

void CCard::OnMouseMove(Event *_event)
{
    if(nullptr == m_pCardSel)
        return;
    
    EventMouse* pMouse = (EventMouse*)_event;
    CDack* pDack = m_pBattleDack->getDack();
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    Vec2 vMove = m_pCardSel->getPosition() - (m_vBeforePos - vMousePos);
    
    m_pCardSel->setPosition(vMove);
    m_vBeforePos = vMousePos;
    Rect rect = getBoundingBox();
    rect.size = rect.size * 2;
    
    if(m_pCardSel == this)
    {
        if(true == pDack->isMouseOn(m_pCardSel->getPosition()))
        {
            pDack->getSelCard()->setState(CARD_SIZEUP);
        }
        else
        {
            if(nullptr!= pDack->getSelCard())
                pDack->getSelCard()->setState(CARD_SIZEDOWN);
        }
    }
    
    else
    {
        if(true == pDack->isMouseOnSecond(vMousePos))
        {
            pDack->getSelCard2()->setState(CARD_SIZEUP);
        }
        else
        {
            if(nullptr!= pDack->getSelCard2())
                pDack->getSelCard2()->setState(CARD_SIZEDOWN);
        }
    }
}

void CCard::OnMouseUp(Event *_event)
{
    if(nullptr == m_pCardSel)
        return;
    
    EventMouse* pMouse = (EventMouse*)_event;
    CDack* pDack = m_pBattleDack->getDack();
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    
    if(m_pCardSel == this)
    {
        if(true == pDack->isMouseOn(m_pCardSel->getPosition()))
        {
            
        }
        else
        {
            
        }
    }
    else
    {
        if(true == pDack->isMouseOnSecond(vMousePos))
        {
            pDack->changeCard();
        }
        else
        {
            pDack->resetSelCard();
        }
    }
    m_pCardSel = nullptr;
}
