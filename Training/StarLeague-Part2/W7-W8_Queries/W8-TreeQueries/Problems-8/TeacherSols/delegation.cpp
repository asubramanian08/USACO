// Delegation Usaco 2020 Feb Gold.cpp : DP on a Tree

#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

ifstream cin("deleg.in");
ofstream cout("deleg.out");

const int SIZE = 1e5 + 1;

int N, M;
vector<int> adjList[SIZE], subTree[SIZE];

//-------------------------------------
void readInput()
{
	cin >> N;
	for (int i = 1; i < N; i++)
	{
		int u, v;
		cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
}
//-------------------------------------
int dfs(int u, int p)
{
	for (int &v : adjList[u])
	{
		if (v == p)
			continue;
		int temp = dfs(v, u);
		subTree[u].push_back(temp + 1);
	}

	int sum = accumulate(subTree[u].begin(), subTree[u].end(), 0);
	if (sum < M)
		subTree[u].push_back(M - sum);
	return sum;
}
//-------------------------------------
int go(int k)
{	
	if (M%k > 0)
		return 0;

	vector<int> freq(k + 1, 0);

	for (int i = 1; i <= N; i++)
	{
		int count = 0;

		for (int x : subTree[i])
		{
			int rem = x % k;
			if (rem == 0)
				continue;

			int other = k - rem;
			if (freq[other] > 0)
			{
				freq[other]--;
				count--;
			}
			else
			{
				freq[rem]++;
				count++;
			}
		}

		if (count != 0)
			return 0;
	}
	return 1;
}
//-------------------------------------
int main()
{
    readInput();
	M = N - 1;
	
	dfs(1, 0);

	cout << 1;
	for (int i = 2; i <= M; i++)
		cout<<go(i);
}