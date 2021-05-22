// Start: 9:48
// Think: 10:01, 10:29-11:04
// Write: 11:33
// Debug: 11:34
#include <iostream>
using namespace std;

#define MAX_SIDE 501
int grid[MAX_SIDE][MAX_SIDE];
bool vis[MAX_SIDE][MAX_SIDE];
#define MAX_RANGE 1'000'100
int sideLen, maxFill;

bool canGo(int px, int py, int cx, int cy, int height)
{
    return abs(grid[px][py] - grid[cx][cy]) <= height;
}
int floodfill(int x, int y, int height)
{
    //current node
    if (vis[x][y])
        return 0;
    vis[x][y] = true;
    int count = 1;

    //neighbor nodes
    if (x > 0 && canGo(x, y, x - 1, y, height))
        count += floodfill(x - 1, y, height);
    if (x < sideLen - 1 && canGo(x, y, x + 1, y, height))
        count += floodfill(x + 1, y, height);
    if (y > 0 && canGo(x, y, x, y - 1, height))
        count += floodfill(x, y - 1, height);
    if (y < sideLen - 1 && canGo(x, y, x, y + 1, height))
        count += floodfill(x, y + 1, height);

    return count;
}
bool works(int height)
{
    for (int i = 0; i < sideLen; i++)
        for (int j = 0; j < sideLen; j++)
            vis[i][j] = false;
    for (int i = 0; i < sideLen; i++)
        for (int j = 0; j < sideLen; j++)
            if (floodfill(i, j, height) >= maxFill)
                return true;
    return false;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);
#endif
    cin >> sideLen;
    for (int i = 0; i < sideLen; i++)
        for (int j = 0; j < sideLen; j++)
            cin >> grid[i][j];

    //compute with bsearch
    maxFill = ((double)(sideLen * sideLen) / 2.0) + 0.5;
    int low = -1, high = MAX_RANGE;
    while (high - low > 1)
        (works((high + low) / 2) ? high : low) = (high + low) / 2;

    //print
    cout << high << endl;
    return 0;
}