//
//  CSelectLayer.cpp
//  UIMaking
//
//  Created by cd-someone on 20/12/2018.
//

#include "Layer_Select.hpp"
#include "Layer_Main.hpp"
#include "Page.hpp"

using namespace cocos2d;

CLayer_Select::CLayer_Select()
    : m_tVisibleSize(Vec2(0, 0))
    , m_tSelectSize(Size(110, 110))
    , m_tCurSelectSize(Size(160, 160))
{
    
}

CLayer_Select::~CLayer_Select()
{
    
}

bool CLayer_Select::init(CLayer_Main* _MainLayer)
{
    if(nullptr == _MainLayer)
        return false;
    
    m_tVisibleSize = Director::getInstance()->getVisibleSize();
    m_pLayer_Main = _MainLayer;
    
    createSelect();
    
    createPannel();
    
    this->setPosition(Vec2(m_tVisibleSize.width * 0.5, 0));
    
    return true;
}

CLayer_Select* CLayer_Select::create(CLayer_Main *_MainLayer)
{
    CLayer_Select *pRet = new(std::nothrow) CLayer_Select();
    if (pRet && pRet->init(_MainLayer))
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

void CLayer_Select::setSpritePos(Sprite *_pSprite, int& _iCount)
{
    _pSprite->setPosition(Vec2(m_tSelectSize.width * _iCount, 0));
    _pSprite->setTag(_iCount);
    int iCurPageTag = m_pLayer_Main->getCurPageTag();
    int iPad = (m_tCurSelectSize.width - m_tSelectSize.width);
    
    if(_iCount == iCurPageTag)
    {
        _pSprite->setContentSize(m_tCurSelectSize);
    }
    
    else
    {
        if(_iCount < iCurPageTag)
        {
            _pSprite->setPosition(Vec2(m_tSelectSize.width * _iCount - iPad, 0));
        }
        
        else if(_iCount > iCurPageTag)
        {
            _pSprite->setPosition(Vec2(m_tSelectSize.width * _iCount + iPad, 0));
        }
        
        _pSprite->setContentSize(m_tSelectSize);
    }
    
    if( _iCount > 0)
    {
        _iCount = -_iCount;
    }
    else if( _iCount < 0)
    {            
        _iCount = 1 - _iCount;
    }
    else if(0 == _iCount)
    {
        ++_iCount;
    }
    
}

void CLayer_Select::createSelect()
{
    Vector<Node*>& vPage = m_pLayer_Main->getChildren();
    
    int iCount = 0;
    
    for(int i = 0; i < vPage.size(); ++i)
    {
        const char* pBGName =((CPage*)vPage.at(i))->getBGName();
        auto sprite = Sprite::create(pBGName);
        
        sprite->setAnchorPoint(Vec2(0.5, 0));
        setSpritePos(sprite, iCount);
        this->addChild(sprite);
    }
}

void CLayer_Select::createPannel()
{
    //Sprite* pSprite = Sprite::create("Pannel.png");
    //this->addChild(pSprite);
}

bool CLayer_Select::Touched(Event* _event)
{
    Vector<Node*>& vNode = getChildren();
    EventMouse* pMouse = (EventMouse*)_event;
    
    for(int i = 0; i < vNode.size(); ++i)
    {
        Sprite* pSprite = (Sprite*)vNode.at(i);
        Rect rect = pSprite->getBoundingBox();
        rect.origin.x += getPositionX();
        if(rect.containsPoint(Vec2(pMouse->getCursorX(), pMouse->getCursorY())))
        {
            CCLOG("Select Touch %d", pSprite->getTag());
            return true;
        }
    }
    
    return false;
}

void CLayer_Select::changeCulSel(int _iBefore, int _iCul)
{
    Sprite* Before = (Sprite*)getChildByTag(_iBefore);
    Sprite* Cul =(Sprite*)getChildByTag(_iCul);
    
    Before->setContentSize(m_tSelectSize);
    Cul->setContentSize(m_tCurSelectSize);
    
    Vector<Node*>& vPage = getChildren();
    
    int iCount = 0;
    for(int i = 0; i < vPage.size(); ++i)
    {
        Sprite* sprite = (Sprite*)vPage.at(i);
        sprite->setAnchorPoint(Vec2(0.5, 0));
        setSpritePos(sprite, iCount);
    }
}

