//
//  Constants.h
//  FBDemo
//
//  Created by Denys Risukhin on 11/24/17.
//
//

#include <stdio.h>

#define kZindexBG 0
#define kZindexFloor 40
#define kZindexTube 35
#define kZindexPlayer 100
#define kZindexCloudFast 20
#define kZindexCloudSlow 10
#define kZindexTree 50
#define kZindexMount 30

#define kCloudScaleSlow 0.4 * GETSCALEY
#define kCloudScaleFast 0.85 * GETSCALEY
#define kMountScale 0.8 * GETSCALEY
#define kTreeScale 1.0 * GETSCALEY

#define kCloudSpeedSlow 13.0 * GETSCALEY * GETSCALEFAC
#define kCloudSpeedFast 53.0 * GETSCALEY * GETSCALEFAC
#define kMountSpeed 30.0 * GETSCALEY * GETSCALEFAC
#define kTreeSpeed 70.0 * GETSCALEY * GETSCALEFAC

#define kPlayerStateMoving 0
#define kPlayerStateStopped 1
#define kPlayerStartSpeedY 300 * GETSCALEY * GETSCALEFAC

#define GRAVITI -620 * GETSCALEY * GETSCALEFAC

#define kBarrierStateActive 0
#define kBarrierStateInActive 1
#define kBarrierStateInActiveX -1000 * GETSCALEX * GETSCALEFAC

#define kBarrierSpawnMinTime 4.3  //2.3  min gap between tubes
#define kBarrierSpawnTimeVariance 8

#define kBarrierTypeUpper 0
#define kBarrierTypeLower 1
#define kBarrierTypePair 2
#define kBarrierTypeNone 3

#define kSingleGapTop 440 * GETSCALEY * GETSCALEFAC
#define kSingleGapBottom 230 * GETSCALEY * GETSCALEFAC
#define kSingleGapMax 280 * GETSCALEY * GETSCALEFAC
#define kSingleGapMin 160 * GETSCALEY * GETSCALEFAC

#define kDoubleGapTop 480 * GETSCALEY * GETSCALEFAC
#define kDoubleGapBottom 120 * GETSCALEY * GETSCALEFAC
#define kDoubleGapMax 220 * GETSCALEY * GETSCALEFAC
#define kDoubleGapMin 140 * GETSCALEY * GETSCALEFAC

#define kTubeMaxUpPixels 180 * GETSCALEY * GETSCALEFAC

#define kEffectPlayerTap 0
#define kEffectSuccess 1
#define kEffectExplosion 2
#define kEffectFly 3

#define kSceneGame 0
#define kSceneSettings 1
#define kSceneSplash 2

#define kFontName "fonts/04B_30__.ttf"

#define kVolTypeEffect 0
#define kVolTypeMusic 1












