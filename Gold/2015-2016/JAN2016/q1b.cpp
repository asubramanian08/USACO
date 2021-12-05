// After looking at sol
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

#define BIG_NUM 1000000000

int main(void)
{
    // read
    //#ifndef HOME
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);
    //#endif
    int numBales;
    cin >> numBales;
    int *bales = new int[numBales];
    for (int i = 0; i < numBales; i++)
        cin >> bales[i];
    sort(bales, bales + numBales);

    // left explosion minimum
    int *left = new int[numBales];
    left[0] = 0;
    for (int i = 1, reachTo = 1; i < numBales; i++)
    {
        while (reachTo < i && left[reachTo] < bales[i] - bales[reachTo])
            reachTo++;
        left[i] = max(left[reachTo - 1] + 1, bales[i] - bales[reachTo - 1]);
        if (reachTo < i)
            left[i] = min(left[i], left[reachTo] + 1);
    }

    // right explosion minimum
    int *right = new int[numBales];
    right[numBales - 1] = 0;
    for (int i = numBales - 2, reachTo = numBales - 2; i >= 0; i--)
    {
        while (reachTo > i && right[reachTo] < bales[reachTo] - bales[i])
            reachTo--;
        right[i] = max(right[reachTo + 1] + 1, bales[reachTo + 1] - bales[i]);
        if (reachTo > i)
            right[i] = min(right[i], right[reachTo] + 1);
    }

    // print and delete
    double ans = BIG_NUM;
    int start = 0, end = numBales - 1;
    while (start < end)
    {
        ans = min(ans, max((bales[end] - bales[start]) / 2.0, max(left[start], right[end]) + 1.0));
        left[start + 1] < right[end - 1] ? start++ : end--;
    }
    cout << setprecision(1) << fixed;
    cout << ans << endl;
    delete[] bales;
    delete[] left;
    delete[] right;
    return 0;
}