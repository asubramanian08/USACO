#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
unsigned long long getNum()
{
    unsigned long long total = 0;
    char ch = getchar();
    while ((ch != ' ') && (ch != '\n'))
    {
        total = (total * 10) + (ch - '0');
        ch = getchar();
    }
    return total;
}
int compareFunc(const void *p1, const void *p2)
{
    return *((double *)p1) - *((double *)p2);
}
int main(void)
{
    double slowings = getNum();
    double *times = (double *)malloc(sizeof(double) * slowings);
    double *dists = (double *)malloc(sizeof(double) * slowings);
    unsigned int totalTimes = 0, totalDists = 0;
    for (unsigned int i = 0; i < slowings; i++)
        if (getchar() == 'T')
        {
            getchar();
            times[totalTimes] = getNum();
            totalTimes++;
        }
        else
        {
            getchar();
            dists[totalDists] = getNum();
            totalDists++;
        }
    qsort(times, totalTimes, sizeof(double), compareFunc);
    qsort(dists, totalDists, sizeof(double), compareFunc);
    unsigned int currTime = 0, currDists = 0;
    double timePassed = 0;
    double distPassed = 0;
    for (double speed = 1; speed <= slowings; speed++)
    {
        if ((currDists == totalDists) ||
            ((currTime != totalTimes) &&
             ((dists[currDists] - distPassed) * speed > times[currTime] - timePassed)))
        {
            distPassed += (times[currTime] - timePassed) / speed;
            timePassed = times[currTime];
            currTime++;
        }
        else
        {
            timePassed += (dists[currDists] - distPassed) * speed;
            distPassed = dists[currDists];
            currDists++;
        }
    }
    timePassed += ((double)1000 - distPassed) * (slowings + (double)1);
    unsigned long long ans = (unsigned long long)timePassed;
    if (timePassed - (double)ans >= 0.5)
        ans++;
    printf("%lld", ans);
    return 0;
}