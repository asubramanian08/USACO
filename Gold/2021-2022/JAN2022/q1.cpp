#include <iostream>
using namespace std;

#define MAX_COWS 15
#define MAX_HEIGHT 105
#define MOD 1000000007

int main(void)
{
    // read
    int numCows;
    cin >> numCows;
    int *height = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> height[i];

    // run DP[c][h_c][h_c-1]
    long long DP[MAX_COWS][MAX_HEIGHT][MAX_HEIGHT] = {0};
    for (int i = 0; i <= height[0]; i++)
        DP[1][i][i] = 1;
    for (int i = 1; i < numCows; i++)
        for (int k = 0; k <= height[i - 1]; k++)
        {
            DP[i][0][k] = DP[i][0][k] % MOD;
            for (int j = 1; j <= height[i]; j++)
                DP[i][j][k] = (DP[i][j][k] + DP[i][j - 1][k]) % MOD;
            if (i % 2)
                for (int j = 0; j <= height[i]; j++)
                    DP[i + 1][max(j - k, 0)][j] += DP[i][j][k];
            else
                for (int j = 0; j <= height[i]; j++)
                    DP[i + 1][max(max(j - k, 0), j)][j] += DP[i][j][k];
        }

    long long ans = 0;
    for (int i = 0; i <= height[numCows - 1]; i++)
        ans = (ans + DP[numCows][0][i]) % MOD;
    cout << ans << endl;
    return 0;
}