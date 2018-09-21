//
//  Player.cpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/28/17.
//
//

#include "Player.hpp"
#include "GameManager.hpp"
#include "Constants.h"

USING_NS_CC;

Player* Player::createWithFileName(std::string fileName) {
    auto sprite = new Player;
    if (sprite && sprite->initWithFile(fileName)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Player::update(float dt) {
    if (state == kPlayerStateMoving) {
        
        // s = ut + 0.5 * a * t * t
        // v = u + a * t
        
        float distance = 0;
        float newSpeed = 0;
        
        distance = _speedY * dt + 0.5 * GRAVITI * dt * dt;
        newSpeed = _speedY + GRAVITI * dt;
        
        this->setPositionY(this->getPositionY() + distance);
        _speedY = newSpeed;
        
        if(this->getPositionY() > _topOfScreen){
            this->setPositionY(_topOfScreen);
            _speedY = 0.0;
        }
    }
}

void Player::reset() {
    state = kPlayerStateStopped;
    setStartSpeed();
}

void Player::setStartSpeed() {
    _speedY = kPlayerStartSpeedY;
    
}

void Player::setTopOfTheScreen(const float tos) {
    _topOfScreen = tos;
}

cocos2d::Rect Player::TubeCollisionBox() {
//    return Rect(
//    this->getBoundingBox().origin.x + SCALEY(25) * GETSCALEFAC,
//    this->getBoundingBox().origin.y + SCALEY(5) * GETSCALEFAC,
//    this->getBoundingBox().size.width - SCALEY(35) * GETSCALEFAC,
//    this->getBoundingBox().size.height - SCALEY(15) * GETSCALEFAC
//    );
    
//    return Rect(
//                this->getBoundingBox().origin.x + 25,
//                this->getBoundingBox().origin.y + 5,
//                this->getBoundingBox().size.width - 35,
//                this->getBoundingBox().size.height - 15
//                );
    
    return this->getBoundingBox();
}

void Player::runFlyAnimation() {
    auto animation = Animation3D::create("models/dragon/Dragon.c3t", "Fly_New");
    
    if (animation) {
        this->stopAllActions();
        
        auto animate = Animate3D::create(animation);
        animate->setSpeed(1.5);
        
        this->runAction(animate);
    }
}

void Player::runWalkAnimation() {
    auto animation = Animation3D::create("models/dragon/Dragon.c3t", "Walk_New");
    
    if (animation) {
        auto animate = Animate3D::create(animation);
        animate->setSpeed(2.5);
        
        this->runAction(RepeatForever::create(animate));
    }
}


void Player::runIdelAnimation() {
    auto animation = Animation3D::create("models/dragon/Dragon.c3t", "Idel_New");
    
    if (animation) {
        auto animate = Animate3D::create(animation);
        animate->setSpeed(2.5);
        
        this->runAction(RepeatForever::create(animate));
    }
}


void Player::runDefaultAnimation() {
    auto animation = Animation3D::create("models/dragon/Dragon.c3t", "Default Take");
    
    if (animation) {
        auto animate = Animate3D::create(animation);
        animate->setSpeed(2.5);
        
        this->runAction(animate);
    }
}


