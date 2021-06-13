/*USACO DEC11 Problem 'umbrella' Analysis by Neal Wu

First note that "Larger umbrellas do not necessarily cost more than smaller umbrellas" is not an issue: 
since we are allowed to overlap umbrellas, we can precompute the minimum cost of covering any particular 
length (at minimum) in O(M) time.

At this point the problem simply becomes a traditional dynamic programming problem: after sorting the cows, 
we just need to divide them into contiguous groups, each of which we cover with an umbrella. This is a 
dynamic programming problem with N + 1 states (where dp[n] is the minimum cost to cover cows 1 through n); 
to compute each value we simply look at all possible last intervals, for an overall O(N^2 + M) algorithm. 
See the code below for more details.*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *in = fopen("umbrella.in", "r"), *out = fopen("umbrella.out", "w");
const int MAXN = 5005, MAXM = 100005;
int N, M, X[MAXN], min_len_cost[MAXM];
int dp[MAXN];
int main()
{
    fscanf(in, "%d %d", &N, &M);
    for (int i = 0; i < N; i++)
        fscanf(in, "%d", X + i);
    sort(X, X + N);
    for (int i = 0; i < M; i++)
        fscanf(in, "%d", min_len_cost + i);
    for (int i = M - 2; i >= 0; i--)
        min_len_cost[i] = min(min_len_cost[i], min_len_cost[i + 1]);
    memset(dp, 63, sizeof(dp));
    dp[0] = 0;
    for (int n = 1; n <= N; n++)
        for (int i = 0; i < n; i++)
            dp[n] = min(dp[n], dp[i] + min_len_cost[X[n - 1] - X[i]]);
    fprintf(out, "%d\n", dp[N]);
    return 0;
}