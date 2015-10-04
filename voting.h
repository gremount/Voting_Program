#include "common.h"
//M is the number of candidates
//N is the number of voters

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

bool cmp(pair<int, pair<int,int> > a, pair<int, pair<int,int> > b)
		{
			if(a.first>b.first)return true;
			else return false;    
		}

class Voting
{
	private:
	public:
		float t[M+1][N+1];
		Voting(float table[M + 1][N + 1])
		{
			for(int i=1;i<=M;i++)
				for(int j=1;j<=N;j++)
					t[i][j]=table[i][j];
		}
		int voting(int k)
		{
			srand((unsigned)time(NULL));
			if(k==2) return Cumulative_Voting();
			else if(k==3) return Condorcet_Voting();
			else if(k==4) return Ranked_Pairs_Voting();
			else {cout<<"error"<<endl;return 0;}
		}

		int Cumulative_Voting()
		{
			float small_score[M+1][N+1]={0};
			float big_score[M+1]={0};
			float max_score = 0;//record the score of final winner
			vector<int> winners;
			float sum=0;
			//change 0 to 1
			for(int i=1;i<=M;i++)
				for(int j=1;j<=N;j++)
					if(t[i][j]==0) t[i][j]=1;

			for(int j=1;j<=N;j++)
			{
				for(int i=1;i<=M;i++)
					sum+=1/t[i][j];
				for(int i=1;i<=M;i++)
					small_score[i][j]=(1/t[i][j])/sum;
			}
			for(int i=1;i<=M;i++)
				for(int j=1;j<=N;j++)
					big_score[i]+=small_score[i][j];

			//find the NO.1 and if there is more than 1 person, return the random one
			max_score = big_score[1];
			for (int i = 2; i <= M; i++)
				if (big_score[i] >= max_score) max_score = big_score[i];
			for (int i = 1; i <= M; i++)
				if (big_score[i] == max_score) winners.push_back(i);
			if (winners.size() == 1) return winners[0];
			else
			{
				int randnum;
				randnum = rand() % winners.size();
				return winners[randnum];
			}
		}

		int Ranked_Pairs_Voting()
		{
			int small_win[M + 1][N + 1] = { 0 };
			int big_win[M + 1] = { 0 };
			int max_win = 0;//record the score of final winner
			vector<int> winners;
			vector<pair<int,pair<int,int> > > comp;
			int winner=0;//the last winner
			for (int j = 1; j <= N; j++)
			{
				for (int i = 1; i <= M - 1; i++)
					for (int h = i + 1; h <= M; h++)
						if (t[i][j] <= t[h][j]) small_win[i][h]++;
						else small_win[h][i]++;
			}
			for (int i = 1; i <= M-1; i++)
				for (int j = i+1; j <= M; j++)
				{
					if (i == j) continue;
					if(small_win[i][j]<ceil(N/2.0)) 
					{
						pair<int, int> p0(j,i);
						pair<int, pair<int,int> > p((M-1-small_win[i][j]),p0);
						comp.push_back(p);
					}
					else
					{
						pair<int, int> p0(i,j);
						pair<int, pair<int,int> > p(small_win[i][j],p0);
						comp.push_back(p);
					}
					/*small_win[i][j]=M-1-small_win[i][j];
					！！！一旦这样换值，如何确定初始值呢-->所以不能换值
				    不用换值，直接把所需要比较的值存入一个list里,然后就可以给这个list排序,
					这里要存储的是三个值，谁和谁比较就有两个值，所获票数比例的值，
					所以这里是一个三元组，用一个类来表示是可以的，或者用pair的嵌套也是可行的
					*/
				}
			//如何使用sort函数来给comp这个list里的元素排序呢？详情见sort_cmp模板
			sort(comp.begin(),comp.end(),cmp);
			vector<Node*> nodes;//存储点
			list<Edge*> incident_list;//存储边
			//接下来就是Ranked Pairs 里的 lock操作,这里才用了拓扑排序来判断是否有环路
			for(int k=0;k<(M-1)*M/2;k++)
			{
				nodes.clear();
				list<int> zero_list;//存储源点
				int src, dst;
				int nodes_num=M;//点数量
				int edges_num=(M-1)*M/2;//边数量
				nodes.push_back(new Node(0));//把第一个空间填上，之后就会从1开始填充vector
				//存储点
				for(int i=1;i<=nodes_num;i++)
					nodes.push_back(new Node(i));
				//存储边
				src=comp[k].second.first;
				dst=comp[k].second.second;
				Edge* e=new Edge(src,dst);
				incident_list.push_back(e);
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
				if(flag==1) {incident_list.pop_back();break;}
			}
			//记录所有点的入度
			list<Edge*>::iterator it,iend;
			it=incident_list.begin();
			iend=incident_list.end();
			for(;it!=iend;it++)
    			nodes[(*it)->dst]->degree_in++;
			for(int i=1;i<=M;i++)
				if(nodes[i]->degree_in==0){winner=i;break;}
			return winner;
		}

		

		int Condorcet_Voting()
		{
			int small_win[M + 1][N + 1] = { 0 };
			int big_win[M + 1] = { 0 };
			int max_win = 0;//record the score of final winner
			vector<int> winners;
			for (int j = 1; j <= N; j++)
			{
				for (int i = 1; i <= M - 1; i++)
					for (int h = i + 1; h <= M; h++)
						if (t[i][j] <= t[h][j]) small_win[i][h]++;//越小越好
						else small_win[h][i]++;
			}
			for (int i = 1; i <= M; i++)
				for (int j = 1; j <= M; j++)
				{
					if (i == j) continue;
					//胜利+1，平均+0，失败-1
					if(small_win[i][j]>small_win[j][i])
						big_win[i] = big_win[i] + 1;
					else if(small_win[i][j]<small_win[j][i])
						big_win[i] = big_win[i] - 1;
				}

			//find the NO.1 and if there is more than 1 person, return the random one
			max_win = big_win[1];
			for (int i = 2; i <= M; i++)
				if (big_win[i] >= max_win) max_win = big_win[i];
			for (int i = 1; i <= M; i++)
				if (big_win[i] == max_win) winners.push_back(i);
			if (winners.size() == 1) return winners[0];
			else
			{
				int randnum;
				randnum = rand() % winners.size();
				return winners[randnum];
			}
		}
};