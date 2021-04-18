// Start: 9:34
// Think: 9:55, 11:54-12:41?
// Write: xxx
// Debug: xxx
//after looking at solution: 2:40-2:57
#include <iostream>
using namespace std;

#define MAX_BSIZE 700
#define MAX_HSIZE 100
bool works[2][MAX_BSIZE + MAX_HSIZE][MAX_BSIZE + MAX_HSIZE]; //** DP state **

int main(void)
{
    //read
#ifndef HOME
    freopen("baleshare.in", "r", stdin);
    freopen("baleshare.out", "w", stdout);
#endif
    int numBayles;
    cin >> numBayles;
    int *bayles = new int[numBayles];
    for (int i = 0; i < numBayles; i++)
        cin >> bayles[i];

    //set up the DP works
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < MAX_BSIZE; j++)
            for (int k = 0; k < MAX_BSIZE; k++)
                works[i][j][k] = false;

    //*** go and set the DP ***
    works[0][0][0] = true;
    for (int i = 0; i < numBayles; i++)
    {
        for (int j = 0; j < MAX_BSIZE; j++)
            for (int k = 0; k < MAX_BSIZE; k++)
            {
                if (!works[i % 2][j][k])
                    continue;
                //place this bayle at ...
                works[(i + 1) % 2][j][k] = true;             // barn1
                works[(i + 1) % 2][j + bayles[i]][k] = true; // barn2
                works[(i + 1) % 2][j][k + bayles[i]] = true; // barn3
            }
    }

    //find the total bayles
    int totalBayles = 0;
    for (int i = 0; i < numBayles; i++)
        totalBayles += bayles[i];

    //find the best
    int minBarn = MAX_BSIZE * 3;
    for (int i = 0; i < MAX_BSIZE; i++)
        for (int j = 0; j < MAX_BSIZE; j++)
            if (works[numBayles % 2][i][j])
                minBarn = min(minBarn, max(max(i, j), totalBayles - i - j));

    //print and delete
    cout << minBarn;
    delete[] bayles;
    return 0;
}