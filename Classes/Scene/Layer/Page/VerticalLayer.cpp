//
//  VerticleLayer.cpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#include "VerticalLayer.hpp"
#include "Layer_Main.hpp"
#include "Layer_Select.hpp"
#include "Page.hpp"
#include "EventGroup.hpp"
#include "EventGroup_01.hpp"


CVerticalLayer::CVerticalLayer()
    : m_pPage(nullptr)
    , m_pCurSelGroup(nullptr)
    , m_vVisibleSize(Vec2(0, 0))
    , m_vMouseDiff(Vec2(0, 0))
    , m_bMouseMove(false)
    , m_iNextEventY(50)
    , m_iFirstEventY(50)
    , m_iEvnetNumber(1)
    , ScrollSpeed(30)
{
    
}

CVerticalLayer::~CVerticalLayer()
{
    
}

void CVerticalLayer::update(float _delta)
{
    if(false == m_bMouseMove)
        return;
    
    const Vec2& vPos = this->getPosition();
    const Size& MenuIconSize = m_pPage->getMainLayer()->getSelectLayer()->getCurIconSize();
    int iBottomY = m_vVisibleSize.y - MenuIconSize.height;
    if(vPos.y < 0)
    {
        this->stopAllActions();
        this->setPositionY(0);
        m_bMouseMove = false;
    }
    
    else if(vPos.y + m_vVisibleSize.y > m_iNextEventY + MenuIconSize.height)
    {
        this->stopAllActions();
        this->setPositionY( m_iNextEventY - iBottomY);
        m_bMouseMove = false;
    }
  
}

bool CVerticalLayer::init(CPage* _pPage)
{
    if(!LayerColor::init())
        return false;
    
    m_pPage = _pPage;
    m_vVisibleSize = Director::getInstance()->getVisibleSize();
    
    auto pLabel_Plus = Label::createWithSystemFont("+", "Thonburi", m_vVisibleSize.x * 0.25);
    auto PlusItem = MenuItemLabel::create(pLabel_Plus, CC_CALLBACK_1(CVerticalLayer::plusEventGroup, this));
    Menu* pMenu = Menu::create(PlusItem, nullptr);
    pMenu->setPosition(Vec2(m_vVisibleSize.x - 30, m_vVisibleSize.y -10));
    
    this->addChild(pMenu);
    this->scheduleUpdate();
    
    auto MouseEvent = EventListenerMouse::create();
    MouseEvent->onMouseMove = CC_CALLBACK_1(CVerticalLayer::OnMouseMove, this);
    MouseEvent->onMouseUp = CC_CALLBACK_1(CVerticalLayer::OnMouseUp, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(MouseEvent, this);
    
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

void CVerticalLayer::mouseTouch(Event *_event)
{
    for(auto& group : m_vecEventgroup)
    {
        if(group->isMouseOn(_event))
        {
            m_pCurSelGroup = group;
            group->mouseTouch(_event);
            m_bMouseMove = false;
            break;
        }
    }
}

void CVerticalLayer::OnMouseMove(Event* _event)
{
    if(nullptr == m_pCurSelGroup)
        return;
    
    m_pCurSelGroup->mouseMove();
    m_pCurSelGroup = nullptr;
}

void CVerticalLayer::OnMouseUp(Event* _event)
{
    if(nullptr == m_pCurSelGroup)
        return;
    
    if(m_bMouseMove)
        return;
    
    m_pCurSelGroup->mouseUp();
    m_pCurSelGroup = nullptr;
}


void CVerticalLayer::VerticalMove(const Vec2& _vDiff)
{
    this->setPositionY(this->getPositionY() + _vDiff.y);
    m_vMouseDiff = _vDiff;
}

void CVerticalLayer::VerticalMoveUp()
{
    const Vec2& vPos = this->getPosition();
    ActionInterval* action = nullptr;
    
    if(vPos.y < 0)
    {
        action = EaseOut::create(MoveTo::create(0.7f, Vec2( vPos.x, 0)), 7);
    }
    
    else
    {
        const Size& MenuIconSize = m_pPage->getMainLayer()->getSelectLayer()->getCurIconSize();
        int iBottomY = m_vVisibleSize.y - MenuIconSize.height;
        if(m_iNextEventY < iBottomY)
        {
            action = EaseOut::create(MoveTo::create(0.7f, Vec2( vPos.x, 0)), 7);
        }
        
        else
        {
            if(vPos.y + m_vVisibleSize.y > m_iNextEventY + MenuIconSize.height)
            {
                action = EaseOut::create(MoveTo::create(0.7f, Vec2( vPos.x, m_iNextEventY - iBottomY)), 7);
            }
            else
            {
                action = EaseOut::create(MoveBy::create(0.7f, Vec2( 0, m_vMouseDiff.y * ScrollSpeed)), 7);
                m_bMouseMove = true;
            }
        }
    }
    
    if(action)
        this->runAction(action);
    
    m_vMouseDiff = Vec2::ZERO;
}

void CVerticalLayer::plusEventGroup(Ref* _sender)
{
    char str[255] = {};
    sprintf(str, "Title_%d", (int)m_vecEventgroup.size() + 1);
    CEventGroup* pEvent = nullptr;
    if(m_vecEventgroup.size() % 2)
    {
        pEvent = CEventGroup::create("EventGroup_00.png", str, this, m_iNextEventY);
    }
    else
    {
        pEvent = CEventGroup_01::create("EventGroup_01.png", str, this, m_iNextEventY);
        pEvent->setTitleSizeY(m_vVisibleSize.y * 0.12);
        pEvent->setIconSizeY(m_vVisibleSize.y * 0.25);
        pEvent->setIconName("EventItem_01.png");
    }
    
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

