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
, m_vVisible(Vec2::ZERO)
, m_iOpacity(255)
, m_fSizeUpScale(1.15)
, m_bLeft(true)
, m_bDack(false)
{
    
}

CCard::~CCard()
{
    
}

void CCard::initData()
{
    m_vVisible = Director::getInstance()->getVisibleSize();
    
    m_tSize = Size(m_vVisible.x * 0.18, m_vVisible.x * 0.25);
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
    case CARD_SIZE_DOWN_WAVE:       cardWave(_fDelta);
    case CARD_SIZE_DOWN :           cardSizeDown(_fDelta);      break;
    case CARD_SIZE_ORIGIN :         cardSizeOrigin(_fDelta);    break;
    case CARD_SIZE_ORIGIN_WAVE:     cardSizeOriginWave(_fDelta);break;
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
        case CARD_SIZE_DOWN_WAVE:
        case CARD_SIZE_DOWN:                        this->scheduleUpdate();     break;
        case CARD_END :         this->setScale(1);                              break;
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
    checkChange(_fDelta);
}

void CCard::cardSizeDown(float _fDelta)
{
    float fScale = getScale();
    
    fScale -= _fDelta;
    if(fScale <= 0.9)
    {
        fScale = 0.9;
    }
    setScale(fScale);
}

void CCard::cardSizeOrigin(float _fDelta)
{
    float fScale = getScale();
    
    fScale += _fDelta;
    if(fScale >= 1)
    {
        fScale = 1;
        setState(CARD_END);
    }
    setScale(fScale);
}

void CCard::cardSizeOriginWave(float _fDelta)
{
    float fScale = getScale();
    
    fScale += _fDelta;
    if(fScale >= 1)
    {
        fScale = 1;
        m_eCardState = CARD_WAVE_RIGHT;
    }
    setScale(fScale);
    
    cardWave(_fDelta);
}

void CCard::checkChange(float _fDelta)
{
    CCard* pCard = m_pBattleDack->getChangeCard();
    
    if(nullptr == pCard)
        return;
    
    if(this == pCard)
        return;
    
    CDack* pDack = m_pBattleDack->getDack();
    
    Vec2 vDackPos = pDack->getDackPos();
    Vec2 vPannelSize = pDack->getPannelSize();
    
    Rect rect = this->getBoundingBox();
    if(!pCard->isDack())
    {
        rect.origin.x += vDackPos.x;
        rect.origin.y = vDackPos.y + rect.origin.y - vPannelSize.y + m_pBattleDack->getPosition().y;
    }
    
    float fScale = this->getScale();
    if(rect.containsPoint(pCard->getPosition()))
    {
        fScale += _fDelta * 0.5;
        if(fScale >= m_fSizeUpScale)
        {
            fScale = m_fSizeUpScale;
        }
    }
    else
    {
        fScale -= _fDelta * 0.5;
        if(fScale <= 1.0)
        {
            fScale = 1.0;
        }
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
    m_bMove = false;
    
    if(pDack->isMouseOn(_event))
    {
        // 덱의 카드를 클릭했다
        m_pCardSel = pDack->getSelCard();
        m_pCardSel->setState(CARD_SIZE_DOWN_WAVE);
    }
    
    else if(rect.containsPoint(vMousePos))
    {
        //현재 선택한 카드를 클릭했다.
        m_pCardSel = this;
    }
    else
    {
        // 전혀 다른데를 클릭했다.
        returnCard();
    }
    
    m_pBattleDack->setChangeCard(m_pCardSel);
}

void CCard::OnMouseMove(Event *_event)
{
    if(nullptr == m_pCardSel)
        return;
    
    CDack* pDack = m_pBattleDack->getDack();
    if(m_pCardSel == pDack->getSelCard())
        m_pCardSel->setState(CARD_SIZE_ORIGIN_WAVE);
    
    EventMouse* pMouse = (EventMouse*)_event;
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    Vec2 vMove = m_pCardSel->getPosition() - (m_vBeforePos - vMousePos);
    
    m_pCardSel->setPosition(vMove);
    m_vBeforePos = vMousePos;
    m_bMove = true;
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
            // 덱과 카드교체
            m_pBattleDack->enableCard(pDack->getSelCard());
            pDack->changeCard(m_pCardSel);
            m_pBattleDack->renewCardPos();
            _eventDispatcher->removeEventListenersForTarget(this);
            ((CSelectScene*)m_pBattleDack->getPage()->getMainLayer()->getScene())->setTouch(true);
        }
        else
        {
            // 선택 해제
            returnCard(false);
        }
    }
    else
    {
        if(!m_bMove)
        {
            // 덱과 카드교체
            m_pBattleDack->enableCard(pDack->getSelCard());
            pDack->changeCard(this);
            m_pBattleDack->renewCardPos();
            _eventDispatcher->removeEventListenersForTarget(this);
            ((CSelectScene*)m_pBattleDack->getPage()->getMainLayer()->getScene())->setTouch(true);
        }
        
        else if(true == pDack->isMouseOnSecond(vMousePos))
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

void CCard::returnCard(bool _bNext)
{
    m_pCardSel = nullptr;
    m_pBattleDack->renewCardPos();
    m_pBattleDack->enableCard();
    _eventDispatcher->removeEventListenersForTarget(this);
    
    if(_bNext)
        ((CSelectScene*)m_pBattleDack->getPage()->getMainLayer()->getScene())->setTouchNext(true);
    
    else
        ((CSelectScene*)m_pBattleDack->getPage()->getMainLayer()->getScene())->setTouch(true);
}
