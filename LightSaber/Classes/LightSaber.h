//
//  LightSaber.h
//  LightSaber
//
//  Created by saiy2k on 24/06/13.
//
//

#ifndef __LightSaber__LightSaber__
#define __LightSaber__LightSaber__

#include "cocos2d.h"

using namespace cocos2d;

class LightSaber : public CCLayer {
public:
    
    
    // MEMBER VARIABLES
    // ****************
    
    CCSprite                        *textureSprite;
    
    CCArray                         *saberArray;
    
    int                             strength;
    
    
    
    // MEMBER FUNCTIONS
    // ****************
    
    // to create a single light saber
    void                            createSabers();
    
    // to update all the light sabers in `saberArray`
    // to stretch between the given 2 points
    void                            updateSabers(CCArray *systems,
                                                 CCPoint startPoint,
                                                 CCPoint endPoint);
    
    void                            removeSabers();
    
    
    
    // TOUCH OVERRIDES
    // ***************
    
    virtual bool                    ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void                    ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void                    ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void                    ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void                            registerWithTouchDispatcher();
    
    
    
    // OBJECT LIFE CYCLE
    // *****************
    
    virtual bool                    init();
    
    CREATE_FUNC(LightSaber);
    
    ~LightSaber();
    
};

#endif /* defined(__LightSaber__LightSaber__) */
