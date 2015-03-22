#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
//#include "pthread\pthread.h"
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
	virtual void update(float delta);
	//virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
	bool initMenu();
	bool initMap();
	bool initPlayer();
	bool initMonster(CCPoint tilePos);
	void menuStartCallback(CCObject* pSender);
	void moveEnd(CCNode *sprite);
	CCPoint transTilePosToCPos(CCPoint tilePos);
	CCPoint transCPosToTilePos(CCPoint cPos);
	static CCPoint getPosByName(CCTMXObjectGroup *objGroup,char* name);
	/*bool initPlayer();
	bool createScoreLab();
	bool createBullet();
	bool createLadder(CCPoint pos);*/
	static void* monster1Thread(void* p);
	static void* monster2Thread(void* p);

	//pthread_t monster1Pid, monster2Pid;
	Player* player;
	CCSprite *monster1,*monster2;
	CCTMXTiledMap *map;
	CCTMXObjectGroup *objGroup;
	CCPoint startPos, endPos;
	CCArray *monsterArray;
	CCTMXLayer *beanLayer;
	int beanCount;//Ê£Óà¶¹×ÓÊý
	int bean[30][20];
};
extern bool wall[][20];
extern CCSize tileSize;
extern CCSize visibleSize;

#endif
