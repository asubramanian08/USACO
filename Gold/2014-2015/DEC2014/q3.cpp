// Start: 9:38
// Think: 9:58
// Write: 10:14
// Debug: 10:23
//Right idea - segment tree
#include <iostream>
#include <set>
using namespace std;

using pii = pair<int, int>;

int main(void)
{
    //read
#ifndef HOME
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);
#endif
    int numCows, time;
    cin >> numCows >> time;
    long long start, speed, end;
    multiset<long long> tracks;
    for (int i = 0; i < numCows; i++)
    {
        cin >> start >> speed;
        end = start + speed * time;
        auto iter = tracks.lower_bound(end);
        if (iter != tracks.begin())
            tracks.erase(--iter);
        tracks.insert(end);
    }

    //print
    cout << tracks.size() << endl;
    return 0;
}