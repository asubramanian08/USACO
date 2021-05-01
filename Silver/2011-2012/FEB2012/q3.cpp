// Start: 8:44
// Think: 9:17, 11:28-na
// Write: na
// Debug: na
// after looking at solution: 12:54-1:43 -> lot of code
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;

typedef pair<int, int> pii;
#define mp make_pair
int numTowns, numConns, numMarkets;
int *markets;
vector<pii> *graph;
int **dists; //first number is the market
#define NA -1
#define BIG_NUM 1'000'000'000

void dijkstra(int source)
{
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push(mp(0, markets[source]));
    pii node; //dist, point
    while (!pq.empty())
    {
        //this node
        node = pq.top();
        pq.pop();
        if (dists[source][node.second] != NA)
            continue;
        dists[source][node.second] = node.first;

        //add other nodes
        for (auto next : graph[node.second])
            if (dists[source][next.second] == NA)
                pq.push(mp(next.first + node.first, next.second));
    }
}
int findCost(const int *ordering, int town)
{
    int dist = dists[ordering[0]][town];
    for (int i = 1; i < numMarkets; i++)
        dist += dists[ordering[i]][markets[ordering[i - 1]]];
    dist += dists[ordering[numMarkets - 1]][town];
    return dist;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("relocate.in", "r", stdin);
    freopen("relocate.out", "w", stdout);
#endif
    cin >> numTowns >> numConns >> numMarkets;
    markets = new int[numMarkets];
    for (int i = 0; i < numMarkets; i++)
    {
        cin >> markets[i];
        markets[i]--;
    }
    int t1, t2, width;
    graph = new vector<pii>[numTowns];
    for (int i = 0; i < numConns; i++)
    {
        cin >> t1 >> t2 >> width;
        t1--;
        t2--;
        graph[t1].push_back(mp(width, t2));
        graph[t2].push_back(mp(width, t1));
    }

    //form the distences from the markets to all other nodes
    dists = new int *[numMarkets];
    for (int i = 0; i < numMarkets; i++)
    {
        dists[i] = new int[numTowns];
        fill(dists[i], dists[i] + numTowns, NA);
        dijkstra(i);
    }

    //set what is a market
    bool *is_mark = new bool[numTowns];
    fill(is_mark, is_mark + numTowns, false);
    for (int i = 0; i < numMarkets; i++)
        is_mark[markets[i]] = true;

    //find the minimum cost at a town
    int minCost = BIG_NUM;
    int *ordering = new int[numMarkets];
    for (int i = 0; i < numTowns; i++)
    {
        if (is_mark[i])
            continue;
        iota(ordering, ordering + numMarkets, 0);
        do
        {
            minCost = min(minCost, findCost(ordering, i));
        } while (next_permutation(ordering, ordering + numMarkets));
    }

    //point and delete
    cout << minCost;
    delete[] markets;
    delete[] graph;
    for (int i = 0; i < numMarkets; i++)
        delete[] dists[i];
    delete[] dists;
    delete[] is_mark;
    delete[] ordering;
    return 0;
}