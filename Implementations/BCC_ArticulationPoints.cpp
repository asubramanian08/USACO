// From AlphaStar-PlatinumB week3

// Biconnected components
#define NA -1
using pii = pair<int, int>;
int *low, *vis;
vector<int> *component;
int added, numComps;
vector<int> *graph;
void DFS_BCC(int node, int par, vector<pii> &edges)
{
    low[node] = vis[node] = ++added;
    int children = 0;
    for (int next : graph[node])
        if (vis[next] == NA)
        {
            edges.push_back(pii(node, next));
            children++;
            DFS_BCC(next, node, edges);
            low[node] = min(low[node], low[next]);
            if ((par == NA ? children > 1 : low[next] >= vis[node]) && ++numComps)
                for (pii rEdge(node, next), prev(NA, NA); prev != rEdge; prev = edges.back(), edges.pop_back())
                {
                    component[edges.back().first].push_back(numComps - 1);
                    component[edges.back().second].push_back(numComps - 1);
                }
        }
        else if (next != par)
        {
            low[node] = min(low[node], vis[next]);
            if (vis[next] < vis[node])
                edges.push_back(pii(node, next));
        }
}
/* return number of components
 * extra param: preset the graph */
int biconnectedComponents(int numNodes)
{
    low = new int[numNodes];
    vis = new int[numNodes];
    component = new vector<int>[numNodes];
    added = numComps = 0;
    for (int i = 0; i < numNodes; i++)
        low[i] = vis[i] = NA;
    vector<pii> edges;
    for (int i = 0; i < numNodes; i++)
        if (vis[i] == NA)
        {
            DFS_BCC(i, NA, edges);
            if (!edges.empty())
                for (numComps++; !edges.empty(); edges.pop_back())
                {
                    component[edges.back().first].push_back(numComps - 1);
                    component[edges.back().second].push_back(numComps - 1);
                }
        }
    for (int i = 0; i < numNodes; i++)
    {
        sort(component[i].begin(), component[i].end());
        component[i].resize(unique(component[i].begin(), component[i].end()) - component[i].begin());
    }
    return numComps;
}
bool is_biconnected(int n1, int n2) // two pointer intersection
{
    int it1 = 0, it2 = 0;
    while (it1 < component[n1].size() && it2 < component[n2].size())
        if (component[n1][it1] < component[n2][it2])
            it1++;
        else if (component[n1][it1] > component[n2][it2])
            it2++;
        else
            return true;
    return false;
}