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
struct inter
{
    bool is_start;
    long loc;
};
int compareFunc(const void *p1, const void *p2)
{
    return ((inter *)p1)->loc - ((inter *)p2)->loc;
}
int main(void)
{
    unsigned int moves = getNum();
    unsigned int minCoat = getNum();
    long currLoc = 0, change;
    inter *ranges = (inter *)malloc(sizeof(inter) * moves * 2);
    for (unsigned int i = 0; i < moves; i++)
    {
        ranges[i * 2].loc = currLoc;
        change = getNum();
        if (getchar() == 'R')
        {
            ranges[i * 2].is_start = true;
            currLoc += change;
            ranges[i * 2 + 1].is_start = false;
        }
        else
        {
            ranges[i * 2].is_start = false;
            currLoc -= change;
            ranges[i * 2 + 1].is_start = true;
        }
        getchar(); //newline
        ranges[i * 2 + 1].loc = currLoc;
    }
    qsort(ranges, moves * 2, sizeof(inter), compareFunc);
    unsigned int layOfPaint = 0;
    unsigned int points = moves * 2;
    unsigned int ans = 0;
    for (unsigned int i = 0; i < points; i++)
    {
        if (layOfPaint >= minCoat)
            ans += ranges[i].loc - ranges[i - 1].loc;
        if (ranges[i].is_start)
            layOfPaint++;
        else
            layOfPaint--;
    }
    printf("%d", ans);
    return 0;
}