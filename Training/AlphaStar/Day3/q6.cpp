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
struct linklist
{
    linklist *next;
    linklist *prev;
    unsigned int width;
    unsigned int height;
    unsigned int place;
};
linklist *nextLowNext(linklist *currLow)
{
    while ((currLow->next != NULL) && (currLow->height > currLow->next->height))
        currLow = currLow->next;
    return currLow;
}
linklist *nextLowPrev(linklist *currLow)
{
    while ((currLow->prev != NULL) && (currLow->height > currLow->prev->height))
        currLow = currLow->prev;
    return currLow;
}
linklist *nextLowBoth(linklist *currLow)
{
    while (true)
    {
        if ((currLow->next != NULL) && (currLow->next->height < currLow->height))
            currLow = currLow->next;
        else if ((currLow->prev != NULL) && (currLow->prev->height < currLow->height))
            currLow = currLow->prev;
        else
            return currLow;
    }
}
int main(void)
{
    unsigned int levels = getNum();
    linklist *top = NULL;
    linklist *temp;
    for (unsigned int i = 0; i < levels; i++)
    {
        temp = (linklist *)malloc(sizeof(linklist));
        temp->next = top;
        if (top)
            top->prev = temp;
        temp->prev = NULL;
        temp->width = getNum();
        temp->height = getNum();
        temp->place = i;
        top = temp;
    }
    unsigned long long *under = (unsigned long long *)malloc(sizeof(unsigned long long) * levels);
    linklist *lowest = top;
    temp = top->next;
    while (temp)
    {
        if (temp->height < lowest->height)
            lowest = temp;
        temp = temp->next;
    }
    unsigned long long gallonSoFar = 0;
    while (top->next)
    {
        under[lowest->place] = gallonSoFar + lowest->width;
        if (lowest->next == NULL)
        {
            gallonSoFar += (lowest->prev->height - lowest->height) * lowest->width;
            lowest->prev->next = NULL;
            temp = lowest;
            lowest = lowest->prev;
            lowest->width += temp->width;
            free(temp);
            lowest = nextLowPrev(lowest);
        }
        else if (lowest->prev == NULL)
        {
            gallonSoFar += (lowest->next->height - lowest->height) * lowest->width;
            top = lowest->next;
            lowest->next->prev = NULL;
            temp = lowest;
            lowest = lowest->next;
            lowest->width += temp->width;
            free(temp);
            lowest = nextLowNext(lowest);
        }
        else
        {
            gallonSoFar += (MIN(lowest->next->height, lowest->prev->height) - lowest->height) * lowest->width;
            lowest->next->prev = lowest->prev;
            lowest->prev->next = lowest->next;
            temp = lowest;
            if (lowest->next->height < lowest->prev->height)
                lowest = lowest->next;
            else
                lowest = lowest->prev;
            lowest->width += temp->width;
            free(temp);
            lowest = nextLowBoth(lowest);
        }
    }
    under[top->place] = gallonSoFar + top->width;
    for (unsigned int i = 0; i < levels; i++)
        printf("%lld\n", under[i]);
    return 0;
}