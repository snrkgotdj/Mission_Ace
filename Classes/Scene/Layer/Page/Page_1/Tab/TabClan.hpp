//
//  TabClan.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef TabClan_hpp
#define TabClan_hpp

#include <stdio.h>
#include "TabBase.hpp"

class CTabClan : public CTabBase
{
    
public:
    virtual void initData();
    virtual bool init(CPage_1* _pPage);
    static CTabClan* create(CPage_1* _pPage);
    
    
};



#endif /* TabClan_hpp */
