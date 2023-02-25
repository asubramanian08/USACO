// 11:40 - 12:24
#include <iostream>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;
#define N 100010

// BIT tree
class BIT
{
private:
    int *bTree;
    int elements;

public:
    BIT(int elem);
    BIT(int elem, int *initialize, int numInit);
    ~BIT() { delete[] bTree; }
    int query(int node);
    void updt(int node, int cng);
};
BIT::BIT(int elem)
{
    elements = elem;
    bTree = new int[elem + 1];
    for (int i = 1; i <= elem; i++)
        bTree[i] = 0;
}
BIT::BIT(int elem, int *initialize, int numInit)
{
    elements = elem;
    bTree = new int[elem + 1];
    for (int i = 1; i <= elem; i++)
        bTree[i] = 0;
    for (int i = 0; i < numInit; i++)
        updt(i, initialize[i]);
}
int BIT::query(int node)
{
    if (node == -1)
        return 0;
    int sum = 0;
    for (int i = node + 1; i > 0; i -= (i & -i))
        sum += bTree[i];
    return sum;
}
void BIT::updt(int node, int cng)
{
    for (int i = node + 1; i <= elements; i += (i & -i))
        bTree[i] += cng;
}

int main(void)
{
#ifndef HOME
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);
#endif
    int n, ans = 0;
    pii arr[N];
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        arr[i].second = i;
        cin >> arr[i].first;
    }
    sort(arr, arr + n, greater<pii>());
    BIT bit(n);
    for (int i = 0; i < n; i++)
    {
        int left = bit.query(arr[i].second);
        int right = i - left;
        ans += max(left, right) > 2 * min(left, right);
        bit.updt(arr[i].second, 1);
    }
    cout << ans << endl;
    return 0;
}