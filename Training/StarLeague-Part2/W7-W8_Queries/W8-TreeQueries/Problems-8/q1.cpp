#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
struct query
{
    int minRel, src, orgLoc;
};
class conn
{
public:
    int n1, n2, wt;
    conn(){};
    conn(int from_, int to_, int wt_)
    {
        n1 = from_;
        n2 = to_;
        wt = wt_;
    }
    const conn &operator=(const conn &c)
    {
        n1 = c.n1;
        n2 = c.n2;
        wt = c.wt;
        return *this;
    }
};

//DSU or union-find
class DSU
{
private:
    int *id;
    int *sz;

public:
    DSU(int n_ele);
    //find its first parent
    int root(int idx);
    bool is_connected(int n1, int n2);
    void connect(int n1, int n2);
    int numConns(int idx);
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
int DSU::numConns(int idx)
{
    return sz[root(idx)];
}
DSU::~DSU()
{
    delete[] id;
    delete[] sz;
}

conn *conns;
query *queries;
int cmpConn(const void *p1, const void *p2)
{
    return ((conn *)p2)->wt - ((conn *)p1)->wt;
}
int cmpQuery(const void *p1, const void *p2)
{
    return ((query *)p2)->minRel - ((query *)p1)->minRel;
}
int cmpAnsCnt(const void *p1, const void *p2)
{
    return ((pii *)p1)->second - ((pii *)p2)->second;
}

int main(void)
{
    /*FILE *junk;
    junk = freopen("mootube.in", "r", stdin);
    junk = freopen("mootube.out", "w", stdout);*/
    //read
    int vids, numQueries;
    cin >> vids >> numQueries;
    int v1, v2, wt;
    conns = new conn[vids - 1];
    for (int i = 1; i < vids; i++)
    {
        cin >> v1 >> v2 >> wt;
        v1--;
        v2--;
        conns[i - 1] = conn(v1, v2, wt);
    }
    queries = new query[numQueries];
    for (int i = 0; i < numQueries; i++)
    {
        cin >> queries[i].minRel >> queries[i].src;
        queries[i].src--;
        queries[i].orgLoc = i;
    }

    //pepare for answer
    qsort(conns, vids - 1, sizeof(conn), cmpConn);
    qsort(queries, numQueries, sizeof(query), cmpQuery);
    DSU recommended(vids);

    //compute ans
    pii *vidCnt = new pii[numQueries];
    int connLoc = 0;
    for (int i = 0; i < numQueries; i++)
    {
        while ((connLoc < vids - 1) && (conns[connLoc].wt >= queries[i].minRel))
        {
            recommended.connect(conns[connLoc].n1, conns[connLoc].n2);
            connLoc++;
        }
        vidCnt[i].first = recommended.numConns(queries[i].src) - 1;
        vidCnt[i].second = queries[i].orgLoc;
    }

    //print
    qsort(vidCnt, numQueries, sizeof(pii), cmpAnsCnt);
    for (int i = 0; i < numQueries; i++)
        cout << vidCnt[i].first << endl;
    return 0;
}