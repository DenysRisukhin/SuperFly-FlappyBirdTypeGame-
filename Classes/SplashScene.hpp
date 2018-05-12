//
//  SplashScene.hpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/29/17.
//
//

#ifndef SplashScene_hpp
#define SplashScene_hpp

#include <stdio.h>
#include "ImageNode.h"

class SplashScene : public cocos2d::Layer
{
private:
    
    void RunGameScreen(float dt);
    
public:
        
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

#endif /* SplashScene_hpp */
