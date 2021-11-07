// Start: 9:20
// Think: 9:35
// Write: 10:02
// Debug: 10:04
#include <iostream>
#include <algorithm>
using namespace std;

using pic = pair<int, char>;
#define MAX_COWS 100000

int main(void)
{
    // read
#ifndef HOME
    freopen("fairphoto.in", "r", stdin);
    freopen("fairphoto.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    pic *cows = new pic[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].first >> cows[i].second;
    sort(cows, cows + numCows);

    // prefixSum: white +1, spotted -1
    int *prefixSum = new int[numCows + 1];
    prefixSum[0] = 0;
    for (int i = 1; i <= numCows; i++)
        prefixSum[i] = prefixSum[i - 1] + (cows[i - 1].second == 'W' ? 1 : -1);

    // rightmost pos (+ MAX_COWS)
    int rightmost[2 * MAX_COWS] = {0};
    for (int i = 1; i <= numCows; i++)
        rightmost[prefixSum[i] + MAX_COWS] = cows[i - 1].first;

    // rightmost -> include color switching
    for (int i = 2 * MAX_COWS - 3; i >= 0; i--)
        rightmost[i] = max(rightmost[i + 2], rightmost[i]);

    // longest picture
    int ans = 0;
    for (int i = 0; i < numCows; i++)
        ans = max(ans, rightmost[prefixSum[i] + MAX_COWS] - cows[i].first);

    // print and delete
    cout << ans << endl;
    delete[] cows;
    delete[] prefixSum;
    return 0;
}