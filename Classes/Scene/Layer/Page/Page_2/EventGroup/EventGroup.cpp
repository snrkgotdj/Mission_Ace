//
//  EventGroup.cpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#include "EventGroup.hpp"
#include "Page_2.hpp"
#include "VerticalLayer.hpp"


using namespace cocos2d;


CEventGroup::CEventGroup()
    : m_pPage(nullptr)
    , m_iTitlePosY(0)
    , m_pTitle(nullptr)
{
    
}

CEventGroup::~CEventGroup()
{
    
}

bool CEventGroup::init(const char* _LabelName, CVerticalLayer* _pPage, int _iPosY)
{
    if(!Layer::init())
        return false;
    
    initData();
    m_strLabel = _LabelName;
    m_pPage = _pPage;
    m_iTitlePosY = m_vVisibleSize.y - _iPosY;
    
    //타이틀 만들기
    m_pTitle = Sprite::create("EventGroup.png");
    m_pTitle->setAnchorPoint(Vec2(0.5, 1));
    m_pTitle->setContentSize(m_tTitleSize);
    m_pTitle->setPosition(Vec2(m_vVisibleSize.x * 0.5, m_iTitlePosY));
    
    //타이틀에 이름넣기
    Label* pLabel = Label::createWithSystemFont(m_strLabel, "Thonburi", 50);
    pLabel->setPosition(m_vLabelPos);
    pLabel->setColor(Color3B::WHITE);
    
    m_pTitle->addChild(pLabel);
    addChild(m_pTitle);
    
    // 더하기 만들기
    auto pLabel_Plus = Label::createWithSystemFont("+", "Thonburi", 50);
    auto PlusItem = MenuItemLabel::create(pLabel_Plus, CC_CALLBACK_1(CEventGroup::ItemCreate, this));
    Menu* pMenu = Menu::create(PlusItem, nullptr);
    pMenu->setPosition(m_vPlusPos);
    
    m_pTitle->addChild(pMenu);
    
    return true;
}

CEventGroup* CEventGroup::create(const char* _LabelName, CVerticalLayer* _pPage, int _iPosY)
{
    CEventGroup *pRet = new(std::nothrow) CEventGroup();
    if (pRet && pRet->init(_LabelName, _pPage, _iPosY))
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

void CEventGroup::ItemCreate(Ref* _sender)
{
    Sprite* pSprite = Sprite::create("EventItem.png");
    pSprite->setAnchorPoint(Vec2(0.5, 1));
    pSprite->setContentSize(m_tItemSize);
    
    int iItemPosY = -m_tItemSize.height * m_listSprite.size();
    pSprite->setPosition(Vec2(m_tTitleSize.width * 0.5, iItemPosY));
    
    char str[255] = {};
    sprintf(str, "event_%d", (int)m_listSprite.size() + 1);
    
    Label* pLabel = Label::createWithSystemFont(str, "Thonburi", 50);
    pLabel->setPosition(m_vItemLabelPos);
    pLabel->setColor(Color3B::WHITE);
    m_listSprite.push_back(pSprite);
    
    m_pPage->addHeight(m_tItemSize.height);
    m_pPage->renewPosition();
    
    pSprite->addChild(pLabel);
    m_pTitle->addChild(pSprite);
    
    
}

int CEventGroup::getFullHeight()
{
    int iHeight = m_tTitleSize.height + m_listSprite.size() * m_tItemSize.height;
    
    return iHeight;
}

void CEventGroup::initData()
{
    m_vVisibleSize = Director::getInstance()->getVisibleSize();
    
    m_tTitleSize = Size(m_vVisibleSize.x -20, m_vVisibleSize.y * 0.1);
    m_vLabelPos = Vec2(m_vVisibleSize.x * 0.5,m_tTitleSize.height * 0.4);
    m_vPlusPos = Vec2(m_vVisibleSize.x * 0.9,m_tTitleSize.height * 0.8);
    m_tItemSize = Size(m_tTitleSize.width - 20, m_tTitleSize.height * 2);
    m_vItemLabelPos = Vec2(m_tItemSize.width * 0.5, m_tItemSize.height * 0.82);
}

void CEventGroup::renewPosition(int _iTitlePos)
{
    m_iTitlePosY = m_vVisibleSize.y - _iTitlePos;
    m_pTitle->setPosition(m_vVisibleSize.x * 0.5, m_iTitlePosY);
}
