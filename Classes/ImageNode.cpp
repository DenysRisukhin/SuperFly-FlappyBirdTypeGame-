//
//  ImageNode.cpp
//  Tarot
//
//  Created by Andrey Bogaevsky on 29.06.15.
//
//

#include "ImageNode.h"

USING_NS_CC;

ImageNode * ImageNode::create (const std::string imageName, Size size, ImageNodeContentMode contentMode)
{
	ImageNode *node = new ImageNode(imageName,size,contentMode);
	
	if (node) {
		node->autorelease();
		return node;
	}
	
	CC_SAFE_DELETE(node);
	return NULL;
}


ImageNode::ImageNode(void) {
	imageSprite = NULL;
}

ImageNode::ImageNode(const std::string imageName, Size size, ImageNodeContentMode contentMode) {

	
    imageSprite = Sprite::create(imageName);
    imageSprite->setAnchorPoint(Vec2(0.5, 0.5));
    //imageSprite->setPosition(Vec2(size.width/2.0, size.height/2.0));
    
    Rect rect = imageSprite->getTextureRect();
    
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    
    switch (contentMode) {
        case kContentAspectFill:
            scaleX = scaleY = ImageNode::getAspectFillScale(rect.size, size);
            break;
            
        case kContentAspectFit:
            scaleX = scaleY = ImageNode::getAspectFitScale(rect.size, size);
            break;
            
        case kContentScaleToFit:
            Vec2 scaleVec = ImageNode::getScaleToFitScale(rect.size, size);
            scaleX = scaleVec.x;
            scaleY = scaleVec.y;
            break;
    }
    
    imageSprite->setScale(scaleX, scaleY);
    addChild(imageSprite);
    imageSprite->setGlobalZOrder(-10);
}

ImageNode::~ImageNode() {
    imageSprite->retain();
    imageSprite->removeFromParent();
    //imageSprite->release();
}


//------------------------------------------------------------------------------
// STATIC
//------------------------------------------------------------------------------

Vec2 ImageNode::getScaleToFitScale (Size &originSize, Size &fitSize) {
	
	// Calculate resize ratios for resizing
	float ratioW = fitSize.width / originSize.width;
	float ratioH = fitSize.height / originSize.height;
	
	return Vec2(ratioW,ratioH);
}

float ImageNode::getAspectFitScale (Size &originSize, Size &fitSize) {
	
	// Calculate resize ratios for resizing
	float ratioW = fitSize.width / originSize.width;
	float ratioH = fitSize.height / originSize.height;
	
	// smaller ratio will ensure that the image fits in the view
	return (ratioW < ratioH ? ratioW : ratioH);
}

float ImageNode::getAspectFillScale(Size &originSize, Size &fillSize) {
	
	// Calculate resize ratios for resizing
	float ratioW = fillSize.width / originSize.width;
	float ratioH = fillSize.height / originSize.height;
	
	// bigger ratio will ensure that the image fill in the view
	return (ratioW > ratioH ? ratioW : ratioH);
}
