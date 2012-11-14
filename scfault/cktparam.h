#ifndef CKT_PARAM_H_
#define CKT_PARAM_H_

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <vector>
using namespace std;

#include "symbol.h"

class ParamNode
{
	public:
		ParamNode(string p,string filename)
		{
			param = p;
			dataname = filename;
		}
		void AddSymb(Symbol* symb)
		{
			paramSymbList.push_back(symb);
		}
		friend bool operator == (const ParamNode& a,const ParamNode& b)
		{
			return a.param==b.param;
		}
		bool IsParamSymb(Symbol* symb)
		{
			list<Symbol*>::iterator it = paramSymbList.begin();
			for(;it!=paramSymbList.end();it++)
			{
				if((*it)->Name()==symb->Name())
				{
					//cout << "match symbol name," << (*it)->Name() << "\t" << symb->Name() << endl;
					return true;
				}
			}
			return false;
		}
		/*
		void Sort()
		{
			list<Symbol*>::iterator it = paramSymbList.begin();
			it++;
			list<Symbol*>::reverse_iterator rit = paramSymbList.rbegin();
			paramSymbList.insert(it,(*rit));
			paramSymbList.pop_back();
			it = paramSymbList.begin();
			rit = paramSymbList.rbegin();
			paramSymbList.insert(it,(*rit));	
			paramSymbList.pop_back();
		}*/
		/*
		bool operator < (const ParamNode& node)
		{
			int ai = (*(this->paramSymbList.begin()))->Index();
			int bi = (*(node.paramSymbList.begin()))->Index();
			return (ai<bi);
		}*/
		void Print()
		{
			cout << param << "(" << dataname <<")" << ":\n";
		list<Symbol*>::iterator it = paramSymbList.begin();
			for(;it!=paramSymbList.end();it++)
			{
				cout << "\t" << (*it)->Name() << endl;
			}
			cout << endl;
		}
		void ReadData()
		{
			fstream file(dataname.c_str(),ios::in);
			while(file)
			{
				double d;
				if(file >> d)
					paramdata.push_back(d);
			}
			/*
			for(int i=0;i<paramdata.size();i++)
			{
				cout << paramdata[i] << endl;
			}*/
		}
		void UpdateSymbValue(double value)
		{
			list<Symbol*>::iterator it = paramSymbList.begin();
			for(;it!=paramSymbList.end();it++)
			{
				Symbol* symb = (*it);
				if(symb->Name()[0]=='L')
					symb->SetValue(-value);
				else if(symb->Name()[0]=='R')
					symb->SetValue(value);
				else
				{
					symb->SetValue(value);
					//cout << "error @ update symb value" << endl;
				}
			}
		}
		void Sort()
		{
			struct cmp_symbolIndex cmp_symbol;
			paramSymbList.sort(cmp_symbol);
		}
		void ReadEsData()
		{
			double fr,fi,hr,hi;
			fstream file(dataname.c_str(),ios::in);
			while(file)
			{
				file >> fr >> fi >> hr >> hi;
				freq.push_back(CPLX(fr,fi));
				Hz.push_back(CPLX(fr,fi));
			}
			
		}
	public:
		string param;
		string dataname;
		vector<double> paramdata;
		vector<CPLX> freq;
		vector<CPLX> Hz;
		list<Symbol*> paramSymbList;
		vector<double> *sens_num_coef;
		vector<double> *sens_den_coef;
};

struct cmp_paramNode
{
	bool operator () (const ParamNode* n1, const ParamNode* n2) const
	{
		int ai = (*(n1->paramSymbList.begin()))->Index();
		int bi = (*(n2->paramSymbList.begin()))->Index();
		return (ai<bi);
		
	}
};

class ParamList
{
	public:
		~ParamList()
		{
			list<ParamNode*>::iterator it = paramList.begin();
			for(;it!=paramList.end();it++)
			{
				delete (ParamNode*) (*it);
			}
		}
		void AddParam(ParamNode* p)
		{
			paramList.push_back(p);
		}
		bool IsParam(string param)
		{
			list<ParamNode*>::iterator it = paramList.begin();
			for(;it!=paramList.end();it++)
			{
				if((*it)->param==param)
					return true;
			}
			return false;
			
		}
		void AddParamSymb(string param,Symbol* symb)
		{
			//cout << "add param symbol," << symb->Name() << endl;
			list<ParamNode*>::iterator it = paramList.begin();
			for(;it!=paramList.end();it++)
			{
				if((*it)->param==param)
				{
					(*it)->AddSymb(symb);
					return;
				}
			}
			
		}
		bool IsParamSymb(Symbol* symb,string& param)
		{
			list<ParamNode*>::iterator it = paramList.begin();
			for(;it!=paramList.end();it++)
			{
				if((*it)->IsParamSymb(symb))
				{	
					param = (*it)->param;
					return true;
				}
			}
			return false;
		}
		void Print()
		{
			list<ParamNode*>::iterator it = paramList.begin();
			for(;it!=paramList.end();it++)
			{
				(*it)->Print();
			}
		}
		void Sort()
		{
			list<ParamNode*>::iterator it = paramList.begin();
			for(;it!=paramList.end();it++)
			{
				(*it)->Sort();
			}
			struct cmp_paramNode cmp_param;
			paramList.sort(cmp_param);
		}
		void ReadData()
		{
			list<ParamNode*>::iterator it = paramList.begin();
			for(;it!=paramList.end();it++)
			{
				(*it)->ReadData();
			}
		}
	public:
		list<ParamNode*> paramList;

};


#endif
