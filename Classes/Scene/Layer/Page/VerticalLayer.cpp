//
//  VerticleLayer.cpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#include "VerticalLayer.hpp"
#include "Layer_Main.hpp"
#include "EventGroup.hpp"


CVerticalLayer::CVerticalLayer()
    : m_pPage(nullptr)
    , m_iNextEventY(50)
    , m_iFirstEventY(50)
    , m_iEvnetNumber(1)
{
    
}

CVerticalLayer::~CVerticalLayer()
{
    
}

bool CVerticalLayer::init(CPage* _pPage)
{
    if(!Layer::init())
        return false;
    
    m_pPage = _pPage;
    
    Vec2 vSize = Director::getInstance()->getVisibleSize();
    
    auto pLabel_Plus = Label::createWithSystemFont("+", "Thonburi", 100);
    auto PlusItem = MenuItemLabel::create(pLabel_Plus, CC_CALLBACK_1(CVerticalLayer::plusEventGroup, this));
    Menu* pMenu = Menu::create(PlusItem, nullptr);
    
    pMenu->setPosition(Vec2(vSize.x - 30, vSize.y -10));
    
    this->addChild(pMenu);
    
    return true;
}

void CVerticalLayer::addHeight(int _height)
{
    m_iNextEventY += _height;
}

void CVerticalLayer::renewPosition()
{
    m_iNextEventY = m_iFirstEventY;
    for(int i = 0; i < m_vecEventgroup.size(); ++i)
    {
        m_vecEventgroup.at(i)->renewPosition(m_iNextEventY);
        m_iNextEventY += m_vecEventgroup.at(i)->getFullHeight();
    }
}

void CVerticalLayer::VerticalMove(const Vec2& _vDiff)
{
    this->setPositionY(this->getPositionY() + _vDiff.y);
}

void CVerticalLayer::VerticalMoveUp()
{
    const Vec2& vPos = this->getPosition();
    ActionInterval* action = nullptr;
    if(vPos.y < 0)
    {
        action = EaseOut::create(MoveTo::create(0.7f, Vec2( vPos.x, 0)), 7);
    }
    
    if(action)
        this->runAction(action);
    
}

void CVerticalLayer::plusEventGroup(Ref* _sender)
{
    char str[255] = {};
    sprintf(str, "Title_%d", (int)m_vecEventgroup.size() + 1);
    
    CEventGroup* pEvent = CEventGroup::create(str, this, m_iNextEventY);
    m_iNextEventY += pEvent->getFullHeight();
    m_vecEventgroup.pushBack(pEvent);
    
    this->addChild(pEvent);
}

CVerticalLayer* CVerticalLayer::create(CPage* _pPage)
{
    CVerticalLayer *pRet = new(std::nothrow) CVerticalLayer();
    if (pRet && pRet->init(_pPage))
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

