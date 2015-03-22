#include "AStar.h"
#include "GameScene.h"
#include <math.h>
#include <stdlib.h>
using namespace std;

AStar::AStar(CCPoint startPos, CCPoint endPos)
{
	this->startPos = startPos;
	this->endPos = endPos;
	memset(nodeExist, 0, sizeof(nodeExist));
}

AStarNode* AStar::getFirstStep()
{
	AStarNode *startNode = new AStarNode(startPos);
	nodeExist[int(startPos.x)][int(startPos.y)];
	openList[0] = startNode;
	startNode->g = 0;
	startNode->parent = NULL;
	startNode->isInOpenList = true;
	openSize = 1;
	
	while (!openList[0]->pos.equals(endPos))
	{
		openList[0]->isInOpenList = false;
		openList[0]->isInCloseList = true;
		insertSurToOpen(openList[0]);//将四周结点加入open表
		swap(openList[0], openList[openSize - 1]);
		--openSize;
		//堆排序
		for (int i = openSize / 2 - 1; i >= 0; i--)
		{
			heapify(openList, openSize, i);
		}
	}
	AStarNode *p = openList[0];
	while (p->parent->parent)
	{
		//CCLOG("%f,%f", p->pos.x, p->pos.y);
		p = p->parent;
	}
	return p;
}


void AStar::insertSurToOpen(AStarNode *node)
{
	
	AStarNode *upNode = new AStarNode(node->pos + ccp(0, 1));
	AStarNode *downNode = new AStarNode(node->pos + ccp(0, -1));
	AStarNode *leftNode = new AStarNode(node->pos + ccp(-1, 0));
	AStarNode *rightNode = new AStarNode(node->pos + ccp(1, 0));
	judge(upNode, node);
	judge(downNode, node);
	judge(leftNode, node);
	judge(rightNode, node);
}

//判断后将结点加入open表
void AStar::judge(AStarNode *child, AStarNode *parent)
{
	/*if (child->isInOpenList)
	{
		if (child->g > parent->g + 1)
		{
			child->g = parent->g + 1;
			child->parent = parent;
		}

	}*/
	if (!nodeExist[int(child->pos.x)][int(child->pos.y)])
	{
		nodeExist[int(child->pos.x)][int(child->pos.y)] = true;
	}
	else if (AStarNode *temp= getNodeFromOpenList(child->pos))
	{
		if (temp->g > parent->g + 1)
		{
			temp->g = parent->g + 1;
			temp->parent = parent;
		}
		return;
	}
	if (!isWall(child->pos) && !child->isInOpenList && !child->isInCloseList)
	{
		child->parent = parent;
		child->g = parent->g + 1;
		child->h = abs(endPos.x - child->pos.x) + abs(endPos.y - child->pos.y);
		openList[openSize++] = child;
		child->isInOpenList = true;
	}
}

bool AStar::isWall(CCPoint pos)
{
	return wall[(int)pos.x][(int)pos.y];
}

inline int AStar::sumGH(AStarNode *node)
{
	return node->g + node->h;
}

void AStar::heapify(AStarNode *array[], int size, int elem)
{
	int lChild = elem * 2 + 1;
	int rChild = lChild + 1;
	while (rChild<size)
	{
		if (sumGH(array[lChild]) >= sumGH(array[elem]) && sumGH(array[rChild]) >= sumGH(array[elem]))
		{
			return;
		}
		if (sumGH(array[lChild]) <= sumGH(array[rChild]))
		{
			swap(array[lChild], array[elem]);
			elem = lChild;
		}
		else
		{
			swap(array[rChild], array[elem]);
			elem = rChild;
		}
		lChild = elem * 2 + 1;
		rChild = lChild + 1;
	}
	if (lChild<size&&sumGH(array[lChild])<sumGH(array[elem]))
	{
		swap(array[lChild], array[elem]);
	}
}


AStarNode* AStar::getNodeFromOpenList(CCPoint pos)
{
	for (int i = 0; i < openSize;i++)
		if (openList[i]->pos.equals(pos))
		{
			return openList[i];
		}
	return NULL;
}