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
#define _max(a,b) (((a) > (b)) ? (a) : (b))
#define _min(a,b) (((a) < (b)) ? (a) : (b))
#define getNum getNumInFile(&fp)
char* readStrInFile(FILE** fp, int size, int* endSize)
{
	char ch = fgetc(*fp);
	char* str = (char*)malloc(sizeof(char) * (size + 1));
	int i = 0;
	while ((ch != ' ') && (ch != '\n')) {
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
	else {
		long long total = ch - '0';
		ch = fgetc(*fp);
		while ((ch != ' ') && (ch != '\n')) {
			total = total * 10 + ch - '0';
			ch = fgetc(*fp);
		}
		return total;
	}
}

struct cow
{
	unsigned int start;
	unsigned int end;
	bool done;
};
int copmareCow(const void* p1, const void* p2)
{
	return ((cow*)p1)->end - ((cow*)p2)->end;
}
int copmareChick(const void* p1, const void* p2)
{
	return *((unsigned int*)p1) - *((unsigned int*)p2);
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfChickens = getNum;
	unsigned int numOfCows = getNum;
	unsigned int* chickens = (unsigned int*)malloc(sizeof(unsigned int) * numOfChickens);
	for (unsigned int i = 0; i < numOfChickens; i++)
		chickens[i] = getNum;
	cow * cows = (cow*)malloc(sizeof(cow) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].start = getNum;
		cows[i].end = getNum;
		cows[i].done = false;
	}
	fclose(fp);
	qsort(cows, numOfCows, sizeof(cow), copmareCow);
	qsort(chickens, numOfChickens, sizeof(unsigned int), copmareChick);
	unsigned int ans = 0;
	unsigned int start = 0;
	for (unsigned int i = 0; i < numOfChickens; i++) {
		while ((start < numOfCows) && (cows[start].end < chickens[i]))start++;
		while ((start < numOfCows) && (cows[start].done)) start++;
		if (start == numOfCows)
			break;
		for (unsigned int j = start; j < numOfCows; j++)
			if ((cows[j].start <= chickens[i]) && (cows[j].done == 0)) {
				ans++;
				cows[j].done = true;
				break;
			}
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCrosswalks = getNum;
	unsigned int inARow = getNum;
	unsigned int damaged = getNum;
	bool* isDamage = (bool*)calloc(numOfCrosswalks, sizeof(bool));
	for (unsigned int i = 0; i < damaged; i++)
		isDamage[getNum -  1] = true;
	fclose(fp);
	unsigned int least = 0;
	for (unsigned int i = 0; i < inARow; i++)
		least += isDamage[i];
	unsigned int curr = least;
	for (unsigned int i = inARow; i < numOfCrosswalks; i++) {
		curr += isDamage[i];
		curr -= isDamage[i - inARow];
		if (curr < least)
			least = curr;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", least);
	fclose(fp);
}

struct feild
{
	bool cantGo;
	bool cow;
};
feild* grid;
unsigned int cowsSoFar;
unsigned int sideLen;
unsigned int lowX = 1000, lowY = 1000, highX = 0, highY = 0;
void floodFill(unsigned int x, unsigned int y)
{
	if (grid[x * (2 * sideLen) + y].cantGo)
		return;
	if (grid[x * (2 * sideLen) + y].cow)
		cowsSoFar++;
	grid[x * (2 * sideLen) + y].cantGo = true;
	if ((x / 2 > lowX) && (grid[(x - 1) * (sideLen * 2) + y].cantGo == 0))
		floodFill(x - 2, y);
	if ((x / 2 < highX - 1) && (grid[(x + 1) * (sideLen * 2) + y].cantGo == 0))
		floodFill(x + 2, y);
	if ((y / 2 > lowY) && (grid[x * (sideLen * 2) + (y - 1)].cantGo == 0))
		floodFill(x, y - 2);
	if ((y / 2 < highY - 1) && (grid[x * (sideLen * 2) + (y + 1)].cantGo == 0))
		floodFill(x, y + 2);
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	sideLen = getNum;
	unsigned int numOfCows = getNum;
	unsigned int numOfRoads = getNum;
	grid = (feild*)calloc((sideLen * 2) * (sideLen * 2), sizeof(feild));
	unsigned int r1, c1, r2, c2;
	for (unsigned int i = 0; i < numOfRoads; i++) {
		r1 = getNum - 1; c1 = getNum - 1; r2 = getNum - 1; c2 = getNum - 1;
		grid[(r1 + r2) * (sideLen * 2) + (c1 + c2)].cantGo = true;
		if (r1 > highX)
			highX = r1;
		if (r1 < lowX)
			lowX = r1;
		if (r2 > highX)
			highX = r2;
		if (r2 < lowX)
			lowX = r2;

		if (c1 > highY)
			highY = c1;
		if (c1 < lowY)
			lowY = c1;
		if (c2 > highY)
			highY = c2;
		if (c2 < lowY)
			lowY = c2;
	}
	for (unsigned int i = 0; i < numOfCows; i++) {
		r1 = getNum - 1;
		c1 = getNum - 1;
		grid[(2 * r1) * (sideLen * 2) + (2 * c1)].cow = true;
		if (r1 > highX)
			highX = r1;
		if (r1 < lowX)
			lowX = r1;

		if (c1 > highY)
			highY = c1;
		if (c1 < lowY)
			lowY = c1;
	}
	fclose(fp);
	if (lowX != 0)
		lowX--;
	if (highX != sideLen)
		highX++;
	if (lowY != 0)
		lowY--;
	if (highY != sideLen)
		highY++;
	unsigned int numOfGroups = 0;
	unsigned int* groups = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	for (unsigned int i = lowX; i < highX; i++)
		for (unsigned int j = lowY; j < highY; j++) {
			cowsSoFar = 0;
			floodFill(i * 2, j * 2);
			if (cowsSoFar) {
				groups[numOfGroups] = cowsSoFar;
				numOfGroups++;
			}
		}
	unsigned int ans = 0;
	for (unsigned int i = 0; i < numOfGroups; i++)
		ans += (groups[i]) * (numOfCows - groups[i]);
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans / 2);
	fclose(fp);
}

int main(void)
{
	q1("helpcross.in", "helpcross.out");
	//q2("maxcross.in", "maxcross.out");
	//q3("countcross.in", "countcross.out");

	//system("pause");
	return 0;
}