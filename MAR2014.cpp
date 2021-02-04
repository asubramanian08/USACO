#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

struct key
{
	unsigned int cow;
	unsigned int goes;
};
int compFunc(const void* p1, const void* p2)
{
	return ((key*)p1)->cow - ((key*)p2)->cow;
}
unsigned int cycle(bool* used, unsigned int* cowPos, key* changeTo, unsigned int currPlace)
{
	unsigned int numLooped;
	unsigned int currNum = cowPos[currPlace];
	used[currPlace] = true;
	cowPos[currPlace] = 0;
	for (numLooped = 1; cowPos[changeTo[currNum - 1].goes]; numLooped++) {
		currPlace = changeTo[currNum - 1].goes;
		currNum = cowPos[currPlace];
		used[currPlace] = true;
		cowPos[currPlace] = 0;
	}
	return numLooped;
}
void q1(const char* fpIn, const char* fpOut)
{
	
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	unsigned int* original = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++)
		original[i] = getNum;
	key* changeTo = (key*)malloc(sizeof(key) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		changeTo[i].cow = getNum;
		changeTo[i].goes = i;
	}
	fclose(fp);
	qsort(changeTo, numOfCows, sizeof(key), compFunc);
	unsigned int* waste = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	bool* used = (bool*)calloc(numOfCows, sizeof(bool));
	unsigned int numOfDiffCycles = 0;
	unsigned int highest = 0; unsigned int curr;
	for(unsigned int i = 0; i < numOfCows; i++)
		if (!used[i]) {
			numOfDiffCycles++;
			memcpy(waste, original, sizeof(unsigned int) * numOfCows);
			curr = cycle(used, waste, changeTo, i);
			if (curr > highest)
				highest = curr;
			if (curr <= 1)
				numOfDiffCycles--;
		}
	fp = fopen(fpOut, "w");
	if (highest <= 1) {
		fprintf(fp, "0 -1");
	}
	else {
		fprintf(fp, "%d ", numOfDiffCycles);
		fprintf(fp, "%d", highest);
	}
	fclose(fp);
}

struct patch
{
	unsigned int numOfGrass;
	unsigned long pos;
};
int compareFunc(const void* p1, const void* p2)
{
	return ((patch*)p1)->pos - ((patch*)p2)->pos;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfPatches = getNum;
	unsigned long willingDistance = getNum * 2;
	patch* grass = (patch*)malloc(sizeof(patch) * numOfPatches);
	for (unsigned int i = 0; i < numOfPatches; i++) {
		grass[i].numOfGrass = getNum;
		grass[i].pos = getNum;
	}
	fclose(fp);
	qsort(grass, numOfPatches, sizeof(patch), compareFunc);
	unsigned long greatest = 0;
	unsigned long currValue = 0;
	for (unsigned int currHigh = 0, currLow = 0; currHigh < numOfPatches; currHigh++) {
		currValue += grass[currHigh].numOfGrass;
		while (grass[currHigh].pos - grass[currLow].pos > willingDistance) {
			currValue -= grass[currLow].numOfGrass;
			currLow++;
		}

		if (currValue > greatest)
			greatest = currValue;
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", greatest);
	fclose(fp);
}

struct tile
{
	int color;
	bool h_vis;
};
tile grid[100][100];
unsigned int lenth;
void floodFill_h(unsigned int currRow, unsigned int currCol) //row = i, col = j
{
	if (grid[currRow][currCol].h_vis)
		return;
	grid[currRow][currCol].h_vis = true;
	if ((currRow + 1 < lenth) && (grid[currRow][currCol].color == grid[currRow + 1][currCol].color) && !grid[currRow + 1][currCol].h_vis)
		floodFill_h(currRow + 1, currCol);
	if ((currCol + 1 < lenth) && (grid[currRow][currCol].color == grid[currRow][currCol + 1].color) && !grid[currRow][currCol + 1].h_vis)
		floodFill_h(currRow, currCol + 1);
	if ((currRow > 0) && (grid[currRow][currCol].color == grid[currRow - 1][currCol].color) && !grid[currRow - 1][currCol].h_vis)
		floodFill_h(currRow - 1, currCol);
	if ((currCol > 0) && (grid[currRow][currCol].color == grid[currRow][currCol - 1].color) && !grid[currRow][currCol - 1].h_vis)
		floodFill_h(currRow, currCol - 1);
}
void floodFill_c(unsigned int currRow, unsigned int currCol) //row = i, col = j
{
	if (grid[currRow][currCol].color == 3)
		return;
	int color = grid[currRow][currCol].color;
	grid[currRow][currCol].color = 3;
	if ((currRow + 1 < lenth) && ((color == grid[currRow + 1][currCol].color) || ((color < 2) && (grid[currRow + 1][currCol].color < 2))))
		floodFill_c(currRow + 1, currCol);
	if ((currCol + 1 < lenth) && ((color == grid[currRow][currCol + 1].color) || ((color < 2) && (grid[currRow][currCol + 1].color < 2))))
		floodFill_c(currRow, currCol + 1);
	if ((currRow > 0) && ((color == grid[currRow - 1][currCol].color) || ((color < 2) && (grid[currRow - 1][currCol].color < 2))))
		floodFill_c(currRow - 1, currCol);
	if ((currCol > 0) && ((color == grid[currRow][currCol - 1].color) || ((color < 2) && (grid[currRow][currCol - 1].color < 2))))
		floodFill_c(currRow, currCol - 1);
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	char ch;
	lenth = getNum;
	for (unsigned int i = 0; i < lenth; i++) {
		for (unsigned int j = 0; j < lenth; j++) {
			ch = fgetc(fp);
			if (ch == 'R')
				grid[i][j].color = 0;
			else if (ch == 'G')
				grid[i][j].color = 1;
			else
				grid[i][j].color = 2;
			grid[i][j].h_vis = false;
		}
		fgetc(fp); // waste newLine
	};
	fclose(fp);
	unsigned int human = 0;
	for (unsigned int i = 0; i < lenth; i++)
		for (unsigned int j = 0; j < lenth; j++)
			if (!grid[i][j].h_vis) {
				floodFill_h(i, j);
				human++;
			}
	unsigned int cow = 0;
	for (unsigned int i = 0; i < lenth; i++)
		for (unsigned int j = 0; j < lenth; j++)
			if (grid[i][j].color != 3) {
				floodFill_c(i, j);
				cow++;
			}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d %d", human, cow);
	fclose(fp);
}

int main(void)
{
	//q1("reorder.in", "reorder.out");
	//q2("lazy.in", "lazy.out");
	q3("cowart.in", "cowart.out");

	//system("pause");
	return 0;
}