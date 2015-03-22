#include "GameScene.h"
#include "StartScene.h"
#include "OverScene.h"
#include "AStar.h"
#include "MoveController.h"
#include "TransPos.h"
#include "Joystick.h"
USING_NS_CC;

bool wall[30][20];
CCSize tileSize;
CCSize visibleSize;

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
	scene->addChild(layer);


    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//this->setTouchEnabled(true);
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	initMap();
	//initMenu();
	//pthread_create(&monster1Pid, NULL, monster1Thread, NULL);
	this->scheduleUpdate();

    return true;
}

bool GameScene::initMap()
{
	map = CCTMXTiledMap::create("map.tmx");
	tileSize = map->getTileSize();
	this->addChild(map,0);

	//初始化障碍物
	CCTMXLayer *wallLayer = map->layerNamed("wall");
	CCSize mapSize = map->getMapSize();
	memset(wall, false, sizeof(wall));
	for (int i = 0; i < mapSize.width; i++)
		for (int j = 0; j < mapSize.height; j++)
		{
			if (wallLayer->tileAt(ccp(i, j)))
			{
				wall[i][j] = true;
			}
		}
	//初始化豆子
	beanLayer = map->layerNamed("bean");
	beanCount = 0;
	memset(bean, false, sizeof(bean));
	for (int i = 0; i < mapSize.width; i++)
		for (int j = 0; j < mapSize.height; j++)
		{
			if (beanLayer->tileAt(ccp(i, j)))
			{
				bean[i][j] = true;
				++beanCount;
			}
		}
	//初始化玩家和怪物
	objGroup = map->objectGroupNamed("object");
	initPlayer();
	monsterArray = CCArray::create();
	monsterArray->retain();
	initMonster(ccp(1,1));
	initMonster(ccp(28, 18));
	

	return true;
}

bool GameScene::initPlayer()
{
	player = (Player*)CCSprite::create("player.png");
	player->setAnchorPoint(ccp(0, 0));
	player->setPosition(getPosByName(objGroup, "player"));
	this->addChild(player, 1);
	//为玩家添加控制器
	switch (controlType)
	{
		case JOYSTICK://摇杆方式控制
		{
			Joystick *joystick = Joystick::create("Joystick_bg.png", "Joystick_stick.png");
			joystick->setPosition(ccp(80, 80));
			joystick->setListener(player);
			this->addChild(joystick);
			break;
		}
		case BUTTON: //方向键方式控制
		{
			
			MoveController *controllerLayer = MoveController::create();
			controllerLayer->setControlListener(player);
			this->addChild(controllerLayer);
			break;
		}
	}
	
	//初始化怪物终点
	endPos = TransPos::transCPosToTilePos(player->getPosition());
	return true;
}

bool GameScene::initMonster(CCPoint tilePos)
{
	CCSprite *monster = CCSprite::create("monster.png");
	monster->setAnchorPoint(ccp(0, 0));
	monster->setPosition(TransPos::transTilePosToCPos(tilePos));
	this->addChild(monster, 1);
	monsterArray->addObject(monster);
	moveEnd(monster);
	return true;
}

CCPoint GameScene::getPosByName(CCTMXObjectGroup *objGroup,char* name)
{
	CCDictionary *dic = objGroup->objectNamed(name);
	float x = dic->valueForKey("x")->floatValue();
	float y = dic->valueForKey("y")->floatValue();
	return TransPos::transTilePosToCPos(TransPos::transCPosToTilePos(ccp(x, y)));
}


void GameScene::menuStartCallback(CCObject* pSender)
{
	
	//startPos = ccp(13, 2);
	//player->setPosition(TransPos::transTilePosToCPos(startPos));
	
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

void GameScene::moveEnd(CCNode *sprite)
{
	CCPoint tilePos = TransPos::transCPosToTilePos(sprite->getPosition());
	if (!tilePos.equals(endPos))
	{
		AStar *aStar = new AStar(tilePos, endPos);
		tilePos = aStar->getFirstStep()->pos;
		delete aStar;
		CCMoveTo *move = CCMoveTo::create(0.2f, TransPos::transTilePosToCPos(tilePos));
		CCCallFuncN *callFunc = CCCallFuncN::create(this, callfuncN_selector(GameScene::moveEnd));
		callFunc->setTarget(sprite);
		CCSequence *sequence = CCSequence::create(move, callFunc, NULL);
		sprite->runAction(sequence);
	}
}

//void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
//{
//	CCTouch *touch = (CCTouch*)pTouches->anyObject();
//	CCPoint pos = touch->getLocation();
//	startPos = TransPos::transCPosToTilePos(pos);
//	moveEnd();
//}

//void* GameScene::monster1Thread(void* p)
//{
//	return NULL;
//}

void GameScene::update(float delta)
{
	endPos = TransPos::transCPosToTilePos(player->getPosition());
	int x = endPos.x;
	int y = endPos.y;
	if (bean[x][y])
	{
		bean[x][y] = false;
		beanLayer->removeTileAt(ccp(x, y));
		--beanCount;
	}
	if (!beanCount)
	{
		CCDirector::sharedDirector()->replaceScene(OverScene::scene(beanCount));
	}
	for (int i = 0; i < monsterArray->count(); i++)
	{
		CCPoint pos = ((CCSprite*)monsterArray->objectAtIndex(i))->getPosition();
		pos = TransPos::transCPosToTilePos(pos);
		if (pos.equals(endPos))
			CCDirector::sharedDirector()->replaceScene(OverScene::scene(beanCount));
	}
}