// Start: 8:43
// Think: 8:57
// Write: ?
// Debug: 9:58
#include <iostream>
#include <queue>
using namespace std;

#define MAX_SIDE 30
bool feild[MAX_SIDE][MAX_SIDE];
bool vis[MAX_SIDE][MAX_SIDE];
int sideLen, samePast, diffPast;

typedef pair<int, int> point;
typedef pair<int, point> node;
priority_queue<node, vector<node>, greater<node>> pq;
void addNode(point pt, int dist, point parent)
{
    if (pt.first < 0 || pt.first >= sideLen ||
        pt.second < 0 || pt.second >= sideLen)
        return;
    if (feild[parent.first][parent.second] == feild[pt.first][pt.second])
        pq.push({dist + samePast, pt});
    else
        pq.push({dist + diffPast, pt});
}
int dijkstra(point src)
{
    for (int i = 0; i < sideLen; i++)
        for (int j = 0; j < sideLen; j++)
            vis[i][j] = false;
    int maxDist = 0, dist;
    point pt;
    pq.push({0, src});
    while (!pq.empty())
    {
        //this node
        dist = pq.top().first;
        pt = pq.top().second;
        pq.pop();
        if (vis[pt.first][pt.second])
            continue;
        vis[pt.first][pt.second] = true;
        maxDist = max(maxDist, dist);
        //next nodes
        addNode({pt.first + 1, pt.second}, dist, pt);
        addNode({pt.first - 1, pt.second}, dist, pt);
        addNode({pt.first, pt.second + 1}, dist, pt);
        addNode({pt.first, pt.second - 1}, dist, pt);
    }
    return maxDist;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("distant.in", "r", stdin);
    freopen("distant.out", "w", stdout);
#endif
    cin >> sideLen >> samePast >> diffPast;
    char ch;
    for (int i = 0; i < sideLen; i++)
        for (int j = 0; j < sideLen; j++)
        {
            cin >> ch;
            feild[i][j] = ch == ')';
        }

    //calculate
    int maxDist = 0;
    for (int i = 0; i < sideLen; i++)
        for (int j = 0; j < sideLen; j++)
            maxDist = max(maxDist, dijkstra({i, j}));

    //print
    cout << maxDist;
    return 0;
}