// Start: 9:11
// Think: 9:22, 9:45
// Write: 9:28, 10:00
// Debug: 9:35 3/10, 10:02
#include <iostream>
#include <algorithm>
using namespace std;

using pii = pair<int, int>;
#define MAX_TALENT 250010
int optimal[MAX_TALENT];
int qualifying[MAX_TALENT];
#define BIG_NUM 1000000000

int main(void)
{
    //read
#ifndef HOME
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);
#endif
    int numCows, minWeight;
    cin >> numCows >> minWeight;
    pii *cows = new pii[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].first >> cows[i].second;

    //set up
    for (int i = 0; i < MAX_TALENT; i++)
        optimal[i] = qualifying[i] = BIG_NUM;
    optimal[0] = 0;

    //for each cow
    for (int i = 0; i < numCows; i++)
        for (int j = MAX_TALENT - 1; j >= 0; j--)
        {
            if (optimal[j] == BIG_NUM)
                continue;
            optimal[j + cows[i].second] = min(optimal[j + cows[i].second], optimal[j] + cows[i].first);
            if (optimal[j] + cows[i].first >= minWeight)
                qualifying[j + cows[i].second] = min(qualifying[j + cows[i].second], optimal[j] + cows[i].first);
        }

    //best ans
    double bestTalent = 0, bestWeight = 1;
    for (int i = 0; i < MAX_TALENT; i++)
        if ((double)i / (double)qualifying[i] > bestTalent / bestWeight)
        {
            bestTalent = i;
            bestWeight = qualifying[i];
        }
    int ans = 1000 * (bestTalent / bestWeight);

    //print and delete
    cout << ans << endl;
    delete[] cows;
    return 0;
}