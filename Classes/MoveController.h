#ifndef __MOVECONTROLLER_H__
#define __MOVECONTROLLER_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Controller.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MoveController :public Controller
{
public:
	virtual bool init();
	CREATE_FUNC(MoveController);

private:
	void upButtonDown(CCObject* pSender,CCControlEvent event);
	void downButtonDown(CCObject* pSender,CCControlEvent event);
	void leftButtonDown(CCObject* pSender,CCControlEvent event);
	void rightButtonDown(CCObject* pSender,CCControlEvent event);
	void buttonUp(CCObject* pSender, CCControlEvent event);
	void move();
	void moveEnd();
	bool initMenu();
	bool buttonDown;
	bool isMoving;
	CCPoint movePos;
};

#endif