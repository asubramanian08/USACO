// 9:32 - 10:03 + DEBUGGING
#include <iostream>
using namespace std;
#define MOD 1000000007
#define N 505

int main(void)
{
// read
#ifndef HOME
    freopen("palpath.in", "r", stdin);
    freopen("palpath.out", "w", stdout);
#endif
    int n;
    char grid[N][N];
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    // DP
    long long DP[2 /*N*/][N][N] = {1}, next = 1;
    for (int dist = 1; dist < n; dist++)
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                DP[next][i][j] = 0;
        for (int x1 = 0; x1 <= dist; x1++)
            for (int x2 = 0; x2 <= dist; x2++)
            {
                int y1 = dist - x1 - 1, y2 = dist - x2 - 1;
                DP[!next /* next - 1 */][x1][x2] %= MOD;
                if (grid[x1][y1] == grid[n - x2 - 1][n - y2 - 1])
                {
                    DP[next][x1 + 0][x2 + 0] += DP[!next /* next - 1 */][x1][x2];
                    DP[next][x1 + 0][x2 + 1] += DP[!next /* next - 1 */][x1][x2];
                    DP[next][x1 + 1][x2 + 0] += DP[!next /* next - 1 */][x1][x2];
                    DP[next][x1 + 1][x2 + 1] += DP[!next /* next - 1 */][x1][x2];
                }
            }
        next = 1 - next; // next++;
    }

    // compute answer
    long long ans = 0;
    for (int x = 0; x < n; x++)
        ans += DP[1 - next /* n - 1 */][x][n - x - 1];
    cout << (ans % MOD) << endl;
    return 0;
}