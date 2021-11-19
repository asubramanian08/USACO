// SumSegTree
class SumSegTree
{
private:
    using pii = pair<int, int>;
    long long *tree;
    pii *cover;
    void init_tree(int pos, int left, int right, long long *arr)
    {
        cover[pos] = pii(left, right);
        if (left == right)
        {
            tree[pos] = arr[left];
            return;
        }
        init_tree(2 * pos + 0, left, (left + right) / 2 + 0, arr);
        init_tree(2 * pos + 1, (left + right) / 2 + 1, right, arr);
        tree[pos] = tree[2 * pos + 0] + tree[2 * pos + 1];
    }

public:
    SumSegTree(int size, long long *arr)
    {
        tree = new long long[size * 4];
        cover = new pii[size * 4];
        init_tree(1, 0, size - 1, arr);
    }
    ~SumSegTree()
    {
        delete[] tree;
        delete[] cover;
    }
    long long query(int left, int right, int pos = 1)
    {
        if (cover[pos].second < left || right < cover[pos].first)
            return 0;
        if (left <= cover[pos].first && cover[pos].second <= right)
            return tree[pos];
        return query(left, right, 2 * pos + 0) +
               query(left, right, 2 * pos + 1);
    }
    void update(int node, long long change, int pos = 1)
    {
        // no intersection
        if (cover[pos].second < node ||
            node < cover[pos].first)
            return;
        // fully covered
        if (node == cover[pos].first &&
            node == cover[pos].second)
            tree[pos] += change;
        // some intersection
        else
        {
            update(node, change, 2 * pos + 0);
            update(node, change, 2 * pos + 1);
            tree[pos] = tree[2 * pos + 0] + tree[2 * pos + 1];
        }
    }
};