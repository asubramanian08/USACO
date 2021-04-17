// Start: 3:00
// Think: 3:15
// Write: 3:27
// Debug: 3:57 -> set exception at function end
#include <iostream>
#include <utility>
#include <set>
#include <map>
using namespace std;

typedef pair<int, int> cow;
#define BIG_NUM 1000000500

int main(void)
{
    //read
#ifndef HOME
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    cow *cows = new cow[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].first >> cows[i].second;

    //number of id's
    set<int> ids;
    for (int i = 0; i < numCows; i++)
        ids.insert(cows[i].second);
    int numID = ids.size();

    //sweep line -> smallest dist
    sort(&cows[0], &cows[numCows]); //by loc
    int minDist = BIG_NUM, rem;
    map<int, int> lastID;
    set<int> lastPos;
    for (int i = 0; i < numCows; i++)
    {
        if (lastID.find(cows[i].second) != lastID.end())
            lastPos.erase(lastID[cows[i].second]);
        lastID[cows[i].second] = cows[i].first;
        lastPos.insert(cows[i].first);
        if (lastID.size() < numID)
            continue;
        minDist = min(minDist, cows[i].first - *lastPos.begin());
    }

    //print and delete
    cout << minDist;
    delete[] cows;
    return 0;
}