//
//  BaseLayer.hpp
//  UIMaking
//
//  Created by cd-someone on 24/12/2018.
//

#ifndef Layer_Base_hpp
#define Layer_Base_hpp

#include <stdio.h>

using namespace cocos2d;

class CLayer_Base : public Layer
{
public:
    virtual bool Touched(Event* _event) { return false; };
    
};



#endif /* BaseLayer_hpp */
