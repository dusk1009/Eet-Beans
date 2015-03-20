#include "TransPos.h"
#include "GameScene.h"

CCPoint TransPos::transTilePosToCPos(CCPoint tilePos)
{
	int x = tileSize.width*tilePos.x;
	int y = visibleSize.height - tileSize.height*(tilePos.y + 1);
	return ccp(x, y);
}

CCPoint TransPos::transCPosToTilePos(CCPoint cPos)
{
	int x = cPos.x / tileSize.width;
	int y = (visibleSize.height - cPos.y - 0.00001) / tileSize.height;
	return ccp(x, y);
}
