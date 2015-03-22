#ifndef __START_SCENE_H__
#define __START_SCENE_H__
enum ControlType
{
	JOYSTICK,
	BUTTON
};

#include "cocos2d.h"
USING_NS_CC;

class StartScene : public cocos2d::CCLayer
{
public:

	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(StartScene);

private:
	void start(CCObject* pSender);
	void joystickCallBack(CCObject* pSender);
	void buttonCallBack(CCObject* pSender);
};
extern int controlType;
#endif