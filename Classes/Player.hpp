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

/*!
 *   Represents the Player.
 */
class Player : public cocos2d::Sprite3D{
public:
    
    /**
     * kPlayerStateMoving 0
     * kPlayerStateStopped 1
     */
    int state;
    
    static Player* createWithFileName(std::string fileName);
    
    /**
     * Calculates new Y pos & speed for the player.
     */
    void update(float dt);
    
    /**
     * Stopped the player.
     */
    void reset();
    
    /**
     * Init speed to const value.
     * @param _speedY
     */
    void setStartSpeed();
    
    void setTopOfTheScreen(const float tos);
    
    
    /**
     * Retruns player bounding box (return An AABB (axis-aligned bounding-box) in its parent's coordinate system).
     */
    cocos2d::Rect TubeCollisionBox();
    
    Player() {};
    
    /**
     * Animations of the player.
     */
    void runFlyAnimation();
    void runWalkAnimation();
    void runIdelAnimation();
    void runDefaultAnimation();
    
private:
    float _speedY;
    float _topOfScreen;
    
};

#endif /* Player_hpp */
