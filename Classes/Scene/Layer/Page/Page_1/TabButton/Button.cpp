//
//  Button.cpp
//  UIMaking
//
//  Created by cd-someone on 24/12/2018.
//

#include "Button.hpp"
#include "TabBase.hpp"

CButton::CButton()
:m_pOn(nullptr)
, m_pOff(nullptr)
, m_pTab(nullptr)
{}

CButton::~CButton()
{}

bool CButton::init(const char* _strOn, const char* _strOff)
{
    if(!Node::init())
        return false;
    
    const Vec2& vVisible = Director::getInstance()->getVisibleSize();
    
    m_pOn = Sprite::create(_strOn);
    m_pOff = Sprite::create(_strOff);
    
    m_pOn->setAnchorPoint(Vec2(0, 1));
    m_pOff->setAnchorPoint(Vec2(0, 1));
    
    setContentSize(Size(vVisible.x / 3, vVisible.y * 0.1));
    
    this->addChild(m_pOn, 0);
    this->addChild(m_pOff, 1);
    
    return true;
}

CButton* CButton::create(const char* _strOn, const char* _strOff)
{
    CButton *pRet = new(std::nothrow) CButton();
    if (pRet && pRet->init(_strOn, _strOff))
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

bool CButton::mouseTouch(Event* _event)
{
    EventMouse* pMouse = (EventMouse*)_event;
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    
    Rect rect = m_pOn->getBoundingBox();
    if(!rect.containsPoint(vMousePos))
    {
        return false;
    }
    
    return true;
}

void CButton::setOn()
{
    if(m_pOn)
        m_pOn->setZOrder(1);
    if(m_pOff)
        m_pOff->setZOrder(0);
    if(m_pTab)
    {
        m_pTab->setZOrder(2);
        m_pTab->setTabOn();
    }
}


void CButton::setOff()
{
    if(m_pOn)
        m_pOn->setZOrder(0);
    if(m_pOff)
        m_pOff->setZOrder(1);
    if(m_pTab)
        m_pTab->setZOrder(1);
}
