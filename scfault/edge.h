#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <ostream>
#include <iostream>
#include <utility>
using std::string;
using std::pair;
using std::ostream;
using std::cout;
using std::endl;


class Edge
{
	public:
		Edge(int n1,int n2)
		{
			index = -1;
			node = pair<int,int>(n1,n2);
		}
		Edge(int id,int n1,int n2)
			:index(id)
		{
			node = pair<int,int>(n1,n2);
		}
		
		Edge(const Edge& edge)
		{
			index = edge.Index();
			node = edge.Node();
		}

		virtual ~Edge()		{	}

		void SetIndex(int id)		{	index = id;	}
		int ReplaceNode(int newnode)
		{
			int oldnode = node.first;
			node.first = newnode;
			return oldnode;
		}
		void AddNodePhase(int n,int b)
		{
			if(b==2 && node.second!=0)
				node.second = node.second + n;
			if(b==1 && node.first!=0)
				node.first = node.first + n;
		}
		void AddNodePhase(int n)	{	
			if(node.first!=0)
				node.first+=n; 
			if(node.second!=0)
				node.second+=n;
		}
		bool ReplaceNode(int oldnode,int newnode)
		{
			if(node.first==oldnode)
				node.first = newnode;
			if(node.second==oldnode)
				node.second = newnode;
			if(node.first==node.second)
				return true;
			return false;
		}

		int Index()	const 			{	return index;	}
		pair<int,int> Node() const 	{	return node;	}

		virtual void Print(ostream& out=cout)
		{
			//out << "id: " << index << "\t";
			out << "( "<< node.first << ", " << node.second << " )";
			out << "\t";
			//out << endl;
		}

		friend bool operator == (const Edge& e1,const Edge& e2)
		{
			return (e1.Index()==e2.Index() && e1.Node()==e2.Node());
		}

		friend bool operator != (const Edge& e1,const Edge& e2)
		{
			return (e1.Index()!=e2.Index() || e1.Node()!=e2.Node());
		}

	protected:
		int index;
		pair<int,int> node;
};

#endif

