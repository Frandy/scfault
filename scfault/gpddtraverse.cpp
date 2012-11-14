#include <stack>
#include <queue>
using std::stack;
using std::queue;

#include "gpdd.h"

#include <iostream>
using std::cout;
using std::endl;

void GPDD::TraverseNodeDFS(GpddNode* node,stack<GpddNode*>& workSpace)
{
	if(!node->Marked())
	{
		workSpace.push(node);
		node->Mark(true);
		if(!node->GetLeft()->Marked())
			TraverseNodeDFS(node->GetLeft(),workSpace);
		if(!node->GetRight()->Marked())
			TraverseNodeDFS(node->GetRight(),workSpace);
	}
}

void GPDD::TraverseNodeBFS(GpddNode* rootnode,stack<GpddNode*>& workSpace)
{
	queue<GpddNode*> nodeQueue;
	nodeQueue.push(rootnode);
	GpddNode* node = NULL;
	while(!nodeQueue.empty())
	{
		node = nodeQueue.front();
		nodeQueue.pop();
		workSpace.push(node);
		if(!node->Marked())
		{
			if(!node->GetLeft()->Marked())
				nodeQueue.push(node->GetLeft());
			if(!node->GetRight()->Marked())
				nodeQueue.push(node->GetRight());
		}
		node->Mark(true);
	}
}

