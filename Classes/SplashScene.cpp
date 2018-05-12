//
//  SplashScene.cpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/29/17.
//
//

#include "SplashScene.hpp"

#include "Constants.h"
#include "GameManager.hpp"
#include "Player.hpp"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    GameManager::Instance()->SetUpScaleFactors();
    
    ImageNode* bgSprite = ImageNode::create("menuBackground.jpg", visibleSize, kContentAspectFill);
    bgSprite->setPosition(Vec2(visibleSize.width/2.0, visibleSize.height/2.0));
    addChild(bgSprite, kZindexBG);

    auto superPic = Sprite::create("superFly.png");
    this->addChild(superPic, kZindexPlayer);
    superPic->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2));
    superPic->setScale(1.75);
    superPic->setOpacity(128);
    
    auto scaleTo = ScaleTo::create(0.5f, 1.74f);
    auto scaleBy = ScaleTo::create(0.5f, 1.75f);
    superPic->runAction(RepeatForever::create(Sequence::create(scaleTo, scaleBy, nullptr)));
    
    Label *theLabel = Label::createWithTTF("Loading...", kFontName, 50);
    theLabel->setPosition(Vec2(visibleSize.width / 2, 50));
    theLabel->setColor(Color3B::RED);
    this->addChild(theLabel, kZindexPlayer);
    
    Player *rocketMan = Player::createWithFileName("models/dragon/Dragon.c3t");
    rocketMan->setRotation3D(Vec3(0, 90, 0));
    rocketMan->runWalkAnimation();
    
    rocketMan->setPosition(Vec2(visibleSize.width/2, 100));
    addChild(rocketMan, 100);
    
    this->scheduleOnce(schedule_selector(SplashScene::RunGameScreen), 2.5f);
    
    return true;
}

void SplashScene::RunGameScreen(float dt){
    GameManager::Instance()->runScene(kSceneGame);
}
