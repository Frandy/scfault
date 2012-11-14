#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_map>
#include <vector>
using std::list;
using std::vector;
using std::unordered_map;

#include "edge.h"


class Graph
{
	public:
		Graph()		{	}
		//Graph()		{	refCount = 0;	}
		~Graph()	{	}

	// graph copy
		Graph(Graph& graph)			
		{	
			edgeArray = list<Edge>(*(graph.GetEdgeArray()));
			nodeArray = vector<int>(*(graph.GetNodeArray()));
			nodeNum = graph.GetNodeNum();
		}
		Graph(Graph* graph)
		{
			edgeArray = list<Edge>(*(graph->GetEdgeArray()));
			nodeArray = vector<int>(*(graph->GetNodeArray()));
			nodeNum = graph->GetNodeNum();
		}

	// for graph building
		list<Edge>* GetEdgeArray() 	{	return &edgeArray;	}
		vector<int>* GetNodeArray()	{	return &nodeArray;	}
		void SetNodeNum(int n)	{	nodeNum = n;	}
		int GetNodeNum() const	{	return nodeNum;	}
		int GetNewNode(int i) const {	return nodeArray[i];	}
//		void SetupAdjList(unordered_map<int,list<Edge*>>& adjList);
		void SetupNodeArray();

	// ref
	/*
		void AddReference()	{	refCount++;	}
		void SubReference()	{	refCount--;	}
		int GetRefCount()	{	return refCount;	}
	*/

	// graph operation
	size_t Hash() const;
	int Short(Edge* edge,int& sign);
	int ShortWire(Edge* edge,int& sign);
	int Open(Edge* edge);
	int OpenWire(Edge* edge);
//	bool IsConnect();
	pair<int,int> GraphSize() const	{	return pair<int,int>(edgeArray.size(),nodeNum);	}

	void Print(ostream& out=cout, int sel=0);

	friend bool operator == (const Graph& g1,const Graph& g2);
	friend bool operator != (const Graph& g1,const Graph& g2);

		static int graphSharedCnt;
	private:
		list<Edge> edgeArray;
//		int refCount;
//		list<int> nodeArray;
		vector<int> nodeArray;
		int nodeNum;
};

#endif

