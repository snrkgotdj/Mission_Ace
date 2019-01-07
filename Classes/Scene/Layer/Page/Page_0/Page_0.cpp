//
//  Page_0.cpp
//  UIMaking
//
//  Created by cd-someone on 24/12/2018.
//

#include "Page_0.hpp"
#include "Layer_Main.hpp"
#include "Profile.hpp"
#include "ItemBox.hpp"

using namespace cocos2d;

CPage_0::CPage_0()
{
    
}

CPage_0::~CPage_0()
{
    
}

bool CPage_0::init(const char* _ImageName, CLayer_Main* _MainLayer)
{
    if(!CPage::init(_ImageName, _MainLayer))
        return false;
    
    Vec2 vVisible = Director::getInstance()->getVisibleSize();
    
    auto pIcon = CItemBox::create("Profile_Button.png");
    pIcon->setPosition(Vec2(vVisible.x * 0.07, vVisible.y * 0.93));
    pIcon->setContentSize(Size(vVisible.x * 0.1, vVisible.x * 0.1));
    
    Vec2 vPos = pIcon->getPosition();
    vPos.x = vVisible.x * 0.5;
    
    auto profileMid = CItemBox::create("Profile_Mid.png");
    profileMid->setContentSize(Size(vVisible.x * 0.7, vVisible.x * 0.1));
    profileMid->setPosition(vPos);
    
    vPos = profileMid->getPosition();
    vPos.x = vVisible.x * 0.93;
    
    auto setting = CItemBox::create("Profile_Setting.png");
    setting->setContentSize(Size(vVisible.x * 0.1, vVisible.x * 0.1));
    setting->setPosition(vPos);
    
    vPos.x = vVisible.x * 0.25;
    vPos.y = vVisible.y * 0.83;
    
    auto quest = CItemBox::create("Quest.png");
    quest->setContentSize(Size(vVisible.x * 0.45, vVisible.y * 0.1));
    quest->setPosition(vPos);
    
    vPos = quest->getPosition();
    vPos.x += vVisible.x * 0.45 + 20;
    
    auto crownBox = CItemBox::create("CrownBox.png");
    crownBox->setContentSize(Size(vVisible.x * 0.45, vVisible.y * 0.1));
    crownBox->setPosition(vPos);
    
    vPos.x = vVisible.x * 0.3;
    vPos.y = vVisible.y * 0.3;
    
    auto battle = CItemBox::create("Battle.png");
    battle->setContentSize(Size(vVisible.x * 0.3, vVisible.y * 0.1));
    battle->setPosition(vPos);
    
    vPos.x += vVisible.x * 0.3 + 20;
    
    auto twobytwo = CItemBox::create("2v2.png");
    twobytwo->setContentSize(Size(vVisible.x * 0.3, vVisible.y * 0.1));
    twobytwo->setPosition(vPos);
    
    this->addChild(pIcon);
    this->addChild(profileMid);
    this->addChild(setting);
    this->addChild(quest);
    this->addChild(crownBox);
    this->addChild(battle);
    this->addChild(twobytwo);
    
    m_vecItem.pushBack(pIcon);
    m_vecItem.pushBack(profileMid);
    m_vecItem.pushBack(setting);
    m_vecItem.pushBack(quest);
    m_vecItem.pushBack(crownBox);
    m_vecItem.pushBack(battle);
    m_vecItem.pushBack(twobytwo);
    
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

void CPage_0::mouseTouch(Event* _event)
{
    EventMouse* pMouse = (EventMouse*)_event;
    Vec2 vMouse = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    for(auto& button : m_vecItem)
    {
        Rect rect = button->getBoundingBox();
        if(rect.containsPoint(vMouse))
        {
            button->mouseTouch(_event);
            return;
        }
    }
}

