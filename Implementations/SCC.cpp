// AlphaStar-PlatinumB week 4

// Strongly Connected Components -> might be done wrong
#define NA -1
void TopologicalOrder(int node, vector<int> *graph, vector<int> &order, bool *vis)
{
    if (vis[node])
        return;
    vis[node] = true;
    for (int next : graph[node])
        TopologicalOrder(next, graph, order, vis);
    order.push_back(node);
}
void DFS_component(int node, vector<int> *graph, int *comp, int currComp)
{
    if (comp[node] != NA)
        return;
    comp[node] = currComp;
    for (int next : graph[node])
        DFS_component(next, graph, comp, currComp);
}
int *SCC(vector<int> *graph, int numNodes)
{
    vector<int> order;
    bool *vis = new bool[numNodes];
    fill(vis, vis + numNodes, false);
    for (int i = 0; i < numNodes; i++)
        TopologicalOrder(i, graph, order, vis);
    reverse(order.begin(), order.end());
    vector<int> *rgraph = new vector<int>[numNodes];
    for (int i = 0; i < numNodes; i++)
        for (int next : graph[i])
            rgraph[next].push_back(i);
    int *component = new int[numNodes];
    fill(component, component + numNodes, NA);
    int compCt = -1;
    for (int i = 0; i < numNodes; i++)
        if (component[order[i]] == NA)
            DFS_component(order[i], rgraph, component, ++compCt);
    delete[] vis;
    delete[] rgraph;
    return component;
}