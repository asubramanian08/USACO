// 12:11 - 12:13 - 12:19
#include <iostream>
using namespace std;

int main(void)
{
#ifndef HOME
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);
#endif
    long long n, t, start, speed;
    cin >> n >> t;
    long long endPos[100010];
    for (int i = 0; i < n; i++)
    {
        cin >> start >> speed;
        endPos[i] = start + t * speed;
    }
    long long ans = 1, currEnd = endPos[n - 1];
    for (int i = n - 2; i >= 0; i--)
        if (endPos[i] < currEnd)
            ans++, currEnd = endPos[i];
    cout << ans << endl;
}