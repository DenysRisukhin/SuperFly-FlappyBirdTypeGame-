//
//  Player.hpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/28/17.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "cocos2d.h"

class Player : public cocos2d::Sprite3D{
public:
    
    // kPlayerStateMoving 0
    // kPlayerStateStopped 1
    int state;
    
    static Player* createWithFileName(std::string fileName);
    
    
    // The method calculates new Y pos & speed for player
    void update(float dt);
    void reset();
    void setStartSpeed();
    
    void setTopOfTheScreen(const float tos);
    
    // The method retruns player bounding box
    cocos2d::Rect TubeCollisionBox();
    
    Player() {};
    
    // Animations
    void runFlyAnimation();
    void runWalkAnimation();
    void runIdelAnimation();
    void runDefaultAnimation();
    
private:
    float _speedY;
    float _topOfScreen;
    
};

#endif /* Player_hpp */
