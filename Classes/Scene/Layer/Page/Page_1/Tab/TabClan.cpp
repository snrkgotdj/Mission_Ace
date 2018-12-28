//
//  TabClan.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "TabClan.hpp"

bool CTabClan::init(CPage_1* _pPage)
{
    if(!CTabBase::init(_pPage))
        return false;
    
    setButtonOn(true);
    
    return true;
}

void CTabClan::initData()
{
    m_strTab = "ClanTab.png";
    m_strButton = "Clan_On.png";
    m_strButton_Off = "Clan_Off.png";
    
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
