// Start: 3:34
// Think: 4:00, 4:25-4:39
// Write: 5:07
// Debug: 5:14
#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;

using station = pair<int, int>;

int main(void)
{
    //read
#ifndef HOME
    freopen("fuel.in", "r", stdin);
    freopen("fuel.out", "w", stdout);
#endif
    int numStations, maxCap, startCap, dist;
    cin >> numStations >> maxCap >> startCap >> dist;
    station *stations = new station[numStations];
    for (int i = 0; i < numStations; i++)
        cin >> stations[i].first >> stations[i].second;
    sort(stations, stations + numStations); //by pos

    //find where is stops
    int *priceSort = new int[numStations];
    iota(priceSort, priceSort + numStations, 0);
    sort(priceSort, priceSort + numStations, [stations](int x, int y)
         { return stations[x].second < stations[y].second; });
    set<int> lessPos;
    lessPos.insert(dist);
    int *stopAt = new int[numStations];
    for (int i = 0; i < numStations; i++)
    {
        stopAt[priceSort[i]] = min(stations[priceSort[i]].first + maxCap,
                                   *lessPos.lower_bound(stations[priceSort[i]].first));
        lessPos.insert(stations[priceSort[i]].first);
    }

    //calculate the cost
    int pos = startCap;
    long long cost = 0;
    for (int i = 0; i < numStations; i++)
    {
        if (pos < stations[i].first)
        {
            cost = -1;
            break;
        }
        if (stopAt[i] > pos)
        {
            cost += (long long)(stopAt[i] - pos) * (long long)stations[i].second;
            pos = stopAt[i];
        }
    }

    //print and delete
    cout << cost << endl;
    delete[] stations;
    delete[] priceSort;
    delete[] stopAt;
    return 0;
}