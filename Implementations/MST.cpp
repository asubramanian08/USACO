/**a tree that covers all the nodes with min weight
 * Sol 1: N^2 adjecency: -> quick to implement (q1 will help, below)
 * Sol 2: N lg E Prim: priority queue or surroundings (below)
 * Sol 3: E lg V kruskal: sort all edges, if not connected (DSU) add edge to MST
 * Sol 4: Boruvka (in lecture, not discussed)
 * Look at Starleague part 1 lesson 6 dedicated to MST for help */
#include <queue>
#include <algorithm>
using namespace std;
int numFarms;
vector<pii> *conns;

#define NA -1
using pii = pair<int, int>;
int main(void)
{
    //set up
    int *costTo = new int[numFarms];
    fill(costTo, costTo + numFarms, NA);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 0}); //0 is the source

    //run though
    int node, wt;
    while (!pq.empty())
    {
        node = pq.top().second;
        wt = pq.top().first;
        pq.pop();
        if (costTo[node] != NA)
            continue;
        costTo[node] = wt;
        for (pii next : conns[node])
            if (costTo[next.second] == NA)
                pq.push({next.first, next.second});
    }
}

#define BIG_NUM 1'000'000'000
#include <utility>
int **adjMatrix;

void n2_MST(void)
{
    int *costTo = new int[numFarms];
    fill(costTo, costTo + numFarms, BIG_NUM);
    costTo[0] = 0;
    bool *vis = new bool[numFarms];
    fill(vis, vis + numFarms, false);
    int node;
    for (int run = 0; run < numFarms; run++)
    {
        node = NA;
        for (int i = 0; i < numFarms; i++)
            if (!vis[i] && (node == NA || costTo[i] < costTo[node]))
                node = i;
        vis[node] = true;
        for (int i = 0; i < numFarms; i++)
            if (!vis[i])
                costTo[i] = min(costTo[i], adjMatrix[node][i]);
    }
}