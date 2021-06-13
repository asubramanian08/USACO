#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
long long getNum(FILE **fp)
{
    long long total = 0;
    char ch = fgetc(*fp);
    /*if (((ch < '0') || (ch > '9')) && (ch != '-'))
        ch = fgetc(*fp);*/
    if (ch == '-')
        return getNum(fp) * -1;
    while ((ch >= '0') && (ch <= '9'))
    {
        total = (total * 10) + (ch - '0');
        ch = fgetc(*fp);
    }
    return total;
}
unsigned int **DP_B;
unsigned int **DP_E;
unsigned int *hayVal;
unsigned int bTurn(unsigned int bPos, unsigned int ePos);
unsigned int eTurn(unsigned int bPos, unsigned int ePos)
{
    if (DP_E[bPos][ePos])
        return DP_E[bPos][ePos];
    unsigned int eStart, minEnd = ~0, currEnd;
    if (ePos - bPos < hayVal[ePos - 1])
        eStart = bPos;
    else
        eStart = ePos - hayVal[ePos - 1];
    for (unsigned int j = eStart; j < ePos; j++)
    {
        currEnd = bTurn(bPos, j);
        if (currEnd < minEnd)
            minEnd = currEnd;
    }
    return DP_E[bPos][ePos] = minEnd;
}
unsigned int bTurn(unsigned int bPos, unsigned int ePos)
{
    if (DP_B[bPos][ePos])
        return DP_B[bPos][ePos];
    unsigned int bEnd = MIN(bPos + hayVal[bPos], ePos), maxEnd = 0, currEnd;
    for (unsigned int i = bPos + 1; i <= bEnd; i++)
    {
        currEnd = eTurn(i, ePos);
        if (currEnd > maxEnd)
            maxEnd = currEnd;
    }
    return DP_B[bPos][ePos] = maxEnd;
}
int main(void)
{
    FILE *fp = fopen("sharing.in", "r");
    unsigned int haybales = getNum(&fp);
    hayVal = (unsigned int *)malloc(sizeof(unsigned int) * haybales);
    for (unsigned int i = 0; i < haybales; i++)
        hayVal[i] = getNum(&fp);
    fclose(fp);
    DP_B = (unsigned int **)malloc(sizeof(unsigned int *) * (haybales + 1));
    DP_E = (unsigned int **)malloc(sizeof(unsigned int *) * (haybales + 1));
    for (unsigned int i = 0; i <= haybales; i++)
    {
        DP_B[i] = (unsigned int *)calloc(haybales + 1, sizeof(unsigned int));
        DP_B[i][i] = i;
        DP_E[i] = (unsigned int *)calloc(haybales + 1, sizeof(unsigned int));
        DP_E[i][i] = i;
    }
    unsigned int bestVal = bTurn(0, haybales);
    unsigned int ans = 0;
    for (unsigned int i = 0; i < bestVal; i++)
        ans += hayVal[i];
    fp = fopen("sharing.out", "w");
    fprintf(fp, "%d", ans);
    fclose(fp);
    return 0;
}