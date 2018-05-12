//
//  GameManager.hpp
//  FBDemo
//
//  Created by Denys Risukhin on 11/24/17.
//
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>

class GameManager{
    
public:
    static GameManager* Instance();
    
    void LateInit();
    
    float GetScaleX();
    float GetScaleY();
    float GetScaleFactor();
    
    void SetUpScaleFactors();
    
    void GetFileName(char *array, const int len, const char *name, const char *fileExt);
    
    void lateInit();
    void playEffect(const int effectNum);
    
    void runScene(const int sceneNum);
    
    int getVol(const int volType);
    void setVol(const int volType, const int val);
    
    void StartBGMusic();
    void StopBGMusic();
    
    int GetHighScore();
    void SetHighScore(const int score);
    
    void SaveSettings(int volM, int volE);
    
private:
    GameManager() {};
    GameManager(GameManager const&){};
    GameManager& operator=(GameManager const&){};
    
    void preloadEffect(const char* name, const int num);
    void playEffectName(const char* name, const int num);
    
    static GameManager* _pInstance;
    
    float _scaleX;
    float _scaleY;
    float _scaleFactor;
    char *_extension;
    
    int _musicVol;
    int _effectsVol;
    int _highScore;
    
    ~GameManager(){};
};

#define GETSCALEX ( GameManager::Instance()->GetScaleX())
#define GETSCALEY ( GameManager::Instance()->GetScaleY())
#define GETSCALEFAC ( GameManager::Instance()->GetScaleFactor() )

#define SCALEX(p) ( (p) * GETSCALEX)
#define SCALEY(p) ( (p) * GETSCALEY)

#define SCALEPOS(x,y) ( Vec2 ( GETSCALEX * (x) * GETSCALEFAC, GETSCALEY * (y) * GETSCALEFAC) )

#define SCALEFONT(p) ( (p) * SCALEY * GETSCALEFAC)

#define GETFILENAME(a, l, n, e) \
     ( GameManager::Instance()->GetFileName(a, l, n, e) )

#define SCALENODE_XY(n) \
    n->setScaleX(GETSCALEX); \
    n->setScaleY(GETSCALEY)

#define SCALENODE_Y(n) \
n->setScale(GETSCALEY)



#endif /* GameManager_hpp */
