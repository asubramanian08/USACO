#include <iostream>
#include <vector>
using namespace std;
struct cow
{
    unsigned long long start;
    unsigned long long end;
};
vector<unsigned long long> solArr;
int bSearch(unsigned long long currEnd)
{
    int high = solArr.size(), low = 0;
    if (solArr[low] < currEnd)
        return low;
    while (high - low > 1)
    {
        if (solArr[(high + low) / 2] < currEnd)
            high = (high + low) / 2;
        else
            low = (high + low) / 2;
    }
    return high;
}
int main(void)
{
    FILE *junk;
    junk = freopen("cowjog.in", "r", stdin);
    junk = freopen("cowjog.out", "w", stdout);
    int numCows;
    unsigned long long time;
    cin >> numCows >> time;
    cow *cows = new cow[numCows];
    for (int i = 0; i < numCows; i++)
    {
        cin >> cows[i].start;
        cin >> cows[i].end; //speed
        cows[i].end = cows[i].start + (cows[i].end * time);
    }
    int bestPlace;
    solArr.push_back(cows[0].end);
    for (int i = 1; i < numCows; i++)
    {
        bestPlace = bSearch(cows[i].end);
        if (bestPlace == solArr.size())
            solArr.push_back(cows[i].end);
        else
            solArr[bestPlace] = cows[i].end;
    }
    cout << solArr.size();
    return 0;
}