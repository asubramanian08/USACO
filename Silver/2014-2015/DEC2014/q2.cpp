// Start: 9:38
// Think: 9:50
// Write: 10:07
// Debug: 10:14
#include <iostream>
using namespace std;

using pii = pair<int, int>;
#define MAX_POINTS 500
#define BIG_NUM 1000000000
int mDist(pii p1, pii p2) { return abs(p1.first - p2.first) + abs(p1.second - p2.second); }

int main(void)
{
    // read
#ifndef HOME
    freopen("marathon.in", "r", stdin);
    freopen("marathon.out", "w", stdout);
#endif
    int numChecks, maxSkip;
    cin >> numChecks >> maxSkip;
    pii *checks = new pii[numChecks];
    for (int i = 0; i < numChecks; i++)
        cin >> checks[i].first >> checks[i].second;

    // DP[i][j]: min dist from node i with j skips
    int DP[MAX_POINTS][MAX_POINTS];
    for (int i = 0; i <= maxSkip; i++)
        DP[numChecks - 1][i] = 0;
    for (int i = numChecks - 2; i >= 0; i--)
        for (int j = 0; j <= maxSkip; j++)
        {
            DP[i][j] = BIG_NUM;
            for (int k = 0; k <= j && i + k + 1 < numChecks; k++)
                DP[i][j] = min(DP[i][j], mDist(checks[i], checks[i + k + 1]) + DP[i + k + 1][j - k]);
        }

    // print and delete
    cout << DP[0][maxSkip] << endl;
    delete[] checks;
    return 0;
}