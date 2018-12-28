//
//  EventIcon_01.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef EventIcon_01_hpp
#define EventIcon_01_hpp

#include <stdio.h>
#include "EventIcon.hpp"

class CEventIcon_01 : public CEventIcon
{
public:
    virtual void initData() override;
    
    static CEventIcon_01* create(const std::string& _strFile, CEventGroup* _pEventGroup);
    
};


#endif /* EventIcon_01_hpp */
