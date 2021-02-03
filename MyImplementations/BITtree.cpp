#include <stdlib.h>

unsigned int *bTree;
unsigned int elements;
void initNoArr(unsigned int elem)
{
    elements = elem;
    bTree = (unsigned int *)malloc(sizeof(unsigned int) * elem);
}
void initArr(unsigned int elem, unsigned int *initialize, unsigned int numInit)
{
    elements = elem;
    bTree = (unsigned int *)malloc(sizeof(unsigned int) * elem);
    for (unsigned int i = 0; i < numInit; i++)
        updt(i, initialize[i]);
}
unsigned int query(unsigned int node)
{
    unsigned int sum = 0;
    for (unsigned int i = node - 1; i >= 0; i -= (i & -i))
        sum += bTree[i];
    return sum;
}
void updt(unsigned int node, unsigned int val)
{
    for (unsigned int i = node - 1; i < elements; i += (i & -i))
        bTree[i] += val;
}