//
//  TabButton.hpp
//  UIMaking
//
//  Created by cd-someone on 03/01/2019.
//

#ifndef TabButton_hpp
#define TabButton_hpp

#include <stdio.h>

enum BUTTON_TYPE
{
    BUTTON_CLAN,
    BUTTON_SOCIETY,
    BUTTON_FRIEND,
    
    BUTTON_END
};

class CPage_1;
class CButton;
class CTabBase;
using namespace cocos2d;

class CTabButton : public Layer
{
private:
    CPage_1* m_pPage;
    CButton* m_arrButton[BUTTON_END];
    
public:
    bool isMouseOn(Event* _event);
    void setTab(BUTTON_TYPE _eType, CTabBase* _pTab);
    
private:
    void onButton(int _iButton);
    
public:
    bool init(CPage_1* _pPage);
    static CTabButton* create(CPage_1* _pPage);
    
private:
    CTabButton();
    ~CTabButton();
};

#endif /* TabButton_hpp */
