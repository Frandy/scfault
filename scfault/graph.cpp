#include <queue>
#include <sstream>
using std::stringstream;
using std::queue;
#include "stringMap.h"
#include "option.h"
#include "graph.h"

#ifdef DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif

void Graph::SetupNodeArray()
{
/*	unordered_map<int,int> tmp_node;
	list<Edge>::iterator it = edgeArray.begin();
	for(;it!=edgeArray.end();it++)
	{
		pair<int,int> node = (*it).Node();
		tmp_node[node.first] = node.first;
		tmp_node[node.second] = node.second;
	}
	unordered_map<int,int>::iterator node_it = tmp_node.begin();
	for(;node_it!=tmp_node.end();node_it++)
	{
		nodeArray.push_back((*node_it).first);
	}
*/
//	nodeNum = nodeArray.size();
	nodeArray = vector<int>(nodeNum,-1);
	list<Edge>::iterator it = edgeArray.begin();
	for(;it!=edgeArray.end();it++)
	{
		pair<int,int> node = (*it).Node();
		nodeArray[node.first] = node.first;
		nodeArray[node.second] = node.second;
	}
}
/*
void Graph::SetupAdjList(unordered_map<int,list<Edge*>>& adjList)
{
	// to create adjList 
	list<Edge*> emptyList;
	list<Edge>::iterator it = edgeArray.begin();
	list<int>::iterator node_it = nodeArray.begin();
//	for(;node_it!=nodeArray.end();node_it++)
//	{
//		adjList[(*node_it)] = emptyList;
//	}
	for(;it!=edgeArray.end();it++)
	{
		pair<int,int> node = (*it).Node();
		adjList[node.first]=emptyList;
		adjList[node.second]=emptyList;
	}
	for(it=edgeArray.begin();it!=edgeArray.end();it++)
	{
		pair<int,int> node = (*it).Node();
		adjList[node.first].push_back(&(*it));
		adjList[node.second].push_back(&(*it));
	}
}
*/

int Graph::ShortWire(Edge* edge,int& sign)
{
	list<Edge>::iterator it = edgeArray.begin();
	for(;it!=edgeArray.end();it++)
	{
		if((*it).Index()==edge->Index())
			break;
	}
	if(it==edgeArray.end())
		return 0;
	pair<int,int> node = (*it).Node();
	sign = 1;
	int tmp_node1 = node.first;  // to replace
	int tmp_node2 = node.second; // to be replaced
	// large node merge to small one
	if(node.first>node.second)
	{
		tmp_node1 = node.second;
		tmp_node2 = node.first;
//		sign *= -1;
	}
	else
		sign *= -1;

	// to remove shorted edge, i.e. self-loop 
	for(it=edgeArray.begin();it!=edgeArray.end();it++)
	{
		if((*it).ReplaceNode(tmp_node2,tmp_node1))
		{
			edgeArray.erase(it);
			it--;
		}
	}
	int smallnodeCnt = 0;
//	nodeArray.remove(tmp_node2);
//	int tn = nodeArray[tmp_node2];
//	smallnodeCnt = nodeArray[tmp_node2];
// no need to count smaller nodes
	smallnodeCnt = nodeArray[tmp_node2];
	nodeArray[tmp_node2] = -1;
	nodeNum--;

/*	list<int>::iterator node_it = nodeArray.begin();
	for(;node_it!=nodeArray.end();node_it++)
	{
		if((*node_it)<tmp_node2 )
			smallnodeCnt++;
	}
*/
//	tmp_node2 = tn;
//	for(unsigned int i=0,j=0;i<nodeArray.size();i++)
	for(unsigned int i=tmp_node2+1;i<nodeArray.size();i++)
	{
		if(nodeArray[i]==-1)
			continue;
		else
		{
/*			if(nodeArray[i]<tmp_node2)
				smallnodeCnt++;
			nodeArray[i]=j;
			j++;
*/
			nodeArray[i] = nodeArray[i]--;
		}
	}	

	if(smallnodeCnt%2==1)
		sign *= -1;
	if(edgeArray.size()==0)
	{
		if(nodeNum==1)
			return 1; // may lead -> ONE, the graph will be deleted
		else
		{
//			cout << "not a valid, return 0" << endl;
			return 0;
		}
	}

	return 2;	// gener
}

/**
 * @brief short operation for graph
 *
 * @param edge input, select edge to short
 * @param sign output, sign, which decided by sign algorithm, there two cases to flip sign,
 * 		-	sign *= -1, if node.second < node.first, since node.first -> node.second is the positive direction, and merge is done by merge big node to samll node
 * 		-	sign *= -1, if after merge, number of nodes < node been mergered 
 * 		-	sign *= -1, (short VS edge, this is processed in SpanNodeE, and SpanNodeH, but node here)
 *
 * @return {0, 1, 2} three kinds of value, and 
 * 		-	0 means short failure for the graph doesn't have this edge,
 * 		-	1 means it is the last edge been short or after short, the graph is empty
 * 		-	2 means general cases
 */
int Graph::Short(Edge* edge,int& sign)
{
//cout << "to short edge: " << edge->Index() << endl;
/*	if(edgeArray.size()==0)
		return 0;
*/	list<Edge>::iterator it = edgeArray.begin();
/*	for(;it!=edgeArray.end();it++)
	{
		if((*it).Index()==edge->Index())
			break;
	}
*/	// if no this edge, means through this path lead to ZERO
	if(it==edgeArray.end())
	{	
//		cout << "empty graph, to return 0" << endl;
		return 0;	// lead -> ZERO, the graph will be deleted
	}
	if((*it).Index()!=edge->Index())
	{
//		cout << "not the same index, to return 0" << endl;
		return 0;
	}
	pair<int,int> node = (*it).Node();
	sign = 1;
	int tmp_node1 = node.first;  // to replace
	int tmp_node2 = node.second; // to be replaced
	// large node merge to small one
	if(node.first>node.second)
	{
		tmp_node1 = node.second;
		tmp_node2 = node.first;
//		sign *= -1;
	}
	
	else
		sign *= -1;


	// to remove shorted edge, i.e. self-loop 
	for(it=edgeArray.begin();it!=edgeArray.end();it++)
	{
		if((*it).ReplaceNode(tmp_node2,tmp_node1))
		{
			edgeArray.erase(it);
			it--;
		}
	}
	int smallnodeCnt = 0;
//	nodeArray.remove(tmp_node2);
//	int tn = nodeArray[tmp_node2];
//	smallnodeCnt = nodeArray[tmp_node2];
// no need to count smaller nodes
	smallnodeCnt = nodeArray[tmp_node2];
	nodeArray[tmp_node2] = -1;
	nodeNum--;

/*	list<int>::iterator node_it = nodeArray.begin();
	for(;node_it!=nodeArray.end();node_it++)
	{
		if((*node_it)<tmp_node2 )
			smallnodeCnt++;
	}
*/
//	tmp_node2 = tn;
//	for(unsigned int i=0,j=0;i<nodeArray.size();i++)
	for(unsigned int i=tmp_node2+1;i<nodeArray.size();i++)
	{
		if(nodeArray[i]==-1)
			continue;
		else
		{
/*			if(nodeArray[i]<tmp_node2)
				smallnodeCnt++;
			nodeArray[i]=j;
			j++;
*/
			nodeArray[i] = nodeArray[i]--;
		}
	}	

	if(smallnodeCnt%2==1)
		sign *= -1;
	if(edgeArray.size()==0)
	{
		if(nodeNum==1)
			return 1; // may lead -> ONE, the graph will be deleted
		else
		{
//			cout << "not a valid, return 0" << endl;
			return 0;
		}
	}

	return 2;	// general cases
}

int Graph::OpenWire(Edge* edge)
{
	list<Edge>::iterator it = edgeArray.begin();
	for(;it!=edgeArray.end();it++)
	{
		if((*it).Index()==edge->Index())
			break;
	}
	// if no this edge
	if(it==edgeArray.end())
	{
		return 2;
	}
	edgeArray.erase(it);	// just to remove this edge
}

/**
 * @brief Open operation for graph 
 *
 * @param edge input, edge selected to open
 *
 * @return {0,1,2} also three kinds of value, and 
 * 		-	0 means after remove, graph is not connected, there are two simple cases
 * 			-	if open edge is the last edge of graph
 * 			-	if after open, N(edge) + 1 < N(node)
 * 		-	1 means, also general cases 
 * 		-	2 means general cases
 */
int Graph::Open(Edge* edge)
{
/*	if(edgeArray.empty())
		return 0;
*/	
/*	if(edge->Index()==8)
	{
		cout << "to open edge 8" << endl;
	}
*/
	list<Edge>::iterator it = edgeArray.begin();
/*	for(;it!=edgeArray.end();it++)
	{
		if((*it).Index()==edge->Index())
			break;
	}
*/	// if no this edge
	if(it==edgeArray.end())
	{
/*	if(edge->Index()==8)
	{
		cout << "to open edge 8,but not exist" << endl;
	}
		
*/		return 2;
	}
	if((*it).Index()!=edge->Index())
		return 2;
/*	if(edge->Index()==8)
	{
		cout << "to open edge 8" << endl;
	}
*/	int tmp_node1 = (*it).Node().first;
	int tmp_node2 = (*it).Node().second;
	edgeArray.erase(it);	// just to remove this edge

	if(edgeArray.size()==0 || edgeArray.size()+1<nodeNum)
		return 0;

	bool isconnected = true;

// a simple version to check connectivity
// just find node of the removed edge whether exist in the remain edgeList

	isconnected = false;
	list<Edge>::iterator tit = edgeArray.begin();
	bool half0 = false;
	bool half1 = false;
	for(;tit!=edgeArray.end();tit++)
	{
		if((*tit).Node().first==tmp_node1 || (*tit).Node().second==tmp_node1)
			half0 = true;
		if((*tit).Node().first==tmp_node2 || (*tit).Node().second==tmp_node2)
			half1 = true;
	}
	isconnected = half0 && half1;
	if(!isconnected)
		return 0;
	else
		return 2;

#ifdef GRAPH_CONNECTIVITY_CHECK
	// here to check connectivity
	// to lookfor path throgh tmp_node1 -> tmp_node2
/*	isconnected = false;
	unordered_map<int,list<Edge*>> adjList;
	SetupAdjList(adjList);
	unordered_map<int,int> mark;	// all edges on this node visited
	unordered_map<int,list<Edge*>>::iterator itadj = adjList.begin();
	int node = 0;
	for(;itadj!=adjList.end();itadj++)
	{
		node = (*itadj).first;
		mark[node] = 0;
	}
	queue<int> nodeQueue;
	if(adjList[tmp_node1].size()<=adjList[tmp_node2].size())
		node = tmp_node1;
	else
	{
		node = tmp_node2;
		tmp_node2 = tmp_node1;
	}
	nodeQueue.push(node);
	while(!nodeQueue.empty())
	{
		node = nodeQueue.front();
		nodeQueue.pop();
		mark[node]=1;
		list<Edge*>* elist = &(adjList[node]);
		list<Edge*>::iterator tmpit = elist->begin();
		Edge* edge = NULL;
		int tmp_node = -1;
		for(;tmpit!=elist->end();tmpit++)
		{
			edge = (*tmpit);
			tmp_node = edge->Node().first;
			if(tmp_node==tmp_node2)
			{
				isconnected = true;
				break;
			}
			if(tmp_node!=node && mark[tmp_node]!=1)
				nodeQueue.push(tmp_node);
			tmp_node = edge->Node().second;
			if(tmp_node==tmp_node2)
			{
				isconnected = true;
				break;
			}
			if(tmp_node!=node && mark[tmp_node]!=1)
				nodeQueue.push(tmp_node);
		}
	}
*/	
#endif	
	if(isconnected)
		return 2;
	else
		return 0;
}
/*
bool Graph::IsConnect()
{
	
	unordered_map<int,list<Edge*>> adjList;
	// to create adjList 
	list<Edge*> emptyList;
	list<Edge>::iterator it = edgeArray.begin();
	for(;it!=edgeArray.end();it++)
	{
		pair<int,int> node = (*it).Node();
		adjList[node.first]=emptyList;
		adjList[node.second]=emptyList;
	}
	for(it=edgeArray.begin();it!=edgeArray.end();it++)
	{
		pair<int,int> node = (*it).Node();
		adjList[node.first].push_back(&(*it));
		adjList[node.second].push_back(&(*it));
	}
	// mark & record 
	unordered_map<int,int> mark;	// all edges on this node visited
	unordered_map<int,int> record;	// can be reached
	unordered_map<int,list<Edge*>>::iterator itadj = adjList.begin();
	int node = 0;
	for(;itadj!=adjList.end();itadj++)
	{
		node = (*itadj).first;
		mark[node] = 0;
		record[node] = 0;
	}
	queue<int> nodeQueue;
	// the node select as it is first node of the next edge likely to be processed
	node =(*(edgeArray.begin())).Node().first;
	nodeQueue.push(node);
	while(!nodeQueue.empty())
	{
		node = nodeQueue.front();
		record[node] = 1;
		list<Edge*>* elist = &(adjList[node]);
		list<Edge*>::iterator tmpit = elist->begin();
		Edge* edge = NULL;
		int tmp_node = -1;
		for(;tmpit!=elist->end();tmpit++)
		{
			edge = (*tmpit);
			tmp_node = edge->Node().first;
			if(tmp_node!=node && mark[tmp_node]!=1)
				nodeQueue.push(tmp_node);
			tmp_node = edge->Node().second;
			if(tmp_node!=node && mark[tmp_node]!=1)
				nodeQueue.push(tmp_node);
		}
		mark[node]=1;
		nodeQueue.pop();
	}
	unordered_map<int,int>::iterator itrecord = record.begin();
	for(;itrecord!=record.end();itrecord++)
	{
		if(itrecord->second!=1)
			return false;
	}
	return true;
}
*/
void Graph::Print(ostream& out,int sel)
{
	out << "Graph: ";
	out << "\tedges= " << edgeArray.size() ;
	out << "\tnodes= " << nodeNum;
	out << endl;
		
	out << "\tedgeArray:" << endl;
	list<Edge>::iterator it = edgeArray.begin();
	for(;it!=edgeArray.end();it++)
	{
		out << (*it).Index() << "\t"; 
//		(*it).Print(out);
		//out << endl;
//		out << "\t\t";
	}
	out << endl;
	it = edgeArray.begin();
	for(;it!=edgeArray.end();it++)
	{
		out << (*it).Node().first << "\t";
	}
	out << endl;
	it = edgeArray.begin();
	for(;it!=edgeArray.end();it++)
	{
		out << (*it).Node().second << "\t";
	}
	out << endl;

	if(sel>0)
	{	
		out << "\tnodeArray:" << endl;
		for(unsigned int i=0;i<nodeArray.size();i++)
			out << "\t" << nodeArray[i];
/*		list<int>::iterator node_it = nodeArray.begin();
		for(;node_it!=nodeArray.end();node_it++)
			out << "\t" << (*node_it);
*/		out << endl;
	}
}

bool operator == (const Graph& g1,const Graph& g2)
{
	if(g1.GraphSize()!=g2.GraphSize())
		return false;
	list<Edge>::const_iterator tmp_it1 = g1.edgeArray.begin();
	list<Edge>::const_iterator tmp_it2 = g2.edgeArray.begin();
	for(;tmp_it1!=g1.edgeArray.end();tmp_it1++,tmp_it2++)
	{
/*		if((*tmp_it1)!=(*tmp_it2))
			return false;
*/		if((*tmp_it1).Index()!=(*tmp_it2).Index())
			return false;
/*		if((*tmp_it1).Node()!=(*tmp_it2).Node())
			return false;
*/
		pair<int,int> node1 = (*tmp_it1).Node();
		pair<int,int> node2 = (*tmp_it2).Node();
		if(g1.GetNewNode(node1.first)!=g2.GetNewNode(node2.first))
			return false;
		if(g1.GetNewNode(node1.second)!=g2.GetNewNode(node2.second))
			return false;
	}
	return true;
}

bool operator != (const Graph& g1,const Graph& g2)
{
	if(g1.GraphSize()!=g2.GraphSize())
		return true;
	list<Edge>::const_iterator tmp_it1 = g1.edgeArray.begin();
	list<Edge>::const_iterator tmp_it2 = g2.edgeArray.begin();
	for(;tmp_it1!=g1.edgeArray.end();tmp_it1++,tmp_it2++)
	{
		if((*tmp_it1)!=(*tmp_it2))
			return true;
/*	if((*tmp_it1).Index()!=(*tmp_it2).Index())
			return true;
		pair<int,int> node1 = (*tmp_it1).Node();
		pair<int,int> node2 = (*tmp_it2).Node();
		if(g1.GetNewNode(node1.first)!=g2.GetNewNode(node2.first))
			return true;
		if(g1.GetNewNode(node1.second)!=g2.GetNewNode(node2.second))
			return true;
*/
	}
	return false;
}

size_t Graph::Hash() const
{
//	size_t value = 0;
	list<Edge>::const_iterator tmp_it1 = edgeArray.begin();
	//stringstream tmp;
	int i=0;
	int maxL = edgeArray.size();
	if(maxL>29)
		maxL = 32;
	int tmp = 0;
	char* temp = new char[maxL];
	tmp = edgeArray.size();
	temp[0] = char(tmp%256);
	tmp = nodeNum;
	temp[1] = char(tmp%256);


//	value = edgeArray.size()<<16;
//	value |= nodeArray.size()<<8;
	for(i=2;i<maxL && tmp_it1!=edgeArray.end();i++,tmp_it1++)
	{
		//tmp += to_string((*tmp_it1).Index()) + to_string((*tmp_it1).Node().first) + to_string((*tmp_it1).Node().second);
		//tmp << (*tmp_it1).Index() << (*tmp_it1).Node().first << (*tmp_it1).Node().second;
		//value ^= (*tmp_it1).Index()<<4;
		//value |= ((*tmp_it1).Node().first+7)<<2;
		//value ^= ((*tmp_it1).Node().second+3)<<1;
		//value ^= value << 13;
		//value ^= (value<<8);
		tmp =((*tmp_it1).Index()<<2);
		tmp += nodeArray[((*tmp_it1).Node().first)]<<1;
		tmp += nodeArray[(*tmp_it1).Node().second];
//		value = (value ^ tmp);
		temp[i] = char(tmp%256);
	}
	temp[maxL-1]='\0';
//cout << value << endl;
//	return myJSHash(temp);
	return myBKDRHash(temp);

//	value = ((edgeArray.size()*nodeArray.size()+nodeArray.size())*value)%218357;
//	return value;
	//return (value%217636919);
	//return myJSHash(tmp.str().c_str());
}
