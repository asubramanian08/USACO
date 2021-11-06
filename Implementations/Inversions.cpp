// From AlphaStar-PlatinumA week 9

// inversions
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
long long inversions(int *arr, int len)
{
    using pii = pair<int, int>;
    pii *order = new pii[len];
    for (int i = 0; i < len; i++)
        order[i] = pii(arr[i], i);
    sort(order, order + len);
    BIT bit(len);
    long long ans = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        ans += bit.query(order[i].second);
        bit.updt(order[i].second, 1);
    }
    return ans;
}