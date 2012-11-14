#include <stack>
using std::stack;

#include <iostream>
#include <utility>
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

#include "gpdd.h"
#include "gpddnodeTripleMap.h"

extern GpddNode* pGpddNodeZero;
extern GpddNode* pGpddNodeOne;

bool curReduceMark = false;

void GPDD::ReduceNode(GpddNode* node,TripleMap& tripleMap,int& tripleCnt)
{
	if(node->Marked()==curReduceMark)
		return;

	GpddNode* left = node->GetLeft();
	if(left->Marked()!=curReduceMark)
		ReduceNode(left,tripleMap,tripleCnt);
	GpddNode* right = node->GetRight();
	if(right->Marked()!=curReduceMark)
		ReduceNode(right,tripleMap,tripleCnt);

	if(left->ZSMarked())
		node->SetLeft(left->GetShare());
	if(right->ZSMarked())
		node->SetRight(right->GetShare());

	pair<TripleMap::iterator,bool> itf = tripleMap.insert(make_pair(node,node));
	GpddNode* tmp = itf.first->second;

	if(itf.second)
	{	
		node->SetIndex(tripleCnt++);
	}
	else
	{
		node->ZSMark(true);
		node->SetShare(tmp);
	}
	node->Mark(curReduceMark);
	return;
}

void GPDD::ReduceR()
{
//cout << "reducing..." << endl;	
	TripleMap tripleMap;
	int tripleCnt = 0;
	curReduceMark = !root->Marked();
	pGpddNodeZero->SetIndex(tripleCnt++);
	pGpddNodeOne->SetIndex(tripleCnt++);
	pGpddNodeZero->Mark(curReduceMark);
	pGpddNodeZero->SetShare(pGpddNodeZero);
	pGpddNodeOne->Mark(curReduceMark);

	ReduceNode(root,tripleMap,tripleCnt);
	ReduceNode(root2,tripleMap,tripleCnt);
}

