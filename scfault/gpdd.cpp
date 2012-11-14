#include "gpdd.h"

#include "option.h"
#ifdef DEBUG
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#endif

GpddNode* pGpddNodeOne;
GpddNode* pGpddNodeZero;

void GPDD::SetupGpddNodeOneZero()
{
	pGpddNodeOne = new GpddNode(ONE);
	pGpddNodeZero = new GpddNode(ZERO);
}


void GPDD::PostProcessRoot()
{
	// for l r graph of root, short edge of root2
	// for l r graph of root2, short edge of root
	int sign = 0;
	root->GetLGraph()->ShortWire(root2->GetSymbol()->GetEdge(),sign);
	root->GetRGraph()->ShortWire(root2->GetSymbol()->GetEdge(),sign);
	root->GetRGraph()->OpenWire(root2->GetSymbol()->GetPairEdge());

	root2->GetLGraph()->ShortWire(root->GetSymbol()->GetEdge(),sign);
	root2->GetRGraph()->ShortWire(root->GetSymbol()->GetEdge(),sign);
	root2->GetRGraph()->OpenWire(root->GetSymbol()->GetPairEdge());

}


void GPDD::InitRoot()
{
	Symbol* symbolX = ckt->GetSymbolX();
	Graph* lGraph = new Graph();
	Graph* rGraph = new Graph();
cerr << "to create LR Graph" << endl;	
	ckt->CreateLRGraph(lGraph,rGraph);
	ckt->SetupSymbolOneZero();
	SetupGpddNodeOneZero();
	root = new GpddNode(symbolX,lGraph,rGraph);
	
	Symbol* symbolX2 = symbolX->Next();
	Graph* lGraph2 = new Graph(lGraph);
	Graph* rGraph2 = new Graph(rGraph);
	root2 = new GpddNode(symbolX2,lGraph2,rGraph2);
//	symbolX->Print();
//	symbolX2->Print();

	root->Print();
//	root2->Print();

	ProcessOpamp();

	root->Print();
//	root2->Print();
	
	symbolX->SetNext(symbolX2->Next());
	PostProcessRoot();

	
	root->Print();
//	root2->Print();

// root short s5
/*
	int sign = 1;
	Symbol* s5_1 = symbolX2->Next();
	Symbol* s5_2 = s5_1->Next();
	root->GetLGraph()->ShortWire(s5_1->GetEdge(),sign);
	root->GetRGraph()->ShortWire(s5_1->GetPairEdge(),sign);

	s5_1->Print();
	cout << "s5 1 was short" << endl;


	root->GetLGraph()->ShortWire(s5_2->GetEdge(),sign);
	root->GetRGraph()->ShortWire(s5_2->GetPairEdge(),sign);

	s5_2->Print();
	cout << "s5 2 was short" << endl;


	cout << "short s5" << endl;	
	root->Print();

	symbolX->SetNext(s5_2->Next());
	cout << "following symbols" << endl;
	s5_2->Next()->Print();
	s5_2->Next()->Next()->Print();
	s5_2->Next()->Next()->Next()->Print();
*/
	root->AddRefCount();
	root2->AddRefCount();

	nodeList.push_back(root);
//	nodeList.push_back(root2);
	cout << "root init done" << endl;
}

void GPDD::ProcessOpamp()
{
	Edge* edge = NULL;
	Edge* pairedge = NULL; 
	int sign = 1;
#ifdef DEBUG_OPAMP
	root->GetLGraph()->Print(cout,1);
	root->GetRGraph()->Print(cout,1);
#endif
/*	
	cout << "to process switch list" << endl;	
	list<Symbol*>* switchList = ckt->GetSwitchList();
	if(!switchList->empty())
	{
		list<Symbol*>::iterator swit = switchList->begin();
		for(;swit!=switchList->end();swit++)
		{
			edge = (*swit)->GetEdge();
			root->GetLGraph()->Short(edge,sign);
			root->GetRGraph()->Short(edge,sign);		
		}
	}
*/		
	list<Symbol*>* opampList = ckt->GetOpampList();
	if(!opampList->empty())
	{
//	list<Symbol*>::reverse_iterator opampit = opampList->rbegin();
		list<Symbol*>::iterator opampit = opampList->begin();
		for(;opampit!=opampList->end();opampit++)
		{
			edge = (*opampit)->GetEdge();
/*			if((*opampit)->Type()==VS)
			{	
				root->GetLGraph()->Short(edge,sign);
				root->GetRGraph()->Short(edge,sign);
				continue;
			}
*/			
			pairedge = (*opampit)->GetPairEdge();
			root->GetLGraph()->Short(edge,sign);
			root->GetRGraph()->Short(pairedge,sign);

			root2->GetLGraph()->Short(edge,sign);
			root2->GetRGraph()->Short(pairedge,sign);
		}
	}

#ifdef DEBUG_OPAMP
	cout << "after process:" << endl;
	root->GetLGraph()->Print(cout,1);
	root->GetRGraph()->Print(cout,1);
#endif
}

void GPDD::MarkAll(bool ok)
{
	list<GpddNode*>::iterator it = nodeList.begin();
	for(;it!=nodeList.end();it++)
	{
		(*it)->Mark(ok);
	}
}

void GPDD::GarbageCollect()
{
	list<GpddNode*>::iterator it = nodeList.begin();
	for(;it!=nodeList.end();it++)
	{
		if((*it)->ZSMarked())
		{
			delete (GpddNode*) (*it);
			nodeList.erase(it);
			it--;
		}
	}
	cerr << "node count: " << GpddNode::total/*nodeList.size()*/ << endl;
}

void GPDD::PrintExp(ostream& out)
{
	out << "numerator:" << endl;
	out << "\t";
	int sign = root->GetSignL() ;//* root->GetSignR();
	if(sign<0)
		out << " - ";
	root->GetLeft()->PrintExp(out);
	out << endl;
	out << "denominator:" << endl;
	out << "\t";
	sign = root->GetSignR();
	if(sign<0)
		out << " - "; 
	root->GetRight()->PrintExp(out);
	out << endl;

	out << "root 2" << endl;
	out << "numerator:" << endl;
	out << "\t";
	sign = root2->GetSignL() ;//* root->GetSignR();
	if(sign<0)
		out << " - ";
	root2->GetLeft()->PrintExp(out);
	out << endl;
	out << "denominator:" << endl;
	out << "\t";
	sign = root2->GetSignR();
	if(sign<0)
		out << " - "; 
	root2->GetRight()->PrintExp(out);
	out << endl;
}

void GPDD::PrintNode()
{
	root->PrintNode();
}

void GPDD::PrintTerm()
{
	list<GpddNode*> termPath;
	int sign = -1;

	cout << "numerator:" << endl;
	GpddNode* left = root->GetLeft();
	sign *= root->GetSignL();//*root->GetSignR();
	PrintTermR(termPath,sign,left);

	cout << "denominator:" << endl;
	termPath.clear();
	left = root->GetRight();
	sign = root->GetSignR();
	//sign = 1;
	PrintTermR(termPath,sign,left);

	if(root2==NULL)
		return;

	cout << "root 2:" << endl;
	sign = -1;
	termPath.clear();
	cout << "numerator:" << endl;
	left = root2->GetLeft();
	sign *= root2->GetSignL();//*root->GetSignR();
	PrintTermR(termPath,sign,left);

	cout << "denominator:" << endl;
	termPath.clear();
	left = root2->GetRight();
	sign = root2->GetSignR();
	//sign = 1;
	PrintTermR(termPath,sign,left);

}

void PrintTermPath(ostream& out, list<GpddNode*> &termPath, int &sign)
{
	if(termPath.empty())
	{
		out << "1" << endl;
		return;
	}

	if(sign<0)
		out << " -  ";
	else
		out << " +  ";

	list<GpddNode*>::iterator it = termPath.begin();
	for(;it!=termPath.end();it++)
	{
		out << (*it)->GetSymbol()->Name() << ".";
	}
	out << endl;
}

bool GPDD::PrintTermR(list<GpddNode*>& termPath,int &sign,GpddNode* node)
{

//	cout << "to visit node:" << node->GetSymbol()->Name() << "\tsign:"<< sign << endl;

	if(node->GetSymbol()->Type()==ONE)
	{
		PrintTermPath(cout,termPath,sign);
		return true;
	}
	else if(node->GetSymbol()->Type()==ZERO)
		return false;
	else
	{
		bool flag = false;
		termPath.push_back(node);
//		cout << "push node:" << node->GetSymbol()->Name() << endl;
		GpddNode* left = node->GetLeft();
/*		if(left->GetSymbol()->Type()==ONE)
		{
			sign *= node->GetSignL();
			flag = true;
			PrintTermPath(cout,termPath,sign);
		}
		else
*/		{
//			termPath.push_back(left);
//			cout << "push left:" << left->GetSymbol()->Name() << endl;
			sign *= node->GetSignL();
			PrintTermR(termPath,sign,left);
			/*
			flag = PrintTermR(termPath,sign,left);
			if(flag)
				PrintTermPath(cout,termPath,sign);
			*/
		}

		termPath.pop_back();
//		cout << "pop back" << endl;
		sign *= node->GetSignL(); 

		left = node->GetRight();
/*		if(left->GetSymbol()->Type()==ONE)
		{
			sign *= node->GetSignR();
			flag = true;
			PrintTermPath(cout,termPath,sign);
		}
		else if(left->GetSymbol()->Type()==ZERO)
		{
			flag = false;
		}
		else
*/		{
//			termPath.push_back(left);
//			cout << "push right:" << left->GetSymbol()->Name() << endl;
			sign *= node->GetSignR();
			PrintTermR(termPath,sign,left);
		}
		return flag;
	}
}
