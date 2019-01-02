//
//  Dack.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef Dack_hpp
#define Dack_hpp

#include <stdio.h>

using namespace cocos2d;

class CBattleDack;
class CCard;

class CDack : public Layer
{
private:
    CBattleDack* m_pBattleDack;
    Sprite* m_pPannel;
    CCard* m_arrCard[8];
    
private:
    Vec2 m_vVisible;
    Vec2 m_vDackPos;
    Vec2 m_vCardStartPos;
    Vec2 m_vCardPad;
    
public:
    Vec2 getPannelSize() const {return m_pPannel->getContentSize();}
    const Vec2& getDackPos() const {return m_vDackPos;}
    
public:
    bool isMouseOn(Event* _event);
    
private:
    void createCard();
    
protected:
    void initData();
    
public:
    bool init(CBattleDack* _pBattleDack);
    static CDack* create(CBattleDack* _pBattleDack);
    
private:
    CDack();
    ~CDack();
};

#endif /* Dack_hpp */
