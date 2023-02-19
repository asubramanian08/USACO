// 10:14 - 11:44
#include <iostream>
using namespace std;
#define INF 1'000'000'000
#define N 105

int main(void)
{
    ios_base::sync_with_stdio(false);
#ifndef HOME
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);
#endif
    int arr[N], n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int DP[N][N][N]; // up till, last pos, total breakouts - 1 (i >= j >= k)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                DP[i][j][k] = INF;
    DP[0][0][0] = arr[0] != 0;
    for (int i = 1; i < n; i++)
        DP[i][0][0] = DP[i - 1][0][0] + (arr[i] != i);
    for (int k = 1; k < n; k++)
        for (int i = k; i < n; i++)
        {
            for (int j = k - 1; j < i; j++) // i is the last breakout
                DP[i][i][k] = min(DP[i][i][k], DP[i - 1][j][k - 1] + (arr[i] != 0));
            for (int j = k; j < i; j++) // j is the last breakout
                DP[i][j][k] = min(DP[i][j][k], DP[i - 1][j][k] + (arr[i] != i - j));
        }
    for (int i = 0; i < n; i++)
    {
        int ans = INF;
        for (int j = i; j < n; j++)
            ans = min(ans, DP[n - 1][j][i]);
        cout << ans << endl;
    }
    return 0;
}