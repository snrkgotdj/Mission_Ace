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

class CVerticalLayer : public Layer
{
private:
    CPage* m_pPage;
    
private:
    Vector<CEventGroup*> m_vecEventgroup;
    int m_iNextEventY;
    int m_iFirstEventY;
    int m_iEvnetNumber;
    
public:
    void addHeight(int _height);
    void renewPosition();
    
public:
    virtual bool init(CPage* _pLayer);
    static CVerticalLayer* create(CPage* _pPage);
    void plusEventGroup(Ref* _sender);
    void VerticalMove(const Vec2& _vDiff);
    void VerticalMoveUp();
    
private:
    CVerticalLayer();
    ~CVerticalLayer();
};

#endif /* VerticleLayer_hpp */
