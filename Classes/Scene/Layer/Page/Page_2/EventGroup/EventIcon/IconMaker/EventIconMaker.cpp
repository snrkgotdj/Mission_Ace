//
//  EventIconMaker.cpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#include "EventIconMaker.hpp"
#include "EventIcon.hpp"

using namespace cocos2d;

CEventIconMaker::CEventIconMaker()
{
    
}

CEventIconMaker::~CEventIconMaker()
{
    
}

CEventIcon* CEventIconMaker::create(const std::string& _strFile, CEventGroup* _pEventGroup)
{
    CEventIcon *sprite = CEventIcon::create(_strFile, _pEventGroup);

    return sprite;
}
