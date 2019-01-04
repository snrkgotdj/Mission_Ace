//
//  Clan.hpp
//  UIMaking
//
//  Created by cd-someone on 04/01/2019.
//

#ifndef Clan_hpp
#define Clan_hpp

#include <stdio.h>

enum CLAN_STATE
{
    CLAN_CLICK_ENTER,
    CLAN_CLICK_MOVE,
    CLAN_CLICK_END,
    
    CLAN_END
};

using namespace cocos2d;
using namespace std;

class CClan : public Sprite
{
private:
    CLAN_STATE m_eState;
    string m_strLabelName;
    
private:
    void update(float _fDelta);
    
    void clickEnter(float _fDelta);
    void clickMove(float _fDelta);
    void clickEnd(float _fDelta);
    
    void scaleOrigin(float _fDelta);
    
public:
    void setState(CLAN_STATE _eState);
    Label* setLabel(const string& _strLabel, const Vec2& _vPos);
    void setClanLabel(int _iCount);
    void setScoreLabel();
    
public:
    bool init();
    static CClan* create(const string& _strImage);
    
    
private:
    CClan();
    ~CClan();
};
#endif /* Clan_hpp */
