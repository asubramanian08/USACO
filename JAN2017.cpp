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

unsigned int numOfCows;
unsigned int maxT;
unsigned int* endTimes; 
unsigned int* performanceOrder;
bool works(unsigned int stageSize)
{
	unsigned int smallestNum;
	for (unsigned int i = stageSize; i < numOfCows; i++) {
		smallestNum = 0;
		for (unsigned int j = 1; j < stageSize; j++)
			if (endTimes[j] < endTimes[smallestNum])
				smallestNum = j;
		endTimes[smallestNum] += performanceOrder[i];
		if (endTimes[smallestNum] > maxT)
			return 0;
	}
	return true;
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	numOfCows = getNum;
	maxT = getNum;
	performanceOrder = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++)
		performanceOrder[i] = getNum;
	fclose(fp);
	endTimes = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	unsigned int low = 0, high = numOfCows;
	while (high - low > 1) {
		memcpy(endTimes, performanceOrder, sizeof(unsigned int) * ((high + low) / 2));
		if (works((high + low) / 2))
			high = (high + low) / 2;
		else
			low = (high + low) / 2;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", high);
	fclose(fp);
}

void q2(const char* fin, const char* fout)
{
	long placementVals[2][3] = { 0 };
	FILE* fp = fopen(fin, "r");
	unsigned int numOfRounds = getNum;
	char ch;
	char* vals = (char*)malloc(sizeof(char) * numOfRounds);
	for (unsigned int i = 0; i < numOfRounds; i++) {
		ch = fgetc(fp);
		fgetc(fp); //newine
		if (ch == 'P')
			vals[i] = 0;
		else if (ch == 'H')
			vals[i] = 1;
		else
			vals[i] = 2;
		placementVals[1][vals[i]]++;
	}
	fclose(fp);
	unsigned int max = _max(placementVals[1][0], _max(placementVals[1][1], placementVals[1][2]));
	for (unsigned int i = 0; i < numOfRounds; i++) {
		placementVals[0][vals[i]]++;
		placementVals[1][vals[i]]--;
		if (max < _max(placementVals[1][0], _max(placementVals[1][1], placementVals[1][2])) + _max(placementVals[0][0], _max(placementVals[0][1], placementVals[0][2])))
			max = _max(placementVals[1][0], _max(placementVals[1][1], placementVals[1][2])) + _max(placementVals[0][0], _max(placementVals[0][1], placementVals[0][2]));
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", max);
	fclose(fp);
}

void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	int strLen;
	char* str = readStrInFile(&fp, 30, &strLen);
	unsigned long long charNum = getNum;
	strLen--;
	fclose(fp);
	unsigned long long pow2 = strLen;
	while (pow2 < charNum)
		pow2 *= 2;
	while (pow2 != strLen){
		pow2 /= 2;
		if (charNum > pow2) {
			charNum = (charNum - 1) % pow2;
			if (charNum == 0)
				charNum = pow2;
		}
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%c", str[charNum - 1]);
	fclose(fp);
}

int main(void)
{
	q1("cowdance.in", "cowdance.out");
	//q2("hps.in", "hps.out");
	//q3("cowcode.in", "cowcode.out");

	//system("pause");
	return 0;
}