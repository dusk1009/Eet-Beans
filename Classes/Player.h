#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

enum class Player_State
{
	UP,
	DOWN,
	STOP,
	SPRINT,
	OVER
};

class Player : public CCSprite
{
public:
	Player();
	~Player();
	virtual bool init();
	CREATE_FUNC(Player);


private:
};


#endif