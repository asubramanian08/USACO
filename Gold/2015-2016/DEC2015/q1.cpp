// Start: 9:34
// Think: 10:16
// Write: 10:38
// Debug: 10:44
#include <iostream>
#include <algorithm>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);
#endif
    int numRounds, half;
    cin >> numRounds;
    half = numRounds / 2;
    int *order = new int[numRounds];
    for (int i = 0; i < numRounds; i++)
    {
        cin >> order[i];
        order[i]--;
    }

    //prep
    sort(order, order + half);
    sort(order + half, order + numRounds);
    bool *is_bessie = new bool[numRounds * 2];
    fill(is_bessie, is_bessie + numRounds * 2, true);
    for (int i = 0; i < numRounds; i++)
        is_bessie[order[i]] = false;
    int *bCards = new int[numRounds];
    int bPlace = 0;
    for (int i = 0; i < numRounds * 2; i++)
        if (is_bessie[i])
            bCards[bPlace++] = i;

    //do the lower side
    bPlace = 0;
    for (int currPos = lower_bound(order + half, order + numRounds, bCards[0]) - order;
         currPos < numRounds; currPos++)
        bPlace += bCards[bPlace] < order[currPos];

    //do the upper side
    int oPlace = 0;
    for (int i = bPlace; i < numRounds && oPlace < half; i++)
        oPlace += bCards[i] > order[oPlace];

    //print and delete
    cout << bPlace + oPlace << endl;
    delete[] order;
    delete[] is_bessie;
    delete[] bCards;
    return 0;
}