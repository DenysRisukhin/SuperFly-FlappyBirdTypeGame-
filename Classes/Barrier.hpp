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

class Barrier: public cocos2d::Sprite{
public:
    
    Barrier(): pairBarrier(NULL) {}
    
    ~Barrier() {}
    
    static Barrier* createWithFileName(std::string fileName);
    
    
    // The method runs animation & calculates distance, time, destination, sets barrier to aactive state
    void start();
    
    // The method sets barrier to inActive state, sets inActiveX pos & scored value
    void stop();
    
    void Initialise(const float speed, const float width);
    
    // The method sets pair barrier type. Usefully for corrects score increment in update method
    void setPair(Barrier* tb);
    
    // The method changes current move speed
    void changeSpeed(float speed);
    
    // kTubeStateActive 0
    // kTubeStateInActive 1
    int state;
    
    // Score state
    bool scored;
    
    Barrier *pairBarrier;
    
private:
    
    // The method calls to method stop(), after current barrier reached his destination (достиг конечной позиции)
    void reachedDestination();
    
    float _speed;
    float _screenWidth;
    
    // Barrier width bounding box
    float _xOffSet;
    
};

#endif /* Barrier_hpp */
