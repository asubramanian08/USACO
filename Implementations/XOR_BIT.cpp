class XOR_BIT
{
private:
    int *bTree;
    int elements;

public:
    XOR_BIT(int elem);
    ~XOR_BIT() { delete[] bTree; }
    int query(int node);
    void updt(int node, int cng);
};
XOR_BIT::XOR_BIT(int elem)
{
    elements = elem;
    bTree = new int[elem + 1];
    for (int i = 1; i <= elem; i++)
        bTree[i] = 0;
}
int XOR_BIT::query(int node)
{
    if (node == -1)
        return 0;
    int ans = 0;
    for (int i = node + 1; i > 0; i -= (i & -i))
        ans ^= bTree[i];
    return ans;
}
void XOR_BIT::updt(int node, int cng)
{
    for (int i = node + 1; i <= elements; i += (i & -i))
        bTree[i] ^= cng;
}