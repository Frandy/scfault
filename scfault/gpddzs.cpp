#include <stack>
using std::stack;

#include "gpdd.h"

extern GpddNode* pGpddNodeZero;
extern GpddNode* pGpddNodeOne;

int curZSmark = false;

void GPDD::ZeroSuppressNode(GpddNode* node)
{
	if(node->Marked()==curZSmark)
		return;
	node->Mark(curZSmark);
	GpddNode* left = node->GetLeft();
	GpddNode* right = node->GetRight();
	if(left->Marked()!=curZSmark)
		ZeroSuppressNode(left);
	if(right->Marked()!=curZSmark)
		ZeroSuppressNode(right);
	if(left->GetSymbol()->Type()==ZERO)
	{
		node->ZSMark(true);
	}
	else if(left->ZSMarked())
	{
		node->SetLeft(left->GetRight());
		node->SetSignL(node->GetSignL()*left->GetSignR());
		if(node->GetLeft()->ZSMarked())
		{
			node->ZSMark(true);
		}
	}
	if(right->ZSMarked() && right->GetSymbol()->Type()!=ZERO)
	{
		node->SetRight(right->GetRight());
		node->SetSignR(node->GetSignR()*right->GetSignR());
	}
}


void GPDD::ZeroSuppressRecursive()
{
//cout << "zero suppressing..." << endl;

	curZSmark = !root->Marked();
	pGpddNodeZero->Mark(curZSmark);
	pGpddNodeOne->Mark(curZSmark);

	ZeroSuppressNode(root);
	ZeroSuppressNode(root2);
//	root->Mark(!curZSmark);
}


/*
GpddNode* GPDD::ZeroSuppressNodeS(GpddNode* node,int& sign)
{
//	cout << "to zs node: " << node->GetSymbol()->Name() << "  mark:" << node->Marked() << "  zs mark:" << node->ZSMarked() << endl;
	if(node->Marked())
	{
		if(node->GetSymbol()->Type()==ZERO)
		{
//			cout << "return: " << node->GetSymbol()->Name() << endl;
			return node;
		}
		else if(node->ZSMarked())
		{	
//			cout << "return: " << node->GetRight()->GetSymbol()->Name() << endl;
			return node->GetRight();
		}
		else
		{
//			cout << "return: " << node->GetSymbol()->Name() << endl;
			return node;
		}
	}
	node->Mark(true);
	GpddNode* left = node->GetLeft();
	GpddNode* right = node->GetRight();
	int sl = node->GetSignL();
	int sr = node->GetSignR();

cout << "before zs:" << endl;	
cout << "zs process node: " << node->GetSymbol()->Name() << endl;
cout << "\tleft : " << left->GetSymbol()->Name() << " sign: " << sl << endl;
cout << "\tright: " << right->GetSymbol()->Name() << " sign: " << sr << endl; 

//	if(!left->Marked())
		left = ZeroSuppressNodeS(left,sl);
//	if(!right->Marked())
		right = ZeroSuppressNodeS(right,sr);
//	cout << "before zs, node: " << node->GetSymbol()->Name() << "  left:" << node->GetLeft()->GetSymbol()->Name() << "  right:" << node->GetRight()->GetSymbol()->Name() << endl;

	node->SetLeft(left);
	node->SetSignL(sl);
	node->SetRight(right);
	node->SetSignR(sr);

	if(left->GetSymbol()->Type()==ZERO)
	{
		node->ZSMark(true);
		sign *= node->GetSignR();
#ifdef REFERENCE
		node->SubRefCount();
#endif
		return right;
	}
	else
	{
		return node;
	}
}
*/


/*
void GPDD::ZeroSuppress()
{
//	list<GpddNode*> workSpace;
	// if span BFS, then get workSpace filled at the same time as node poped
	// so push_back, pop_back;
	GpddNode* node = NULL;
	GpddNode* left = NULL;
	GpddNode* right = NULL;
	GpddNode* leftRight = NULL;
	int sign = 1;

	stack<GpddNode*> workSpace;
	MarkAll(false);
	TraverseNodeBFS(root,workSpace);
	
	MarkAll(false);

//			cout << "before gc, node count: " << gpddnodeMap.Size() << endl;
	while(!workSpace.empty())
	{
		node = workSpace.top();
		workSpace.pop();
	
		if(node->Marked())
			continue;
		left = node->GetLeft();
		right = node->GetRight();
		
		if(left->GetSymbol()->Type()==ZERO)
		{
			node->ZSMark(true);
#ifdef REFERENCE
			left->SubRefCount();
			node->GetRight()->SubRefCount();
#endif		
		}
		else if(left->ZSMarked())
		{
#ifdef REFERENCE			
			left->SubRefCount();
#endif
			leftRight = left->GetRight();

			// leftRight = NULL
			if(leftRight->ZSMarked())
			{
				node->ZSMark(true);
#ifdef REFERENCE
				node->GetRight()->SubRefCount();
#endif
				//node->SetLeft(pGpddNodeZero);
				//pGpddNodeZero->AddRefCount();
			}
			else
			{
				sign = (node->GetSignL()) * (left->GetSignR());
				node->SetLeft(leftRight);
				node->SetSignL(sign);
#ifdef REFERENCE				
				leftRight->AddRefCount();
#endif
			}
#ifdef DELETE_ON_FLY
			if(left->RefCount()<=0)
				delete (GpddNode*) left;
#endif
		}
		if(right->ZSMarked() && right->GetSymbol()->Type()!=ZERO)
		{
#ifdef REFERENCE			
			right->SubRefCount();
#endif
			node->SetRight(right->GetRight());
			node->SetSignR(node->GetSignR()*right->GetSignR());
#ifdef REFERENCE			
			right->GetRight()->AddRefCount();
#endif
#ifdef DELETE_ON_FLY	
			if(right->RefCount()<=0)
				delete (GpddNode*) right;
#endif
		}
		node->Mark(true);

	}
#ifndef DELETE_ON_FLY	
//	GarbageCollect();
// do after reduce
#endif
//			cout << "after gc, node count: " << gpddnodeMap.Size() << endl;
}
*/



/*
void GPDD::ZeroSuppressInList()
{
	list<GpddNode*>::reverse_iterator it = nodeList.rbegin();
	GpddNode* node = NULL;
	bool curZSMark = !root->Marked();
	pGpddNodeOne->Mark(curZSMark);
	pGpddNodeZero->Mark(curZSMark);
	for(;it!=nodeList.rend();it++)
	{
		node = (*it);
		if(node->Marked()==curZSMark)
			continue;
		else
		{
			node->Mark(curZSMark);
			GpddNode* left = node->GetLeft();
			GpddNode* right = node->GetRight();
			if(left->GetSymbol()->Type()==ZERO)
			{
				node->ZSMark(true);
			}
			else if(left->ZSMarked())
			{
				node->SetLeft(left->GetRight());
				node->SetSignL(node->GetSignL()*left->GetSignR());
				if(node->GetLeft()->ZSMarked())
				{
					node->ZSMark(true);
				}
			}
		
			if(right->ZSMarked() && right->GetSymbol()->Type()!=ZERO)
			{
				node->SetRight(right->GetRight());
				node->SetSignR(node->GetSignR()*right->GetSignR());
			}
		}
	}
	GarbageCollect();
}
*/

