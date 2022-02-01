#include <iostream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

// DSU or union-find
class DSU
{
private:
    int *id;
    int *sz;
    bool *alive;

public:
    DSU(int n_ele);
    // find its first parent
    int root(int idx);
    bool is_connected(int n1, int n2);
    void connect(int n1, int n2);
    int compSize(int idx);
    void setAlive(int nd) { alive[root(nd)] = true; }
    bool getAlive(int nd) { return alive[root(nd)]; }
    ~DSU();
};
DSU::DSU(int n_ele)
{
    id = new int[n_ele];
    sz = new int[n_ele];
    alive = new bool[n_ele];
    for (int i = 0; i < n_ele; i++)
    {
        id[i] = i;
        sz[i] = 1;
        alive[i] = false;
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

void DFS(int nd, set<int> *graph, int *death, int setDeath)
{
    if (death[nd] == setDeath)
        return;
    death[nd] = setDeath;
    for (int next : graph[nd])
        DFS(next, graph, death, setDeath);
}

int main(void)
{
    // read
    int nodes, queries;
    cin >> nodes >> queries;
    set<int> *graph = new set<int>[nodes];
    int *death = new int[nodes];
    for (int i = 0; i < nodes; i++)
        death[i] = queries;
    using pii = pair<int, int>;
    vector<pii> conns;
    vector<pair<char, pii>> action;
    for (int i = 0; i < queries; i++)
    {
        char act;
        int n1, n2;
        cin >> act >> n1;
        if (act == 'A')
        {
            cin >> n2;
            n1--, n2--;
            conns.push_back(pii(n1, n2));
            graph[n1].insert(n2);
            graph[n2].insert(n1);
        }
        else
        {
            n1--;
            action.push_back(pair(act, pii(n1, i)));
            if (act == 'R')
            {
                graph[conns[n1].first].erase(conns[n1].second);
                graph[conns[n1].second].erase(conns[n1].first);
            }
            else
                death[n1] = -1;
        }
    }

    // things that never died
    queue<int> immortal;
    for (int i = 0; i < nodes; i++)
        if (death[i] == queries)
        {
            immortal.push(i);
            death[i] = 0; // like a vis
        }
    while (!immortal.empty())
    {
        int nd = immortal.front();
        immortal.pop();
        if (death[nd] == queries)
            continue;
        death[nd] = queries;
        for (int next : graph[nd])
            immortal.push(next);
    }

    // create DSU to represent graph
    DSU dsu(nodes);
    for (int i = 0; i < nodes; i++)
        for (int next : graph[i])
            dsu.connect(i, next);
    for (int i = 0; i < nodes; i++)
        if (death[i] == queries)
            dsu.setAlive(i);

    // got though insturctions in reverse
    for (int i = action.size() - 1; i >= 0; i--)
    {
        int searchSet = -1;
        if (action[i].first == 'D' && !dsu.getAlive(action[i].second.first))
            searchSet = action[i].second.first;
        if (action[i].first == 'R' && dsu.getAlive(conns[action[i].second.first].first) !=
                                          dsu.getAlive(conns[action[i].second.first].second))
            searchSet = dsu.getAlive(conns[action[i].second.first].first)
                            ? conns[action[i].second.first].second
                            : conns[action[i].second.first].first;
        if (searchSet != -1)
            DFS(searchSet, graph, death, action[i].second.second);
        if (action[i].first == 'D')
            dsu.setAlive(action[i].second.first);
        else
        {
            dsu.connect(conns[action[i].second.first].second,
                        conns[action[i].second.first].first);
            graph[conns[action[i].second.first].second].insert(conns[action[i].second.first].first);
            graph[conns[action[i].second.first].first].insert(conns[action[i].second.first].second);
        }
    }

    // print and delete
    for (int i = 0; i < nodes; i++)
        cout << death[i] << endl;
    return 0;
}