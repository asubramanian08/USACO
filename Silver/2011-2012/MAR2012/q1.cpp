// Start: 3:15
// Think: 3:24, 5:03-5:31
// Write: (forgot) not much debug time
// Debug: 7:12
//could have done 1-0 BFS
#include <iostream>
#include <queue>
using namespace std;

#define gridSide 1001
typedef pair<int, int> point;
#define x first
#define y second
typedef pair<point, int> edge;

int numBayles, cost, remMin;
bool vis[gridSide][gridSide] = {false};
int is_bale[gridSide][gridSide] = {0};

bool out_range(point pt)
{
    return (pt.x < 0 || pt.x > gridSide) || (pt.y < 0 || pt.y > gridSide);
}
bool check(point pt)
{
    if (out_range(pt))
        return true;
    if (vis[pt.x][pt.y])
        return true;
    vis[pt.x][pt.y] = true;
    return false;
}

bool is_start(point src)
{
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            if (!out_range(make_pair(src.x + i, src.y + j)) &&
                !is_bale[src.x + i][src.y + j] &&
                vis[src.x + i][src.y + j])
                return true;
    return false;
}
bool is_end(point src)
{
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            if (!out_range(make_pair(src.x + i, src.y + j)) &&
                !is_bale[src.x + i][src.y + j] &&
                !vis[src.x + i][src.y + j])
                return true;
    return false;
}
void addEdge(edge src, queue<edge> &q, queue<point> &BFS)
{
    if (check(src.first))
        return;
    is_bale[src.first.x][src.first.y] ? q.push(src) : BFS.push(src.first);
}
void BFSedge(queue<edge> &q, queue<point> &BFS)
{
    remMin = q.size();
    edge curr;
    while (!q.empty())
    {
        //this not
        curr = q.front();
        q.pop();
        if (is_start(curr.first))
            curr.second = 1;
        if (is_end(curr.first))
            remMin = min(remMin, curr.second);

        //other nodes
        for (int i = -1; i < 2; i++)
            for (int j = -1; j < 2; j++)
                addEdge(make_pair(make_pair(curr.first.x + i, curr.first.y + j), curr.second + 1), q, BFS);
    }
    cost += remMin;
}

void addNode(point pt, queue<point> &BFS, queue<edge> &edge)
{
    if (check(pt))
        return;
    is_bale[pt.x][pt.y] ? edge.push(make_pair(pt, 0)) : BFS.push(pt);
}

int main(void)
{
    //read
#ifndef HOME
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);
#endif
    point tracktor;
    cin >> numBayles >> tracktor.x >> tracktor.y;
    int one, two;
    for (int i = 0; i < numBayles; i++)
    {
        cin >> one >> two;
        is_bale[one][two] = 1;
    }

    //flood fill (BFS)
    queue<point> BFS;
    queue<edge> edge;
    point curr;
    cost = 0;
    BFS.push(tracktor);
    while (!BFS.empty() || !edge.empty())
    {
        //this node
        if (BFS.empty())
            BFSedge(edge, BFS);
        curr = BFS.front();
        if (curr.x == 0 || curr.y == 0)
        {
            cout << cost;
            return 0;
        }
        BFS.pop();

        //other nodes
        addNode(make_pair(curr.x - 1, curr.y), BFS, edge);
        addNode(make_pair(curr.x + 1, curr.y), BFS, edge);
        addNode(make_pair(curr.x, curr.y - 1), BFS, edge);
        addNode(make_pair(curr.x, curr.y + 1), BFS, edge);
    }

    //print and delete
    cout << cost;
    return 0;
}