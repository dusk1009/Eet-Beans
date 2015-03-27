#include "Joystick.h"
#include "TransPos.h"
#include "GameScene.h"

#define PI 3.1415926

Joystick* Joystick::create(const char* bgFileName, const char* stickFileName, float scale)
{
	Joystick *joystick = new Joystick();
	if (joystick && joystick->init(bgFileName, stickFileName, scale))
	{
		joystick->autorelease();
		return joystick;
	}

	CC_SAFE_DELETE(joystick);
	return NULL;
}

bool Joystick::init(const char* bgFileName, const char* stickFileName, float scale)
{
	m_bg = CCSprite::create(bgFileName);
	m_bg->setScale(scale);
	m_bgRadius = scale * m_bg->getContentSize().width / 2;
	this->addChild(m_bg);
	m_stick = CCSprite::create(stickFileName);
	m_stick->setScale(scale);
	m_stickRadius = scale * m_stick->getContentSize().width / 2;
	//m_stick->setPosition(ccp(m_bgRadius + 10, m_bgRadius + 10));
	this->addChild(m_stick);

	this->scheduleUpdate();

	return true;
}

//void Joystick::setListener(CCSprite* listener)
//{
//	this->m_controlListener = listener;
//}

void Joystick::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0,true);
}

void Joystick::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool Joystick::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	CCPoint pos = this->convertTouchToNodeSpaceAR(touch);
	if (pos.x*pos.x + pos.y*pos.y < m_stickRadius*m_stickRadius)
	{
		m_stick->setPosition(pos);
		return true;
	}
	return false;
	
}

void Joystick::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
	CCPoint pos = this->convertTouchToNodeSpaceAR(touch);
	float temp = pos.x*pos.x + pos.y*pos.y;
	if (temp > m_bgRadius*m_bgRadius)
	{
		pos = pos.normalize();
		pos = pos*m_bgRadius;
	}
	m_stick->setPosition(pos);
	if (temp > m_stickRadius*m_stickRadius)
	{
		m_isTouching = true;
		judgeDirection(pos);
	}
}

void Joystick::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	m_stick->setPosition(ccp(0, 0));
	m_isTouching = false;
}

void Joystick::ccTouchCancelled(CCTouch *touch, CCEvent *event)
{

}

void Joystick::judgeDirection(CCPoint pos)
{
	
	CCLOG("%f,%f,%f", pos.x, pos.y, atan2f(pos.y,pos.x));
	float angle = atan2f(pos.y, pos.x);
	if (abs(angle) < PI / 4 )
	{
		m_direction = ccp(1, 0);
	}
	else if (angle > PI / 4 && angle < 3*PI / 4)
	{
		m_direction = ccp(0, 1);
	}
	else if (abs(angle) > 3*PI / 4)
	{
		m_direction = ccp(-1, 0);
	}
	else if (angle > -3*PI / 4 && angle < -PI / 4)
	{
		m_direction = ccp(0, -1);
	}
}

void Joystick::update(float delta)
{
	if (!m_isMoving && m_isTouching)
	{
		CCPoint tilePos = TransPos::transCPosToTilePos(m_controlListener->getPosition() + m_direction*tileSize.width);
		if (!wall[int(tilePos.x)][int(tilePos.y)])
		{
			m_isMoving = true;
			CCMoveBy *move = CCMoveBy::create(0.1f, m_direction*tileSize.width);
			CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(Joystick::moveEnd));
			CCSequence *sequence = CCSequence::create(move, callFunc, NULL);
			m_controlListener->runAction(sequence);
		}
	}
}

void Joystick::moveEnd()
{
	m_isMoving = false;
}