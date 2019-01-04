//
//  TabClan.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "TabClan.hpp"
#include "ClanLayer.hpp"
#include "Page_1.hpp"
#include "Layer_Main.hpp"
#include "Layer_Select.hpp"


CTabClan::CTabClan()
: m_pClanLayer(nullptr)
, m_vMouseDiff(Vec2::ZERO)
, m_bMouseMove(false)
{
    
}

CTabClan::~CTabClan()
{
    
}

bool CTabClan::init(CPage_1* _pPage)
{
    if(!CTabBase::init(_pPage))
        return false;
    
    auto head = Sprite::create("ClanTab_Head.png");
    
    head->setContentSize(Size(m_tTabSize.width, m_tTabSize.height * 0.32));
    head->setAnchorPoint(Vec2(0.5, 1));
    head->setPosition(Vec2(m_tTabSize.width * 0.5, m_tTabSize.height));
    
    this->addChild(head, 3);
    
    m_pClanLayer = CClanLayer::create(this);
    this->addChild(m_pClanLayer, 0);
    
    this->scheduleUpdate();
    
    return true;
}

void CTabClan::initData()
{
    m_strTab = "ClanTab.png";
    
    m_vVisibleSize = Director::getInstance()->getVisibleSize();
    m_tTabSize = Size(m_vVisibleSize.x, m_vVisibleSize.y * 0.9);
    m_tButtonSize = Size(m_vVisibleSize.x * 0.3, m_vVisibleSize.y * 0.1 );
    m_vButtonPos = Vec2(m_tTabSize.width * 0.2, m_tTabSize.height);
}

CTabClan* CTabClan::create(CPage_1* _pPage)
{
    CTabClan *pRet = new(std::nothrow) CTabClan();
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

void CTabClan::update(float _fDelta)
{
    if(true == m_bMouseMove)
        return;
    
    const Vec2& vPos = m_pClanLayer->getPosition();
    const Size& MenuIconSize = m_pPage->getMainLayer()->getSelectLayer()->getCurIconSize();
    int iHeight = m_pClanLayer->getHeight();
    const Vec2& vStart = m_pClanLayer->getStartPos();
    const Vec2& vSize = m_pClanLayer->getClanSize();
    int iBottom = MenuIconSize.height + vSize.y - vStart.y + iHeight;
    
    if(vPos.y < 0)
    {
        m_pClanLayer->stopAllActions();
        m_pClanLayer->setPositionY(0);
        m_bMouseMove = false;
    }
    
    else if(vPos.y > iBottom)
    {
        m_pClanLayer->stopAllActions();
        m_pClanLayer->setPositionY(iBottom);
        m_bMouseMove = false;
    }
}

bool CTabClan::isTouch(Event *_event)
{
    if(false == CTabBase::isTouch(_event))
        return false;
    
    m_pClanLayer->isTouch(_event);
    
    
    return true;
}


void CTabClan::VerticalMove(const Vec2& _vDiff)
{
    m_pClanLayer->setPositionY(m_pClanLayer->getPositionY() + _vDiff.y);
    m_vMouseDiff = _vDiff;
    m_bMouseMove = true;
}
void CTabClan::VerticalMoveUp()
{
    const Vec2& vPos = m_pClanLayer->getPosition();
    ActionInterval* action = nullptr;
    
    if(vPos.y < 0)
    {
        action = EaseOut::create(MoveTo::create(0.7f, Vec2( vPos.x, 0)), 7);
    }
    
    else
    {
        int iHeight = m_pClanLayer->getHeight();
        const Vec2& vStart = m_pClanLayer->getStartPos();
        const Size& MenuIconSize = m_pPage->getMainLayer()->getSelectLayer()->getCurIconSize();
        const Vec2& vSize = m_pClanLayer->getClanSize();
        int iBottom = MenuIconSize.height + vSize.y - vStart.y + iHeight;
        
        if(vPos.y > iBottom)
        {
            action = EaseOut::create(MoveTo::create(0.7f, Vec2( vPos.x, iBottom)), 7);
        }
        
        else
        {
            action = EaseOut::create(MoveBy::create(0.7f, Vec2( 0, m_vMouseDiff.y * 30)), 7);
            m_bMouseMove = false;
        }
    }
    
    
    if(action)
    {
        m_pClanLayer->runAction(action);
    }
    m_vMouseDiff = Vec2::ZERO;
}
