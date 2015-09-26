#include "common.h"
#include "voting.h"
int main()
{
	int winner = 0;//No.1
	float table[M+1][N+1] = {0};
	ifstream test("d:\\a\\Voting_Program\\table.txt");
	for (int i = 1; i <= M;i++)
		for (int j = 1; j <= N; j++)
			test >> table[i][j];
	cout << "table is " << endl;
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
			cout << table[i][j] << " ";
		cout << endl;
	}
	Voting vv(table);
	winner=vv.voting(2);
	cout << "winner is" << endl;
	cout << winner << endl;
	getchar();
	return 0;
}