//
//  Page_-1.cpp
//  UIMaking-mobile
//
//  Created by cd-someone on 28/12/2018.
//

#include "Page_m1.hpp"
#include "BattleDack.hpp"
#include "Layer_Main.hpp"
#include "Layer_Select.hpp"

CPage_m1::CPage_m1()
:m_pBattleDack(nullptr)
, m_vMouseDiff(Vec2::ZERO)
, m_bMove(false)
, m_bUseCard(false)
{
    m_bVerticalMove = true;
}

CPage_m1::~CPage_m1()
{
    
}

void CPage_m1::update(float _delta)
{
    if(m_bMove)
        return;
    
    const Vec2& vPos = m_pBattleDack->getPosition();
    const Vec2& vVisibleSize = Director::getInstance()->getVisibleSize();
    const Size& MenuIconSize = getMainLayer()->getSelectLayer()->getCurIconSize();
    int iHeight = m_pBattleDack->getHeight();
    if(vPos.y < 0)
    {
        m_pBattleDack->stopAllActions();
        m_pBattleDack->setPositionY(0);
    }
    
    else if(vPos.y + vVisibleSize.y > MenuIconSize.height + iHeight )
    {
        m_pBattleDack->stopAllActions();
        m_pBattleDack->setPositionY(MenuIconSize.height + iHeight - vVisibleSize.y);
    }
}


bool CPage_m1::init(const char* _ImageName, CLayer_Main* _MainLayer)
{
    if(!CPage::init(_ImageName, _MainLayer))
        return false;
    
    m_pBattleDack = CBattleDack::create(this);
    
    this->addChild(m_pBattleDack);
    this->scheduleUpdate();
    
    return true;
}

CPage_m1* CPage_m1::create(const char* _ImageName, CLayer_Main* _MainLayer)
{
    CPage_m1 *pRet = new(std::nothrow) CPage_m1();
    if (pRet && pRet->init(_ImageName, _MainLayer))
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

void CPage_m1::mouseTouch(Event *_event)
{
    m_bUseCard = false;
    m_pBattleDack->stopAllActions();
    m_pBattleDack->mouseTouch(_event);
    m_bMove = false;
}

void CPage_m1::VerticalMove(const Vec2& _vDiff)
{
    m_pBattleDack->setPositionY(m_pBattleDack->getPositionY() + _vDiff.y);
    m_vMouseDiff = _vDiff;
    m_bMove = true;
}

void CPage_m1::VerticalMoveUp()
{
//    m_pBattleDack->stopAllActions();
    if(m_bUseCard)
        return;
    
    const Vec2& vPos = m_pBattleDack->getPosition();
    const Vec2& vVisibleSize = Director::getInstance()->getVisibleSize();
    ActionInterval* action = nullptr;
    
    if(vPos.y < 0)
    { 
        action = EaseOut::create(MoveTo::create(0.7f, Vec2( vPos.x, 0)), 7);
    }
    
    else
    {
        const Size& MenuIconSize = getMainLayer()->getSelectLayer()->getCurIconSize();
        int iHeight = m_pBattleDack->getHeight();
        if(vPos.y + vVisibleSize.y > MenuIconSize.height + iHeight )
        {
            action = EaseOut::create(MoveTo::create(0.7f, Vec2( vPos.x, MenuIconSize.height + iHeight - vVisibleSize.y)), 7);
        }
        else
        {
            action = EaseOut::create(MoveBy::create(0.7f, Vec2( 0, m_vMouseDiff.y * 20)), 7);
            m_bMove = false;
        }
    }
    if(action)
        m_pBattleDack->runAction(action);
    
    m_vMouseDiff = Vec2::ZERO;
}
