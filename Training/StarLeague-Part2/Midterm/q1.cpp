#include <iostream>
using namespace std;

int main(void)
{
    /*FILE *junk;
    junk = freopen("feast.in", "r", stdin);
    junk = freopen("feast.out", "w", stdout);*/

    int maxFull, lemon, orange;
    cin >> maxFull >> lemon >> orange;
    int *preWater = new int[maxFull + 1];
    for (int i = 0; i <= maxFull; i++)
        preWater[i] = i;
    for (int i = maxFull; i >= 0; i--)
    {
        if (i >= lemon)
            preWater[i - lemon] = max(preWater[i - lemon], preWater[i]);
        if (i >= orange)
            preWater[i - orange] = max(preWater[i - orange], preWater[i]);
    }
    int *postWater = new int[maxFull + 1];
    for (int i = 0; i <= maxFull; i++)
        postWater[i] = i;
    for (int i = maxFull; i >= 0; i--)
    {
        postWater[i] = max(postWater[i], max(preWater[i], preWater[i / 2]));
        if (i >= lemon)
            postWater[i - lemon] = max(postWater[i - lemon], postWater[i]);
        if (i >= orange)
            postWater[i - orange] = max(postWater[i - orange], postWater[i]);
    }
    cout << postWater[0];
    return 0;
}