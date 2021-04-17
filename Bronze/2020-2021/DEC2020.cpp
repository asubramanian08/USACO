//taken for real 3/3

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <iostream>
//#include <stdarg.h>
//#include <assert.h>
//#include <errno.h>
//#include <signal.h>
//#include <setjmp.h>
//_CRT_SECURE_NO_WARNINGS;
#define _max(a, b) (((a) > (b)) ? (a) : (b))
#define _min(a, b) (((a) < (b)) ? (a) : (b))
char *readStr(int size, int *endSize)
{
    char ch = getchar();
    char *str = (char *)malloc(sizeof(char) * (size + 1));
    int i = 0;
    while ((ch != ' ') && (ch != '\n'))
    {
        str[i] = ch;
        i++;
        ch = getchar();
    }
    str[i] = '\0';
    *endSize = i + 1;
    str = (char *)realloc(str, sizeof(char) * (i + 1));
    return str;
}
long long getNum()
{
    char ch = getchar();
    if (ch == '-')
        return -1 * getNum();
    else
    {
        long long total = ch - '0';
        ch = getchar();
        while ((ch != ' ') && (ch != '\n'))
        {
            total = total * 10 + ch - '0';
            ch = getchar();
        }
        return total;
    }
}

int compareInt(const void *p1, const void *p2)
{
    return *((unsigned int *)p1) - *((unsigned int *)p2);
}
void q1(void)
{
    unsigned int *nums = (unsigned int *)malloc(sizeof(unsigned int *) * 7);
    for (unsigned int i = 0; i < 7; i++)
        nums[i] = getNum();
    qsort(nums, 7, sizeof(unsigned int), compareInt);
    printf("%d %d %d\n", nums[0], nums[1], nums[6] - nums[0] - nums[1]);
}

unsigned int *petals;
bool is_avr(unsigned int start, unsigned int end, unsigned int avr)
{
    for (unsigned int i = start; i <= end; i++)
        if (petals[i] == avr)
            return true;
    return false;
}
void q2(void)
{
    unsigned int numOfFlowers = getNum(), avr = 0;
    petals = (unsigned int *)malloc(sizeof(unsigned int) * numOfFlowers);
    for (unsigned int i = 0; i < numOfFlowers; i++)
        avr += (petals[i] = getNum());
    avr /= numOfFlowers;

    unsigned int ans = 0, sum;
    for (unsigned int i = 0; i < numOfFlowers; i++)
    {
        sum = 0;
        for (unsigned int j = i; j < numOfFlowers; j++)
        {
            sum += petals[j];
            if (sum % (j - i + 1) == 0)
                ans += is_avr(i, j, sum / (j - i + 1));
        }
    }
    printf("%d\n", ans);
}

struct cow
{
    bool is_nor;
    bool stopped;
    unsigned long x;
    unsigned long y;
    unsigned long squares;
    unsigned int loc;
};
cow *cows;
bool willCross(unsigned int nor, unsigned int eas)
{
    return ((cows[nor].y <= cows[eas].y) && (cows[nor].x >= cows[eas].x));
}
int compareCow(const void *a, const void *b)
{
    cow *p1 = (cow *)a;
    cow *p2 = (cow *)b;
    if (p1->is_nor - p2->is_nor)
        return p1->is_nor - p2->is_nor;
    if (p1->is_nor)
        return p1->x - p2->x;
    return p1->y - p2->y;
}
int compareLoc(const void *p1, const void *p2)
{
    return ((cow *)p1)->loc - ((cow *)p2)->loc;
}
void q3(void)
{
    unsigned int numOfCows = getNum();
    cows = (cow *)malloc(sizeof(cow) * numOfCows);
    for (unsigned int i = 0; i < numOfCows; i++)
    {
        cows[i].is_nor = (getchar() == 'N');
        getchar(); //space
        cows[i].x = getNum();
        cows[i].y = getNum();
        cows[i].stopped = false;
        cows[i].loc = i;
    }
    qsort(cows, numOfCows, sizeof(cow), compareCow);
    unsigned int switchDir;
    for (switchDir = 0; cows[switchDir].is_nor == false; switchDir++)
        ; //find where it switches
    for (unsigned int i = 0; i < switchDir; i++)
        for (unsigned int j = switchDir; j < numOfCows; j++)
            if ((cows[i].stopped == false) && (cows[j].stopped == false) && (willCross(j, i)))
            {
                if (cows[j].x - cows[i].x < cows[i].y - cows[j].y)
                {
                    cows[j].squares = cows[i].y - cows[j].y;
                    cows[j].stopped = true;
                }
                else if (cows[j].x - cows[i].x > cows[i].y - cows[j].y)
                {
                    cows[i].squares = cows[j].x - cows[i].x;
                    cows[i].stopped = true;
                }
            }

    qsort(cows, numOfCows, sizeof(cow), compareLoc);
    for (unsigned int i = 0; i < numOfCows; i++)
    {
        if (!cows[i].stopped)
            printf("Infinity\n");
        else
            printf("%d\n", cows[i].squares);
    }
}

int main(void)
{
    //q1();
    //q2();
    q3();

    return 0;
}