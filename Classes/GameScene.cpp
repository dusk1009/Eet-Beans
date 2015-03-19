#include "GameScene.h"
#include "AStar.h"
USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->setTouchEnabled(true);
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	initMap();
	//initMenu();
    return true;
}

bool wall[30][20];
void GameScene::initMap()
{
	map = CCTMXTiledMap::create("map.tmx");
	this->addChild(map,0);

	//初始化障碍物
	CCTMXLayer *wallLayer = map->layerNamed("wall");
	CCSize mapSize = map->getMapSize();
	memset(wall, 0, sizeof(wall));
	for (int i = 0; i < mapSize.width; i++)
		for (int j = 0; j < mapSize.height; j++)
		{
			if (wallLayer->tileAt(ccp(i, j)))
			{
				wall[i][j] = true;
			}
		}
	//初始化玩家和怪物
	CCTMXObjectGroup *objGroup = map->objectGroupNamed("object");
	player = CCSprite::create("player.png");
	player->setAnchorPoint(ccp(0, 0));
	player->setPosition(getPosByName(objGroup, "player"));
	this->addChild(player, 1);
	monster1 = CCSprite::create("monster.png");
	monster1->setAnchorPoint(ccp(0, 0));
	monster1->setPosition(getPosByName(objGroup, "monster1"));
	this->addChild(monster1, 1);
	monster2 = CCSprite::create("monster.png");
	monster2->setAnchorPoint(ccp(0, 0));
	monster2->setPosition(getPosByName(objGroup, "monster2"));
	this->addChild(monster2, 1);

	startPos = transCPosToTilePos(player->getPosition());

}

CCPoint GameScene::getPosByName(CCTMXObjectGroup *objGroup,char* name)
{
	CCDictionary *dic = objGroup->objectNamed(name);
	float x = dic->valueForKey("x")->floatValue();
	float y = dic->valueForKey("y")->floatValue();
	return transTilePosToCPos(transCPosToTilePos(ccp(x, y)));
}

CCPoint GameScene::transTilePosToCPos(CCPoint tilePos)
{
	CCSize tileSize = map->getTileSize();
	int x = tileSize.width*tilePos.x;
	int y = visibleSize.height - tileSize.height*(tilePos.y+1);
	return ccp(x, y);
}

CCPoint GameScene::transCPosToTilePos(CCPoint cPos)
{
	CCSize tileSize = map->getTileSize();
	int x = cPos.x / tileSize.width;
	int y = (visibleSize.height - cPos.y-0.00001) / tileSize.height;
	return ccp(x, y);
}

void GameScene::menuStartCallback(CCObject* pSender)
{
	
	//startPos = ccp(13, 2);
	//player->setPosition(transTilePosToCPos(startPos));
	
}

bool GameScene::initMenu()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCLabelTTF *startLabel = CCLabelTTF::create("Start", "Arial", 50);
	CCMenuItemLabel *startMenu = CCMenuItemLabel::create(startLabel, this, menu_selector(GameScene::menuStartCallback));
	CCMenu *menu = CCMenu::create(startMenu, NULL);
	menu->alignItemsVertically();
	menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(menu, 1);
	return true;
}

void GameScene::moveEnd()
{
	if (!startPos.equals(endPos))
	{
		AStar *aStar = new AStar(startPos, endPos);
		startPos = aStar->getFirstStep()->pos;
		delete aStar;
		CCMoveTo *move = CCMoveTo::create(0.2f, transTilePosToCPos(startPos));
		CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GameScene::moveEnd));
		CCSequence *sequence = CCSequence::create(move, callFunc, NULL);
		player->runAction(sequence);
	}
}

void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint pos = touch->getLocation();
	endPos = transCPosToTilePos(pos);
	moveEnd();
}