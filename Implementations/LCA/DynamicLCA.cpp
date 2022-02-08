#include <iostream>
#include <vector>
#include <array>
using namespace std;

// Dynamic least common ancestor
#define NA -1
#define GLOB_LOG 30
class DynamicLCA /*Not tested*/
{
private:
    vector<array<int, GLOB_LOG + 1>> sparseTBL;
    vector<int> dpt;
    vector<vector<int>> tree;

public:
    int query(int node1, int node2);
    int depth(int node) { return dpt[node]; }
    void add(int par);
};
int DynamicLCA::query(int node1, int node2)
{
    // fix nodes
    if (dpt[node1] < dpt[node2])
        swap(node1, node2);
    for (int i = GLOB_LOG; i >= 0; i--) // loop though bits
        if (dpt[node1] - (1 << i) >= dpt[node2])
            node1 = sparseTBL[node1][i];
    if (node1 == node2) // n2 is ancestor
        return node2;

    // main compute
    for (int i = GLOB_LOG; i >= 0; i--)
        if (sparseTBL[node1][i] != sparseTBL[node2][i])
            node1 = sparseTBL[node1][i],
            node2 = sparseTBL[node2][i];
    return sparseTBL[node1][0];
}
void DynamicLCA::add(int par)
{
    int node = dpt.size();
    sparseTBL.push_back(array<int, GLOB_LOG + 1>());
    sparseTBL.back().fill(NA);
    sparseTBL[node][0] = par;
    for (int i = 1; (i <= GLOB_LOG) && (sparseTBL[node][i - 1] != NA); i++)
        sparseTBL[node][i] = sparseTBL[sparseTBL[node][i - 1]][i - 1];
    dpt.push_back(dpt[par] + 1);
    tree[par].push_back(node);
    tree.push_back({});
}