//
//  CProfile.hpp
//  UIMaking
//
//  Created by cd-someone on 26/12/2018.
//

#ifndef Profile_hpp
#define Profile_hpp

#include <stdio.h>

class CButton;

using namespace cocos2d;

class CProfile : public Layer
{
private:
    CButton* m_pButton;
    CButton* m_pMid;
    CButton* m_pSetting;
    
public:
    virtual bool init();
    CREATE_FUNC(CProfile);
    
private:
    CProfile();
    ~CProfile();
};

#endif /* CProfile_hpp */
