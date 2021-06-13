// K-leaf Tree.cpp : DP on a Tree
// Osman Ay. Feb 2020.

#include <fstream>
#include <vector>
#include <algorithm>

#define INF INT_MAX/2

using namespace std;

ifstream cin("leaves.in");
ofstream cout("leaves.out");

int N, K, root;
vector<vector<int>> adjList;

vector<int> W, treeWeight; 		//node weight and tree weight
vector<vector<int>> treeCost;	//treeCost[i][k] cost of tree i for k leaves
vector<int> parent;
//--------------------------------------
void readInput()
{
	cin >> N >> K >> root;
	root--;
	W.resize(N);
	for (int i = 0; i < N; i++)
		cin >> W[i];
	adjList.resize(N);
	for (int i = 0; i < N - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		u--; v--;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
}
//--------------------------------------
//totol weight of each subtree
int subTrees(int u)
{
	int sum = W[u];
	for (int v : adjList[u])
	{
		if (parent[u] == v)
			continue;
		parent[v] = u;
		sum += subTrees(v);
	}
	return treeWeight[u] = sum;
}
//--------------------------------------
void go(int u)
{
	treeCost[u][0] = treeWeight[u];

	treeCost[u][1] = 0;
	vector<int> children;
	for (int v : adjList[u])
	{
		if (parent[u] == v)
			continue;
		children.push_back(v);
		go(v);
	}

	int M = children.size(); //number of children

	//u is a leaf.
	if (M == 0)  
		return;

	//Calculate treeCost[u][1]
	int sum = 0;
	for (int v : children)
		sum += treeWeight[v];
	int bestChild = INF;
	for (int v : children)
	{
		bestChild = min(bestChild, sum - treeWeight[v] + treeCost[v][1]);
	}

	treeCost[u][1] = min(sum, bestChild);


	//Calculate treeCost[u][j] where j>1

	//C[i][j] min cost for j leaves for the first i children.
	vector<vector<int>> C(M, vector<int>(K+1, INF));

	sum = 0;
	for (int i = 0; i < M; i++)
	{
		int v = children[i];
		sum += treeWeight[v];
		for (int j = 0; j <= K; j++)
		{
			if (j == 0) //no leaves
			{
				C[i][j] = sum;
				continue;
			}

			if (i == 0) //only the first child
			{
				C[i][j] = treeCost[v][j];
				continue;
			}
			
			//iterate rest of the children
			C[i][j] = INF;
			for (int k = 0; k <= j; k++)
			{
				C[i][j] = min(C[i][j], C[i - 1][k] + treeCost[v][j - k]);
			}
		}
	}

	for (int j = 2; j <= K; j++)
		treeCost[u][j] = C[M - 1][j];
}
//--------------------------------------
int main()
{
    readInput(); 
	parent.resize(N, -1);
	treeWeight.resize(N, 0);
	subTrees(root);
	treeCost.resize(N, vector<int>(K+1, INF));
	go(root);
	if (treeCost[root][K] == INF)
		cout << "Impossible" << endl;
	else
		cout << treeCost[root][K] << endl;
}

