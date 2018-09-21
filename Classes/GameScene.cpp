#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "GameManager.hpp"

USING_NS_CC;

Scene* GameScene::createScene() {
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    GameManager::Instance()->SetUpScaleFactors();
    GameManager::Instance()->StartBGMusic();
    
    log("visibleSize:%.1f, %.1f", visibleSize.width, visibleSize.height);
    log("origin:%.1f, %.1f", origin.x, origin.x);
    
    ImageNode* bgSprite = ImageNode::create("background.jpg", visibleSize, kContentAspectFill);
    bgSprite->setPosition(Vec2(visibleSize.width/2.0, visibleSize.height/2.0));
    addChild(bgSprite, kZindexBG);
    
    // init floor
    for(int i = 0; i < 2; i++){
        _floorSprite.pushBack(Sprite::create("treeline.png"));
        
        if (i == 0)
            _floorSprite.at(i)->setPosition(Vec2(visibleSize.width / 2, -200));
        else
            _floorSprite.at(i)->setPosition(Vec2(_floorSprite.at(i)->getBoundingBox().size.width + visibleSize.width / 2, -200));
        
        this->addChild(_floorSprite.at(i), kZindexTree);
    }
    
    _player = Player::createWithFileName("models/dragon/Dragon.c3t");
    this->addChild(_player, 100);
    _player->reset();
    _player->setTopOfTheScreen(visibleSize.height);
    _player->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 2));
    _player->setRotation3D(Vec3(0, 90, 0));
    _player->runFlyAnimation();
    
    _gameOver = true;
    _acceptTouches = true;
    
    _floorBottom = 50;
    _gameTime = 0;
    _middleY = visibleSize.height/2;
    _lastSpawnTime = 0;
    _nextSpawnTime = 0.2;
    _nextSpawnTimeDecrement = 0.1;
    
    _barrierSpeed = kTreeSpeed;
    
    log("_barrierSpeed = %f", _barrierSpeed);
    
    _barriers = Vector<Barrier*>{10};
    
    _gameScore = 0;
    
    initLabels();
    initListeners();
    createClouds();
    
    schedule(schedule_selector(GameScene::gameUpdate));
    
    return true;
}

#pragma mark - Init EventListeners & Labels

void GameScene::initListeners() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto listener2 = EventListenerKeyboard::create();
    listener2->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener2->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
    
    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->setEnabled(true);
    _mouseListener->onMouseUp = CC_CALLBACK_1(GameScene::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

void GameScene::initLabels() {
    
    const float labelFontSize = 24 * GETSCALEY * GETSCALEFAC;
    //const float scorePositionX = 42 * GETSCALEY * GETSCALEFAC;
    const float scorePositionY = 24 * GETSCALEY * GETSCALEFAC;
    //const float settingsGap = 24 * GETSCALEY * GETSCALEFAC;
    
    _scoreLabel = addLabel(labelFontSize + 15, "Point 0", Vec2(0.5, 0.5), Vec2(150, visibleSize.height - scorePositionY));
    
    _highScoreLabel = addLabel(labelFontSize + 15, "Best 0", Vec2(0.5, 0.5), Vec2(visibleSize.width/2, visibleSize.height / 1.3));
    _highScoreLabel->setVisible(false);
    
    _gameOverLabel = addLabel(labelFontSize + 25, "Game Over", Vec2(0.5, 0.5), Vec2(visibleSize.width/2, visibleSize.height / 2 ));
    
    _startLabel = addLabel(labelFontSize, "Press Any Key", Vec2(0.5, 0.5),Vec2(visibleSize.width / 2, visibleSize.height * 3/5));
    _gameOverLabel->setVisible(false);
    
    updateHighScoreLabel();
    
    auto closeItem = MenuItemImage::create(
                                           "settings.png",
                                           "settings.png",
                                           CC_CALLBACK_1(GameScene::menuSettingsCallback, this));
    
    closeItem->setScale(0.5);
    
    closeItem->setPosition(Point( visibleSize.width - 50 , visibleSize.height - 50));
    
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, kZindexPlayer);
}

Label* GameScene::addLabel(const float fontSize, const char *text, const Vec2 anchor, const Vec2 position){
    Label *theLabel = Label::createWithTTF(text, kFontName, fontSize);
    theLabel->setAnchorPoint(anchor);
    theLabel->setPosition(position);
    theLabel->setColor(Color3B::RED);
    this->addChild(theLabel, kZindexPlayer);
    return theLabel;
}

#pragma mark - Game logic

void GameScene::startGame() {
    _startLabel->setVisible(false);
    menu->setVisible(false);
    
    _player->state = kPlayerStateMoving;
    _gameOver = false;
    startClouds();
    
    auto *actionMove = MoveBy::create(12.2, Vec2(-visibleSize.width, NULL));
     _floorSprite.at(0)->runAction(RepeatForever::create(actionMove));
    
    actionMove = MoveBy::create(12.2, Vec2(-visibleSize.width, NULL ));
    _floorSprite.at(1)->runAction(RepeatForever::create(actionMove));
}

void GameScene::gameOver() {
    
    GameManager::Instance()->playEffect(kEffectExplosion);
    
    menu->setVisible(true);
    _gameOverLabel->setVisible(true);
    _acceptTouches = false;
    _player->reset();
    GameManager::Instance()->SetHighScore(_gameScore);
    stopGame();
    
    _highScoreLabel->setVisible(true);
    _scoreLabel->setPosition( Vec2(visibleSize.width/2, visibleSize.height / 3.5));
}

void GameScene::stopGame() {
    _nextSpawnTime = 0.2;
    stopClouds();
    
    for(int i = 0; i < 2; i++)
        _floorSprite.at(i)->stopAllActions();
    
    scheduleOnce(schedule_selector(GameScene::resetEnableAfterGameOver), 2.5f);
}

void GameScene::resetEnableAfterGameOver(float dt) {
    _gameScore = 0;
    updateScoreLabel();
    updateHighScoreLabel();
    _gameOverLabel->setVisible(false);
    _startLabel->setVisible(true);
    _acceptTouches = true;
    _player->setPositionY(_middleY);
    
    for(auto tube: this->_barriers)
        tube->stop();
    
    _player->runIdelAnimation();
    _highScoreLabel->setVisible(false);
    _scoreLabel->setPosition( Vec2(150, visibleSize.height - 24 * GETSCALEY * GETSCALEFAC));
    
    _barrierSpeed = kTreeSpeed;
    _nextSpawnTimeDecrement = 0.1;
    _barriers.clear();
}

#pragma mark - Update Events

void GameScene::updateScoreLabel() {
    char ScoreString[64];
    sprintf(ScoreString, "Point %d", _gameScore);
    _scoreLabel->setString(ScoreString);
}

void GameScene::updateHighScoreLabel() {
    char ScoreString[64];
    sprintf(ScoreString, "Best %d", GameManager::Instance()->GetHighScore());
    _highScoreLabel->setString(ScoreString);
}

void GameScene::gameUpdate(float dt) {
    //log("HelloWorld::gameUpdate dt:%f", dt);
    if (_gameOver == false) {
        _gameTime += dt;
        
        _lastSpawnTime += dt;
        
        if (_lastSpawnTime > _nextSpawnTime) {
            // add barriers
            setSpawnTime();
            spawnNewBarriers();
        }
        
        if (_player->getPositionY() < _floorBottom) {
            _gameOver = true;
        } else{
            
            // collision detection
            for(auto barrier: this->_barriers){
                if (_player->TubeCollisionBox().intersectsRect( Rect( barrier->getBoundingBox().origin.x + 25,
                                                                      barrier->getBoundingBox().origin.y,
                                                                      barrier->getBoundingBox().size.width/2,
                                                                      barrier->getBoundingBox().size.height)
                                                               )) {
                    _gameOver = true;
                    break;
                } else{
                    if (barrier->state == kBarrierStateActive && barrier->scored == false) {
                        if ( (barrier->getBoundingBox().origin.x + barrier->getBoundingBox().size.width) < _player->getBoundingBox().origin.x )  {
                                barrier->scored = true;
                            
                            if(barrier->pairBarrier != NULL)
                                barrier->pairBarrier->scored = true;
                            
                            
                            for(auto barrier: _barriers){
                                if(barrier->state == kBarrierStateActive){
                                    barrier->changeSpeed(_barrierSpeed);
                                }
                            }
                            
                                _gameScore += 1;
                                _barrierSpeed += 10;
                                GameManager::Instance()->playEffect(kEffectSuccess);
                        }
                    }
                }
            }
        }
        
        updateScoreLabel();
        
        if (_gameOver == false) {
            _player->update(dt);
        } else {
            gameOver();
        }
        
        // update floor
        if  (_floorSprite.at(0)->getPositionX() <= -visibleSize.width/2)
            _floorSprite.at(0)->setPosition(Vec2(_floorSprite.at(1)->getPositionX() + _floorSprite.at(1)->getBoundingBox().size.width, -200));
        
        if  (_floorSprite.at(1)->getPositionX() <= -visibleSize.width/2)
            _floorSprite.at(1)->setPosition(Vec2(_floorSprite.at(0)->getPositionX() + _floorSprite.at(1)->getBoundingBox().size.width,-200));
    }
}

#pragma mark - Clouds Logic

void GameScene::startClouds() {
    for(auto cloud: this->_clouds)
        cloud->start();
    
    for(auto tube: this->_barriers)
        tube->stop();
}

void GameScene::stopClouds() {
    for(auto cloud: this->_clouds)
        cloud->stop();
    
    for(auto tube: this->_barriers)
        tube->stopAllActions();
}

void GameScene::createClouds() {
    _clouds = Vector<Cloud*>{30};
   
    addCloud(kCloudSpeedSlow, SCALEPOS(700, 610), 0.5, kZindexCloudSlow, "cloud.png");
    
    addCloud(kCloudSpeedSlow, Vec2(700, 590), 0.5, kZindexCloudSlow, "cloud.png");
    addCloud(kCloudSpeedSlow, Vec2(150, 550), 0.5, kZindexCloudSlow, "cloud.png");
    
    addCloud(kCloudSpeedFast, Vec2(150, 300), 0.5, kZindexMount, "cloud.png");
    addCloud(kCloudSpeedFast, Vec2(400, 500), 0.5, kZindexMount, "cloud.png");
    addCloud(kCloudSpeedFast, Vec2(880, 400), 0.5, kZindexMount, "cloud.png");
    
    addCloud(kMountSpeed, Vec2(300, 170), 4, kZindexMount, "mountain1.png");
    addCloud(kMountSpeed, Vec2(900, 170), 4, kZindexMount, "mountain2.png");
}

void GameScene::addCloud(const float speed, const Vec2 position, const float scale, const int zIndex, std::string fileName) {
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Cloud *cloud = Cloud::createWithFileName(fileName);
    cloud->setSpeedAndWidth(speed, visibleSize.width);
    cloud->setScale(scale);
    cloud->setPosition(position);
    cloud->setGlobalZOrder(-10);
    this->addChild(cloud, zIndex);
    
    _clouds.pushBack(cloud);
}

#pragma mark - Barriers Logic

void  GameScene::setSpawnTime() {
    _lastSpawnTime = 0;
    _nextSpawnTime = (float)(rand() % kBarrierSpawnTimeVariance / 10 + kBarrierSpawnMinTime);
    _nextSpawnTime -= _nextSpawnTimeDecrement;
    _nextSpawnTimeDecrement += 0.05;
    log("_nextSpawnTime = %f", _nextSpawnTime);
}

void  GameScene::spawnNewBarriers() {
    int ourChance = rand() % 3 + 1;
    
    while(1){
        if(_lastBarrierType == kBarrierTypeUpper && ourChance == 1){
            ourChance = rand() % 3 + 1;
        } else if(_lastBarrierType == kBarrierTypeLower && ourChance == 2){
            ourChance = rand() % 3 + 1;
        } else if(_lastBarrierType == kBarrierTypePair && ourChance == 3){
            ourChance = rand() % 3 + 1;
        } else{
            break;
        }
    }
    
    if (ourChance == 1) {
        spawnUpperOrLower(true);
    } else if(ourChance == 2){
        spawnUpperOrLower(false);
    } else {
        spawnBarrierPair();
    }
}

// установка туба ниже или выше по Y ???????
void  GameScene::spawnUpperOrLower(bool isUpper) {
    _lastBarrierType = isUpper == true ? kBarrierTypeUpper : kBarrierTypeLower;
    
    int YMax = isUpper == true ? _middleY : kSingleGapTop;
    int YMin = isUpper == true ? kSingleGapBottom : _middleY;
    
    if(isUpper == false){
        if(YMax - _lastGetUnderY > kTubeMaxUpPixels){
            YMax = _lastGetUnderY + kTubeMaxUpPixels;
        }
    }
    
    int YRange = abs(YMax - YMin);
    int Ypos = YMax - rand() % YRange;
    
    if(isUpper){
        _lastGetUnderY = Ypos;
    } else {
        _lastGetUnderY = _middleY;
    }
    
    spawnABarrier(isUpper, Ypos);
}


void GameScene::spawnBarrierPair() {
    _lastBarrierType = kBarrierTypePair;
    
    int Gap = kDoubleGapMin + (rand() % (int)(kDoubleGapMax - kDoubleGapMin)); // разрыв
    int YRange = kDoubleGapTop - Gap - kDoubleGapBottom;  // Y диапазон
    int TopY = kDoubleGapTop - (rand() % YRange); // рандомная позиция сверху Y
    int BottomY = TopY - Gap;                     // рандомная позиция снизу Y
    
    _lastGetUnderY = TopY;
        
    spawnABarrier(true, TopY)->setPair(spawnABarrier(false, BottomY));
}

Barrier* GameScene::spawnABarrier(bool isUpper, float Ypos) {
    Barrier *barrier = getNextBarrier();
    
    if(isUpper){
        barrier->setAnchorPoint(Vec2(0.5, 0));
        barrier->setFlippedY(false);
    }
    else{
        barrier->setAnchorPoint(Vec2(0.5, 1));
        barrier->setFlippedY(true);
    }
    
    barrier->setPositionY(Ypos);
    
    barrier->start();
    
    return barrier;
}


Barrier* GameScene::getNextBarrier() {
    
    for(auto barrier: _barriers){
        if(barrier->state == kBarrierStateInActive){
            return barrier;
        }
    }
    
    
    Barrier *newBarrier = Barrier::createWithFileName("liana.png");
    
    newBarrier->setScale(3);
    newBarrier->Initialise(_barrierSpeed, visibleSize.width);
    this->addChild(newBarrier, kZindexTube);
    
    _barriers.pushBack(newBarrier);
    
    return newBarrier;
}

#pragma mark - Touch/Key/Mouse Events

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    //log("x:%f y:%f", touch->getLocation().x, touch->getLocation().y);
    
    if (!_acceptTouches)
        return false;
    
    GameManager::Instance()->playEffect(kEffectFly);
    
    if (_gameOver == true) {
        startGame();
    } else {
        _player->runFlyAnimation();
        _player->setStartSpeed();
    }
    
    return true;
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if( keyCode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE ){
        
        if (_acceptTouches) {
            
             GameManager::Instance()->playEffect(kEffectFly);
            
            if (_gameOver == true) {
                startGame();
            } else {
                _player->runFlyAnimation();
                _player->setStartSpeed();
            }
        }
    }
    
    if( keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE )
        menuCloseCallback(NULL);
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
    if( keyCode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE ){
        
    }
}

void GameScene::onMouseDown(cocos2d::Event *event) {
    
    if (_acceptTouches) {
        
         GameManager::Instance()->playEffect(kEffectFly);
        
        if (_gameOver == true) {
            startGame();
        } else {
            _player->runFlyAnimation();
            _player->setStartSpeed();
        }
    }
}

void GameScene::onMouseUp(cocos2d::Event *event) {
    
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameScene::menuSettingsCallback(Ref* pSender){
    GameManager::Instance()->playEffect(kEffectPlayerTap);
    GameManager::Instance()->runScene(kSceneSettings);
}
