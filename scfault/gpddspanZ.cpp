#include "gpdd.h"
#include "option.h"

extern GpddNode* pGpddNodeOne;
extern GpddNode* pGpddNodeZero;

void GPDD::IncludeZ(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& graphMap,GpddNodeMap& gpddnodeMap)
{
	GpddNode* lnode = NULL;
	Edge* edge = node->GetSymbol()->GetEdge();
	Graph* lGraph = NULL;
	Graph* rGraph = NULL;
	int fl = 0, fr = 0;
	int sign = 1;
	int sl = 1;
	int sr = 1;
	pair<GpddNodeMap::iterator,bool> itf;
	
	lGraph = new Graph(*(node->GetLGraph()));

	fl = lGraph->Short(edge,sl);
	if(fl==0)
	{	
		lnode = pGpddNodeZero;
		delete (Graph*) lGraph;
		goto LEFT;
	}

	rGraph = new Graph(*(node->GetRGraph()));

	fr = rGraph->Short(edge,sr);
	if(fr==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		delete rGraph;
		goto LEFT;
	}
	
	sign = sl * sr;
	if(fl==1 && fr==1)
	{
		if(IsTerminated(node->GetSymbol()))
			lnode = pGpddNodeOne;
		else
			lnode = pGpddNodeZero;

		delete lGraph;
		delete rGraph;
		goto LEFT;
	}	
	// if(node->GetSymbol()->Next()==NULL)
		// if this symbol is the last one to process, 
		// then the L & R graph after processing must be empty
	// Hash Graph, left and right

	lGraph = graphMap.GraphShare(lGraph);
	rGraph = graphMap.GraphShare(rGraph);

#ifdef DEBUG_GraphReduction
	cout << "L Graph:" << endl;
	lGraph->Print(cout,1);
	cout << "R Graph:" << endl;
	rGraph->Print(cout,1);
#endif

	// Hash GpddNode
	lnode = new GpddNode(node->GetSymbol()->Next(),lGraph,rGraph);
	/*pair<GpddNodeMap::iterator,bool>*/ itf = gpddnodeMap.insert(make_pair(lnode,lnode));
	if(!itf.second)
	{ 
		GpddNode* tmp_node = itf.first->second;
		delete (GpddNode*) lnode;
		lnode = tmp_node;
	}
	else
	{
		nodeList.push_back(lnode);
		workLayer.push(lnode);
	}	
	
LEFT:	
	node->SetSignL(sign);
	node->SetLeft(lnode);
#ifdef REFERENCE
	lnode->AddRefCount();
#endif
#ifdef DEBUG_SPAN	
	cout << "chjd here, left  node: " << lnode->GetSymbol()->Name() << "\tsign: " << sign << endl;
#endif
}

void GPDD::ExcludeZ(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& graphMap,GpddNodeMap& gpddnodeMap)
{
//cout << "chjd here, exclude z, " << endl;
	GpddNode* lnode = NULL;
	Edge* edge = node->GetSymbol()->GetEdge();
	Graph* lGraph = NULL;
	Graph* rGraph = NULL;
	int fl = 0, fr = 0;
	pair<GpddNodeMap::iterator,bool> itf;

	lGraph = new Graph(*(node->GetLGraph()));
//cout << "lGraph copy done" << endl;

	fl = lGraph->Open(edge);
//cout << "lGraph open done, fl=" << fl <<endl;	
	if(fl==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		goto RIGHT;
	}

	rGraph = new Graph(node->GetRGraph());
//cout << "rGraph copy done" << endl;

	fr = rGraph->Open(edge);
//cout << "rGraph open done, fr=" << fr <<endl;	
	if(fr==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		delete rGraph;
		goto RIGHT;
	}
	
/*
	if(fl==1 && fr==1)
	{
		lnode = pGpddNodeOne;
		delete lGraph;
		delete rGraph;
		return;
	}
*/
/*	if(graphMap.Find(lGraph)!=NULL)
	{
		Graph* tmp = graphMap.Find(lGraph);
		delete (Graph*) lGraph;
		lGraph = tmp;
	}
	else
	{
		graphMap.Add(lGraph);
	}

	if(graphMap.Find(rGraph)!=NULL)
	{
		Graph* tmp = graphMap.Find(rGraph);
		delete (Graph*) rGraph;
		rGraph = tmp;
	}
	else
	{
		graphMap.Add(rGraph);
	}
*/
	lGraph = graphMap.GraphShare(lGraph);
	rGraph = graphMap.GraphShare(rGraph);

#ifdef DEBUG_GraphReduction
	cout << "L Graph:" << endl;
	lGraph->Print(cout,1);
	cout << "R Graph:" << endl;
	rGraph->Print(cout,1);
#endif


	lnode = new GpddNode(node->GetSymbol()->Next(),lGraph,rGraph);
	/*pair<GpddNodeMap::iterator,bool>*/ itf = gpddnodeMap.insert(make_pair(lnode,lnode));
	if(!itf.second)
	{ 
		GpddNode* tmp_node = itf.first->second;
		delete (GpddNode*) lnode;
		lnode = tmp_node;
	}
	else
	{
		nodeList.push_back(lnode);
		workLayer.push(lnode);
	}	
	
RIGHT:
	node->SetRight(lnode);
#ifdef REFERENCE
	lnode->AddRefCount();
#endif
#ifdef DEBUG_SPAN	
	cout << "chjd here, right node: " << lnode->GetSymbol()->Name() << "\tsign: " << 1 << endl;
#endif
}

