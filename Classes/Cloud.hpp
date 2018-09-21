//
//  Cloud.hpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/28/17.
//
//

#ifndef Cloud_hpp
#define Cloud_hpp

#include <stdio.h>
#include "cocos2d.h"

/*!
 *   Represents movable object's on the background:
 *   1. Clouds
 *   2. Mountains_1
 *   3. Mountains_2
 */
class Cloud: public cocos2d::Sprite{
public:
    
    static Cloud* createWithFileName(std::string fileName);
    
    /**
     * Starts moving.
     */
    void start();
    
    /**
     * Stoped all actions.
     */
    void stop();
    
    void setSpeedAndWidth(const float speed, const float width);
    
    Cloud() {};
    
private:
    
    /**
     * Sets start point for every obstacle and starts moving.
     */
    void reachedDestination();
    
    float _speed;
    float _screenWidth;
    float _xOffSet;
    
};

#endif /* Cloud_hpp */
