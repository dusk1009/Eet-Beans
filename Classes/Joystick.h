#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__
#include "Controller.h"

USING_NS_CC;

class Joystick : public CCNode, public CCTargetedTouchDelegate
{
public:
	Joystick() : m_isMoving(false), m_isTouching(false){};
	static Joystick* create(const char* bgFileName, const char* stickFileName);
	bool init(const char* bgFileName, const char* stickFileName);

	virtual void update(float delta);

	void onEnter();
	void onExit();
	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
	virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
	virtual void ccTouchCancelled(CCTouch *touch, CCEvent *event);

	void setListener(CCSprite* listener);
	void judgeDirection(CCPoint pos);
	void moveEnd();

private:
	CCSprite* m_listener;
	CCSprite* m_bg;
	CCSprite* m_stick;
	float m_bgRadius;
	float m_stickRadius;
	CCPoint m_direction;
	bool m_isMoving;
	bool m_isTouching;

};

#endif
