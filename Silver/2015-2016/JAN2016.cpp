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

int compareFunc(const void* p1, const void* p2)
{
	return *((int*)p1) - *((int*)p2);
}
bool works(unsigned int range, unsigned int numOfCows, unsigned int* locations, unsigned int numOfBales)
{
	unsigned int currCow = 0;
	unsigned int start; unsigned int curr = 0;
	while ((currCow != numOfCows) && (curr < numOfBales)) {
		for (start = locations[curr]; locations[curr] - start <= range; curr++);
		currCow++;
	}
	return curr == numOfBales;
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfBales = getNum;
	unsigned int numOfCows = getNum;
	unsigned int* locations = (unsigned int*)malloc(sizeof(unsigned int) * numOfBales);
	for (unsigned int i = 0; i < numOfBales; i++)
		locations[i] = getNum;
	fclose(fp);
	qsort(locations, numOfBales, sizeof(unsigned int), compareFunc);
	unsigned int highEnd = ((((locations[numOfBales - 1] - locations[0]) / numOfCows) + 1) / 2) + 1;
	unsigned int lowEnd = 0;
	while (highEnd - lowEnd > 1) {
		if (works(((highEnd + lowEnd) / 2) * 2, numOfCows, locations, numOfBales))
			highEnd = (highEnd + lowEnd) / 2;
		else
			lowEnd = (highEnd + lowEnd) / 2;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", highEnd);
	fclose(fp);
}

void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum;
	unsigned int* valueSoFar = (unsigned int*)malloc(sizeof(unsigned int) * (numOfCows + 1));
	unsigned int currVal = 0;
	for (unsigned int i = 0; i < numOfCows; i++) {
		valueSoFar[i] = currVal;
		currVal = (currVal + getNum) % 7;
	}
	fclose(fp);
	valueSoFar[numOfCows] = currVal;
	unsigned int lowestType[7] = { 0 };
	unsigned int highestType[7] = { 0 };
	unsigned int numOfValues = numOfCows + 1;
	for (unsigned int i = 0; i < numOfValues; i++) {
		if (!lowestType[valueSoFar[i]])
			lowestType[valueSoFar[i]] = i + 1;
		highestType[valueSoFar[i]] = i + 1;
	}
	unsigned int ans = 0;
	for (unsigned int i = 0; i < 7; i++) {
		if (ans < highestType[i] - lowestType[i])
			ans = highestType[i] - lowestType[i];
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

struct spot
{
	int x;
	int y;
};
bool* grid;
void q3(const char* fin, const char* fout)
{
	grid = (bool*)calloc(4000 * 4000, sizeof(bool));
	FILE * fp = fopen(fin, "r");
	unsigned int numOfInstra = getNum;
	spot loc = { 2000, 2000 };
	grid[loc.x * 4000 + loc.y] = true;
	spot dir, prev_dir = {0, 0}; char ch;
	bool prev_intersect = false;
	unsigned int ans = 0;
	for (unsigned int i = 0; i < numOfInstra; i++) { //place lines
		ch = fgetc(fp);
		if (ch == 'N')
			dir = { 0, -1 };
		else if (ch == 'E')
			dir = { 1, 0 };
		else if (ch == 'S')
			dir = { 0, 1 };
		else
			dir = { -1, 0 };
		loc.x += dir.x;
		loc.y += dir.y;
		if (grid[loc.x * 4000 + loc.y]) {
			if (!prev_intersect) {
				ans++;
				if ((-prev_dir.x == dir.x) && (-prev_dir.y == dir.y))
					ans--;
			}
			prev_intersect = true;
		}
		else {
			grid[loc.x * 4000 + loc.y] = true;
			prev_intersect = false;
		}
		loc.x += dir.x;
		loc.y += dir.y;
		if (grid[loc.x * 4000 + loc.y]) {
			if (!prev_intersect) {
				ans++;
			}
			prev_intersect = true;
		}
		else {
			grid[loc.x * 4000 + loc.y] = true;
			prev_intersect = false;
		}
		prev_dir.x = dir.x;
		prev_dir.y = dir.y;
	}
	fclose(fp);
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}
int main(void)
{
	q1("angry.in", "angry.out");
	//q2("div7.in", "div7.out");
	//q3("gates.in", "gates.out");

	//system("pause");
	return 0;
}