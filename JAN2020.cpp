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

int compareBerr(const void* p1, const void* p2)
{
	return *((unsigned int*)p2) - *((unsigned int*)p1);
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfTrees = getNum;
	unsigned int numOfBask = getNum;
	unsigned int maxBerryInTree = 0;
	unsigned int* trees = (unsigned int*)malloc(sizeof(unsigned int) * numOfTrees);
	for (unsigned int i = 0; i < numOfTrees; i++) {
		trees[i] = getNum;
		maxBerryInTree = _max(trees[i], maxBerryInTree);
	}
	fclose(fp);
	unsigned int maxBerry = 0, currBerry = 0;
	unsigned int baskUsed = 0;
	unsigned int* currTrees = (unsigned int*)malloc(sizeof(unsigned int) * numOfTrees);
	for (unsigned int berrInBask = 1; berrInBask <= maxBerryInTree; berrInBask++) {
		memcpy(currTrees, trees, sizeof(unsigned int) * numOfTrees);
		baskUsed = 0;
		currBerry = 0;
		for (unsigned int i = 0; i < numOfTrees; i++) {
			baskUsed += currTrees[i] / berrInBask;
			currTrees[i] %= berrInBask;
			if (baskUsed > numOfBask)
				break;
		}
		if (baskUsed < numOfBask / 2)
			break;
		if (baskUsed >= numOfBask)
			currBerry = (numOfBask / 2) * berrInBask;
		else {
			qsort(currTrees, numOfTrees, sizeof(unsigned int), compareBerr);
			currBerry = (baskUsed - (numOfBask / 2)) * berrInBask;
			for (unsigned int i = 0; i < numOfTrees; i++) {
				baskUsed++;
				if (baskUsed > numOfBask / 2)
					currBerry += currTrees[i];
				if (baskUsed == numOfBask)
					break;
			}
		}
		maxBerry = _max(maxBerry, currBerry);
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", maxBerry);
	fclose(fp);
}

unsigned long long milkOwed, days, minVal;
bool works(long long x)
{
	long long owing = milkOwed, numOfDays, y, pastDays = 0;
	while ((owing > 0) && (pastDays < days)) {
		y = owing / x;
		if(y < minVal)
			return ((days - pastDays) * minVal >= owing);
		numOfDays = _min((owing - (x * y)) / y + 1, days - pastDays);
		pastDays += numOfDays;
		owing -= y * numOfDays;
	}
	return (owing <= 0);
}
void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	milkOwed = getNum; days = getNum; minVal = getNum;
	fclose(fp);
	long long min = 1;
	long long max = milkOwed + 1;
	while (max - min > 1) {
		if (works((min + max) / 2))
			min = (min + max) / 2;
		else
			max = (min + max) / 2;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%llu", min);
	fclose(fp);
}

/*struct wormHole
{
	unsigned int start;
	unsigned int end;
	unsigned int width;
};
struct stack
{
	unsigned int conTo;
	stack* next;
};
struct diff
{
	unsigned int cow;
	unsigned int currLoc;
};
int compareHoles(const void* p1, const void* p2)
{
	return ((wormHole*)p2)->width - ((wormHole*)p1)->width;
}
void q3(const char* fin, const char* fout)
{
	unsigned int loc;
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum;
	unsigned int numOfHoles = getNum;
	diff* different = (diff*)malloc(sizeof(diff) * numOfCows);
	unsigned int numOfDiff = 0;
	wormHole* holes = (wormHole*)malloc(sizeof(wormHole) * numOfHoles);
	unsigned int* inGroup = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		loc = getNum - 1;
		if (loc != i) {
			different[numOfDiff].cow = i;
			different[numOfDiff].currLoc = loc;
			numOfDiff++;
		}
		inGroup[i] = i;
	}
	for (unsigned int i = 0; i < numOfHoles; i++) {
		holes[i].start = getNum - 1;
		holes[i].end = getNum - 1;
		holes[i].width = getNum;
	}
	fclose(fp);
	qsort(holes, numOfHoles, sizeof(wormHole), compareHoles);
	unsigned int startDiff = 0;
	unsigned int fromNum, toNum;
	int ans;
	if (numOfDiff != 0) {
		for (unsigned int i = 0; i < numOfHoles; i++) {
			fromNum = inGroup[holes[i].end];
			toNum = inGroup[holes[i].start];
			for (unsigned int j = 0; j < numOfCows; j++)
				if (inGroup[j] == fromNum)
					inGroup[j] = toNum;
			while ((startDiff < numOfDiff) && (inGroup[different[startDiff].cow] == inGroup[different[startDiff].currLoc]))
				startDiff++;
			if (startDiff == numOfDiff) {
				ans = holes[i].width;
				break;
			}
		}
	}
	else
		ans = -1;
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}*/
//their solution
struct stack
{
	unsigned int holeWidth;
	unsigned int conTo;
	stack* next;
};
struct spot
{
	unsigned int cowHere;
	stack* wormholes;
};
int comapreWidth(const void* p1, const void* p2)
{
	return *((unsigned int*)p1) - *((unsigned int*)p2);
}
spot* locs; unsigned int numOfLocs; unsigned int* group;
void floodFill(unsigned int currLoc, unsigned int maxWidth, unsigned int currGroup)
{
	if (group[currLoc] == currGroup)
		return;
	group[currLoc] = currGroup;
	stack* curr = locs[currLoc].wormholes;
	while (curr) {
		if (curr->holeWidth >= maxWidth)
			floodFill(curr->conTo, maxWidth, currGroup);
		curr = curr->next;
	}
}
bool works(unsigned int maxWidth)
{
	group = (unsigned int*)calloc(numOfLocs, sizeof(unsigned int));
	unsigned int currGroup = 1;
	for (unsigned int i = 0; i < numOfLocs; i++)
		if (!group[i]) {
			floodFill(i, maxWidth, currGroup);
			currGroup++;
		}
	for (unsigned int i = 0; i < numOfLocs; i++)
		if (group[i] != group[locs[i].cowHere])
			return false;
	return true;
}
void q3(const char* fin, const char* fout)
{
	bool is_diff = false;
	FILE* fp = fopen(fin, "r");
	numOfLocs = getNum;
	unsigned int numOfWorm = getNum;
	locs = (spot*)malloc(sizeof(spot) * numOfLocs);
	for (unsigned int i = 0; i < numOfLocs; i++) {
		locs[i].cowHere = getNum - 1;
		if (i != locs[i].cowHere)
			is_diff = true;
		locs[i].wormholes = NULL;
	}
	unsigned int loc1, loc2, width;
	stack* temp;
	unsigned int* widths = (unsigned int*)malloc(sizeof(unsigned int) * numOfWorm);
	for (unsigned int i = 0; i < numOfWorm; i++) {
		loc1 = getNum - 1; loc2 = getNum - 1; width = getNum;
		widths[i] = width;

		temp = (stack*)malloc(sizeof(stack));
		temp->holeWidth = width;
		temp->conTo = loc2;
		temp->next = locs[loc1].wormholes;
		locs[loc1].wormholes = temp;

		temp = (stack*)malloc(sizeof(stack));
		temp->holeWidth = width;
		temp->conTo = loc1;
		temp->next = locs[loc2].wormholes;
		locs[loc2].wormholes = temp;
	}
	fclose(fp);
	qsort(widths, numOfWorm, sizeof(unsigned int), comapreWidth);
	int maxWidth;
	if (is_diff) {
		unsigned int min = 0, max = numOfWorm;
		while (max - min > 1) {
			if (works(widths[(max + min) / 2]))
				min = (max + min) / 2;
			else
				max = (max + min) / 2;
		}
		maxWidth = widths[min];
	}
	else
		maxWidth = -1;
	fp = fopen(fout, "w");
	fprintf(fp, "%d", maxWidth);
	fclose(fp);
}
int main(void)
{
	//q1("berries.in", "berries.out");
	//q2("loan.in", "loan.out");
	q3("wormsort.in", "wormsort.out");

	return 0;
}