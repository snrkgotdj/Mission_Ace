//
//  EventGroup.cpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#include "EventGroup.hpp"
#include "Page_2.hpp"
#include "VerticalLayer.hpp"
#include "EventIcon.hpp"
#include "EventIconMaker.hpp"

using namespace cocos2d;


CEventGroup::CEventGroup()
    : m_pPage(nullptr)
    , m_iTitlePosY(0)
    , m_pTitle(nullptr)
    , m_pCurIcon(nullptr)
    , m_pEventIconMaker(nullptr)
    , m_pIconName("EventItem_00.png")
{
    
}

CEventGroup::~CEventGroup()
{
    if(m_pEventIconMaker)
        delete m_pEventIconMaker;
    
}

bool CEventGroup::init(const char* _strSprite, const char* _LabelName, CVerticalLayer* _pPage, int _iPosY)
{
    if(!Layer::init())
        return false;
    
    this->initData();
    m_strLabel = _LabelName;
    m_pPage = _pPage;
    m_iTitlePosY = m_vVisibleSize.y - _iPosY;
    
    //타이틀 만들기
    m_pTitle = Sprite::create(_strSprite);
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

CEventGroup* CEventGroup::create(const char* _strSprite, const char* _LabelName, CVerticalLayer* _pPage, int _iPosY)
{
    CEventGroup *pRet = new(std::nothrow) CEventGroup();
    if (pRet && pRet->init(_strSprite, _LabelName, _pPage, _iPosY))
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
    if(m_pEventIconMaker == nullptr)
        return;
    
    CEventIcon* pIcon = m_pEventIconMaker->create(m_pIconName.c_str(), this);
    pIcon->setAnchorPoint(Vec2(0.5, 1));
    pIcon->setContentSize(m_tItemSize);
    pIcon->setDefaultSize(m_tItemSize);
    
    int iItemPosY = -m_tItemSize.height * m_listIcon.size();
    pIcon->setPosition(Vec2(m_tTitleSize.width * 0.5, iItemPosY));
    
    char str[255] = {};
    sprintf(str, "event_%d", (int)m_listIcon.size() + 1);
    
    Label* pLabel = Label::createWithSystemFont(str, "Thonburi", 50);
    pLabel->setPosition(m_vItemLabelPos);
    pLabel->setColor(Color3B::WHITE);
    pLabel->setTag(0);
    m_listIcon.push_back(pIcon);
    
    m_pPage->addHeight(m_tItemSize.height);
    m_pPage->renewPosition();
    
    pIcon->addChild(pLabel);
    m_pTitle->addChild(pIcon);
}

int CEventGroup::getFullHeight()
{
    int iHeight = m_tTitleSize.height + m_listIcon.size() * m_tItemSize.height;
    
    return iHeight;
}

void CEventGroup::renewPosition(int _iTitlePos)
{
    m_iTitlePosY = m_vVisibleSize.y - _iTitlePos;
    m_pTitle->setPosition(m_vVisibleSize.x * 0.5, m_iTitlePosY);
}

bool CEventGroup::mouseTouch(Event *_event)
{
    if(m_pCurIcon)
        m_pCurIcon->touchMouse();
    return true;
}

bool CEventGroup::mouseMove()
{
    if(m_pCurIcon)
        m_pCurIcon->moveMouse();
    
    return true;
}

bool CEventGroup::mouseUp()
{
    if(m_pCurIcon)
        m_pCurIcon->upMouse();
    
    return true;
}


bool CEventGroup::isMouseOn(Event *_event)
{
    EventMouse* pMouse = (EventMouse*)_event;
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    Vec2 vLayerPos = m_pPage->getPosition();
    for(auto& icon : m_listIcon)
    {
        Rect rect = icon->getBoundingBox();
        Rect TitleRect = m_pTitle->getBoundingBox();
        rect.origin += TitleRect.origin;
        rect.origin.y += vLayerPos.y;
        if(rect.containsPoint(vMousePos))
        {
            m_pCurIcon = icon;
            return true;
        }
    }
    return false;
}

void CEventGroup::initData()
{
    m_vVisibleSize = Director::getInstance()->getVisibleSize();
    
    m_tTitleSize = Size(m_vVisibleSize.x -20, m_vVisibleSize.y * 0.1);
    m_vLabelPos = Vec2(m_vVisibleSize.x * 0.5,m_tTitleSize.height * 0.4);
    m_vPlusPos = Vec2(m_vVisibleSize.x * 0.9,m_tTitleSize.height * 0.8);
    m_tItemSize = Size(m_tTitleSize.width - 20, m_vVisibleSize.y * 0.2);
    m_vItemLabelPos = Vec2(m_tItemSize.width * 0.5, m_tItemSize.height * 0.82);
    
    m_pEventIconMaker = new CEventIconMaker;
}
