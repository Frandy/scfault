#include "gpddnode.h"

extern Symbol* pSymbolOne;
extern Symbol* pSymbolZero;
extern GpddNode* pGpddNodeOne;
extern GpddNode* pGpddNodeZero;


GpddNode::GpddNode(SymbolType type)
{
	if(type==ONE)
	{
		symbol = pSymbolOne;
		zsmark = false;
	}
	else if(type==ZERO)
	{	
		symbol = pSymbolZero;
		zsmark = true;
	}
	lGraph = NULL;
	rGraph = NULL;
	pLeft = NULL;
	pRight = NULL;
	signL = 1;
	signR = 1;
	value = symbol->GetCplxValue();
	mark = true;
	pShare = NULL;
	refCount = 0; // 0 is ok ,since it not added to gpddnodeMap	
	coefArray = NULL;

//	cout << "\t\tnode created: " << symbol->Name() << endl;

	total++;
}

GpddNode::GpddNode(Symbol* symbol,Graph* lGraph,Graph* rGraph)
	:symbol(symbol),lGraph(lGraph),rGraph(rGraph)
{
	pLeft = pGpddNodeOne;
	pRight = pGpddNodeZero;
	signL = 1;
	signR = 1;
	mark = false;
	zsmark = false;
	pShare = NULL;
	refCount = 0;
//	cout << "\t\tnode created: " << symbol->Name() << endl;
	total++;
	coefArray = NULL;
}


CPLX GpddNode::Value(bool curValueMark)
{
	if(mark^curValueMark)
		Evaluate(curValueMark);
	return value;
}

void GpddNode::Evaluate(bool curValueMark)
{
	value = symbol->GetCplxValue();
	value *= CPLX(signL,0) * pLeft->Value(curValueMark);
	value += CPLX(signR,0) * pRight->Value(curValueMark);
	mark = curValueMark;
}

void GpddNode::Print(ostream& out)
{
	out << "symbol: ";
	symbol->Print(out);
	out << endl;
	out << "L Graph: " << endl;
	lGraph->Print(out,2);
	out << "R Graph: " << endl;
	rGraph->Print(out,2);
	out << endl;
}

void GpddNode::PrintExp(ostream& out)
{
	if(symbol->Type()==ONE || symbol->Type()==ZERO)
	{
		symbol->PrintSymbol(out);
		return;
	}
	out << "(";
	if(signL<0)
		out << "-";
	symbol->PrintSymbol(out);
	if(pLeft->GetSymbol()->Type()!=ONE)
	{
		out << ".";
		pLeft->PrintExp(out);
	}
	if(pRight->GetSymbol()->Type()!=ZERO)
	{
		if(signR<0)
			out << " - ";
		else
			out << " + ";
		pRight->PrintExp(out);
	}
	out << ")";
}

void GpddNode::PrintNode()
{
	if(symbol->Type()==ONE || symbol->Type()==ZERO)
	{
		cout << "node: " << symbol->Name() << endl;
		return;
	}
	else
	{
		cout << "node: " << symbol->Name();
		cout << " \tsignL:" << signL << " \tleft node: " << pLeft->GetSymbol()->Name();
		cout << " \tsignR:" << signR << " \tright node: " << pRight->GetSymbol()->Name();
		cout << endl;
		pLeft->PrintNode();
		pRight->PrintNode();
	}
//	PrintNode(root);

}

bool operator == (const GpddNode& node1, const GpddNode& node2)
{
	if( *(node1.GetSymbol()) != *(node2.GetSymbol()))
		return false;
	if( *(node1.GetLGraph()) != *(node2.GetLGraph()))
		return false;
	if( *(node1.GetRGraph()) != *(node2.GetRGraph()))
		return false;
	return true;
}

bool operator != (const GpddNode& node1, const GpddNode& node2)
{
	if( *(node1.GetSymbol()) != *(node2.GetSymbol()))
		return true;
	if( *(node1.GetLGraph()) != *(node2.GetLGraph()))
		return true;
	if( *(node1.GetRGraph()) != *(node2.GetRGraph()))
		return true;
	return false;
}


