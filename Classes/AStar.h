#ifndef __ASTAR_H__
#define __ASTAR_H__
#include "cocos2d.h"
USING_NS_CC;

class AStarNode
{
public:
	CCPoint pos;
	CCPoint parentPos;
	int g;
	int h;
	int type;
	bool isInOpenList;
	bool isInCloseList;
	AStarNode *parent;
	AStarNode(const CCPoint& pos)
	{
		this->pos = pos;
		this->isInOpenList = false;
		this->isInCloseList = false;
	}

};

class AStar
{
public:
	AStarNode* getFirstStep();
	AStar(CCPoint startPos, CCPoint endPos);
private:
	AStarNode* getNodeFromOpenList(CCPoint pos);
	inline int sumGH(AStarNode *node);
	void insertSurToOpen(AStarNode *node);
	void judge(AStarNode *child, AStarNode *parent);
	bool isWall(CCPoint pos);
	void heapify(AStarNode *array[], int size, int elem);
	AStarNode *openList[1000];
	AStarNode *closeList[100];
	CCPoint startPos, endPos;
	int openSize;
	
	bool nodeExist[30][20];
};

#endif