// Start: 11:21
// Think: 12:16,
// Write:
// Debug:
//After looking at sol: 2:28-3:18
#include <iostream>
#include <algorithm>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("nochange.in", "r", stdin);
    freopen("nochange.out", "w", stdout);
#endif
    int numCoins, numPerch;
    cin >> numCoins >> numPerch;
    int *coins = new int[numCoins];
    for (int i = 0; i < numCoins; i++)
        cin >> coins[i];
    int *prefixPerch = new int[numPerch];
    int perch, last = 0;
    for (int i = 0; i < numPerch; i++)
    {
        cin >> perch;
        prefixPerch[i] = last + perch;
        last = prefixPerch[i];
    }

    //fill in the DP
    int *DP = new int[1 << numCoins];
    fill(DP, DP + (1 << numCoins), 0);
    long long ans = -1, rem;
    for (int coinSubset = 1; coinSubset < 1 << numCoins; coinSubset++)
    {
        rem = 0;
        for (int i = 0; i < numCoins; i++)
            if (coinSubset & (1 << i))
            {
                int prev = DP[coinSubset ^ (1 << i)] - 1;
                prev = prev == -1 ? 0 : prefixPerch[prev];
                int find = upper_bound(prefixPerch, prefixPerch + numPerch, prev + coins[i]) - prefixPerch;
                DP[coinSubset] = max(DP[coinSubset], find);
            }
            else
                rem += coins[i];
        if (DP[coinSubset] == numPerch)
            ans = max(ans, rem);
    }

    //print and delete
    cout << ans << endl;
    delete[] coins;
    delete[] prefixPerch;
    delete[] DP;
    return 0;
}