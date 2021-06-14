//star league Part 2 week 7 q1
#include <iostream>
#include <utility>
#include <algorithm>
int main(void)
{
    int log, numCows; //these values will already be here
    pair<int, int> st[100][100];
    for (int j = 1; j < log; j++)
        for (int i = 0; i + (1 << j) <= numCows; i++)
        {
            st[i][j].first = min(st[i][j - 1].first, st[i + (1 << (j - 1))][j - 1].first);
            st[i][j].second = max(st[i][j - 1].second, st[i + (1 << (j - 1))][j - 1].second);
        }
}