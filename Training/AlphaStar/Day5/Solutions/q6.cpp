/* Solution  (USACO 2019 December Contest, Gold) (Analysis by Benjamin Qi)

We can answer the queries offline (meaning that we process them in an order that is convenient for us, not 
that which is given by the input). Like the silver version, run a DFS from farm 1. Suppose that we're 
currently processing the farm 𝑥. Store a stack 𝑜𝑟𝑑 containing all the nodes on the path from 1 to 𝑥, and 
also a stack 𝑠𝑡𝑜𝑟[𝑡] for each type 𝑡 containing the pairs (𝑦,𝑑𝑒𝑝𝑡ℎ[𝑦]) for all farms 𝑦 with type 𝑡 on the path 
from 1 to 𝑥. 

Suppose that we want to update the answer for a query 𝑖 having an endpoint 𝐴𝑖=𝑥 (the reasoning for 𝐵𝑖=𝑥 is 
similar). We need to check whether the last farm 𝑦 in the stack corresponding to 𝐶𝑖 actually lies on the 
path from 𝐴𝑖 to 𝐵𝑖. Let 𝐿 be the least common ancestor of 𝐴𝑖 and 𝐵𝑖. First, we can check whether 𝑦 is an 
ancestor of 𝐵𝑖 in 𝑂(1) using the preorder and postorder traversals of the tree. If not, then 𝑦 lies on the 
path between 𝐴𝑖 and 𝐿𝑖, so the answer to this query must be 1. If yes, then it's still possible for 𝑦 to 
lie on the path from 𝐴𝑖 to 𝐵𝑖 if 𝑦=𝐿𝑖.

One option is to actually find 𝐿𝑖 and compare it to 𝑦, but this is unnecessary. Instead, if 𝑦≠𝐴𝑖 then 
consider the farm 𝑌=𝑜𝑟𝑑[𝑑𝑒𝑝𝑡ℎ[𝑦]+1]. If 𝑌 is an ancestor of 𝐵𝑖, then 𝑦 is clearly not the LCA. Otherwise, 𝐴𝑖 
and 𝐵𝑖 lie in different child subtrees of 𝑦, implying that 𝑦 is the LCA.

Thus, this problem is solvable in 𝑂(𝑁+𝑀) time. */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vpi;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto &a : x)

#define mp make_pair
#define pb push_back
#define f first
#define s second

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rsz resize

const int MX = 100005;

void setIO(string name)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}

int N, M, T[MX], C[MX];
bool ok[MX];
vi adj[MX];
array<int, 2> dat[MX];
vi todo[MX];
pi range[MX];

int co = 0;
void dfs(int x, int y)
{
    range[x].f = co++;
    trav(t, adj[x]) if (t != y) dfs(t, x);
    range[x].s = co - 1;
}

vpi stor[MX];
vi ord;

bool anc(int a, int b)
{
    return range[a].f <= range[b].f && range[b].s <= range[a].s;
}

void dfs2(int x, int y)
{
    stor[T[x]].pb({x, sz(ord)});
    ord.pb(x);
    trav(t, todo[x]) if (sz(stor[C[t]]))
    {
        pi y = stor[C[t]].back();
        if (y.f == x)
            ok[t] = 1;
        else
        {
            int Y = ord[y.s + 1];
            // x is one of endpoints for query t
            assert(dat[t][0] == x || dat[t][1] == x);
            if (!anc(Y, dat[t][0] + dat[t][1] - x))
                ok[t] = 1;
        }
    }
    trav(t, adj[x]) if (t != y) dfs2(t, x);
    stor[T[x]].pop_back();
    ord.pop_back();
}

int main()
{
    setIO("milkvisits");
    cin >> N >> M;
    FOR(i, 1, N + 1)
    cin >> T[i];
    F0R(i, N - 1)
    {
        int A, B;
        cin >> A >> B;
        adj[A].pb(B), adj[B].pb(A);
    }
    dfs(1, 0);
    F0R(i, M)
    {
        cin >> dat[i][0] >> dat[i][1] >> C[i];
        F0R(j, 2)
        todo[dat[i][j]].pb(i);
    }
    dfs2(1, 0);
    F0R(i, M)
    {
        if (ok[i])
            cout << 1;
        else
            cout << 0;
    }
    cout << "\n";
}
//Bonus : solve the problem online in 𝑂((𝑁 + 𝑀) log𝑁).
//(Reference : Retrieved from USACO website)