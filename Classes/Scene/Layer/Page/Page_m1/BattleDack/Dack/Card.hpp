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
    
    CARD_END,
};

class CCard : public Sprite
{
private:
    CBattleDack* m_pBattleDack;
    std::string m_strName;
    
private:
    CARD_STATE m_eCardState;
    int m_iCost;
    Size m_tSize;
    int m_iRow;
    int m_iCol;
    int m_iOpacity;
    
public:
    void setRowCol(int _iRow, int _iCol) {m_iRow = _iRow; m_iCol = _iCol;}
    
public:
    int getCost() { return m_iCost; }
    
public:
    void disAble();
    
private:
    void update(float _fDelta);
    
    void cardDisable(float _fDelta);
    
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
