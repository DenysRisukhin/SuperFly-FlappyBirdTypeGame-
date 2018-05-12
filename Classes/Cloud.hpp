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

class Cloud: public cocos2d::Sprite{
public:
    
    static Cloud* createWithFileName(std::string fileName);
    void start();
    void stop();
    void setSpeedAndWidth(const float speed, const float width);
    
    Cloud() {};
    
private:
    
    void reachedDestination();
    
    float _speed;
    float _screenWidth;
    float _xOffSet;
    
};

#endif /* Cloud_hpp */
