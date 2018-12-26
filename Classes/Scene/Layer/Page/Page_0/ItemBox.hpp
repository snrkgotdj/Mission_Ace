//
//  ItemBox.hpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#ifndef ItemBox_hpp
#define ItemBox_hpp

#include <stdio.h>

class CButton;

using namespace cocos2d;

class CItemBox : public Layer
{
private:
    Vector<CButton*> m_vecButton;
    
public:
    virtual bool init() override;
    CREATE_FUNC(CItemBox);
    
private:
    CItemBox();
    ~CItemBox();
};


#endif /* ItemBox_hpp */
