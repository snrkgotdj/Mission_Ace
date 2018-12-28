//
//  PopupPage.hpp
//  UIMaking
//
//  Created by cd-someone on 27/12/2018.
//

#ifndef PopupPage_hpp
#define PopupPage_hpp

#include <stdio.h>

class CPage;

using namespace cocos2d;

class CPopupPage : public Layer
{
private:
    Sprite* m_pSprite;
    CPage* m_pPage;
    
public:
    virtual bool onTouchBegan(Touch* touch, Event* event);
    bool init(const char* _string, CPage* _pPage);
    static CPopupPage* create(const char* _string, CPage* _pPage);
    
private:
    CPopupPage();
    ~CPopupPage();
};

#endif /* PopupPage_hpp */
