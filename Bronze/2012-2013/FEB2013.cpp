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
//_CRT_SECURE_NO_WARNINGS;

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

struct loopy
{
	int goesTo;
	int is_loopy;
};
void findLoopy(unsigned int numOfCows, loopy* cows, int start)
{
	while ((start != -1) && (cows[start].is_loopy == 0)) {
		cows[start].is_loopy++;
		start = cows[start].goesTo;
	}
	int changeTo = 2;
	if ((start == -1) || (cows[start].is_loopy == 3))
		changeTo = 3;
	for (unsigned int i = 0; i < numOfCows; i++) {
		if (cows[i].is_loopy == 1)
			cows[i].is_loopy = changeTo;
	}
}
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNumInFile(&fp);
	loopy* cows = (loopy*)malloc(sizeof(loopy) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].goesTo = getNumInFile(&fp) - 1;
		cows[i].is_loopy = 0;
	}
	fclose(fp);
	unsigned int ans = 0;
	for (int i = 0; i < numOfCows; i++) {
		if (cows[i].is_loopy == 0) 
			findLoopy(numOfCows, cows, i);
		if (cows[i].is_loopy == 3)
			ans++;
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

struct position
{
	unsigned int cowNumber;
	long location;
	//int* ansPtr;
};
int compareFunc(const void* p1, const void* p2)
{
	return ((position*)p1)->location - ((position*)p2)->location;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNumInFile(&fp);
	position* starts = (position*)malloc(sizeof(position) * numOfCows);
	position* ends = (position*)malloc(sizeof(position) * numOfCows);
	int* seen = (int*)calloc(numOfCows, sizeof(int));
	for (unsigned int i = 0; i < numOfCows; i++) {
		starts[i].location = getNumInFile(&fp);
		ends[i].location = getNumInFile(&fp);
		starts[i].cowNumber = i;
		ends[i].cowNumber = i;
	}
	fclose(fp);
	qsort(starts, numOfCows, sizeof(position), compareFunc);
	qsort(ends, numOfCows, sizeof(position), compareFunc);
	int lookingFor = -1;
	unsigned int lookingForNum;
	unsigned int ans = 0;
	for (unsigned int i = 0; i < numOfCows; i++) {
		if ((lookingFor == -1) && (seen[starts[i].cowNumber] == 0)) {
			lookingFor = starts[i].cowNumber;
			lookingForNum = i;
		}
		if ((lookingFor != -1) && (lookingFor == ends[i].cowNumber)) {
			if (lookingForNum == i)
				ans++;
			lookingFor = -1;
		}
		seen[ends[i].cowNumber] = 1;
		seen[starts[i].cowNumber] = 1;
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

/*struct point
{
	int x;
	int y;
};*/
int floodFill(int greatestX, int greatestY, int lowestX, int lowestY, int currX, int currY, short grid[102][102])
{
	if (grid[currX][currY])
		return grid[currX][currY] & 1;
	grid[currX][currY] = 2;
	int total = 0;
	if (currX < greatestX)
		total += floodFill(greatestX, greatestY, lowestX, lowestY, currX + 1, currY, grid);
	if (currX > lowestX)
		total += floodFill(greatestX, greatestY, lowestX, lowestY, currX - 1, currY, grid);
	if (currY < greatestY)
		total += floodFill(greatestX, greatestY, lowestX, lowestY, currX, currY + 1, grid);
	if (currY > lowestY)
		total += floodFill(greatestX, greatestY, lowestX, lowestY, currX, currY - 1, grid);
	return total;
}
void q3(const char* fpIn, const char* fpOut)
{
	short grid[102][102] = { 0 };
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNumInFile(&fp);
	int xVal;
	int yVal;
	int greatestX = 0, greatestY = 0, lowestX = 101, lowestY = 101;
	for (unsigned int i = 0; i < numOfCows; i++) {
		xVal = getNumInFile(&fp);
		yVal = getNumInFile(&fp);
		if (xVal > greatestX)
			greatestX = xVal;
		if (xVal < lowestX)
			lowestX = xVal;
		if (yVal > greatestY)
			greatestY = yVal;
		if (yVal < lowestY)
			lowestY = yVal;
		grid[xVal][yVal] = 1;
	}
	fclose(fp);
	int ans = floodFill(greatestX + 1, greatestY + 1, lowestX - 1, lowestY - 1, greatestX + 1, greatestY + 1, grid);
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

int main(void)
{
	//q1("relay.in", "relay.out");
	//q2("crossings.in", "crossings.out");
	q3("perimeter.in", "perimeter.out");
	//system("pause");
	return 0;
}