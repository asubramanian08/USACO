#include <stdlib.h>

unsigned int *id, *sz;
void init(unsigned int N)
{
    id = (unsigned int *)malloc(sizeof(unsigned int) * N);
    sz = (unsigned int *)malloc(sizeof(unsigned int) * N);
    for (unsigned int i = 0; i < N; i++)
    {
        id[i] = i;
        sz[i] = 1;
    }
}
//find its first parent
unsigned int root(unsigned int i)
{
    while (i != id[i])
    {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}
bool is_connected(unsigned int p, unsigned int q) { return root(p) == root(q); }
void connect(unsigned int p, unsigned int q)
{
    unsigned int i = root(p), j = root(q);
    if (i == j)
        return;
    if (sz[i] < sz[j])
    {
        id[i] = j;
        sz[j] += sz[i];
    }
    else
    {
        id[j] = i;
        sz[i] += sz[j];
    }
}