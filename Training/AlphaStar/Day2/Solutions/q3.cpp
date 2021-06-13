/*
USACO DEC13 Problem 'vacation' (Silver) Analysis by Fatih Gelgi
The problem asks to find the minimum cost for each trip request from a_i to b_i through at least one of 
the hubs. In this case, computing all shortest path pairs using Floyd-Warshall algorithm will be 
sufficient for us (note that, N<=200 hence O(N^3) running time is fast enough for the problem).Then the 
answer of a minimum cost request (a_i,b_i) will be min_x {mincost[a_i,x] + mincost[x,b_i]} where x is a 
hub and mincost is the distance matrix obtained by Floyd- Warshall.bA sample solution is provided as 
follows: */
#include <fstream>
#include <algorithm>
#define MAX 201
#define INF 1000000000
using namespace std;
int n, m, k, q, mat[MAX][MAX], cnt;
long long sum;
int main()
{
    ifstream fin("vacation.in");
    fin >> n >> m >> k >> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
                mat[i][j] = INF;
    int u, v, d;
    for (int i = 0; i < m; i++)
    {
        fin >> u >> v >> d;
        mat[--u][--v] = d;
    }
    // Floyd-Warshall
    for (int x = 0; x < n; x++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = min(mat[i][j], mat[i][x] + mat[x][j]);
    for (int i = 0; i < q; i++)
    {
        fin >> u >> v;
        int cost = INF;
        for (int j = 0; j < k; j++)
            cost = min(cost, mat[u - 1][j] + mat[j][v - 1]);
        if (cost != INF)
            cnt++, sum += cost;
    }
    ofstream fout("vacation.out");
    fout << cnt << "\n"
         << sum << "\n";
}