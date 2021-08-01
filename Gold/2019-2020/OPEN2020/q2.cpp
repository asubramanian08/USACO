// Start: 12:14
// Think: NA
// Write:
// Debug:
// After looking at sol: 2:52-3:23
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define NA -1

int main(void)
{
    //read
#ifndef HOME
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);
#endif
    int numCows, numAdmires;
    cin >> numCows >> numAdmires;
    vector<int> *admirers = new vector<int>[numCows];
    int c1, c2;
    for (int i = 0; i < numAdmires; i++)
    {
        cin >> c1 >> c2;
        admirers[c1 - 1].push_back(c2 - 1);
    }

    //prep
    queue<int> q;
    int *par = new int[numCows];
    vector<int> *childs = new vector<int>[numCows];
    for (int i = 0; i < numCows; i++)
    {
        par[i] = i;
        childs[i].push_back(i);
        if (admirers[i].size() > 1)
            q.push(i);
    }

    //run queue till max 1 admirer
    while (!q.empty())
    {
        int cow = q.front();
        if (admirers[cow].size() <= 1)
        {
            q.pop();
            continue;
        }
        c1 = admirers[cow].front();
        c2 = admirers[cow].back();
        admirers[cow].pop_back();
        c1 = par[c1], c2 = par[c2];
        if (c1 == c2)
            continue;
        if (childs[c1].size() > childs[c2].size())
            swap(c1, c2);
        for (int child : childs[c1])
        {
            par[child] = c2;
            childs[c2].push_back(child);
        }
        for (int admirer : admirers[c1])
            admirers[c2].push_back(admirer);
        admirers[c1].clear();
        if (admirers[c2].size() > 1)
            q.push(c2);
    }

    //determine group
    int *group = new int[numCows];
    for (int i = 0; i < numCows; i++)
        group[i] = NA;
    int numGroups = 0;
    for (int i = 0; i < numCows; i++)
    {
        if (group[par[i]] == NA)
            group[par[i]] = ++numGroups;
        group[i] = group[par[i]];
    }

    //print and delete
    for (int i = 0; i < numCows; i++)
        cout << group[i] << endl;
    delete[] admirers;
    delete[] par;
    delete[] childs;
    delete[] group;
    return 0;
}