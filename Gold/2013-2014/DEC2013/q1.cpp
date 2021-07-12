// Start: 9:35
// Think: 10:00, 11:37-11:46
// Write: 12:04
// Debug: 12:12
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

using pii = pair<int, int>;
#define BIG_NUM 1000000000
bool *vis;
int numNodes;
void dijkstra(int source, vector<pii> *graph, int *cost)
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

int main(void)
{
    //read
#ifndef HOME
    freopen("vacationgold.in", "r", stdin);
    freopen("vacationgold.out", "w", stdout);
#endif
    int numConns, numHubs, numQueries;
    cin >> numNodes >> numConns >> numHubs >> numQueries;
    vector<pii> *graph = new vector<pii>[numNodes];
    vector<pii> *rGraph = new vector<pii>[numNodes];
    int n1, n2, wt;
    for (int i = 0; i < numConns; i++)
    {
        cin >> n1 >> n2 >> wt;
        n1--, n2--;
        graph[n1].push_back({wt, n2});
        rGraph[n2].push_back({wt, n1});
    }
    int *hubs = new int[numHubs];
    for (int i = 0; i < numHubs; i++)
    {
        cin >> hubs[i];
        hubs[i]--;
    }
    pii *queries = new pii[numQueries];
    for (int i = 0; i < numQueries; i++)
    {
        cin >> queries[i].first >> queries[i].second;
        queries[i].first--, queries[i].second--;
    }

    //do dijkstra on hubs
    vis = new bool[numNodes];
    int *to = new int[numNodes];
    int *from = new int[numNodes];
    int *dist = new int[numQueries];
    fill(dist, dist + numQueries, BIG_NUM);
    for (int i = 0; i < numHubs; i++)
    {
        dijkstra(hubs[i], graph, to);
        dijkstra(hubs[i], rGraph, from);
        for (int j = 0; j < numQueries; j++)
            dist[j] = min(dist[j], from[queries[j].first] + to[queries[j].second]);
    }

    //print and delete
    int numTraveled = numQueries;
    long long ans = 0;
    for (int i = 0; i < numQueries; i++)
        if (dist[i] == BIG_NUM)
            numTraveled--;
        else
            ans += dist[i];
    cout << numTraveled << endl
         << ans << endl;
    return 0;
}