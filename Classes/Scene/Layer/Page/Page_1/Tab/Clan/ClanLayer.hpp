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

using namespace cocos2d;

class CClanLayer : public Layer
{
private:
    CTabClan* m_pClan;
    Vec2 m_vStartPos;
    Size m_vSize;
    int m_iPad;
    int m_iClanCount;
    
public:
    bool init(CTabClan* _pClan);
    static CClanLayer* create(CTabClan* _pClan);
    
private:
    CClanLayer();
    ~CClanLayer();
};

#endif /* ClanLayer_hpp */
