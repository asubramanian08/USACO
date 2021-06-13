// Grazing Starleague Gold.cpp : DP on a grid.
// Osman Ay, December 2020.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//ifstream cin("grazing.in");
//fstream cout("grazing.out");

int main()
{
	int N;
	cin >> N;
	vector<vector<int>> grid(N, vector<int>(N));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> grid[i][j];

	vector<vector<int>> dp(N, vector<int>(N));

	dp[0][0] = grid[0][0];
	for (int i = 1; i < N; i++)
	{
		dp[0][i] = dp[0][i - 1] + grid[0][i];
		dp[i][0] = dp[i - 1][0] + grid[i][0];
	}

	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++)
			dp[i][j] = grid[i][j] + max(dp[i - 1][j - 1], max(dp[i - 1][j], dp[i][j - 1]));

	cout << dp[N - 1][N - 1] << endl;
}


