#include <stdio.h>
#include <stdlib.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
unsigned long long getNum()
{
    unsigned long long total = 0;
    char ch;
    while (((ch = getchar()) != ' ') && (ch != '\n'))
        total = (total * 10) + (ch - '0');
    return total;
}
unsigned int **maxScore;
unsigned int numOfCoins;
unsigned int *values;
void DP(unsigned int coinsPicked, unsigned int maxPick)
{
    unsigned int sumation;
    if (coinsPicked == 0)
        sumation = values[numOfCoins - 1];
    else
        sumation = values[numOfCoins - 1] - values[coinsPicked - 1];
    if (coinsPicked + maxPick >= numOfCoins)
        maxScore[coinsPicked][maxPick - 1] = sumation;
    else if (maxPick > 1)
        maxScore[coinsPicked][maxPick - 1] = MAX(sumation - maxScore[coinsPicked + maxPick][MIN(maxPick * 2 - 1, numOfCoins - 1)], maxScore[coinsPicked][maxPick - 2]);
    else
        maxScore[coinsPicked][maxPick - 1] = sumation - maxScore[coinsPicked + maxPick][MIN(maxPick * 2 - 1, numOfCoins - 1)];
}
int main(void)
{
    numOfCoins = getNum();
    values = (unsigned int *)malloc(sizeof(unsigned int) * numOfCoins);
    maxScore = (unsigned int **)malloc(sizeof(unsigned int *) * numOfCoins);
    unsigned int totalVal = 0;
    for (unsigned int i = 0; i < numOfCoins; i++)
    {
        maxScore[i] = (unsigned int *)malloc(sizeof(unsigned int) * numOfCoins);
        totalVal += getNum();
        values[i] = totalVal;
    }
    for (int i = numOfCoins - 1; i >= 0; i--)
        for (unsigned int j = 0; j < numOfCoins; j++)
            DP(i, j + 1);
    printf("%d", maxScore[0][1]);
    return 0;
}