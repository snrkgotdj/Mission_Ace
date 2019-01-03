//
//  TabSociety.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef TabSociety_hpp
#define TabSociety_hpp

#include <stdio.h>
#include "TabBase.hpp"

class CTabSociety : public CTabBase
{
    
public:
    virtual void initData();
    virtual bool init(CPage_1* _pPage);
    static CTabSociety* create(CPage_1* _pPage);
    
    
};

#endif /* TabSociety_hpp */
