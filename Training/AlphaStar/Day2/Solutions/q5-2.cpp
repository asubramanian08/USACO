/*Lewin Gan’s explanation:

It's easiest to view this as a knapsack problem, but we need to find out what our items are.

For any arbitrary tile, let us construct a set of possible weight/cost pairs that we can add into the 
knapsack. We notice that a tile can have value up to at most sqrt(M), since any more than that will go 
over M, so we just construct the set for a tile as { (i*i,(i-tile)^2 }, where i ranges from 1 to sqrt(M), 
and tile is the tile value.

We need to add exactly one item from each set such that the weights add up to M and the costs are minimized.

The way to do this is dynamic programming. Let cost[i][j] denote the item in the set with weight i*i and 
cost (i-tile[j])^2. Then, let dp[i][j] denote the minimum cost to get tiles with weights that sum up to i 
but we only use the first j tiles. The recurrence for dp[i][j] is then dp[i][j] = 
min(dp[i- k*k][j- 1]+cost[k][j-1]), since we need to choose exactly one tile from this set. Iterating 
through this dp-table will take O(N*M^3/2), which will run in time

Sample solution by Brian below:*/

#include <iostream>
#include <fstream>>
using namespace std;
int main()
{
    ifstream in("tilechng.in");
    ofstream out("tilechng.out");
    int N, M;
    in >> N >> M;
    int mincost[M + 1][N + 1];
    int costvector[101][N];
    int tmp;
    for (int n = 0; n < N; n++)
    {
        in >> tmp;
        for (int i = 1; i <= 100; i++)
        {
            costvector[i][n] = (tmp - i) * (tmp - i);
        }
    }
    for (int i = 0; i <= M; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            mincost[i][j] = 10000000;
        }
    }
    mincost[0][0] = 0;
    for (int n = 1; n <= N; n++)
    {
        for (int m = 0; m <= M; m++)
        {
            for (int i = 1; i * i <= m; i++)
            {
                if (mincost[m][n] > mincost[m - i * i][n - 1] + costvector[i][n - 1])
                {
                    mincost[m][n] = mincost[m - i * i][n - 1] + costvector[i][n - 1];
                }
            }
        }
    }
    if (mincost[M][N] == 10000000)
        out << "-1\n";
    else
        out << mincost[M][N] << "\n";
    return 0;
}