//
//  Page_2.cpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#include "Page_2.hpp"
#include "Layer_Main.hpp"
#include "EventGroup.hpp"
#include "VerticalLayer.hpp"

using namespace cocos2d;

CPage_2::CPage_2()
    : m_pLayer(nullptr)
{
    m_bVerticalMove = true;
}

CPage_2::~CPage_2()
{
    
}

bool CPage_2::init(const char* _ImageName, CLayer_Main* _MainLayer)
{
    if(!CPage::init(_ImageName, _MainLayer))
        return false;
    
    m_pLayer = CVerticalLayer::create(this);
    this->addChild(m_pLayer);
    
    return true;
}

CPage_2* CPage_2::create(const char* _ImageName, CLayer_Main* _MainLayer)
{
    CPage_2 *pRet = new(std::nothrow) CPage_2();
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

void CPage_2::mouseTouch(Event *_event)
{
    m_pLayer->mouseTouch(_event);
}

void CPage_2::VerticalMove(const Vec2& _vDiff)
{
    m_pLayer->VerticalMove(_vDiff);
}

void CPage_2::VerticalMoveUp()
{
    m_pLayer->VerticalMoveUp();

}
