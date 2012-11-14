#ifndef _PARALLEL_EDGE_MAP_H
#define _PARALLEL_EDGE_MAP_H

#include <unordered_map>
#include <utility>
using std::unordered_map;
using std::pair;

#include "symbol.h"

class ParallelEdgeHash
{
	public:
		size_t operator () (const pair<int,int>& node) const
		{
			size_t value = 0;
			int n1 = node.first+1;
			int n2 = node.second+1;
			value = (n1+n2)*(n1*n2);
			value = value%163;
			return value;
		}
};

class ParallelEdgeCompare
{
	public:
		bool operator () (const pair<int,int>& n1,const pair<int,int>& n2) const
		{
			if(n1.first==n2.first && n1.second==n2.second)
				return true;
			if(n1.second==n2.first && n1.first==n2.second)
				return true;
			return false;
		}
};

class ParallelEdgeMap
{
	public:
		ParallelEdgeMap()	{	cnt = 0;	}
		Symbol* Find(Symbol* symbol)
		{
			unordered_map<pair<int,int>,Symbol*,ParallelEdgeHash,ParallelEdgeCompare>::iterator it;
			pair<int,int> node = symbol->GetEdge()->Node();
			it = parallelEdgeMap.find(node);
			if(it!=parallelEdgeMap.end())
			{
				Symbol* symbol = (*it).second;
				if(symbol->ParallelMark()<=0)
					symbol->SetParallelMark(++cnt);
				return symbol;
			}
			else
				return NULL;
		}

		void Add(Symbol* symbol)
		{
			parallelEdgeMap[symbol->GetEdge()->Node()] = symbol;
		}

	private:
		unordered_map<pair<int,int>,Symbol*,ParallelEdgeHash,ParallelEdgeCompare> parallelEdgeMap;
		int cnt;
		
};

#endif
