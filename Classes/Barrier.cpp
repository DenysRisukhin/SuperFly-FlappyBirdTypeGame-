//
//  Barrier.cpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/28/17.
//
//

#include "Barrier.hpp"
#include "Constants.h"
#include "GameManager.hpp"

USING_NS_CC;

Barrier* Barrier::createWithFileName(std::string fileName){
    auto sprite = new Barrier;
    if (sprite && sprite->initWithFile(fileName)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Barrier::Initialise(const float speed, const float width){
    _speed = speed;
    _screenWidth = width;
    _xOffSet = this->getBoundingBox().size.width;
    state = kBarrierStateInActive;
    scored = false;
}

void Barrier::start(){
    this->stopAllActions();
    this->setVisible(true);
  
    float distance = _xOffSet + _screenWidth + _xOffSet;
    float time = distance / _speed;
    
    log("time= %f ", time);
    
    Vec2 destination = Vec2(-_xOffSet, this->getPositionY());
    
    this->setPosition(Vec2(_xOffSet + _screenWidth, this->getPositionY() ));
    
    state = kBarrierStateActive;
    
    MoveTo *actionMove = MoveTo::create(time, destination);
    CallFunc *actionMoveDone = CallFunc::create(CC_CALLBACK_0(Barrier::reachedDestination, this));
    this->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void Barrier::stop(){
    this->setVisible(false);
    
    state = kBarrierStateInActive;
    
    this->setPosition(Vec2(kBarrierStateInActiveX, this->getPositionY() ));
    scored = false;
}

void Barrier::reachedDestination(){
    this->stop();
}

void Barrier::setPair(Barrier* br){
    pairBarrier = br;
    br->pairBarrier = this;
}

void Barrier::changeSpeed(float speed){
    _speed = speed;
    
    this->stopAllActions();
    
    float distance = _xOffSet + this->getPositionX();
    float time = distance / _speed;
    
    log("time(%f) =  distance(%f) / _speed(%f)", time, distance, _speed);
    
    Vec2 destination = Vec2(-_xOffSet, this->getPositionY());
    
    MoveTo *actionMove = MoveTo::create(time, destination);
    CallFunc *actionMoveDone = CallFunc::create(CC_CALLBACK_0(Barrier::reachedDestination, this));
    this->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

