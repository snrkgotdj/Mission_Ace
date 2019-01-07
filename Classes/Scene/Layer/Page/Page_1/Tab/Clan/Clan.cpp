//
//  Clan.cpp
//  UIMaking
//
//  Created by cd-someone on 04/01/2019.
//

#include "Clan.hpp"
#include "PopupPage.hpp"
#include "ClanLayer.hpp"
#include "TabClan.hpp"
#include "Page_1.hpp"
#include "Layer_Main.hpp"

CClan::CClan()
:m_eState(CLAN_END)
{
    
}

CClan::~CClan()
{
    
}

bool CClan::init()
{
    this->setAnchorPoint(Vec2(0.5, 1));
    this->scheduleUpdate();
    
    setScoreLabel();
    
    return true;
}

CClan* CClan::create(const string& _strImage)
{
    CClan *pRet = new(std::nothrow) CClan();
    if (pRet && pRet->initWithFile(_strImage) && pRet->init())
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

void CClan::update(float _fDelta)
{
    switch((int)m_eState)
    {
        case CLAN_CLICK_ENTER:
            clickEnter(_fDelta);
            break;
            
        case CLAN_CLICK_MOVE:
            clickMove(_fDelta);
            break;
            
        case CLAN_CLICK_END:
            clickEnd(_fDelta);
            break;
    }
}

void CClan::clickEnter(float _fDelta)
{
    float fScale = this->getScale();
    fScale -= _fDelta;
    
    if(fScale <= 0.95)
    {
        fScale = 0.95;
    }
    
    this->setScale(fScale);
}

void CClan::clickMove(float _fDelta)
{
    scaleOrigin(_fDelta);
}

void CClan::clickEnd(float _fDelta)
{
    scaleOrigin(_fDelta);
}

void CClan::scaleOrigin(float _fDelta)
{
    float fScale = this->getScale();
    fScale += _fDelta;
    
    if(fScale >= 1)
    {
        fScale = 1;
        m_eState = CLAN_END;
    }
    
    this->setScale(fScale);
}

void CClan::setState(CLAN_STATE _eState)
{
    m_eState = _eState;
    
    if(m_eState == CLAN_CLICK_END)
    {
        CClanLayer* pLayer = (CClanLayer*)this->getParent();
        CPage* pPage = pLayer->getClanTab()->getPage();
        
        auto popup = CPopupPage::create(m_strLabelName.c_str(), pPage);
        
        popup->setLocalZOrder(10);
    }
}

Label* CClan::setLabel(const string& _strLabel, const Vec2& _vPos)
{
    const Size& size = Director::getInstance()->getVisibleSize();
    auto label = Label::createWithSystemFont(_strLabel, "Thonburi", size.width * 0.05);
    m_strLabelName = _strLabel;
    
    label->setAnchorPoint(Vec2(0, 0.5));
    label->setPosition(_vPos);
    label->setColor(Color3B::BLACK);
    
    this->addChild(label);
    
    return label;
}

void CClan::setClanLabel(int _iCount)
{
    char label[20] = {};
    sprintf(label, "Clan_%d", _iCount);
    
    Vec2 vSize = this->getContentSize();
    setLabel(label, Vec2(vSize.x * 0.05, vSize.y * 0.5));
}

void CClan::setScoreLabel()
{
    char label[5] = {};
    int iRand = random(1, 1000);
    sprintf(label, "%d", iRand);
    
    Vec2 vSize = this->getContentSize();
    Label* pLabel = setLabel(label, Vec2(vSize.x * 0.83, vSize.y * 0.5));
    pLabel->setAnchorPoint(Vec2(1, 0.5));
}
