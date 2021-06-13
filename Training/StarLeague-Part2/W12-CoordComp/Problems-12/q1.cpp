#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct action
{
    bool is_query;
    int num1, num2;
};
#define newPos(x) (lower_bound(map.begin(), map.end(), (x)) - map.begin())

//BIT or fenwick tree
class BIT
{
private:
    int *bTree;
    int elements;

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
    if (node == -1)
        return 0;
    int sum = 0;
    for (int i = node + 1; i > 0; i -= (i & -i))
        sum += bTree[i];
    return sum;
}
void BIT::updt(int node, int cng)
{
    for (int i = node + 1; i <= elements; i += (i & -i))
        bTree[i] += cng;
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("swalking2.in", "r", stdin);
    junk = freopen("swalking2.out", "w", stdout);
    int numCows, numStalls, numActions, minCows, relStalls;
    cin >> numCows >> numStalls >> numActions >> minCows;
    int *cows = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i];
    action *actions = new action[numActions];
    for (int i = 0; i < numActions; i++)
        cin >> actions[i].is_query >> actions[i].num1 >> actions[i].num2;

    //compress coordinates
    //get the map
    vector<int> map;
    for (int i = 0; i < numCows; i++)
        map.push_back(cows[i]);
    for (int i = 0; i < numActions; i++)
    {
        if (actions[i].is_query)
            map.push_back(actions[i].num1);
        map.push_back(actions[i].num2);
    }
    sort(map.begin(), map.end());
    map.resize(unique(map.begin(), map.end()) - map.begin());
    relStalls = map.size();
    //change the values
    for (int i = 0; i < numCows; i++)
        cows[i] = newPos(cows[i]);
    for (int i = 0; i < numActions; i++)
    {
        if (actions[i].is_query)
            actions[i].num1 = newPos(actions[i].num1);
        actions[i].num2 = newPos(actions[i].num2);
    }

    //initialize and start the bit tree
    BIT stalls(relStalls);
    for (int i = 0; i < numCows; i++)
        stalls.updt(cows[i], 1);

    //do the actions
    int range1, range2, cowsInRange;
    for (int i = 0; i < numActions; i++)
        if (!actions[i].is_query)
        {
            stalls.updt(cows[actions[i].num1 - 1], -1);
            cows[actions[i].num1 - 1] = actions[i].num2;
            stalls.updt(cows[actions[i].num1 - 1], 1);
        }
        else
        {
            range1 = stalls.query(actions[i].num1 - 1);
            range2 = stalls.query(actions[i].num2);
            cowsInRange = range2 - range1;
            if (cowsInRange > minCows)
                cout << cowsInRange << endl;
        }

    //delete
    delete[] cows;
    delete[] actions;
    return 0;
}