//
//  TabClan.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef TabClan_hpp
#define TabClan_hpp

#include <stdio.h>
#include "TabBase.hpp"

class CClanLayer;


class CTabClan : public CTabBase
{
private:
    CClanLayer* m_pClanLayer;
    Vec2 m_vMouseDiff;
    bool m_bMouseMove;
    
public:
    virtual void initData();
    virtual bool init(CPage_1* _pPage);
    static CTabClan* create(CPage_1* _pPage);
    virtual void VerticalMove(const Vec2& _vDiff);
    virtual void VerticalMoveUp();
    
private:
    CTabClan();
    ~CTabClan();
};



#endif /* TabClan_hpp */
