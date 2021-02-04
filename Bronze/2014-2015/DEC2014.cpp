#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
#include <iostream>
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

struct point
{
	int x;
	int y;
};
#define findDist(point1, point2) (abs(point1.x - point2.x) + abs(point1.y - point2.y))
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfPoints = getNum;
	point* checkPoints = (point*)malloc(sizeof(point) * numOfPoints);
	for (unsigned int i = 0; i < numOfPoints; i++) {
		checkPoints[i].x = getNum;
		checkPoints[i].y = getNum;
	}
	fclose(fp);
	unsigned int totalDistance = findDist(checkPoints[0], checkPoints[1]);
	unsigned int canBeSkiped = numOfPoints - 1;
	unsigned int maxSaved = 0;
	unsigned int currSaved;
	for (unsigned int i = 1; i < canBeSkiped; i++) {
		currSaved = (findDist(checkPoints[i - 1], checkPoints[i]) + findDist(checkPoints[i], checkPoints[i + 1])) - 
			findDist(checkPoints[i - 1], checkPoints[i + 1]);
		if (currSaved > maxSaved)
			maxSaved = currSaved;
		totalDistance += findDist(checkPoints[i], checkPoints[i + 1]);
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u\n", totalDistance - maxSaved);
	fclose(fp);
}

struct loc
{
	unsigned int row;
	unsigned int col;
};
bool is_hora(unsigned int rows, unsigned int cols, unsigned int currRow, unsigned int currCol, bool* grid)
{
	return ((currCol == 0) || grid[currRow * cols + (currCol - 1)]) && //the one before
		((currCol + 2 < cols) && (grid[currRow * cols + (currCol + 1)] == 0) && (grid[currRow * cols + (currCol + 2)] == 0)); //ones after
}
bool is_vert(unsigned int rows, unsigned int cols, unsigned int currRow, unsigned int currCol, bool* grid)
{
	return ((currRow == 0) || grid[(currRow - 1) * cols + currCol]) && //the one before
		((currRow + 2 < rows) && (grid[(currRow + 1) * cols + currCol] == 0) && (grid[(currRow + 2) * cols + currCol] == 0)); //ones after
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int rows = getNum;
	unsigned int cols = getNum;
	bool* grid = (bool*)malloc(sizeof(bool) * rows * cols);
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++)
			grid[i * cols + j] = (fgetc(fp) == '#');
		fgetc(fp); //newline
	}
	fclose(fp);
	loc* starts = (loc*)malloc(sizeof(loc) * rows * cols);
	unsigned int numPut = 0;
	for (unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < cols; j++)
			if ((grid[i * cols + j] == 0) && (is_hora(rows, cols, i, j, grid) || is_vert(rows, cols, i, j, grid))) {
				starts[numPut].row = i + 1;
				starts[numPut].col = j + 1;
				numPut++;
			}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u\n", numPut);
	for (unsigned int i = 0; i < numPut; i++)
		fprintf(fp, "%u %u\n", starts[i].row, starts[i].col);
	fclose(fp);
}

void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	unsigned long long* speed = (unsigned long long*)malloc(sizeof(unsigned long long) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		getNum;
		speed[i] = getNum;
	}
	fclose(fp);
	unsigned int numOfGroups = 1;
	unsigned long long currLowSpeed = speed[numOfCows - 1];
	for (int i = numOfCows - 2; i >= 0; i--)
		if (speed[i] <= currLowSpeed) {
			numOfGroups++;
			if (speed[i] < currLowSpeed)
				currLowSpeed = speed[i];
		}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", numOfGroups);
	fclose(fp);
}

struct cow
{
	bool type;
	unsigned long weight;
};
struct range
{
	unsigned long end;
	bool type;
};
int compareFunc(const void* p1, const void* p2) {
	return ((cow*)p1)->weight - ((cow*)p2)->weight;
}
void q4(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	unsigned long startNum = getNum;
	unsigned long endNum = getNum;
	cow* prevCows = (cow*)malloc(sizeof(cow) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		prevCows[i].type = (fgetc(fp) == 'S');
		if (fgetc(fp) == 'S') //waste
			fgetc(fp);
		prevCows[i].weight = getNum;
	}
	fclose(fp);
	qsort(prevCows, numOfCows, sizeof(cow), compareFunc);
	unsigned int goUpTo = numOfCows - 1;
	range * ranges = (range*)malloc(sizeof(range) * numOfCows);
	for (unsigned int i = 0; i < goUpTo; i++) {
		if (ranges[i].type = prevCows[i].type)
			ranges[i].end = (prevCows[i].weight + prevCows[i + 1].weight) / 2;
		else
			ranges[i].end = (prevCows[i].weight + prevCows[i + 1].weight - 1) / 2;
	}
	ranges[goUpTo].type = prevCows[goUpTo].type;
	ranges[goUpTo].end = ~((unsigned long)0);
	unsigned int currRange = 0;
	while (startNum > ranges[currRange].end)
		currRange++;
	unsigned long numSpotted = 0;
	unsigned long start = startNum;
	while (endNum > ranges[currRange].end) {
		if (ranges[currRange].type)
			numSpotted += ranges[currRange].end - start + 1;
		start = ranges[currRange].end + 1;
		currRange++;
	}
	if (ranges[currRange].type)
		numSpotted += endNum - start + 1;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%lu", numSpotted);
	fclose(fp);
};

int main(void)
{
	//q1("marathon.in", "marathon.out");
	//q2("crosswords.in", "crosswords.out");
	//q3("cowjog.in", "cowjog.out");
	q4("learning.in", "learning.out");

	//system("pause");
	return 0;
}