//
//  CLayer_Main.cpp
//  UIMaking
//
//  Created by cd-someone on 19/12/2018.
//

#include "Layer_Main.hpp"
#include "Layer_Select.hpp"
#include "Page.hpp"
#include "Page_m1.hpp"
#include "Page_0.hpp"
#include "Page_2.hpp"
#include "Page_1.hpp"
using namespace cocos2d;

CLayer_Main::CLayer_Main()
    : m_pScene(nullptr)
    , m_pSelectLayer(nullptr)
    , m_pVerticalPage(nullptr)
    , m_bMouseOn(false)
    , m_bMouseCheckOnce(false)
    , m_bCheckVertical(false)
    , m_vOldMousePos(Vec2(0.f, 0.f))
    , m_vFirstMousePos(Vec2(0.f, 0.f))
    , m_iPagePad(50)
    , m_iCurPageTag(0)
    , m_iMaxPageTag(0)
    , m_iMinPageTag(0)
    , m_iCountPageTag(0)
    , m_fPageChangeTime(1.3f)
{
    m_vecPage.reserve(5);
}

CLayer_Main::~CLayer_Main()
{
    
}

bool CLayer_Main::init(Scene* _pScene)
{
    if(!Layer::init())
        return false;
    
    m_pScene = _pScene;
    
    m_vCenterPos = Director::getInstance()->getVisibleSize() * 0.5;
    m_tVisibleSize = Director::getInstance()->getVisibleSize();
    
    createPage();
    
    auto MouseEvent = EventListenerMouse::create();
    MouseEvent->onMouseMove = CC_CALLBACK_1(CLayer_Main::OnMouseMove, this);
    MouseEvent->onMouseUp = CC_CALLBACK_1(CLayer_Main::OnMouseUp, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(MouseEvent, this);
    
    return true;
}

void CLayer_Main::createPage()
{
    this->addPage(CPage_0::create("Neco_Main.jpeg", this));
    this->addPage(CPage_1::create("Neco_1.jpg", this));
    this->addPage(CPage_m1::create("Neco_2.jpg", this));
    this->addPage(CPage_2::create("Neco_3.jpg", this));
    this->addPage(CPage::create("Neco_4.jpg", this));
}

bool CLayer_Main::Touched(Event* _event)
{
    m_bMouseOn = true;
    EventMouse* Mouse = (EventMouse*)_event;
    m_vOldMousePos.x = Mouse->getCursorX();
    m_vOldMousePos.y = Mouse->getCursorY();
    m_vFirstMousePos = m_vOldMousePos;
    
    for(int i = 0; i < m_vecPage.size(); ++i)
    {
        if(m_vecPage.at(i)->checkTouch(m_vOldMousePos))
        {
            m_vecPage.at(i)->mouseTouch(_event);
            break;
        }
    }
    
    return true;
}

void CLayer_Main::OnMouseMove(Event* _event)
{
    if(!m_bMouseOn)
        return;
    
    EventMouse* Mouse = (EventMouse*)_event;
    Vec2 vMousePos = Vec2(Mouse->getCursorX(), Mouse->getCursorY());
    Vec2 vDiff = vMousePos - m_vFirstMousePos;
    
    float iLength = vDiff.length();
    if(iLength < 20)
    {
        m_vOldMousePos = vMousePos;
        return;
    }
    
    
    //최초 한번 마우스 체크
    if(false == m_bMouseCheckOnce)
    {
        m_bMouseCheckOnce = true;
        m_bCheckVertical = false;
        if(abs(vDiff.x) < abs(vDiff.y) * 1.5)
        {
            for(int i = 0; i < m_vecPage.size(); ++i)
            {
                if(m_vecPage.at(i)->checkVertical(vMousePos))
                {
                    m_bCheckVertical = true;
                    break;
                }
            }
        }
    }
    
    vDiff = vMousePos - m_vOldMousePos;
    
    if(m_bCheckVertical)
    {
        m_pVerticalPage->VerticalMove(vDiff);//세로일경우 체크
    }
    else
    {
        this->setPositionX(this->getPositionX() + vDiff.x);//가로일경우 체크
    }
    
    m_vOldMousePos = vMousePos;

}

void CLayer_Main::OnMouseUp(Event* _event)
{
    if(!m_bMouseOn)
        return;
    
    m_bMouseOn = false;
    m_bMouseCheckOnce = false;
    
    if(m_bCheckVertical)
    {
        m_pVerticalPage->VerticalMoveUp();
    }
    
    ActionInterval* action = nullptr;
    stopAllActions();
    int iBeforeTag = m_iCurPageTag;
    float fPosX = this->getPositionX();
    float fSize = m_tVisibleSize.width * 0.5;
    if(fPosX < -m_iCurPageTag * (m_tVisibleSize.width + m_iPagePad) - fSize)
    {
        if(m_iCurPageTag < m_iMaxPageTag)
        {
            ++m_iCurPageTag;
        }
    }
    
    else if(fPosX > -m_iCurPageTag * (m_tVisibleSize.width + m_iPagePad) + fSize)
    {
        if(m_iCurPageTag > m_iMinPageTag)
        {
            --m_iCurPageTag;
        }
    }
    
    action = EaseOut::create(MoveTo::create(m_fPageChangeTime, Vec2(-m_iCurPageTag * (m_tVisibleSize.width + m_iPagePad), 0)), 7);
    
    this->runAction(action);
    
    m_pSelectLayer->changeCulSel(iBeforeTag, m_iCurPageTag);
}

void CLayer_Main::changeCulSel(int _iCulSel)
{
    ActionInterval* action = nullptr;
    stopAllActions();
    int iBeforeTag = m_iCurPageTag;
    
    m_iCurPageTag = _iCulSel;
    
    action = EaseOut::create(MoveTo::create(m_fPageChangeTime, Vec2(-m_iCurPageTag * (m_tVisibleSize.width + m_iPagePad), 0)), 7);
    
    this->runAction(action);
    
    m_pSelectLayer->changeCulSel(iBeforeTag, m_iCurPageTag);
}

bool CLayer_Main::addPageLeft(CPage* _pPage)
{
    if(nullptr == _pPage)
        return false;
    
    this->addChild(_pPage);
    --m_iMinPageTag;
    ++m_iCountPageTag;
    
    return true;
}

bool CLayer_Main::addPageRight(CPage* _pPage)
{
    if(nullptr == _pPage)
        return false;
    
    this->addChild(_pPage);
    ++m_iMaxPageTag;
    ++m_iCountPageTag;
    
    return true;
}

Vec2 CLayer_Main::getNextPagePos() const
{
    Vec2 vPos = Vec2::ZERO;
    if(0 == m_iCountPageTag)
    {
        return vPos;
    }
    // 홀수 : 오른쪽
    else if( m_iCountPageTag % 2)
    {
        vPos.x = (m_iMaxPageTag + 1) * (m_tVisibleSize.width + m_iPagePad);
    }
    // 짝수 : 왼쪽
    else
    {
        vPos.x = (m_iMinPageTag - 1) * (m_tVisibleSize.width + m_iPagePad);
    }
    
    return vPos;
}

bool CLayer_Main::addPage(CPage *_pPage)
{
    if(nullptr == _pPage)
        return false;
    
    _pPage->setPosition(getNextPagePos());
    this->addChild(_pPage);
    _pPage->setTag(addPageTag());
    m_vecPage.pushBack(_pPage);
    
    return true;
}

int CLayer_Main::addPageTag()
{
    ++m_iCountPageTag;
    
    if(m_iCountPageTag <= 1)
    {
        return 0;
    }
    
    if( m_iCountPageTag % 2)
    {
        return --m_iMinPageTag;
    }

    else
    {
        return ++m_iMaxPageTag;
    }
}

CLayer_Main* CLayer_Main::create(Scene* _pScene)
{
    CLayer_Main *pRet = new(std::nothrow) CLayer_Main();
    if (pRet && pRet->init(_pScene))
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
