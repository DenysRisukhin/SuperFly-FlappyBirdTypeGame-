//
//  Cloud.cpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/28/17.
//
//

#include "Cloud.hpp"

USING_NS_CC;

Cloud* Cloud::createWithFileName(std::string fileName) {
    auto sprite = new Cloud;
    if (sprite && sprite->initWithFile(fileName)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Cloud::start() {
    this->stopAllActions();
    float currentX = this->getPositionX();
    float distance = currentX + _xOffSet;
    float time = distance / _speed;
    Vec2 destination = Vec2(-_xOffSet, this->getPositionY());
    
    MoveTo *actionMove = MoveTo::create(time, destination);
    CallFunc *actionMoveDone = CallFunc::create(CC_CALLBACK_0(Cloud::reachedDestination, this));
    this->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void Cloud::stop() {
    this->stopAllActions();
}

void Cloud::setSpeedAndWidth(const float speed, const float width) {
    _speed = speed;
    _screenWidth = width;
    _xOffSet = this->getBoundingBox().size.width;
}

void Cloud::reachedDestination() {
    this->setPositionX(_xOffSet + _screenWidth);
    this->start();
}
