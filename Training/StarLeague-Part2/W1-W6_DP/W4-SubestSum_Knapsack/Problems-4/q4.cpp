//This was changed from my original (not working) code to match the teacher solution
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int main(void)
{
    // FILE *junk;
    // junk = freopen("exercise.in", "r", stdin);
    // junk = freopen("exercise.out", "w", stdout);
    int permLen;
    long long mod;
    cin >> permLen >> mod;
    vector<int> prime;
    long long *DP = new long long[permLen + 1];
    memset(DP, 0, sizeof(long long) * (permLen + 1));
    DP[0] = 1;
    long long *temp = new long long[permLen + 1];
    bool isPrime;
    for (int i = 2; i <= permLen; i++)
    {
        isPrime = true;
        for (int j = 0; j < prime.size(); j++)
            if (i % prime[j] == 0)
            {
                isPrime = false;
                break;
            }
        if (!isPrime)
            continue;
        prime.push_back(i);
        memset(temp, 0, sizeof(long long) * (permLen + 1));
        for (int k = i; k <= permLen; k *= i)
            for (int j = 0; j + k <= permLen; j++)
                temp[j + k] += (DP[j] * k) % mod;
        for (int j = 0; j <= permLen; j++)
            DP[j] += temp[j];
    }
    int ans = 0;
    for (int i = 0; i <= permLen; i++)
        ans = (ans + DP[i]) % mod;
    /*long long addBack = 0, currNum;
    for (long long i = 2; i <= permLen; i++)
    {
        isPrime = false;
        for (int j = 0; j < prime.size(); j++)
            if (i == prime[j])
            {
                isPrime = true;
                break;
            }
        if (isPrime)
            continue;
        currNum = i;
        for (int j = 0; j < prime.size(); j++)
        {
            if (currNum % prime[j] == 0)
                currNum /= prime[j];
            if (currNum % prime[j] == 0 || currNum == 1)
                break;
        }
        if (currNum != 1)
            addBack = (addBack + i) % mod;
    }*/
    cout << ans;
    return 0;
}