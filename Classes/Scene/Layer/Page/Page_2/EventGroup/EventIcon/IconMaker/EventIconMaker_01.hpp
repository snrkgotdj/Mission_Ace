//
//  EventIconMaker_01.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef EventIconMaker_01_hpp
#define EventIconMaker_01_hpp

#include <stdio.h>
#include "EventIconMaker.hpp"

class CEventIcon;

class CEventIconMaker_01 : public CEventIconMaker
{
public:
    virtual CEventIcon* create(const std::string& _strFile, CEventGroup* _pEventGroup) override;
    
    
public:
    CEventIconMaker_01();
    ~CEventIconMaker_01();
};

#endif /* EventIconMaker_01_hpp */
