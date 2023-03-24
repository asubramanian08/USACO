// 8:46 - 9:39
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define MAX_N 100010

// BIT tree with XOR
class XOR_BIT
{
private:
    int *bTree;
    int elements;

public:
    XOR_BIT(int elem);
    ~XOR_BIT() { delete[] bTree; }
    int query(int node);
    void updt(int node, int cng);
};
XOR_BIT::XOR_BIT(int elem)
{
    elements = elem;
    bTree = new int[elem + 1];
    for (int i = 1; i <= elem; i++)
        bTree[i] = 0;
}
int XOR_BIT::query(int node)
{
    if (node == -1)
        return 0;
    int ans = 0;
    for (int i = node + 1; i > 0; i -= (i & -i))
        ans ^= bTree[i];
    return ans;
}
void XOR_BIT::updt(int node, int cng)
{
    for (int i = node + 1; i <= elements; i += (i & -i))
        bTree[i] ^= cng;
}

// Least common ancestor
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

// flatten the tree
int flatten(vector<int> *graph, int *first, int *second, int node, int pos, int parent)
{
    first[node] = pos;
    for (int next : graph[node])
        if (next != parent)
            pos = flatten(graph, first, second, next, pos + 1, node);
    return second[node] = pos + 1;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
#ifndef HOME
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
#endif
    int n, q, x, y, op;
    cin >> n >> q;
    int enjoyment[MAX_N];
    for (int i = 0; i < n; i++)
        cin >> enjoyment[i];
    vector<int> graph[MAX_N];
    for (int i = 1; i < n; i++)
    {
        cin >> x >> y;
        x--, y--;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    LCA lca(graph, n);
    int first[MAX_N], second[MAX_N];
    flatten(graph, first, second, 0, 0, -1);
    XOR_BIT xb(2 * n);
    for (int i = 0; i < n; i++)
    {
        xb.updt(first[i], enjoyment[i]);
        xb.updt(second[i], enjoyment[i]);
    }
    while (q--)
    {
        cin >> op >> x >> y;
        x--;
        if (op == 1)
        {
            int change = enjoyment[x] ^ y;
            xb.updt(first[x], change);
            xb.updt(second[x], change);
            enjoyment[x] = y;
            continue;
        }
        y--;
        cout << (xb.query(first[x]) ^ xb.query(first[y]) ^ enjoyment[lca.query(x, y)]) << endl;
    }
    return 0;
}