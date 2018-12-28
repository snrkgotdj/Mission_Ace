//
//  CSelectLayer.hpp
//  UIMaking
//
//  Created by cd-someone on 20/12/2018.
//

#ifndef Layer_Select_hpp
#define Layer_Select_hpp

#include <stdio.h>
#include "Layer_Base.hpp"

class CLayer_Main;

using namespace cocos2d;

class CLayer_Select : public CLayer_Base
{
private:
    CLayer_Main* m_pLayer_Main;
    Size m_tVisibleSize;
    Size m_tSelectSize;
    Size m_tCurSelectSize;
    
public:
    const Size& getIconSize(){return m_tSelectSize;}
    const Size& getCurIconSize() {return m_tCurSelectSize;}
    
public:
    void changeCulSel(int _iBefore, int _iCul);
    
private:
    void createSelect();
    void createPannel();
    void setSpritePos(Sprite* _pSprite, int& iCount);
    
public:
    virtual bool Touched(Event* _event) override;
    virtual bool init(CLayer_Main* _MainLayer);
    static CLayer_Select* create(CLayer_Main* _MainLayer);
    
private:
    CLayer_Select();
    ~CLayer_Select();
};


#endif /* CSelectLayer_hpp */
