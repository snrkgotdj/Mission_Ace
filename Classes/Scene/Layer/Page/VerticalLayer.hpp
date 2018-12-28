//
//  VerticleLayer.hpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#ifndef VerticleLayer_hpp
#define VerticleLayer_hpp

#include <stdio.h>

class CEventGroup;
class CPage;

using namespace cocos2d;

class CVerticalLayer : public LayerColor
{
private:
    CPage* m_pPage;
    
private:
    Vector<CEventGroup*> m_vecEventgroup;
    CEventGroup* m_pCurSelGroup;
    Vec2 m_vVisibleSize;
    Vec2 m_vMouseDiff;
    bool m_bMouseMove;
    int m_iNextEventY;
    int m_iFirstEventY;
    int m_iEvnetNumber;
    float ScrollSpeed;
    
public:
    CPage* getPage() { return m_pPage; }
    void addHeight(int _height);
    void renewPosition();
    
public:
    virtual bool init(CPage* _pLayer);
    static CVerticalLayer* create(CPage* _pPage);
    void plusEventGroup(Ref* _sender);
    void mouseTouch(Event* _event);
    void VerticalMove(const Vec2& _vDiff);
    void VerticalMoveUp();
    
private:
    void update(float delta);
    void OnMouseMove(Event* _event);
    void OnMouseUp(Event* _event);
    
private:
    CVerticalLayer();
    ~CVerticalLayer();
};

#endif /* VerticleLayer_hpp */
