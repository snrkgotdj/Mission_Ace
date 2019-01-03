//
//  Page_1.cpp
//  UIMaking-mobile
//
//  Created by cd-someone on 28/12/2018.
//

#include "Page_1.hpp"
#include "TabClan.hpp"
#include "TabSociety.hpp"
#include "TabFriend.hpp"
#include "TabButton.hpp"

CPage_1::CPage_1()
:m_pTabButton(nullptr)
, m_pCurTab(nullptr)
{
    m_bVerticalMove = true;
}

CPage_1::~CPage_1()
{
    
}

CPage_1* CPage_1::create(const char* _ImageName, CLayer_Main* _MainLayer)
{
    CPage_1 *pRet = new(std::nothrow) CPage_1();
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

bool CPage_1::init(const char* _ImageName, CLayer_Main* _MainLayer)
{
    if(!CPage::init(_ImageName, _MainLayer))
        return false;
    
    // 버튼생성
    m_pTabButton = CTabButton::create(this);
    this->addChild(m_pTabButton, 3);
    
    // 탭 생성
    auto pTabClan = CTabClan::create(this);
    auto pTabSociety = CTabSociety::create(this);
    auto pTabFriend = CTabFriend::create(this);

    this->addChild(pTabClan, 2);
    this->addChild(pTabSociety, 1);
    this->addChild(pTabFriend, 1);

    m_vecTabBase.pushBack(pTabClan);
    m_vecTabBase.pushBack(pTabSociety);
    m_vecTabBase.pushBack(pTabFriend);
    
    m_pTabButton->setTab(BUTTON_CLAN, pTabClan);
    m_pTabButton->setTab(BUTTON_SOCIETY, pTabSociety);
    m_pTabButton->setTab(BUTTON_FRIEND, pTabFriend);
    
    m_pCurTab = pTabClan;
    
    return true;
}

void CPage_1::mouseTouch(Event *_event)
{
    if(m_pTabButton->isMouseOn(_event))
    {
        return;
    }
    
    if(m_pCurTab->isTouch(_event))
    {
        return;
    }
}

void CPage_1::VerticalMove(const Vec2& _vDiff)
{
    m_pCurTab->VerticalMove(_vDiff);
}

void CPage_1::VerticalMoveUp()
{
    m_pCurTab->VerticalMoveUp();
    
}

