#ifndef CKT_H
#define CKT_H

#include <vector>
#include <list>
using std::vector;
using std::list;

#include "edge.h"
#include "node.h"
#include "symbol.h"
#include "graph.h"
#include "stringMap.h"
#include "actask.h"
#include "cktparam.h"

class CKT
{
	public:
		CKT(string filename);
		~CKT();

		string FileName() const	{	return filename; }
		void Print(ostream& out=cout);

	/* node */	
		int FindNodeIndex(string name);
		Node* FindNode(string name);	
		Node* FindNode(int index);
		int AddNodeS(string name);
		int NodeCount()	{	return nodeMap.size();	}
		void PrintAllNode(ostream& out=cout,int sel=0);
		void Clock(double d) {clk = d;}
		double Clock()	{return clk;}

		void SetSCOutStat(int a)	{	scOutStat=a;}
	/* symbol */	
		void AddSymbol(Symbol* symbol)		
		{	
			symbolList.push_back(symbol);	
			symbolMap[symbol->Name()] = symbol;
			
		}
		void AddCCXS(Symbol* symbol,string text)
		{
			ccxsList.push_back(pair<Symbol*,string>(symbol,text));
		}

		void AddSymbolX(Symbol* symbol)	
		{	
			symbolList.push_front(symbol);	
			symbolMap[symbol->Name()] = symbol;
		}
		void AddOpamp(Symbol* symbol)
		{
			opampList.push_back(symbol);
		}
		void AddSwitch(Symbol* symbol)
		{
			switchList.push_back(symbol);
		}
		void AlterScOutStat();
		int GetScOutStat() {	return scOutStat;	}

		list<Symbol*>* GetOpampList()	{	return &opampList;	}
		list<Symbol*>* GetSwitchList()	{	return &switchList;	}
		void PostProcessCCXSList();
		void ProcessParallelEdge();
		void AddSymbolInOrder(Symbol* symbol);
		void SettleSymbolIndex();

		Symbol* FindSymbol(string name);
//		Symbol* FindSymbol(string& name);
		
		int SymbolCount()			{	return symbolList.size();	}
		void PrintAllSymbol(ostream& out=cout);

		bool Infinity() const	{	return infinity;	}
		void Infinity(bool inf)	{	infinity = inf;	}

	/* ac task */
		ACTask* GetACTask()	{	return actask;	}
		void SetACTask(int tp,int no,double st,double ef)	{	actask = new ACTask(tp,no,st,ef); }
	/* edge */	
	//	void AddEdge(Edge* edge)	{	edgeList.push_back(edge);	}
	//	int EdgeCount()				{	return edgeList.size();	}
	//	void PrintAllEdge(ostream& out=cout);
	
	/* post parser */
		void AttachSymbolToNode();
		void SettleSymbolOrder();
	//	void CreateEdgeList();
		void SettleEdgeIndex();

	/* set up for GPDD */
		void CreateLRGraph(Graph* lGraph,Graph* rGraph);
		void CreateLRTwoPhaseGraph(Graph* lGraph,Graph* rGraph);
		void PostProcessCSC();
		Symbol* GetSymbolX()	{	return *(symbolList.begin());	}
		void SetupSymbolOneZero();
		void SetupSymbolFreqValue(double freq);

	private:
		string filename;
		ACTask *actask;
		int scOutStat;
	//	list<Edge*> edgeList;
		list<Symbol*> symbolList;
		list<Symbol*> opampList;
		list<Symbol*> switchList;
		list<pair<Symbol*,string>> ccxsList;
		unordered_map<int,list<Symbol*>*> parallelEdgeList;
		unordered_map<string,Symbol*,StringHash,StringCompare> symbolMap;
		unordered_map<string,int,StringHash,StringCompare> nodeMap;
		vector<Node*> nodeArray;
		double clk;
		bool infinity;
	public:
		ParamList paramList;
/*		list<Symbol*> inputlist;
		list<Symbol*> outputlist;
		list<Symbol*> pairlist;
*/
};

#endif

