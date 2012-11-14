#include <queue>
#include <iostream>
#include <cmath>
using std::queue;
using std::cout;
using std::endl;

#include "ckt.h"
#include "paralleledgeMap.h"
#include "option.h"


CKT::CKT(string filename)
{
	filename = filename;
	actask = NULL;
	AddNodeS("0");
}

CKT::~CKT()
{
	list<Symbol*>::iterator it = symbolList.begin();
	for(;it!=symbolList.end();it++)
		delete (Symbol*) (*it);
	
	for(unsigned int i=0;i<nodeArray.size();i++)
		delete (Node*) nodeArray[i];
}

void CKT::Print(ostream& out)
{
	out << "all the symbols: " << endl;
	PrintAllSymbol(out);
//	out << "all the nodes: " << endl;
//	PrintAllNode(out,1);
}

int CKT::FindNodeIndex(string name)
{
	if(nodeMap.find(name)!=nodeMap.end())
		return nodeMap[name];
	else
		return -1;
}


Node* CKT::FindNode(string name)	
{
	if(nodeMap.find(name)!=nodeMap.end())
		return nodeArray[nodeMap[name]];
	else
		return NULL;
}

Node* CKT::FindNode(int index)	
{
	return nodeArray[index];
}

int CKT::AddNodeS(string name)
{
//	int index = stoi(name);
	int index = -1;
	if(nodeMap.find(name)==nodeMap.end())
	{
		Node* node = new Node(name);
		index = nodeMap.size();
		node->SetIndex(index);
		nodeMap[name] = index;
		nodeArray.push_back(node);
	}
	else
	{
		index = nodeMap[name];
	}
	return index;
}

void CKT::PrintAllNode(ostream& out,int sel)
{
	for(unsigned int i=0;i<nodeArray.size();i++)
		nodeArray[i]->Print(out,sel);
}

/* symbol */
void CKT::AddSymbolInOrder(Symbol* symbol)
{
	symbolMap[symbol->Name()] = symbol;
	list<Symbol*>::iterator it = symbolList.begin();
	for(;it!=symbolList.end();it++)
	{
		if(symbol->Type()<(*it)->Type())
		{
			symbolList.insert(it,symbol);
			return;
		}
	}
	symbolList.push_back(symbol);
}

void CKT::SettleSymbolIndex()
{
	int i = 0;
	list<Symbol*>::iterator it = symbolList.begin();
	for(;it!=symbolList.end();it++)
		(*it)->SetIndex(i++);
/*	it = symbolList.begin();
	for(;it!=symbolList.end();it++)
	{
		(*it)->Print();
		cout << "\t" <<(*it)->Index() << endl;
	}
*/
}

Symbol* CKT::FindSymbol(string name)
{
	Symbol* symbol = NULL;
	if(symbolMap.find(name)!=symbolMap.end())
		symbol = symbolMap[name];
	return symbol;
}

void CKT::PrintAllSymbol(ostream& out)
{
	list<Symbol*>::iterator it = symbolList.begin();
	for(;it!=symbolList.end();it++)
		(*it)->Print(out);
	if(!opampList.empty())
	{
		list<Symbol*>::iterator tit = opampList.begin();
		for(;tit!=opampList.end();tit++)
			(*tit)->Print(out);
	}
/*	if(!switchList.empty())
	{
		list<Symbol*>::iterator sit = switchList.begin();
		for(;sit!=switchList.end();sit++)
			(*sit)->Print(out);
	}
*/
}

/* post parser */
void CKT::AttachSymbolToNode()
{
	Node* node = NULL;
	Edge* edge = NULL;
	list<Symbol*>::iterator it = symbolList.begin();
	for(;it!=symbolList.end();it++)
	{
		edge = (*it)->GetEdge();
		node = nodeArray[edge->Node().first];
		node->AddSymbol(*it);
		node = nodeArray[edge->Node().second];
		node->AddSymbol(*it);
	}
}

void CKT::SettleSymbolOrder()
{
	list<Symbol*>::iterator it = symbolList.begin();
	list<Symbol*>::iterator nextit = symbolList.begin();
	nextit++;
	unsigned int i = 0;
	for(;it!=symbolList.end();it++,nextit++)
	{		
		(*it)->SetIndex(++i);
		(*it)->SetNext(*nextit);
	}
	it--;
	(*it)->SetNext(NULL);
/*	it = symbolList.begin();
	for(;it!=symbolList.end();it++)
	{
		(*it)->Print();
		cout << "\t" <<(*it)->Index() << endl;
	}
*/
	PrintAllSymbol();
}

void CKT::SettleEdgeIndex()
{
	list<Symbol*>::iterator symbit = symbolList.begin();
	Symbol* symbol = NULL;
	int cnt = 0;
	for(;symbit!=symbolList.end();symbit++)
	{
		symbol = (*symbit);
		symbol->GetEdge()->SetIndex(++cnt);
		if(symbol->GetPairEdge()!=NULL)
		{			
			symbol->GetPairEdge()->SetIndex(++cnt);
		}
	}

//	cout << "error here" << endl;

	if(!opampList.empty())
	{
		list<Symbol*>::iterator opampit = opampList.begin();
		for(;opampit!=opampList.end();opampit++)
		{
//			(*opampit)->Print(cout);
			(*opampit)->GetEdge()->SetIndex(++cnt);
			(*opampit)->GetPairEdge()->SetIndex(++cnt);
		}
	}
}
	
void CKT::CreateLRGraph(Graph* lGraph,Graph* rGraph)
{
	list<Edge>* edgeList1 = lGraph->GetEdgeArray();
	list<Edge>* edgeList2 = rGraph->GetEdgeArray();

/*cerr << "to process parallel edges" << endl;
cerr << "before, symbol count: " << symbolList.size() << endl;
	ProcessParallelEdge();
cerr << "ater, symbol count: " << symbolList.size() << endl;
*/
/*cerr << "to process switch " << endl;
	PostProcessCSC();
cerr << "done." << endl;
*/
cerr << "to settle symbol order" << endl;
	SettleSymbolOrder();
#ifdef DEBUG_ORDER
//	cout << "ordered symbol list: " << endl;
//	this->PrintAllSymbol(cout);
#endif

cerr << "to settle edge index" << endl;	
	SettleEdgeIndex();
cerr << "---\tedge index done" << endl;	

	Symbol* symbol = NULL;
	Edge* edge = NULL;
	Edge* pairedge = NULL;
/*	
	if(!switchList.empty())
	{
		list<Symbol*>::iterator swit = switchList.begin();
		for(;swit!=switchList.end();swit++)
		{
			edge = (*swit)->GetEdge();
			edgeList1->push_back(*edge);
			edgeList2->push_back(*edge);
		}
	}

cerr << "---\tswitch done" << endl;
*/
	if(!opampList.empty())
	{
		list<Symbol*>::iterator opampit = opampList.begin();
		for(;opampit!=opampList.end();opampit++)
		{
			edge = (*opampit)->GetEdge();
			if((*opampit)->Type()==VS)
			{
			edgeList1->push_back(*edge);		// NO
			edgeList2->push_back(*edge);		// NO
			continue;
			}
			pairedge = (*opampit)->GetPairEdge();
			edgeList1->push_back(*edge);		// NO
			edgeList2->push_back(*pairedge);	// NU
		}
	}

cerr << "---\topamp done" << endl;

	list<Symbol*>::iterator symbit = symbolList.begin();
	for(;symbit!=symbolList.end();symbit++)
	{
		symbol = (*symbit);
		switch(symbol->Type())
		{
			case E:// VCVS
				{
					edge = symbol->GetEdge();
					pairedge = symbol->GetPairEdge();
					edgeList1->push_back(*edge);
					edgeList2->push_back(*edge);
					edgeList2->push_back(*pairedge);
				}
				break;
			case F:// CCCS
				{
					edge = symbol->GetEdge();
					pairedge = symbol->GetPairEdge();
					edgeList1->push_back(*edge);
					edgeList1->push_back(*pairedge);
					edgeList2->push_back(*pairedge);
				}
				break;
			case G:// VCCS
				{
					edge = symbol->GetEdge();
					pairedge = symbol->GetPairEdge();
					edgeList1->push_back(*edge);
					edgeList2->push_back(*pairedge);
				}
				break;
/*			case GSC:
				{
					edge = symbol->GetEdge();
					pairedge = symbol->GetPairEdge();
					edgeList1->push_back(*edge);
					edgeList2->push_back(*pairedge);

				}
				break;
*/			case H:// CCVS
				{
					edge = symbol->GetEdge();
					pairedge = symbol->GetPairEdge();
					edgeList1->push_back(*edge);
					edgeList1->push_back(*pairedge);
					edgeList2->push_back(*edge);
					edgeList2->push_back(*pairedge);
				}
				break;
		/*	case NUNO:
				{
					edge = symbol->GetEdge();
					pairedge = symbol->GetPairEdge();
					edgeList1->push_back(*edge);
					edgeList2->push_back(*pairedge);
				}
				break; */
			default:
				{
					edge = symbol->GetEdge();
					edgeList1->push_back(*edge);
					edgeList2->push_back(*edge);
				}
				break;
		}
	}
	lGraph->SetNodeNum(2*nodeArray.size()-1);
	lGraph->SetupNodeArray();
	rGraph->SetNodeNum(2*nodeArray.size()-1);
	rGraph->SetupNodeArray();
}

Symbol* pSymbolOne;
Symbol* pSymbolZero;

void CKT::SetupSymbolOneZero()
{
	pSymbolOne = new Symbol(ONE);
	pSymbolZero = new Symbol(ZERO);
	symbolMap[pSymbolOne->Name()] = pSymbolOne;
	pSymbolOne->SetIndex(symbolList.size()+1);
	symbolMap[pSymbolZero->Name()] = pSymbolZero;
	pSymbolZero->SetIndex(symbolList.size()+2);
}

void CKT::SetupSymbolFreqValue(double freq)
{
	list<Symbol*>::iterator it = symbolList.begin();
	Symbol* symbol = NULL;
	double value = 0;
//	double tmp_freq = 2*M_PI*freq;
	double pi = 3.14159;
	double tmp_freq = 2*pi*freq;
	CPLX tmp_value = CPLX(0,0);
	for(;it!=symbolList.end();it++)
	{
		symbol = *it;
		switch(symbol->Type())
		{
			case R:
				{
					value = symbol->Value();
					tmp_value = CPLX(value,0.0);
					symbol->SetCplxValue(tmp_value);
				}
				break;
			case C:
				{
					value = symbol->Value();
					tmp_value = CPLX(0,tmp_freq*value);
					symbol->SetCplxValue(tmp_value);
				}
				break;
			case L:
				{
					value = symbol->Value();
					//tmp_value = CPLX(0,-1.0/(tmp_freq*value));
					tmp_value = CPLX(0,-value/(tmp_freq));
					symbol->SetCplxValue(tmp_value);
				}
				break;
/*			case GSC:
				{
				}
				break;
*/			case Z:
				{
					list<Symbol*>* tmpList = (parallelEdgeList[symbol->ParallelMark()]);
					list<Symbol*>::iterator tmpit = tmpList->begin();
					tmpit++;
					CPLX tmp1_value(0,0);
					Symbol* tmp_symbol = NULL;
					for(;tmpit!=tmpList->end();tmpit++)
					{
						tmp_symbol = (*tmpit);
						switch(tmp_symbol->Type())
						{
							case R:
								{
									value = tmp_symbol->Value();
								//	tmp1_value += CPLX(1.0/value,0.0);
									tmp_symbol->SetCplxValue(tmp_value);
								}
								break;
							case C:
								{
									value = tmp_symbol->Value();
								//	tmp1_value += CPLX(0,tmp_freq*value);
									tmp_symbol->SetCplxValue(tmp_value);
								}
								break;
							case L:
								{
									value = tmp_symbol->Value();
								//	tmp1_value += CPLX(0,-1.0/(tmp_freq*value));
									tmp_symbol->SetCplxValue(tmp_value);
								}
								break;		
							default:;
						}
					}
					symbol->SetCplxValue(tmp1_value);
				}
				break;
			default:;
		}
	}
}

void CKT::PostProcessCCXSList()
{
//cout << "to process ccxs list " << endl;

	if(!ccxsList.empty())
	{
		list<pair<Symbol*,string>>::iterator it = ccxsList.begin();
		bool v0flag = false;
		for(;it!=ccxsList.end();it++)
		{
			string text = (*it).second;
			Symbol* tmp_symbol = this->FindSymbol(text);
			Edge* tmp_edge = tmp_symbol->GetEdge();
			Edge* e2 = NULL;
			if(text[0]=='V' || text[0]=='v')
			{
				e2 = new Edge(*tmp_edge);
				v0flag = true;
			}
			else
			{
				string mcnode = "mc_";
				mcnode = mcnode + tmp_symbol->Name();
				int newnode = this->AddNodeS(mcnode);
				int oldnode = tmp_edge->ReplaceNode(newnode);
				e2 = new Edge(oldnode,newnode);
			}
			(*it).first->SetPairEdge(e2);
		}
		if(v0flag)
		{
			list<Symbol*>::iterator tmit = symbolList.begin();
			for(;tmit!=symbolList.end();tmit++)
			{
				if((*tmit)->Type()==VS && (*tmit)->Value()<=1e-6)
				{
					symbolList.erase(tmit);
					tmit--;
				}
			}
		}
	}
}


void CKT::ProcessParallelEdge()
{
	list<Symbol*>::iterator it = symbolList.begin();
	ParallelEdgeMap parallelEdgeMap;
	Symbol* symbol = NULL;
	Symbol* tmp_symbol = NULL;
	for(;it!=symbolList.end();it++)
	{
		symbol = (*it);
		if(symbol->Type()==C || symbol->Type()==L || symbol->Type()==R)
		{
			tmp_symbol = parallelEdgeMap.Find(symbol);
			if(tmp_symbol!=NULL)
			{
				symbol->SetParallelMark(tmp_symbol->ParallelMark());
			}
			else
			{
				parallelEdgeMap.Add(symbol);
			}
		}
	}

	for(it=symbolList.begin();it!=symbolList.end();it++)
	{
		int parallelMark = (*it)->ParallelMark();
		if(parallelMark>0)
		{
			if(parallelEdgeList.find(parallelMark)==parallelEdgeList.end())
			{
				list<Symbol*>* tmplist=new list<Symbol*>();
				tmplist->push_back((*it));
				Symbol* newsymbol = new Symbol(*it);
				newsymbol->SetType(Z);
				tmplist->push_front(newsymbol);
				symbolList.insert(it,newsymbol);
				symbolList.erase(it);
				it--;
				parallelEdgeList[parallelMark] = tmplist;
			}
			else
				{
				parallelEdgeList[parallelMark]->push_back((*it));
				Symbol* newsymbol = (*(parallelEdgeList[parallelMark]->begin()));
				newsymbol->AddParallelName((*it)->Name());
				symbolList.erase(it);
				it--;
			}
		}
	}
#ifdef DEBUG_PARALLEL
	cout << "now the new symbol list is " << endl;
	for(it=symbolList.begin();it!=symbolList.end();it++)
	{
		(*it)->Print(cout);
	}
#endif

}

void CKT::AlterScOutStat()
{
	switch(scOutStat)
	{
		case 0:
			scOutStat = 1;
			break;
		case 1:
			scOutStat = 0;
			break;
		case 2:
			scOutStat = 3;
			break;
		case 3:
			scOutStat = 2;
			break;
		default:;
	}
	
	Symbol* symbol = NULL;
	int N = nodeArray.size()-1;
	list<Symbol*>::iterator sit = symbolList.begin();
	symbol = (*sit);
	Symbol* vin = new Symbol(symbol);

	vin->SetType(VS);
	if(scOutStat<=1) // vin' should be short 
	{
		vin->GetEdge()->AddNodePhase(N);
	}
	else // vin' as input and vin should be short
	{
		symbol->GetEdge()->AddNodePhase(N);
	}
	Edge* nedge = new Edge(*(vin->GetEdge()));
	vin->SetPairEdge(nedge);
	vin->SetValue(0);
	opampList.push_back(vin);
	
	if(scOutStat==1 || scOutStat==3) // vout' as output
	{
		symbol->GetPairEdge()->AddNodePhase(N);
	}
	
	PostProcessCCXSList();
}

void CKT::PostProcessCSC()
{
//	cout << "before post process csc" << endl;
//	Print(cout);
 	

	Symbol* symbol = NULL;
	int N = nodeArray.size()-1;

	if(opampList.empty())
		return;
	
	list<Symbol*>::iterator oit = opampList.begin();
	for(;oit!=opampList.end();oit++)
	{
		symbol = (*oit);
		if(symbol->Type()==S && symbol->Fault().empty()) 
		{	
			if(2==int(symbol->Value()))
			{
//				cout << "here 1:" << endl;
//				symbol->Print(cout);
				symbol->SetNamePhase();
				symbol->SetNodePhase(N);
			}
		}
		else if(0==int(symbol->Value())) // opamp
		{
			Symbol* symb1 = new Symbol(symbol);
			symb1->SetOpampPhase(1,N);
			symbol->SetOpampPhase(2,N);
			symbol->SetNamePhase();
			opampList.insert(oit,symb1);
		}
		else 
		{
//			
			if(symbol->Fault()!="short")			
				cerr << "switch fault error" << endl;
//			cout << "here 2:" << endl;
//				symbol->Print(cout);
			Symbol* symb1 = new Symbol(symbol);
			symbol->SetNamePhase();
			symbol->SetNodePhase(N);
			opampList.insert(oit,symb1);
			// short in two phase
		}
	}

	list<Symbol*>::iterator sit = symbolList.begin();
	// for all symbol, add '
	for(;sit!=symbolList.end();sit++)
	{
		(*sit)->SetNamePhase();
	}

	sit = symbolList.begin();

	symbol = (*sit);
	if(scOutStat==1 || scOutStat==3) // vout' as output
	{
		symbol->GetPairEdge()->AddNodePhase(N);
	}

	Symbol* vin = new Symbol(symbol);
	vin->GetEdge()->AddNodePhase(N);
	sit++;
	symbolList.insert(sit,vin);

	//paramList.Print();
	for(;sit!=symbolList.end();sit++)
	{
		symbol = (*sit);
		if(symbol->Type()==S)
		{
			// whether with fault, two phase switch needed
			Symbol* symb1 = new Symbol(symbol);
			symbol->SetNamePhase();
			symbol->SetNodePhase(N);
			
			symbol->SetType(G);
			symb1->SetType(G);

			symbolList.insert(sit,symb1);

			if(symbol->Fault().empty()||symbol->Fault()=="fault")
			{
				if(int(symbol->Value())==1)
				{
					symb1->SetValue(1.0);
					symb1->Infinity(true);
					symbol->SetValue(0.0);
				}
				else if(int(symbol->Value())==2)
				{
					symb1->SetValue(0.0);
					symbol->SetValue(1.0);
					symbol->Infinity(true);
				}
			}
			else if(symbol->Fault()=="short")
			{
				symb1->SetValue(1.0);
				symb1->Infinity(true);
				symbol->SetValue(1.0);
				symbol->Infinity(true);
			}
			else if(symbol->Fault()=="open")
			{
				symb1->SetValue(0.0);
				symbol->SetValue(0.0);
			}
			else 
			{
				cerr << "something error when post process csc" << endl;
			}
			Infinity(true);
			continue;	
		}

		Symbol* symb1 = NULL;
		if(symbol->Type()==G)
		{
			symb1 = new Symbol(symbol);	
			symb1->SetGPhase(1,N);
			symbol->SetGPhase(2,N);
			symbol->SetNamePhase();
			symbolList.insert(sit,symb1);
		}
		else
		{

			symb1 = new Symbol(symbol);
			symbol->SetNamePhase();
			symbol->SetNodePhase(N);
			symbolList.insert(sit,symb1);
		}
	/*	cout << "symbol,";
		symbol->Print();
		cout << endl;
		cout << "symb1,";
		symb1->Print();
		cout << endl;
	*/
		string param;
		if(paramList.IsParamSymb(symbol,param))
		{
			paramList.AddParamSymb(param,symb1);
		}
	}
	paramList.Print();
}
