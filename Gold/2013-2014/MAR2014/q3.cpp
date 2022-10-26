// 10:38 - 11:47 + 6:48 - ?
// Looking at solution: ~30 mins
// Erdos-Gallai Theorem
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
using namespace std;

int n, arr[505];
bool isZeros(vector<int> arr)
{
    for (int x : arr)
        if (x != 0)
            return false;
    return true;
}
bool isValid(int remove)
{
    vector<int> curr;
    for (int i = 0; i <= n; i++)
        if (i != remove)
            curr.push_back(arr[i]);
    sort(curr.begin(), curr.end(), greater<int>());
    int sum = 0, idx = n - 1;
    vector<int> ps(curr.size() + 1);
    ps[0] = curr[0];
    for (int i = 1; i < n; i++)
        ps[i] = curr[i] + ps[i - 1];
    for (int i = 0; i < curr.size(); i++)
    {
        for (idx = max(idx, i); idx > i && curr[idx] < i + 1; idx--)
            ;
        sum += curr[i];
        int right = i * (i + 1);
        right += ps[n - 1] - ps[idx];
        right += (i + 1) * (idx - i);
        if (sum > right)
            return false;
    }
    return sum % 2 == 0;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef HOME
    freopen("fcount.in", "r", stdin);
    freopen("fcount.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i <= n; i++)
        cin >> arr[i];
    vector<int> ans;
    for (int i = 0; i <= n; i++)
        if (isValid(i))
            ans.push_back(i);
    cout << ans.size() << endl;
    for (int x : ans)
        cout << (x + 1) << endl;
    return 0;
}