//
//  ImageNode.h
//  Tarot
//
//  Created by Andrey Bogaevsky on 29.06.15.
//
//	Make sprite with concrete size and scale modes.

#ifndef __Tarot__ImageNode__
#define __Tarot__ImageNode__

#include <stdio.h>
#include "ImageNode.h"

USING_NS_CC;

enum ImageNodeContentMode {
	kContentScaleToFit, // scale to image initial size
	kContentAspectFit, // all image on screen with borders
	kContentAspectFill // all initial size fill with image (without borders)
};

/*!
 *   Represents images processing.
 */
class ImageNode : public cocos2d::Node
{
private:
	Sprite * imageSprite;
	ImageNode(void);	
    ImageNode(const std::string imageName, cocos2d::Size size, ImageNodeContentMode contentMode = kContentScaleToFit);
	
public:
	virtual ~ImageNode();
	
	static ImageNode * create (const std::string imageName, cocos2d::Size size, ImageNodeContentMode contentMode);

    /**
     * Scale methods.
     */
	static Vec2 getScaleToFitScale (cocos2d::Size &originSize, cocos2d::Size &fitSize);
	static float getAspectFitScale (cocos2d::Size &originSize, cocos2d::Size &fitSize);
	static float getAspectFillScale (cocos2d::Size &originSize, cocos2d::Size &fillSize);
};


#endif /* defined(__Tarot__ImageNode__) */
