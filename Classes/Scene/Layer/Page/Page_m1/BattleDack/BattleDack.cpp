//
//  BattleDack.cpp
//  UIMaking-mobile
//
//  Created by cd-someone on 28/12/2018.
//

#include "BattleDack.hpp"
#include "Dack.hpp"
#include "Card.hpp"
#include "Page_m1.hpp"
#include "SelectScene.h"
#include "Layer_Main.hpp"
#include "Layer_Select.hpp"

using namespace std;

CBattleDack::CBattleDack()
    : m_pDack(nullptr)
    , m_pSelCard(nullptr)
    , m_iFirstCardCount(13)
    , m_vCardStartPos(Vec2::ZERO)
    , m_vCardPad(Vec2::ZERO)
    , m_iLastRow(0)
    , m_iLastColum(0)
{
    
}

CBattleDack::~CBattleDack()
{
    
}

bool CBattleDack::init(CPage_m1 *_pPage)
{
    if(!Layer::init())
        return false;
    
    m_pDack = CDack::create(this);
    m_pPage = _pPage;
    
    this->addChild(m_pDack);
    
    createCard();
    
    auto touch = EventListenerMouse::create();
    touch->onMouseMove = CC_CALLBACK_1(CBattleDack::OnMouseMove, this);
    touch->onMouseUp = CC_CALLBACK_1(CBattleDack::OnMouseUp, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
    return true;
}

CBattleDack* CBattleDack::create(CPage_m1* _pPage)
{
    CBattleDack *pRet = new(std::nothrow) CBattleDack();
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

void CBattleDack::createCard()
{
    Vec2 vPannelSize = m_pDack->getPannelSize();
    Vec2 vDackPos = m_pDack->getDackPos();
    const Vec2& vVisibleSize = Director::getInstance()->getVisibleSize();
    
    
    
    CCard* pCard = nullptr;
    for(int i = 0; i < m_iFirstCardCount; ++i)
    {
        pCard = CCard::create(this);
        addChild(pCard);
        
        m_listCard.push_back(pCard);
    }
    m_vCardSize = pCard->getContentSize();
    m_vCardPad.x = (vVisibleSize.x - m_vCardSize.x * 4 - vDackPos.x * 2) * 0.25;
    m_vCardPad.y = m_vCardPad.x * 2;
    
    vDackPos.x += 10 + m_vCardSize.x * 0.5;
    vDackPos.y -= vPannelSize.y + 70 + m_vCardSize.y * 0.5;
    m_vCardStartPos = vDackPos;
    
    renewCardPos();
}

void CBattleDack::renewCardPos()
{
    int i = 0;
    Vec2 vCardPos = m_vCardStartPos;
    m_listCard.sort([](CCard* _pLeft, CCard*
                       _pRight)->bool {return (_pLeft->getCost() < _pRight->getCost()); });

    Vec2 iCardSize = Vec2::ZERO;
    for(auto& card : m_listCard)
    {
        m_iLastRow = i % 4;
        m_iLastColum = i / 4;
        iCardSize = card->getContentSize();

        vCardPos.x = m_vCardStartPos.x + m_iLastRow * (iCardSize.x + m_vCardPad.x);
        vCardPos.y = m_vCardStartPos.y - m_iLastColum * (iCardSize.y + m_vCardPad.y);
        card->setPosition(vCardPos);
        card->setRowCol(m_iLastRow, m_iLastColum);
        ++i;
    }
    
    Vec2 vPannelSize = m_pDack->getPannelSize();
    Vec2 vDackPos = m_pDack->getDackPos();
    const Vec2& vVisibleSize = Director::getInstance()->getVisibleSize();
    m_iHeight = vVisibleSize.y - m_vCardStartPos.y + m_iLastColum * (iCardSize.y + m_vCardPad.y) + iCardSize.y * 0.5;
}

void CBattleDack::mouseTouch(Event *_event)
{
    if(m_pDack->isMouseOn(_event))
    {
        // 댁 클릭 옵션
        return;
    }
    
    EventMouse* pMouse = (EventMouse*)_event;
    Vec2 vMousePos = Vec2(pMouse->getCursorX(), pMouse->getCursorY());
    
    
    for(auto & card : m_listCard)
    {
        Rect rect = card->getBoundingBox();
        rect.origin.y += getPositionY();
        
        
        if(rect.containsPoint(vMousePos))
        {
            m_pSelCard = card;
            return;
        }
    }
    
}

void CBattleDack::OnMouseMove(Event *_event)
{
    if(nullptr == m_pSelCard)
        return;
    
    m_pSelCard = nullptr;
}

void CBattleDack::OnMouseUp(Event *_event)
{
    if(nullptr == m_pSelCard)
        return;
    
    disableCard(m_pSelCard);
    moveCard(m_pSelCard);
    m_pSelCard->enableTouch();
    
    m_pDack->waveCard();
    
    m_pSelCard = nullptr;
}


void CBattleDack::disableCard(CCard* _except)
{
    for(auto card: m_listCard)
    {
        if(_except == card)
            continue;
        
        card->disable();
    }
    
    ((CSelectScene*)m_pPage->getMainLayer()->getScene())->setTouch(false);
}

void CBattleDack::enableCard()
{
    for(auto card: m_listCard)
    {
        card->enable();
    }
    
    m_pDack->stopCard();
    ((CSelectScene*)m_pPage->getMainLayer()->getScene())->setTouch(false);
}

void CBattleDack::moveCard(CCard* _pCard)
{
    this->stopAllActions();
    this->setPositionY(0);
    
    const Size& MenuIconSize = m_pPage->getMainLayer()->getSelectLayer()->getCurIconSize();
    const Size& vVisible = Director::getInstance()->getVisibleSize();
    
    Vec2 vPos = Vec2(vVisible.width * 0.5 , MenuIconSize.height + m_vCardSize.y * 0.5);
    
    auto action = EaseOut::create(MoveTo::create(0.7, vPos), 5);
    
    _pCard->runAction(action);
}
