// Start: 9:19
// Think: 9:38 (segment tree),10:23-10:33
// Write: 11:25
// Debug: NA
#include <iostream>
#include <cmath>
using namespace std;

//Min Segment Tree copied and edited from geeksforgeeks
int getMid(int s, int e) { return s + (e - s) / 2; }
int MaxUtil(int *st, int ss, int se, int l, int r, int node)
{
    if (l <= ss && r >= se)
        return st[node];
    if (se < l || ss > r)
        return -1;
    int mid = getMid(ss, se);
    return max(MaxUtil(st, ss, mid, l, r, 2 * node + 1),
               MaxUtil(st, mid + 1, se, l, r, 2 * node + 2));
}
void updateValue(int arr[], int *st, int ss, int se, int index, int value, int node)
{
    if (index < ss || index > se)
    {
        cout << "Invalid Input" << endl;
        return;
    }
    if (ss == se)
    {
        arr[index] = value;
        st[node] = value;
    }
    else
    {
        int mid = getMid(ss, se);
        if (index >= ss && index <= mid)
            updateValue(arr, st, ss, mid, index, value, 2 * node + 1);
        else
            updateValue(arr, st, mid + 1, se, index, value, 2 * node + 2);
        st[node] = max(st[2 * node + 1], st[2 * node + 2]);
    }
    return;
}
int getMax(int *st, int n, int l, int r)
{
    if (l < 0 || r > n - 1 || l > r)
    {
        printf("Invalid Input");
        return -1;
    }
    return MaxUtil(st, 0, n - 1, l, r, 0);
}
int constructSTUtil(int arr[], int ss, int se, int *st, int si)
{
    if (ss == se)
    {
        st[si] = arr[ss];
        return arr[ss];
    }
    int mid = getMid(ss, se);
    st[si] = max(constructSTUtil(arr, ss, mid, st, si * 2 + 1),
                 constructSTUtil(arr, mid + 1, se, st, si * 2 + 2));

    return st[si];
}
int *constructST(int arr[], int n)
{
    int x = (int)(ceil(log2(n)));
    int max_size = 2 * (int)pow(2, x) - 1;
    int *st = new int[max_size];
    constructSTUtil(arr, 0, n - 1, st, 0);
    return st;
}

//BIT or fenwick tree
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

using pii = pair<int, int>;
int dist(pii p1, pii p2) { return abs(p1.first - p2.first) + abs(p1.second - p2.second); }
int saved(pii p1, pii p2, pii p3) { return dist(p1, p2) + dist(p2, p3) - dist(p1, p3); }
#define NA -1

int main(void)
{
    //read
#ifndef HOME
    freopen("marathon.in", "r", stdin);
    freopen("marathon.out", "w", stdout);
#endif
    int numCows, queries;
    cin >> numCows >> queries;
    pii *cows = new pii[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].first >> cows[i].second;

    //time saved
    int *timeSaved = new int[numCows];
    timeSaved[0] = timeSaved[numCows - 1] = 0;
    for (int i = 1; i < numCows - 1; i++)
        timeSaved[i] = saved(cows[i - 1], cows[i], cows[i + 2]);

    //bit
    BIT bit(numCows);
    for (int i = 1; i < numCows; i++)
        bit.updt(i, dist(cows[i], cows[i - 1]));

    //queries
    int *st = constructST(timeSaved, numCows);
    char action;
    int num1, num2, num3;
    for (int i = 0; i < numCows; i++)
    {
        cin >> action;
        if (action == 'Q')
        {
            cin >> num1 >> num2;
            num1--, num2--;
            if (num1 == num2)
                cout << 0 << endl;
            else if (num1 + 1 == num2)
                cout << dist(cows[num1], cows[num2]) << endl;
            else
                cout << (bit.query(num2) - bit.query(num1) -
                         getMax(st, numCows, num1 + 1, num2 - 1))
                     << endl;
        }
        else //action == 'U'
        {
            cin >> num1 >> num2 >> num3;
            cows[--num1] = pii(num2, num3);
            if (num1 - 1 > 0)
                updateValue(timeSaved, st, 0, numCows - 1, num1 - 1,
                            saved(cows[num1 - 2], cows[num1 - 1], cows[num1]), 0);
            if (num1 > 0 && num1 < numCows - 1)
                updateValue(timeSaved, st, 0, numCows - 1, num1,
                            saved(cows[num1 - 1], cows[num1], cows[num1 + 1]), 0);
            if (num1 + 1 < numCows - 1)
                updateValue(timeSaved, st, 0, numCows - 1, num1 + 1,
                            saved(cows[num1], cows[num1 + 1], cows[num1 + 2]), 0);
            if (num1 > 0)
                bit.updt(num1, dist(cows[num1 - 1], cows[num1]) - (bit.query(num1) - bit.query(num1 - 1)));
            if (num1 < numCows - 1)
                bit.updt(num1 + 1, dist(cows[num1], cows[num1 + 1]) - (bit.query(num1 + 1) - bit.query(num1)));
        }
    }

    //delete
    delete[] cows;
    delete[] timeSaved;
    return 0;
}