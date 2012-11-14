#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <ostream>
#include <iostream>
using std::string;
using std::ostream;
using std::cout;
using std::endl;

#include "cplx.h"
#include "edge.h"

enum SymbolType{ONE=12,ZERO=13,
				/*X=1,*/
				E=1,F=2,G=3,H=4,
				C=5,L=6,R=7,Z=8,
				VS=9,IS=10,
				NUNO=11,
				GSC=14,CSC=15,S=16
				};

class Symbol
{
	public:
		Symbol(string nm, SymbolType tp, Edge* e1, double var)
			: name(nm), type(tp), edge(e1), value(var)
		{
			index = -1;
			pairedge = NULL;
			tmp_value = CPLX(value,0);
			mark = false;
			parallelMark = 0;
			next = NULL;
			infinity = 0;
		}

		Symbol(string nm, SymbolType tp, Edge* e1, Edge* e2, double var)
			: name(nm), type(tp), edge(e1), pairedge(e2), value(var)	
		{
			index = -1;
			tmp_value = CPLX(value,0);
			parallelMark = 0;
			mark = false;
			next = NULL;
			infinity = 0;
		}

		Symbol(SymbolType tp)
		{
			type = tp;
			if(tp==ZERO)
			{
				name = "0";
				value = 0;
			}
			else if(tp==ONE)
			{
				name = "1";
				value = 1;
			}
			edge = NULL;
			pairedge = NULL;
			tmp_value = CPLX(value,0);
			parallelMark = 0;
			infinity = 0;
			mark = true;
			next = NULL;
		}

		// controlling edge
		Symbol(SymbolType tp, Edge* e1)
			: type(tp), pairedge(e1)
		{
			index = -1;
			edge = NULL;
			value = 1;
			tmp_value = CPLX(value,0);
			mark = false;
			parallelMark = 0;
			next = NULL;
		}


		Symbol(const Symbol* symbol)
		{
			name = symbol->Name();
			index = symbol->Index();
			type = symbol->Type();
			edge = new Edge(*(symbol->GetEdge()));
			if(symbol->GetPairEdge()!=NULL)
				pairedge = new Edge(*(symbol->GetPairEdge()));
			value = symbol->Value();
			tmp_value = symbol->GetCplxValue();
			mark = symbol->Marked();
			parallelMark = symbol->ParallelMark();
			infinity = symbol->Infinity();
			zeroMark = symbol->ZeroMarked();
			next = NULL;//symbol->Next();
		}

		~Symbol()
		{
			delete (Edge*) edge;
			delete (Edge*) pairedge;
		}

		string Name() const				{	return name;	}
		int Index()	const				{	return index;	}
		SymbolType Type() const			{	return type;	}
		Edge* GetEdge() const			{	return edge;	}
		Edge* GetPairEdge() const 		{	return pairedge;	}
		double Value() const			{	return value;	}
		CPLX GetCplxValue() const		{	return tmp_value;	}
		int ParallelMark() const		{	return parallelMark;	}
		bool Marked() const				{	return mark;	}
		Symbol* Next() const 			{	return next;	}
		
		int Infinity() const 	{ return infinity;	}
		void Infinity(int index)	{	infinity = index;	}
		void ZeroMark(bool ok)	{zeroMark = ok;}
		bool ZeroMarked()	const {return zeroMark;}

		void SetNameX()					{	name = "X";		}
		void SetNamePhase()				{	name += "'"; 	}
		void SetNodePhase(int n)		
		{	edge->AddNodePhase(n);
			if(pairedge!=NULL)
				pairedge->AddNodePhase(n);
		}
		void SetOpampPhase(int a,int b)
		{
			if(a==1)
			{
				pairedge->AddNodePhase(b,1);
			}
			else if(a==2)
			{
			//	name = name + "'";
				edge->AddNodePhase(b);
				pairedge->AddNodePhase(b,2);
			}

		}
		void SetGPhase(int a,int b)
		{
			if(a==1)
			{
				pairedge->AddNodePhase(b,1);
				pairedge->AddNodePhase(b,2);
			}
			else if(a==2)
			{
				edge->AddNodePhase(b,1);
				edge->AddNodePhase(b,2);
			}
		}

		void SetGLSC(int a,int b)
		{
		//	type = GSC;
/*			if(a==1)
			{
				type = NUNO;
				name = "XOPAMP"+name + "_1";
				int a = pairedge->Node().second;
				
				pairedge->AddNodePhase(b);	
			}
			else if(a==2)
			{
				name = "L"+name;
				SetNamePhase();
				edge->AddNodePhase(b);
			}
			else if(a==3)
			{
				name = "XOPAMP"+name + "_1";
				pairedge->AddNodePhase(b);	
			
			}
			else if(a==4)
			{
			
			}
			else if(a==5)
			{
			
			}
			else if(a=6)
			{
			}
*/		}
		void SetGSC(int a,int b)
		{
/*			type = R;
			name = "R"+name;
			value = 1.0/value;
			if(a==2)
			{
				SetNamePhase();
				edge->AddNodePhase(b);
			}
*/		}

		void AddParallelName(string nm) {	name += "//" + nm;}
		void SetIndex(int id)			{	index = id;		}
		void SetType(SymbolType tp)		{	type = tp;		}
		void SetEdge(Edge* edge)		{	edge = edge;	}
		void SetPairEdge(Edge* edge)	
		{	if(pairedge!=NULL)
				delete (Edge*) pairedge;
			pairedge = edge;	
		}
		void Mark(bool ok)				{	mark = ok;		}
		void SetParallelMark(int parallel)	{	parallelMark = parallel;	}
		void SetNext(Symbol* nextSymbol){	next = nextSymbol;	}
		void SetValue(double var)		{	value = var; tmp_value = CPLX(var);	}
		double GetValue()	{	return value;	}
		void SetCplxValue(CPLX& var)	{	tmp_value = var;	}

		void Print(ostream& out=cout)
		{
			out << name << "\t\t";
			//out << "type: " << type << "\t\t";
			edge->Print(out);
			if(pairedge!=NULL)
				pairedge->Print(out);
			out << value;
		/*	if(!fault.empty())
				out << "fault:" << fault;
		*/	out << endl;
		}
		void PrintSymbol(ostream& out=cout)
		{
			out << name;
		}

		string Fault() {return fault;}
		void Fault(string ft) {fault=ft;}


		friend bool operator == (const Symbol& symb1, const Symbol& symb2)
		{
			return symb1.Index()==symb2.Index();
		}
		friend bool operator != (const Symbol& symb1, const Symbol& symb2)
		{
			return symb1.Index()!=symb2.Index();
		}
		friend bool operator > (const Symbol& symb1, const Symbol& symb2)
		{
			return symb1.Index()>symb2.Index();
		}
		friend bool operator < (const Symbol& symb1, const Symbol& symb2)
		{
			cout << "comparing:" << symb1.Name() << " " << symb1.Index()<< "\t" << symb2.Name() << " " << symb2.Index();
			cout << "\tresult:" << (symb1.Index()<symb2.Index()) << endl;
			return (symb1.Index()<symb2.Index());
		}
		/*
		friend bool operator < (const Symbol*& symb1, const Symbol*& symb2)
		{
			cout << "comparing:" << symb1->Name() << " " << symb1->Index()<< "\t" << symb2->Name() << " " << symb2->Index();
			cout << "\tresult:" << (symb1->Index()<symb2->Index()) << endl;
			return (symb1->Index()<symb2->Index());
		}*/


	private:
		string name;
		SymbolType type;
		int index;
		Edge* edge;			// if E,F,G,H, edge: CS or VS, pairedge: VC or CC & NUNO, edge: NO, pairedge: NU
		Edge* pairedge;
		double value;
		CPLX tmp_value;
		bool mark;
		int parallelMark;
		string fault;
		Symbol* next;
		int infinity;
		bool zeroMark;
};

struct cmp_symbolIndex
{
	bool operator () (const Symbol* s1, const Symbol* s2) const
	{
		return (s1->Index()<s2->Index());
	}
};

// if symbol in order it appear, then index from symbolMap.size(),
// else if symbol in order on node BFS, then index decide with node BFS
// else symbol in order X < C,L < R in whole ckt

#endif
