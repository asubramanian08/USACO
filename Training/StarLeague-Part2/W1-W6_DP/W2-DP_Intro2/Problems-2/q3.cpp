#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
long long getNum(FILE **fp)
{
    long long total = 0;
    char ch = fgetc(*fp);
    /*if(((ch < '0') || (ch > '9')) && (ch != '-'))
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
int compare(const void *p1, const void *p2)
{
    return *((unsigned int *)p1) - *((unsigned int *)p2);
}
struct cow
{
    unsigned int cost;
    unsigned int dist;
};

int main(void)
{
    FILE *fp = fopen("fencepaint.in", "r");
    unsigned int fenceLen = getNum(&fp), numOfCows = getNum(&fp);
    unsigned int *bestVal = (unsigned int *)malloc((fenceLen + 1) * sizeof(unsigned int));
    memset(bestVal, ~0, sizeof(unsigned int) * (fenceLen + 1));
    cow *cows = (cow *)malloc(sizeof(cow) * numOfCows);
    for (unsigned int i = 0; i < numOfCows; i++)
    {
        cows[i].dist = getNum(&fp);
        cows[i].cost = getNum(&fp);
        bestVal[cows[i].dist] = cows[i].cost;
    }
    fclose(fp);
    for (unsigned int i = 0; i < fenceLen; i++)
        if (bestVal[i] != ~0)
            for (unsigned int j = 0; j < numOfCows; j++)
                if (i + cows[j].dist <= fenceLen)
                    bestVal[i + cows[j].dist] = MIN(bestVal[i + cows[j].dist],
                                                    bestVal[i] + cows[j].cost);
    fp = fopen("fencepaint.out", "w");
    if (bestVal[fenceLen])
        fprintf(fp, "%d", bestVal[fenceLen]);
    else
        fprintf(fp, "-1");
    fclose(fp);
    return 0;
}