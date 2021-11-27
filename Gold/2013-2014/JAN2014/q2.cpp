// Start: 9:37
// Think: 9:58, 11:31
// Write:
// Debug:
// After looking at sol: Didn't time
#include <iostream>
using namespace std;
#define MAX_SIDE 101

int main(void)
{
    // read
#ifndef HOME
    freopen("skicourse.in", "r", stdin);
    freopen("skicourse.out", "w", stdout);
#endif
    int rows, cols;
    cin >> rows >> cols;
    bool rough[MAX_SIDE][MAX_SIDE];
    bool soft[MAX_SIDE][MAX_SIDE];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            char type;
            cin >> type;
            rough[i][j] = type == 'R';
            soft[i][j] = type == 'S';
        }

    // DP[i][j]: largest stamp at (i,j)
    int ans = MAX_SIDE; // large number
    while (true)
    {
        int best = -1, bestR, bestC;
        int rough_DP[MAX_SIDE][MAX_SIDE] = {0};
        int soft_DP[MAX_SIDE][MAX_SIDE] = {0};
        for (int r = rows - 1; r >= 0; r--)
            for (int c = cols - 1; c >= 0; c--)
            {
                rough_DP[r][c] = rough[r][c] ? min(min(rough_DP[r + 1][c], rough_DP[r][c + 1]), rough_DP[r + 1][c + 1]) + 1 : 0;
                soft_DP[r][c] = soft[r][c] ? min(min(soft_DP[r + 1][c], soft_DP[r][c + 1]), soft_DP[r + 1][c + 1]) + 1 : 0;
                if (rough_DP[r][c] != soft_DP[r][c] && max(rough_DP[r][c], soft_DP[r][c]) > best)
                    best = max(rough_DP[r][c], soft_DP[r][c]), bestR = r, bestC = c;
            }
        if (best == -1)
            break;
        ans = min(ans, best);
        for (int i = 0; i < best; i++)
            for (int j = 0; j < best; j++)
                rough[i + bestR][j + bestC] = soft[i + bestR][j + bestC] = true;
    }

    // print
    cout << ans << endl;
    return 0;
}