#ifndef GPDDNODE_MAP_H
#define GPDDNODE_MAP_H

#include <unordered_map>
using std::unordered_map;
#include <time.h>

#include "gpddnode.h"

#include <iostream>
using std::cout;
using std::endl;

#ifndef GPDD_HASH_PRIME
#define GPDD_HASH_PRIME 5614657 
#endif

class GpddNodeHash
{
	public:
		size_t operator () (const GpddNode* node) const
		{
			Symbol* index = node->GetSymbol();
			Graph* pL = node->GetLGraph();
			Graph* pR = node->GetRGraph();
			int value = (((unsigned int)pL<<7) + ((unsigned int)pR)) + ((unsigned int)index);
		//	return (value % GPDD_HASH_PRIME);
			return (value&0x7FFFFFFF);
		}
};

class GpddNodeCompare
{
	public:
		bool operator () (const GpddNode* node1, const GpddNode* node2) const
		{
			return (node1==node2 || *node1 == *node2);
		}
};

typedef unordered_map<GpddNode*,GpddNode*,GpddNodeHash,GpddNodeCompare> GpddNodeMap;
/*
class GpddNodeMap
{
	public:
		GpddNode* Find(GpddNode* node)
		{
			if(gpddnodeMap.find(node)!=gpddnodeMap.end())
			{
				return gpddnodeMap[node];
			}
			else
				return NULL;
		}

		void Add(GpddNode* node)
		{
			gpddnodeMap[node] = node;
		}

		void GpddNodeShare(GpddNode* node)
		{
			unordered_map<GpddNode*,GpddNode*,GpddNodeHash,GpddNodeCompare>::iterator it = gpddnodeMap.find(node);
			if(it!=gpddnodeMap.end())
			{
				delete (GpddNode*) node;
				node = (*it).second;
			}
			else
			{
				gpddnodeMap[node] = node;
			}
		}

		void MarkAll(bool ok)
		{
			unordered_map<GpddNode*,GpddNode*,GpddNodeHash,GpddNodeCompare>::iterator it = gpddnodeMap.begin();
			for(;it!=gpddnodeMap.end();it++)
				(*it).second->Mark(ok);

		}

		void DebugRefCount()
		{
			unordered_map<GpddNode*,GpddNode*,GpddNodeHash,GpddNodeCompare>::iterator it = gpddnodeMap.begin();
			GpddNode* node = NULL;
			for(;it!=gpddnodeMap.end();it++)
			{
				node = (*it).second;
				cout << "\tnode: " << node->GetSymbol()->Name();
				cout << "\tzsmark: " << node->ZSMarked();
				cout << "\trefCount: " << node->RefCount() << endl;
			}
		}

		void GarbageCollect()
		{
clock_t t0 = clock();
			unordered_map<GpddNode*,GpddNode*,GpddNodeHash,GpddNodeCompare>::iterator it = gpddnodeMap.begin();
			GpddNode* node = NULL;
			for(;it!=gpddnodeMap.end();it++)
			{
				node = (*it).second;
				if(node->RefCount()<=0)
				{
					delete (GpddNode*) node;
					gpddnodeMap.erase(it);
				}
			}
clock_t t1 = clock();
cerr << "garbage collection takes time: " << (double(t1-t0)/CLOCKS_PER_SEC) << endl;

		}

		size_t Size() const	
		{
			return gpddnodeMap.size();
		}

	private:
		unordered_map<GpddNode*,GpddNode*,GpddNodeHash,GpddNodeCompare> gpddnodeMap;
		
};
*/
	//	unordered_map<pair<Symbol*,pair<Graph*,Graph*>>,GpddNode*,GpddNodeHash,GpddNodeCompare> gpddNodeMap;

		
#endif
