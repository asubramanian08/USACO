#include <vector>
using std::vector;
//from star league part 1 lesson 3 q3
class DSU
{
private:
    vector<int> id, sz;

public:
    DSU(int n_ele = 0);
    //find its first parent
    int root(int idx);
    bool is_connected(int n1, int n2);
    void connect(int n1, int n2);
    void addEle(void);
    int compSize(int idx);
    int numEle(void);
};
DSU::DSU(int n_ele)
{
    id.resize(n_ele);
    sz.resize(n_ele);
    for (int i = 0; i < n_ele; i++)
        addEle();
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
void DSU::addEle(void)
{
    id.push_back(id.size());
    sz.push_back(1);
}
int DSU::compSize(int idx) { return sz[root(idx)]; }
int DSU::numEle(void) { return id.size(); }