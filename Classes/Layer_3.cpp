//
//  Layer_3.cpp
//  UIMaking
//
//  Created by cd-someone on 19/12/2018.
//

#include "Layer_3.hpp"

using namespace cocos2d;

CLayer_3::CLayer_3()
{
    
}

CLayer_3::~CLayer_3()
{
    
}

bool CLayer_3::init()
{
    if(!Layer::init())
        return false;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = Sprite::create("Neco_Main.jpeg");
    sprite->setContentSize(Size(visibleSize.width + 50, visibleSize.height));
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    this->addChild(sprite, 0);
    return true;
}
