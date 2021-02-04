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

//my solution edited to youtube guy's solution
bool* vis;
unsigned int* cycle;
void findSpot(unsigned long toRepeate, unsigned int* comeFrom, unsigned int* endAt, unsigned int currCow)
{
	unsigned int currPos = currCow;
	unsigned long numInCycle = 0;
	do {
		vis[currPos] = true;
		cycle[numInCycle] = currPos;
		numInCycle++;
		currPos = comeFrom[currPos];
	} while (currPos != currCow);
	unsigned int mod = toRepeate % numInCycle;
	for (unsigned int i = 0; i < numInCycle; i++)
		endAt[cycle[i]] = cycle[(i + mod) % numInCycle];
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum;
	unsigned int numOfInstra = getNum;
	unsigned long toRepeate = getNum;
	vis = (bool*)calloc(numOfCows, sizeof(bool));
	cycle = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	unsigned int** cows = (unsigned int**)malloc(sizeof(unsigned int*) * 2);
	cows[0] = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	cows[1] = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	bool corrList = 0;
	for (unsigned int i = 0; i < numOfCows; i++)
		cows[corrList][i] = i;
	unsigned int start, end;
	for (unsigned int i = 0; i < numOfInstra; i++) {
		start = getNum - 1;
		end = getNum - 1;
		memcpy(cows[!corrList], cows[corrList], sizeof(unsigned int) * start);
		for (unsigned int i = start; i <= end; i++)
			cows[!corrList][i] = cows[corrList][end - (i - start)];
		memcpy(cows[!corrList] + end + 1, cows[corrList] + end + 1, sizeof(unsigned int) * (numOfCows - end - 1));
		corrList = !corrList;
	}
	fclose(fp);
	for (unsigned int i = 0; i < numOfCows; i++) {
		if (vis[i] == false)
			findSpot(toRepeate, cows[corrList], cows[!corrList], i);
	}
	corrList = !corrList;
	fp = fopen(fout, "w");
	for (unsigned int i = 0; i < numOfCows; i++)
		fprintf(fp, "%d\n", cows[corrList][i] + 1);
	fclose(fp);
}

#define modBy 1000000007
struct point
{
	long x;
	long y;
};
int compareX(const void* p1, const void* p2)
{
	return ((point*)p1)->x - ((point*)p2)->x;
}
int compareY(const void* p1, const void* p2)
{
	return ((point*)p1)->y - ((point*)p2)->y;
}
unsigned long bSearch(unsigned long numOfGroups, unsigned long* xGroups, point* xOrder, long xVal)
{
	unsigned long low = 0, high = numOfGroups - 1;
	long currVal;
	if (xOrder[xGroups[low]].x == xVal)
		return xGroups[low];
	if (xOrder[xGroups[high]].x == xVal)
		return xGroups[high];
	while (high - low > 1) {
		currVal = xOrder[xGroups[(high + low) / 2]].x;
		if (currVal > xVal)
			high = (high + low) / 2;
		else if (currVal < xVal)
			low = (high + low) / 2;
		else
			return xGroups[(high + low) / 2];
	}
	return -1;
}
void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned long numOfPoints = getNum;
	point* xOrder = (point*)malloc(sizeof(point) * numOfPoints);
	for (unsigned long i = 0; i < numOfPoints; i++) {
		xOrder[i].x = getNum;
		xOrder[i].y = getNum;
	}
	fclose(fp);
	qsort(xOrder, numOfPoints, sizeof(point), compareX);
	point* yOrder = (point*)malloc(sizeof(point) * numOfPoints);
	memcpy(yOrder, xOrder, sizeof(point) * numOfPoints);
	qsort(yOrder, numOfPoints, sizeof(point), compareY);

	unsigned long* xGroups = (unsigned long*)malloc(sizeof(unsigned long) * numOfPoints);
	unsigned long numOfXGroups = 0; bool on = false;
	for (unsigned long i = 1; i < numOfPoints; i++)
		if (xOrder[i - 1].x == xOrder[i].x) {
			if (!on) {
				xGroups[numOfXGroups] = i - 1;
				numOfXGroups++;
			}
			on = true;
		}
		else on = false;

	unsigned long xStart, xSum, ySum, j;
	unsigned long long ans = 0;
	for (unsigned long i = 0; i < numOfPoints; ) {
		if ((i + 1 < numOfPoints) && (yOrder[i].y == yOrder[i + 1].y)) {
			for (j = i; (j < numOfPoints) && (yOrder[j].y == yOrder[i].y); j++) {
				xSum = 0; ySum = 0;
				xStart = bSearch(numOfXGroups, xGroups, xOrder, yOrder[j].x);
				if (xStart == -1)
					continue;
				for (unsigned long k = i; (k < numOfPoints) && (yOrder[k].y == yOrder[i].y); k++)
					ySum += abs(yOrder[j].x - yOrder[k].x);
				for (unsigned long k = xStart; (k < numOfPoints) && (xOrder[k].x == yOrder[j].x); k++)
					xSum += abs(yOrder[j].y - xOrder[k].y);
				ans += ySum * xSum;
				ans = ans % modBy;
			}
			i = j;
		}
		else
			i++;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%lu", ans);
	fclose(fp);
}

struct stack
{
	unsigned int room;
	stack* next;
};
struct room
{
	stack* connections;
	unsigned int currClock;
};
room* rooms;
unsigned int recursive(unsigned int parent, unsigned int currRoom)
{
	stack* currInStack = rooms[currRoom].connections;
	unsigned int calls = 0;
	while (currInStack) {
		if (currInStack->room != parent)
			calls += recursive(currRoom, currInStack->room);
		currInStack = currInStack->next;
	}
	unsigned int returnVal = rooms[currRoom].currClock + calls;
	returnVal %= 12;
	return 12 - returnVal;
}
bool works(unsigned int currRoom) {
	unsigned int total = rooms[currRoom].currClock;
	stack* currInStack = rooms[currRoom].connections;
	while (currInStack) {
		total += recursive(currRoom, currInStack->room);
		currInStack = currInStack->next;
	}
	total %= 12;
	return (total == 0) || (total == 1);
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfRooms = getNum;
	rooms = (room*)malloc(sizeof(room) * numOfRooms);
	for (unsigned int i = 0; i < numOfRooms; i++) {
		rooms[i].currClock = getNum;
		rooms[i].connections = NULL;
	}
	unsigned int r1, r2; stack* temp;
	for (unsigned int i = 1; i < numOfRooms; i++) {
		r1 = getNum - 1; r2 = getNum - 1;
		temp = (stack*)malloc(sizeof(stack));
		temp->next = rooms[r1].connections;
		temp->room = r2;
		rooms[r1].connections = temp;

		temp = (stack*)malloc(sizeof(stack));
		temp->next = rooms[r2].connections;
		temp->room = r1;
		rooms[r2].connections = temp;
	}
	fclose(fp);
	unsigned int ans = 0;
	for (unsigned int i = 0; i < numOfRooms; i++)
		if (works(i))
			ans++;
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

int main(void)
{
	//q1("swap.in","swap.out");
	//q2("triangles.in","triangles.out");
	q3("clocktree.in","clocktree.out");

	return 0;
}