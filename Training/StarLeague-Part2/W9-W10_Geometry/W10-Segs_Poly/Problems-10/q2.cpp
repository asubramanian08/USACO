#include <iostream>
#include <cmath>
using namespace std;

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("quad.in", "r", stdin);
    junk = freopen("quad.out", "w", stdout);
    int woodLen;
    cin >> woodLen;

    //calculate and print
    int totalWays = 0, minLen, remWood;
    //loops through the first two cuts
    for (int c1 = 1; c1 < woodLen; c1++)
        for (int c2 = c1 + 1; c2 < woodLen; c2++)
        {
            remWood = woodLen - c2;
            //min restriction
            if (remWood < 2)
                continue; //not enough for cut 3
            if (remWood <= abs((c2 - c1) - c1))
                continue; //can't reach back
            //max restriction
            if (remWood > c2)
                minLen = (remWood - c2) / 2;
            else
                minLen = 0;
            minLen++;
            totalWays += (woodLen - minLen) - (c2 + minLen) + 1;
        }
    cout << totalWays;
    return 0;
}