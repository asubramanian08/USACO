// Start: 8:48
// Think: 8:59
// Write: 9:17
// Debug: 9:18
#include <iostream>
#include <vector>
#include <map>
#include <set>
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
    int numCows;
    cin >> numCows;
    int *breed = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> breed[i];

    // leftmost and rightmost positions a paired leader in
    map<int, vector<int>> breedOrder;
    int *breedPos = new int[numCows];
    for (int i = 0; i < numCows; i++)
    {
        breedPos[i] = breedOrder[breed[i]].size();
        breedOrder[breed[i]].push_back(i);
    }
    int *left = new int[numCows];
    int *right = new int[numCows];
    for (int i = 0; i < numCows; i++)
    {
        left[i] = breedPos[i] > 0 ? breedOrder[breed[i]][breedPos[i] - 1] : -1;
        right[i] = breedPos[i] < breedOrder[breed[i]].size() - 1
                       ? breedOrder[breed[i]][breedPos[i] + 1]
                       : numCows;
    }

    // Range query (BIT) for all leader pairs
    BIT bit(numCows);
    using pii = pair<int, int>;
    set<pii> leaderEnd; // end, cow
    long long pairs = 0;
    for (int i = 0; i < numCows; i++)
    {
        while (leaderEnd.size() && leaderEnd.begin()->first <= i)
            bit.updt(leaderEnd.begin()->second, -1), leaderEnd.erase(leaderEnd.begin());
        pairs += bit.query(i) - bit.query(left[i]);
        bit.updt(i, 1);
        leaderEnd.insert(pii(right[i], i));
    }

    // print and delete
    cout << pairs << endl;
    delete[] breed;
    delete[] breedPos;
    delete[] left;
    delete[] right;
    return 0;
}