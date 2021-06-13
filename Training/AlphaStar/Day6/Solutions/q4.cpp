/*USACO JAN18 Problem 'atlarge' Analysis by Dhruv Rohatgi

In this problem we are given a rooted tree, where Bessie starts at the root, and we must determine the minimum 
number of farmers, each starting at a leaf of the tree, needed to ensure that Bessie cannot reach a leaf before 
she is caught.

First observe that it is always optimal for Bessie to move away from the root of the tree (assuming that she does 
not seek to delay her capture, when it proves inevitable). If she were to move toward the root, then this means 
she is undoing her previous move, which is a waste of time. Since Bessie has perfect information (and infinite 
mental power), this situation would never arise.

We can similarly observe that it is always optimal for farmers to move towards the root of the tree. If a farmer 
is moving away from the root, he is either moving away from Bessie, which is pointless, or Bessie is in his 
subtree, which means that he will not be able to catch Bessie, so he may as well stay put.

So every simple path from the root to a leaf defines a potential escape route. The farmers' moves are 
predetermined; Bessie knows this, so she will escape if and only if there exists a feasible escape route. For an 
escape route to be feasible, Bessie must be able to reach each point on the route before a farmer reaches that 
same point. That is, every point on the route must be closer to the root of the tree than to the nearest 
farmer-occupied leaf.

Consider some arrangement of farmers for which Bessie has no feasible escape routes. Consider any barn which is 
closer to the root than to the nearest leaf (farmer-occupied or not). Then Bessie can reach this barn without 
being caught. And for Bessie to be unable to escape, there must be a farmer in every child subtree of this barn. 
Conversely, if every such barn has a farmer in every child subtree, then Bessie obviously cannot escape.

Thus, the number of farmers needed to thwart Bessie's escape is equal to the number of barns which satisfy the 
following two conditions: - the barn's parent is closer to the root than to the nearest leaf - but the barn 
itself is at least as far from the root as from the nearest leaf.

The second condition is needed to prevent double-counting.

To count the number of barns satisfying the above conditions, we compute each node's distance-to-root and 
distance-to-nearest-leaf. The former can be computed for all nodes with a single depth-first search, and the 
latter can be computed for all nodes with a breadth-first search starting at the leaves. Alternatively, we can 
use a depth-first search to compute for each node the nearest leaf in its subtree, and then use a second 
depth-first search to take care of leaves outside the subtree.

The latter method is implemented below. */

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXN 100000
vector<int> edges[MAXN];
int distLeaf[MAXN];
int distStart[MAXN];
int ans;
void dfsDistances(int i, int par)
{
    distLeaf[i] = MAXN + 1;
    if (par != -1)
        distStart[i] = 1 + distStart[par];
    else
        distStart[i] = 0;
    bool isLeaf = 1;
    for (int j = 0; j < edges[i].size(); j++)
        if (par != edges[i][j])
        {
            dfsDistances(edges[i][j], i);
            distLeaf[i] = min(distLeaf[i], 1 + distLeaf[edges[i][j]]);
            isLeaf = 0;
        }
    if (isLeaf)
        distLeaf[i] = 0;
}
void dfsDistances2(int i, int par)
{
    if (par != -1)
        distLeaf[i] = min(distLeaf[i], distLeaf[par] + 1);
    for (int j = 0; j < edges[i].size(); j++)
        if (par != edges[i][j])
            dfsDistances2(edges[i][j], i);
}
void dfs(int i, int par)
{
    if ((par != -1) && (distLeaf[i] <= distStart[i]) && (distLeaf[par] > distStart[par]))
        ans++;
    for (int j = 0; j < edges[i].size(); j++)
        if (edges[i][j] != par)
            dfs(edges[i][j], i);
}
int main()
{
    int K;
    int N, a, b;
    cin >> N >> K;
    K--;
    for (int i = 1; i < N; i++)
    {
        cin >> a >> b;
        a--, b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    for (int i = K; i < K + 1; i++)
    {
        if (edges[i].size() == 1)
        {
            cout << 1 << '\n';
            continue;
        }
        ans = 0;
        dfsDistances(i, -1);
        dfsDistances2(i, -1);
        dfs(i, -1);
        cout << ans << '\n';
    }
}