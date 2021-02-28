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
    void updt(int node, int val);
};
BIT::BIT(int elem)
{
    elements = elem;
    bTree = new int[elem];
}
BIT::BIT(int elem, int *initialize, int numInit)
{
    elements = elem;
    bTree = new int[elem];
    for (int i = 0; i < numInit; i++)
        updt(i, initialize[i]);
}
int BIT::query(int node)
{
    int sum = 0;
    for (int i = node - 1; i >= 0; i -= (i & -i))
        sum += bTree[i];
    return sum;
}
void BIT::updt(int node, int val)
{
    for (int i = node - 1; i < elements; i += (i & -i))
        bTree[i] += val;
}