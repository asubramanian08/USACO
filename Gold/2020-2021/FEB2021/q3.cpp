// Start: 9:33
// Think: 10:10,
// Write:
// Debug:
// After looking at sol: 4:00-4:13
#include <iostream>
using namespace std;

#define MAX_POW 40

int main(void)
{
    // setup
    long long *power3 = new long long[MAX_POW];
    power3[0] = 1;
    for (int i = 1; i < MAX_POW; ++i)
        power3[i] = 3 * power3[i - 1];
    long long DP[3][2][2], next[3][2][2];
    int queries;
    cin >> queries;
    auto reset = [](long long(&dp)[3][2][2])
    {
        for (int it1 = 0; it1 < 3; it1++)
            for (int it2 = 0; it2 < 2; it2++)
                for (int it3 = 0; it3 < 2; it3++)
                    dp[it1][it2][it3] = 0;
    };

    // answer queries
    for (int testNum = 0; testNum < queries; testNum++)
    {
        long long dist, x, y;
        cin >> dist >> x >> y;
        reset(DP);
        DP[1][0][0] = 1;
        for (int i = 0; i < MAX_POW - 1; i++)
        {
            reset(next);
            int dd = dist / power3[i] % 3, xDist = x / power3[i] % 3, yDist = y / power3[i] % 3;
            for (int cmp = 0; cmp < 3; cmp++)
                for (int xc = 0; xc < 2; xc++)
                    for (int yc = 0; yc < 2; yc++)
                        for (int j = 0; j < 3; j++)
                        {
                            int XD = (xDist + xc + j) % 3, XC = (xDist + xc + j) / 3;
                            int YD = (yDist + yc + j) % 3, YC = (yDist + yc + j) / 3;
                            int CMP = cmp;
                            if (j > dd)
                                CMP = 2;
                            if (j < dd)
                                CMP = 0;
                            if (XD % 2 == YD % 2)
                                next[CMP][XC][YC] += DP[cmp][xc][yc];
                        }
            swap(DP, next);
        }
        cout << (DP[0][0][0] + DP[1][0][0]) << endl;
    }
    delete[] power3;
    return 0;
}