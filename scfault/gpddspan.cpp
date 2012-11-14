//#include <pthread.h>
#include <unistd.h>
#include <iostream>
using std::cerr;

#include "gpdd.h"
#include "option.h"

/**
 * @brief GraphReduction BFS
 * 	-	workLayer list used as Queue, so op is push_back/pop_front
 */

bool thread_flag;

void *Statistics(void* arg)
{
	while(thread_flag)
	{
		int cnt = GpddNode::total;
		if(cnt>100)
		{	
			cerr << "node count: " << cnt << endl;
			cerr.flush();
		}
		sleep(3);
	}
}

bool GPDD::IsTerminated(Symbol* symbol)
{
	bool flag = true;
	symbol = symbol->Next();
	while(symbol!=NULL)
	{
		if(symbol->Type()==E || symbol->Type()==F || symbol->Type()==H)
		{	
			flag = false;
			break;
		}
		symbol = symbol->Next();
	}
	return flag;
}

void GPDD::GraphReductionBFS()
{
	GpddNode* node = NULL;
	queue<GpddNode*> layer_0;
	queue<GpddNode*> layer_1;
	GraphMap graphMap_0;
	GraphMap graphMap_1;
	GpddNodeMap nodeMap_0;
	GpddNodeMap nodeMap_1;

	layer_0.push(root);
	layer_0.push(root2);
//	root2->SetLeft(pGpddNodeZero);
//	root2->SetRight(pGpddNodeZero);
	graphMap_0.Add(root->GetLGraph());
	graphMap_0.Add(root->GetRGraph());
	graphMap_0.Add(root2->GetLGraph());
	graphMap_0.Add(root2->GetRGraph());


	while((!layer_0.empty()) || (!layer_1.empty()))
	{
		while(!layer_0.empty())
		{
			node = layer_0.front();
			layer_0.pop();
cout << "to span node:" ;
node->GetSymbol()->Print(cout);
			GraphReductionNodeBFS(node,layer_1,graphMap_1,nodeMap_1);
		}
		graphMap_0.Clear();

		while(!layer_1.empty())
		{
			node = layer_1.front();
			layer_1.pop();
cout << "to span node:" ;
node->Print(cout);
			GraphReductionNodeBFS(node,layer_0,graphMap_0,nodeMap_0);
		}
		graphMap_1.Clear();
	}

	cerr << "node count: " << GpddNode::total << endl;
	cerr << "shared graph count: " << Graph::graphSharedCnt << endl;
}


/**
 * @brief BFS GraphReduction Process for a node
 * 	-	BFS, left node first and right node followed, so push_back left node first, that is Include first, then Exclude
 *
 * @param node
 */
void GPDD::GraphReductionNodeBFS(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap)
{
	if(node->Marked())
		return;
	SymbolType type = node->GetSymbol()->Type();
	switch(type)
	{
		case E:
			{
				IncludeE(node,workLayer,workgraphMap,nodeMap);
				ExcludeE(node,workLayer,workgraphMap,nodeMap);
			}
			break;
		case F:
			{
				IncludeF(node,workLayer,workgraphMap,nodeMap);
				ExcludeF(node,workLayer,workgraphMap,nodeMap);
			}
			break;
		case G:
			{
				if(node->GetSymbol()->Infinity())
				{
					IncludeG(node,workLayer,workgraphMap,nodeMap);
				}
				else
				{
					IncludeG(node,workLayer,workgraphMap,nodeMap);
					ExcludeG(node,workLayer,workgraphMap,nodeMap);
				}
			}
			break;
		case H:
			{
				IncludeH(node,workLayer,workgraphMap,nodeMap);
				ExcludeH(node,workLayer,workgraphMap,nodeMap);
			}
			break;
		default:
			{
				IncludeZ(node,workLayer,workgraphMap,nodeMap);
				ExcludeZ(node,workLayer,workgraphMap,nodeMap);
			}
			break;
	}
	node->SetLGraph(NULL);
	node->SetRGraph(NULL);
	node->Mark(true);
}

/*
void GPDD::GraphReductionBFS()
{
	GpddNode* node = NULL;
	queue<GpddNode*> layer_0;
	queue<GpddNode*> layer_1;
	GraphMap graphMap_0;
	GraphMap graphMap_1;
	GpddNodeMap nodeMap_0;
	GpddNodeMap nodeMap_1;
	layer_0.push(root);
	graphMap_0.Add(root->GetLGraph());
	graphMap_0.Add(root->GetRGraph());

cout << "L Graph:" << endl;
root->GetLGraph()->Print();
cout << "R Graph:" << endl;
root->GetRGraph()->Print();

	pthread_t thread_0;
if(ckt->SymbolCount()>=64)	
{
	thread_flag = true;
#ifdef THREAD
	int pthread_id = pthread_create( &thread_0, NULL,Statistics, NULL);
#endif
}
	while((!layer_0.empty()) || (!layer_1.empty()))
	{
		while(!layer_0.empty())
		{
			node = layer_0.front();
#ifdef DEBUG_GraphReduction
	cout << "chjd here, to GraphReduction node " << node->GetSymbol()->Name() << endl;
	node->Print(cout);
#endif
			layer_0.pop();
			GraphReductionNodeBFS(node,layer_1,graphMap_1,nodeMap_1);

  			cout << "\t\t\tnode: " << node->GetSymbol()->Name() << " " << node;
			cout << "\tleft: " << node->GetLeft()->GetSymbol()->Name() << " " << node->GetLeft();
			cout << "\t\tright: " << node->GetRight()->GetSymbol()->Name() << " " << node->GetRight();
			cout << endl;
		}
		graphMap_0.Clear();
		while(!layer_1.empty())
		{
			node = layer_1.front();
#ifdef DEBUG_GraphReduction
	cout << "chjd here, to GraphReduction node " << node->GetSymbol()->Name() << endl;
	node->Print(cout);
#endif
			layer_1.pop();
			GraphReductionNodeBFS(node,layer_0,graphMap_0,nodeMap_0);

			cout << "\t\t\tnode: " << node->GetSymbol()->Name() << " " << node;
			cout << "\tleft: " << node->GetLeft()->GetSymbol()->Name() << " " << node->GetLeft();
			cout << "\t\tright: " << node->GetRight()->GetSymbol()->Name() << " " << node->GetRight();
			cout << endl;

		}
		graphMap_1.Clear();
	}

	thread_flag = false;
if(ckt->SymbolCount()>=32)
{
#ifdef THREAD
	pthread_join(thread_0,NULL);
#endif
}
	cerr << "node count: " << GpddNode::total << endl;
	cerr << "shared graph count: " << Graph::graphSharedCnt << endl;
//	cerr << "node count from list: " << nodeList.size() << endl;

//	GarbageCollect();
}
*/

/**
 * @brief GraphReduction DFS
 * 	-	workLayer list used as Stack, so op is push_back/pop_back
 */
/*
void GPDD::GraphReductionDFS()
{
	GpddNode* node = NULL;
	workLayer.push_back(root);
	while(!workLayer.empty())
	{
		node = workLayer.back();
#ifdef DEBUG_GraphReduction
	cout << "chjd here, to GraphReduction node " << node->GetSymbol()->Name() << endl;
	node->Print(cout);
#endif
		workLayer.pop_back();
		GraphReductionNodeDFS(node);
	}
}
*/



/**
 * @brief DFS GraphReduction Process
 * 	-	DFS,	stack, last in, first out, so exclude first, then include
 *
 * @param node
 */
/*
void GPDD::GraphReductionNodeDFS(GpddNode* node)
{
	if(node->Marked())
		return;
	SymbolType type = node->GetSymbol()->Type();
	switch(type)
	{
		case E:
			{
				ExcludeE(node);
				IncludeE(node);
			}
			break;
		case F:
			{
				ExcludeF(node);
				IncludeF(node);
			}
			break;
		case G:
			{
				ExcludeG(node);
				IncludeG(node);
			}
			break;
		case H:
			{
				ExcludeH(node);
				IncludeH(node);
			}
			break;
		default:
			{
				ExcludeZ(node);
				IncludeZ(node);
			}
			break;
	}
	node->Mark(true);
}
*/

