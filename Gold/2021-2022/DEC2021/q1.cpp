#include <iostream>
using namespace std;

#define MAX_COWS 100010
int myMax(int n1, int n2)
{
    return n1 > n2 ? n1 : n2;
}
int myMin(int n1, int n2)
{
    return n1 < n2 ? n1 : n2;
}
#define SMALL_NUM -1000000000
#define BIG_NUM 1000000000

int main(void)
{
    // read
    int type, numCows, dist;
    cin >> type >> numCows >> dist;
    auto oper = type == 2 ? myMin : myMax;
    using pii = pair<int, int>;
    pii *cows = new pii[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].first >> cows[i].second;
    int totalWt = 0;
    for (int i = 0; i < numCows; i++)
        totalWt += cows[i].second;

    // DP[i][j]: weight of paired cows at cows i with jump j
    int DP[MAX_COWS][3] = {0};
    auto best = [&DP, &oper](int pos)
    {
        if (pos < 0)
            return 0;
        return oper(oper(DP[pos][0], DP[pos][1]), DP[pos][2]);
    };
    for (int i = 0; i < numCows; i++)
    {
        if (i == 0)
            DP[i][0] = 0;
        else if (cows[i].first - cows[i - 1].first > dist)
            DP[i][0] = best(i - 1);
        else if (i >= 3 && cows[i].first - cows[i - 2].first > dist)
            DP[i][0] = oper(DP[i - 1][1], DP[i - 1][2]);
        else if (i >= 3 && cows[i].first - cows[i - 3].first > dist)
            DP[i][0] = DP[i - 1][1];
        else
            DP[i][0] = (type == 2 ? BIG_NUM : SMALL_NUM);

        DP[i][1] = DP[i][2] = (type == 2 ? BIG_NUM : SMALL_NUM);
        if (i > 0 && cows[i].first - cows[i - 1].first <= dist)
            DP[i][1] = cows[i].second + cows[i - 1].second + best(i - 2);
        if (i > 1 && cows[i].first - cows[i - 2].first <= dist)
        {
            DP[i][2] = cows[i].second + cows[i - 2].second;
            if (DP[i - 1][2] == (type == 2 ? BIG_NUM : SMALL_NUM))
                DP[i][2] += best(i - 3);
            else
                DP[i][2] += cows[i - 1].second + cows[i - 3].second + best(i - 4);
        }
    }

    // print and delete
    int bestAnswer = totalWt - best(numCows - 1);
    cout << bestAnswer << endl;
    delete[] cows;
    return 0;
}