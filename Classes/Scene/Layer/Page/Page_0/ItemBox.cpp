//
//  ItemBox.cpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#include "ItemBox.hpp"
#include "Button.hpp"

CItemBox::CItemBox()
{
    m_vecButton.reserve(4);
}

CItemBox::~CItemBox()
{
    
}

bool CItemBox::init()
{
    if(!Layer::init())
        return false;
    
    
    
    return true;
}

