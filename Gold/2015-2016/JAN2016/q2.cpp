// Start: 9:45
// Think: 9:50
// Write: 10:09
// Debug: 10:12
#include <iostream>
using namespace std;

using pii = pair<int, int>;
#define MAX_STEPS 1001
#define BIG_NUM 1000000000

int squareDist(pii p1, pii p2)
{
    return (p1.first - p2.first) * (p1.first - p2.first) +
           (p1.second - p2.second) * (p1.second - p2.second);
}
int main(void)
{
    // read
#ifndef HOME
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);
#endif
    int fMoves, bMoves;
    cin >> fMoves >> bMoves;
    fMoves++, bMoves++;
    pii *fPos = new pii[fMoves];
    cin >> fPos[0].first >> fPos[0].second;
    pii *bPos = new pii[bMoves];
    cin >> bPos[0].first >> bPos[0].second;
    for (int i = 1; i < fMoves; i++)
    {
        char move;
        cin >> move;
        if (move == 'N')
            fPos[i] = pii(fPos[i - 1].first + 0, fPos[i - 1].second + 1);
        else if (move == 'E')
            fPos[i] = pii(fPos[i - 1].first + 1, fPos[i - 1].second + 0);
        else if (move == 'S')
            fPos[i] = pii(fPos[i - 1].first + 0, fPos[i - 1].second - 1);
        else // move == 'W'
            fPos[i] = pii(fPos[i - 1].first - 1, fPos[i - 1].second + 0);
    }
    for (int i = 1; i < bMoves; i++)
    {
        char move;
        cin >> move;
        if (move == 'N')
            bPos[i] = pii(bPos[i - 1].first + 0, bPos[i - 1].second + 1);
        else if (move == 'E')
            bPos[i] = pii(bPos[i - 1].first + 1, bPos[i - 1].second + 0);
        else if (move == 'S')
            bPos[i] = pii(bPos[i - 1].first + 0, bPos[i - 1].second - 1);
        else // move == 'W'
            bPos[i] = pii(bPos[i - 1].first - 1, bPos[i - 1].second + 0);
    }

    // DP[i][j] = min battery at fPos[i] and bPos[j]
    int DP[MAX_STEPS][MAX_STEPS];
    for (int i = 0; i < fMoves; i++)
        for (int j = 0; j < bMoves; j++)
            DP[i][j] = BIG_NUM;
    DP[0][0] = -squareDist(fPos[0], bPos[0]);
    for (int i = 0; i < fMoves; i++)
        for (int j = 0; j < bMoves; j++)
        {
            DP[i][j] += squareDist(fPos[i], bPos[j]);
            if (i < fMoves - 1)
                DP[i + 1][j] = min(DP[i + 1][j], DP[i][j]);
            if (j < bMoves - 1)
                DP[i][j + 1] = min(DP[i][j + 1], DP[i][j]);
            if (i < fMoves - 1 && j < bMoves - 1)
                DP[i + 1][j + 1] = min(DP[i + 1][j + 1], DP[i][j]);
        }

    // print and delete
    cout << DP[fMoves - 1][bMoves - 1] << endl;
    delete[] fPos;
    delete[] bPos;
    return 0;
}