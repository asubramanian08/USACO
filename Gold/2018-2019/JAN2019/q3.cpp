// Start: 6:30
// Think: 6:39
// Write: 7:06
// Debug: 7:20
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

using pii = pair<int, int>;
#define BIG_NUM 1000000000

int main(void)
{
    // read
#ifndef HOME
    freopen("shortcut.in", "r", stdin);
    freopen("shortcut.out", "w", stdout);
#endif
    int fields, trails, shortTime;
    cin >> fields >> trails >> shortTime;
    int *numCows = new int[fields];
    for (int i = 0; i < fields; i++)
        cin >> numCows[i];
    vector<pii> *graph = new vector<pii>[fields];
    for (int i = 0; i < trails; i++)
    {
        int n1, n2, time;
        cin >> n1 >> n2 >> time;
        n1--, n2--;
        graph[n1].push_back(pii(time, n2));
        graph[n2].push_back(pii(time, n1));
    }

    // dijkstras
    int *parent = new int[fields];
    int *time = new int[fields];
    fill(time, time + fields, BIG_NUM);
    priority_queue<pair<pii, int>, vector<pair<pii, int>>, greater<pair<pii, int>>> pq;
    pq.push(pair(pii(0, -1), 0));
    while (!pq.empty())
    {
        pii curr = pq.top().first;
        int to = pq.top().second;
        pq.pop();
        if (time[to] != BIG_NUM)
            continue;
        parent[to] = curr.second;
        time[to] = curr.first;
        for (pii next : graph[to])
            pq.push(pair(pii(next.first + time[to], to), next.second));
    }

    // nodes that pass through
    int *children = new int[fields];
    fill(children, children + fields, 0);
    for (int i = 1; i < fields; i++)
        children[parent[i]]++;
    queue<int> q;
    for (int i = 0; i < fields; i++)
        if (children[i] == 0)
            q.push(i);
    while (q.front() != 0)
    {
        numCows[parent[q.front()]] += numCows[q.front()];
        if (--children[parent[q.front()]] == 0)
            q.push(parent[q.front()]);
        q.pop();
    }

    // pick shortcut
    long long maxSaved = 0;
    for (int i = 0; i < fields; i++)
        maxSaved = max(maxSaved, (time[i] - shortTime) * (long long)numCows[i]);

    // print and delete
    cout << maxSaved << endl;
    delete[] numCows;
    delete[] graph;
    delete[] parent;
    delete[] time;
    delete[] children;
    return 0;
}