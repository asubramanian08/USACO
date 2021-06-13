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
struct point
{
    int x;
    int y;
};
unsigned int numfjMoves, numBessMoves;
point *fjLocs;
point *bessLocs;
unsigned long **minCost;
void minToGetHere(unsigned int currFj, unsigned int currBess)
{
    unsigned long self =
        (abs(fjLocs[currFj].x - bessLocs[currBess].x) * abs(fjLocs[currFj].x - bessLocs[currBess].x)) +
        (abs(fjLocs[currFj].y - bessLocs[currBess].y) * abs(fjLocs[currFj].y - bessLocs[currBess].y));
    if (currFj > 0)
    {
        if (currBess > 0)
            minCost[currFj][currBess] = MIN(minCost[currFj - 1][currBess], MIN(minCost[currFj][currBess - 1], minCost[currFj - 1][currBess - 1])) + self;
        else
            minCost[currFj][currBess] = minCost[currFj - 1][currBess] + self;
    }
    else
    {
        if (currBess > 0)
            minCost[currFj][currBess] = minCost[currFj][currBess - 1] + self;
        else
            minCost[currFj][currBess] = 0;
    }
}
int main(void)
{
    numfjMoves = getNum() + 1;
    numBessMoves = getNum() + 1;
    fjLocs = (point *)malloc(sizeof(point) * numfjMoves);
    bessLocs = (point *)malloc(sizeof(point) * numBessMoves);
    minCost = (unsigned long **)malloc(sizeof(unsigned long *) * numfjMoves);
    //point currFJ, currBess;
    fjLocs[0].x = getNum();
    fjLocs[0].y = getNum();
    minCost[0] = (unsigned long *)malloc(sizeof(unsigned long) * numBessMoves);
    bessLocs[0].x = getNum();
    bessLocs[0].y = getNum();
    char dir;
    for (unsigned int i = 1; i < numfjMoves; i++)
    {
        minCost[i] = (unsigned long *)malloc(sizeof(unsigned long) * numBessMoves);
        dir = getchar();
        if (dir == 'N')
        {
            fjLocs[i].x = fjLocs[i - 1].x;
            fjLocs[i].y = fjLocs[i - 1].y + 1;
        }
        else if (dir == 'S')
        {
            fjLocs[i].x = fjLocs[i - 1].x;
            fjLocs[i].y = fjLocs[i - 1].y - 1;
        }
        else if (dir == 'E')
        {
            fjLocs[i].x = fjLocs[i - 1].x + 1;
            fjLocs[i].y = fjLocs[i - 1].y;
        }
        else //dir == 'W'
        {
            fjLocs[i].x = fjLocs[i - 1].x - 1;
            fjLocs[i].y = fjLocs[i - 1].y;
        }
    }
    getchar(); //newline
    for (unsigned int i = 1; i < numBessMoves; i++)
    {
        dir = getchar();
        if (dir == 'N')
        {
            bessLocs[i].x = bessLocs[i - 1].x;
            bessLocs[i].y = bessLocs[i - 1].y + 1;
        }
        else if (dir == 'S')
        {
            bessLocs[i].x = bessLocs[i - 1].x;
            bessLocs[i].y = bessLocs[i - 1].y - 1;
        }
        else if (dir == 'E')
        {
            bessLocs[i].x = bessLocs[i - 1].x + 1;
            bessLocs[i].y = bessLocs[i - 1].y;
        }
        else //dir == 'W'
        {
            bessLocs[i].x = bessLocs[i - 1].x - 1;
            bessLocs[i].y = bessLocs[i - 1].y;
        }
    }
    getchar(); //newline

    for (unsigned int i = 0; i < numfjMoves; i++)
        for (unsigned int j = 0; j < numBessMoves; j++)
            minToGetHere(i, j);
    printf("%lu", minCost[numfjMoves - 1][numBessMoves - 1]);
    return 0;
}