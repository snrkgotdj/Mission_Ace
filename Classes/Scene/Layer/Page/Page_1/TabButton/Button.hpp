//
//  Button.hpp
//  UIMaking
//
//  Created by cd-someone on 24/12/2018.
//

#ifndef CButton_hpp
#define CButton_hpp

#include <stdio.h>

class CTabBase;

using namespace cocos2d;

class CButton : public Node
{
private:
    CTabBase* m_pTab;
    Sprite* m_pOn;
    Sprite* m_pOff;
    
public:
    void setOff();
    void setOn();
    void setPosition(const Vec2& _vPos){ m_pOn->setPosition(_vPos); m_pOff->setPosition(_vPos);}
    void setContentSize(const Size& _vSize) { m_pOn->setContentSize(_vSize); m_pOff->setContentSize(_vSize);}
    void setTab(CTabBase* _pTab) {m_pTab = _pTab;}
    
public:
    bool mouseTouch(Event* _event);
    
public:
    virtual bool init(const char* _strOn, const char* _strOff);
    static CButton* create(const char* _strOn, const char* _strOff);

    
private:
    CButton();
    ~CButton();
};



#endif /* Button_hpp */
