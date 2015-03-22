#include "StartScene.h"
#include "GameScene.h"

int controlType;

CCScene* StartScene::scene()
{
	CCScene *scene = CCScene::create();
	StartScene *layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCLabelTTF *label = CCLabelTTF::create("How to Control ? ", "Arial", 80);
	label->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 100));
	this->addChild(label);
	//操作方式菜单
	CCLabelTTF *joystickLabel = CCLabelTTF::create("Joystick", "Arial", 50);
	CCMenuItemLabel *joystickMenu = CCMenuItemLabel::create(joystickLabel, this, menu_selector(StartScene::joystickCallBack));
	CCLabelTTF *buttonLabel = CCLabelTTF::create("Button", "Arial", 50);
	CCMenuItemLabel *buttonMenu = CCMenuItemLabel::create(buttonLabel, this, menu_selector(StartScene::buttonCallBack));
	CCMenu *menu = CCMenu::create(joystickMenu, buttonMenu, NULL);
	menu->alignItemsVertically();
	menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(menu, 1);
	return true;
}

void StartScene::joystickCallBack(CCObject* pSender)
{
	controlType = JOYSTICK;
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void StartScene::buttonCallBack(CCObject* pSender)
{
	controlType = BUTTON;
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}