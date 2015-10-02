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
	int nodes_num;//点数量
	int edges_num;//边数量
	vector<Node*> nodes;//存储点
	list<Edge*> incident_list;//存储边
	list<int> zero_list;//存储源点
	int src, dst;
	ifstream test("d:\\graph\\nodes3.txt");
	test>>nodes_num>>edges_num;
	nodes.push_back(new Node(0));//把第一个空间填上，之后就会从1开始填充vector
	//存储点
	for(int i=1;i<=nodes_num;i++)
		nodes.push_back(new Node(i));
	//存储边
	for(int i=1;i<=edges_num;i++)
	{
		test>>src>>dst;
		Edge* e=new Edge(src,dst);
		incident_list.push_back(e);
    }
	//记录所有点的入度
    list<Edge*>::iterator it,iend;
    it=incident_list.begin();
    iend=incident_list.end();
    for(;it!=iend;it++)
    {
    	nodes[(*it)->dst]->degree_in++;
    	nodes[(*it)->src]->neighbors.push_back((*it)->dst);
    }
	//初始化图结束

	//找到开始时所有的源节点
	for(int i=1;i<=nodes_num;i++)
		if(nodes[i]->degree_in==0)zero_list.push_back(i);
	//处理源节点
	while(zero_list.size()!=0)
	{
		int zero;
		zero=zero_list.front();//待处理的源节点
		zero_list.pop_front();//从源节点链表中删除
		//将该源节点关联的所有边删除，具体做法就是将相邻节点的入度减去1
		list<int>::iterator it,iend;
		iend=nodes[zero]->neighbors.end();
		for(it=nodes[zero]->neighbors.begin();it!=iend;it++)
		{nodes[*it]->degree_in--;if(nodes[*it]->degree_in==0)zero_list.push_back(*it);}
	}
	//处理完成后，根据入度判断是否有环
	int flag=0;//flag=1 --> has circle or flag=0--> no circle
	for(int i=1;i<=nodes_num;i++)
		if(nodes[i]->degree_in!=0){flag=1;break;}
	if(flag==0) cout<<"no circle"<<endl;
	else cout<<"has circle"<<endl;
    getchar();
    return 0;
} 
