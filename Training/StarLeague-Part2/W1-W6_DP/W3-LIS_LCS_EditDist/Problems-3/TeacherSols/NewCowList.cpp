// New Cow List Starleague Gold.cpp : Edit Distance.
// Osman Ay, December 2020.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define SIZE 1005

using namespace std;

//ifstream cin("cowlist.in");
//ofstream cout("cowlist.out");

int N, del, ins, rep;
vector<string> s1, s2;
vector<vector<int>> dp(SIZE + 1, vector<int>(SIZE + 1));
//--------------------------------
void readInput()
{
	cin >> N;
	s1.resize(N);
	s2.resize(N);
	for (int i = 0; i < N; i++)
		cin >> s1[i] >> s2[i];
	cin >> del >> ins >> rep;
}
//--------------------------------
int go(string w1, string w2)
{
	int cost = 0, n = w1.length(), m = w2.length();


	for(int i=1; i<=n; i++)
		for (int j = 1; j <= m; j++)
		{
			dp[i][j] = min(dp[i][j - 1] + ins, dp[i - 1][j] + del);
			
			if (w1[i - 1] == w2[j - 1])
				dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
			else
				dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + rep);
		}

	return dp[n][m];
}
//--------------------------------
int main()
{
    readInput(); 

	for (int i = 1; i <= SIZE; i++)
	{
		dp[i][0] = dp[i - 1][0] + del;
		dp[0][i] = dp[0][i - 1] + ins;
	}

	int res = 0;
	for(int i=0; i<N; i++)
		res += go(s1[i], s2[i]);

	cout << res;
}
