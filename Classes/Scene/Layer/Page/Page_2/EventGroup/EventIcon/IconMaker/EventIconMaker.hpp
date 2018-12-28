//
//  EventIconMaker.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef EventIconMaker_hpp
#define EventIconMaker_hpp

#include <stdio.h>

class CEventIcon;
class CEventGroup;

class CEventIconMaker
{
public:
    virtual CEventIcon* create(const std::string& _strFile, CEventGroup* _pEventGroup);
    
public:
    CEventIconMaker();
    virtual ~CEventIconMaker();
};


#endif /* EventIconMaker_hpp */
