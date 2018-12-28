//
//  EventGroup.hpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#ifndef EventGroup_hpp
#define EventGroup_hpp

#include <stdio.h>

class CPage_2;
class CVerticalLayer;
class CEventIcon;
class CEventIconMaker;

using namespace cocos2d;

enum ICON_TOUCH
{
    ICON_SCALEDOWN,
    ICON_SCALEUP,
    
    ICON_END
};

class CEventGroup : public Layer
{
protected:
    std::string m_strLabel;
    CVerticalLayer* m_pPage;
    std::list<CEventIcon*> m_listIcon;
    CEventIconMaker* m_pEventIconMaker;
    CEventIcon* m_pCurIcon;
    std::string m_pIconName;
    
protected:
    Sprite* m_pTitle;
    Size m_tTitleSize;
    Size m_tItemSize;
    Vec2 m_vVisibleSize;
    Vec2 m_vLabelPos;
    Vec2 m_vItemLabelPos;
    Vec2 m_vPlusPos;
    int m_iTitlePosY;
    
    
public:
    void setTitleSizeY(float _fSizeY) { m_tTitleSize.height = _fSizeY; m_pTitle->setContentSize(m_tTitleSize);}
    void setIconSize(Vec2 _vSize) { m_tItemSize = _vSize;}
    void setIconSizeY(float _fSize) { m_tItemSize.height = _fSize;}
    void setIconName(const char* _strName) {m_pIconName = _strName;} 
public:
    int getFullHeight();
    CVerticalLayer* getLayer() { return m_pPage; };
    
public:
    void renewPosition(int _iTitlePos);
    void resetPosition();
    bool mouseTouch(Event* _event);
    bool mouseMove();
    bool mouseUp();
    bool isMouseOn(Event* _event);
    
private:
    void ItemCreate(Ref* _sender);
    
public:
    virtual void initData();
    
public:
    bool init(const char* _strSprite, const char* _LabelName, CVerticalLayer* _pPage, int _iPosrY);
    static CEventGroup* create(const char* _strSprite, const char* _LabelName, CVerticalLayer* _pPage, int _iPosY);
    
    
protected:
    CEventGroup();
    virtual ~CEventGroup();
};


#endif /* EventGroup_hpp */
