//
//  TabFriend.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "TabFriend.hpp"


bool CTabFriend::init(CPage_1* _pPage)
{
    if(!CTabBase::init(_pPage))
        return false;

    return true;
}

void CTabFriend::initData()
{
    m_strTab = "FriendTab.png";
    
    m_vVisibleSize = Director::getInstance()->getVisibleSize();
    m_tTabSize = Size(m_vVisibleSize.x, m_vVisibleSize.y * 0.9);
    m_tButtonSize = Size(m_vVisibleSize.x * 0.3, m_vVisibleSize.y * 0.1 );
    m_vButtonPos = Vec2(m_tTabSize.width * 0.8, m_tTabSize.height);
}

CTabFriend* CTabFriend::create(CPage_1* _pPage)
{
    CTabFriend *pRet = new(std::nothrow) CTabFriend();
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
