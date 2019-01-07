//
//  PopupPage.cpp
//  UIMaking
//
//  Created by cd-someone on 27/12/2018.
//

#include "PopupPage.hpp"
#include "Page.hpp"
#include "Layer_Main.hpp"
#include "SelectScene.h"

CPopupPage::CPopupPage()
    :m_pSprite(nullptr)
{
    
}

CPopupPage::~CPopupPage()
{
    
}

bool CPopupPage::init(const char *_string, CPage *_pPage)
{
    if(!Layer::init())
        return false;
    
    const Size& vSize = Director::getInstance()->getVisibleSize();
    
    Sprite* pSprite = Sprite::create("Pannel.png");
    pSprite->setContentSize(Size(vSize.width * 0.5, vSize.width * 0.5));
    pSprite->setPosition(Size(vSize * 0.5));
    
    Label* pLabel = Label::createWithSystemFont(_string, "Thonburi", vSize.width * 0.1);
    pLabel->setColor(Color3B::BLACK);
    pLabel->setPosition(Vec2(pSprite->getContentSize() * 0.5));
    
    pSprite->addChild(pLabel);
    this->addChild(pSprite);
    _pPage->addChild(this);
    
    m_pSprite = pSprite;
    m_pPage = _pPage;
    
    auto touch = EventListenerTouchOneByOne::create();
    touch->onTouchBegan = CC_CALLBACK_2(CPopupPage::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
    
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget((Layer*)m_pPage->getMainLayer());
    ((CSelectScene*)m_pPage->getMainLayer()->getScene())->setTouch(false);
    return true;
}

CPopupPage* CPopupPage::create(const char *_string, CPage *_pPage)
{
    CPopupPage *pRet = new(std::nothrow) CPopupPage();
    if (pRet && pRet->init(_string, _pPage))
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

bool CPopupPage::onTouchBegan(Touch* touch, Event* event)
{
    Rect rect = m_pSprite->getBoundingBox();
    
    if(rect.containsPoint(touch->getLocation()))
    {
        
    }
    else
    {
        ((CSelectScene*)m_pPage->getMainLayer()->getScene())->setTouchNext(true);
        m_pPage->removeChild(this);
    }
    
    return true;
}
