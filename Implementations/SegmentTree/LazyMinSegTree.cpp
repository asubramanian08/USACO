// Look at AlphaStar-PlatinumA week 9

#define BIG_NUM 1000000000
class LazyMinSegTree
{
private:
    using pii = pair<int, int>;
    long long *tree, *changeDown;
    pii *cover;
    void init_tree(int pos, int left, int right, long long *arr)
    {
        cover[pos] = pii(left, right);
        changeDown[pos] = 0;
        if (left == right)
        {
            tree[pos] = arr[left];
            return;
        }
        init_tree(2 * pos + 0, left, (left + right) / 2 + 0, arr);
        init_tree(2 * pos + 1, (left + right) / 2 + 1, right, arr);
        tree[pos] = min(tree[2 * pos + 0], tree[2 * pos + 1]);
    }
    void updateChangeDown(int pos)
    {
        tree[pos] += changeDown[pos];
        if (cover[pos].first != cover[pos].second)
        {
            changeDown[2 * pos + 0] += changeDown[pos];
            changeDown[2 * pos + 1] += changeDown[pos];
        }
        changeDown[pos] = 0;
    }

public:
    LazyMinSegTree(int size, long long *arr)
    {
        tree = new long long[size * 3];
        cover = new pii[size * 3];
        changeDown = new long long[size * 3];
        init_tree(1, 0, size - 1, arr);
    }
    ~LazyMinSegTree()
    {
        delete[] tree;
        delete[] cover;
        delete[] changeDown;
    }
    long long query(int left, int right, int pos = 1)
    {
        updateChangeDown(pos);
        if (left <= cover[pos].first && cover[pos].second <= right)
            return tree[pos];
        if (cover[pos].second < left || right < cover[pos].first)
            return BIG_NUM;
        return min(query(left, right, 2 * pos + 0),
                   query(left, right, 2 * pos + 1));
    }
    void update(int rangeLeft, int rangeRight, long long change, int pos = 1)
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
            tree[pos] = min(tree[2 * pos + 0], tree[2 * pos + 1]);
        }
    }
};