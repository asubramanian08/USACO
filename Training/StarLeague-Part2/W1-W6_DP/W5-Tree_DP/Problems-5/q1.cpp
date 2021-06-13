#include <vector>
#include <iostream>
using namespace std;

#define BIGNUM 10000000
struct node
{
    int node_wt;
    vector<int> children;
    int leavesUnder;
    int *costs;
};
node *tree;
int leaves;
void removeParent(int currNode, int parent)
{
    for (int i = 0; i < tree[currNode].children.size(); i++)
        if (tree[currNode].children[i] == parent)
        {
            tree[currNode].children.erase(tree[currNode].children.begin() + i);
            break;
        }
    for (int i = 0; i < tree[currNode].children.size(); i++)
        removeParent(tree[currNode].children[i], currNode);
}
int findLeaves(int currNode)
{
    tree[currNode].leavesUnder = tree[currNode].children.size() == 0;
    for (int i = 0; i < tree[currNode].children.size(); i++)
        tree[currNode].leavesUnder += findLeaves(tree[currNode].children[i]);
    return tree[currNode].leavesUnder;
}
void findCosts(int currNode)
{
    for (int i = 0; i < tree[currNode].children.size(); i++)
        findCosts(tree[currNode].children[i]);
    int **DP = new int *[tree[currNode].children.size() + 1];
    for (int i = 0; i <= tree[currNode].children.size(); i++)
        DP[i] = new int[leaves + 1];
    DP[0][0] = 0; //tree[currNode].node_wt;
    for (int i = 1; i <= leaves; i++)
        DP[0][i] = 0;
    int checkTill = min(leaves, tree[currNode].leavesUnder);
    for (int i = 1; i <= tree[currNode].children.size(); i++)
    {
        for (int j = 0; j <= checkTill; j++)
        {
            DP[i][j] = BIGNUM;
            for (int k = 0; k <= j; k++)
                if (tree[tree[currNode].children[i - 1]].costs[k] != BIGNUM)
                    DP[i][j] = min(DP[i][j], DP[i - 1][j - k] + tree[tree[currNode].children[i - 1]].costs[k]);
        }
        for (int j = checkTill + 1; j <= leaves; j++)
            DP[i][j] = BIGNUM;
    }
    for (int i = 0; i < tree[currNode].children.size(); i++)
        delete[] DP[i];
    DP[tree[currNode].children.size()][0] += tree[currNode].node_wt;
    tree[currNode].costs = DP[tree[currNode].children.size()];
    delete[] DP;
}

int main(void)
{
    /*FILE *junk;
    junk = freopen("leaves.in", "r", stdin);
    junk = freopen("leaves.out", "w", stdout);*/
    int nodes, root;
    cin >> nodes >> leaves >> root;
    root--;
    tree = new node[nodes];
    for (int i = 0; i < nodes; i++)
        cin >> tree[i].node_wt;
    int n1, n2;
    for (int i = 1; i < nodes; i++)
    {
        cin >> n1 >> n2;
        n1--;
        n2--;
        tree[n1].children.push_back(n2);
        tree[n2].children.push_back(n1);
    }
    removeParent(root, -1);
    findLeaves(root);
    findCosts(root);
    if (tree[root].costs[leaves] != BIGNUM)
        cout << tree[root].costs[leaves];
    else
        cout << "Impossible";
    return 0;
}