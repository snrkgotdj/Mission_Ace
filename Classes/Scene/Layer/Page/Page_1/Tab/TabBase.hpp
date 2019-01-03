//
//  TabBase.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef TabBase_hpp
#define TabBase_hpp

#include <stdio.h>

using namespace cocos2d;

class CPage_1;

class CTabBase : public Layer
{
protected:
    CPage_1* m_pPage;
    Sprite* m_pTab;
    
protected:
    std::string m_strTab;
    Vec2 m_vButtonPos;
    Vec2 m_vVisibleSize;
    Size m_tTabSize;
    Size m_tButtonSize;
    

public:
    CPage_1* getPage(){return m_pPage;}
    void setTabOn();
    
public:
    bool init(CPage_1* _pPage);
    
    virtual void initData();
    virtual bool isTouch(Event* _event);
    virtual void VerticalMove(const Vec2& _vDiff) {};
    virtual void VerticalMoveUp() {};
    
protected:
    CTabBase();
    virtual ~CTabBase();
};

#endif /* TabBase_hpp */
