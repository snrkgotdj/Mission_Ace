//
//  Layer_2.hpp
//  UIMaking
//
//  Created by cd-someone on 20/12/2018.
//

#ifndef Page_hpp
#define Page_hpp

#include <stdio.h>

class CLayer_Main;

using namespace cocos2d;

class CPage : public Layer
{
protected:
    CLayer_Main* m_pLayer_Main;
    Sprite* m_pBGSprite;
    const char* m_pBGName;
    bool m_bVerticalMove;
    
public:
    const char*     getBGName() { return m_pBGName; }
    CLayer_Main*    getMainLayer() { return m_pLayer_Main; }
    Sprite*         getBGSprite(){ return m_pBGSprite; }
    
public:
    virtual void mouseTouch(Event* _event) {};
    virtual void VerticalMove(const Vec2& _vDiff) {};
    virtual void VerticalMoveUp() {};
    bool checkVertical(const Vec2& _vMousePos);
    bool checkTouch(const Vec2& _vMousePos);
    
public:
    virtual bool init(const char* _ImageName, CLayer_Main* _MainLayer);
    static CPage* create(const char* _ImageName, CLayer_Main* _MainLayer);
    
protected:
    CPage();
    virtual ~CPage();
};



#endif /* Layer_2_hpp */
