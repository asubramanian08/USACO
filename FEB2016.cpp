#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
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

void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int x = getNum;
	unsigned int y = getNum;
	unsigned int m = getNum;
	fclose(fp);
	unsigned int max = (m / x) * x;
	unsigned int numOfX = m / x;
	while ((max < m) && (numOfX != 0)) {
		numOfX--;
		if (max < numOfX * x + (((m - (numOfX * x)) / y) * y))
			max = numOfX * x + (((m - (numOfX * x)) / y) * y);
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", max);
	fclose(fp);
}

void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfBarns = getNum;
	unsigned int* cowsInBarn = (unsigned int*)malloc(sizeof(unsigned int) * numOfBarns);
	for (unsigned int i = 0; i < numOfBarns; i++)
		cowsInBarn[i] = getNum;
	fclose(fp);
	unsigned int currVal = 0;
	unsigned int numOfCows = 0;
	for (int i = numOfBarns - 1; i >= 0; i--) {
		currVal += numOfCows;
		numOfCows += cowsInBarn[i];
	}
	unsigned int least = currVal;
	unsigned int upTo = numOfBarns - 1;
	for (int currExit = numOfBarns - 1; currExit >= 1; currExit--) {
		currVal += numOfCows - (cowsInBarn[currExit] * numOfBarns);
		if (currVal < least)
			least = currVal;
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", least);
	fclose(fp);
}

struct point
{
	int x;
	int y;
};
int byX(const void* p1, const void* p2)
{
	return ((point*)p1)->x - ((point*)p2)->x;
}
int byY(const void* p1, const void* p2)
{
	return ((point*)p1)->y - ((point*)p2)->y;
}
#define _max(a,b) (((a) > (b)) ? (a) : (b))
#define _min(a,b) (((a) < (b)) ? (a) : (b))
void q3(const char* fpIn, const char* fpOut)
{
	/*FILE* fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	getNum;
	point* cows = (point*)malloc(sizeof(point) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].x = getNum;
		cows[i].y = getNum;
	}
	fclose(fp);
	qsort(cows, numOfCows, sizeof(point), byX);
	int bestXval = 0;
	unsigned int minDiff = ~(unsigned int)0;
	unsigned int currX;
	for (unsigned int i = 0; i < numOfCows;) {
		currX = cows[i].x;
		while ((cows[i].x == currX) && (i < numOfCows))
			i++;
		if (_max(i, numOfCows - i) - _min(i, numOfCows - i) < minDiff) {
			minDiff = _max(i, numOfCows - i) - _min(i, numOfCows - i);
			bestXval = cows[i - 1].x + 1;
		}
	}
	qsort(cows, numOfCows, sizeof(point), byY);
	int bestYval = 0;
	minDiff = ~(unsigned int)0;
	unsigned int currY;
	for (unsigned int i = 0; i < numOfCows;) {
		currY = cows[i].y;
		while ((cows[i].y == currY) && (i < numOfCows))
			i++;
		if (_max(i, numOfCows - i) - _min(i, numOfCows - i) < minDiff) {
			minDiff = _max(i, numOfCows - i) - _min(i, numOfCows - i);
			bestYval = cows[i - 1].y + 1;
		}
	}
	unsigned int sections[4] = { 0 };
	for (unsigned int i = 0; i < numOfCows; i++) {
		sections[2 * (cows[i].x > bestXval) + (cows[i].y > bestYval)]++;
	}
	unsigned int max = _max(_max(sections[0], sections[1]), _max(sections[2], sections[3]));
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", max);
	fclose(fp);*/
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	unsigned int B = getNum;
	unsigned int* X = (unsigned int*)calloc(B, sizeof(unsigned int));
	unsigned int* Y = (unsigned int*)calloc(B, sizeof(unsigned int));
	point* cows = (point*)malloc(sizeof(point) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].x = getNum;
		X[cows[i].x]++;
		cows[i].y = getNum;
		Y[cows[i].y]++;
	}
	fclose(fp);
	int bestXval = 0;
	unsigned int minDiff = ~(unsigned int)0;
	unsigned int passedSoFar = 0;
	for (unsigned int i = 0; i < B; i++) {
		passedSoFar += X[i];
		if (_max(passedSoFar, numOfCows - passedSoFar) - _min(passedSoFar, numOfCows - passedSoFar) < minDiff) {
			minDiff = _max(passedSoFar, numOfCows - passedSoFar) - _min(passedSoFar, numOfCows - passedSoFar);
			bestXval = i + 1;
		}
	}

	int bestYval = 0;
	minDiff = ~(unsigned int)0;
	passedSoFar = 0;
	for (unsigned int i = 0; i < B; i++) {
		passedSoFar += Y[i];
		if (_max(passedSoFar, numOfCows - passedSoFar) - _min(passedSoFar, numOfCows - passedSoFar) < minDiff) {
			minDiff = _max(passedSoFar, numOfCows - passedSoFar) - _min(passedSoFar, numOfCows - passedSoFar);
			bestYval = i + 1;
		}
	}

	unsigned int sections[4] = { 0 };
	for (unsigned int i = 0; i < numOfCows; i++) {
		sections[2 * (cows[i].x > bestXval) + (cows[i].y > bestYval)]++;
	}
	unsigned int max = _max(_max(sections[0], sections[1]), _max(sections[2], sections[3]));
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", max);
	fclose(fp);
}

int main(void)
{
	//q1("pails.in", "pails.out");
	//q2("cbarn.in", "cbarn.out");
	q3("balancing.in", "balancing.out");

	system("pause");
	return 0;
}