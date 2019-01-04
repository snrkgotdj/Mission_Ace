//
//  ItemBox.hpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#ifndef ItemBox_hpp
#define ItemBox_hpp

#include <stdio.h>

using namespace cocos2d;
using namespace std;

enum ITEM_STATE
{
    ITEM_DOWN,
    ITEM_ORIGIN,
    
    ITEM_END,
    
};

class CItemBox : public Sprite
{
private:
    ITEM_STATE m_eState;
    bool m_bMouseOn;
    
private:
    void update(float _fDelta);
    void OnMouseMove(Event* _event);
    void OnMouseUp(Event* _event);
    
    void itemDown(float _fDelta);
    void itemOrigin(float _fDelta);
    
public:
    bool mouseTouch(Event* _event);
    
public:
    bool init();
    static CItemBox* create(const string& _strImage);
    
private:
    CItemBox();
    ~CItemBox();
};


#endif /* ItemBox_hpp */
