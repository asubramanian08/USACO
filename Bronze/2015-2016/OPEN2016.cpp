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

int compFunc(const void* p1, const void* p2)
{
	return *((unsigned int*)p1) - *((unsigned int*)p2);
}
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfDia = getNum;
	unsigned int max_Dist = getNum;
	unsigned int* sizes = (unsigned int*)malloc(sizeof(unsigned int) * numOfDia);
	for (unsigned int i = 0; i < numOfDia; i++)
		sizes[i] = getNum;
	fclose(fp);
	qsort(sizes, numOfDia, sizeof(unsigned int), compFunc);
	unsigned int low = 0;
	unsigned int max = 0;
	for (unsigned int high = 1; high < numOfDia; high++) {
		while (sizes[high] - sizes[low] > max_Dist)
			low++;
		if (high - low > max)
			max = high - low;
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", max + 1);
	fclose(fp);
}

struct match
{
	unsigned int type;
	bool* grid;
};
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	int sideLen = getNum;
	unsigned int numOfPeicies = getNum;
	bool* origianl = (bool*)malloc(sizeof(bool) * sideLen * sideLen);
	for (unsigned int i = 0; i < sideLen; i++) {
		for (unsigned int j = 0; j < sideLen; j++)
			origianl[i * sideLen + j] = (fgetc(fp) == '#');
		fgetc(fp); //newLine
	}
	bool** peices = (bool**)malloc(sizeof(bool*) * numOfPeicies);
	for (unsigned int i = 0; i < numOfPeicies; i++) {
		peices[i] = (bool*)malloc(sizeof(bool) * sideLen * sideLen);
		for (unsigned int j = 0; j < sideLen; j++) {
			for (unsigned int k = 0; k < sideLen; k++)
				peices[i][j * sideLen + k] = (fgetc(fp) == '#');
			fgetc(fp); //newLine
		}
	}
	fclose(fp);
	fp = fopen(fpOut, "w");
	unsigned int maxVersions = 0;
	bool works;
	for (unsigned int i = 0; i < numOfPeicies; i++) { //first grid
		for (unsigned int j = i + 1; j < numOfPeicies; j++) { //second grid
			for (int x1change = 1 - sideLen; x1change < sideLen; x1change++) { //            Pick
				for (int y1change = 1 - sideLen; y1change < sideLen; y1change++) {//         x and
					for (int x2change = 1 - sideLen; x2change < sideLen; x2change++) {//     y change
						for (int y2change = 1 - sideLen; y2change < sideLen; y2change++) {// on both grids
							//go through grid
							works = true;
							for (int x = 0; x < sideLen; x++) {
								for (int y = 0; y < sideLen; y++) {
									if (peices[i][x * sideLen + y])
										if ((x + x1change < 0) || (x + x1change >= sideLen) || (y + y1change < 0) || (y + y1change >= sideLen)) {
											works = false;
											break;
										}
									if (peices[j][x * sideLen + y])
										if ((x + x2change < 0) || (x + x2change >= sideLen) || (y + y2change < 0) || (y + y2change >= sideLen)) {
											works = false;
											break;
										}
									bool type1 = ((x - x1change >= 0) && (x - x1change < sideLen) && (y - y1change >= 0) && (y - y1change < sideLen)) && (peices[i][(x - x1change) * sideLen + (y - y1change)]);
									bool type2 = ((x - x2change >= 0) && (x - x2change < sideLen) && (y - y2change >= 0) && (y - y2change < sideLen)) && (peices[j][(x - x2change) * sideLen + (y - y2change)]);
									if((type1 == type2) && type1){
										works = false;
										break;
									}
									if (origianl[x * sideLen + y] != (type1 || type2)) {
										works = false;
										break;
									}
								}
								if (!works)
									break;
							}
							if (works) {
								fprintf(fp, "%d %d", i + 1, j + 1);
								return;
							}
						}
					}
				}
			}
		}
	}
	fclose(fp);
}

struct point
{
	unsigned int x;
	unsigned int y;
	unsigned int cowNum;
};
int compX(const void* p1, const void* p2)
{
	return ((point*)p1)->x - ((point*)p2)->x;
}
int compY(const void* p1, const void* p2)
{
	return ((point*)p1)->y - ((point*)p2)->y;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	point* xFirst = (point*)malloc(sizeof(point) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		xFirst[i].x = getNum;
		xFirst[i].y = getNum;
		xFirst[i].cowNum = i;
	}
	fclose(fp);

	qsort(xFirst, numOfCows, sizeof(point), compX);
	point* yFirst = (point*)malloc(sizeof(point) * numOfCows);
	memcpy(yFirst, xFirst, sizeof(point) * numOfCows);
	qsort(yFirst, numOfCows, sizeof(point), compY);

	unsigned int min;
	if (xFirst[numOfCows - 1].cowNum == yFirst[numOfCows - 1].cowNum)
		min = (xFirst[numOfCows - 2].x - xFirst[0].x) * (yFirst[numOfCows - 2].y - yFirst[0].y);
	else if (xFirst[numOfCows - 1].cowNum == yFirst[0].cowNum)
		min = (xFirst[numOfCows - 2].x - xFirst[0].x) * (yFirst[numOfCows - 1].y - yFirst[1].y);
	else
		min = (xFirst[numOfCows - 2].x - xFirst[0].x) * (yFirst[numOfCows - 1].y - yFirst[0].y);

	if (xFirst[0].cowNum == yFirst[numOfCows - 1].cowNum) {
		if ((xFirst[numOfCows - 1].x - xFirst[1].x) * (yFirst[numOfCows - 2].y - yFirst[0].y) < min)
			min = (xFirst[numOfCows - 1].x - xFirst[1].x) * (yFirst[numOfCows - 2].y - yFirst[0].y);
	}
	else if (xFirst[0].cowNum == yFirst[0].cowNum) {
		if ((xFirst[numOfCows - 1].x - xFirst[1].x) * (yFirst[numOfCows - 1].y - yFirst[1].y) < min)
			min = (xFirst[numOfCows - 1].x - xFirst[1].x) * (yFirst[numOfCows - 1].y - yFirst[1].y);
	}
	else {
		if ((xFirst[numOfCows - 1].x - xFirst[1].x) * (yFirst[numOfCows - 1].y - yFirst[0].y) < min)
			min = (xFirst[numOfCows - 1].x - xFirst[1].x) * (yFirst[numOfCows - 1].y - yFirst[0].y);
	}

	if ((yFirst[0].cowNum != xFirst[0].cowNum) && (yFirst[0].cowNum != xFirst[numOfCows - 1].cowNum)) {
		if ((xFirst[numOfCows - 1].x - xFirst[0].x) * (yFirst[numOfCows - 1].y - yFirst[1].y) < min)
			min = (xFirst[numOfCows - 1].x - xFirst[0].x) * (yFirst[numOfCows - 1].y - yFirst[1].y);
	}

	if ((yFirst[numOfCows - 1].cowNum != xFirst[0].cowNum) && (yFirst[numOfCows - 1].cowNum != xFirst[numOfCows - 1].cowNum)) {
		if ((xFirst[numOfCows - 1].x - xFirst[0].x) * (yFirst[numOfCows - 2].y - yFirst[0].y) < min)
			min = (xFirst[numOfCows - 1].x - xFirst[0].x) * (yFirst[numOfCows - 2].y - yFirst[0].y);
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", min);
	fclose(fp);
}

int main(void)
{
	//q1("diamond.in", "diamond.out");
	q2("bcs.in", "bcs.out");
	//q3("reduce.in", "reduce.out");

	//system("pause");
	return 0;
}