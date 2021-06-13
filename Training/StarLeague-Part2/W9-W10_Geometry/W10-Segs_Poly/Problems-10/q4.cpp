#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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

struct barn
{
    int x, y, cows, yPos;
};
struct query
{
    int xLine, yLine, orgPos;
    int A, B, C, D;
};

bool cmp_x(barn &b1, barn &b2)
{
    if (b1.x != b2.x)
        return b1.x < b2.x;
    return b1.y < b2.y;
}
bool cmp_y(const barn &b1, const barn &b2)
{
    if (b1.y != b2.y)
        return b1.y < b2.y;
    return b1.x < b2.x;
}
bool cmp_query(query &q1, query &q2)
{
    if (q1.xLine != q2.xLine)
        return q1.xLine < q2.xLine;
    return q1.yLine < q2.yLine;
}
bool cmp_org(query &q1, query &q2)
{
    return q1.orgPos < q2.orgPos;
}

int main(void)
{
    //read (barns)
    FILE *junk;
    junk = freopen("paritition.in", "r", stdin);
    junk = freopen("paritition.out", "w", stdout);
    int numBarns, numQueries, cowTotal = 0;
    cin >> numBarns >> numQueries;
    barn *barnsArr = new barn[numBarns];
    for (int i = 0; i < numBarns; i++)
    {
        cin >> barnsArr[i].x >> barnsArr[i].y >> barnsArr[i].cows;
        cowTotal += barnsArr[i].cows;
    }
    query *queries = new query[numQueries];
    for (int i = 0; i < numQueries; i++)
    {
        cin >> queries[i].xLine >> queries[i].yLine;
        queries[i].orgPos = i;
    }

    //make the barns index and prefix sum
    //y things
    sort(&barnsArr[0], &barnsArr[numBarns], cmp_y);
    int *yIndex = new int[numBarns];
    for (int i = 0; i < numBarns; i++)
    {
        barnsArr[i].yPos = i;
        yIndex[i] = barnsArr[i].y;
    }
    int *y_pSum = new int[numBarns];
    y_pSum[0] = barnsArr[0].cows;
    for (int i = 1; i < numBarns; i++)
        y_pSum[i] = y_pSum[i - 1] + barnsArr[i].cows;
    //x things
    sort(&barnsArr[0], &barnsArr[numBarns], cmp_x);
    int *xIndex = new int[numBarns];
    for (int i = 0; i < numBarns; i++)
        xIndex[i] = barnsArr[i].x;
    int *x_pSum = new int[numBarns];
    x_pSum[0] = barnsArr[0].cows;
    for (int i = 1; i < numBarns; i++)
        x_pSum[i] = x_pSum[i - 1] + barnsArr[i].cows;

    //start BIT, prepare queries
    BIT getY(numBarns);
    for (int i = 0; i < numQueries; i++)
    {
        queries[i].xLine = lower_bound(&xIndex[0], &xIndex[numBarns], queries[i].xLine) - &xIndex[0] - 1;
        queries[i].yLine = lower_bound(&yIndex[0], &yIndex[numBarns], queries[i].yLine) - &yIndex[0] - 1;
    }
    sort(&queries[0], &queries[numQueries], cmp_query);

    //answer queries
    int addedTill = 0;
    for (int i = 0; i < numQueries; i++)
    {
        while ((addedTill < numBarns) && (addedTill <= queries[i].xLine))
        {
            getY.updt(barnsArr[addedTill].yPos, barnsArr[addedTill].cows);
            addedTill++;
        }
        queries[i].A = getY.query(queries[i].yLine);
        queries[i].B = y_pSum[queries[i].yLine] - queries[i].A;
        queries[i].D = x_pSum[queries[i].xLine] - queries[i].A;
        queries[i].C = cowTotal - queries[i].B - queries[i].D - queries[i].A;
    }

    //sort queries and print answers
    sort(&queries[0], &queries[numQueries], cmp_org);
    for (int i = 0; i < numQueries; i++)
        cout << queries[i].A << ' ' << queries[i].B << ' '
             << queries[i].C << ' ' << queries[i].D << endl;
    return 0;
}