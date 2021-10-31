// Start: 9:18
// Think: 9:23
// Write: 9:37
// Debug: 9:38
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define BIG_NUM 1000000000
int *dijkstra(int start, vector<int> *graph, int numFields, int cost)
{
    int *dist = new int[numFields];
    for (int i = 0; i < numFields; i++)
        dist[i] = BIG_NUM;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push(pii(0, start));
    while (!pq.empty())
    {
        pii curr = pq.top();
        pq.pop();
        if (dist[curr.second] != BIG_NUM)
            continue;
        dist[curr.second] = curr.first;
        for (int next : graph[curr.second])
            pq.push(pii(curr.first + cost, next));
    }
    return dist;
}

int main(void)
{
    // read
#ifndef HOME
    freopen("piggyback.in", "r", stdin);
    freopen("piggyback.out", "w", stdout);
#endif
    int bCost, eCost, pCost, numFields, numConns;
    cin >> bCost >> eCost >> pCost >> numFields >> numConns;
    vector<int> *graph = new vector<int>[numFields];
    for (int i = 0; i < numConns; i++)
    {
        int n1, n2;
        cin >> n1 >> n2;
        n1--, n2--;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    // distences: 1 (B), 2 (E), N (P)
    int *bDist = dijkstra(0, graph, numFields, bCost);
    int *eDist = dijkstra(1, graph, numFields, eCost);
    int *pDist = dijkstra(numFields - 1, graph, numFields, pCost);

    // minCost
    int minCost = BIG_NUM;
    for (int i = 0; i < numFields; i++)
        minCost = min(minCost, bDist[i] + eDist[i] + pDist[i]);

    // print and delete
    cout << minCost << endl;
    delete[] graph;
    delete[] bDist;
    delete[] eDist;
    delete[] pDist;
    return 0;
}