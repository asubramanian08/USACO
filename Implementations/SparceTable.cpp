// star league Part 2 week 7 q1
// both min and max in range
#include <utility>
#include <cmath>
#include <iostream>
using namespace std;

#define rangeMin(start, end, log) min(st[start][log].first, st[end - (1 << log) + 1][log].first)
#define rangeMax(start, end, log) max(st[start][log].second, st[end - (1 << log) + 1][log].second)
#define rangeDif(start, end, log) (rangeMax(start, end, log) - rangeMin(start, end, log))
#define queryLog(start, end) log2(end - start + 1)

using pii = pair<int, int>;

int main(void)
{
    // start ST
    int numCows;
    pii **st = new pii *[numCows];
    int log = log2(numCows) + 1;
    for (int i = 0; i < numCows; i++)
    {
        st[i] = new pii[log];
        cin >> st[i][0].first;
        st[i][0].second = st[i][0].first;
    }

    // fix ST
    for (int j = 1; j < log; j++)
        for (int i = 0; i + (1 << j) <= numCows; i++)
        {
            st[i][j].first = min(st[i][j - 1].first, st[i + (1 << (j - 1))][j - 1].first);
            st[i][j].second = max(st[i][j - 1].second, st[i + (1 << (j - 1))][j - 1].second);
        }
}