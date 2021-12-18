#include <iostream>
#include <set>
using namespace std;

class LazySumSegTree
{
private:
    using pii = pair<int, int>;
    int *tree, *changeDown;
    pii *cover;
    void init_tree(int pos, int left, int right)
    {
        cover[pos] = pii(left, right);
        changeDown[pos] = 0;
        if (left == right)
        {
            tree[pos] = 0;
            return;
        }
        init_tree(2 * pos + 0, left, (left + right) / 2 + 0);
        init_tree(2 * pos + 1, (left + right) / 2 + 1, right);
        tree[pos] = tree[2 * pos + 0] + tree[2 * pos + 1];
    }
    void updateChangeDown(int pos)
    {
        tree[pos] += (cover[pos].second - cover[pos].first + 1) * changeDown[pos];
        if (cover[pos].first != cover[pos].second)
        {
            changeDown[2 * pos + 0] += changeDown[pos];
            changeDown[2 * pos + 1] += changeDown[pos];
        }
        changeDown[pos] = 0;
    }

public:
    LazySumSegTree(int size)
    {
        tree = new int[size * 4];
        cover = new pii[size * 4];
        changeDown = new int[size * 4];
        init_tree(1, 0, size - 1);
    }
    ~LazySumSegTree()
    {
        delete[] tree;
        delete[] cover;
        delete[] changeDown;
    }
    int query(int left, int right, int pos = 1)
    {
        updateChangeDown(pos);
        if (left <= cover[pos].first && cover[pos].second <= right)
            return tree[pos];
        if (cover[pos].second < left || right < cover[pos].first)
            return 0;
        return query(left, right, 2 * pos + 0) +
               query(left, right, 2 * pos + 1);
    }
    void update(int rangeLeft, int rangeRight, int change, int pos = 1)
    {
        // fully covered
        if (rangeLeft <= cover[pos].first &&
            cover[pos].second <= rangeRight)
            changeDown[pos] += change;
        updateChangeDown(pos);
        // no intersection
        if (cover[pos].second < rangeLeft ||
            rangeRight < cover[pos].first)
            return;
        // some intersection
        if (cover[pos].first < rangeLeft ||
            rangeRight < cover[pos].second)
        {
            update(rangeLeft, rangeRight, change, 2 * pos + 0);
            update(rangeLeft, rangeRight, change, 2 * pos + 1);
            tree[pos] = tree[2 * pos + 0] + tree[2 * pos + 1];
        }
    }
};

int main(void)
{
    // read
    int len;
    cin >> len;
    int *order = new int[len];
    for (int i = 0; i < len; i++)
        cin >> order[i];

    // setup
    LazySumSegTree lsst(len + 1);
    using pii = pair<int, int>;
    set<pii> divisions;
    divisions.insert(pii(len + 1, -2));
    divisions.insert(pii(0, -1));

    // run through list
    for (int i = 0; i < len; i++)
    {
        pii div(order[i], i);
        auto hi = divisions.lower_bound(div);
        auto lo = hi;
        lo--;
        if (hi->second > lo->second)
            lsst.update(order[i], hi->first - 1, 1);
        divisions.insert(div);
    }

    // print and delete
    for (int i = 0; i <= len; i++)
        cout << lsst.query(i, i) << endl;
    delete[] order;
    return 0;
}