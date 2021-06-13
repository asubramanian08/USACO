//Almost a copy of the USACO 2012 open gold problem 3 solution
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int numCows;
typedef pair<int, int> pr;
vector<int> set[2];
vector<pr> sums[2];
void findSums(int size, bool setNum)
{
    int sum;
    for (int i = 0; i < 1 << size; i++)
    {
        for (int j = i; j; j = (j - 1) & i)
        {
            sum = 0;
            for (int k = 0; k < size; k++)
            {
                if (j & (1 << k))
                    sum += set[setNum][k];
                else if (i & (1 << k))
                    sum -= set[setNum][k];
            }
            if (sum >= 0)
                sums[setNum].push_back(pr(sum, i));
            if (j == 0)
                break;
        }
    }
    sort(sums[setNum].begin(), sums[setNum].end());
    sums[setNum].resize(unique(sums[setNum].begin(), sums[setNum].end()) - sums[setNum].begin());
}
int main(void)
{
    // FILE *junk;
    // junk = freopen("subsets.in", "r", stdin);
    // junk = freopen("subsets.out", "w", stdout);
    cin >> numCows;
    int val;
    for (int i = 0; i < numCows; i++)
    {
        cin >> val;
        set[i % 2].push_back(val);
    }
    findSums(set[0].size(), false);
    findSums(set[1].size(), true);

    bool *works = new bool[1 << numCows];
    memset(works, 0, sizeof(bool) * (1 << numCows));
    int setPlace[2];
    setPlace[0] = setPlace[1] = 0;
    while ((setPlace[0] < sums[0].size()) && (setPlace[1] < sums[1].size()))
    {
        if (sums[0][setPlace[0]].first < sums[1][setPlace[1]].first)
            setPlace[0]++;
        else if (sums[0][setPlace[0]].first > sums[1][setPlace[1]].first)
            setPlace[1]++;
        else
        {
            int place0 = setPlace[0];
            while ((place0 < sums[0].size()) && (sums[0][place0].first == sums[0][setPlace[0]].first))
                place0++;
            int place1 = setPlace[1];
            while ((place1 < sums[1].size()) && (sums[1][place1].first == sums[1][setPlace[1]].first))
                place1++;
            for (int i = setPlace[0]; i < place0; i++)
                for (int j = setPlace[1]; j < place1; j++)
                    works[sums[0][i].second | (sums[1][j].second << set[0].size())] = true;
            setPlace[0] = place0;
            setPlace[1] = place1;
        }
    }
    int ans = 0;
    for (int i = 1; i < 1 << numCows; i++)
        ans += works[i];
    cout << ans;
    return 0;
}
