#include <iostream>
using namespace std;

//BIT tree class
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
    /*FILE *junk;
    junk = freopen("circlecross.in", "r", stdin);
    junk = freopen("circlecross.out", "w", stdout);*/
    //read
    int cows;
    cin >> cows;
    int numCross = cows << 1;
    int *crossPoint = new int[numCross];
    for (int i = 0; i < numCross; i++)
        cin >> crossPoint[i];
    for (int i = 0; i < numCross; i++)
        crossPoint[i]--;

    //initialize
    int *start = new int[cows]; //-1 = not started
    for (int i = 0; i < cows; i++)
        start[i] = -1;
    BIT circle(numCross);

    //compute the pairs
    int pairs = 0;
    for (int i = 0; i < numCross; i++)
        if (start[crossPoint[i]] == -1)
        {
            circle.updt(i, 1);
            start[crossPoint[i]] = i;
        }
        else
        {
            circle.updt(start[crossPoint[i]], -1);
            pairs += circle.query(i) - circle.query(start[crossPoint[i]]);
        }

    //print and return
    cout << pairs;
    return 0;
}