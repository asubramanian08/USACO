using namespace std;

int *bTree;
int elements;
void initNoArr(int elem)
{
    elements = elem;
    bTree = new int[elem];
}
void initArr(int elem, int *initialize, int numInit)
{
    elements = elem;
    bTree = new int[elem];
    for (int i = 0; i < numInit; i++)
        updt(i, initialize[i]);
}
int query(int node)
{
    int sum = 0;
    for (int i = node - 1; i >= 0; i -= (i & -i))
        sum += bTree[i];
    return sum;
}
void updt(int node, int val)
{
    for (int i = node - 1; i < elements; i += (i & -i))
        bTree[i] += val;
}