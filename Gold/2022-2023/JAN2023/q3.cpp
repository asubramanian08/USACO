// Official: Correct
#include <iostream>
#include <vector>
using namespace std;
#define MOD 1000000007

long long fact[10000000];
long long pow(long long b, long long e)
{
    if (e == 0)
        return 1;
    long long half = pow(b, e / 2), ans = (half * half) % MOD;
    return (ans * (e % 2 ? b : 1)) % MOD;
}
long long choose(long long n, long long i) { return ((fact[n] * pow(fact[i], MOD - 2)) % MOD * pow(fact[n - i], MOD - 2)) % MOD; }

int main(void)
{
    fact[0] = 1;
    for (int i = 1; i < 10000000; i++)
        fact[i] = (fact[i - 1] * i) % MOD;
    ios_base::sync_with_stdio(false);
    int n, x;
    cin >> n;
    vector<int> v = {2};
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        v.push_back(x);
    }
    v.push_back(0);
    long long ans = 1;
    for (int i = 1; i <= n; i++)
    {
        int left = (v[i] - 2) / 2, leftBack = max(v[i] - v[i - 1], 0) / 2;
        long long leftOptions = choose(left, leftBack);
        int right = v[i] / 2, rightBack = max(v[i] - v[i + 1], 0) / 2;
        long long rightOptions = choose(right, rightBack);
        ans = (ans * leftOptions) % MOD;
        ans = (ans * rightOptions) % MOD;
    }
    cout << ans << endl;
    return 0;
}