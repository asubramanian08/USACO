// Also in AlphaStar-PlatinumA week 4 q3
// Start: 11:00
// Think: 11:21,
// Write:
// Debug: (geometry problem)

/* MY thoughts on the problem before looking at sol
 * Can find where the tangent is, with radius and dist to center
 * Might sort by angle to the circle or the tangent
 * Find the 2 ranges and find what isn't there */

// After looking at sol: 9:17-11:17 (storing what is wrapped problems)
#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;

#define NA -1
double fixRange(double val)
{
    if (val < 0)
        val += 2 * M_PI;
    if (val >= 2 * M_PI)
        val -= 2 * M_PI;
    return val;
}

int main(void)
{
    // read
#ifndef HOME
    freopen("sight.in", "r", stdin);
    freopen("sight.out", "w", stdout);
#endif
    int numCows, radius;
    cin >> numCows >> radius;
    pair<double, double> *view = new pair<double, double>[numCows];
    int x, y;
    double alpha, delta, firstInt;
    for (int i = 0; i < numCows; i++)
    {
        cin >> x >> y;
        alpha = fixRange(atan2(y, x));
        delta = fixRange(acos(radius / sqrt((double)x * x + (double)y * y)));
        view[i] = make_pair(fixRange(alpha - delta), fixRange(alpha + delta));
    }

    // make the evenetpoints + set
    int *events = new int[numCows * 2];
    for (int i = 0; i < numCows * 2; i++)
        events[i] = i;
    sort(events, events + numCows * 2, [numCows, &view](int e1, int e2)
         {
             double pos1 = e1 < numCows ? view[e1].first : view[e1 - numCows].second;
             double pos2 = e2 < numCows ? view[e2].first : view[e2 - numCows].second;
             return pos1 < pos2; });
    set<int> on;

    // run though, fake then real
    int ans = 0;
    for (int run = 0; run < 2; run++) // first to make sure back things are on
        for (int i = 0; i < numCows * 2; i++)
        {
            if (events[i] < numCows && run == 1)
                ans += on.size();
            if (events[i] < numCows)
                on.insert(events[i]);
            else if (on.find(events[i] - numCows) != on.end())
                on.erase(events[i] - numCows);
        }

    // print and delete
    cout << ans << endl;
    delete[] view;
    delete[] events;
    return 0;
}