//
//  Page_0.cpp
//  UIMaking
//
//  Created by cd-someone on 24/12/2018.
//

#include "Page_0.hpp"
#include "Layer_Main.hpp"
#include "Profile.hpp"


using namespace cocos2d;

CPage_0::CPage_0()
    :m_pProfile(nullptr)
{
    
}

CPage_0::~CPage_0()
{
    
}

bool CPage_0::init(const char* _ImageName, CLayer_Main* _MainLayer)
{
    if(!CPage::init(_ImageName, _MainLayer))
        return false;
    
    //m_pProfile = CProfile::create();
    
    //his->addChild(m_pProfile);
    
    return true;
}

CPage_0* CPage_0::create(const char* _ImageName, CLayer_Main* _MainLayer)
{
    CPage_0 *pRet = new(std::nothrow) CPage_0();
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
