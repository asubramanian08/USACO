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
struct cow
{
    unsigned int weight;
    unsigned int strength;
};
/*int compare(const void *p1, const void *p2)
{
    return (((cow *)p1)->strength - ((cow *)p1)->weight) -
           (((cow *)p2)->strength - ((cow *)p2)->weight);
}*/
int compare(const void *p1, const void *p2)
{
    return ((cow *)p1)->strength - ((cow *)p2)->strength;
}
int main(void)
{
    FILE *fp = fopen("tower.in", "r");
    unsigned int numOfCows = getNum(&fp);
    cow *cows = (cow *)malloc(sizeof(cow) * numOfCows);
    for (unsigned int i = 0; i < numOfCows; i++)
    {
        cows[i].weight = getNum(&fp);
        cows[i].strength = getNum(&fp);
    }
    fclose(fp);
    qsort(cows, numOfCows, sizeof(cow), compare);
    unsigned int *minWeight = (unsigned int *)malloc(sizeof(unsigned int) * (numOfCows + 1));
    memset(minWeight, ~0, sizeof(unsigned int) * (numOfCows + 1));
    minWeight[0] = 0;
    unsigned int nextHeight = 1;

    for (unsigned int i = 0; i < numOfCows; i++)
    {
        for (unsigned int j = nextHeight; j > 0; j--)
            if (minWeight[j - 1] + cows[i].weight <= cows[i].strength)
                minWeight[j] = MIN(minWeight[j], minWeight[j - 1] + cows[i].weight);
        if (minWeight[nextHeight] != ~0)
            nextHeight++;
    }
    fp = fopen("tower.out", "w");
    fprintf(fp, "%d", nextHeight - 1);
    fclose(fp);
    return 0;
}