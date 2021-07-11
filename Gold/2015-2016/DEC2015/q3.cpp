// Start: 10:58
// Think: 10:16?
// Write: 12:13
// Debug: 12:27
#include <iostream>
#include <queue>
using namespace std;

#define MAX_SIDE 1000
bool vis[MAX_SIDE][MAX_SIDE][2][4] = {0};
int grid[MAX_SIDE][MAX_SIDE];
struct pos
{
    int x, y;
    int cost;
    bool is_orange;
    int dir;
    pos(int x, int y, int cost, bool is_o, int dir)
        : x(x), y(y), cost(cost), is_orange(is_o), dir(dir) {}
};

queue<pos> q;
int numRows, numCols;
bool cantVis(pos node) { return !(node.x >= 0 && node.x < numRows && node.y >= 0 && node.y < numCols) ||
                                grid[node.x][node.y] == 0 || (grid[node.x][node.y] == 3 && !node.is_orange); }
bool make_vis(pos node)
{
    if (cantVis(node))
        return true;
    bool ret = vis[node.x][node.y][node.is_orange][node.dir];
    vis[node.x][node.y][node.is_orange][node.dir] = true;
    return ret;
}
pos findNext(pos node, int dir, bool curr_o)
{
    switch (dir)
    {
    case 0:
        return pos(node.x - 1, node.y, node.cost + 1, curr_o, 0);
    case 1:
        return pos(node.x, node.y + 1, node.cost + 1, curr_o, 1);
    case 2:
        return pos(node.x + 1, node.y, node.cost + 1, curr_o, 2);
    default: //case 3
        return pos(node.x, node.y - 1, node.cost + 1, curr_o, 3);
    }
}

int main(void)
{
    //read
#ifndef HOME
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);
#endif
    cin >> numRows >> numCols;
    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < numCols; j++)
            cin >> grid[i][j];

    //BFS the grid
    q.push(pos(0, 0, 0, false, 1));
    q.push(pos(0, 0, 0, false, 2));
    int ans = -1;
    while (!q.empty())
    {
        //this node
        pos node = q.front();
        q.pop();
        if (cantVis(node))
            continue;
        if (node.x == numRows - 1 && node.y == numCols - 1)
        {
            ans = node.cost;
            break;
        }

        //other nodes
        bool curr_o = node.is_orange || grid[node.x][node.y] == 2;
        switch (grid[node.x][node.y])
        {
        case 4:
            if (!make_vis(findNext(node, node.dir, curr_o)))
            {
                q.push(findNext(node, node.dir, curr_o));
                break;
            }
        default:
            if (!make_vis(findNext(node, 0, curr_o)))
                q.push(findNext(node, 0, curr_o));
            if (!make_vis(findNext(node, 1, curr_o)))
                q.push(findNext(node, 1, curr_o));
            if (!make_vis(findNext(node, 2, curr_o)))
                q.push(findNext(node, 2, curr_o));
            if (!make_vis(findNext(node, 3, curr_o)))
                q.push(findNext(node, 3, curr_o));
        }
    }

    //print
    cout << ans << endl;
    return 0;
}