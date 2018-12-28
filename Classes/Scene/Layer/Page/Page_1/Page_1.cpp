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


CPage_1::CPage_1()
{
    m_bVerticalMove = true;
}

CPage_1::~CPage_1()
{
    
}

void CPage_1::setCurTab(CTabBase *_pTab)
{
    for(auto& tab : m_vecTabBase)
    {
        if(tab != _pTab)
        {
            tab->setLocalZOrder(1);
            tab->setButtonOn(false);
        }
        else
        {
            tab->setButtonOn(true);
            tab->setLocalZOrder(2);
        }
    }
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
    
    auto pTabClan = CTabClan::create(this);
    auto pTabSociety = CTabSociety::create(this);
    auto pTabFriend = CTabFriend::create(this);
    
    this->addChild(pTabClan, 2);
    this->addChild(pTabSociety, 1);
    this->addChild(pTabFriend, 1);
    
    m_vecTabBase.pushBack(pTabClan);
    m_vecTabBase.pushBack(pTabSociety);
    m_vecTabBase.pushBack(pTabFriend);
    
    return true;
}

void CPage_1::mouseTouch(Event *_event)
{
    for(auto& tab : m_vecTabBase)
    {
        if(tab->isTouch(_event))
        {
            
            break;
        }
    }
}

