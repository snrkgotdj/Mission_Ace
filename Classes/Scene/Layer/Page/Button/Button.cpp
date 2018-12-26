//
//  Button.cpp
//  UIMaking
//
//  Created by cd-someone on 24/12/2018.
//

#include "Button.hpp"

CButton::CButton()
{}

CButton::~CButton()
{}

bool CButton::init()
{
        
    
    return true;
}

CButton* CButton::create(const char* _strSprite)
{
    CButton *pRet = new(std::nothrow) CButton();
    if (pRet && pRet->initWithFile(_strSprite) && pRet->init())
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
