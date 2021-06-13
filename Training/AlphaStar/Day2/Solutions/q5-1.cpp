/*
USACO NOV11 Problem 'tilechng' Analysis by Brian Dean

This problem is solved with dynamic programming. Let best[i][j] denote the minimum cost of building a 
total area of i by exchanging only tiles 1 through j (or infinity if it is impossible to do so). As a base
case, we have best[0][0] = 0 and best[i>0][0] = infinity. Otherwise, we can compute best[i][j] using the 
following recursive formula:

best[i][j] = min (k-A[j])^2 + best[i-k*k][j-1]

where the minimum is taken over k, the side length of the tile we exchange for the final tile j. The 
formula above can be interpreted as saying that the cost of an optimal solution for subproblem best[i][j] 
that ends by exchanging tile j for one of side length k is given by the cost of the exchange, (k-A[j])^2, 
plus the optimal cost for building the remaining area of i-k*k using only the remaining tiles 1 through 
j-1. Since k*k <= i <= M and j <= N, the total number of iterations of the inner loop of this solution is 
at most 10*100*10,000 = 10 million, so this solution should easily run in time.

Note that the statement for this problem did not specify whether exchanges for zero-area tiles were 
allowed, so we designed our test data so that this case would not be an issue (i.e., programs should get 
correct answers regardless of which assumption they make concerning exchanges for zero-area tiles). */

#include <stdio.h>
#define MAX_M 10000
#define MAX_N 10
#define INF 1000000000
int best[MAX_M + 1][MAX_N + 1];
int A[MAX_M + 1];
int main(void)
{
    int M, N, i, j, k;
    freopen("tilechng.in", "r", stdin);
    freopen("tilechng.out", "w", stdout);
    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; i++)
        scanf("%d", &A[i]);
    for (i = 1; i <= M; i++)
        best[i][0] = INF;
    for (j = 1; j <= N; j++)
        for (i = 0; i <= M; i++)
        {
            best[i][j] = INF;
            for (k = 1; k * k <= i; k++)
                if ((A[j] - k) * (A[j] - k) + best[i - k * k][j - 1] < best[i][j])
                    best[i][j] = (A[j] - k) * (A[j] - k) + best[i - k * k][j - 1];
        }
    if (best[M][N] == INF)
        printf("-1\n");
    else
        printf("%d\n", best[M][N]);
    return 0;
}