// Start: 9:18
// Think: ?, 10:00-10:20
// Write: 10:27
// Debug: 10:27
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// DSU or union-find
class DSU
{
private:
    int *id;
    int *sz;

public:
    DSU(int n_ele);
    // find its first parent
    int root(int idx);
    bool is_connected(int n1, int n2);
    void connect(int n1, int n2);
    int compSize(int idx);
    ~DSU();
};
DSU::DSU(int n_ele)
{
    id = new int[n_ele];
    sz = new int[n_ele];
    for (int i = 0; i < n_ele; i++)
    {
        id[i] = i;
        sz[i] = 1;
    }
}
int DSU::root(int idx)
{
    while (idx != id[idx])
    {
        id[idx] = id[id[idx]];
        idx = id[idx];
    }
    return idx;
}
bool DSU::is_connected(int n1, int n2) { return root(n1) == root(n2); }
void DSU::connect(int n1, int n2)
{
    int i = root(n1), j = root(n2);
    if (i == j)
        return;
    if (sz[i] < sz[j])
    {
        id[i] = j;
        sz[j] += sz[i];
    }
    else
    {
        id[j] = i;
        sz[i] += sz[j];
    }
}
int DSU::compSize(int idx) { return sz[root(idx)]; }
DSU::~DSU()
{
    delete[] id;
    delete[] sz;
}

int main(void)
{
    int numNodes;
    cin >> numNodes;
    DSU dsu(numNodes * 2);
    using pii = pair<int, int>;
    vector<pair<int, pii>> edges;
    for (int i = 0; i < numNodes; i++)
    {
        int cost, p1, p2, p3, p4;
        cin >> cost >> p1 >> p2 >> p3 >> p4;
        p1--, p2--, p3--, p4--;
        dsu.connect(p1, p2);
        dsu.connect(p3, p4);
        edges.push_back(pair(cost, pii(p1, p3)));
        edges.push_back(pair(cost, pii(p1, p4)));
    }
    sort(edges.begin(), edges.end());
    int totalCost = 0;
    for (auto edge : edges)
        if (!dsu.is_connected(edge.second.first, edge.second.second))
        {
            totalCost += edge.first;
            dsu.connect(edge.second.first, edge.second.second);
        }
    cout << totalCost << endl;
    return 0;
}