// Start: 6:00
// Think: ?
// Write: 6:21
// Debug: 6:30
#include <iostream>
#include <set>
#include <vector>
using namespace std;

// BIT or fenwick tree
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
    // read
#ifndef HOME
    freopen("sleepy.in", "r", stdin);
    freopen("sleepy.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    int *cows = new int[numCows];
    for (int i = 0; i < numCows; i++)
    {
        cin >> cows[i];
        cows[i]--;
    }

    // sort cows
    BIT bit(numCows);
    int end = numCows - 1;
    bit.updt(cows[end], 1);
    while (end >= 0 && cows[end - 1] < cows[end])
    {
        end--;
        bit.updt(cows[end], 1);
    }
    vector<int> moves;
    for (int start = 0; start < end; start++)
    {
        moves.push_back(bit.query(cows[start]) + end - start - 1);
        bit.updt(cows[start], 1);
    }

    // print and delete
    cout << moves.size() << endl;
    for (int i = 0; i < moves.size(); i++)
        cout << moves[i] << (i != moves.size() - 1 ? " " : "");
    cout << endl;
    delete[] cows;
    return 0;
}