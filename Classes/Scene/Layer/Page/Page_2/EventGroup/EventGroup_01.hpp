//
//  EventGroup_01.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef EventGroup_01_hpp
#define EventGroup_01_hpp

#include <stdio.h>
#include "EventGroup.hpp"

class CEventGroup_01 : public CEventGroup
{
  
public:
    virtual void initData() override;
    
    static CEventGroup_01* create(const char* _strSprite, const char* _LabelName, CVerticalLayer* _pPage, int _iPosY);
    
};
#endif /* EventGroup_01_hpp */
