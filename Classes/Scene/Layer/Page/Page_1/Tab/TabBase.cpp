//
//  TabBase.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "TabBase.hpp"
#include "Page_1.hpp"

CTabBase::CTabBase()
    : m_pPage(nullptr)
    , m_pButton(nullptr)
    , m_pTab(nullptr)
    , m_vButtonPos(Vec2::ZERO)
    , m_vVisibleSize(Vec2::ZERO)
    , m_tTabSize(Vec2::ZERO)
    , m_tButtonSize(Vec2::ZERO)
{
    
}

CTabBase::~CTabBase()
{
    
}

bool CTabBase::init(CPage_1* _pPage)
{
    if(!Layer::init())
        return false;
    
    initData();
    m_pPage = _pPage;
    
    if(m_strTab.empty())
        return false;
    
    m_pTab = Sprite::create(m_strTab);
    m_pTab->setAnchorPoint(Vec2::ZERO);
    m_pTab->setContentSize(m_tTabSize);
    
    this->addChild(m_pTab);
    
    createButton();
    
    
    
    
    return true;
}

void CTabBase::initData()
{
    
    m_strTab = "ClanTab.png";
    m_strButton = "Clan_On.png";
    
    m_vVisibleSize = Director::getInstance()->getVisibleSize();
    m_tTabSize = Size(m_vVisibleSize.x, m_vVisibleSize.y * 0.9);
    m_tButtonSize = Size(m_vVisibleSize.x * 0.3, m_vVisibleSize.y * 0.1 );
    m_vButtonPos = Vec2(m_tTabSize.width * 0.5, m_tTabSize.height);
}

bool CTabBase::isTouch(Event* _event)
{
    auto rect = m_pButton->getBoundingBox();
    
    EventMouse* Mouse = (EventMouse*)_event;
    Vec2 vMousePos = Vec2(Mouse->getCursorX(), Mouse->getCursorY());
    
    if(rect.containsPoint(vMousePos))
    {
        m_pPage->setCurTab(this);
        return true;
    }
    rect = m_pTab->getBoundingBox();
    
    if(rect.containsPoint(vMousePos))
    {
        return true;
    }
    return false;
}

void CTabBase::setButtonOn(bool _bOn)
{
    if(_bOn)
    {
        this->removeChild(m_pButton);
        this->removeChild(m_pButton_Off);
        this->addChild(m_pButton);
    }
    else
    {
        this->removeChild(m_pButton);
        this->removeChild(m_pButton_Off);
        this->addChild(m_pButton_Off);
    }
}

void CTabBase::createButton()
{
    if(m_strButton.empty())
        return;
    
    if(m_strButton_Off.empty())
        return;
    
    m_pButton = Sprite::create(m_strButton);
    m_pButton->setAnchorPoint(Vec2(0.5f, 0.f));
    m_pButton->setContentSize(m_tButtonSize);
    m_pButton->setPosition(m_vButtonPos);
    
    m_pButton->retain();
    //m_pTab->addChild(m_pButton);
    
    m_pButton_Off = Sprite::create(m_strButton_Off);
    m_pButton_Off->setAnchorPoint(Vec2(0.5f, 0.f));
    m_pButton_Off->setContentSize(m_tButtonSize);
    m_pButton_Off->setPosition(m_vButtonPos);
    
    m_pButton_Off->retain();
    
}
