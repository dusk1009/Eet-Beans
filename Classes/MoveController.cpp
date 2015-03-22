#include "MoveController.h"
#include "GameScene.h"
#include "TransPos.h"

bool MoveController::init()
{
	initMenu();
	buttonDown = false;
	isMoving = false;
	return true;
}

bool MoveController::initMenu()
{
    //上下左右按钮
	CCScale9Sprite *upNormal = CCScale9Sprite::create("UpNormal.png");
	CCControlButton *upButton = CCControlButton::create(upNormal);
	upButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MoveController::upButtonDown), CCControlEventTouchDown);
	upButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MoveController::buttonUp), CCControlEventTouchUpInside);
	upButton->setPreferredSize(CCSize(100, 100));
	upButton->setPosition(ccp(0, 100));
	this->addChild(upButton, 1);
	
	CCScale9Sprite *downNormal = CCScale9Sprite::create("UpNormal.png");
	CCControlButton *downButton = CCControlButton::create(downNormal);
	downButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MoveController::downButtonDown), CCControlEventTouchDown);
	downButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MoveController::buttonUp), CCControlEventTouchUpInside);
	downButton->setPreferredSize(CCSize(100, 100));
	downButton->setPosition(ccp(0, 0));
	this->addChild(downButton, 1);
	
	CCScale9Sprite *leftNormal = CCScale9Sprite::create("UpNormal.png");
	CCControlButton *leftButton = CCControlButton::create(leftNormal);
	leftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MoveController::leftButtonDown), CCControlEventTouchDown);
	leftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MoveController::buttonUp), CCControlEventTouchUpInside);
	leftButton->setPreferredSize(CCSize(100, 100));
	leftButton->setPosition(ccp(-100, 0));
	this->addChild(leftButton, 1);
	
	CCScale9Sprite *rightNormal = CCScale9Sprite::create("UpNormal.png");
	CCControlButton *rightButton = CCControlButton::create(rightNormal);
	rightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MoveController::rightButtonDown), CCControlEventTouchDown);
	rightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MoveController::buttonUp), CCControlEventTouchUpInside);
	rightButton->setPreferredSize(CCSize(100, 100));
	rightButton->setPosition(ccp(100, 0));
	this->addChild(rightButton, 1);
	
	return true;
	
}

void MoveController::upButtonDown(CCObject* pSender, CCControlEvent event)
{
	if (!m_controlListener)
		return;
	buttonDown = true;
	movePos = ccp(0, tileSize.height);
	move();
}

void MoveController::downButtonDown(CCObject* pSender, CCControlEvent event)
{
	if (!m_controlListener)
		return;
	buttonDown = true;
	movePos = ccp(0, -tileSize.height);
	move();
}

void MoveController::leftButtonDown(CCObject* pSender, CCControlEvent event)
{
	if (!m_controlListener)
		return;
	buttonDown = true;
	movePos = ccp(-tileSize.width, 0);
	move();
}

void MoveController::rightButtonDown(CCObject* pSender, CCControlEvent event)
{
	if (!m_controlListener)
		return;
	buttonDown = true;
	movePos = ccp(tileSize.width, 0);
	move();
}

void MoveController::buttonUp(CCObject* pSender, CCControlEvent event)
{
	buttonDown = false;
}

void MoveController::moveEnd()
{
	isMoving = false;
	move();
}

void MoveController::move()
{
	if (buttonDown&&!isMoving)
	{
		CCPoint tilePos = TransPos::transCPosToTilePos(m_controlListener->getPosition()+movePos);
		if (!wall[int(tilePos.x)][int(tilePos.y)])
		{
			isMoving = true;
			CCMoveBy *moveUp = CCMoveBy::create(0.1f, movePos);
			CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(MoveController::moveEnd));
			CCSequence *sequence = CCSequence::create(moveUp, callFunc, NULL);
			m_controlListener->runAction(sequence);
		}

	}
}