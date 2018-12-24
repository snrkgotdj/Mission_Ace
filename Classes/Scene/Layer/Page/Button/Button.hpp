//
//  Button.hpp
//  UIMaking
//
//  Created by cd-someone on 24/12/2018.
//

#ifndef CButton_hpp
#define CButton_hpp

#include <stdio.h>

using namespace cocos2d;

class CButton : public Sprite
{
    
    
public:
    virtual bool init();
    CREATE_FUNC(CButton);
    
private:
    CButton();
    ~CButton();
};



#endif /* Button_hpp */
