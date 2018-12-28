//
//  EventIcon_01.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "EventIcon_01.hpp"


void CEventIcon_01::initData()
{
    const Vec2& vSize = this->getContentSize();
    
    m_vMoneyPos = Vec2(vSize.x * 0.2, vSize.y * 0.28);
    m_vBookPos = Vec2(vSize.x * 0.2, vSize.y * 0.14);
    m_vCrystalPos = Vec2(vSize.x * 0.54, vSize.y * 0.21);
}

CEventIcon_01* CEventIcon_01::create(const std::string& _strFile, CEventGroup* _pEventGroup)
{
    CEventIcon_01 *sprite = new (std::nothrow) CEventIcon_01();
    if (sprite && sprite->initWithFile(_strFile) && sprite->init(_pEventGroup))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

