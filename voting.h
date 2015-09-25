#include "common.h"
#define M 3 //the number of candidates
#define N 3 //the number of voters

class Voting
{
	private:
	public:
		float t[M][N];
		Voting(float table[M][N])
		{
			for(int i=1;i<=M;i++)
				for(int j=1;j<=N;j++)
					t[i][j]=table[i][j];
		}
		int voting(int k)
		{
			if(k==2) return Comulative_Voting();
			else if(k==3) return Condorcet_Voting();
			else {cout<<"error"<<endl;return 0;}
		}
		int Comulative_Voting()
		{

		}
		int Condorcet_Voting()
		{
			int small_win[M][N] = {0};
			int big_win[M] = {0};
			for (int j = 1; j <= N; j++)
			{
				for (int i = 1; i <= M - 1; i++)
					for (int h = i + 1; h <= M; h++)
						if (t[i][j] >= t[h][j]) small_win[i][h]++;
						else small_win[h][i]++;
			}
			for (int i = 1; i <= M; i++)
				for (int j = 1; j <= M; j++)
				{
					if (i == j) continue;
					big_win[i]

				}

		}

};