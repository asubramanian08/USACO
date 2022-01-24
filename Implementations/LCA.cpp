#include <vector>
#include <cmath>
using namespace std;

// Also main lecture in AlphaStar-PlatinumB week 2

// Least common ancestor -> binary lifting
#define NA -1
class LCA
{
private:
    int **sparseTBL, *dpt, length, log;
    vector<int> *graph;
    void init(int node, int parent, int lev);

public:
    LCA(vector<int> *g, int len);
    ~LCA();
    int query(int node1, int node2);
    int depth(int node);
};
void LCA::init(int node, int parent, int lev)
{
    dpt[node] = lev;
    sparseTBL[node][0] = parent;
    for (int i = 1; (i <= log) && (sparseTBL[node][i - 1] != NA); i++)
        sparseTBL[node][i] = sparseTBL[sparseTBL[node][i - 1]][i - 1];
    for (int i = 0; i < graph[node].size(); i++)
        if (graph[node][i] != parent)
            init(graph[node][i], node, lev + 1);
}
LCA::LCA(vector<int> *g, int len) : graph(g), length(len), log(log2(len))
{
    sparseTBL = new int *[length];
    for (int i = 0; i < length; i++)
    {
        sparseTBL[i] = new int[log + 1];
        for (int j = 0; j <= log; j++)
            sparseTBL[i][j] = NA;
    }
    dpt = new int[length];
    init(0, NA, 0);
}
LCA::~LCA()
{
    for (int i = 0; i < length; i++)
        delete[] sparseTBL[i];
    delete[] sparseTBL;
    delete[] dpt;
}
int LCA::query(int node1, int node2)
{
    // fix nodes
    if (dpt[node1] < dpt[node2])
    {
        int temp = node1;
        node1 = node2;
        node2 = temp;
    }
    for (int i = log; i >= 0; i--) // loop though bits
        if (dpt[node1] - (1 << i) >= dpt[node2])
            node1 = sparseTBL[node1][i];
    if (node1 == node2) // n2 is ancestor
        return node2;

    // main compute
    for (int i = log; i >= 0; i--)
        if (sparseTBL[node1][i] != sparseTBL[node2][i])
        {
            node1 = sparseTBL[node1][i];
            node2 = sparseTBL[node2][i];
        }
    return sparseTBL[node1][0];
}
int LCA::depth(int node) { return dpt[node]; }