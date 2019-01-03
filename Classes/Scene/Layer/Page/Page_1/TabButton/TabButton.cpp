//
//  TabButton.cpp
//  UIMaking
//
//  Created by cd-someone on 03/01/2019.
//

#include "TabButton.hpp"
#include "Page_1.hpp"
#include "Button.hpp"

CTabButton::CTabButton()
:m_pPage(nullptr)
,m_arrButton{}
{
    
}

CTabButton::~CTabButton()
{
    
}

bool CTabButton::init(CPage_1 *_pPage)
{
    if(!Layer::init())
        return false;
    
    const Vec2& vVisible = Director::getInstance()->getVisibleSize();
    
    m_pPage = _pPage;
    m_arrButton[BUTTON_CLAN] = CButton::create("Clan_On.png", "Clan_Off.png");
    m_arrButton[BUTTON_SOCIETY] = CButton::create("Society_On.png", "Society_Off.png");
    m_arrButton[BUTTON_FRIEND] = CButton::create("Friend_On.png", "Friend_Off.png");
    
    m_arrButton[BUTTON_CLAN]->setPosition(Vec2(0, vVisible.y));
    m_arrButton[BUTTON_SOCIETY]->setPosition(Vec2(vVisible.x / 3, vVisible.y));
    m_arrButton[BUTTON_FRIEND]->setPosition(Vec2((vVisible.x / 3) * 2, vVisible.y));
    
    this->addChild(m_arrButton[BUTTON_CLAN]);
    this->addChild(m_arrButton[BUTTON_SOCIETY]);
    this->addChild(m_arrButton[BUTTON_FRIEND]);
    
    m_arrButton[BUTTON_CLAN]->setOn();
    return true;
    
}


CTabButton* CTabButton::create(CPage_1 *_pPage)
{
    CTabButton *pRet = new(std::nothrow) CTabButton();
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

bool CTabButton::isMouseOn(Event *_event)
{
    for(int i =0 ; i < BUTTON_END; ++i)
    {
        if(m_arrButton[i]->mouseTouch(_event))
        {
            onButton(i);
            return true;
        }
    }
    
    return false;
}

void CTabButton::onButton(int _iButton)
{
    for(int i = 0; i < BUTTON_END; ++i)
    {
        if( i == _iButton)
        {
            m_arrButton[i]->setOn();
        }
        else
        {
            m_arrButton[i]->setOff();
        }
    }
}

void CTabButton::setTab(BUTTON_TYPE _eType, CTabBase* _pTab)
{
    m_arrButton[_eType]->setTab(_pTab);
}
