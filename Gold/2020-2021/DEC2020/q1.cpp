// Start: 5:34
// Think: 5:57,
// Write:
// Debug:
// After looking at sol: 6:26-7:50
#include <iostream>
#include <queue>
using namespace std;

int sideLen, interval;
#define MAX_SIDE 1010
using pii = pair<int, int>;
struct group
{
    int x, y, time;
    group(int x, int y, int time) : x(x), y(y), time(time) {}
};
#define NA -1
int dirX[] = {0, 1, 0, -1};
int dirY[] = {-1, 0, 1, 0};
#define DIRS 4
bool checkPos(pii pos)
{
    return pos.first >= 0 && pos.first < sideLen &&
           pos.second >= 0 && pos.second < sideLen;
}

int main(void)
{
    //read
    cin >> sideLen >> interval;
    int rockDist[MAX_SIDE][MAX_SIDE];
    queue<pii> rockQ;
    queue<group> bots;
    char ch;
    for (int i = 0; i < sideLen; i++)
        for (int j = 0; j < sideLen; j++)
        {
            cin >> ch;
            rockDist[i][j] = ch == '#' ? 0 : NA;
            if (rockDist[i][j] == 0)
                rockQ.push({i, j});
            if (ch == 'S')
                bots.push(group(i, j, 0));
        }

    //find the rock dist
    pii prev, curr;
    while (!rockQ.empty())
    {
        prev = rockQ.front();
        rockQ.pop();
        for (int i = 0; i < DIRS; i++)
            if (checkPos(curr = {prev.first + dirX[i], prev.second + dirY[i]}) &&
                rockDist[curr.first][curr.second] == NA)
            {
                rockDist[curr.first][curr.second] = rockDist[prev.first][prev.second] + 1;
                rockQ.push(curr);
            }
    }

    //find where the center can go
    int width[MAX_SIDE][MAX_SIDE];
    for (int i = 0; i < sideLen; i++)
        for (int j = 0; j < sideLen; j++)
            width[i][j] = NA;
    queue<pii> center[MAX_SIDE];
    while (!bots.empty())
    {
        group g = bots.front();
        bots.pop();
        if (width[g.x][g.y] != NA)
            continue;
        width[g.x][g.y] = rockDist[g.x][g.y];
        center[width[g.x][g.y]].push({g.x, g.y});
        if (rockDist[g.x][g.y] < g.time / interval + 1)
            continue;
        for (int i = 0; i < DIRS; i++)
            if (checkPos(curr = {g.x + dirX[i], g.y + dirY[i]}) &&
                width[curr.first][curr.second] == NA)
                bots.push(group(curr.first, curr.second, g.time + 1));
    }

    //expand center
    int ans = 0;
    for (int i = sideLen - 1; i > 0; i--)
        while (!center[i].empty())
        {
            prev = center[i].front();
            center[i].pop();
            if (width[prev.first][prev.second] != i)
                continue;
            ans++;
            for (int j = 0; j < DIRS; j++)
                if (checkPos(curr = {prev.first + dirX[j], prev.second + dirY[j]}) &&
                    width[curr.first][curr.second] < width[prev.first][prev.second] - 1)
                {
                    width[curr.first][curr.second] = width[prev.first][prev.second] - 1;
                    center[width[curr.first][curr.second]].push(curr);
                }
        }

    //print
    cout << ans << endl;
    return 0;
}