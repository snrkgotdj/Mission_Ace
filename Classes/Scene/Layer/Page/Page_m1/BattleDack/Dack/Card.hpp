//
//  Card.hpp
//  UIMaking
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>

using namespace cocos2d;
using namespace std;

class CBattleDack;

enum CARD_STATE
{
    CARD_DISABLE,
    CARD_ENABLE,
    CARD_WAVE_LEFT,
    CARD_WAVE_RIGHT,
    CARD_SIZE_DOWN,
    CARD_SIZE_ORIGIN,
    
    CARD_END,
};

class CCard : public Sprite
{
private:
    CBattleDack* m_pBattleDack;
    std::string m_strName;
    CCard* m_pCardSel;
    
private:
    CARD_STATE m_eCardState;
    Vec2 m_vBeforePos;
    Size m_tSize;
    int m_iCost;
    int m_iRow;
    int m_iCol;
    int m_iOpacity;
    float m_fSizeUpScale;
    
    bool m_bLeft;
    bool m_bDack;
    
    
public:
    void setRowCol(int _iRow, int _iCol) {m_iRow = _iRow; m_iCol = _iCol;}
    void setState(CARD_STATE _eState);
    void setRowCol(int _iIdx){m_iRow = _iIdx % 4; m_iCol = _iIdx / 4;}
    void setDack(bool _bIsDack) {m_bDack = _bIsDack;}
    
public:
    const int getCost() const { return m_iCost; }
    const Vec2& getBeforePos() const { return m_vBeforePos; }
    int getIdx(){return ((m_iCol * 4) + m_iRow);}
    CBattleDack* getBattleDack(){return m_pBattleDack;}
    
public:
    bool isDack() {return m_bDack;}
    void createCardUse();
    void disable();
    void enable();
    void enableTouch();
    void returnCard();
    
private:
    void update(float _fDelta);
    void OnMouseTouch(Event* _event);
    void OnMouseMove(Event* _event);
    void OnMouseUp(Event* _event);
    
    void cardDisable(float _fDelta);
    void cardEnable(float _fDelta);
    void cardWave(float _fDelta);
    void cardSizeDown(float _fDelta);
    void cardSizeOrigin(float _fDelta);
    void cardEnd();
    
private:
    void checkChange(float _fDelta);
    
    
protected:
    void initData();
    
public:
    bool init(CBattleDack* _pBattleDack);
    static CCard* create(CBattleDack* _pBattleDack);
    
private:
    CCard();
    ~CCard();
};


#endif /* Card_hpp */
