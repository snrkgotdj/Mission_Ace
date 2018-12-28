//
//  TabSociety.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "TabSociety.hpp"

bool CTabSociety::init(CPage_1* _pPage)
{
    if(!CTabBase::init(_pPage))
        return false;
    
    setButtonOn(false);
    return true;
}

void CTabSociety::initData()
{
    m_strTab = "SocietyTab.png";
    m_strButton = "Society_On.png";
    m_strButton_Off = "Society_Off.png";
    
    m_vVisibleSize = Director::getInstance()->getVisibleSize();
    m_tTabSize = Size(m_vVisibleSize.x, m_vVisibleSize.y * 0.9);
    m_tButtonSize = Size(m_vVisibleSize.x * 0.3, m_vVisibleSize.y * 0.1 );
    m_vButtonPos = Vec2(m_tTabSize.width * 0.5, m_tTabSize.height);
}

CTabSociety* CTabSociety::create(CPage_1* _pPage)
{
    CTabSociety *pRet = new(std::nothrow) CTabSociety();
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
