// Start: 9:55
// Think: 10:21, 11:45-11:53
// Write: 10:28, 11:38-11:45?
// Debug:  xxx
//after looking at solution: 3:33-3:45
#include <iostream>
#include <queue>
using namespace std;

typedef pair<int, int> cow;
class cmpDown
{
public:
    bool operator()(cow &c1, cow &c2)
    {
        return c1.second > c2.second; //for priority_queue
    }
};

int main(void)
{
    //read
#ifndef HOME
    freopen("climb.in", "r", stdin);
    freopen("climb.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    cow *cows = new cow[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].first >> cows[i].second;

    //sort and get ordering (greedy)
    auto greedy_cmp = [](cow &c1, cow &c2) {
        //shorter up than down
        bool type1 = c1.first < c2.second;
        bool type2 = c2.first < c2.second;
        //determine result
        if (type1 != type2)
            return type1;
        if (type1)
            return c1.first < c2.first;
        return c1.second > c2.second;
    };
    sort(&cows[0], &cows[numCows], greedy_cmp);

    //find time
    int *upCost = new int[numCows];
    for (int i = 0; i < numCows; i++)
        upCost[i] = (i > 0 ? upCost[i - 1] : 0) + cows[i].first;
    int *downCost = new int[numCows];
    for (int i = 0; i < numCows; i++)
        downCost[i] = max((i > 0 ? downCost[i - 1] : 0), upCost[i]) + cows[i].second;

    //print and delete
    cout << downCost[numCows - 1];
    delete[] cows;
    delete[] upCost;
    delete[] downCost;
    return 0;
}