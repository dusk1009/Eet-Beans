#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include "cocos2d.h"
USING_NS_CC;

class Controller :public CCLayer
{
public:

	void setControlListener(CCSprite* controlListener);

protected:

	CCSprite* m_controlListener;
};

#endif