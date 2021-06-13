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

int main(void)
{
    FILE *fp = fopen("248.in", "r");
    unsigned int numOfNums = getNum(&fp);
    unsigned int *nums = (unsigned int *)malloc(sizeof(unsigned int) * numOfNums);
    unsigned int **combine = (unsigned int **)malloc(sizeof(unsigned int *) * numOfNums);
    for (unsigned int i = 0; i < numOfNums; i++)
    {
        combine[i] = (unsigned int *)calloc(i + 1, sizeof(unsigned int));
        nums[i] = getNum(&fp);
    }
    fclose(fp);
    unsigned int maxVal = 0, currEndBlock, currVal;
    bool change;
    for (unsigned int i = 0; i < numOfNums; i++)
    {
        currEndBlock = i;
        combine[i][currEndBlock] = (currVal = nums[i]);
        while (currEndBlock)
            for (unsigned int j = 0; j < currEndBlock; j++)
                if (combine[currEndBlock - 1][j] == currVal)
                    combine[i][currEndBlock = j] = ++currVal;
                else if (j == currEndBlock - 1)
                    currEndBlock = 0;
        if (maxVal < currVal)
            maxVal = currVal;
    }
    fp = fopen("248.out", "w");
    fprintf(fp, "%d", maxVal);
    fclose(fp);
    return 0;
}