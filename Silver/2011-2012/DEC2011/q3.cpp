// Start: 11:00
// Think: ?
// Write: 11:52
// Debug: 11:54
//done after q3.txt
#include <iostream>
using namespace std;

int **costST;
int calcMin(int start, int end)
{
    start--;
    end--;
    int log = log2(end - start + 1);
    return min(costST[start][log],
               costST[end - (1 << log) + 1][log]);
}

int main(void)
{
    //read
#ifndef HOME
    freopen("umbrella.in", "r", stdin);
    freopen("umbrella.out", "w", stdout);
#endif
    int numCows, range;
    cin >> numCows >> range;
    int *cows = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i];
    int log = log2(range) + 1;
    costST = new int *[range];
    for (int i = 0; i < range; i++)
    {
        costST[i] = new int[log];
        cin >> costST[i][0];
    }

    //RMQ -> sparse table
    for (int j = 1; j < log; j++)
        for (int i = 0; i + (1 << j) <= range; i++)
            costST[i][j] = min(costST[i][j - 1],
                               costST[i + (1 << (j - 1))][j - 1]);

    //find the cost
    sort(&cows[0], &cows[numCows]);
    int *finishCost = new int[numCows];
    finishCost[numCows - 1] = calcMin(1, range);
    for (int i = numCows - 2; i >= 0; i--)
    {
        finishCost[i] = calcMin(cows[numCows - 1] - cows[i] + 1, range);
        for (int j = i + 1; j < numCows; j++)
            finishCost[i] = min(finishCost[i], calcMin(cows[j - 1] - cows[i] + 1, range) + finishCost[j]);
    }

    //delete and print
    cout << finishCost[0];
    delete[] cows;
    for (int i = 0; i < range; i++)
        delete[] costST[i];
    delete[] costST;
    delete[] finishCost;
    return 0;
}