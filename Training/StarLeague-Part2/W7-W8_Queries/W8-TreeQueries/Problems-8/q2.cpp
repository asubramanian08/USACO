#include <iostream>
#include <vector>
#include <set>
#include <cstring>
using namespace std;

//init
#define MAX_PATH 100007
vector<int> *conns;
int farms;
int *subTree_sz;
int seeking[MAX_PATH];
int *parent;

//funcs (important part of code)
void countNodes(int node)
{
    subTree_sz[node] = 1;
    for (int i = 0; i < conns[node].size(); i++)
    {
        if (conns[node][i] == parent[node])
            continue;
        parent[conns[node][i]] = node;
        countNodes(conns[node][i]);
        subTree_sz[node] += subTree_sz[conns[node][i]];
    }
}
bool isPoss(int pathLen) //from usaco solution
{
    memset(seeking, 0, sizeof(int) * pathLen);
    int count = 0, leftOver;
    for (int i = 0; i < farms; i++)
    {
        for (int j = 0; j < conns[i].size(); j++)
        {
            if (conns[i][j] == parent[i]) //if this is the parent
                leftOver = farms - subTree_sz[i];
            else
                leftOver = subTree_sz[conns[i][j]];
            leftOver %= pathLen;
            if (leftOver == 0)
                continue;
            if (seeking[leftOver])
            {
                seeking[leftOver]--;
                count--;
            }
            else
            {
                seeking[pathLen - leftOver]++;
                count++;
            }
        }
        if (count != 0)
            return false;
    }
    return true;
}

int main(void)
{
    //read + setup
    /*FILE *junk;
    junk = freopen("deleg.in", "r", stdin);
    junk = freopen("deleg.out", "w", stdout);*/
    cin >> farms;
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
    subTree_sz = new int[farms];
    parent = new int[farms];
    parent[0] = -1;
    countNodes(0);

    //find if the things are possible & print
    for (int i = 1; i < farms; i++)
        if ((farms - 1) % i != 0) //can't equally divide
            cout << '0';
        else if (isPoss(i)) //check if this can work
            cout << '1';
        else
            cout << '0';
    cout << endl;
    return 0;
}