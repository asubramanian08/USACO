// Start: 10:05
// Think: 10:31, 12:16-
// Write: 10:53
// Debug: 11:00 -> 4/11
/**After look at solution (same algo) 1:18-1:21
 * Look at the code below to see the problem */
#include <iostream>
#include <algorithm>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("empty.in", "r", stdin);
    freopen("empty.out", "w", stdout);
#endif
    int numStalls, lines;
    cin >> numStalls >> lines;
    int *prefCount = new int[numStalls];
    fill(prefCount, prefCount + numStalls, 0);
    long long numCows, times, mult, add; //I changed from int to long long
    for (int i = 0; i < lines; i++)
    {
        cin >> numCows >> times >> mult >> add;
        for (int j = 1; j <= times; j++)
            prefCount[(j * mult + add) % numStalls] += numCows;
    }

    //loop through and find the first open
    int left = 0;
    for (int i = 0; i < numStalls; i++)
        if (left || prefCount[i])
        {
            left += prefCount[i] - 1;
            prefCount[i] = 1;
        }
    for (int i = 0; i < numStalls; i++)
        if (left || prefCount[i])
        {
            left += prefCount[i] - 1;
            prefCount[i] = 1;
        }
        else
        {
            cout << i << endl;
            break;
        }
    return 0;
}