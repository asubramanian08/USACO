// Doing to stop debug time -> submit once
// Start: 4:55
// Think: 5:03
// Write: 5:14 -> 6/10
//look at afterward 8:10-8:12 -> forgot if statement
#include <iostream>
using namespace std;

int main(void)
{
    //read
    int numCows, odds = 0, evens = 0, num;
    cin >> numCows;
    for (int i = 0; i < numCows; i++)
    {
        cin >> num;
        if (num % 2 == 0)
            evens++;
        else
            odds++;
    }

    //fix evens
    while (odds > evens)
        evens++, odds -= 2;
    evens = min(evens, odds + 1);
    int ans = odds + evens;

    //print
    cout << ans;
    return 0;
}