#ifndef NODE_H
#define NODE_H

#include <list>
using std::list;

#include "symbol.h"

class Node
{
	public:
		Node(string nm)	
		{
			name = nm;
			index = -1;
			mark = false;
		}

		Node(string& nm,int id)
			:name(nm),index(id)	{	}
		~Node()	{	}

		void AddSymbol(Symbol* symbol)
		{
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

		string Name() const {	return name;	}
		int Index()	const 	{	return index;	}
		bool Marked() const	{	return mark;	}
		list<Symbol*>* GetSymbolList()	{	return &symbolList;	}
		void SetIndex(int id)	{	index = id;	}
		void Mark(bool ok)	{	mark = ok;	}
/*
		int ReOrderSymbol(int id)	{	return id;	}
*/
		void Print(ostream& out=cout,int sel=0)
		{
			out << name << ": " << index << endl;
			if(sel==1)
			{
				list<Symbol*>::iterator it = symbolList.begin();
				for(;it!=symbolList.end();it++)
				{
					out << "\t";
					(*it)->Print(out);
				}
			}
		}

	private:
		string name;
		int index;
		bool mark;
		list<Symbol*> symbolList;
};


#endif
