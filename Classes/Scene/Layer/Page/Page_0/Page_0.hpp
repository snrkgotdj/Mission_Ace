//
//  Page_0.hpp
//  UIMaking
//
//  Created by cd-someone on 24/12/2018.
//

#ifndef Page_0_hpp
#define Page_0_hpp

#include <stdio.h>
#include "Page.hpp"

class CProfile;
class CItemBox;

using namespace cocos2d;

class CPage_0 : public CPage
{
private:
    Vector<CItemBox*> m_vecItem;
    
    
public:
    virtual void mouseTouch(Event* _event) override;
    virtual bool init(const char* _ImageName, CLayer_Main* _MainLayer) override;
    static CPage_0* create(const char* _ImageName, CLayer_Main* _MainLayer);
private:
    CPage_0();
    ~CPage_0();
};
#endif /* Page_0_hpp */
