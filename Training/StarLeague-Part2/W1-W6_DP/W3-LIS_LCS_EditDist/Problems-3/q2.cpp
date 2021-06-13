#include <iostream>
#include <vector>
using namespace std;

struct cow
{
    int wt;
    int iq;
};
int compareIQ(const void *p1, const void *p2)
{
    int retVal = ((cow *)p2)->iq - ((cow *)p1)->iq;
    if (retVal == 0)
        retVal = ((cow *)p2)->wt - ((cow *)p1)->wt;
    return retVal;
}
vector<int> solArr;
int bSearch(int wt)
{
    int high = solArr.size(), low = 0;
    if (solArr[low] >= wt)
        return low;
    while (high - low > 1)
    {
        if (solArr[(high + low) / 2] < wt)
            low = (high + low) / 2;
        else
            high = (high + low) / 2;
    }
    return high;
}
int main(void)
{
    //FILE *junk;
    //junk = freopen("smarter.in", "r", stdin);
    //junk = freopen("smarter.out", "w", stdout);
    int numCows;
    cin >> numCows;
    cow *cows = new cow[numCows];
    for (int i = 0; i < numCows; i++)
    {
        cin >> cows[i].wt;
        cin >> cows[i].iq;
    }
    qsort(cows, numCows, sizeof(cow), compareIQ);
    int bestPlace;
    solArr.push_back(cows[0].wt);
    for (int i = 1; i < numCows; i++)
    {
        bestPlace = bSearch(cows[i].wt);
        if (bestPlace == solArr.size())
            solArr.push_back(cows[i].wt);
        else
            solArr[bestPlace] = cows[i].wt;
    }
    cout << solArr.size();
    return 0;
}