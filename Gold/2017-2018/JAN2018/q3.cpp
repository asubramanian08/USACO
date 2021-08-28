// Start: 11:01
// Think: 11:43
// Write: 12:00
// Debug: 12:29,1:39-NA //2/12
//After looking at sol: 3:23-3:34
#include <iostream>
using namespace std;

#define MOD 1000000007

int main(void)
{
    //read
#ifndef HOME
    freopen("spainting.in", "r", stdin);
    freopen("spainting.out", "w", stdout);
#endif
    int stripLen, colors, width;
    cin >> stripLen >> colors >> width;

    //find sum DP down to 1
    long long *sum = new long long[stripLen + 1];
    sum[0] = 0;
    for (int i = 1; i < width; i++)
        sum[i] = (sum[i - 1] * colors + colors) % MOD;
    for (int i = width; i <= stripLen; i++)
        sum[i] = (sum[i - 1] * colors + MOD - ((colors - 1) * sum[i - width]) % MOD) % MOD;

    //fillings without restrictions
    long long fillings = 1;
    for (int i = 1; i <= stripLen; i++)
        fillings = (fillings * colors) % MOD;

    //print and delete
    cout << (fillings + MOD - sum[stripLen] + sum[stripLen - 1]) % MOD << endl;
    delete[] sum;
    return 0;

    /*int stripLen, colors, width;
    cin >> stripLen >> colors >> width;

    //setup
    long long *possible = new long long[stripLen + 1];
    long long waysLess = 0;
    long long choices = colors;
    for (int i = width + 1; i < stripLen; i++)
        choices = (choices * colors) % MOD;
    long long lessPick = choices;
    choices = (choices * colors) % MOD;
    long long same2k = 1;
    for (int i = 2 * width; i <= stripLen; i++)
        same2k = (same2k * colors) % MOD;
    for (int i = 0; i <= stripLen; i++)
        possible[i] = 0;
    possible[width] = choices;

    //find possible
    for (int i = width + 1; i <= stripLen; i++)
    {
        if (i >= width * 2)
            waysLess = (waysLess + same2k) % MOD;
        possible[i] = (MOD + choices - lessPick - waysLess + (waysLess == 0 ? 0 : same2k * colors)) % MOD;
    }

    //print and delete
    long long ans = 0;
    for (int i = width; i <= stripLen; i++)
        ans = (ans + possible[i]) % MOD;
    cout << ans << endl;
    delete[] possible;
    return 0;*/
}