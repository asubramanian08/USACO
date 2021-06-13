#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
unsigned long long getNum(FILE **fp)
{
    unsigned long long total = 0;
    char ch = fgetc(*fp);
    /*if((ch < '0') || (ch > '9'))
        ch = fgetc(*fp);*/
    while ((ch >= '0') && (ch <= '9'))
    {
        total = (total * 10) + (ch - '0');
        ch = fgetc(*fp);
    }
    return total;
}

#define MOD_BY 1000000007
int main(void)
{
    FILE *fp = fopen("milkcollect.in", "r");
    unsigned int cows = (unsigned int)getNum(&fp), bucketGoal = (unsigned int)getNum(&fp);
    unsigned int *milkOut = (unsigned int *)malloc(sizeof(unsigned int) * cows);
    for (unsigned int i = 0; i < cows; i++)
        milkOut[i] = (unsigned int)getNum(&fp);
    fclose(fp);
    unsigned int *waysToGet = (unsigned int *)calloc(bucketGoal + 1, sizeof(unsigned int));
    waysToGet[0] = 1;
    for (unsigned int i = 0; i < bucketGoal; i++)
        for (unsigned int j = 0; j < cows; j++)
            if (i + milkOut[j] <= bucketGoal)
                waysToGet[i + milkOut[j]] = (waysToGet[i + milkOut[j]] + waysToGet[i]) % MOD_BY;
    fp = fopen("milkcollect.out", "w");
    fprintf(fp, "%d", (int)waysToGet[bucketGoal]);
    fclose(fp);
    return 0;
}