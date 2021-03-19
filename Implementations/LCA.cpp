#include <vector>
using namespace std;

//Least common ancestor -> binary lifting
#define NP -1
class LCA
{
private:
    int **sparseTBL;
    int *level_;
    int numEle, Log;
    vector<int> *conns_;
    void initDFS(int node, int parent, int lev);

public:
    LCA(vector<int> *conns__, int n_ele);
    ~LCA();
    int lca(int node1, int node2);
    int level(int node);
};
void LCA::initDFS(int node, int parent, int lev)
{
    level_[node] = lev;
    sparseTBL[node][0] = parent;
    for (int i = 1; (i <= Log) && (sparseTBL[node][i - 1] != NP); i++)
        sparseTBL[node][i] = sparseTBL[sparseTBL[node][i - 1]][i - 1];

    for (int i = 0; i < conns_[node].size(); i++)
        if (conns_[node][i] != parent)
            initDFS(conns_[node][i], node, lev + 1);
}
LCA::LCA(vector<int> *conns__, int n_ele)
{
    numEle = n_ele;
    conns_ = conns__;
    Log = log2(numEle);
    sparseTBL = new int *[numEle];
    for (int i = 0; i < numEle; i++)
    {
        sparseTBL[i] = new int[Log + 1];
        for (int j = 0; j <= Log; j++)
            sparseTBL[i][j] = NP;
    }
    level_ = new int[numEle];
    initDFS(0, NP, 0);
}
LCA::~LCA()
{
    for (int i = 0; i < numEle; i++)
        delete[] sparseTBL[i];
    delete[] sparseTBL;
    delete[] level_;
    //conns was passed
}
int LCA::lca(int node1, int node2)
{
    //fix nodes
    if (level_[node1] < level_[node2])
    {
        int temp = node1;
        node1 = node2;
        node2 = temp;
    }
    for (int i = Log; i >= 0; i--) //loop though bits
        if (level_[node1] - (1 << i) >= level_[node2])
            node1 = sparseTBL[node1][i];
    if (node1 == node2) //n2 is ancestor
        return node2;

    //main compute
    for (int i = Log; i >= 0; i--)
        if (sparseTBL[node1][i] != sparseTBL[node2][i])
        {
            node1 = sparseTBL[node1][i];
            node2 = sparseTBL[node2][i];
        }
    return sparseTBL[node1][0];
}
int LCA::level(int node) { return level_[node]; }