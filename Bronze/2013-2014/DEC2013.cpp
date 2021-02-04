#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <stdarg.h>
//#include <assert.h>
//#include <errno.h> 
//#include <signal.h> 
//#include <setjmp.h>
//_CRT_SECURE_NO_WARNINGS;
#define getNum getNumInFile(&fp)
char* readStrInFile(FILE** fp, int size, int* endSize)
{
	char ch = fgetc(*fp);
	char* str = (char*)malloc(sizeof(char) * (size + 1));
	int i = 0;
	while ((ch != ' ') && (ch != '\n'))
	{
		str[i] = ch;
		i++;
		ch = fgetc(*fp);
	}
	str[i] = '\0';
	*endSize = i + 1;
	str = (char*)realloc(str, sizeof(char) * (i + 1));
	return str;
}
long long getNumInFile(FILE * *fp)
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

int compNames(const void* p1, const void* p2)
{
	return strcmp(*(const char**)p1, *(const char**)p2);
}
int compareGroups(const void* p1, const void* p2)
{
	const char** a = *(const char***)p1;
	const char** b = *(const char***)p2;
	int retrurnVal = strcmp(a[0], b[0]);
	if (retrurnVal != 0)
		return retrurnVal;
	if ((retrurnVal = strcmp(a[1], b[1])) != 0)
		return retrurnVal;
	return strcmp(a[2], b[2]);
}
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfGroups = getNum;
	char*** list = (char***)malloc(sizeof(char**) * numOfGroups);
	int junk = 0;
	for (unsigned int i = 0; i < numOfGroups; i++) {
		list[i] = (char**)malloc(sizeof(char*) * 3);
		for (unsigned int j = 0; j < 3; j++)
			list[i][j] = readStrInFile(&fp, 10, &junk);
		qsort(list[i], 3, sizeof(char*), compNames);
	}
	fclose(fp);
	qsort(list, numOfGroups, sizeof(char**), compareGroups);
	unsigned int highestNum = 0;
	unsigned int currNum = 0;
	char** currGroup = list[0];
	for (unsigned int i = 0; i < numOfGroups; i++) {
		if (compareGroups(&currGroup, &list[i]) == 0)
			currNum++;
		else {
			currGroup = list[i];
			if (highestNum < currNum)
				highestNum = currNum;
			currNum = 1;
		}
	}
	if (highestNum < currNum)
		highestNum = currNum;
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", highestNum);
	fclose(fp);
}

int compareFunc(const void* p1, const void* p2)
{
	return *((int*)p1) - *((int*)p2);
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	unsigned int* cowLoc = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++)
		cowLoc[i] = getNum;
	fclose(fp);
	qsort(cowLoc, numOfCows, sizeof(unsigned int), compareFunc);
	unsigned long ans = 0;
	unsigned int i = 0, k = 0, j = 0, lowerBound, upperBound;
	for (i = 0; i < numOfCows; i++) {
		for (j = i + 1; j < numOfCows; j++) {
			lowerBound = cowLoc[j] + (cowLoc[j] - cowLoc[i]);
			if (lowerBound > cowLoc[numOfCows - 1])
				break;
			upperBound = cowLoc[j] +  (2 * (cowLoc[j] - cowLoc[i]));
			for (k = j + 1; k < numOfCows; k++) {
				if (cowLoc[k] > upperBound)
					break;
				else if (cowLoc[k] >= lowerBound)
					ans++;
			}
		}
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%lu", ans);
	fclose(fp);
}

struct point
{
	unsigned int x;
	unsigned int y;
};
int compareHoles(const void* p1, const void* p2)
{
	if (((point*)p1)->y != ((point*)p2)->y)
		return ((point*)p1)->y - ((point*)p2)->y;
	return ((point*)p1)->x - ((point*)p2)->x;
}
bool check(point* holes, unsigned int* pairs, unsigned int numOfCows)
{
	unsigned int curr;
	for (unsigned int i = 0; i < numOfCows; i++) {
		curr = i;
		while (true) {
			curr = pairs[curr] - 1; //go throguh hole
			if (!((curr + 1< numOfCows) && (holes[curr + 1].y == holes[curr].y))) 
				break;
			else
				curr++; //walk to next hole
			if (curr == i)
				return 1;
		}
	}
	return 0;
}
unsigned int recursave(unsigned int numOfCows, unsigned int currCow, unsigned int* pairs, point* holes)
{
	if (numOfCows == currCow)
		return check(holes, pairs, numOfCows);
	if (pairs[currCow])
		return recursave(numOfCows, currCow + 1, pairs, holes);
	unsigned int total = 0;
	for (unsigned int i = currCow + 1; i < numOfCows; i++) {
		if (pairs[i] == 0) {
			pairs[currCow] = i + 1;
			pairs[i] = currCow + 1;
			total += recursave(numOfCows, currCow + 1, pairs, holes);
			pairs[i] = 0;
			pairs[currCow] = 0;
		}
	}
	return total;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfHoles = getNum;
	point* holes = (point*)malloc(sizeof(point) * numOfHoles);
	for (unsigned int i = 0; i < numOfHoles; i++) {
		holes[i].x = getNum;
		holes[i].y = getNum;
	}
	fclose(fp);
	qsort(holes, numOfHoles, sizeof(point), compareHoles);
	unsigned int* pairs = (unsigned int*)malloc(sizeof(unsigned int) * numOfHoles);
	memset(pairs, 0, sizeof(unsigned int) * numOfHoles);
	unsigned int ans = recursave(numOfHoles, 0, pairs, holes);
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", ans);
	fclose(fp);
}

int main(void)
{
	//q1("records.in", "records.out");
	//q2("baseball.in", "baseball.out");
	q3("wormhole.in", "wormhole.out");
}