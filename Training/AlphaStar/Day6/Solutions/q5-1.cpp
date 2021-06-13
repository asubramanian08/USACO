/*USACO MAR09 Problem 'fristeam' Analysis by Neal Wu

This is a standard dynamic programming (DP) problem. We first allow the empty set to be used and will subtract 
one from our result to fix this later. We define the function f(n, s) [where 0 <= n <= N and 0 <= s < F] to be 
the number of subsets of the first n numbers such that the sum of the numbers is equivalent to s (mod F). Then we 
have the following recurrence:

f(n + 1, s) = f(n, s) + f(n, (s - cow [n] + F) % F)

Thus, we can iterate over all cows and sums, and calculate the values of our DP table in O(NF) time; our answer 
is then f(N, 0) - 1. */

#include <cstdio>
using namespace std;
FILE *fin = fopen("fristeam.in", "r");
FILE *fout = fopen("fristeam.out", "w");
const int MAXN = 2005, MAXF = 1005, MOD = 100000000;
int N, F, R, dp[MAXN][MAXF];
// dp [n][k] = the number of ways we can obtain a rating sum of k (mod F)
//             with some of the first n cows
int main(void)
{
    fscanf(fin, "%d %d", &N, &F);
    dp[0][0] = 1; /* we can obtain a sum of 0 with 0 cows */
    for (int i = 0; i < N; i++)
    {
        fscanf(fin, "%d", &R);
        for (int j = 0; j < F; j++)
        {
            dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD;
            /* don't put cow i in the team */
            dp[i + 1][(j + R) % F] = (dp[i + 1][(j + R) % F] + dp[i][j]) % MOD;
            /* put cow i in the team */
        }
    }
    fprintf(fout, "%d\n", (dp[N][0] - 1 + MOD) % MOD);
    /* subtract 1 for the empty set of cows - note that we add MOD again in case dp [N][0] is equal to 0 */
    return 0;
}