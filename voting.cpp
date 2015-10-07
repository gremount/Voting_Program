#include "common.h"
#include "voting.h"
int main()
{
	int winner = 0;//No.1
	float table[M+1][N+1] = {0};
	int ranking[N+1]={0};
	ifstream test("d:\\a\\Voting_Program\\table.txt");
	for(int i=1;i<=N;i++)
		test >> ranking[i];
	for (int i = 1; i <= M;i++)
		for (int j = 1; j <= N; j++)
			test >> table[i][j];
	cout << "votes are: "<<endl;
	for(int i=1;i<=N;i++)
		cout<<ranking[i]<<" ";
	cout<<endl<<endl;
	cout << "table is " << endl;
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
			cout << table[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "results are:"<<endl;
	Voting vv(table,ranking);
	winner=vv.voting(1);
	cout<<"schulze method : "<<endl;
	cout<<winner<<endl;
	winner=vv.voting(2);
	cout << "comulative winner is" << endl;
	cout << winner << endl;
	winner=vv.voting(3);
	cout << "condorcet winner is" << endl;
	cout << winner << endl;
	winner=vv.voting(4);
	cout << "ranked pairs winner is" << endl;
	cout << winner << endl;
	
	getchar();
	return 0;
}