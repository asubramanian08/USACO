// Start: 10:04
// Think: 10:16
// Write: 10:55
// Debug: 10:56
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using pii = pair<int, int>;
#define mp make_pair
#define NA -1
pii *dijkstra(int source, vector<pii> *graph, int len)
{
    pii *parent = new pii[len];
    for (int i = 0; i < len; i++)
        parent[i].second = NA;
    priority_queue<pair<pii, int>, vector<pair<pii, int>>, greater<pair<pii, int>>> pq;
    pq.push(mp(mp(0, source), source));
    while (!pq.empty())
    {
        pii node = pq.top().first;
        int par = pq.top().second;
        pq.pop();
        if (parent[node.second].second != NA)
            continue;
        parent[node.second] = mp(node.first, par);
        for (pii next : graph[node.second])
            pq.push(mp(mp(node.first + next.first, next.second), node.second));
    }
    return parent;
}

int main(void)
{
    // read
#ifndef HOME
    freopen("gpsduel.in", "r", stdin);
    freopen("gpsduel.out", "w", stdout);
#endif
    int numNodes, numEdges;
    cin >> numNodes >> numEdges;
    // NOTE the graphs are reversed
    vector<pii> *graph1 = new vector<pii>[numNodes];
    vector<pii> *graph2 = new vector<pii>[numNodes];
    for (int i = 0; i < numEdges; i++)
    {
        int from, to, wt1, wt2;
        cin >> from >> to >> wt1 >> wt2;
        from--, to--;
        graph1[to].push_back(mp(wt1, from));
        graph2[to].push_back(mp(wt2, from));
    }

    // complain graph
    pii *parent1 = dijkstra(numNodes - 1, graph1, numNodes);
    pii *parent2 = dijkstra(numNodes - 1, graph2, numNodes);
    vector<pii> *complainGraph = new vector<pii>[numNodes];
    for (int i = 0; i < numNodes; i++)
        for (int j = 0; j < graph1[i].size(); j++)
        {
            int complains = 0;
            if (i != parent1[graph1[i][j].second].second)
                complains++;
            if (i != parent2[graph2[i][j].second].second)
                complains++;
            complainGraph[i].push_back(mp(complains, graph1[i][j].second));
        }

    // ans: min complains
    pii *complainParent = dijkstra(numNodes - 1, complainGraph, numNodes);
    int ans = complainParent[0].first;

    // print and delete
    cout << ans << endl;
    delete[] graph1;
    delete[] graph2;
    delete[] parent1;
    delete[] parent2;
    delete[] complainGraph;
    delete[] complainParent;
    return 0;
}