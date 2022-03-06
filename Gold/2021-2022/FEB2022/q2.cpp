#include <iostream>
#include <cmath>
using namespace std;

int main(void)
{
    long long cases, tests;
    cin >> cases >> tests;
    if (cases == 1)
    {
        cout << 1.0 << endl;
        return 0;
    }
    long double ans = 0, curr;
    long double *ps = new long double[cases + 1];
    ps[0] = 1;
    for (long long i = 1; i <= cases; i++)
        ps[i] = (ps[i - 1] * cases) / i;
    for (long long i = 0; i <= cases; i++)
        ps[i] *= i;
    for (long long i = 0; i <= cases; i++)
        for (long long j = 1; j < cases; j++)
            ps[i] /= 2;
    for (long long i = 1; i <= cases; i++)
        ps[i] += ps[i - 1];
    for (long long i = 0; i < tests; i++, ans = curr)
    {
        curr = ps[cases] - ps[(long long)(floor(ans))];
        curr += 0;
    }
    cout << ans << endl;
    delete[] ps;
    return 0;
}