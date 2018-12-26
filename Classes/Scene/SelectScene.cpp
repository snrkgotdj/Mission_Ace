#include "SelectScene.h"
#include "Layer_Main.hpp"
#include "Layer_Select.hpp"
#include "Layer_Base.hpp"

USING_NS_CC;

CSelectScene::CSelectScene()
{
    
}

CSelectScene::~CSelectScene()
{
    
}


Scene* CSelectScene::createScene()
{
    return CSelectScene::create();
}

bool CSelectScene::init()
{
    if ( !Scene::init() )
        return false;
    
    m_pMainLayer = CLayer_Main::create(this);
    m_pSelectLayer = CLayer_Select::create(m_pMainLayer);
    m_pMainLayer->setSelectLayer(m_pSelectLayer);
    
    m_pMainLayer->setTag(5);
    m_pSelectLayer->setTag(4);
    
    m_vecLayer.pushBack(m_pMainLayer);
    m_vecLayer.pushBack(m_pSelectLayer);
    
    MouseTouch();
    
    this->addChild(m_pMainLayer);
    this->addChild(m_pSelectLayer);
    
    return true;
}


void CSelectScene::MouseTouch()
{
    auto MouseEvent = EventListenerMouse::create();
    
    MouseEvent->onMouseDown = CC_CALLBACK_1(CSelectScene::OnMouseDown, this);
    MouseEvent->onMouseMove = CC_CALLBACK_1(CSelectScene::OnMouseMove, this);
    MouseEvent->onMouseUp = CC_CALLBACK_1(CSelectScene::OnMouseUp, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(MouseEvent, 2);
}

void CSelectScene::OnMouseDown(Event* _event)
{
    std::sort(m_vecLayer.begin(), m_vecLayer.end(), [](Node* _pLeft, Node* _pRight)->bool
    {return (_pLeft->getTag() < _pRight->getTag()); });

    for(int i = 0; i < m_vecLayer.size(); ++i)
    {
        if(m_vecLayer.at(i)->Touched(_event))
            return;
    }
}


void CSelectScene::OnMouseMove(Event* _event)
{
    
    
    
}

void CSelectScene::OnMouseUp(Event* _event)
{
    
    
}
