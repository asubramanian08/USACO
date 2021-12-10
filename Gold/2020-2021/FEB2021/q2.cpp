// Start: 9:00
// Think: 9:33, 11:37-
// Write:
// Debug:
// After looking at sol: 3:48-3:57
#include <iostream>
using namespace std;

#define MAX_SIDE 300

int main(void)
{
    // read
    int paintSize;
    cin >> paintSize;
    int *painting = new int[paintSize];
    for (int i = 0; i < paintSize; i++)
        cin >> painting[i];

    // DP[i][j]: max segments from i to j
    int DP[MAX_SIDE][MAX_SIDE] = {0};
    for (int i = paintSize - 1; i >= 0; i--)
        for (int j = i + 1; j < paintSize; j++)
        {
            if (painting[i] == painting[j]) // max segment
                DP[i][j] = DP[i + 1][j - 1] + 1;
            for (int k = i + 1; k < j; k++)
                DP[i][j] = max(DP[i][j], DP[i][k] + DP[k][j]);
        }

    // print and delete
    cout << (paintSize - DP[0][paintSize - 1]) << endl;
    delete[] painting;
    return 0;
}