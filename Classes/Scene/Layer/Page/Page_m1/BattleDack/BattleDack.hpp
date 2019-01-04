//
//  BattleDack.hpp
//  UIMaking-mobile
//
//  Created by cd-someone on 28/12/2018.
//

#ifndef BattleDack_hpp
#define BattleDack_hpp

#define CARD_USE_TAG 10

#include <stdio.h>

using namespace cocos2d;
using namespace std;

class CPage_m1;
class CDack;
class CCard;
class CCardUse;

class CBattleDack : public Layer
{
    friend class CCard;
    friend class CCardUse;
    friend class CDack;
private:
    CPage_m1* m_pPage;
    CDack* m_pDack;
    std::list<CCard*> m_listCard;
    CCard* m_pSelCard;
    CCard* m_pChangeCard;
    Menu* m_pEdit;
    
private:
    int m_iFirstCardCount;
    Vec2 m_vCardStartPos;
    Vec2 m_vCardPad;
    Vec2 m_vCardSize;
    int m_iLastRow;
    int m_iLastColum;
    int m_iHeight;
    
public:
    void setChangeCard(CCard* _pCard){ m_pChangeCard = _pCard;}
    void setDacktoCard(CCard* _pCard);
    
public:
    int getLastColum() const {return m_iLastColum;}
    int getHeight() const {return m_iHeight;}
    CCard* getChangeCard(){return m_pChangeCard;}
    CDack* getDack() const {return m_pDack;}
    CPage_m1* getPage() const {return m_pPage;}
    
public:
    void subtractCard(CCard* _pCard);
    
public:
    void mouseTouch(Event* _event);
    
private:
    void OnMouseMove(Event* _event);
    void OnMouseUp(Event* _event);
    void plusCard_1(Ref* _sender);
    void plusCard_3(Ref* _sender);
    
private:
    void disableCard(CCard* _except);
    void enableCard(CCard* _pCard = nullptr);
    void moveCard(CCard* _pCard);
    void lookAtUseCard(CCardUse* _pCard);
    void createCard();
    void createEditor();
    void createCardUse();
    void renewCardPos();
    
    
public:
    bool init(CPage_m1* _pPage);
    static CBattleDack* create(CPage_m1* _pPage);
    
    
private:
    CBattleDack();
    ~CBattleDack();
};


#endif /* BattleDack_hpp */
