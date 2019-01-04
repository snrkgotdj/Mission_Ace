//
//  ItemBox.cpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#include "ItemBox.hpp"


CItemBox::CItemBox()
:m_eState(ITEM_END)
, m_bMouseOn(false)
{
    
}

CItemBox::~CItemBox()
{
    
}

bool CItemBox::init()
{
    this->setAnchorPoint(Vec2(0.5, 0.5));
    this->scheduleUpdate();
    
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(CItemBox::OnMouseMove, this);
    listener->onMouseUp = CC_CALLBACK_1(CItemBox::OnMouseUp, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

CItemBox* CItemBox::create(const string& _strImage)
{
    CItemBox *pRet = new(std::nothrow) CItemBox();
    if (pRet && pRet->initWithFile(_strImage) && pRet->init())
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

void CItemBox::update(float _fDelta)
{
    switch(m_eState)
    {
        case ITEM_DOWN:
            itemDown(_fDelta);
            break;
            
        case ITEM_ORIGIN:
            itemOrigin(_fDelta);
            break;
    }
}

bool CItemBox::mouseTouch(Event *_event)
{
    m_eState = ITEM_DOWN;
    m_bMouseOn = true;
    
    return true;
}

void CItemBox::OnMouseMove(Event* _event)
{
    if(m_bMouseOn == false)
        return;
    m_eState= ITEM_ORIGIN;
    m_bMouseOn = false;
}

void CItemBox::OnMouseUp(Event* _event)
{
    if(m_bMouseOn == false)
        return;
    m_eState= ITEM_ORIGIN;
    m_bMouseOn = false;
}

void CItemBox::itemDown(float _fDelta)
{
    float fScale = this->getScale();
    fScale -= _fDelta;
    
    if(fScale <= 0.95)
    {
        fScale = 0.95;
    }
    
    this->setScale(fScale);
}

void CItemBox::itemOrigin(float _fDelta)
{
    float fScale = this->getScale();
    fScale += _fDelta;
    
    if(fScale >= 1)
    {
        fScale = 1;
        m_eState = ITEM_END;
    }
    
    this->setScale(fScale);
}
