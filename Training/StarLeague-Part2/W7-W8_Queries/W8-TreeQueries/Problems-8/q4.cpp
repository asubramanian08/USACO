#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//Euler tour
vector<int> *conns;
vector<int> ET_arr;
int *inTime;
int *outTime;
int Time;
void EulerTour(int node, int parent)
{
    ET_arr.push_back(node);
    inTime[node] = Time;
    Time++;

    for (int i = 0; i < conns[node].size(); i++)
        if (conns[node][i] != parent)
            EulerTour(conns[node][i], node);

    ET_arr.push_back(node);
    outTime[node] = Time;
    Time++;
}

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

//BIT or fenwick tree -> CHANGED for XOR
class BIT
{
private:
    int elements;
    int *bTree;

public:
    BIT(int elem);
    BIT(int elem, int *initialize, int numInit);
    ~BIT() { delete[] bTree; }
    int query(int node);
    void updt(int node, int cng);
};
BIT::BIT(int elem)
{
    elements = elem;
    bTree = new int[elem + 1];
    for (int i = 1; i <= elem; i++)
        bTree[i] = 0;
}
BIT::BIT(int elem, int *initialize, int numInit)
{
    elements = elem;
    bTree = new int[elem + 1];
    for (int i = 1; i <= elem; i++)
        bTree[i] = 0;
    for (int i = 0; i < numInit; i++)
        updt(i, initialize[i]);
}
int BIT::query(int node)
{
    int sum = 0;
    for (int i = node + 1; i > 0; i -= (i & -i))
        sum ^= bTree[i];
    return sum;
}
void BIT::updt(int node, int cng)
{
    for (int i = node + 1; i <= elements; i += (i & -i))
        bTree[i] ^= cng;
}

int main(void)
{
    //read
    /*FILE *junk;
    junk = freopen("cowland.in", "r", stdin);
    junk = freopen("cowland.out", "w", stdout);*/
    int attractions, actions;
    cin >> attractions >> actions;
    int *enjoy = new int[attractions];
    for (int i = 0; i < attractions; i++)
        cin >> enjoy[i];
    conns = new vector<int>[attractions];
    int a1, a2;
    int count;
    for (int i = 1; i < attractions; i++)
    {
        cin >> a1 >> a2;
        a1--;
        a2--;
        conns[a1].push_back(a2);
        conns[a2].push_back(a1);
    }

    //set up things for actions
    inTime = new int[attractions];
    outTime = new int[attractions];
    Time = 0;
    EulerTour(0, -1);
    LCA getLCA(conns, attractions);
    BIT XOR_BIT(ET_arr.size());
    for (int i = 0; i < ET_arr.size(); i++)
        XOR_BIT.updt(i, enjoy[ET_arr[i]]);

    //do actions and print
    int mode, node, other;
    int change;
    int sum1, sum2, ansSum, ans; //ans = ancestor
    for (int i = 0; i < actions; i++)
    {
        cin >> mode >> node >> other;
        node--;
        if (mode == 1) //updating
        {
            change = XOR_BIT.query(inTime[node]) ^ XOR_BIT.query(inTime[node] - 1);
            change = other ^ change;
            XOR_BIT.updt(inTime[node], change);
            XOR_BIT.updt(outTime[node], change);
        }
        else //querying
        {
            other--;
            if (other < node)
            {
                int temp = node;
                node = other;
                other = temp;
            }

            ans = getLCA.lca(node, other);
            sum1 = XOR_BIT.query(inTime[node]) ^ XOR_BIT.query(inTime[ans]);
            sum2 = XOR_BIT.query(inTime[other]) ^ XOR_BIT.query(inTime[ans]);
            ansSum = XOR_BIT.query(inTime[ans]) ^ XOR_BIT.query(inTime[ans] - 1);
            cout << (sum1 ^ sum2 ^ ansSum) << endl;
        }
    }
    return 0;
}