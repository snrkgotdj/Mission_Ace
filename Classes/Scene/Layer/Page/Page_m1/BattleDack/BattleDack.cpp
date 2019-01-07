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
#include "Card_Use.hpp"

using namespace std;



CBattleDack::CBattleDack()
    : m_pDack(nullptr)
    , m_pSelCard(nullptr)
    , m_pChangeCard(nullptr)
    , m_pEdit(nullptr)
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
    
    createEditor();
    
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
    m_vCardPad.x = (vVisibleSize.x - m_vCardSize.x * 4 - vDackPos.x * 2) * 0.2;
    m_vCardPad.y = m_vCardPad.x * 2;
    
    vDackPos.x += 10 + m_vCardSize.x * 0.5;
    vDackPos.y -= vPannelSize.y + 70 + m_vCardSize.y * 0.5;
    m_vCardStartPos = vDackPos;
    
    renewCardPos();
}

void CBattleDack::createEditor()
{
    const Vec2& vVisible = Director::getInstance()->getVisibleSize();
    
    auto pLabel_Plus_1 = Label::createWithSystemFont("+1", "Thonburi", vVisible.x * 0.1);
    auto pLabel_Plus_3 = Label::createWithSystemFont("+3", "Thonburi", vVisible.x * 0.1);
    
    auto PlusItem_1 = MenuItemLabel::create(pLabel_Plus_1, CC_CALLBACK_1(CBattleDack::plusCard_1, this));
    auto PlusItem_3 = MenuItemLabel::create(pLabel_Plus_3, CC_CALLBACK_1(CBattleDack::plusCard_3, this));
    
    m_pEdit = Menu::create(PlusItem_1, PlusItem_3,nullptr);
    m_pEdit->setPosition(Vec2(vVisible.x * 0.8, vVisible.y * 0.3));
    m_pEdit->alignItemsHorizontally();
    
    this->addChild(m_pEdit);
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
        //////
        auto action = MoveTo::create(0.1, vCardPos);
        card->runAction(action);
        //card->setPosition(vCardPos);
        card->setRowCol(m_iLastRow, m_iLastColum);
        card->setPositionZ(0);
        ++i;
    }
    
    Vec2 vPannelSize = m_pDack->getPannelSize();
    Vec2 vDackPos = m_pDack->getDackPos();
    const Vec2& vVisibleSize = Director::getInstance()->getVisibleSize();
    m_iHeight = vVisibleSize.y - m_vCardStartPos.y + m_iLastColum * (iCardSize.y + m_vCardPad.y) + iCardSize.y * 0.5;
    m_pChangeCard = nullptr;
}

void CBattleDack::mouseTouch(Event *_event)
{
    if(m_pDack->isMouseOn(_event))
    {
        m_pSelCard = m_pDack->getSelCard();
        m_pSelCard->setState(CARD_SIZE_DOWN);
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
            card->setState(CARD_SIZE_DOWN);
            return;
        }
    }
    
}

void CBattleDack::OnMouseMove(Event *_event)
{
    if(nullptr == m_pSelCard)
        return;
    
    if(m_pSelCard == m_pDack->getSelCard())
    {
        m_pSelCard->setState(CARD_SIZE_ORIGIN);
        m_pSelCard = nullptr;
        return;
    }
    
    m_pSelCard->setState(CARD_SIZE_ORIGIN);
    m_pSelCard = nullptr;
}

void CBattleDack::OnMouseUp(Event *_event)
{
    if(this->getChildByTag(CARD_USE_TAG))
        this->removeChildByTag(CARD_USE_TAG);
    
    if(nullptr == m_pSelCard)
        return;
    
    if(m_pSelCard == m_pDack->getSelCard())
    {
        m_pSelCard->setState(CARD_SIZE_ORIGIN);
        m_pSelCard = nullptr;
        return;
    }
    
    m_pSelCard->setState(CARD_SIZE_ORIGIN);
    createCardUse();
    ((CSelectScene*)m_pPage->getMainLayer()->getScene())->setTouch(false);
    
    m_pSelCard = nullptr;
}

void CBattleDack::createCardUse()
{
    auto cardUse = CCardUse::create(m_pSelCard);
    m_pSelCard->setOpacity(255);
    this->addChild(cardUse);
    
    lookAtUseCard(cardUse);
}

void CBattleDack::lookAtUseCard(CCardUse* _pCard)
{
    Vec2 vCardUsePos = _pCard->getPosition();
    Vec2 vCardUseSize = _pCard->getContentSize();
    Vec2 vPos = this->getPosition();
    Vec2 vIconSize = m_pPage->getMainLayer()->getSelectLayer()->getCurIconSize();
    
    
    int iHeight = vIconSize.y + vCardUseSize.y * 0.7 - vCardUsePos.y;
    
    if(vPos.y < iHeight)
    {
        auto action = EaseOut::create(MoveTo::create(1.f, Vec2( vPos.x, iHeight)), 5);
        this->runAction(action);
        m_pPage->setUseCard(true);
    }
    
}


void CBattleDack::disableCard(CCard* _except)
{
    for(auto card: m_listCard)
    {
        if(_except == card)
            continue;
        
        card->disable();
    }
}

void CBattleDack::enableCard(CCard* _pCard)
{
    for(auto card: m_listCard)
    {
        if(_pCard == card)
            continue;
        card->enable();
    }
    
    m_pDack->stopCard();
    ((CSelectScene*)m_pPage->getMainLayer()->getScene())->setTouch(false);
    m_pPage->setMove(false);
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

void CBattleDack::setDacktoCard(CCard *_pCard)
{
    list<CCard*>::iterator iter = m_listCard.begin();
    for(; iter != m_listCard.end(); ++iter)
    {
        if((*iter)->getCost() >= _pCard->getCost())
        {
            m_listCard.insert(iter, _pCard);
            break;
        }
    }
}

void CBattleDack::subtractCard(CCard *_pCard)
{
    list<CCard*>::iterator iter = m_listCard.begin();
    for(; iter != m_listCard.end(); ++iter)
    {
        if(*iter == _pCard)
        {
            m_listCard.erase(iter);
            break;
        }
    }
}

void CBattleDack::plusCard_1(Ref *_sender)
{
    CCard* pCard = CCard::create(this);
    pCard->setPosition(m_pEdit->getPosition());
    
    this->addChild(pCard);
    setDacktoCard(pCard);
    renewCardPos();
}

void CBattleDack::plusCard_3(Ref *_sender)
{
    for(int i = 0; i < 3; ++i)
    {
        CCard* pCard = CCard::create(this);
        pCard->setPosition(m_pEdit->getPosition());
        
        this->addChild(pCard);
        setDacktoCard(pCard);
    }
    renewCardPos();
}
