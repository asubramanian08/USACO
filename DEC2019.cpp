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

void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned long findNum = getNum;
	fclose(fp);
	bool is_num[] = { 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1 };
	unsigned long ans = (findNum / 8) * 15;
	findNum %= 8;
	if (findNum == 0)
		ans--;
	for (unsigned int i = 0; (findNum > 0) || ((ans += i) && false); i++)
		findNum -= is_num[i];
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

struct cow
{
	char dir;
	unsigned long loc;
	unsigned int weight;
};
struct finish
{
	unsigned int time;
	unsigned int weight;
};
int compareFunc(const void* p1, const void* p2)
{
	return ((finish*)p1)->time - ((finish*)p2)->time;
}
int compareFunc2(const void* p1, const void* p2)
{
	return ((cow*)p1)->loc - ((cow*)p2)->loc;
}
void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum;
	unsigned int end = getNum * 2;
	unsigned int halfWeight = 0;
	cow* cows = (cow*)malloc(sizeof(cow) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		halfWeight += (cows[i].weight = getNum);
		cows[i].loc = getNum * 2;
		cows[i].dir = getNum;
	}
	fclose(fp);
	halfWeight = (halfWeight + 1) / 2;
	qsort(cows, numOfCows, sizeof(cow), compareFunc2);

	finish * ends = (finish*)malloc(sizeof(finish) * numOfCows);
	unsigned int currEnd = 0;
	for (unsigned int i = 0; i < numOfCows; i++) //find one way
		if (cows[i].dir == -1) {
			ends[currEnd].time = cows[i].loc;
			ends[currEnd].weight = cows[currEnd].weight;
			currEnd++;
		}
	for (unsigned int i = 0; i < numOfCows; i++) //find the other way
		if (cows[i].dir == 1) {
			ends[currEnd].time = end - cows[i].loc;
			ends[currEnd].weight = cows[currEnd].weight;
			currEnd++;
		}
	qsort(ends, numOfCows, sizeof(finish), compareFunc);
	unsigned int weightSoFar = 0;
	unsigned int endTimeAt;
	for (unsigned int i = 0; (weightSoFar < halfWeight) || ((endTimeAt = ends[i - 1].time) && 0); i++)
		weightSoFar += ends[i].weight;
	free(ends);

	unsigned long numOfCol = 0;
	unsigned int* forwards = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	unsigned int forwEnd = 0, forwStart = 0;
	for (unsigned int i = 0; i < numOfCows; i++) {
		while ((forwStart < forwEnd) && ((cows[i].loc - cows[forwards[forwStart]].loc) / 2 > endTimeAt))
			forwStart++;
		if (cows[i].dir == 1) {
			forwards[forwEnd] = i;
			forwEnd++;
		}
		else
			numOfCol += forwEnd - forwStart;
	}
	forwEnd = 0; forwStart = 0;
	for (int i = numOfCows - 1; i >= 0; i--) {
		while ((forwStart < forwEnd) && ((cows[forwards[forwStart]].loc - cows[i].loc) / 2 > endTimeAt))
			forwStart++;
		if (cows[i].dir == -1) {
			forwards[forwEnd] = i;
			forwEnd++;
		}
		else
			numOfCol += forwEnd - forwStart;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", numOfCol / 2);
	fclose(fp);
}

/*struct feild
{
	unsigned long feildNum;
	unsigned long numOfConnections;
	unsigned long currCon;
	unsigned long* connections;
	bool cowType_isH;
};
bool likes_H;
unsigned long dest;
feild* feilds;
unsigned int recursive(unsigned long currFeild, unsigned long prevFeild, bool foundCow)
{
	foundCow = foundCow || (feilds[currFeild].cowType_isH == likes_H);
	if (currFeild == dest)
		return foundCow * 2;
	unsigned int curr;
	for (unsigned int i = 0; i < feilds[currFeild].numOfConnections; i++)
		if ((feilds[currFeild].connections[i] != prevFeild) && ((curr = recursive(feilds[currFeild].connections[i], currFeild, foundCow)) != 1))
			return curr;
	return 1;
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned long numOfFeilds = getNum;
	feilds = (feild*)malloc(sizeof(feild) * numOfFeilds);
	unsigned long numOfFriends = getNum;
	for (unsigned long i = 0; i < numOfFeilds; i++) {
		feilds[i].cowType_isH = (fgetc(fp) == 'H');
		feilds[i].numOfConnections = 0;
	}
	numOfFeilds--;
	fgetc(fp); //newline
	for (unsigned long i = 0; i < numOfFeilds; i++) {
		feilds[getNum - 1].numOfConnections++;
		feilds[getNum - 1].numOfConnections++;
	}
	numOfFeilds++;
	fclose(fp);
	fp = fopen(fin, "r");
	getNum; getNum;
	for (unsigned long i = 0; i < numOfFeilds; i++) {
		fgetc(fp); //get back to before
		feilds[i].connections = (unsigned long *)malloc(sizeof(unsigned long*) * feilds[i].numOfConnections);
		feilds[i].currCon = 0;
	}
	numOfFeilds--;
	fgetc(fp); //newline
	for (unsigned long i = 0; i < numOfFeilds; i++) {
		unsigned long feild1 = getNum - 1;
		unsigned long feild2 = getNum - 1;
		feilds[feild1].connections[feilds[feild1].currCon] = feild2;
		feilds[feild1].currCon++;
		feilds[feild2].connections[feilds[feild2].currCon] = feild1;
		feilds[feild2].currCon++;
	}
	numOfFeilds++;
	FILE* fpout = fopen(fout, "w");
	for (unsigned long i = 0; i < numOfFriends; i++) {
		unsigned long start = getNum - 1;
		dest = getNum - 1;
		likes_H = (fgetc(fp) == 'H');
		fgetc(fp);//newline
		fprintf(fpout, "%d", recursive(start, numOfFeilds, false) / 2);
	}
	fclose(fp);
	fclose(fpout);
}*/

struct feild
{
	unsigned long feildNum;
	unsigned long numOfConnections;
	unsigned long currCon;
	unsigned long* connections;
	bool* goesThisWay;
	bool cowType_isH;
};
bool likes_H;
unsigned long dest;
feild* feilds;
unsigned long numOfFeilds;
unsigned int recursive(unsigned long currFeild, unsigned long prevFeild, bool foundCow)
{
	foundCow = foundCow || (feilds[currFeild].cowType_isH == likes_H);
	if (currFeild == dest)
		return foundCow * 2;
	for (unsigned int i = 0; i < feilds[currFeild].numOfConnections; i++) {
		if (feilds[currFeild].goesThisWay[i * numOfFeilds + dest])
			return recursive(feilds[currFeild].connections[i], currFeild, foundCow);
	}
	unsigned int curr;
	for (unsigned int i = 0; i < feilds[currFeild].numOfConnections; i++)
		if ((feilds[currFeild].connections[i] != prevFeild) && ((curr = recursive(feilds[currFeild].connections[i], currFeild, foundCow)) != 1)) {
			feilds[currFeild].goesThisWay[i * numOfFeilds + dest] = true;
			return curr;
		}
	return 1;
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	numOfFeilds = getNum;
	feilds = (feild*)malloc(sizeof(feild) * numOfFeilds);
	unsigned long numOfFriends = getNum;
	for (unsigned long i = 0; i < numOfFeilds; i++) {
		feilds[i].cowType_isH = (fgetc(fp) == 'H');
		feilds[i].numOfConnections = 0;
	}
	numOfFeilds--;
	fgetc(fp); //newline
	for (unsigned long i = 0; i < numOfFeilds; i++) {
		feilds[getNum - 1].numOfConnections++;
		feilds[getNum - 1].numOfConnections++;
	}
	numOfFeilds++;
	fclose(fp);
	fp = fopen(fin, "r");
	getNum; getNum;
	for (unsigned long i = 0; i < numOfFeilds; i++) {
		fgetc(fp); //get back to before
		feilds[i].connections = (unsigned long*)malloc(sizeof(unsigned long*) * feilds[i].numOfConnections);
		feilds[i].currCon = 0;
		feilds[i].goesThisWay = (bool*)calloc(feilds[i].numOfConnections * numOfFeilds, sizeof(bool));
	}
	numOfFeilds--;
	fgetc(fp); //newline
	for (unsigned long i = 0; i < numOfFeilds; i++) {
		unsigned long feild1 = getNum - 1;
		unsigned long feild2 = getNum - 1;
		feilds[feild1].connections[feilds[feild1].currCon] = feild2;
		feilds[feild1].currCon++;
		feilds[feild2].connections[feilds[feild2].currCon] = feild1;
		feilds[feild2].currCon++;
	}
	numOfFeilds++;
	FILE* fpout = fopen(fout, "w");
	for (unsigned long i = 0; i < numOfFriends; i++) {
		unsigned long start = getNum - 1;
		dest = getNum - 1;
		likes_H = (fgetc(fp) == 'H');
		fgetc(fp);//newline
		fprintf(fpout, "%d", recursive(start, numOfFeilds, false) / 2);
	}
	fclose(fp);
	fclose(fpout);
}

int main(void)
{
	//q1("moobuzz.in", "moobuzz.out");
	//q2("meetings.in", "meetings.out");
	q3("milkvisits.in", "milkvisits.out");

	//system("pause");
	return 0;
}