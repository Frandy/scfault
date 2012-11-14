#ifndef GPDDNODE_TRIPLE_MAP_H
#define GPDDNODE_TRIPLE_MAP_H

#include <unordered_map>
using std::unordered_map;

#include <iostream>
using std::cout;
using std::endl;

#include "gpddnode.h"


class GpddNodeTripleHash
{
	public:
		size_t operator () (const GpddNode* node) const
		{
			int symbId = node->GetSymbol()->Index();
			int leftId = node->GetLeft()->Index();
			int rightId = node->GetRight()->Index();
//			int signL = node->GetSignL();
//			int signR = node->GetSignR();
			size_t value = 0;	//symbId*2729 << 7;
//			value ^= value * leftId * 175447 << signL;
//			value = value * rightId * 2807303 >> signR;
			value = (symbId*symbId)+(leftId*leftId<<8)+(rightId*rightId<<8);
//			value = value%2147483647;
			value = value&0x7FFFFFFF;
			return value;
		}
};

class GpddNodeTripleCompare
{
	public:
		bool operator () (const GpddNode* n1,const GpddNode* n2) const
		{
			if(n1->GetSymbol()->Index() != n2->GetSymbol()->Index())
				return false;
			if(n1->GetLeft()->Index() != n2->GetLeft()->Index())
				return false;
			if(n1->GetRight()->Index() != n2->GetRight()->Index())
				return false;
			if(n1->GetSignL() != n2->GetSignL())
				return false;
			if(n1->GetSignR() != n2->GetSignR())
				return false;
			return true;
		}
};

typedef unordered_map<GpddNode*,GpddNode*,GpddNodeTripleHash,GpddNodeTripleCompare> TripleMap;

/*
class GpddNodeTripleMap
{
	public:
		GpddNode* Find(GpddNode* node)
		{
			unordered_map<GpddNode*,GpddNode*,GpddNodeTripleHash,GpddNodeTripleCompare>::iterator it = tripleMap.find(node);
			if(it!=tripleMap.end())
				return (*it).second;
			else
				return NULL;
		}

		void Add(GpddNode*node)
		{
			cout << "add triple: (" << node->GetSymbol()->Name() << ",";
			cout << node->GetLeft()->GetSymbol()->Name() << ",";
			cout << node->GetRight()->GetSymbol()->Name() << ")";
			cout << "\t" << tripleMap.size() << endl;

			tripleMap[node] = node;
			node->SetIndex(tripleMap.size());
		}
	private:
		unordered_map<GpddNode*,GpddNode*,GpddNodeTripleHash,GpddNodeTripleCompare> tripleMap;
};
*/


#endif
