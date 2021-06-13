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

int main(void)
{
    FILE *fp = fopen("teamwork.in", "r");
    unsigned int cows = getNum(&fp), maxGroup = getNum(&fp);
    unsigned int *skill = (unsigned int *)malloc(sizeof(unsigned int) * (cows + 1));
    unsigned int *DP = (unsigned int *)malloc(sizeof(unsigned int) * (cows + 1));
    skill[0] = 0;
    for (unsigned int i = 1; i <= cows; i++)
        skill[i] = getNum(&fp);
    fclose(fp);
    unsigned int maxInGroup, maxSkill;
    DP[0] = 0;
    for (unsigned int i = 1, group_sz; i <= cows; i++)
    {
        group_sz = maxSkill = maxInGroup = 0;
        while ((group_sz < i) && (group_sz < maxGroup))
        {
            maxInGroup = MAX(maxInGroup, skill[i - group_sz]);
            group_sz++;
            maxSkill = MAX(maxSkill, (maxInGroup * group_sz) + DP[i - group_sz]);
        }
        DP[i] = maxSkill;
    }
    fp = fopen("teamwork.out", "w");
    fprintf(fp, "%d", DP[cows]);
    fclose(fp);
    return 0;
}