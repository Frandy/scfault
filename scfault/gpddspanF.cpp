#include "gpdd.h"
#include "option.h"

extern GpddNode* pGpddNodeOne;
extern GpddNode* pGpddNodeZero;

void GPDD::IncludeF(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& graphMap,GpddNodeMap& gpddnodeMap)
{
	GpddNode* lnode = NULL;
	Edge* edgeCS = node->GetSymbol()->GetEdge();
	Edge* edgeCC = node->GetSymbol()->GetPairEdge();
	Graph* lGraph = NULL;
	Graph* rGraph = NULL;
	int fl1 = 0, fl2 = 0, fr1 = 0;
	int sign = 1;
	int sl = 1;
	int sr = 1;
	pair<GpddNodeMap::iterator,bool> itf; 
	lGraph = new Graph(*(node->GetLGraph()));
//cout << "chjd here, Include F error" << endl;
	fl1 = lGraph->Short(edgeCS,sl);
//cout << "chjd here, Include F error, after short CS, fl1 = " << fl1 << endl;	
	if(fl1==0)
	{	
		lnode = pGpddNodeZero;
		delete (Graph*) lGraph;
		goto LEFT;
	}
//cout << "chjd here, Include F error, to open CC" << endl;	
//lGraph->Print(cout);
	fl2 = lGraph->Open(edgeCC);
//cout << "chjd here, Include F error, after open CC, fl2 = " << fl2 << endl;	
	if(fl2==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		goto LEFT;
	}

	rGraph = new Graph(*(node->GetRGraph()));

	fr1 = rGraph->Short(edgeCC,sr);
//cout << "chjd here, Include F error, after R short CC, fr1 = " << fr1 << endl;	
	if(fr1==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		delete rGraph;
		goto LEFT;
	}

	sign = sl * sr;
	if(fl1==1 && fr1==1)
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

void GPDD::ExcludeF(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& graphMap,GpddNodeMap& gpddnodeMap)
{

//cout << "chjd here, Exclude F error" << endl;	

	GpddNode* lnode = NULL;
	Edge* edgeCS = node->GetSymbol()->GetEdge();
	Edge* edgeCC = node->GetSymbol()->GetPairEdge();
	Graph* lGraph = NULL;
	Graph* rGraph = NULL;
	int fl1 = 0, fl2 = 0, fr1 = 0;
	int sign = 1;
	int sl = 1;
	int sr = 1;
	pair<GpddNodeMap::iterator,bool> itf;
	lGraph = new Graph(*(node->GetLGraph()));

//cout << "to open edgeCS, "; edgeCS->Print(cout); cout << endl;
	fl2 = lGraph->Open(edgeCS);
//cout << "chjd here, Exclude F error, after L Open CS, fl2 = " << fl2 << endl;	
	if(fl2==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		goto RIGHT;
	}

	fl1 = lGraph->Short(edgeCC,sl);
//cout << "chjd here, Exclude F error, after L short CC, fl1 = " << fl1 << endl;	
	if(fl1==0)
	{	
		lnode = pGpddNodeZero;
		delete (Graph*) lGraph;
		goto RIGHT;
	}

	rGraph = new Graph(*(node->GetRGraph()));
	fr1 = rGraph->Short(edgeCC,sr);
//cout << "chjd here, Exclude F error, after R short CC, fr1 = " << fr1 << endl;	
	if(fr1==0)
	{
		lnode = pGpddNodeZero;
		delete lGraph;
		delete rGraph;
		goto RIGHT;
	}

	sign = sl * sr;
	if(fl1==1 && fr1==1)
	{
		if(IsTerminated(node->GetSymbol()))
			lnode = pGpddNodeOne;
		else
			lnode = pGpddNodeZero;
		delete lGraph;
		delete rGraph;
		goto RIGHT;
	}

//cout << "chjd here, Exclude F error" << endl;	
//	lGraph = graphMap.GraphShare(lGraph);
//	rGraph = graphMap.GraphShare(rGraph);

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
	
//cout << "chjd here, Exclude F error" << endl;	

RIGHT:
//cout << "chjd here, Exclude F error, goto Right here" << endl;	
	node->SetSignR(sign);
	node->SetRight(lnode);
#ifdef REFERENCE
	lnode->AddRefCount();
#endif
#ifdef DEBUG_SPAN	
	cout << "chjd here, right node:" << lnode->GetSymbol()->Name() << "\tsign: "<< sign << endl;
#endif
}
