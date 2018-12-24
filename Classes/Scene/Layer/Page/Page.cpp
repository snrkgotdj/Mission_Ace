//
//  Layer_2.cpp
//  UIMaking
//
//  Created by cd-someone on 20/12/2018.
//

#include "Page.hpp"
#include "Layer_Main.hpp"

using namespace cocos2d;

CPage::CPage()
    :m_pLayer_Main(nullptr)
{
    
}

CPage::~CPage()
{
    
}

bool CPage::init(const char* _ImageName, CLayer_Main* _MainLayer)
{
    if(!Layer::init())
        return false;
    
    m_pLayer_Main = _MainLayer;
    m_pBGName = _ImageName;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if(_ImageName)
    {
        auto sprite = Sprite::create(_ImageName);
        sprite->setContentSize(Size(visibleSize.width + m_pLayer_Main->getPagePad(), visibleSize.height));
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        sprite->setTag(0);
        this->addChild(sprite, 0);
    }
    
    return true;
}

CPage* CPage::create(const char* _ImageName, CLayer_Main* _MainLayer)
{
    CPage *pRet = new(std::nothrow) CPage();
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
