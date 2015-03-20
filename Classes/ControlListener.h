#ifndef __CONTROLLISTENER_H__
#define __CONTROLLISTENER_H__
#include "cocos2d.h"
USING_NS_CC;

class ControlListener
{
public:

	virtual void setPos(CCPoint pos) = 0;
	virtual CCPoint getPos() = 0;
	
};

#endif