#include "OverScene.h"
#include "GameScene.h"
using namespace cocos2d;

CCScene* OverScene::scene(int score)
{
	CCScene *scene = CCScene::create();
	OverScene *layer = OverScene::create();
	layer->showScore(score);
	scene->addChild(layer);
	return scene;
}

bool OverScene::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//重开按钮
	CCLabelTTF *restartLabel = CCLabelTTF::create("Restart", "Arial", 50);
	CCMenuItemLabel *startMenu = CCMenuItemLabel::create(restartLabel, this, menu_selector(OverScene::restart));
	CCMenu *menu = CCMenu::create(startMenu, NULL);
	menu->alignItemsVertically();
	menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(menu, 1);


	return true;
}

void OverScene::restart(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void OverScene::showScore(int score)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//显示得分
	CCLabelTTF *scoreLab = CCLabelTTF::create(CCString::createWithFormat("Your Score : %d", score)->getCString(), "Arial", 60);
	scoreLab->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 100));
	this->addChild(scoreLab);
}