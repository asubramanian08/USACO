// 7:24 - 8:17
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

using pii = pair<int, int>;
int n, m, x, y, c, f, dist[1010];
vector<pair<int, pii>> graph[1010];

int dijkstra(int minFlow)
{
    priority_queue<pii> pq;
    pq.push({0, 0});
    for (int i = 0; i < n; i++)
        dist[i] = 1'000'000'000;
    while (!pq.empty())
    {
        int node = pq.top().second;
        int cost = pq.top().first;
        pq.pop();
        dist[node] = cost;
        for (pair<int, pii> next : graph[node])
            if (next.second.second >= minFlow && dist[next.first] > dist[node] + next.second.first)
            {
                dist[next.first] = dist[node] + next.second.first;
                pq.push({dist[node] + next.second.first, next.first});
            }
    }
    return dist[n - 1];
}

int main(void)
{
    // IO Set up
    ios_base::sync_with_stdio(false);
#ifndef HOME
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);
#endif

    // read
    cin >> n >> m;
    vector<int> flows;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> c >> f;
        x--, y--;
        graph[x].push_back({y, {c, f}});
        graph[y].push_back({x, {c, f}});
        flows.push_back(f);
    }
    sort(flows.begin(), flows.end());
    flows.resize(unique(flows.begin(), flows.end()) - flows.begin());

    // calculate
    double ans = 0;
    for (int x : flows)
        ans = max(ans, (double)x / dijkstra(x));

    // print
    cout << (int)(ans * 1e6) << endl;
    return 0;
}