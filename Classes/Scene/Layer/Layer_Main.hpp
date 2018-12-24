//
//  CLayer_Main.hpp
//  UIMaking
//
//  Created by cd-someone on 19/12/2018.
//

#ifndef Layer_Main_hpp
#define Layer_Main_hpp

#include <stdio.h>
#include "SelectScene.h"
#include "Layer_Base.hpp"

using namespace cocos2d;

class CPage;
class CLayer_Select;

class CLayer_Main : public CLayer_Base
{
private:
    Scene* m_pScene;
    CLayer_Select* m_pSelectLayer;
    
    //위치 계산용 변수들
    Size m_tVisibleSize;
    Vec2 m_vCenterPos;
    Vec2 m_vOldMousePos;
    Vec2 m_vFirstMousePos;
    bool m_bMouseOn;
    float m_fPageChangeTime;
    int m_iPagePad;
    int m_iCurPageTag;
    int m_iNextPageTag;
    int m_iMaxPageTag;
    int m_iMinPageTag;
    int m_iCountPageTag;
    
   
public:
    void changeCulSel(int _iCulSel);
    void setScene(CSelectScene* _pScene) {m_pScene = _pScene;}
    void setSelectLayer(CLayer_Select* _pSelectLayer){m_pSelectLayer = _pSelectLayer;}
    bool addPage(CPage* _pPage);
    bool addPageLeft(CPage* _pPage);
    bool addPageRight(CPage* _pPage);
    
    
public:
    Vec2 getNextPagePos() const;
    const Vec2& getCenterPos() const {return m_vCenterPos;}
    const Size& getVisibleSize() const {return m_tVisibleSize;}
    const int getPagePad() const {return m_iPagePad;}
    const int getCurPageTag() const {return m_iCurPageTag;}
    
    
private:
    int addPageTag();
    void createPage();
    void OnMouseMove(Event* _event);
    void OnMouseUp(Event* _event);
    
public:
    virtual bool Touched(Event* _event);
    virtual bool init(Scene* _pScene);
    static CLayer_Main* create(Scene* _pScene);
    
    CLayer_Main();
    ~CLayer_Main();
};

#endif /* CLayer_Main_hpp */
