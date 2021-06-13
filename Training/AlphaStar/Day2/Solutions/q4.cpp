/*USACO NOV09 Problem 'xoinc' Analysis by Hanson Wang

A glance at the problem statement suggests a DP solution. To determine the optimal move for a state, we 
only need to know which coins are left (an integer from 0..N) and the number of coins the previous player
removed (an integer from 1..N).

For each state we wish to calculate how much a player can get if he plays optimally. To do this, we can 
try all possible moves (by enumerating the number of coins you remove). Once you remove x coins, you hand
the game over to the other player and the state changes to have (coins - x) coins remaining, and x coins
from the last turn. Now, given the amount of coins the other person can take in the best case, the number
of coins you can take is simply the remaining coins minus the amount of coins the other person can take.

Expressed as a formula:

Let best[c][p] be the best amount you can achieve with the coins from 1..c left, and the last player 
having removed p coins:

best[0][*] = 0 (since you've got nothing left)

best[c][p] = max{i=1 to min(2*p, c)} of sum_coins[c-i+1..c] +

(sum_coins[1..c-i] - best[c-i][i]) = max{i=1 to min(2*p, c)} of sum_coins[1..c] - best[c-i][i]

ans = best[N][1]

We can precalculate sum_coins easily, but the main problem here is that since there are N^2 states and 
each state transition is O(N), the overall running time is O(N^3).

To optimize this down to a manageable O(N^2), we notice that there is a lot of overlap in the transition 
states of best[c][p] and best[c][p+1]:

best[c][p] = max{i=1 to min(2*p, c)} of sum_coins[c] - best[c-i][i] best[c][p+1] = max{i=1 to min(2*(p+1),
c)} of sum_coins[c] - best[c-i][i]

= max{best[c][p], sum_coins[c] - best[c-(2*p+1)][2*p+1], sum_coins[c] - best[c-(2*p+2)][2*p+2]}

Of course, there are some boundary cases to take care of where 2*p+1 > c or 2*p+2 > c, but these can be 
taken care of quite easily.

Now that we have the recurrence relation, the code follows quite easily. 

My solution: */

#include <iostream>
using namespace std;
int a[2011];
int sum[2011]; //globals are auto-initialized to 0 :D
int dp[2011][2011];
int main()
{
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) //it's a stack, so read in reverse
        cin >> a[N - i + 1];
    for (int i = 1; i <= N; i++)
        sum[i] = sum[i - 1] + a[i];
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
        {
            dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            if (i >= 2 * j - 1)
                dp[i][j] = max(dp[i][j], sum[i] - dp[i - (2 * j - 1)][2 * j - 1]);
            if (i >= 2 * j)
                dp[i][j] = max(dp[i][j], sum[i] - dp[i - 2 * j][2 * j]);
        }
    cout << dp[N][1] << endl;
    return 0;
}