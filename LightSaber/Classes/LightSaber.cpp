//
//  LightSaber.cpp
//  LightSaber
//
//  Created by saiy2k on 24/06/13.
//
//

#include "LightSaber.h"

void LightSaber::createSabers() {
    CCParticleSystem                *saber;
    
    textureSprite               =   CCSprite::create("swipeParticle.png");
    textureSprite->retain();
    
    for (int i = 0; i < strength; i++) {
        
        saber                      =   CCParticleSun::create();
        saber->setTexture(textureSprite->getTexture());
        saber->setAutoRemoveOnFinish(true);
        saber->setEmissionRate(2000);
        saber->setLife(0.06);
        saber->setLifeVar(0.01);
        saber->setSpeed(0.0);
        saber->setSpeedVar(0.0);
        saber->setStartColor(ccc4f(0.2, 0.2, 0.9, 0.9));
        saber->setEndColor(ccc4f(0.1, 0.1, 0.9, 0.5));
        saber->setStartSize(16.0);
        saber->setStartSizeVar(2.0);
        saber->setEndSize(8.0);
        saber->setEndSizeVar(2.0);
        saber->setBlendAdditive(true);
        saber->setPosition( ccp(2020, 2020) );
        saberArray->addObject(saber);
        this->addChild(saber);
    }
    
    textureSprite->release();
    
}

void LightSaber::updateSabers(CCArray *systems, CCPoint startPoint, CCPoint endPoint) {
    float                           dist;
    CCPoint                         velocity;
    CCPoint                         delta, offset, final;
    CCPoint                         centerPoint;
    CCParticleSystem                *saber;
    float                           ang;
    
    delta                       =   ccpSub(endPoint, startPoint);
    centerPoint                 =   ccpAdd(ccpMult(delta, 0.5), startPoint);
    ang                         =   atan2f(delta.y, delta.x) * 180 / 3.14;
    dist                        =   ccpDistance(startPoint, endPoint);
    
    for (int i = 0; i < systems->count(); i++) {
        saber           =   (CCParticleSystem *)systems->objectAtIndex(i);
        saber->setPosition( centerPoint );
        saber->setPosVar( ccp(0, dist * 0.5) );
        saber->setRotation(90 - ang);
    }
}

void LightSaber::removeSabers() {
    
    CCObject                        *obj;
    CCParticleSystem                *particleSys;
    
    CCARRAY_FOREACH(saberArray, obj) {
        particleSys             =   (CCParticleSystem *)obj;
        particleSys->stopSystem();
        particleSys->setAutoRemoveOnFinish(true);
    }
    
}

#pragma mark -
#pragma mark TOUCH OVERRIDES

bool LightSaber::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    
    this->createSabers();
    
    return                          true;
    
}

void LightSaber::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint                         point;

    point                       =   pTouch->getLocation();
    this->updateSabers(saberArray, point, ccpAdd(point, ccp(-40, 100)));
}

void LightSaber::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    
    this->removeSabers();
    
}

void LightSaber::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {
    
}

void LightSaber::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, true);
}

#pragma mark -
#pragma mark OBJECT LIFE CYCLE

bool LightSaber::init() {
    
    if ( !CCLayer::init() ) {
        return                      false;
    }
    
    this->setTouchEnabled(true);
    
    strength                    =   8;
    
    saberArray                  =   CCArray::create();
    saberArray->retain();
    
    return                          true;
    
}

LightSaber::~LightSaber() {
    saberArray->release();
}
