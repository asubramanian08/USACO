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
        return -1 * getNum(fp);
    while ((ch >= '0') && (ch <= '9'))
    {
        total = (total * 10) + (ch - '0');
        ch = fgetc(*fp);
    }
    return total;
}

int main(void)
{
    FILE *fp = fopen("grazing.in", "r");
    unsigned int sideLen = (unsigned int)getNum(&fp);
    int **grid = (int **)malloc(sizeof(int *) * sideLen);
    int **DP = (int **)malloc(sizeof(int *) * sideLen);
    for (unsigned int i = 0; i < sideLen; i++)
    {
        grid[i] = (int *)malloc(sizeof(int) * sideLen);
        DP[i] = (int *)malloc(sizeof(int) * sideLen);
        for (unsigned int j = 0; j < sideLen; j++)
            grid[i][j] = (int)getNum(&fp);
    }
    fclose(fp);
    for (unsigned int i = 0; i < sideLen; i++)
        for (unsigned int j = 0; j < sideLen; j++)
        {
            if (i > 0)
                if (j > 0)
                    DP[i][j] = MAX(MAX(DP[i - 1][j], DP[i][j - 1]), DP[i - 1][j - 1]);
                else
                    DP[i][j] = DP[i - 1][j];
            else if (j > 0)
                DP[i][j] = DP[i][j - 1];
            else
                DP[i][j] = 0;
            DP[i][j] += grid[i][j];
        }
    fp = fopen("grazing.out", "w");
    fprintf(fp, "%d", DP[sideLen - 1][sideLen - 1]);
    fclose(fp);
    return 0;
}