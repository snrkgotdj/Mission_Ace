//
//  ClanLayer.cpp
//  UIMaking
//
//  Created by cd-someone on 03/01/2019.
//

#include "ClanLayer.hpp"
#include "TabClan.hpp"

CClanLayer::CClanLayer()
: m_pClan(nullptr)
, m_vStartPos(Vec2::ZERO)
, m_vSize(Size::ZERO)
, m_iPad(10)
, m_iClanCount(50)
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
    
    Sprite* sprite = nullptr;
    for(int i = 0; i< m_iClanCount; ++i)
    {
        sprite = Sprite::create("Clan.png");
        sprite->setAnchorPoint(Vec2(0.5, 1));
        sprite->setContentSize(m_vSize);
        sprite->setPosition(Vec2(m_vStartPos.x, m_vStartPos.y - i * (m_vSize.height + m_iPad)));
        this->addChild(sprite);
    }
    
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
