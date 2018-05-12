//
//  SettingsScene.cpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/29/17.
//
//

#include "SettingsScene.hpp"
#include "Constants.h"
#include "GameManager.hpp"
#include "Player.hpp"


USING_NS_CC;


Scene* SettingsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SettingsScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SettingsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //    Size visibleSize =  Size(kDesignSizeW, kDesignSizeH);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    char fileName[32];
    
    ImageNode* bgSprite = ImageNode::create("menuBackground.jpg", visibleSize, kContentAspectFill);
    bgSprite->setPosition(Vec2(visibleSize.width/2.0, visibleSize.height/2.0));
    addChild(bgSprite, kZindexBG);
        
    float sf = 1.0; //GETSCALEY * GETSCALEFAC;
    const float BackButtonBottom = 40 * GETSCALEY * GETSCALEFAC;
    const float BackButtonLeft = 60 * GETSCALEY * GETSCALEFAC;
    const float FontSize = 20 * GETSCALEY * GETSCALEFAC;
    const float GapToAdjust = 140 * GETSCALEY * GETSCALEFAC;
    const float LeftGap = 120 * GETSCALEY * GETSCALEFAC;
    
    AddLabelVoid(FontSize, "SETTINGS", Vec2(0.5, 1.0), Vec2(visibleSize.width / 2, visibleSize.height - BackButtonBottom));
    AddLabelVoid(FontSize, "EFFETCS VOL.", Vec2(0.0, 0.5), Vec2(LeftGap, visibleSize.height / 2 + BackButtonBottom));
    
    _backLabel = AddLabel(FontSize + 20, "<", Vec2(0.0,0.0), Vec2(BackButtonLeft, visibleSize.height/1.11));
    
    _effVolPlusLabel = AddLabel(FontSize, "+", Vec2(0.5, 0.5), Vec2(visibleSize.width - LeftGap, visibleSize.height / 2 + BackButtonBottom));
    _effValueLabel = AddLabel(FontSize, "0", Vec2(0.5, 0.5), Vec2(_effVolPlusLabel->getBoundingBox().origin.x - GapToAdjust, visibleSize.height / 2 + BackButtonBottom));
    _effVolMinusLabel = AddLabel(FontSize, "-", Vec2(0.5, 0.5), Vec2(_effValueLabel->getBoundingBox().origin.x - GapToAdjust, visibleSize.height / 2 + BackButtonBottom));
    
    float EffectBottomY = _effValueLabel->getBoundingBox().origin.y;
    
    AddLabelVoid(FontSize, "MUSIC VOL.", Vec2(0.0, 1.0), Vec2(LeftGap, EffectBottomY - BackButtonBottom * 2));
    _musVolplusLabel = AddLabel(FontSize, "+", Vec2(0.5, 1.0), Vec2(visibleSize.width - LeftGap, EffectBottomY - BackButtonBottom * 2));
    _musicValueLabel = AddLabel(FontSize, "0", Vec2(0.5, 1.0), Vec2(_effVolPlusLabel->getBoundingBox().origin.x - GapToAdjust, EffectBottomY - BackButtonBottom * 2));
    _musVolMinusLabel = AddLabel(FontSize, "-", Vec2(0.5, 1.0), Vec2(_effValueLabel->getBoundingBox().origin.x - GapToAdjust, EffectBottomY - BackButtonBottom * 2));
    
    setLabelValues();
    
    Player *player = Player::createWithFileName("models/dragon/Dragon.c3t");
    player->setRotation3D(Vec3(0, 90, 0));
    player->runIdelAnimation();
    player->setScale(2);
    player->setPosition(Vec2(visibleSize.width/2, visibleSize.height/1.5));
    addChild(player, 100);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(SettingsScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool SettingsScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    //	CCLOG("HelloWorld::onTouchBegan x:%f y:%f", touch->getLocation().x, touch->getLocation().y);
    
    GameManager::Instance()->playEffect(kEffectPlayerTap);
    Point tp = Point(touch->getLocation().x,touch->getLocation().y);
    
    if(_backLabel->getBoundingBox().containsPoint(tp)) {
        GameManager::Instance()->runScene(kSceneGame);
    }
    else if (_musVolMinusLabel->getBoundingBox().containsPoint(tp)){
        IncVol(kVolTypeMusic, -1);
    }
    else if (_musVolplusLabel->getBoundingBox().containsPoint(tp)){
        IncVol(kVolTypeMusic, 1);
    }
    else if (_effVolMinusLabel->getBoundingBox().containsPoint(tp)){
        IncVol(kVolTypeEffect, -1);
    }
    else if (_effVolPlusLabel->getBoundingBox().containsPoint(tp)){
        IncVol(kVolTypeEffect, 1);
    }
    
    return true;
}

void SettingsScene::IncVol(const int type, const int inc){
    int CurrentVol = GameManager::Instance()->getVol(type);
    if ((inc == -1 && CurrentVol > 0) || (inc == 1 && CurrentVol < 10)){
        GameManager::Instance()->setVol(type, CurrentVol + inc);
    }
    setLabelValues();
}

Label* SettingsScene::AddLabel(const float fontSize, const char *text,
                               const cocos2d::Vec2 anchor, const cocos2d::Vec2 position) {
    Label *theLabel = Label::createWithTTF(text, kFontName, fontSize);
    theLabel->setAnchorPoint(anchor);
    theLabel->setPosition(position);
    theLabel->setColor(Color3B::RED);
    this->addChild(theLabel, kZindexPlayer);
    return theLabel;
}


void SettingsScene::AddLabelVoid(const float fontSize, const char *text,
                                 const cocos2d::Vec2 anchor, const cocos2d::Vec2 position) {
    Label *theLabel = Label::createWithTTF(text, kFontName, fontSize);
    theLabel->setAnchorPoint(anchor);
    theLabel->setPosition(position);
    theLabel->setColor(Color3B::RED);
    this->addChild(theLabel, kZindexPlayer);
}

void SettingsScene::setLabelValues() {
    char ValueString[16];
    int volM = GameManager::Instance()->getVol(kVolTypeMusic);
    
    
    sprintf(ValueString, "%d", volM);
    _musicValueLabel->setString(ValueString);
    
    int volE = GameManager::Instance()->getVol(kVolTypeEffect);
    memset(ValueString, 0, sizeof(ValueString));
    sprintf(ValueString, "%d", volE);
    _effValueLabel->setString(ValueString);
}

