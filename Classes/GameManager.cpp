 //
//  GameManager.cpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/24/17.
//
//

#include "GameManager.hpp"
#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"
#include "Constants.h"
#include "GameScene.h"
#include "SettingsScene.hpp"
#include "SplashScene.hpp"

USING_NS_CC;

using namespace CocosDenshion;

#define kEXTHD "-HD"
#define kEXTUHD "-HD"
#define kEXTND "-ND"

#define kNumExplosions 2
#define kNumPlayerTap 1
#define kNumSuccess 2

GameManager *GameManager::_pInstance = NULL;

void GameManager::runScene(const int sceneNum){
    Scene *pScene = NULL;
    
    if (sceneNum == kSceneGame) {
        pScene = GameScene::createScene();
    } else if (sceneNum == kSceneSettings)
        pScene = SettingsScene::createScene();
    else if (sceneNum == kSceneSplash)
        pScene = SplashScene::createScene();
    
    if(pScene != NULL){
        if(Director::getInstance()->getRunningScene() == NULL)
            Director::getInstance()->runWithScene(pScene);
        else
            Director::getInstance()->replaceScene(pScene);
    }
    
}

GameManager *GameManager::Instance(){
    if(!_pInstance){
        _pInstance = new GameManager;
    }
    return _pInstance;
}

float GameManager::GetScaleX(){
    return _scaleX;
}

float GameManager::GetScaleY(){
    return _scaleY;
}

float GameManager::GetScaleFactor(){
    return _scaleFactor;
}

void GameManager::SetUpScaleFactors(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _extension = (char*)kEXTHD;
    _scaleFactor = 1.0;
    
    if(visibleSize.width * visibleSize.height > 960 * 640){
        _scaleFactor = 2.0;
        _extension = (char*)kEXTHD;
    } else if(visibleSize.width * visibleSize.height <= 480 * 320){
        _scaleFactor = 0.5;
        _extension = (char*)kEXTND;
    }
    
    _scaleX = visibleSize.width / (960 * _scaleFactor);
    _scaleY = visibleSize.height / (640 * _scaleFactor);
    
    log("_scaleFactor:%.2f _scaleX:%.2f _scaleY:%.2f", _scaleFactor, _scaleX, _scaleY);
}

void GameManager::GetFileName(char *array, const int len, const char *name, const char *fileExt){
    memset(array, 0, sizeof(char) * len);
    sprintf(array, "%s%s%s", name, _extension, fileExt);
}

void GameManager::lateInit(){
    int index = 0;
    
    for(index = 0; index < kNumExplosions; ++index)
        preloadEffect("Explosion", index+1);
    
    	for (index = 0; index < kNumPlayerTap; ++index){
    		preloadEffect("Tap", index + 1);
    	}
    	for (index = 0; index < kNumSuccess; ++index){
    		preloadEffect("Success", index + 1);
    	}
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.mp3");
    
    _musicVol = 5;
    _effectsVol = 5;
    _highScore = 0;
}

void GameManager::playEffect(const int effectNum){
    	switch (effectNum)
    	{
    	case kEffectExplosion:
    		playEffectName("Explosion", kNumExplosions);
    		break;
    	case kEffectPlayerTap:
    		//playEffectName("Tap", kNumPlayerTap);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Tap.wav");
    		break;
    	case kEffectSuccess:
    		playEffectName("Success", kNumSuccess);
    		break;
        case kEffectFly:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dragonFly.wav");
            //playEffectName("dragonFly", kNumSuccess);
            break;
        }
}

void GameManager::preloadEffect(const char* name, const int num){
    	char EffectName[32];
    	memset(EffectName, 0, sizeof(EffectName));
    	sprintf(EffectName, "%s%d.wav", name, num);
    	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(EffectName);
}

void GameManager::playEffectName(const char* name, const int num){
    	int randnum = rand() % num + 1;
    	char EffectName[32];
    	memset(EffectName, 0, sizeof(EffectName));
    	sprintf(EffectName, "%s%d.wav", name, randnum);
    	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)_effectsVol / 10);
    	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EffectName);
}

int GameManager::getVol(const int volType){
    if (volType == kVolTypeMusic){
        return _musicVol;
    }
    else if (volType == kVolTypeEffect){
        return	_effectsVol;
    }
}

void GameManager::setVol(const int volType, const int val){
    if (volType == kVolTypeMusic){
        _musicVol = val;
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)_musicVol / 10);
       // UserDefault::getInstance()->setIntegerForKey(US_VOL_MUSIC, _musicVol);
    }
    else if (volType == kVolTypeEffect){
        _effectsVol = val;
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)_effectsVol / 10);
        //UserDefault::getInstance()->setIntegerForKey(US_VOL_EFFECT, _effectsVol);
    }
}

void GameManager::StartBGMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)_musicVol / 10);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
}

void GameManager::StopBGMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

int GameManager::GetHighScore() {
    return _highScore;
}

void GameManager::SetHighScore(const int score) {
    if (score > _highScore) {
        _highScore = score;
        //UserDefault::getInstance()->setIntegerForKey(US_HIGH_SCORE, _highScore);
    }
}


void GameManager::SaveSettings(int volM, int volE){
    //UserDefault::getInstance()->setIntegerForKey(US_VOL_MUSIC, volM);
    //UserDefault::getInstance()->setIntegerForKey(US_VOL_EFFECT, volE);
}
