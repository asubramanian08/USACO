// MinSegTree
#define BIG_NUM 10000000000
class MinSegTree
{
private:
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
        tree[pos] = min(tree[2 * pos + 0], tree[2 * pos + 1]);
    }

public:
    MinSegTree(int size, long long *arr)
    {
        tree = new long long[size * 4];
        cover = new pii[size * 4];
        init_tree(1, 0, size - 1, arr);
    }
    ~MinSegTree()
    {
        delete[] tree;
        delete[] cover;
    }
    long long query(int left, int right, int pos = 1)
    {
        if (left > right || cover[pos].second < left || right < cover[pos].first)
            return BIG_NUM;
        if (left <= cover[pos].first && cover[pos].second <= right)
            return tree[pos];
        return min(query(left, right, 2 * pos + 0),
                   query(left, right, 2 * pos + 1));
    }
    void update(int node, long long set, int pos = 1)
    {
        // no intersection
        if (cover[pos].second < node ||
            node < cover[pos].first)
            return;
        // fully covered
        if (node == cover[pos].first &&
            node == cover[pos].second)
            tree[pos] = set;
        // some intersection
        else
        {
            update(node, set, 2 * pos + 0);
            update(node, set, 2 * pos + 1);
            tree[pos] = min(tree[2 * pos + 0], tree[2 * pos + 1]);
        }
    }
};