#ifndef GPDD_H
#define GPDD_H

#include <stack>
#include <queue>
#include <utility>
using std::pair;
using std::make_pair;
using std::stack;
using std::queue;

#include "ckt.h"
#include "gpddnode.h"
#include "gpddnodeMap.h"
#include "graphMap.h"
#include "gpddnodeTripleMap.h"

class GPDD
{
	public:
		GPDD(CKT* ckt):ckt(ckt)	{	root = NULL;	}
		~GPDD()	{	}

		void SetupGpddNodeOneZero();
		void InitRoot();

		void ProcessOpamp();
		void GraphReductionDFS();
		void GraphReductionBFS();
				
	//	void ZeroSuppress();
		void ZeroSuppressRecursive();
		void ZeroSuppressNode(GpddNode* node);
	//	void ZeroSuppressInList();
	//	GpddNode* ZeroSuppressNodeS(GpddNode* node,int& sign);

	//	void Reduce();
		void ReduceR();
		void ReduceNode(GpddNode* node,TripleMap& tripleMap,int& tripleCnt);
	//	GpddNode* ReduceNode(GpddNode* node,TripleMap& tripleMap,int& tripleCnt);

		void GarbageCollect();
		void TraverseNodeBFS(GpddNode* node,stack<GpddNode*>& workSpace);
		void TraverseNodeDFS(GpddNode* node,stack<GpddNode*>& workSpace);

		void MarkAll(bool ok);

		CPLX Evaluate();
		CPLX EvaluateNode(GpddNode* node);
		void ACAnalysis();


		void PostProcessRoot();

		void SExpand();
		void CreateCoefInit();
		void SExpandNode(GpddNode* node,bool flag);
		//void EvaluateCoef(vector<double>& numcoef,vector<int>& numpower,vector<double>& dencoef,vector<int>&denpower);
		void EvaluateCoef();
		double EvaluateCoefNode(GpddNode* p, bool flag);
		void ACCoefAnalysis();
		void ACAnalysisWithSCCoef(string filename);
		void MonteAnalysis(string filename);

		void InfinityExpand();
		void InfinityExpandNode(GpddNode* p, bool flag);

		
		void EvaluateInfinityCoef();
		void EvaluateInfinityCoefNode(GpddNode* p,bool flag);


		double EvaluateSensCoefNode(GpddNode* p,int updated,Symbol* target);
		void EvaluateCoefSens(Symbol* target,vector<double>& sens_numcoef,vector<double>& sens_dencoef);
		void SensAnalysis(string filename);
		void SensParametricFault(vector<double>& freqArray,vector<vector<CPLX> >& res);
		void MonteFaultAnalysis(vector<vector<CPLX> >& res,vector<vector<double> >& param);
		void CFaultAnalysis(vector<vector<CPLX> >& resSens,vector<vector<CPLX> >& resData,vector<vector<double> >& param);

		void Print(ostream& out)	{	root->Print(out);	}
		void PrintNode();
		void PrintExp(ostream& out);
		void PrintTerm();
		bool PrintTermR(list<GpddNode*> &termPath, int &sign, GpddNode* node);
		void PrintCoef();
		void PrintNodeCoef(const GpddNode* p);
	//	void PrintPathOne(ostream& out);

	private:
		bool IsTerminated(Symbol* symbol);
		void GraphReductionNodeBFS(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);
		//void GraphReductionNodeDFS(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap);
	/**  include & exclude, processed by type */
		void IncludeE(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);
		void ExcludeE(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);

		void IncludeF(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);
		void ExcludeF(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);

		void IncludeG(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);
		void ExcludeG(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);

		void IncludeH(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);
		void ExcludeH(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);

		void IncludeZ(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);
		void ExcludeZ(GpddNode* node,queue<GpddNode*>& workLayer,GraphMap& workgraphMap,GpddNodeMap& nodeMap);

	private:
		CKT* ckt;
		GpddNode* root;
		GpddNode* root2;
		list<GpddNode*> nodeList;
	public:
		vector<double> numcoef;
		vector<int> numpower;
		vector<double> dencoef;
		vector<int> denpower;
		
		vector<double> numcoef2;
		vector<int> numpower2;
		vector<double> dencoef2;
		vector<int> denpower2;

		vector<double> numcoef3;
		vector<int> numpower3;
		
};

#endif
