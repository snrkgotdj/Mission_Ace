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
    , m_pBGSprite(nullptr)
    , m_bVerticalMove(false)
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
        m_pBGSprite = Sprite::create(_ImageName);
        m_pBGSprite->setContentSize(Size(visibleSize.width + m_pLayer_Main->getPagePad(), visibleSize.height));
        m_pBGSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        m_pBGSprite->setTag(0);
        this->addChild(m_pBGSprite, 0);
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

bool CPage::checkVertical(Vec2 _vMousePos)
{
    if(false == m_bVerticalMove)
        return false;
    
    Rect rect = m_pBGSprite->getBoundingBox();
    rect.origin.x += getPositionX() + m_pLayer_Main->getPositionX();
    m_pLayer_Main->setVerticalPage(this);
    
    return rect.containsPoint(_vMousePos);
}
