//
//  Card_Use.hpp
//  UIMaking
//
//  Created by cd-someone on 03/01/2019.
//

#ifndef Card_Use_hpp
#define Card_Use_hpp

#include <stdio.h>

class CCard;

enum USE_STATE
{
    USE_SCALE_DOWN,
    USE_SCALE_ORIGIN,
    
    USE_END
};

using namespace cocos2d;

class CCardUse : public Sprite
{
private:
    CCard* m_pCard;
    Sprite* m_pUseButton;
    USE_STATE m_eState;
    
private:
    Sprite* m_bClickButton;
    
private:
    void update(float _fDelta) override;
    void OnMouseTouch(Event* _event);
    void OnMouseMove(Event* _event);
    void OnMouseUp(Event* _event);
    
    void buttonScaleDown(float _fDelta);
    void buttonScaleOrigin(float _fDelta);
    
    
public:
    bool init(CCard* _pCard);
    static CCardUse* create(CCard* _pCard);
    
    
private:
    CCardUse();
    ~CCardUse();
    
    
};

#endif /* Card_Use_hpp */
