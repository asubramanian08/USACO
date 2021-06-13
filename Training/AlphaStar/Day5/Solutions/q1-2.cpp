/*We now turn to slightly more algorithmically advanced techniques, which we discuss here for completeness.
It is often possible to turn O(n!) algorithms into O(2^n) algorithms with dynamic programming (Traveling 
Salesman is a classic example); let's try it here. Define f(set) to be the minimum cost arrangement given 
that the cows in set are in the first |set| positions. This, unfortunately, isn't well-defined; it depends 
on what order the cows are in, which is exactly what we were trying to forget in the first place!

The problem with the previous approach was that we needed to remember where we placed cows so we could pay 
for their friendships later. We can salvage the idea by paying for friendships incrementally, not all at 
once. Imagine placing 1 cow at a time, and building 1 segment of wire in that position for each friendship 
that will need to cross it. We can compute the number of friendships that need to cross a particular cow 
given only the set of cows that have been placed (it is just the number of friendships between cows in the 
set and cows outside of the set). And if we place all the cows in this way, paying for one segment of wire 
at a time, when we get to the end we will have paid for all the wire we needed for this arrangement.

This solution runs in O(2^n * n). There are 2^n subsets, and n choices for which cow to add next.

One little programming trick: the C++ solution below keeps track of set (the set of cows used so far) and
out (the number of friendships that are between a cow in set and a cow not in set), even though out is not
part of the DP state. This is OK, because out is uniquely determined by set. Maintaining information that 
is not part of your DP state but is determined by it often leads to more convenient code.

Here is a C++ implementation of the DP idea: */

#include <iostream>
using namespace std;
#define NMAX 12
#define infinite 1000000000
int dp[1 << NMAX];
int main()
{
#ifndef HOME
#endif
    freopen("haywire.in", "r", stdin);
    freopen("haywire.out", "w", stdout);
    int n;
    scanf("%d", &n);
    int a1[12], a2[12], a3[12];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &a1[i], &a2[i], &a3[i]);
        a1[i]--;
        a2[i]--;
        a3[i]--;
    }
    dp[0] = 0;
    for (int subset = 1; subset < (1 << n); subset++)
    {
        int totalOut = 0;
        for (int i = 0; i < n; i++)
        {
            if (subset & (1 << i))
            {
                totalOut += 3 - (((subset >> a1[i]) & 1) + ((subset >> a2[i]) & 1) + ((subset >> a3[i]) & 1));
            }
        }
        dp[subset] = infinite;
        for (int i = 0; i < n; i++)
        {
            if (subset & (1 << i))
            {
                int cost = totalOut - 3 + 2 * (((subset >> a1[i]) & 1) + ((subset >> a2[i]) & 1) + ((subset >> a3[i]) & 1));
                dp[subset] = min(dp[subset], dp[subset & ~(1 << i)] + cost);
            }
        }
    }
    printf("%d\n", dp[(1 << n) - 1]);
}