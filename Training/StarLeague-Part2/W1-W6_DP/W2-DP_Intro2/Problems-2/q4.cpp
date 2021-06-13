#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define friendly(a, b) (abs((int)a - (int)b) <= 4)
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
int main(void)
{
    FILE *fp = fopen("nocross.in", "r");
    unsigned int numOfFeilds = getNum(&fp);
    unsigned int *feild1 = (unsigned int *)malloc(sizeof(unsigned int) * numOfFeilds);
    unsigned int *feild2 = (unsigned int *)malloc(sizeof(unsigned int) * numOfFeilds);
    for (unsigned int i = 0; i < numOfFeilds; i++)
        feild1[i] = getNum(&fp);
    for (unsigned int i = 0; i < numOfFeilds; i++)
        feild2[i] = getNum(&fp);
    fclose(fp);
    unsigned int **DP = (unsigned int **)malloc(sizeof(unsigned int *) * numOfFeilds);
    for (unsigned int i = 0; i < numOfFeilds; i++)
        DP[i] = (unsigned int *)malloc(sizeof(unsigned int) * numOfFeilds);
    for (int i = numOfFeilds - 1; i >= 0; i--)
        for (int j = numOfFeilds - 1; j >= 0; j--)
            if (i != numOfFeilds - 1)
                if (j != numOfFeilds - 1)
                    DP[i][j] = MAX(DP[i + 1][j + 1] + friendly(feild1[i], feild2[j]),
                                   MAX(DP[i + 1][j], DP[i][j + 1]));
                else
                    DP[i][j] = MAX(DP[i + 1][j], friendly(feild1[i], feild2[j]));
            else if (j != numOfFeilds - 1)
                DP[i][j] = MAX(DP[i][j + 1], friendly(feild1[i], feild2[j]));
            else
                DP[i][j] = friendly(feild1[i], feild2[j]);
    fp = fopen("nocross.out", "w");
    fprintf(fp, "%d", DP[0][0]);
    fclose(fp);
    return 0;
}