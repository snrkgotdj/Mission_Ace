//
//  ClanLayer.hpp
//  UIMaking
//
//  Created by cd-someone on 03/01/2019.
//

#ifndef ClanLayer_hpp
#define ClanLayer_hpp

#include <stdio.h>

class CTabClan;
class CClan;

using namespace cocos2d;

class CClanLayer : public Layer
{
private:
    CTabClan* m_pClan;
    CClan* m_pSelClan;
    Vec2 m_vStartPos;
    Size m_vSize;
    int m_iPad;
    int m_iClanCount;
    int m_iHeight;
    
public:
    bool isTouch(Event* _event);
    int getHeight() const {return m_iHeight;}
    const Vec2& getClanSize() const {return m_vSize;}
    const Vec2& getStartPos() const {return m_vStartPos;}
    CTabClan* getClanTab(){return m_pClan;}
    
public:
    bool onTouchBegan(Touch *touch, Event *unused_event) override { return true; };
    void onTouchMoved(Touch *touch, Event *unused_event) override;
    void onTouchEnded(Touch *touch, Event *unused_event) override;
    
public:
    bool init(CTabClan* _pClan);
    static CClanLayer* create(CTabClan* _pClan);
    
private:
    CClanLayer();
    ~CClanLayer();
};

#endif /* ClanLayer_hpp */
