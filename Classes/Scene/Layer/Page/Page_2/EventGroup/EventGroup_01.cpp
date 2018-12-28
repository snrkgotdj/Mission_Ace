//
//  EventGroup_01.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "EventGroup_01.hpp"
#include "EventIconMaker_01.hpp"


void CEventGroup_01::initData()
{
    m_vVisibleSize = Director::getInstance()->getVisibleSize();
    
    m_tTitleSize = Size(m_vVisibleSize.x -20, m_vVisibleSize.y * 0.12);
    m_vLabelPos = Vec2(m_vVisibleSize.x * 0.5,m_tTitleSize.height * 0.4);
    m_vPlusPos = Vec2(m_vVisibleSize.x * 0.9,m_tTitleSize.height * 0.8);
    m_tItemSize = Size(m_tTitleSize.width - 20, m_vVisibleSize.y * 0.25);
    m_vItemLabelPos = Vec2(m_tItemSize.width * 0.5, m_tItemSize.height * 0.82);
    
    m_pEventIconMaker = new CEventIconMaker_01;
}


CEventGroup_01* CEventGroup_01::create(const char* _strSprite, const char* _LabelName, CVerticalLayer* _pPage, int _iPosY)
{
    CEventGroup_01 *pRet = new(std::nothrow) CEventGroup_01();
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
