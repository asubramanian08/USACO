/*USACO JAN13 Problem 'truth' Analysis by Travis Hance

When we get a line of the form "x y T", we learn that x and y must be of the same type, that is, they are 
either both truth tellers, or both liars. On the other hand, a line of the form "x y L" means that x and y 
are of different type.

Consider a graph where every vertex represents a cow, and for any statement about cows x and y, we put an 
edge between those two cows in the graph to represent the new relation. How can we check that the 
relations are consistent at any point in time? For any connected component of the graph, we need to be 
able to separate it into two subcomponents A and B, where each "T" edge is between two vertices of the 
same subcomponent, and each "L" edge is between two vertices of opposite subcomponents. Then, we could 
make a valid assignment of cows to types by assigning all cows in A to be truth-tellers and all cows in B 
to be liars, or the other way around.

We can check if a given set of relations is consistent by first using flood-fill to find the connected 
components. We can assign the cows in a given component to the two subcomponents as we perform the 
flood-fill. For example, when we examine a vertex x assigned to subcomponent A, all of x's neighbors along 
"T" edges should also be in A, and all x's neighbors along "L" edges should be assigned to B. Then, we just 
have to check that our assignment is consistent along all edges. This process takes O(M) time.

Now, one approach is to add edges one-by-one, and at each step, use the above to check consistency until we 
find the first statement that makes it inconsistent. This solutions take O(M2) time. However, this will 
take slightly too long.

Instead of adding edges one-by-one, we could binary search on the answer. Then we only need to do the 
flood-fill O(log(M)) times, giving an O(M log(M)) algorithm, which is definitely efficient enough for this 
problem. 

Here is a C++ solution implementing the binary search solution: */

#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;
#define NMAX 1005
#define MMAX 10005
// a type of 'true' indicates an 'L' edge, that is, the two
// relevant cows should be of different type
struct edge
{
    int dest;
    bool type;
    int index;
};
vector<edge> edges[NMAX];
int components[NMAX];
bool type[NMAX];
// DFS flood-fill, restricting to edges with indices at most // nstatments
bool dfs(int v, int comp, bool t, int nstatements)
{
    if (components[v] != 0)
    {
        return t == type[v];
    }
    components[v] = comp;
    type[v] = t;
    for (int i = 0; i < edges[v].size(); i++)
    {
        if (edges[v][i].index < nstatements &&
            !dfs(edges[v][i].dest, comp, edges[v][i].type ^ t, nstatements))
        {
            return false;
        }
    }
    return true;
}

// Returns true if the first nstatements statements are consistent
bool consistent(int n, int nstatements)
{
    for (int i = 0; i < n; i++)
    {
        components[i] = 0;
    }
    int nComponents = 0;
    for (int i = 0; i < n; i++)
    {
        if (components[i] == 0)
        {
            nComponents++;
            if (!dfs(i, nComponents, false, nstatements))
            {
                return false;
            }
        }
        return true;
    }
}
int main()
{
    freopen("truth.in", "r", stdin);
    freopen("truth.out", "w", stdout);
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    for (int line = 0; line < m; line++)
    {
        int a, b;
        char c;
        scanf("%d", &a);
        scanf("%d", &b);
        a--;
        b--;
        do
        {
            c = fgetc(stdin);
        } while (c != 'L' && c != 'T');
        edge e;
        e.type = (c == 'L');
        e.index = line;
        e.dest = b;
        edges[a].push_back(e);
        e.dest = a;
        edges[b].push_back(e);
    }
    // binary search
    // invariant: lo <= answer < hi
    int lo = 1, hi = m + 1;
    while (lo + 1 < hi)
    {
        int mid = (lo + hi) / 2;
        if (consistent(n, mid))
        {
            lo = mid;
        }
        else
        {
            hi = mid;
        }
    }
    printf("%d\n", lo);
}