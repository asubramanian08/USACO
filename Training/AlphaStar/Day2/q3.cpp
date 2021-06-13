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

int main(void)
{
    unsigned int nodes = getNum(), flights = getNum(), hubs = getNum(), querys = getNum();
    unsigned int **matrix = (unsigned int **)malloc(sizeof(unsigned int *) * nodes);
    for (unsigned int i = 0; i < nodes; i++)
    {
        matrix[i] = (unsigned int *)malloc(sizeof(unsigned int) * nodes);
        for (unsigned int j = 0; j < nodes; j++)
            matrix[i][j] = ~((unsigned int)0);
        matrix[i][i] = 0;
    }
    unsigned int from, to;
    for (unsigned int i = 0; i < flights; i++)
    {
        from = getNum() - 1;
        to = getNum() - 1;
        matrix[from][to] = getNum();
    }

    //floyd–Warshall
    for (unsigned int gobetween = 0; gobetween < nodes; gobetween++)
        for (from = 0; from < nodes; from++)
            for (to = 0; to < nodes; to++)
                if ((matrix[from][gobetween] != ~((unsigned int)0)) &&
                    (matrix[gobetween][to] != ~((unsigned int)0)) &&
                    (matrix[from][to] > matrix[from][gobetween] + matrix[gobetween][to]))
                    matrix[from][to] = matrix[from][gobetween] + matrix[gobetween][to];

    unsigned int minPrice, numPoss = 0;
    unsigned long long total = 0;
    for (unsigned int i = 0; i < querys; i++)
    {
        from = getNum() - 1;
        to = getNum() - 1;
        minPrice = ~((unsigned int)0);
        for (unsigned int hub = 0; hub < hubs; hub++)
            if ((matrix[from][hub] != ~((unsigned int)0)) &&
                (matrix[hub][to] != ~((unsigned int)0)) &&
                (minPrice > matrix[from][hub] + matrix[hub][to]))
                minPrice = matrix[from][hub] + matrix[hub][to];
        if (minPrice != ~((unsigned int)0))
        {
            total += minPrice;
            numPoss++;
        }
    }
    printf("%d\n%lld", numPoss, total);
}