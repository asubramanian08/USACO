#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
unsigned int *collected;
unsigned int *goTo;
unsigned int stalls;
bool *beenTo;
struct stack
{
    unsigned int stall;
    stack *next;
};
void findCycles(unsigned int currPos)
{
    memset(beenTo, 0, stalls * sizeof(bool));
    stack *cycle = NULL;
    stack *temp;
    while ((!beenTo[currPos]) && (collected[currPos] == 0))
    {
        beenTo[currPos] = true;
        temp = (stack *)malloc(sizeof(stack));
        temp->stall = currPos;
        temp->next = cycle;
        cycle = temp;
        currPos = goTo[currPos];
    }
    if (beenTo[currPos])
    {
        unsigned int cycleLen = 0;
        for (temp = cycle; temp->stall != currPos; cycleLen++)
            temp = temp->next;
        cycleLen++;
        for (unsigned int i = 1; cycle != NULL; i++)
        {
            collected[cycle->stall] = MAX(i, cycleLen);
            temp = cycle;
            cycle = cycle->next;
            free(temp);
        }
    }
    else
        for (unsigned int i = 1 + collected[currPos]; cycle != NULL; i++)
        {
            collected[cycle->stall] = i;
            temp = cycle;
            cycle = cycle->next;
            free(temp);
        }
}
int main(void)
{
    stalls = getNum();
    goTo = (unsigned int *)malloc(sizeof(unsigned int) * stalls);
    for (unsigned int i = 0; i < stalls; i++)
        goTo[i] = getNum() - 1;

    collected = (unsigned int *)calloc(stalls, sizeof(unsigned int));
    beenTo = (bool *)malloc(stalls * sizeof(bool));
    for (unsigned int i = 0; i < stalls; i++)
    {
        if (collected[i] == 0)
            findCycles(i);
        printf("%d\n", collected[i]);
    }
    return 0;
}