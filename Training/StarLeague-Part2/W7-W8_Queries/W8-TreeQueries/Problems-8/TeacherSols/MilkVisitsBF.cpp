// Milk Visits Usaco Gold Brute Force.cpp : Brute force solution with LCA.
// Osman Ay. November 2020.

#include <fstream>
#include <vector>

using namespace std;

ifstream cin("milkvisits.in");
ofstream cout("milkvisits.out");

int N, M;
vector<int> milkTypes, parents, depths;
vector<vector<int>> adjList;
//---------------------------------------
void readInput()
{
	cin >> N >> M;
	
	milkTypes.resize(N + 1);
	for (int i=1; i<=N; i++)
		cin >> milkTypes[i];

	adjList.resize(N + 1);
	for (int i = 1; i < N; i++)
	{
		int u, v;
		cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
}
//---------------------------------------
void dfs(int u, int d) //current node, depth
{
	depths[u] = d;
	for (int v : adjList[u])
	{
		if (parents[u] != v)
		{
			parents[v] = u;
			dfs(v, d + 1);
		}
	}
}
//---------------------------------------
bool go(int u, int v, int type)
{
	while (depths[u] > depths[v])
	{
		if (milkTypes[u] == type)
			return true;
		u = parents[u];
	}

	while (depths[v] > depths[u])
	{
		if (milkTypes[v] == type)
			return true;
		v = parents[v];
	}

	while (u != v)
	{
		if (milkTypes[u] == type || milkTypes[v] == type)
			return true;
		u = parents[u];
		v = parents[v];
	}

	if (milkTypes[u] == type || milkTypes[v] == type)
		return true;

	return false;
}
//---------------------------------------
int main()
{
	readInput();

	parents.resize(N + 1);
	depths.resize(N + 1);
	dfs(1, 0);

	for (int i = 0; i < M; i++)
	{
		int u, v, type;
		cin >> u >> v >> type;
		cout << go(u, v, type);
	}
}

