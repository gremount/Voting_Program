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
	int nodes_num;//������
	int edges_num;//������
	vector<Node*> nodes;//�洢��
	list<Edge*> incident_list;//�洢��
	list<int> zero_list;//�洢Դ��
	int src, dst;
	ifstream test("d:\\graph\\nodes3.txt");
	test>>nodes_num>>edges_num;
	nodes.push_back(new Node(0));//�ѵ�һ���ռ����ϣ�֮��ͻ��1��ʼ���vector
	//�洢��
	for(int i=1;i<=nodes_num;i++)
		nodes.push_back(new Node(i));
	//�洢��
	for(int i=1;i<=edges_num;i++)
	{
		test>>src>>dst;
		Edge* e=new Edge(src,dst);
		incident_list.push_back(e);
    }
	//��¼���е�����
    list<Edge*>::iterator it,iend;
    it=incident_list.begin();
    iend=incident_list.end();
    for(;it!=iend;it++)
    {
    	nodes[(*it)->dst]->degree_in++;
    	nodes[(*it)->src]->neighbors.push_back((*it)->dst);
    }
	//��ʼ��ͼ����

	//�ҵ���ʼʱ���е�Դ�ڵ�
	for(int i=1;i<=nodes_num;i++)
		if(nodes[i]->degree_in==0)zero_list.push_back(i);
	//����Դ�ڵ�
	while(zero_list.size()!=0)
	{
		int zero;
		zero=zero_list.front();//�������Դ�ڵ�
		zero_list.pop_front();//��Դ�ڵ�������ɾ��
		//����Դ�ڵ���������б�ɾ���������������ǽ����ڽڵ����ȼ�ȥ1
		list<int>::iterator it,iend;
		iend=nodes[zero]->neighbors.end();
		for(it=nodes[zero]->neighbors.begin();it!=iend;it++)
		{nodes[*it]->degree_in--;if(nodes[*it]->degree_in==0)zero_list.push_back(*it);}
	}
	//������ɺ󣬸�������ж��Ƿ��л�
	int flag=0;//flag=1 --> has circle or flag=0--> no circle
	for(int i=1;i<=nodes_num;i++)
		if(nodes[i]->degree_in!=0){flag=1;break;}
	if(flag==0) cout<<"no circle"<<endl;
	else cout<<"has circle"<<endl;
    getchar();
    return 0;
} 
