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
	bool is_active;
	unsigned int x, y;
};
cow** byX, ** byY;
unsigned int minArea = ~((unsigned int)0);
unsigned int numOfCows;
int compareFuncX(const void* p1, const void* p2)
{
	return (*((cow * *)p1))->x - (*((cow * *)p2))->x;
}
int compareFuncY(const void* p1, const void* p2)
{
	return (*((cow * *)p1))->y - (*((cow * *)p2))->y;
}
void findSmallestArea(unsigned int highX, unsigned int lowX, unsigned int highY, unsigned int lowY, unsigned int depth)
{
	while (!byX[highX]->is_active)
		(highX)--;
	while (!byY[highY]->is_active)
		(highY)--;
	while (!byX[lowX]->is_active)
		(lowX)++;
	while (!byY[lowY]->is_active)
		(lowY)++;
	if (minArea > (byX[highX]->x - byX[lowX]->x) * (byY[highY]->y - byY[lowY]->y))
		minArea = (byX[highX]->x - byX[lowX]->x) * (byY[highY]->y - byY[lowY]->y);
	if (depth == 3)
		return;
	
	byX[highX]->is_active = false;
	findSmallestArea(highX, lowX, highY, lowY, depth + 1);
	byX[highX]->is_active = true;

	byX[lowX]->is_active = false;
	findSmallestArea(highX, lowX, highY, lowY, depth + 1);
	byX[lowX]->is_active = true;

	byY[highY]->is_active = false;
	findSmallestArea(highX, lowX, highY, lowY, depth + 1);
	byY[highY]->is_active = true;

	byY[lowY]->is_active = false;
	findSmallestArea(highX, lowX, highY, lowY, depth + 1);
	byY[lowY]->is_active = true;
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	numOfCows = getNum;
	if (numOfCows <= 4) {
		fclose(fp);
		fp = fopen(fout, "w");
		fprintf(fp, "0");
		fclose(fp);
		return;
	}
	cow* cows = (cow*)malloc(sizeof(cow) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++){
		cows[i].is_active = true;
		cows[i].x = getNum;
		cows[i].y = getNum;
	}
	fclose(fp);
	byX = (cow * *)malloc(sizeof(cow*) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++)
		byX[i] = &cows[i];
	qsort(byX, numOfCows, sizeof(cow*), compareFuncX);
	byY = (cow * *)malloc(sizeof(cow*) * numOfCows);
	memcpy(byY, byX, sizeof(cow*) * numOfCows);
	qsort(byY, numOfCows, sizeof(cow*), compareFuncY);
	findSmallestArea(numOfCows - 1, 0, numOfCows - 1, 0, 0);
	fp = fopen(fout, "w");
	fprintf(fp, "%d", minArea);
	fclose(fp);
}

int compareFunc(const void* p1, const void* p2)
{
	return *(unsigned int*)p1 - *(unsigned int*)p2;
}
void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numberOfDia = getNum;
	unsigned int range = getNum;
	unsigned int* diamonds = (unsigned int*)malloc(sizeof(unsigned int) *numberOfDia);
	for (unsigned int i = 0; i < numberOfDia; i++)
		diamonds[i] = getNum;
	fclose(fp);
	qsort(diamonds, numberOfDia, sizeof(unsigned int), compareFunc);
	unsigned int currMaxDia = 0;
	unsigned int currMaxDia1 = 0;
	unsigned int curr = 0;
	unsigned int start = 0;
	unsigned int start1;
	for (unsigned int i = 1; i < numberOfDia; i++) {
		if (diamonds[i] - diamonds[start] <= range)
			continue;
		start1 = i;
		currMaxDia1 = 0;
		for (unsigned int j = i; j < numberOfDia; j++) {
			while (diamonds[j] - diamonds[start1] > range)
				start1++;
			if (currMaxDia1 < j - start1)
				currMaxDia1 = j - start1;
		}
		if (currMaxDia < (currMaxDia1 + 1) + (i - start))
			currMaxDia = (currMaxDia1 + 1) + (i - start);
		if ((i - 1) - start == range)
			break;
		while (diamonds[i] - diamonds[start] > range)
			start++;

	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", currMaxDia);
	fclose(fp);
}

struct linkList
{
	unsigned int bridgeTo;
	linkList* next;
};
struct barn
{
	linkList* bridges;
	linkList* end;
	bool isOpen;
};
bool* canMake;
barn* barns;
unsigned int numOfBarns;
void DFS(unsigned int currBarn)
{
	canMake[currBarn] = true;
	linkList* curr = barns[currBarn].bridges;
	while (curr) {
		if (barns[curr->bridgeTo].isOpen && !canMake[curr->bridgeTo])
			DFS(curr->bridgeTo);
		curr = curr->next;
	}
}
bool isCon(void)
{
	for (unsigned int i = 0; i < numOfBarns; i++)
		if ((barns[i].isOpen) && (!canMake[i]))
			return false;
	return true;
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	numOfBarns = getNum;
	barns = (barn*)malloc(sizeof(barn) * numOfBarns);
	for (unsigned int i = 0; i < numOfBarns; i++) {
		barns[i].isOpen = true;
		barns[i].bridges = NULL;
		barns[i].end = NULL;
	}
	unsigned int numOfStreets = getNum;
	for (unsigned int i = 0; i < numOfStreets; i++) {
		unsigned int b1 = getNum - 1, b2 = getNum - 1;
		if (barns[b1].end) {
			barns[b1].end->next = (linkList*)malloc(sizeof(linkList));
			barns[b1].end = barns[b1].end->next;
		}
		else {
			barns[b1].end = (linkList*)malloc(sizeof(linkList));
			barns[b1].bridges = barns[b1].end;
		}
		barns[b1].end->bridgeTo = b2;
		barns[b1].end->next = NULL;

		if (barns[b2].end) {
			barns[b2].end->next = (linkList*)malloc(sizeof(linkList));
			barns[b2].end = barns[b2].end->next;
		}
		else {
			barns[b2].end = (linkList*)malloc(sizeof(linkList));
			barns[b2].bridges = barns[b2].end;
		}
		barns[b2].end->bridgeTo = b1;
		barns[b2].end->next = NULL;
	}
	unsigned int* order = (unsigned int*)malloc(sizeof(unsigned int) * numOfBarns);
	for (unsigned int i = 0; i < numOfBarns; i++)
		order[i] = getNum - 1;
	fclose(fp);
	canMake = (bool*)malloc(sizeof(bool) * numOfBarns);
	unsigned int earlyestOne = 0;
	fp = fopen(fout, "w");
	for (unsigned int i = 0; i < numOfBarns; i++) {
		memset(canMake, 0, sizeof(bool) * numOfBarns);
		if(i != 0)
			barns[order[i - 1]].isOpen = false;
		for (unsigned int j = earlyestOne; j < numOfBarns; j++)
			if (barns[j].isOpen) {
				earlyestOne = j;
				break;
			}
		DFS(earlyestOne);
		if (isCon())
			fprintf(fp, "YES\n");
		else
			fprintf(fp, "NO\n");
	}
	fclose(fp);
}

int main(void)
{
	q1("reduce.in", "reduce.out");
	//q2("diamond.in", "diamond.out");
	//q3("closing.in", "closing.out");

	//system("pause");
	return 0;
}