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

using namespace cocos2d;

class CEventGroup : public Layer
{
private:
    std::list<Sprite*> m_listSprite;
    
private:
    std::string m_strLabel;
    CVerticalLayer* m_pPage;
    Sprite* m_pTitle;
    Size m_tTitleSize;
    Size m_tItemSize;
    Vec2 m_vVisibleSize;
    Vec2 m_vLabelPos;
    Vec2 m_vItemLabelPos;
    Vec2 m_vPlusPos;
    int m_iTitlePosY;
    
    
public:
    int getFullHeight();
    void renewPosition(int _iTitlePos);
    void resetPosition();
    
private:
    void initData();
    void ItemCreate(Ref* _sender);
    
public:
    bool init(const char* _LabelName, CVerticalLayer* _pPage, int _iPosrY);
    static CEventGroup* create(const char* _LabelName, CVerticalLayer* _pPage, int _iPosY);
    
    
private:
    CEventGroup();
    ~CEventGroup();
};


#endif /* EventGroup_hpp */
