//
//  CProfile.cpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#include "Profile.hpp"
#include "Button.hpp"


CProfile::CProfile()
{
    
}

CProfile::~CProfile()
{
    
}

bool CProfile::init()
{
    if(!Layer::init())
        return false;
        
    m_pButton = CButton::create("Profile_Button.png");
    
    Size vSize = Director::getInstance()->getVisibleSize();
    m_pButton->setAnchorPoint(Vec2(0, 1));
    m_pButton->setContentSize(Size(vSize.width * 0.1, vSize.width * 0.1));
    m_pButton->setPosition(Size(vSize.width * 0.04, vSize.height * 0.95));
    this->addChild(m_pButton);
    
    Vec2 vPos = m_pButton->getPosition();
    vPos.x += m_pButton->getContentSize().width + 10;
    
    m_pMid = CButton::create("Profile_Mid.png");
    m_pMid->setAnchorPoint(Vec2(0, 1));
    m_pMid->setContentSize(Size(vSize.width * 0.7, vSize.width * 0.1));
    m_pMid->setPosition(vPos);
    this->addChild(m_pMid);
    
    vPos = m_pMid->getPosition();
    vPos.x += m_pMid->getContentSize().width + 10;
    
    m_pSetting = CButton::create("Profile_Setting.png");
    m_pSetting->setAnchorPoint(Vec2(0, 1));
    m_pSetting->setContentSize(Size(vSize.width * 0.1, vSize.width * 0.1));
    m_pSetting->setPosition(vPos);
    this->addChild(m_pSetting);
    
    return true;
}

