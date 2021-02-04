#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>

#include <string.h>
#include <queue>
using namespace std;
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
int compareCows(const void* p1, const void* p2)
{
	return *((unsigned int*)p1) - *((unsigned int*)p2);
}
unsigned int maxCap, numOfBusses, numOfCows; unsigned int* times;
bool works(unsigned int maxWait)
{
	unsigned int busLeft = numOfBusses - 1;
	unsigned int start = 0;
	for (unsigned int i = 1; i < numOfCows; i++) {
		if ((i - start + 1 > maxCap) || (times[i] - times[start] > maxWait)) {
			if (busLeft == 0)
				return false;
			else {
				start = i;
				busLeft--;
			}
		}
	}
	return true;
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	numOfCows = getNum;
	numOfBusses = getNum;
	maxCap = getNum;
	times = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++)
		times[i] = getNum;
	fclose(fp);
	qsort(times, numOfCows, sizeof(unsigned int), compareCows);
	unsigned int min = 0;
	unsigned int max = times[numOfCows - 1] - times[0];
	while (max - min > 1) {
		if (works((max + min) / 2))
			max = (max + min) / 2;
		else
			min = (max + min) / 2;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", max);
	fclose(fp);
}

struct cow
{
	unsigned int priority;
	unsigned int arriveTime;
	unsigned int eatTime;
};
int compareStart(const void* p1, const void* p2)
{
	if (((cow*)p1)->arriveTime - ((cow*)p2)->arriveTime)
		return ((cow*)p1)->arriveTime - ((cow*)p2)->arriveTime;
	return ((cow*)p1)->priority - ((cow*)p2)->priority;
}
void* pQue = NULL;
void* endLoc;
#define connectionMacros true
#define getLeftChild(parent, pQue, sizeOfElement) ((((((char*)parent - (char*)pQue)/sizeOfElement) * 2) + 1) * sizeOfElement)
#define getRightChild(parent, pQue, sizeOfElement) (((((char*)parent - (char*)pQue)/sizeOfElement + 1) * 2) * sizeOfElement)
#define findParent(pQue, child, sizeOfElement) ((char*)pQue + ((((((char*)child - (char*)pQue)/sizeOfElement) - 1) / 2) * sizeOfElement))
#define correctChild(pQue, child, parent, sizeOfElement, compareFunc) (compareFunc(child = (char*)pQue + getLeftChild(parent, pQue, sizeOfElement) + (compareFunc((char*)pQue + getRightChild(parent, pQue, sizeOfElement), (char*)pQue + getLeftChild(parent, pQue, sizeOfElement)) * sizeOfElement), parent))
void pQue_enque(void* item, size_t sizeOfElement, bool(*compareFunc)(const void* parent, const void* child))
{
	//first time stuff
	static void* lastUnit = NULL;
	static unsigned long previoslyMalloced;
	if (pQue == NULL) {
		pQue = malloc(sizeOfElement * 100);
		lastUnit = (char*)pQue + sizeOfElement * 99;
		previoslyMalloced = 100;
		endLoc = pQue;
	}

	memcpy(endLoc, item, sizeOfElement); // the enquing
	void* child = endLoc; void* parent; void* temp = malloc(sizeOfElement);
	while ((child != pQue) && compareFunc(child, parent = findParent(pQue, child, sizeOfElement))) { //heapafy
		//swap parent and child
		memcpy(temp, child, sizeOfElement);
		memcpy(child, parent, sizeOfElement);
		memcpy(parent, temp, sizeOfElement);
		child = parent;
	}
	free(temp);
	//increment endloc
	if (endLoc == lastUnit) {
		previoslyMalloced *= 2;
		endLoc = ((previoslyMalloced / 2 - 1) * sizeOfElement) + (char*)(pQue = realloc(pQue, sizeOfElement * previoslyMalloced));
		lastUnit = (char*)pQue + sizeOfElement * (previoslyMalloced - 1);
	}
	endLoc = (char*)endLoc + sizeOfElement;
}
void* pQue_deque(size_t sizeOfElement, bool(*compareFunc)(const void* p1, const void* p2))
{
	//if the end location == the start, or there is no start
	if ((pQue == NULL) || (endLoc <= pQue))
		return NULL;
	endLoc = (char*)endLoc - sizeOfElement;
	void* returnVal = malloc(sizeOfElement);
	memcpy(returnVal, pQue, sizeOfElement);
	memcpy(pQue, endLoc, sizeOfElement);
	void* parent = pQue;
	void* child = pQue;
	void* temp = malloc(sizeOfElement);
	while ((getRightChild(parent, pQue, sizeOfElement) < (char*)endLoc - (char*)pQue) &&
		correctChild(pQue, child, parent, sizeOfElement, compareFunc)) { //heapafy
		//swap child and parent
		memcpy(temp, child, sizeOfElement);
		memcpy(child, parent, sizeOfElement);
		memcpy(parent, temp, sizeOfElement);
		parent = child;
	}
	//if one of the cilderen is there
	if ((child == parent) && (getLeftChild(parent, pQue, sizeOfElement) < (char*)endLoc - (char*)pQue) &&
		compareFunc(child = (char*)pQue + getLeftChild(parent, pQue, sizeOfElement), parent)) {
		memcpy(temp, child, sizeOfElement);
		memcpy(child, parent, sizeOfElement);
		memcpy(parent, temp, sizeOfElement);
	}
	free(temp);
	return returnVal;
}
void doneWith_pQue(void)
{
	free(pQue);
	pQue = NULL;
}
bool comparePriority(const void* parent, const void* child)
{
	return (((cow*)child)->priority < ((cow*)parent)->priority);
}
void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum;
	cow* cows = (cow*)malloc(sizeof(cow) * numOfCows);
	unsigned int curr;
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].arriveTime = getNum;
		cows[i].eatTime = getNum;
		cows[i].priority = numOfCows - i;
	}
	fclose(fp);
	qsort(cows, numOfCows, sizeof(cow), compareStart);
	unsigned int numInList = 0, enqueAt = 0, startsAt = cows[0].arriveTime, maxWait = 0, compNum;
	/*while((numInList != 0) || (enqueAt < numOfCows)) {
		if (numInList == 0) {
			pQue_enque(&enqueAt, sizeof(unsigned int), comparePriority);
			numInList++; enqueAt++;
		}
		compNum = (unsigned int*)pQue_deque(sizeof(unsigned int), comparePriority); numInList--;
		startsAt = _max(startsAt, cows[*compNum].arriveTime);
		if (maxWait < startsAt - cows[*compNum].arriveTime)
			maxWait = startsAt - cows[*compNum].arriveTime;
		startsAt += cows[*compNum].eatTime;
		while ((enqueAt < numOfCows) && (cows[enqueAt].arriveTime <= startsAt)) {
			pQue_enque(&enqueAt, sizeof(unsigned int), comparePriority);
			enqueAt++; numInList++;
		}
		free(compNum);
	}*/
	priority_queue<pair<unsigned int, unsigned int> >line;
	while ((numInList != 0) || (enqueAt < numOfCows)) {
		if (numInList == 0) {
			line.push(make_pair(cows[enqueAt].priority, enqueAt));
			numInList++; enqueAt++;
		}
		compNum = line.top().second; numInList--; line.pop();
		startsAt = _max(startsAt, cows[compNum].arriveTime);
		if (maxWait < startsAt - cows[compNum].arriveTime)
			maxWait = startsAt - cows[compNum].arriveTime;
		startsAt += cows[compNum].eatTime;
		while ((enqueAt < numOfCows) && (cows[enqueAt].arriveTime <= startsAt)) {
			line.push(make_pair(cows[enqueAt].priority, enqueAt));
			enqueAt++; numInList++;
		}
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", maxWait);
	fclose(fp);
}

struct stack
{
	unsigned int group;
	stack* next;
};
bool* vis; unsigned int** grid; unsigned int height;
unsigned int floodFill(unsigned int x, unsigned int y, unsigned int hayType)
{
	if ((vis[x * 10 + y]) || (grid[x][y] != hayType))
		return 0;
	vis[x * 10 + y] = true;
	unsigned int ans = 1;
	if (x > 0)
		ans += floodFill(x - 1, y, hayType);
	if (x + 1 < height)
		ans += floodFill(x + 1, y, hayType);
	if (y > 0)
		ans += floodFill(x, y - 1, hayType);
	if (y + 1 < 10)
		ans += floodFill(x, y + 1, hayType);
	return ans;
}
void floodFillChange(unsigned int x, unsigned int y, unsigned int hayType)
{
	if (grid[x][y] != hayType)
		return;
	grid[x][y] = 0;
	if (x > 0)
		floodFillChange(x - 1, y, hayType);
	if (x + 1 < height)
		floodFillChange(x + 1, y, hayType);
	if (y > 0)
		floodFillChange(x, y - 1, hayType);
	if (y + 1 < 10)
		floodFillChange(x, y + 1, hayType);
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	height = getNum;
	unsigned int minGroup = getNum;
	grid = (unsigned int**)malloc(sizeof(unsigned int*) * height);
	for (unsigned int i = 0; i < height; i++) {
		grid[i] = (unsigned int*)malloc(sizeof(unsigned int) * 10);
		for (unsigned int j = 0; j < 10; j++)
			grid[i][j] = fgetc(fp) - '0';
		fgetc(fp); //newline
	}
	fclose(fp);
	vis = (bool*)malloc(sizeof(bool) * height * 10);
	unsigned int numOfGroups = 0; stack* start = NULL;
	int goTo;
	bool somethingDone = true;
	while (somethingDone) {
		somethingDone = false;
		memset(vis, 0, sizeof(bool) * height * 10);
		for (unsigned int i = 0; i < height; i++)
			for (unsigned int j = 0; j < 10; j++)
				if ((!vis[i * 10 + j]) && (grid[i][j] != 0) && (floodFill(i, j, grid[i][j]) >= minGroup)) {
					somethingDone = true;
					floodFillChange(i, j, grid[i][j]);
				}
		for (unsigned int j = 0; j < 10; j++) { //put grid back down
			goTo = height - 1;
			for (int i = height - 1; i >= 0; i--)
				if (grid[i][j] != 0) {
					grid[goTo][j] = grid[i][j];
					goTo--;
				}
			while (goTo >= 0) {
				grid[goTo][j] = 0;
				goTo--;
			}
		}
	}
	fp = fopen(fout, "w");
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < 10; j++)
			fprintf(fp, "%d", grid[i][j]);
		fprintf(fp, "\n");
	}
	fclose(fp);
}

int main(void)
{
	//q1("convention.in", "convention.out");
	q2("convention2.in", "convention2.out");
	//q3("mooyomooyo.in", "mooyomooyo.out");

	return 0;
}