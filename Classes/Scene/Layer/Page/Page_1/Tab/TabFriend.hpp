//
//  TabFriend.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef TabFriend_hpp
#define TabFriend_hpp

#include <stdio.h>
#include "TabBase.hpp"

class CTabFriend : public CTabBase
{

public:
    virtual void initData();
    virtual bool init(CPage_1* _pPage);
    static CTabFriend* create(CPage_1* _pPage);
    
    
};


#endif /* TabFriend_hpp */
