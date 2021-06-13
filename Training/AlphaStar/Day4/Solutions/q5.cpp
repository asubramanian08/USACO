/*USACO FEB09 Problem 'surround' Analysis by Fatih Gelgi

This is a simple Graph Theory problem. Observe that the question asks to find a central island that 
connects the other islands with minimum total cost. Traveling around an island doesn't matter since we can 
start at any location, move a couple of vertices, travel to another island, return from the same route, 
and continue to surround the same island. So we can use any vertex in an island to travel to any vertex of 
another island. That means, to travel between any two islands, we always choose the vertices with minimum 
cost between these two islands.

Hence, we can solve the problem by contracting vertices in an islands. We can determine the islands using 
Depth First Search (DFS) and contract them. Note that the travel cost between two islands is the minimum 
cost of the vertices between two islands. The solution is twice the sum of the minimum cost due to the 
returns following the same route between the islands.

Consider the example given in the question:

  1        10            4
    xxxxxxx              x
   xxxxxxxxx            xxxx
7 xxx I1 xxxx 6        x I2 xx
 xxxxxxxxxxx       11 xxxxxxxxxx 5
  xxxxxxx
   xxx
  3         12 xxxxxxx 2
              xxxxxxxx
              xxxxxxxx
             xxxxxxxxx
             xx I3 xxx
            xxxxxxxxxx
            xxxxxxxxxx
          8 xxxxxxxxxx 9

After contracting the vertices of three islands, the graph reduces to:
         8
I1 ------------- I2
 \               /
   \           /
  7  \       / 8
       \   / 
         I3

The cost between island 1 (I1) to island 2 (I2) is 8 since the minimum cost of the vertices between these 
two islands is 8 (from 1 to 11). Travel costs between islands (I1, I3) is 7 (from 1 to 12), and (I2, I3) 
is 8 (from 9 to 11). For the example above, the minimum cost is (7 + 8) * 2 = 30.

The solution requires O(N^2) memory to keep the cost matrix and the contracted graph. Contracting requires 
O(N^2) time utilizing an adjacency matrix. */

/* DFS - O(N^2) */
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;
#define MAX 500
#define INF 1000000000
int m, l[MAX][MAX];
list<int> g[MAX];
int n, island[MAX], mat[MAX][MAX];
// DFS
void dfs(int x)
{
    island[x] = n;
    for (list<int>::iterator i = g[x].begin(); i != g[x].end(); i++)
        if (!island[*i])
            dfs(*i);
}

// contract the vertices in the same island
void contract()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = INF;
    // choose minimum cost between islands
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if (mat[island[i] - 1][island[j] - 1] > l[i][j])
                mat[island[i] - 1][island[j] - 1] = l[i][j];
}

// Find a central island that connects the islands // with minimum total cost
int solve()
{
    int cost = 1000000000;
    // i is the central island
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; sum += mat[i][j++])
            ;
        if (cost > sum)
            cost = sum;
    }
    return cost;
}

int main()
{
    cin >> m;
    int v1, v2;
    for (int i = 0; i < m; i++)
    {
        cin >> v1 >> v2;
        g[--v1].push_back(--v2);
        g[v2].push_back(v1);
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            cin >> l[i][j];
    // identify islands using DFS
    for (int i = 0; i < m; i++)
        if (!island[i])
        {
            n++;
            dfs(i);
        }
    contract();
    cout << 2 * solve() << endl;
}