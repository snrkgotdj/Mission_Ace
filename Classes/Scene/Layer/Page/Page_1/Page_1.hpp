//
//  Page_1.hpp
//  UIMaking-mobile
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef Page_1_hpp
#define Page_1_hpp

#include <stdio.h>
#include "Page.hpp"

class CTabBase;
class CTabButton;

using namespace cocos2d;
class CPage_1 : public CPage
{
private:
    CTabButton* m_pTabButton;
    Vector<CTabBase*> m_vecTabBase;
    CTabBase* m_pCurTab;
    
public:
    void setCurTab(CTabBase* _pTab) {m_pCurTab = _pTab;}
    virtual void VerticalMove(const Vec2& _vDiff) override;
    virtual void VerticalMoveUp() override;
    
public:
    virtual void mouseTouch(Event* _event) override;
    
public:
    virtual bool init(const char* _ImageName, CLayer_Main* _MainLayer) override;
    static CPage_1* create(const char* _ImageName, CLayer_Main* _MainLayer);
    
protected:
    CPage_1();
    virtual ~CPage_1();
};

#endif /* Page_1_hpp */
