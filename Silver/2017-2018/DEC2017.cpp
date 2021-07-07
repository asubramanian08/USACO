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
#include <assert.h>
//#include <errno.h>
//#include <signal.h>
//#include <setjmp.h>
//_CRT_SECURE_NO_WARNINGS;
#define _max(a, b) (((a) > (b)) ? (a) : (b))
#define _min(a, b) (((a) < (b)) ? (a) : (b))
#define getNum getNumInFile(&fp)
char *readStrInFile(FILE **fp, int size, int *endSize)
{
    char ch = fgetc(*fp);
    char *str = (char *)malloc(sizeof(char) * (size + 1));
    int i = 0;
    while ((ch != ' ') && (ch != '\n'))
    {
        str[i] = ch;
        i++;
        ch = fgetc(*fp);
    }
    str[i] = '\0';
    *endSize = i + 1;
    str = (char *)realloc(str, sizeof(char) * (i + 1));
    return str;
}
long long getNumInFile(FILE **fp)
{
    char ch = fgetc(*fp);
    if (ch == '-')
        return -1 * getNumInFile(fp);
    else
    {
        long long total = ch - '0';
        ch = fgetc(*fp);
        while ((ch != ' ') && (ch != '\n'))
        {
            total = total * 10 + ch - '0';
            ch = fgetc(*fp);
        }
        return total;
    }
}

struct question
{
    unsigned int grade;
    bool active;
};
struct aver
{
    double average;
    unsigned int eatenTill;
};
int compQs(const void *p1, const void *p2)
{
    return (*((question **)p1))->grade - (*((question **)p2))->grade;
}
int compAver(const void *p1, const void *p2)
{
    if (((aver *)p2)->average != ((aver *)p1)->average)
    {
        if (((aver *)p2)->average > ((aver *)p1)->average)
            return 1;
        return -1;
    }
    return ((aver *)p1)->eatenTill - ((aver *)p2)->eatenTill;
}
void q1(const char *fin, const char *fout)
{
    FILE *fp = fopen(fin, "r");
    unsigned int numOfQs = getNum, sum = 0;
    question *qOrder = (question *)malloc(sizeof(question) * numOfQs);
    question **worstGrade = (question **)malloc(sizeof(question *) * numOfQs);
    for (unsigned int i = 0; i < numOfQs; i++)
    {
        sum += (qOrder[i].grade = getNum);
        qOrder[i].active = true;
        worstGrade[i] = &qOrder[i];
    }
    fclose(fp);
    qsort(worstGrade, numOfQs, sizeof(question *), compQs);
    unsigned int eatTill = numOfQs - 2, currWorstGrade = 0;
    aver *avereges = (aver *)malloc(sizeof(aver) * eatTill);
    for (unsigned int i = 0; i < eatTill; i++)
    {
        qOrder[i].active = false;
        while (worstGrade[currWorstGrade]->active == false)
            currWorstGrade++;
        sum -= qOrder[i].grade;
        avereges[i].eatenTill = i + 1;
        avereges[i].average = ((double)sum - (double)worstGrade[currWorstGrade]->grade) /
                              (double)((double)numOfQs - (i + 1) - 1);
    }
    qsort(avereges, eatTill, sizeof(aver), compAver);
    fp = fopen(fout, "w");
    for (unsigned int i = 0; (i < numOfQs) && (avereges[i].average == avereges[0].average); i++)
        fprintf(fp, "%d\n", avereges[i].eatenTill);
    fclose(fp);
}

//also in Starleague Part 1 lesson 2.2 q1
struct logType
{
    unsigned int day;
    unsigned int cow;
    int change;
};
int compLog(const void *p1, const void *p2)
{
    return ((logType *)p1)->day - ((logType *)p2)->day;
}
unsigned int *cows;
int compareFunc(const void *p1, const void *p2)
{
    return cows[*((unsigned int *)p2)] - cows[*((unsigned int *)p1)];
}
#define MAX_COWS 110000
inline bool works(unsigned int i, logType *logs, unsigned int *sortedCows)
{
    if (cows[logs[i].cow] == cows[sortedCows[0]])
    {                                                   // if the high
        if (cows[sortedCows[0]] == cows[sortedCows[1]]) //not the only one
            return true;
        if (cows[sortedCows[0]] + logs[i].change <= cows[sortedCows[1]]) //decends into the second
            return true;
    }
    else if (cows[logs[i].cow] + logs[i].change >= cows[sortedCows[0]]) //beat the first
        return true;
    return false;
}
void q2(const char *fin, const char *fout)
{
    FILE *fp = fopen(fin, "r");
    unsigned int numOfLogs = getNum;
    unsigned int startMilk = getNum;
    logType *logs = (logType *)malloc(sizeof(logType) * numOfLogs);
    for (unsigned int i = 0; i < numOfLogs; i++)
    {
        logs[i].day = getNum;
        logs[i].cow = getNum + MAX_COWS;
        if (fgetc(fp) == '-')
            logs[i].change = -1 * getNum;
        else
            logs[i].change = getNum;
    }
    fclose(fp);
    qsort(logs, numOfLogs, sizeof(logType), compLog);
    unsigned int numOfCows = 1;
    for (unsigned int i = 0; i < numOfLogs; i++)
        if (logs[i].cow >= MAX_COWS)
        {
            for (unsigned int j = i + 1; j < numOfLogs; j++)
                if (logs[i].cow == logs[j].cow)
                    logs[j].cow = numOfCows;
            logs[i].cow = numOfCows;
            numOfCows++;
        }
    cows = (unsigned int *)malloc(sizeof(unsigned int) * numOfCows);
    unsigned int *sortedCows = (unsigned int *)malloc(sizeof(unsigned int) * numOfCows);
    for (unsigned int i = 0; i < numOfCows; i++)
    {
        cows[i] = startMilk;
        sortedCows[i] = i;
    }
    unsigned int ans = 0;
    for (unsigned int i = 0; i < numOfLogs; i++)
        if (logs[i].change != 0)
        {
            if (works(i, logs, sortedCows))
            {
                cows[logs[i].cow] += logs[i].change;
                qsort(sortedCows, numOfCows, sizeof(unsigned int), compareFunc);
                ans++;
            }
            else
            {
                cows[logs[i].cow] += logs[i].change;
                qsort(sortedCows, numOfCows, sizeof(unsigned int), compareFunc);
            }
        }
    fp = fopen(fout, "w");
    fprintf(fp, "%d", ans);
    fclose(fp);
}

struct shuffle
{
    unsigned int recived;
    shuffle *next;
};
void apllyTakeBack(shuffle *curr)
{
    while (curr->recived == 0)
    {
        curr = curr->next;
        curr->recived--;
    }
}
void q3(const char *fin, const char *fout)
{
    FILE *fp = fopen(fin, "r");
    unsigned int numOfShuffle = getNum;
    shuffle *spots = (shuffle *)calloc(numOfShuffle, sizeof(shuffle));
    for (unsigned int i = 0; i < numOfShuffle; i++)
    {
        spots[i].next = &spots[getNum - 1];
        spots[i].next->recived++;
    }
    fclose(fp);
    bool *notGiven = (bool *)malloc(sizeof(bool) * numOfShuffle);
    for (unsigned int i = 0; i < numOfShuffle; i++)
        notGiven[i] = !spots[i].recived;
    for (unsigned int i = 0; i < numOfShuffle; i++)
        if (notGiven[i])
            apllyTakeBack(&spots[i]);
    unsigned int ans = 0;
    for (unsigned int i = 0; i < numOfShuffle; i++)
        if (spots[i].recived != 0)
            ans++;
    fp = fopen(fout, "w");
    fprintf(fp, "%d", ans);
    fclose(fp);
}

int main(void)
{
    //q1("homework.in", "homework.out");
    q2("measurement.in", "measurement.out");
    //q3("shuffle.in", "shuffle.out");
}