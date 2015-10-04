#include "common.h"
//M is the number of candidates
//N is the number of voters


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
			else {cout<<"error"<<endl;return 0;}
		}

		bool cmp(pair<float, pair<int,int> > a, pair<float, pair<int,int> > b)
		{
			if(a.first>b.first)return true;
			else return false;    
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
				if (big_score[i] >= big_score[i - 1]) max_score = big_score[i];
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
			vector<pair<float,pair<int,int> > > comp;

			for (int j = 1; j <= N; j++)
			{
				for (int i = 1; i <= M - 1; i++)
					for (int h = i + 1; h <= M; h++)
						if (t[i][j] <= t[h][j]) small_win[i][h]++;
						else small_win[h][i]++;
			}
			for (int i = 1; i <= M; i++)
				for (int j = 1; j <= M; j++)
				{
					if (i == j) continue;
					if(small_win[i][j]<((M-1)/2.0)) 
					{
						pair<int, int> p0(j,i);
						pair<float, pair<int,int> > p((M-1-small_win[i][j])/(M-1),p0);
						comp.push_back(p);
					}
					else
					{
						pair<int, int> p0(i,j);
						pair<float, pair<int,int> > p(small_win[i][j]/(M-1),p0);
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

			return 0;
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
						if (t[i][j] <= t[h][j]) small_win[i][h]++;
						else small_win[h][i]++;
			}
			for (int i = 1; i <= M; i++)
				for (int j = 1; j <= M; j++)
				{
					if (i == j) continue;
					big_win[i] = big_win[i] + small_win[i][j];
				}

			//find the NO.1 and if there is more than 1 person, return the random one
			max_win = big_win[1];
			for (int i = 2; i <= M; i++)
				if (big_win[i] >= big_win[i - 1]) max_win = big_win[i];
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