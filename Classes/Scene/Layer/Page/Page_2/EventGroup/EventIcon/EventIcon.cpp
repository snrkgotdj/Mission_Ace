//
//  EventIcon.cpp
//  UIMaking-mobile
//
//  Created by cd-someone on 27/12/2018.
//

#include "EventIcon.hpp"
#include "EventGroup.hpp"
#include "VerticalLayer.hpp"
#include "Page.hpp"
#include "PopupPage.hpp"
#include "Layer_Main.hpp"
#include "SelectScene.h"

CEventIcon::CEventIcon()
    : m_pEventGroup(nullptr)
    , m_eIcon(ICON_END)
    , m_fMinimumRatio(0.95f)
    , m_vDefaultSize(Vec2::ZERO)
    , m_vMoneyPos(Vec2::ZERO)
    , m_vBookPos(Vec2::ZERO)
    , m_vCrystalPos(Vec2::ZERO)
{
    
}

CEventIcon::~CEventIcon()
{
    
}

void CEventIcon::update(float _fDelta)
{
    switch((int)m_eIcon)
    {
        case ICON_SCALEDOWN:            iconScaleDown(_fDelta);            break;
        case ICON_SCALEUP:              iconScaleUp(_fDelta);              break;
            
    }
    
}

CEventIcon* CEventIcon::create(const std::string& _strFile, CEventGroup* _pEventGroup)
{
    CEventIcon *sprite = new (std::nothrow) CEventIcon();
    if (sprite && sprite->initWithFile(_strFile) && sprite->init(_pEventGroup))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool CEventIcon::init(CEventGroup* _pEventGroup)
{
    m_pEventGroup = _pEventGroup;
    this->scheduleUpdate();
    
    initData();
    
    Vec2 vSize = this->getContentSize();
    
    createItem("Money.png", m_vMoneyPos);
    createItem("Book.png", m_vBookPos);
    createCrystal("Crystal.png", m_vCrystalPos);
    
    return true;
}

void CEventIcon::touchMouse()
{
    m_eIcon = ICON_SCALEDOWN;
}

void CEventIcon::moveMouse()
{
    m_eIcon = ICON_SCALEUP;
}

void CEventIcon::upMouse()
{
    m_eIcon = ICON_SCALEUP;
    
    CPage* pPage = m_pEventGroup->getLayer()->getPage();
    Label* pLabel = (Label*)getChildByTag(0);
    CPopupPage::create(pLabel->getString().c_str(), pPage);
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget((Layer*)pPage->getMainLayer());
    ((CSelectScene*)pPage->getMainLayer()->getScene())->setTouch(false);
}

void CEventIcon::initData()
{
    const Vec2& vSize = this->getContentSize();
    
    m_vMoneyPos = Vec2(vSize.x * 0.2, vSize.y * 0.33);
    m_vBookPos = Vec2(vSize.x * 0.2, vSize.y * 0.15);
    m_vCrystalPos = Vec2(vSize.x * 0.57, vSize.y * 0.24);
}

void CEventIcon::iconScaleDown(float _fDelta)
{
    Size vSize = this->getContentSize();
    
    vSize.width -= vSize.width * _fDelta * 0.3f;
    vSize.height -= vSize.height * _fDelta * 0.3f;
    
    if(vSize.width <= m_vDefaultSize.x * m_fMinimumRatio)
    {
        vSize = m_vDefaultSize * m_fMinimumRatio;
        m_eIcon = ICON_END;
    }
    
    this->setContentSize(vSize);
}

void CEventIcon::iconScaleUp(float _fDelta)
{
    Size vSize = this->getContentSize();
    
    vSize.width += vSize.width * _fDelta * 0.3f;
    vSize.height += vSize.height * _fDelta * 0.3f;
    
    if(vSize.width >= m_vDefaultSize.x)
    {
        vSize = m_vDefaultSize;
        m_eIcon = ICON_END;
    }
    
    this->setContentSize(vSize);
}

void CEventIcon::createItem(const char* _strSprite, Vec2 _vPos, int _iData)
{
    Sprite* sprite = Sprite::create(_strSprite);
    sprite->setScale(0.9);
    sprite->setPosition(_vPos);
    this->addChild(sprite);
    
    int iData = _iData;
    if(-1 == iData)
        iData = random(0, 1000000);
    
    char str[50] = {};
    sprintf(str, "%d", iData);
    Label* pLabel = Label::createWithSystemFont(str, "Thonburi", 20);
    pLabel->setAnchorPoint(Vec2(0.f, 0.5f));
    pLabel->setPosition(Vec2(sprite->getContentSize().width, sprite->getContentSize().height * 0.5));
    
    sprite->addChild(pLabel);
}

void CEventIcon::createCrystal(const char* _strSprite, Vec2 _vPos, int _iData)
{
    Sprite* sprite = Sprite::create(_strSprite);
    sprite->setAnchorPoint(Vec2(1.f, 0.5f));
    sprite->setScale(0.9);
    
    int iData = _iData;
    if(-1 == iData)
        iData = random(0, 10000);
    
    char str[50] = {};
    sprintf(str, "%d", iData);
    Label* pLabel = Label::createWithSystemFont(str, "Thonburi", 20);
    pLabel->setAnchorPoint(Vec2(1.f, 0.5f));
    pLabel->setPosition(Vec2(0, sprite->getContentSize().height * 0.5));
    
    float fLength = (pLabel->getContentSize().width + sprite->getContentSize().width) * 0.5f;
    _vPos.x += fLength;
    
    sprite->setPosition(_vPos);
    sprite->addChild(pLabel);
    this->addChild(sprite);
}
