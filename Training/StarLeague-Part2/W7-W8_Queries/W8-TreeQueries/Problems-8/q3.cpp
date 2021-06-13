#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//ancestor decedent relationship
class ADR
{
private:
    int *inTime;
    int *outTime;
    int Time, numElements;
    vector<int> *conns;
    void findTimes(int node, int parent);

public:
    ADR() {}
    ADR(vector<int> *conns, int n_ele);
    bool isAns(int node, int parent);
};
void ADR::findTimes(int node, int parent)
{
    inTime[node] = ++Time;
    for (int i = 0; i < conns[node].size(); i++)
        if (conns[node][i] != parent)
            findTimes(conns[node][i], node);
    outTime[node] = ++Time;
}
bool ADR::isAns(int node, int parent)
{
    return (inTime[parent] <= inTime[node]) &&
           (outTime[parent] >= outTime[node]);
}
ADR::ADR(vector<int> *conns_, int n_ele)
{
    conns = conns_;
    numElements = n_ele;
    inTime = new int[numElements];
    outTime = new int[numElements];
    Time = 0;
    findTimes(0, -1);
}

// declarations and init.
class query
{
public:
    int f1, f2, milkPref;
    query()
    {
    }
    query(int f1_, int f2_, int milkPref_)
    {
        f1 = f1_;
        f2 = f2_;
        milkPref = milkPref_;
    }
};
typedef pair<int, int> pii;
int *milk;
vector<int> *conns;
int Time, *inTime, *outTime;
query *queries;
ADR times;
vector<pii> *nodeQuery;
bool *happy;
stack<int> *onPath;
int *toNode;

void DFS(int node, int parent)
{
    onPath[milk[node]].push(node);
    for (int i = 0; i < conns[node].size(); i++)
        if ((toNode[node] = conns[node][i]) != parent)
            DFS(toNode[node], node);

    int posAns, pairNode; //possible ancestor
    for (int i = 0; i < nodeQuery[node].size(); i++)
    {
        pairNode = queries[nodeQuery[node][i].first].f2;
        if (nodeQuery[node][i].second == 2)
            pairNode = queries[nodeQuery[node][i].first].f1;

        if (onPath[queries[nodeQuery[node][i].first].milkPref].empty())
            continue;
        posAns = onPath[queries[nodeQuery[node][i].first].milkPref].top();
        if (times.isAns(node, posAns) &&                                        //it is ans. of this one
            (!times.isAns(pairNode, posAns) ||                                  //not ans. of the other one
             ((pairNode == posAns) || !times.isAns(pairNode, toNode[posAns])))) //OR is the LAC
            happy[nodeQuery[node][i].first] = true;
    }

    onPath[milk[node]].pop();
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("milkvisits.in", "r", stdin);
    junk = freopen("milkvisits.out", "w", stdout);
    int farms, friends;
    cin >> farms >> friends;
    milk = new int[farms];
    for (int i = 0; i < farms; i++)
    {
        cin >> milk[i];
        milk[i]--;
    }
    conns = new vector<int>[farms];
    int f1, f2;
    for (int i = 1; i < farms; i++)
    {
        cin >> f1 >> f2;
        f1--;
        f2--;
        conns[f1].push_back(f2);
        conns[f2].push_back(f1);
    }
    queries = new query[friends];
    for (int i = 0; i < friends; i++)
    {
        cin >> queries[i].f1 >> queries[i].f2 >> queries[i].milkPref;
        queries[i].f1--;
        queries[i].f2--;
        queries[i].milkPref--;
    }
    times = ADR(conns, farms);

    //set up (data structures)
    nodeQuery = new vector<pii>[farms];
    for (int i = 0; i < friends; i++)
    {
        nodeQuery[queries[i].f1].push_back(make_pair(i, 1));
        nodeQuery[queries[i].f2].push_back(make_pair(i, 2));
    }
    happy = new bool[friends];
    for (int i = 0; i < friends; i++)
        happy[i] = false;
    onPath = new stack<int>[farms];
    toNode = new int[farms];

    //get ans (DFS) and print
    DFS(0, -1);
    for (int i = 0; i < friends; i++)
        cout << happy[i];
    cout << endl;
    return 0;
}