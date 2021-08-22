// Start: 8:38
// Think: 9:11, 10:30-10:39
// Write: 11:06
// Debug: 11:46
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using pii = pair<int, int>;
int numCows, conditions;
vector<pii> *graph;
bool *vis, *on;
bool cycle(int nd, int order)
{
    if (on[nd])
        return true;
    if (vis[nd] == false)
    {
        vis[nd] = on[nd] = true;
        for (pii next : graph[nd])
            if (next.second <= order && cycle(next.first, order))
                return true;
    }
    on[nd] = false;
    return false;
}
bool hasCycles(int order)
{
    for (int i = 0; i < numCows; i++)
        vis[i] = on[i] = false;
    for (int i = 0; i < numCows; i++)
        if (vis[i] == false && cycle(i, order))
            return true;
    return false;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);
#endif
    cin >> numCows >> conditions;
    graph = new vector<pii>[numCows];
    int orderSize, c1, c2;
    for (int i = 0; i < conditions; i++)
    {
        cin >> orderSize >> c1;
        for (int j = 1; j < orderSize; j++)
        {
            cin >> c2;
            graph[c1 - 1].push_back({c2 - 1, i});
            c1 = c2;
        }
    }

    //binary search graph
    int lo = 0, hi = conditions;
    vis = new bool[numCows];
    on = new bool[numCows];
    while (hi - lo > 1)
        if (hasCycles((hi + lo) / 2))
            hi = (hi + lo) / 2;
        else
            lo = (hi + lo) / 2;

    //determine ordering
    int *in_deg = new int[numCows];
    for (int i = 0; i < numCows; i++)
        in_deg[i] = 0;
    for (int i = 0; i < numCows; i++)
        for (pii next : graph[i])
            if (next.second <= lo)
                in_deg[next.first]++;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < numCows; i++)
        if (in_deg[i] == 0)
            pq.push(i);
    vector<int> ordering;
    int nd;
    while (!pq.empty())
    {
        int nd = pq.top();
        pq.pop();
        for (pii next : graph[nd])
            if (next.second <= lo && --in_deg[next.first] == 0)
                pq.push(next.first);
        ordering.push_back(nd);
    }

    //print and delete
    for (int val : ordering)
        cout << (val + 1) << (val != ordering.back() ? " " : "");
    cout << endl;
    delete[] graph;
    delete[] vis;
    delete[] in_deg;
    return 0;
}