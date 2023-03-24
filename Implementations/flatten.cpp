// flatten the tree
int flatten(vector<int> *graph, int *first, int *second, int node, int pos, int parent)
{
    first[node] = pos;
    for (int next : graph[node])
        if (next != parent)
            pos = flatten(graph, first, second, next, pos + 1, node);
    return second[node] = pos + 1;
}