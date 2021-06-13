#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//getting things ready
#define BIG_NUM 1000000
typedef pair<int, int> pii;
struct pie
{
    int bVal;
    int eVal;
    int orgLoc;
};

//compares
int bCompare(const void *p1, const void *p2)
{
    return ((pie *)p1)->eVal - ((pie *)p2)->eVal;
}
int eCompare(const void *p1, const void *p2)
{
    return ((pie *)p1)->bVal - ((pie *)p2)->bVal;
}
int orgCompare(const void *p1, const void *p2)
{
    return ((pie *)p1)->orgLoc - ((pie *)p2)->orgLoc;
}

//initialization
pie *bPies;
pie *ePies;
vector<int> *bConns;
vector<int> *eConns;
int *bCost;
int *eCost;
queue<int> bQ;
queue<int> eQ;

//b&e BFS funcs
void bFind(int source)
{
    for (int i = 0; i < bConns[source].size(); i++)
        if (eCost[bConns[source][i]] > bCost[source] + 1)
        {
            eCost[bConns[source][i]] = bCost[source] + 1;
            eQ.push(bConns[source][i]);
        }
}
void eFind(int source)
{
    for (int i = 0; i < eConns[source].size(); i++)
        if (bCost[eConns[source][i]] > eCost[source] + 1)
        {
            bCost[eConns[source][i]] = eCost[source] + 1;
            bQ.push(eConns[source][i]);
        }
}

int main(void)
{
    /*FILE *junk;
    junk = freopen("piepie.in", "r", stdin);
    junk = freopen("piepie.out", "w", stdout);*/
    //get pies
    int numPies, range;
    cin >> numPies >> range;
    bPies = new pie[numPies];
    for (int i = 0; i < numPies; i++)
    {
        cin >> bPies[i].bVal;
        cin >> bPies[i].eVal;
        bPies[i].orgLoc = i;
    }
    qsort(bPies, numPies, sizeof(pie), bCompare);
    ePies = new pie[numPies];
    for (int i = 0; i < numPies; i++)
    {
        cin >> ePies[i].bVal;
        cin >> ePies[i].eVal;
        ePies[i].orgLoc = i;
    }
    qsort(ePies, numPies, sizeof(pie), eCompare);

    //find graph (reverse direction)
    bConns = new vector<int>[numPies];
    eConns = new vector<int>[numPies];
    for (int i = 0; i < numPies; i++)
    {
        int low = 0;
        int high = numPies;
        int goal = bPies[i].bVal - range;
        if (ePies[low].bVal >= goal)
            high = low;
        while (high - low > 1)
        {
            if (ePies[(high + low) / 2].bVal < goal)
                low = (high + low) / 2;
            else
                high = (high + low) / 2;
        }
        for (int j = high; (j < numPies) && (ePies[j].bVal <= bPies[i].bVal); j++)
            bConns[bPies[i].orgLoc].push_back(ePies[j].orgLoc);
    }
    for (int i = 0; i < numPies; i++)
    {
        int low = 0;
        int high = numPies;
        int goal = ePies[i].eVal - range;
        if (bPies[low].eVal >= goal)
            high = low;
        while (high - low > 1)
        {
            if (bPies[(high + low) / 2].eVal < goal)
                low = (high + low) / 2;
            else
                high = (high + low) / 2;
        }
        for (int j = high; (j < numPies) && (bPies[j].eVal <= ePies[i].eVal); j++)
            eConns[ePies[i].orgLoc].push_back(bPies[j].orgLoc);
    }
    qsort(bPies, numPies, sizeof(pie), orgCompare);
    qsort(ePies, numPies, sizeof(pie), orgCompare);

    //set costs and start queue
    bCost = new int[numPies];
    eCost = new int[numPies];
    for (int i = 0; i < numPies; i++)
        if (bPies[i].eVal == 0)
        {
            bCost[i] = 1;
            bQ.push(i);
        }
        else
            bCost[i] = BIG_NUM;
    for (int i = 0; i < numPies; i++)
        if (ePies[i].bVal == 0)
        {
            eCost[i] = 1;
            eQ.push(i);
        }
        else
            eCost[i] = BIG_NUM;

    //compute costs
    while (!bQ.empty() || !eQ.empty())
    {
        if (eQ.empty() || (!bQ.empty() && bCost[bQ.front()] < eCost[eQ.front()]))
        {
            bFind(bQ.front());
            bQ.pop();
        }
        else
        {
            eFind(eQ.front());
            eQ.pop();
        }
    }

    //print out
    for (int i = 0; i < numPies; i++)
    {
        if (bCost[i] != BIG_NUM)
            cout << bCost[i] << endl;
        else
            cout << "-1" << endl;
    }

    //return
    return 0;
}