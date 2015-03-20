#ifndef __OVER_SCENE_H__
#define __OVER_SCENE_H__
#include "cocos2d.h"

class OverScene : public cocos2d::CCLayer
{
public:

	virtual bool init();
	static cocos2d::CCScene* scene(int score);
	CREATE_FUNC(OverScene);

private:
	void showScore(int score);
	void restart(CCObject* pSender);
	void menuStartCallback(CCObject* pSender);
};
#endif