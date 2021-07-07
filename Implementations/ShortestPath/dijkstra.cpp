//Look at Starleague part 1 lesson 7, about BFS and dijkstra
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

#define BIG_NUM 1000000000
using pii = pair<int, int>;
int numNodes;
vector<pii> *graph; //wt, nd
bool *vis;
int *cost;
void dijkstra(int source)
{
    fill(vis, vis + numNodes, false);
    fill(cost, cost + numNodes, BIG_NUM);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, source});
    int node, wt;
    while (!pq.empty())
    {
        node = pq.top().second;
        wt = pq.top().first;
        pq.pop();
        if (vis[node])
            continue;
        vis[node] = true;
        cost[node] = wt;
        for (const pii &next : graph[node])
            if (!vis[next.second] && cost[next.second] > wt + next.first)
            {
                cost[next.second] = wt + next.first;
                pq.push({wt + next.first, next.second});
            }
    }
}