#include "gpdd.h"
#include "option.h"

extern GpddNode* pGpddNodeOne;
extern GpddNode* pGpddNodeZero;

void GPDD::IncludeE(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& graphMap,GpddNodeMap& gpddnodeMap)
{
	GpddNode* lnode = NULL;
	Edge* edgeVS = node->GetSymbol()->GetEdge();
	Edge* edgeVC = node->GetSymbol()->GetPairEdge();
	Graph* lGraph = NULL;
	Graph* rGraph = NULL;
	int fl = 0, fr1 = 0, fr2 = 0;
	int sign = 1;
	int sl = 1;
	int sr = 1;
	pair<GpddNodeMap::iterator,bool> itf;
	
	lGraph = new Graph(*(node->GetLGraph()));

	fl = lGraph->Short(edgeVS,sl);
	sl *= -1;	// flip sign when short VS edge
	if(fl==0)
	{	
		lnode = pGpddNodeZero;
		delete (Graph*) lGraph;
		goto LEFT;
	}
	
	rGraph = new Graph(*(node->GetRGraph()));

	fr2 = rGraph->Open(edgeVS);
	if(fr2==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		delete rGraph;
		goto LEFT;
	}

	fr1 = rGraph->Short(edgeVC,sr);
	if(fr1==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		delete rGraph;
		goto LEFT;
	}

	sign = sl * sr;
	if(fl==1 && fr1==1)
	{
		if(IsTerminated(node->GetSymbol()))
			lnode = pGpddNodeOne;
		else
			lnode = pGpddNodeZero;
		delete lGraph;
		delete rGraph;
		goto LEFT;
	}

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
	cout << "chjd here, left  node:" << lnode->GetSymbol()->Name() << "\tsign: " << sign << endl;
#endif
}

void GPDD::ExcludeE(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& graphMap,GpddNodeMap& gpddnodeMap)
{
	GpddNode* lnode = NULL;
	Edge* edgeVS = node->GetSymbol()->GetEdge();
	Edge* edgeVC = node->GetSymbol()->GetPairEdge();
	Graph* lGraph = NULL;
	Graph* rGraph = NULL;
	int fl = 0, fr1 = 0, fr2 = 0;
	int sign = 1;
	int sl = 1;
	int sr = 1;
	pair<GpddNodeMap::iterator,bool> itf;

	lGraph = new Graph(node->GetLGraph());
	fl = lGraph->Short(edgeVS,sl);
	if(fl==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		goto RIGHT;
	}

	rGraph = new Graph(node->GetRGraph());
	fr1 = rGraph->Short(edgeVS,sr);
	if(fr1==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		delete rGraph;
		goto RIGHT;
	}

	sign = sl * sr;
	if(fl==1 && fr1==1)
	{
		if(IsTerminated(node->GetSymbol()))
			lnode = pGpddNodeOne;
		else
			lnode = pGpddNodeZero;
		
		delete lGraph;
		delete rGraph;
		goto RIGHT;
	}

	fr2 = rGraph->Open(edgeVC);
	if(fr2==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		delete rGraph;
		goto RIGHT;
	}

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
RIGHT:	
	node->SetSignR(sign);
	node->SetRight(lnode);
#ifdef REFERENCE
	lnode->AddRefCount();	
#endif
#ifdef DEBUG_SPAN	
	cout << "chjd here, right node:" << lnode->GetSymbol()->Name() << "\tsign: "<< sign << endl;
#endif
}

