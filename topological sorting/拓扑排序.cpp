#include<stdio.h>
#include<iostream>
#include<list>
#include<vector>
#include<fstream>
using namespace std;
#define N 100
//topological sorting

class Node
{
public:
	int id;
	int degree_in;
	list<int> neighbors;
	Node(){;}
	Node(int a){id=a;degree_in=0;}
};

class Edge
{
public:
	int src;
	int dst;
	Edge(){;}
	Edge(int a, int b){src=a; dst=b;}
};

int main()
{
	Node nodes[N];
	int nodes_num;
	int edges_num;
	list<Edge> incident_list;
	int src, dst;
	ifstream test("d:\\graph\\nodes3.txt");
	test>>nodes_num>>edges_num;
	for(int i=1;i<=nodes_num;i++)
		nodes[i]=Node(i);
	for(int i=1;i<=edges_num;i++)
	{
		test>>src>>dst;
		incident_list.push_back(Edge(src,dst));
    }
    list<Edge>::iterator it,iend;
    it=incident_list.begin();
    iend=incident_list.end();
    for(;it!=iend;it++)
    {
    	nodes[it->dst].degree_in++;
    	nodes[it->src].neighbors.push_back(it->dst);
    }
    getchar();
    return 0;
} 
