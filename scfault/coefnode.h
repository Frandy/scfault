#ifndef COEFNODE_H_
#define COEFNODE_H_

#include <vector>

#include "gpddnode.h"
class GpddNode;

class CoefNode{
	public:
		vector<int> spower;
		vector<GpddNode*> scoef;
	public:
		CoefNode(){}
};


#endif
