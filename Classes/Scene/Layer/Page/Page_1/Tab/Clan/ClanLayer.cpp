//
//  ClanLayer.cpp
//  UIMaking
//
//  Created by cd-someone on 03/01/2019.
//

#include "ClanLayer.hpp"
#include "TabClan.hpp"
#include "Clan.hpp"

CClanLayer::CClanLayer()
: m_pClan(nullptr)
, m_pSelClan(nullptr)
, m_vStartPos(Vec2::ZERO)
, m_vSize(Size::ZERO)
, m_iPad(10)
, m_iClanCount(50)
, m_iHeight(0)
{
    
}

CClanLayer::~CClanLayer()
{
    
}

bool CClanLayer::init(CTabClan *_pClan)
{
    if(!Layer::init())
        return false;
    
    m_pClan = _pClan;
    
    const Vec2& vVisible = Director::getInstance()->getVisibleSize();
    const Vec2& vClanSize = _pClan->getContentSize();
    
    m_vStartPos = Vec2(vVisible.x * 0.5, vVisible.y * 0.6);
    m_vSize = Size(vClanSize.x * 0.88, vClanSize.y * 0.08);
    
    CClan* sprite = nullptr;
    for(int i = 0; i< m_iClanCount; ++i)
    {
        sprite = CClan::create("Clan.png");
        sprite->setAnchorPoint(Vec2(0.5, 1));
        sprite->setContentSize(m_vSize);
        sprite->setPosition(Vec2(m_vStartPos.x, m_vStartPos.y - i * (m_vSize.height + m_iPad)));
        sprite->setClanLabel(i);
        this->addChild(sprite);
    }
    
    m_iHeight = (m_iClanCount - 1) * (m_vSize.height + m_iPad);
    
    auto touch = EventListenerTouchOneByOne::create();
    touch->setSwallowTouches(true);
    
    touch->onTouchBegan = CC_CALLBACK_2(CClanLayer::onTouchBegan, this);
    touch->onTouchMoved = CC_CALLBACK_2(CClanLayer::onTouchMoved, this);
    touch->onTouchEnded = CC_CALLBACK_2(CClanLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
    
    return true;
}

CClanLayer* CClanLayer::create(CTabClan *_pClan)
{
    CClanLayer *pRet = new(std::nothrow) CClanLayer();
    if (pRet && pRet->init(_pClan))
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

bool CClanLayer::isTouch(Event* _event)
{
    Vector<Node*> vecChildren = this->getChildren();
    EventMouse* pMouse = (EventMouse*)_event;
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    Vec2 vPos = this->getPosition();
    
    for(auto& child : vecChildren)
    {
        CClan* pClan = (CClan*)child;

        Rect rect = pClan->getBoundingBox();
        rect.origin.y += vPos.y;
        
        if(rect.containsPoint(vMousePos))
        {
            m_pSelClan = pClan;
            m_pSelClan->setState(CLAN_CLICK_ENTER);
            return true;
        }
    }
    
    return false;
}

void CClanLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(nullptr == m_pSelClan)
        return;
    
    m_pSelClan->setState(CLAN_CLICK_MOVE);
    m_pSelClan = nullptr;
}

void CClanLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(nullptr == m_pSelClan)
        return;
    
    m_pSelClan->setState(CLAN_CLICK_END);
    m_pSelClan = nullptr;
}
