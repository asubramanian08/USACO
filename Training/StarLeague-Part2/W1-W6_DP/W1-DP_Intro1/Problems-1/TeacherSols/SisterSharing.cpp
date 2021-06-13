// Sister Sharing Starleague Gold.cpp : DP
// Osman Ay, December 2020

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//ifstream cin("sharing.in");
//ofstream cout("sharing.out");

int goBessie(int, int);
int goElsie(int, int);

int N;
vector<int> bales, preSum;
vector<vector<int>> dpB, dpE;
//---------------------------------------
void readInput()
{
	cin >> N;
	bales.resize(N+1);
	for (int i=1; i<=N; i++)
		cin >> bales[i];
}
//---------------------------------------
int goElsie(int i, int j)
{
	if (dpE[i][j] > 0)
		return dpE[i][j];

	int sum = preSum[j] - preSum[i - 1];
	if (bales[j] >= j - i + 1)
		return dpE[i][j] = sum;

	int temp = 0;
	for (int k = 1; k <= bales[j] && j - k >= i; k++)
		temp = max(temp, sum - goBessie(i, j-k));

	return dpE[i][j] = temp;
}
//---------------------------------------
int goBessie(int i, int j)
{
	if (dpB[i][j] > 0)
		return dpB[i][j];

	int sum = preSum[j] - preSum[i - 1];
	if (bales[i] >= j - i + 1)
		return dpB[i][j] = sum;

	int temp = 0;
	for (int k = 1; k <= bales[i] && i+k <= j; k++)
		temp = max(temp, sum - goElsie(i + k, j));
	
	return dpB[i][j] = temp;
}
//---------------------------------------
int main()
{
    readInput();
	
	dpB.resize(N, vector<int>(N+1, 0));
	dpE.resize(N, vector<int>(N+1, 0));

	preSum.resize(N+1);
	preSum[0] = 0;
	for (int i = 1; i <= N; i++)
		preSum[i] = preSum[i - 1] + bales[i];

	cout << goBessie(1, N) << endl;
}


