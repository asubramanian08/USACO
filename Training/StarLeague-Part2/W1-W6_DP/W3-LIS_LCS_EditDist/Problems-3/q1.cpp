#include <iostream>
using namespace std;

struct bale
{
    int b1;
    int b2;
    int b3;
};
int compare(const void *p1, const void *p2)
{
    int returnVal = ((bale *)p1)->b1 - ((bale *)p2)->b1;
    if (returnVal == 0)
        returnVal = ((bale *)p1)->b2 - ((bale *)p2)->b2;
    return returnVal;
}
int main(void)
{
    FILE *junk;
    junk = freopen("baletower.in", "r", stdin);
    junk = freopen("baletower.out", "w", stdout);
    int numBales;
    cin >> numBales;
    bale *bales = new bale[numBales * 3];
    bale currBale;
    for (int i = 0; i < numBales; i++)
    {
        cin >> currBale.b1 >> currBale.b3 >> currBale.b2;

        bales[i * 3].b1 = min(currBale.b1, currBale.b2);
        bales[i * 3].b2 = max(currBale.b1, currBale.b2);
        bales[i * 3].b3 = currBale.b3;

        bales[i * 3 + 1].b1 = min(currBale.b1, currBale.b3);
        bales[i * 3 + 1].b2 = max(currBale.b1, currBale.b3);
        bales[i * 3 + 1].b3 = currBale.b2;

        bales[i * 3 + 2].b1 = min(currBale.b2, currBale.b3);
        bales[i * 3 + 2].b2 = max(currBale.b2, currBale.b3);
        bales[i * 3 + 2].b3 = currBale.b1;
    }
    qsort(bales, numBales * 3, sizeof(bale), compare);
    int *DP = new int[numBales * 3];
    int totBales = numBales * 3;
    for (int i = 0; i < totBales; i++)
        DP[i] = bales[i].b3;
    for (int i = 0; i < totBales; i++)
        for (int j = 0; j < i; j++)
            if (bales[j].b1 < bales[i].b1 && bales[j].b2 < bales[i].b2)
                DP[i] = max(DP[i], DP[j] + bales[i].b3);
    int ans = 0;
    for (int i = 0; i < totBales; i++)
        ans = max(ans, DP[i]);
    cout << ans;
    return 0;
}