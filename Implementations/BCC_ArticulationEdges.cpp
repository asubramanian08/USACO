// From AlphaStar-PlatinumB week3

// Biconnected components with articulation edges
#define NA -1
using pii = pair<int, int>;
int *low, *vis, *component;
int added, numComps;
vector<int> *graph;
void DFS_BCC(int node, int par, vector<pii> &edges)
{
    low[node] = vis[node] = ++added;
    for (int next : graph[node])
        if (vis[next] == NA)
        {
            edges.push_back(pii(node, next));
            DFS_BCC(next, node, edges);
            low[node] = min(low[node], low[next]);
            if (vis[node] < low[next] && ++numComps)
                for (pii rEdge(node, next), prev(NA, NA); prev != rEdge; prev = edges.back(), edges.pop_back())
                {
                    component[edges.back().first] = edges.back().first == node ? NA : numComps - 1;
                    component[edges.back().second] = edges.back().second == node ? NA : numComps - 1;
                }
        }
        else if (vis[next] < vis[node] && next != par)
        {
            low[node] = min(low[node], vis[next]);
            edges.push_back(pii(node, next));
        }
}
/* return number of components
 * extra param: preset the graph */
int BiconnectedComponents(int numNodes)
{
    low = new int[numNodes];
    vis = new int[numNodes];
    component = new int[numNodes];
    added = numComps = 0;
    for (int i = 0; i < numNodes; i++)
        low[i] = vis[i] = component[i] = NA;
    vector<pii> edges;
    // if root is a separate component
    edges.push_back(pii(0, 0));
    for (int i = 0; i < numNodes; i++)
        if (vis[i] == NA)
            DFS_BCC(i, NA, edges);
    for (numComps++; !edges.empty(); edges.pop_back())
        component[edges.back().first] = component[edges.back().second] = numComps - 1;
    return numComps;
}