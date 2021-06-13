#include <iostream>
using namespace std;

int main(void)
{
    //FILE *junk;
    //junk = freopen("money.in", "r", stdin);
    //junk = freopen("money.out", "w", stdout);
    int total, numCoins;
    cin >> numCoins >> total;
    int *coins = new int[numCoins];
    for (int i = 0; i < numCoins; i++)
        cin >> coins[i];
    unsigned long long *DP = new unsigned long long[total + 1];
    for (int i = 0; i <= total; i++)
        DP[i] = 0;
    DP[0] = 1; // one way to get 0
    for (int i = 0; i < numCoins; i++)
        for (int j = 0; j < total; j++)
            if (j + coins[i] <= total)
                DP[j + coins[i]] += DP[j];
    cout << DP[total];
    return 0;
}