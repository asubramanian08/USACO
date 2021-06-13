// Christmas Tree Starleague Gold.cpp : DP on a tree. O(N)
// Osman Ay, Jan 2021.

#include <iostream>
#include <vector>
#include <algorithm>

#define BIGNUM 1000000

using namespace std;

//ifstream cin("tree.in");
//ofstream cout("tree.out");

//two switch operations (off, on) and two bulb states (zero, one)
struct Node
{
	int offZero, offOne, onZero, onOne;
};

int N, root;
vector<int> states;
vector<vector<int>> adjList;
//--------------------------------------
void readInput()
{
	cin >> N;
	states.resize(N + 1);
	for (int i = 1; i <= N; i++)
		cin >> states[i];

	adjList.resize(N + 1);
	for (int i = 0; i < N - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
}
//--------------------------------------
//u is the current root, p is its parent
Node go(int u, int p)
{
	Node res = { 0, BIGNUM, BIGNUM, 1 };
	if (states[u] == 1)
		res = { BIGNUM, 0, 1, BIGNUM };

	Node child1, child2;
	bool found1 = false, found2 = false;
	for (int v : adjList[u])
	{
		if (v == p)
			continue;
		if (!found1)
		{
			child1 = go(v, u);
			found1 = true;
		}
		else 
		{
			child2 = go(v, u);
			found2 = true;
		}
	}

	if (!found1)	//leaf node
		return res;

	if (!found2)	//single child
	{
		//res = { BIGNUM, BIGNUM, BIGNUM, BIGNUM };
		if (states[u] == 0)
		{
			res.offZero = child1.offOne;
			res.offOne = child1.onOne;
			res.onZero = child1.onZero + 1;
			res.onOne = child1.offZero + 1;
		}
		else //states[u] ==1)
		{
			res.offZero = child1.onOne;
			res.offOne = child1.offOne;
			res.onZero = child1.offZero + 1;
			res.onOne = child1.onZero + 1;
		}

		return res;
	}
	
	//res = { BIGNUM, BIGNUM, BIGNUM, BIGNUM };

	if (states[u] == 0)
	{
		res.offZero = min(BIGNUM, child1.offOne + child2.offOne);
		res.offZero = min(res.offZero, min(BIGNUM, child1.onOne + child2.onOne));

		res.offOne = min(BIGNUM, child1.onOne + child2.offOne);
		res.offOne = min(res.offOne, min(BIGNUM, child1.offOne + child2.onOne));

		res.onZero = min(BIGNUM, child1.onZero + child2.offZero + 1);
		res.onZero = min(res.onZero, min(BIGNUM, child1.offZero + child2.onZero + 1));

		res.onOne = min(BIGNUM, child1.offZero + child2.offZero + 1);
		res.onOne = min(res.onOne, min(BIGNUM, child1.onZero + child2.onZero + 1));
	}
	else // if (states[u] == 1
	{
		res.offZero = min(BIGNUM, child1.onOne + child2.offOne);
		res.offZero = min(res.offZero, min(BIGNUM, child1.offOne + child2.onOne));

		res.offOne = min(BIGNUM, child1.offOne + child2.offOne);
		res.offOne = min(res.offOne, min(BIGNUM, child1.onOne + child2.onOne));

		res.onZero = min(BIGNUM, child1.offZero + child2.offZero + 1);
		res.onZero = min(res.onZero, min(BIGNUM, child1.onZero + child2.onZero + 1));

		res.onOne = min(BIGNUM, child1.offZero + child2.onZero + 1);
		res.onOne = min(res.onOne, min(BIGNUM, child1.onZero + child2.offZero + 1));
	}

	return res;
}
//--------------------------------------
int main()
{
    readInput(); 
    
    for(int i=1; i<=N; i++)
        if(adjList[i].size() < 3)
        {
            root = i;
            break;
        }
    
	Node rootResult = go(root, root);

	if (rootResult.offOne >= BIGNUM && rootResult.onOne >= BIGNUM)
		cout << "Impossible" << endl;
	else
		cout << min(rootResult.offOne, rootResult.onOne) << endl;
}

