// Start: 3:59
// Think: 4:18
// Write: 4:44
// Debug: 5:00 not right (only test case)

// I tried used only add and sub then tried to use change if better
// Edit distance
// After looking at sol: 6:26-6:47
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 10000000

int main(void)
{
    //read
#ifndef HOME
    freopen("landscape.in", "r", stdin);
    freopen("landscape.out", "w", stdout);
#endif
    int numBeds, add, sub, trans;
    cin >> numBeds >> add >> sub >> trans;
    vector<int> start;
    vector<int> goal;
    int length;
    for (int i = 0; i < numBeds; i++)
    {
        cin >> length;
        start.resize(start.size() + length);
        fill(start.end() - length, start.end(), i);
        cin >> length;
        goal.resize(goal.size() + length);
        fill(goal.end() - length, goal.end(), i);
    }

    //make the 2D array
    int **editDist = new int *[start.size() + 1];
    for (int i = 0; i <= start.size(); i++)
    {
        editDist[i] = new int[goal.size() + 1];
        fill(editDist[i], editDist[i] + goal.size() + 1, INF);
    }

    //do the edit distance
    for (int i = 0; i <= start.size(); i++)
        editDist[i][0] = i * sub;
    for (int i = 0; i <= goal.size(); i++)
        editDist[0][i] = i * add;
    for (int i = 1; i <= start.size(); i++)
        for (int j = 1; j <= goal.size(); j++)
        {
            editDist[i][j] = min(editDist[i][j], editDist[i - 1][j] + sub);
            editDist[i][j] = min(editDist[i][j], editDist[i][j - 1] + add);
            editDist[i][j] = min(editDist[i][j], editDist[i - 1][j - 1] + trans * abs(start[i - 1] - goal[j - 1]));
        }

    //print and delete
    cout << editDist[start.size()][goal.size()];
    for (int i = 0; i <= start.size(); i++)
        delete[] editDist[i];
    delete[] editDist;
    return 0;
}