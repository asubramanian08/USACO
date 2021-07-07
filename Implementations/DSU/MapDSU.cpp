#include <map>
using namespace std;
//from starleague part1 lesson 2 q2
class MapDSU
{
private:
    map<int, pair<int, int>> m;

public:
    MapDSU(void);
    MapDSU(int n_ele, int *keys);
    //find its first parent
    void haveEle(int key);
    int root(int idx);
    bool is_connected(int n1, int n2);
    void connect(int n1, int n2);
    int compSize(int idx);
    int childrenSize(int idx); //specialization for this problem
};
MapDSU::MapDSU(void) = default;
MapDSU::MapDSU(int n_ele, int *keys)
{
    for (int i = 0; i < n_ele; i++)
        haveEle(keys[i]);
}
void MapDSU::haveEle(int key)
{
    if (m.find(key) == m.end())
        m[key] = pair<int, int>(key, 1);
}
int MapDSU::root(int idx)
{
    while (idx != m[idx].first)
    {
        m[idx].first = m[m[idx].first].first;
        idx = m[idx].first;
    }
    return idx;
}
bool MapDSU::is_connected(int n1, int n2) { return root(n1) == root(n2); }
void MapDSU::connect(int n1, int n2)
{
    haveEle(n1);
    haveEle(n2);
    int i = root(n1), j = root(n2);
    if (i == j)
        return;
    if (m[i].second < m[j].second)
    {
        m[i].first = j;
        m[j].second += m[i].second;
    }
    else
    {
        m[j].first = i;
        m[i].second += m[j].second;
    }
}
int MapDSU::compSize(int idx) { return m[root(idx)].second; }
int MapDSU::childrenSize(int idx) { return m[idx].second; }