#ifndef __TRANSPOS_H__
#define __TRANSPOS_H__
#include "cocos2d.h"
USING_NS_CC;

class TransPos
{
public:
	static CCPoint transTilePosToCPos(CCPoint tilePos);
	static CCPoint transCPosToTilePos(CCPoint cPos);
private:
};

#endif