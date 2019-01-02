//
//  Page_-1.hpp
//  UIMaking-mobile
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef Page_m1_hpp
#define Page_m1_hpp

#include <stdio.h>
#include "Page.hpp"

class CBattleDack;

using namespace cocos2d;

class CPage_m1 : public CPage
{
private:
    CBattleDack* m_pBattleDack;
    Vec2 m_vMouseDiff;
    bool m_bMove;
    
private:
    void update(float delta);
    
public:
    virtual void mouseTouch(Event* _event) override;
    virtual void VerticalMove(const Vec2& _vDiff) override;
    virtual void VerticalMoveUp() override;
    virtual bool init(const char* _ImageName, CLayer_Main* _MainLayer) override;
    static CPage_m1* create(const char* _ImageName, CLayer_Main* _MainLayer);
    
private:
    CPage_m1();
    ~CPage_m1();
};

#endif /* Page__1_hpp */
