#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	
	
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

private:
	virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
	bool initMenu();
	void initMap();
	void menuStartCallback(CCObject* pSender);
	void moveEnd();
	CCPoint transTilePosToCPos(CCPoint tilePos);
	CCPoint transCPosToTilePos(CCPoint cPos);
	CCPoint getPosByName(CCTMXObjectGroup *objGroup,char* name);
	/*bool initPlayer();
	bool createScoreLab();
	bool createBullet();
	bool createLadder(CCPoint pos);*/


	CCSize visibleSize;
	CCSprite *player,*monster1,*monster2;
	CCTMXTiledMap *map;
	CCPoint startPos, endPos;
};
extern bool wall[][20];

#endif
