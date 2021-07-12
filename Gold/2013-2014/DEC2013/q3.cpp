// Start: 10:30
// Think: 11:37,
// Write: NA
// Debug: NA
// After looking at sol: NA
#include <iostream>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("shufflegold.in", "r", stdin);
    freopen("shufflegold.out", "w", stdout);
#endif
    int numNodes, shuffleSize, numQueries;
    cin >> numNodes >> shuffleSize >> numQueries;
    int *shuffle = new int[shuffleSize];
    for (int i = 0; i < shuffleSize; i++)
    {
        cin >> shuffle[i];
        shuffle[i] -= 2;
        //make loop around
    }

    return 0;
}