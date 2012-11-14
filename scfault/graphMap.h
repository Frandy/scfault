#ifndef GRAPH_MAP_H
#define GRAPH_MAP_H

#include <unordered_map>
#include <utility>
using std::pair;
using std::make_pair;
using std::unordered_map;

#include <iostream>
using std::cout;
using std::endl;

#include "graph.h"

#ifndef GRAPH_HASH_PRIME
#define GRAPH_HASH_PRIME 5614657
#endif

class GraphHash
{
	public:
		size_t operator () (const Graph* graph) const
		{
			return graph->Hash();	
		}
};

class GraphCompare
{
	public:
		bool operator () (const Graph* g1,const Graph* g2) const
		{
			return (g1==g2 || (*g1==*g2));
		}
};

typedef unordered_map<Graph*,Graph*,GraphHash,GraphCompare> GraphMapMap;
class GraphMap
{
	public:
		GraphMap()	{	}
		~GraphMap()	
		{
			unordered_map<Graph*,Graph*,GraphHash,GraphCompare>::iterator it = graphMap.begin();
			for(;it!=graphMap.end();it++)
			{
				delete (Graph*) (it->first);
			}
		}

		void Add(Graph* graph)
		{
			graphMap.insert(make_pair(graph,graph));
		}

		Graph* GraphShare(Graph* graph)
		{
			//unordered_map<Graph*,Graph*,GraphHash,GraphCompare>::iterator it = graphMap.find(graph);
			pair<GraphMapMap::iterator,bool> itf = graphMap.insert(make_pair(graph,graph));
			if(!itf.second)
			{
				Graph::graphSharedCnt++;
/*
cout << "graph shared:" << endl;
graph->Print(cout,1);
*/
				delete (Graph*) graph;
			}
			return itf.first->second;
		}

		void Clear()
		{
			unordered_map<Graph*,Graph*,GraphHash,GraphCompare>::iterator it = graphMap.begin();
			for(;it!=graphMap.end();it++)
			{
				delete (Graph*) (*it).second;
			}
			graphMap.clear();
		}


	private:
		unordered_map<Graph*,Graph*,GraphHash,GraphCompare> graphMap;
};


#endif

