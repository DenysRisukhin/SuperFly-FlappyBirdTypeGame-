#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.hpp"
#include "Cloud.hpp"
#include "Barrier.hpp"
#include "ImageNode.h"

USING_NS_CC;

class Player;
class Cloud;
class Tube;

class GameScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    void menuSettingsCallback(Ref* pSender);

    bool onTouchBegan(Touch *touch, Event *event);
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void onMouseDown(cocos2d::Event *event);
    void onMouseUp(cocos2d::Event *event);
    
private:
    
    Menu* menu;

    Player* _player;
    
    void gameUpdate(float dt);
    
    bool _gameOver;
    float _floorBottom;
    float _nextSpawnTimeDecrement;
    
    Vector<Cloud*> _clouds;
    Vector<Barrier*> _barriers;
    Vector<Sprite*> _floorSprite;
    
    Label *_scoreLabel;
    Label *_highScoreLabel;
    Label *_exitLabel;
    Label *_startLabel;
    Label *_gameOverLabel;
    Label *_settingsLabel;
    
    float _barrierSpeed;
    float _nextSpawnTime;
    float _lastSpawnTime;
    float _lastGetUnderY;
    float _gameTime;
    int   _lastBarrierType;
    float _middleY;
    int   _gameScore;
    
    void addCloud(const float speed, const Vec2 position, const float scale, const int zIndex, std::string fileName);
    
    // The method runs clouds animation & set barriers in inActiveX position
    void startClouds();
    
    // The method stops animatons for clouds & barriers
    void stopClouds();
    
    void createClouds();
    
    // The method sets spawn time for barriers
    void setSpawnTime();
    
    // The method sets type of barriers
    void spawnNewBarriers();
    
    // The method sets barriers Y pos
    void spawnUpperOrLower(bool isUpper);
    
    // The method calculates gap between pair barriers
    void spawnBarrierPair();
    
    // The method flipes the barriers, set Ypos & call to method barrier->start()
    Barrier* spawnABarrier(bool isUpper, float Ypos);
    
    // The method creates & returns new barrier or returns barrier from list with inActive state
    Barrier *getNextBarrier();
    
    bool _acceptTouches;
    
    cocos2d::Size visibleSize;
    
    void startGame();
    void stopGame();
    void gameOver();
    void resetEnableAfterGameOver(float dt);
    
    void updateScoreLabel();
    void updateHighScoreLabel();
    
    Label* addLabel(const float fontSize, const char *text, const Vec2 anchor, const Vec2 position);
    void initLabels();
    void initListeners();
};

#endif // __GAME_SCENE_H__