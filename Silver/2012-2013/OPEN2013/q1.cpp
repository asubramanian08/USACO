// Start: 2:15
// Think: 2:28
// Write: 3:10
// Debug: 3:34
#include <iostream>
#include <deque>
using namespace std;

#define MAX_SIDE 500
#define BIG_NUM 1'000'000'000
struct point
{
    int x, y;
    bool gav;
    point(int x, int y, bool gav) : x(x), y(y), gav(gav) {}
    point() = default;
};

int cost[MAX_SIDE][MAX_SIDE][2] = {0};
bool block[MAX_SIDE][MAX_SIDE];
int height, width;
deque<point> travel;

inline int next(int x, bool gav) { return x + (gav ? -1 : 1); }
void add(const point &pt, const point &par, bool add)
{
    if ((pt.y < 0 || pt.y >= width) ||
        (block[pt.x][pt.y]) ||
        (cost[pt.x][pt.y][pt.gav] != BIG_NUM))
        return;
    cost[pt.x][pt.y][pt.gav] = cost[par.x][par.y][par.gav] + add;
    add ? travel.push_back(pt) : travel.push_front(pt);
}

int main(void)
{
    //read
#ifndef HOME
    freopen("gravity.in", "r", stdin);
    freopen("gravity.out", "w", stdout);
#endif
    cin >> height >> width;
    char ch;
    point start;
    int endX, endY;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            cin >> ch;
            block[i][j] = ch == '#';
            if (ch == 'C')
                start = point(i, j, false);
            if (ch == 'D')
                endX = i, endY = j;
            cost[i][j][false] = cost[i][j][true] = BIG_NUM;
        }

    //setup
    cost[start.x][start.y][start.gav] = 0;
    travel.push_front(start);
    while (!travel.empty())
    {
        point pos = travel.front();
        travel.pop_front();
        int nxt = next(pos.x, pos.gav);
        if (nxt < 0 || nxt >= height)
            continue;
        if (!block[nxt][pos.y])
        {
            add(point(nxt, pos.y, pos.gav), pos, false);
            continue;
        }
        add(point(pos.x, pos.y - 1, pos.gav), pos, false);
        add(point(pos.x, pos.y + 1, pos.gav), pos, false);
        add(point(pos.x, pos.y, !pos.gav), pos, true);
    }
    int ans = min(cost[endX][endY][false], cost[endX][endY][true]);
    cout << (ans == BIG_NUM ? -1 : ans) << endl;
    return 0;
}