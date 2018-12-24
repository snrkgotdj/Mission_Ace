//
//  Layer_2.hpp
//  UIMaking
//
//  Created by cd-someone on 20/12/2018.
//

#ifndef Page_hpp
#define Page_hpp

#include <stdio.h>

class CLayer_Main;

using namespace cocos2d;

class CPage : public Layer
{
private:
    CLayer_Main* m_pLayer_Main;
    const char* m_pBGName;
    
    
public:
    const char* getBGName(){return m_pBGName;}
    
public:
    virtual bool init(const char* _ImageName, CLayer_Main* _MainLayer);
    static CPage* create(const char* _ImageName, CLayer_Main* _MainLayer);
    
private:
    CPage();
    ~CPage();
};



#endif /* Layer_2_hpp */
