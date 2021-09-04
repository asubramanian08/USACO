// Start: 10:03
// Think: 10:10
// Write: 10:40
// Debug: 10:06
#include <iostream>
using namespace std;

#define MAX_COWS 1010
long long DP[MAX_COWS][MAX_COWS][2];
using pii = pair<long long, long long>;
#define BIG_NUM 100000000000

long long squareDist(pii p1, pii p2)
{
    return (p1.first - p2.first) * (p1.first - p2.first) +
           (p1.second - p2.second) * (p1.second - p2.second);
}

int main(void)
{
    //read
#ifndef HOME
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
#endif
    int numHol, numGue;
    cin >> numHol >> numGue;
    pii *hols = new pii[numHol];
    for (int i = 0; i < numHol; i++)
        cin >> hols[i].first >> hols[i].second;
    pii *gues = new pii[numGue];
    for (int i = 0; i < numGue; i++)
        cin >> gues[i].first >> gues[i].second;

    //set up (ends at H)
    for (int i = 0; i <= numGue; i++)
        DP[numHol][i][0] = BIG_NUM;
    for (int i = 0; i < numHol; i++)
        DP[i][numGue + 1][1] = BIG_NUM;
    DP[numHol][numGue][0] = 0;

    //run the DP
    for (int i = numHol - 1; i >= 0; i--)
        for (int j = numGue; j >= 0; j--)
            for (int from = 0; from <= 1; from++)
            {
                if ((j == 0 && from == 1) || (i == 0 && from == 0))
                {
                    DP[i][j][from] = BIG_NUM;
                    continue;
                }
                pii pos = from == 0 ? hols[i - 1] : gues[j - 1];
                DP[i][j][from] = min(squareDist(pos, hols[i]) + DP[i + 1][j][0],
                                     squareDist(pos, gues[j]) + DP[i][j + 1][1]);
            }

    //print and delete
    cout << DP[1][0][0] << endl;
    delete[] hols;
    delete[] gues;
    return 0;
}