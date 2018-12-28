//
//  EventIconMaker_01.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "EventIconMaker_01.hpp"
#include "EventIcon_01.hpp"

using namespace cocos2d;

CEventIconMaker_01::CEventIconMaker_01()
{
    
}

CEventIconMaker_01::~CEventIconMaker_01()
{
    
}

CEventIcon* CEventIconMaker_01::create(const std::string& _strFile, CEventGroup* _pEventGroup)
{
    CEventIcon_01 *sprite = CEventIcon_01::create(_strFile, _pEventGroup);
    
    return sprite;
}
