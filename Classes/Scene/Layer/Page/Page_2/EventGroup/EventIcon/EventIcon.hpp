//
//  EventIcon.hpp
//  UIMaking-mobile
//
//  Created by cd-someone on 27/12/2018.
//

#ifndef EventIcon_hpp
#define EventIcon_hpp

#include <stdio.h>
#include "EventGroup.hpp"

using namespace cocos2d;

class CEventIcon : public Sprite
{
    
protected:
    CEventGroup* m_pEventGroup;
    ICON_TOUCH m_eIcon;
    Vec2 m_vDefaultSize;
    Vec2 m_vMoneyPos;
    Vec2 m_vBookPos;
    Vec2 m_vCrystalPos;
    
    float m_fMinimumRatio;
    
private:
    void update(float _fDelta);
    
private:
    void iconScaleDown(float _fDelta);
    void iconScaleUp(float _fDelta);
    
    void createItem(const char* _strSprite, Vec2 _vPos, int _iData = -1);
    void createCrystal(const char* _strSprite, Vec2 _vPos, int _iData = -1);
    
public:
    void setDefaultSize(const Vec2& _vSize){ m_vDefaultSize = _vSize; }
    
public:
    void touchMouse();
    void moveMouse();
    void upMouse();
    virtual void initData();
    
    bool init(CEventGroup* _pEventGroup);
    static CEventIcon* create(const std::string& _strFile, CEventGroup* _pEventGroup);
    
protected:
    CEventIcon();
    ~CEventIcon();
};


#endif /* EventIcon_hpp */
