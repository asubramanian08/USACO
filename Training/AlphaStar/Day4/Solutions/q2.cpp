/*Solution USACO 2018 December Contest, Gold (Analysis by Nathan Pinsker)

In order to know whether a given path is some amount of greater than the optimal path, we first need to 
know the optimal path! So we can begin by running Dijkstra's algorithm from barn N to find the 
minimum-length path from each pasture to the barn.

Since 𝑁≤50,000, any sort of all-pairs shortest paths approach will be too slow to pass. However, we can 
notice that the constraints of the problem suggest something peculiar: eating a haybale with yumminess 
value Y is exactly equivalent to "subtracting" Y from a cow's traveled distance. In other words, this 
problem is a normal shortest-path problem, where some edges are negative -- but we must also modify the 
graph in some way to ensure that these negative edges can only be traveled once.

Perhaps the cleanest way of dealing with this is to add a directed edge from pasture 𝑁 to each other 
pastures containing a haybale, with a weight of (the length of the path from that vertex to N, minus the 
yumminess of that haybale). We also delete all other edges connected to pasture 𝑁, so that any path to the 
barn *must* use some haybale. This graph would normally have negative cycles, but all of these cycles 
include vertex 𝑁(and we have deleted all edges leading into 𝑁) so we are still able to run Dijkstra's on 
the resulting graph. For each pasture, we take the difference between the distances obtained between the 
two runs of Dijkstra's algorithm. The cow can get to the barn if, and only if, the second value is at most 
the first (meaning eating the haybale did not make the path worse).

The total runtime is 𝑂(𝑀log𝑁) with a priority-queue based implementation of Dijkstra's.*/

#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

int N, M, K;
vector<int> nbrs[100001];
map<pair<int, int>, int> edgewt;
int H[100000], Y[100000];

map<int, int> dist;

void dijkstra(int source)
{
    set<pair<int, int>> visited;
    visited.insert(make_pair(0, source));
    while (!visited.empty())
    {
        int i = visited.begin()->second;
        visited.erase(visited.begin());
        for (auto j : nbrs[i])
            if (dist.count(j) == 0 || dist[i] + edgewt[make_pair(i, j)] < dist[j])
            {
                dist[j] = dist[i] + edgewt[make_pair(i, j)];
                visited.insert(make_pair(dist[j], j));
            }
    }
}

int main(void)
{
    ifstream fin("dining.in");
    ofstream fout("dining.out");
    fin >> N >> M >> K;
    for (int i = 0; i < M; i++)
    {
        int a, b, t;
        fin >> a >> b >> t;
        a--;
        b--;
        nbrs[a].push_back(b);
        nbrs[b].push_back(a);
        edgewt[make_pair(a, b)] = t;
        edgewt[make_pair(b, a)] = t;
    }
    for (int i = 0; i < K; i++)
    {
        fin >> H[i] >> Y[i];
        H[i]--;
    }

    dijkstra(N - 1);
    map<int, int> orig_dist = dist;
    for (int i = 0; i < K; i++)
    {
        nbrs[N].push_back(H[i]);
        edgewt[make_pair(N, H[i])] = orig_dist[H[i]] - Y[i];
    }
    dist.clear();
    dijkstra(N);
    for (int i = 0; i < N - 1; i++)
        fout << (dist[i] <= orig_dist[i]) << "\n";

    return 0;
}
//(Reference : Retrieved from USACO website)