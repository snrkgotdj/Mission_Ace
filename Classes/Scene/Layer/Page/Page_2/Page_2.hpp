//
//  Page_2.hpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#ifndef Page_2_hpp
#define Page_2_hpp

#include <stdio.h>
#include "Page.hpp"

class CEventGroup;
class CVerticalLayer;

using namespace cocos2d;

class CPage_2 : public CPage
{
private:
    CVerticalLayer* m_pLayer;

public:
    virtual void VerticalMove(const Vec2& _vDiff) override;
    virtual void VerticalMoveUp() override;
    
public:
    virtual bool init(const char* _ImageName, CLayer_Main* _MainLayer) override;
    static CPage_2* create(const char* _ImageName, CLayer_Main* _MainLayer);
    
private:
    CPage_2();
    ~CPage_2();
};


#endif /* Page_2_hpp */
