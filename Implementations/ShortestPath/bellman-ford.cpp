//node to everywhere, O(VE)
//look at starleague part 1 lesson 8
#include <algorithm>
using namespace std;
#define BIG_NUM 1000000000

struct edge
{
    int u, v, wt;
};
int main(void)
{
    int numNodes, numEdges, source;
    edge *edges;

    int *dist = new int[numNodes];
    fill(dist, dist + numNodes, BIG_NUM);
    dist[source] = 0;
    for (int run = 1; run < numNodes; run++)
        for (int i = 0; i < numEdges; i++)
            dist[edges[i].v] = min(dist[edges[i].v], dist[edges[i].u] + edges[i].wt);
    for (int i = 0; i < numEdges; i++) //pos cycle check
        if (dist[edges[i].v] > dist[edges[i].u] + edges[i].wt)
            return 0; //NEGATIVE CYCLE
}