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

		}

};