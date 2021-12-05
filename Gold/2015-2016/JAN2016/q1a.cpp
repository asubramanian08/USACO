// Start: 9:22
// Think: 9:45, 10:52-11:20
// Write: 12:07
// Debug: 12:22  -> 1 test case failed
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

#define BIG_NUM 1000000000

int main(void)
{
// read
#ifndef HOME
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);
#endif
    int numBayles;
    cin >> numBayles;
    double *balyes = new double[numBayles];
    for (int i = 0; i < numBayles; i++)
        cin >> balyes[i];
    sort(balyes, balyes + numBayles);

    // left explosion minimum
    double *left = new double[numBayles * 2];
    left[0] = 0;
    for (int i = 1, reachTo = 1; i < numBayles * 2 - 1; i++)
    {
        double pos = balyes[i / 2];
        if (i % 2)
            pos = (pos + balyes[i / 2 + 1]) / 2;
        while (reachTo * 2 < i && left[reachTo * 2] < pos - balyes[reachTo])
            reachTo++;
        left[i] = max(left[(reachTo - 1) * 2] + 1, pos - balyes[reachTo - 1]);
        if (reachTo * 2 < i)
            left[i] = min(left[i], left[reachTo * 2] + 1);
    }

    // right explosion minimum
    double *right = new double[numBayles * 2];
    right[(numBayles - 1) * 2] = 0;
    for (int i = (numBayles - 1) * 2 - 1, reachTo = numBayles - 2; i >= 0; i--)
    {
        double pos = balyes[i / 2];
        if (i % 2)
            pos = (pos + balyes[i / 2 + 1]) / 2;
        while (reachTo * 2 > i && right[reachTo * 2] < balyes[reachTo] - pos)
            reachTo--;
        right[i] = max(right[(reachTo + 1) * 2] + 1, balyes[reachTo + 1] - pos);
        if (reachTo * 2 > i)
            right[i] = min(right[i], right[reachTo * 2] + 1);
    }

    // print and delete
    double ans = BIG_NUM;
    for (int i = 0; i < numBayles * 2 - 1; i++)
        ans = min(ans, max(left[i], right[i]));
    cout << setprecision(1) << fixed;
    cout << ans << endl;
    delete[] balyes;
    delete[] left;
    delete[] right;
    return 0;
}