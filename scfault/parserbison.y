%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserdefs.h"
#include <ctype.h>

#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ios;
using std::fstream;

/*
head files
*/
#include "edge.h"
#include "node.h"
#include "symbol.h"
#include "ckt.h"
#include "option.h"
#include "stringenc.h"


extern FILE *yyin;
extern int linenum;

extern CKT* myckt;
extern Symbol* symbolX;

int yylex();
int myparser(const char filename[]);
void yyerror(char *s,...);
%}

%defines "parserbison.hpp"

%union {
	struct mytoken *token;
}

%token <token> RID CID LID VID IID EID FID GID HID XID SID
%token <token> TEXT NUM INF 
%token DC AC DEC LIN
%token DOTTITLE DOTOP DOTPRINT DOTDC DOTTRAN DOTAC DOTPZ DOTDDD DOTPARAM
%token DOTCLOCK
%token OPAMP
%token LEVEL EQUAL PHASE SHORTOPEN FAULT
%token OP CP COMMA
%token DOTSC VOO VOE VEO VEE
%token COMMENT
%token LINEEND

%%

netlist:netlist ckt_statements
	| netlist cmd_statements
	| netlist LINEEND
	| ckt_statements
	| cmd_statements
	| LINEEND
	|
	;

ckt_statements:ckt_statements ckt_elem
	| ckt_elem	
	;

cmd_statements:cmd_statements cmd_elem
	| cmd_elem;

ckt_elem:r_elem
	| c_elem
	| l_elem
	| v_elem
	| i_elem
	| e_elem
	| f_elem
	| g_elem
	| s_elem
	| h_elem
	| x_elem
	;

cmd_elem:cmd_title 
	| cmd_op 
	| cmd_print
	| cmd_dc 
	| cmd_tran 
	| cmd_ac 
	| cmd_pz
	| cmd_ddd
	| cmd_sc
	| cmd_param
	| cmd_clock
	;

r_elem:RID node node elem_param{
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		Symbol* symbol = new Symbol($<token>1->s,R,edge,1/$<token>4->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	}
	;

c_elem:CID node node elem_param{
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		Symbol* symbol = new Symbol($<token>1->s,C,edge,$<token>4->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	}
	| CID node node elem_param LEVEL EQUAL NUM {
/* add for switched capacitor */	
		if(int($<token>7->d)==1)
		{
			int a = -1, b = -1; 
			
			a = myckt->AddNodeS($<token>2->s);
			b = myckt->AddNodeS($<token>3->s);
			string tmp1 = string($<token>1->s) + "_la";
			string tmp2 = string($<token>1->s) + "_lb";
			int c = -1, d = -1;
			c = myckt->AddNodeS(tmp1);
			d = myckt->AddNodeS(tmp2);
			string name = string($<token>1->s);

			string name1 = "XOPAMP" + name + "_SC_1";
			Edge* edge1 = new Edge(a,c);
			Edge* pedge1 = new Edge(a,c);
	//		Edge* pedge1 = new Edge(c,a);
			Symbol* symb1 = new Symbol(name1,NUNO,edge1,pedge1,0);
			
			Edge* edge2 = new Edge(b,d);
			Edge* pedge2 = new Edge(b,d);
	//		Edge* pedge2 = new Edge(d,b);
			string name2 = "XOPAMP" + name + "_SC_2";
			Symbol* symb2 = new Symbol(name2,NUNO,edge2,pedge2,0);
			
			Edge* edge3 = new Edge(c,d);
			string name3 = "L" + name ;//+ "_SC";
			Symbol* symb3 = new Symbol(name3,L,edge3,-$<token>4->d);

			Edge* edge4 = new Edge(a,b);
			string name4 = "R" + name ;//+ "_SC";
			Symbol* symb4 = new Symbol(name4,R,edge4,$<token>4->d);
	//		myckt->AddSwitch(symb1);
	//		myckt->AddSwitch(symb2);
			myckt->AddOpamp(symb1);
			myckt->AddOpamp(symb2);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
			myckt->AddSymbolInOrder(symb3);
			myckt->AddSymbolInOrder(symb4);
#else
			myckt->AddSymbol(symb3);
			myckt->AddSymbol(symb4);
#endif
		}
		else if(int($<token>7->d)==2)
		{
			int a = -1, b = -1; 
			a = myckt->AddNodeS($<token>2->s);
			b = myckt->AddNodeS($<token>3->s);
			string name = string($<token>1->s);
			
			string name1 = "G" + name;
			Edge* edge1 = new Edge(b,a);
			Edge* pedge1 = new Edge(b,a);
			Symbol* symb1 = new Symbol(name1,G,edge1,pedge1,$<token>4->d);

			string name4 = "R" + name ;//+ "_SC";
			Edge* edge4 = new Edge(a,b);
			Symbol* symb4 = new Symbol(name4,R,edge4,$<token>4->d);

			myckt->AddSymbol(symb1);
			myckt->AddSymbol(symb4);
		
		}
	}
	| CID node node INF LEVEL EQUAL NUM {
/* add for switched capacitor */	
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		string tmp1 = string($<token>1->s) + "_la";
		string tmp2 = string($<token>1->s) + "_lb";
		int c = -1, d = -1;
		c = myckt->AddNodeS(tmp1);
		d = myckt->AddNodeS(tmp2);
		string name = string($<token>1->s);

		string name1 = "XOPAMP" + name + "_SC_1";
		Edge* edge1 = new Edge(a,c);
		Edge* pedge1 = new Edge(a,c);
//		Edge* pedge1 = new Edge(c,a);
		Symbol* symb1 = new Symbol(name1,NUNO,edge1,pedge1,0);
		
		Edge* edge2 = new Edge(b,d);
		Edge* pedge2 = new Edge(b,d);
//		Edge* pedge2 = new Edge(d,b);
		string name2 = "XOPAMP" + name + "_SC_2";
		Symbol* symb2 = new Symbol(name2,NUNO,edge2,pedge2,0);
	
		double var = 1.0;
		if($<token>4->s[0]=='-')
			var = -var;
		myckt->Infinity(true);

		Edge* edge3 = new Edge(c,d);
		string name3 = "L" + name ;//+ "_SC";
		Symbol* symb3 = new Symbol(name3,L,edge3,-var);
		symb3->Infinity(1);

		Edge* edge4 = new Edge(a,b);
		string name4 = "R" + name ;//+ "_SC";
		Symbol* symb4 = new Symbol(name4,R,edge4,var);
		symb4->Infinity(1);
//		myckt->AddSwitch(symb1);
//		myckt->AddSwitch(symb2);
		myckt->AddOpamp(symb1);
		myckt->AddOpamp(symb2);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symb3);
		myckt->AddSymbolInOrder(symb4);
#else
		myckt->AddSymbol(symb3);
		myckt->AddSymbol(symb4);
#endif
	}


	| CID node node TEXT LEVEL EQUAL NUM {
/* add for switched capacitor */	
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		string tmp1 = string($<token>1->s) + "_la";
		string tmp2 = string($<token>1->s) + "_lb";
		int c = -1, d = -1;
		c = myckt->AddNodeS(tmp1);
		d = myckt->AddNodeS(tmp2);
		string name = string($<token>1->s);

		string name1 = "XOPAMP" + name + "_SC_1";
		Edge* edge1 = new Edge(a,c);
		Edge* pedge1 = new Edge(a,c);
//		Edge* pedge1 = new Edge(c,a);
		Symbol* symb1 = new Symbol(name1,NUNO,edge1,pedge1,0);
		
		Edge* edge2 = new Edge(b,d);
		Edge* pedge2 = new Edge(b,d);
//		Edge* pedge2 = new Edge(d,b);
		string name2 = "XOPAMP" + name + "_SC_2";
		Symbol* symb2 = new Symbol(name2,NUNO,edge2,pedge2,0);
		
		Edge* edge3 = new Edge(c,d);
		string name3 = "L" + name ;//+ "_SC";
		Symbol* symb3 = new Symbol(name3,L,edge3,-$<token>4->d);

		Edge* edge4 = new Edge(a,b);
		string name4 = "R" + name ;//+ "_SC";
		Symbol* symb4 = new Symbol(name4,R,edge4,$<token>4->d);
//		myckt->AddSwitch(symb1);
//		myckt->AddSwitch(symb2);
		myckt->AddOpamp(symb1);
		myckt->AddOpamp(symb2);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symb3);
		myckt->AddSymbolInOrder(symb4);
#else
		myckt->AddSymbol(symb3);
		myckt->AddSymbol(symb4);
#endif
		//cout << "match here," << $<token>1->s << endl;
		if(myckt->paramList.IsParam($<token>4->s))
		{
			//cout << $<token>4->d << endl;	
			myckt->paramList.AddParamSymb($<token>4->s,symb3);
			myckt->paramList.AddParamSymb($<token>4->s,symb4);
		}
	}

	;

l_elem:LID node node elem_param{
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		Symbol* symbol = new Symbol($<token>1->s,L,edge,1/$<token>4->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	}
	;

v_elem:VID node node AC elem_param {
		int a = -1, b = -1; 
	
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		double var = $<token>5->d;
//cout << "vs:" << $<token>1->s << " var: " << var << endl;		
		if(var<=1e-9)
		{
			Symbol* symbol = new Symbol($<token>1->s,VS,edge,var);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif
		}
		else
		{
			if(symbolX==NULL)
			{
				symbolX = new Symbol($<token>1->s,VS,edge,$<token>5->d);
			}
			else
			{
				if(symbolX->Type()==VS)
					symbolX->SetType(E);
				else if(symbolX->Type()==IS)
					symbolX->SetType(H);
				symbolX->SetEdge(edge);
			}
		}
	}
	| VID node node DC elem_param AC elem_param {
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		if(symbolX==NULL)
		{
			symbolX = new Symbol($<token>1->s,VS,edge,$<token>7->d);
		}
		else
		{
			if(symbolX->Type()==VS)
				symbolX->SetType(E);	// VC VS
			else if(symbolX->Type()==IS)
				symbolX->SetType(H);	// CC VS
			symbolX->SetEdge(edge);
		}
	}
	;

i_elem:IID node node AC elem_param {
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		//Edge* edge = new Edge(b,a);
		if(symbolX==NULL)
		{
			symbolX = new Symbol($<token>1->s,IS,edge,$<token>5->d);
		}
		else
		{
			if(symbolX->Type()==VS)
				symbolX->SetType(G);	// VC CS
			else if(symbolX->Type()==IS)
				symbolX->SetType(F);	// CC CS
			symbolX->SetEdge(edge);
		}
	}
	| IID node node DC elem_param AC elem_param {
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		if(symbolX==NULL)
		{
			symbolX = new Symbol($<token>1->s,IS,edge,$<token>7->d);
		}
		else
		{
			if(symbolX->Type()==VS)
				symbolX->SetType(G);	// VC CS
			else if(symbolX->Type()==IS)
				symbolX->SetType(F);	// CC CS
			symbolX->SetEdge(edge);
		}
	}
	;

e_elem:EID node node node node elem_param {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		c = myckt->AddNodeS($<token>4->s);
		d = myckt->AddNodeS($<token>5->s);
		e1 = new Edge(a,b);
		e2 = new Edge(c,d);
		Symbol* symbol = new Symbol($<token>1->s,E,e1,e2,$<token>6->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	}
	| EID node node node node INF {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		c = myckt->AddNodeS($<token>4->s);
		d = myckt->AddNodeS($<token>5->s);
		e1 = new Edge(a,b);
		e2 = new Edge(c,d);
		double var = 1.0;
		if($<token>6->s[0]=='-')
			var = -var;
		myckt->Infinity(true);
		Symbol* symbol = new Symbol($<token>1->s,E,e1,e2,var);
		symbol->Infinity(1);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif
	}
	| EID node node node node TEXT {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		c = myckt->AddNodeS($<token>4->s);
		d = myckt->AddNodeS($<token>5->s);
		e1 = new Edge(a,b);
		e2 = new Edge(c,d);
		cout << $<token>6->s << endl;
		double var = 1.0;
		if($<token>6->s[0]=='-')
			var = -var;
		myckt->Infinity(true);
		Symbol* symbol = new Symbol($<token>1->s,E,e1,e2,var);
		symbol->Infinity(1);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	}
	;

f_elem:FID node node TEXT elem_param {
	  /* CCCS */
		int a = -1, b = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		e1 = new Edge(a,b);
/*	
		Symbol* tmp_symbol = myckt->FindSymbol($<token>4->s);	// control current must appear earlier
		Edge* tmp_edge = tmp_symbol->GetEdge();
		string mcnode = "mc_";
		mcnode = mcnode + tmp_symbol->Name();
		int newnode = myckt->AddNodeS(mcnode);
		int oldnode = tmp_edge->ReplaceNode(newnode);
		e2 = new Edge(oldnode,newnode);
		Symbol* symbol = new Symbol($<token>1->s,F,e1,e2,$<token>5->d);
*/
		Symbol* symbol = new Symbol($<token>1->s,F,e1,$<token>5->d);
		myckt->AddCCXS(symbol,$<token>4->s);

#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	}
	| FID node node node node elem_param {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		c = myckt->AddNodeS($<token>4->s);
		d = myckt->AddNodeS($<token>5->s);
		e1 = new Edge(a,b);
		e2 = new Edge(c,d);
		Symbol* symbol = new Symbol($<token>1->s,F,e1,e2,$<token>6->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif	
	}
	;

g_elem:GID node node node node elem_param {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		c = myckt->AddNodeS($<token>4->s);
		d = myckt->AddNodeS($<token>5->s);
		e1 = new Edge(a,b);
		Symbol* symbol = NULL;
		if(a==c && b==d)
			symbol = new Symbol($<token>1->s,R,e1,$<token>6->d);
		else	
		{	
			e2 = new Edge(c,d);
			symbol = new Symbol($<token>1->s,G,e1,e2,$<token>6->d);
		}
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	}
	;

s_elem:SID node node PHASE EQUAL NUM {
/* add for switched capacitor */	
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		Edge* pedge = new Edge(a,b);
		Symbol* symbol = new Symbol($<token>1->s,S,edge,pedge,$<token>6->d);
	//	myckt->AddSwitch(symbol);
		myckt->AddOpamp(symbol);
	//	myckt->AddSymbol(symbol);
	}
	| SID node node NUM SHORTOPEN {
		string ft = strtolower(($<token>5->s));
		if(ft=="SHORT" || ft=="short")	
		{
			int a = -1, b = -1; 
			a = myckt->AddNodeS($<token>2->s);
			b = myckt->AddNodeS($<token>3->s);
			Edge* edge = new Edge(a,b);
			Edge* pedge = new Edge(a,b);
			Symbol* symbol = new Symbol($<token>1->s,S,edge,pedge,$<token>4->d);
			//symbol->Fault("short");
			symbol->Fault(ft);
			//myckt->AddSymbol(symbol);
			myckt->AddOpamp(symbol);
			cout << "a short switch:" << $<token>1->s << endl;		
		}
			// if open, no need to parse
	}
	| SID node node NUM FAULT {
		string ft = strtolower(($<token>5->s));
		//if(ft=="SHORT" || ft=="short")	
		//{
		int a = -1, b = -1; 
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		Edge* pedge = new Edge(a,b);
		Symbol* symbol = new Symbol($<token>1->s,S,edge,pedge,$<token>4->d);
		//symbol->Fault("short");
		symbol->Fault(ft);
		myckt->AddSymbol(symbol);
		//myckt->AddOpamp(symbol);
		cout << "a short switch:" << $<token>1->s << endl;		
		//}
		// if open, no need to parse
	}
	| SID node node NUM FAULT SHORTOPEN{
		string ft = strtolower(($<token>5->s));
		string st = strtolower(($<token>6->s));
		//if(ft=="SHORT" || ft=="short")	
		//{
		int a = -1, b = -1; 
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		Edge* pedge = new Edge(a,b);
		Symbol* symbol = new Symbol($<token>1->s,S,edge,pedge,$<token>4->d);
		//symbol->Fault("short");
		symbol->Fault(st);
		myckt->AddSymbol(symbol);
		//myckt->AddOpamp(symbol);
		cout << "a fault switch:" << $<token>1->s << endl;		
		//}
		// if open, no need to parse
	}

	| SID node node NUM {
		int a = -1, b = -1; 
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		Edge* edge = new Edge(a,b);
		Edge* pedge = new Edge(a,b);
		Symbol* symbol = new Symbol($<token>1->s,S,edge,pedge,$<token>4->d);
	//	myckt->AddSymbol(symbol);
		myckt->AddOpamp(symbol);
	}
	;

h_elem:HID node node TEXT elem_param {
		int a = -1, b = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		e1 = new Edge(a,b);
/*
		Symbol* tmp_symbol = myckt->FindSymbol($<token>4->s);	// control current must appear earlier
		Edge* tmp_edge = tmp_symbol->GetEdge();
		string mcnode = "mc_";
		mcnode = mcnode + tmp_symbol->Name();
		int newnode = myckt->AddNodeS(mcnode);
		int oldnode = tmp_edge->ReplaceNode(newnode);
		e2 = new Edge(oldnode,newnode);

		Symbol* symbol = new Symbol($<token>1->s,H,e1,e2,$<token>5->d);
*/
		Symbol* symbol = new Symbol($<token>1->s,H,e1,$<token>5->d);
		myckt->AddCCXS(symbol,$<token>4->s);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	}
	| HID node node node node elem_param {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		a = myckt->AddNodeS($<token>2->s);
		b = myckt->AddNodeS($<token>3->s);
		c = myckt->AddNodeS($<token>4->s);
		d = myckt->AddNodeS($<token>5->s);
		e1 = new Edge(a,b);
		e2 = new Edge(c,d);
		Symbol* symbol = new Symbol($<token>1->s,H,e1,e2,$<token>6->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif	
	
	}
	;

x_elem:XID OPAMP node node node node{
		int a = myckt->AddNodeS($<token>3->s);
		int b = myckt->AddNodeS($<token>4->s);
		int c = myckt->AddNodeS($<token>5->s);
		int d = myckt->AddNodeS($<token>6->s);
		Edge *e1 = new Edge(a,b);
		Edge *e2 = new Edge(c,d);
		Symbol* symbol = new Symbol($<token>1->s,NUNO,e1,e2,1);
		myckt->AddOpamp(symbol);
	  }
	  | XID OPAMP node node node node TEXT{
		int a = myckt->AddNodeS($<token>3->s);
		int b = myckt->AddNodeS($<token>4->s);
		int c = myckt->AddNodeS($<token>5->s);
		int d = myckt->AddNodeS($<token>6->s);
		Edge *e1 = new Edge(a,b);
		Edge *e2 = new Edge(c,d);
		Symbol* symbol = new Symbol($<token>1->s,E,e1,e2,$<token>7->d);
		myckt->AddSymbol(symbol);	
		if(myckt->paramList.IsParam($<token>7->s))
		{
			cout << "param opamp" << endl;
			myckt->paramList.AddParamSymb($<token>7->s,symbol);
		}
	  };


node:NUM
	| TEXT
	;

elem_param:NUM
	;

cmd_title:DOTTITLE
	;

cmd_op:DOTOP
	;

cmd_sc:DOTSC VOO {
	  	myckt->SetSCOutStat(0);
	  }
	  | DOTSC VOE {
	  	myckt->SetSCOutStat(1);
	  }
	  | DOTSC VEO {
	  	myckt->SetSCOutStat(2);
	  }
	  | DOTSC VEE {
	  	myckt->SetSCOutStat(3);
	  }

cmd_print: DOTPRINT AC TEXT OP node CP {
	  	char outtype = toupper(($<token>3->s)[0]);
		Edge* outedge = NULL;
		if(symbolX!=NULL)
		{
			if(outtype=='V')
			{
				int node = myckt->FindNodeIndex($<token>5->s);
				outedge = new Edge(node,0);
				if(symbolX->Type()==VS)
					symbolX->SetType(E);
				else if(symbolX->Type()==IS)
					symbolX->SetType(G);
			}
	/*		
			else if(outtype=='I')
			{
				Symbol* tmp_symbol = myckt->FindSymbol($<token>5->s);
				Edge* tmp_edge = tmp_symbol->GetEdge();
				string mcnode = "mc_";
				mcnode = mcnode + tmp_symbol->Name();
				int newnode = myckt->AddNodeS(mcnode);
				int oldnode = tmp_edge->ReplaceNode(newnode);
				outedge = new Edge(oldnode,newnode);
				if(symbolX->Type()==VS)
					symbolX->SetType(H);
				else if(symbolX->Type()==IS)
					symbolX->SetType(F);
			}
	*/			symbolX->SetPairEdge(outedge);
		}
		else if(symbolX==NULL)
		{
			// some problems 
		}
	}
	| DOTPRINT AC TEXT OP node COMMA node CP {
	  	char outtype = toupper(($<token>3->s)[0]);
		Edge* outedge = NULL;
		if(symbolX!=NULL)
		{
			if(outtype=='V')
			{
				int node1 = myckt->FindNodeIndex($<token>5->s);
				int node2 = myckt->FindNodeIndex($<token>7->s);
				outedge = new Edge(node1,node2);
				if(symbolX->Type()==VS)
					symbolX->SetType(E);
				else if(symbolX->Type()==IS)
					symbolX->SetType(G);
			}
			symbolX->SetPairEdge(outedge);
		}
		else if(symbolX==NULL)
		{
			// some problems 
		}
		
	}
	| DOTPRINT AC TEXT OP TEXT CP {
	  	char outtype = toupper(($<token>3->s)[0]);
		Edge* outedge = NULL;
		if(symbolX!=NULL)
		{
			if(outtype=='V')
			{
				Symbol* tmp_symbol = myckt->FindSymbol($<token>5->s);
				if(tmp_symbol!=NULL)
				{
					int node1 = tmp_symbol->GetEdge()->Node().first;
					int node2 = tmp_symbol->GetEdge()->Node().second;
					outedge = new Edge(node1,node2);
				}
				else
				{
					int node = myckt->FindNodeIndex($<token>5->s);
					outedge = new Edge(node,0);
				}
				if(symbolX->Type()==VS)
					symbolX->SetType(E);
				else if(symbolX->Type()==IS)
					symbolX->SetType(G);
			}
			else if(outtype=='I')
			{
				Symbol* tmp_symbol = myckt->FindSymbol($<token>5->s);
				Edge* tmp_edge = tmp_symbol->GetEdge();
				string mcnode = "mc_";
				mcnode = mcnode + tmp_symbol->Name();
				int newnode = myckt->AddNodeS(mcnode);
				int oldnode = tmp_edge->ReplaceNode(newnode);
				outedge = new Edge(oldnode,newnode);
				if(symbolX->Type()==VS)
					symbolX->SetType(H);
				else if(symbolX->Type()==IS)
					symbolX->SetType(F);
			}
				symbolX->SetPairEdge(outedge);
		}
		else if(symbolX==NULL)
		{
			// some problems 
		}
	}
	;

cmd_dc:DOTDC
	;

cmd_tran:DOTTRAN
	;

cmd_ac:DOTAC DEC elem_param elem_param elem_param {
		myckt->SetACTask(1,$<token>3->d,$<token>4->d,$<token>5->d);
	}
	| DOTAC LIN elem_param elem_param elem_param {
		myckt->SetACTask(0,$<token>3->d,$<token>4->d,$<token>5->d);
	}
	;

cmd_pz:DOTPZ TEXT OP TEXT CP TEXT {
/*	  	char intype = toupper(($<token>2->s)[0]);
		char outtype = toupper(($<token>6->s)[0]);
		PZTask* task = new PZTask(intype,$<token>4->s,outtype,$<token>6->s);
		ckt->AddTask(task);
		task->Print(cout);
*/	}
	| DOTPZ TEXT OP node CP TEXT {
/*	  	char intype = toupper(($<token>2->s)[0]);
		char outtype = toupper(($<token>6->s)[0]);
		PZTask* task = new PZTask(intype,$<token>4->s,outtype,$<token>6->s);
		ckt->AddTask(task);
		task->Print(cout);
*/	}
	;
cmd_ddd:DOTDDD TEXT OP node CP {
/*	    cout << "to set ddd output" << endl;
		ckt->SetDDDOutput($<token>4->s);   
*/	}
	| DOTDDD AC TEXT OP node CP {
/*	    cout << "to set ddd output" << endl;
		ckt->SetDDDOutput($<token>5->s);   
*/	}

cmd_param:DOTPARAM TEXT TEXT {
		ParamNode* p = new ParamNode($<token>2->s,$<token>3->s);
		myckt->paramList.AddParam(p)
	}
	;

cmd_clock:DOTCLOCK elem_param {
		myckt->Clock($<token>2->d);	 
	}
	;

%%


int myparser(const char filename[]){
	
	myckt = new CKT(filename);
	symbolX = NULL;

	yyin = fopen(filename,"r");
	yyparse();
	symbolX->SetNameX();
	myckt->AddSymbolX(symbolX);
	myckt->PostProcessCCXSList();
	fclose(yyin);
	
	return 0;
}

void yyerror(char *s,...){
	fprintf(stderr,"line %d error %s\n",linenum,s);	
	exit(-1);
}
