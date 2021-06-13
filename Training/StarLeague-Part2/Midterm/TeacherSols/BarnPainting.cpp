// Barn Painting USACO 2017 Dec Gold.cpp : 
// Osman Ay. 2020 Feb.

#include <fstream>
#include <vector>
#include <algorithm>

#define MOD 1000000007

using namespace std;

ifstream cin("barnpainting.in");
ofstream cout("barnpainting.out");

int N, K;
vector<int> color;
vector<vector<int>> adjList;
vector<vector<long long>> dp;
//------------------------------------------
void readInput()
{
	cin >> N >> K;
	adjList.resize(N);
	for (int i = 0; i < N - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		u--; v--;

		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	color.resize(N, -1);
	for (int i = 0; i < K; i++)
	{
		int u, c;
		cin >> u >> c;
		u--; c--;
		color[u] = c;
	}
}
//------------------------------------------
//u: current node, curC: current color, par: parent, parC: parrent color
long long go(int u, int curC, int par, int parC)
{
	if (curC == parC)
		return 0 ;

	if (color[u] >= 0 && color[u] != curC)
		return 0;

	if (dp[u][curC] >= 0)
		return dp[u][curC];

	dp[u][curC] = 1;
	for (int v : adjList[u])
	{
		if (v == par)
			continue;
		long long temp = go(v, 0, u, curC);
		temp %= MOD;
		temp += go(v, 1, u, curC);
		temp %= MOD;
		temp += go(v, 2, u, curC);
		temp %= MOD;
		
		dp[u][curC] *= temp;
		dp[u][curC] %= MOD;
	}

	return dp[u][curC];
}
//------------------------------------------
int main()
{
    readInput();
	dp.resize(N, vector<long long>(3, -1));

	long long res = go(0, 0, -1, -1);
	res += go(0, 1, -1, -1);
	res %= MOD;
	res += go(0, 2, -1, -1);
	res %= MOD;

	cout << res << endl;
}


