// Start: 9:32
// Think: 10:31
// Write: 10:54
// Debug: 11:19
#include <iostream>
using namespace std;

#define RANGE 2000010
#define HALF_RANGE 1000000

int main(void)
{
    //read
#ifndef HOME
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
#endif
    int arrLen, numQueries;
    cin >> arrLen >> numQueries;
    int *array = new int[arrLen];
    for (int i = 0; i < arrLen; i++)
        cin >> array[i];

    //find number of things somthing works with
    long long **ans = new long long *[arrLen];
    int *on = new int[RANGE];
    for (int i = 0; i < RANGE; i++)
        on[i] = 0;
    for (int i = 0; i < arrLen; i++)
    {
        ans[i] = new long long[arrLen];
        for (int j = 0; j <= i; j++)
            ans[i][j] = 0;
        for (int j = i + 1; j < arrLen; j++)
        {
            if (HALF_RANGE - (array[i] + array[j]) >= 0 && HALF_RANGE - (array[i] + array[j]) < RANGE)
                ans[i][j] = on[HALF_RANGE - (array[i] + array[j])];
            on[HALF_RANGE + array[j]]++;
        }
        for (int j = i + 1; j < arrLen; j++)
            on[HALF_RANGE + array[j]]--;
    }

    //find the answer to every set
    for (int i = arrLen - 1; i >= 0; i--)
        for (int j = i + 1; j < arrLen; j++)
            ans[i][j] += ans[i][j - 1] + ans[i + 1][j] - ans[i + 1][j - 1];

    //answer the queries
    int p1, p2;
    for (int i = 0; i < numQueries; i++)
    {
        cin >> p1 >> p2;
        p1--, p2--;
        cout << ans[p1][p2] << endl;
    }
    return 0;
}