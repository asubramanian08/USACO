// Doing to stop debug time -> submit once
// Start: 5:14
// Think: 5:18
// Write: 5:30
#include <iostream>
#include <algorithm>
using namespace std;

int main(void)
{
    //read
    int numCows;
    cin >> numCows;
    int *cows = new int[numCows];
    int *stalls = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i];
    for (int i = 0; i < numCows; i++)
        cin >> stalls[i];

    //sort
    sort(cows, cows + numCows);

    //2 Pointers
    int inStalls;
    long long ans = 1;
    for (int cow = numCows - 1; cow >= 0; cow--)
    {
        inStalls = 0;
        for (int i = 0; i < numCows; i++)
            inStalls += cows[cow] <= stalls[i];
        ans *= (long long)inStalls - (long long)(numCows - (cow + 1));
    }

    //print and delete
    cout << ans;
    delete[] cows;
    delete[] stalls;
    return 0;
}