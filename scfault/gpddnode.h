#ifndef GPDDNODE_H
#define GPDDNODE_H

#include "symbol.h"
#include "ckt.h"
#include "graph.h"
#include "cplx.h"
#include "coefnode.h"

class CoefNode;

#include "option.h"
#ifdef DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif



class GpddNode
{
	public:
		GpddNode(SymbolType type);
		GpddNode(Symbol* symbol,Graph* lgraph=NULL,Graph* rGraph=NULL);
		~GpddNode() {	
			total--; }

		Symbol* GetSymbol() const		{	return symbol;	}
		Graph* GetLGraph() const		{	return lGraph;	}
		Graph* GetRGraph() const 		{	return rGraph;	}
		GpddNode* GetLeft() const		{	return pLeft;	}
		int GetSignL() const			{	return signL;	}
		int GetSignR() const			{	return signR;	}
		GpddNode* GetRight() const		{	return pRight;	}
		int Index() const				{	return index;	}
		int Marked() const				{	return mark;	}
		bool ZSMarked() const			{	return zsmark;	}
		GpddNode* GetShare() const		{	return pShare;	}
		int RefCount() const 			{	return refCount;	}

		int GetInfinityOrder() const {return infinityOrder;}
		void SetInfinityOrder(int order)	{infinityOrder = order;}

		void Print(ostream& out=cout);
		void PrintNode();
		void PrintExp(ostream& out=cout);

		CPLX Value(bool curValueMark=true);
		CPLX GetValue() const			{	return value;	}
		void SetValue(CPLX v)	{	value = v;	}
		void Evaluate(bool curValueMark=true);

		void SetSymbol(Symbol* symb)	{	symbol = symb;	}
		void SetLGraph(Graph* l)		{	lGraph = l;		}
		void SetRGraph(Graph* r)		{	rGraph = r;		}
		void SetLeft(GpddNode* node)	{	pLeft = node;	}
		void SetRight(GpddNode* node)	{	pRight = node;	}
		void SetSignL(int sign)			{	signL = sign; 	}
		void SetSignR(int sign)			{	signR = sign;	}
		void SetIndex(int key)			{	index = key;	}
		void Mark(int ok)				{	mark = ok;		}
		void ZSMark(bool ok)			{	zsmark = ok;	}
		void SetShare(GpddNode* node)	{	pShare = node;	}

		void AddRefCount()				
		{	
			refCount++;		
		}
		void SubRefCount()				
		{	
			refCount--;		
		}

		friend bool operator == (const GpddNode& node1, const GpddNode& node2);
		friend bool operator != (const GpddNode& node1, const GpddNode& node2);

	static long int total;

		void SetCoef(CoefNode* coef)	{ coefArray = coef;
		}
		CoefNode*  GetCoef() const {	return coefArray;
		}

	private:
		Symbol* symbol;
		Graph* lGraph;
		Graph* rGraph;
		GpddNode* pLeft;
		GpddNode* pRight;
		int signL;
		int signR;
		CPLX value;
		int mark;
		bool zsmark;
		GpddNode* pShare;
		int index;
		int refCount;	// for GC
		int infinityOrder;
		CoefNode* coefArray;

};

#endif
