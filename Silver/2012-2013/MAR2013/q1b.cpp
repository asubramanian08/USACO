// 6:08 - 6:28 - 6:43
#include <iostream>
using namespace std;

int main(void)
{
#ifndef HOME
    freopen("poker.in", "r", stdin);
    freopen("poker.out", "w", stdout);
#endif
    long long n, ans = 0, curr = 0, x;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        if (x > curr)
            ans += x - curr;
        curr = x;
    }
    cout << ans << endl;
}