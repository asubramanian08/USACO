//http://docplayer.net/171511525-Problems-translated-from-croatian-by-paula-gombar.html -> question 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
/*unsigned long long getNum()
{
    unsigned long long total = 0;
    char ch = getchar();
    while ((ch != ' ') && (ch != '\n'))
    {
        total = (total * 10) + (ch - '0');
        ch = getchar();
    }
    return total;
}*/
int compareFunc(const void *p1, const void *p2)
{
    return *((unsigned int *)p1) - *((unsigned int *)p2);
}
unsigned long long getNum()
{
    char ch;
    unsigned long long total = 0;
    while (((ch = getchar()) >= '0') && (ch <= '9'))
    {
        total = (total * 10) + (ch - '0');
    }
    return total;
}
int main(void)
{
    unsigned int numOfTables = getNum(), maxDays = 0;
    getchar(); //swallow something after??
    unsigned int *candyAtTbl = (unsigned int *)malloc(sizeof(unsigned int) * numOfTables);
    for (unsigned int i = 0; i < numOfTables; i++)
    {
        candyAtTbl[i] = getNum();
        maxDays = MAX(maxDays, candyAtTbl[i]);
    }
    maxDays++;
    qsort(candyAtTbl, numOfTables, sizeof(unsigned int), compareFunc);

    unsigned int *firstGroup = (unsigned int *)calloc(numOfTables, sizeof(unsigned int));
    unsigned int *currVals = (unsigned int *)malloc(sizeof(unsigned int *) * numOfTables);
    unsigned int *changeDay = (unsigned int *)malloc(numOfTables * sizeof(unsigned int));
    for (unsigned int i = 0; i < numOfTables; i++)
        changeDay[i] = 1;
    memcpy(currVals, candyAtTbl, sizeof(unsigned int) * numOfTables);
    unsigned int nextDay, lastNum, count;
    count = 0;
    lastNum = currVals[0];
    for (unsigned int i = 0; i < numOfTables; i++)
        if (lastNum == currVals[i])
            count++;
        else
        {
            if (firstGroup[count - 1] == 0)
                firstGroup[count - 1] = 2;
            count = 1;
            lastNum = currVals[i];
        }
    if (firstGroup[count - 1] == 0)
        firstGroup[count - 1] = 2;
    do
    {
        nextDay = ~((unsigned int)0);
        for (unsigned int i = 0; i < numOfTables; i++)
            if (currVals[i] != 0)
            {
                if (candyAtTbl[i] / (changeDay[i] + 1) == currVals[i])
                    nextDay = MIN(nextDay, candyAtTbl[i] / currVals[i] + 1);
                else
                    nextDay = MIN(nextDay, changeDay[i] + 1);
            }
        for (unsigned int i = 0; i < numOfTables; i++)
            if (currVals[i] != candyAtTbl[i] / nextDay)
            {
                currVals[i] = candyAtTbl[i] / nextDay;
                changeDay[i] = nextDay;
            }
        if (nextDay <= maxDays + 1)
        {
            count = 0;
            lastNum = currVals[0];
            for (unsigned int i = 0; i < numOfTables; i++)
                if (lastNum == currVals[i])
                    count++;
                else
                {
                    if (firstGroup[count - 1] == 0)
                        firstGroup[count - 1] = nextDay + 1;
                    count = 1;
                    lastNum = currVals[i];
                }
            if (firstGroup[count - 1] == 0)
                firstGroup[count - 1] = nextDay + 1;
        }
    } while (nextDay <= maxDays + 1);
    for (unsigned int i = 0; i < numOfTables; i++)
        printf("%d\n", firstGroup[i] - 1);
    return 0;
}