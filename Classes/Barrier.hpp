//
//  Barrier.hpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/28/17.
//
//

#ifndef Tube_hpp
#define Tube_hpp

#include <stdio.h>
#include "cocos2d.h"

/*!
 *   Represents obstacles. Uses 4 types of obstacles:
 *   1. kTubeTypePair
 *   2. kTubeTypeUpper
 *   3. kTubeTypeLower
 *   4. kTubeTypeNone
 */

class Barrier: public cocos2d::Sprite{
public:
    
    Barrier(): pairBarrier(NULL) {}
    
    ~Barrier() {}
    
    static Barrier* createWithFileName(std::string fileName);
    
    /**
     * Init data:
     * @param _speed
     * @param _screenWidth
     * @param _xOffSet
     * @param state
     * @param scored
     */
    void Initialise(const float speed, const float width);
    
    /**
     * Runs animation & calculates distance, time, destination, sets barrier to aactive state.
     */
    void start();
    
    /**
     * Sets barrier to inActive state, sets inActiveX pos & scored value.
     */
    void stop();
    
    /**
     * Sets pair barrier type. Usefully for corrects score increment in update method.
     */
    void setPair(Barrier* tb);
    
    /**
     * Changes current move speed.
     */
    void changeSpeed(float speed);
    
    /**
     * kTubeStateActive 0
     * kTubeStateInActive 1
     */
    int state;
    
    /**
     * State of score.
     */
    bool scored;
    
    Barrier *pairBarrier;
    
private:
    
    // The method calls to method stop(), after current barrier reached his destination (достиг конечной позиции)
    /**
     * Sets barrier to inActive state, sets inActiveX pos & scored value.
     */
    void reachedDestination();
    
    float _speed;
    float _screenWidth;
    
    // Barrier width bounding box
    float _xOffSet;
    
};

#endif /* Barrier_hpp */
