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
#define getNum getNumInFile(&fp)
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

struct move
{
	unsigned int time;
	unsigned int speed;
};
inline int compare(unsigned int x, unsigned int y, int lead)
{
	if (x == y)
		return lead;
	return x > y;
}
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int bessieInsra = getNum;
	unsigned int elsieInsra = getNum;
	move* bessieMoves = (move*)malloc(sizeof(move) * bessieInsra);
	move* elsieMoves = (move*)malloc(sizeof(move) * elsieInsra);
	for (unsigned int i = 0; i < bessieInsra; i++) {
		bessieMoves[i].speed = getNum;
		bessieMoves[i].time = getNum;
	}
	for (unsigned int i = 0; i < elsieInsra; i++) {
		elsieMoves[i].speed = getNum;
		elsieMoves[i].time = getNum;
	}
	fclose(fp);
	unsigned int changes = 0;
	unsigned int bessieLoc = 0;
	unsigned int elsieLoc = 0;
	unsigned int elsieMove = 0;
	unsigned int bessieMove = 0;
	unsigned int timeToTake;
	int lead = 2;
	while ((elsieMove < elsieInsra) && (bessieMove < bessieInsra)) {
		if (elsieMoves[elsieMove].time > bessieMoves[bessieMove].time)
			timeToTake = bessieMoves[bessieMove].time;
		else 
			timeToTake = elsieMoves[elsieMove].time;
		elsieLoc += timeToTake * elsieMoves[elsieMove].speed;
		bessieLoc += timeToTake * bessieMoves[bessieMove].speed;
		elsieMoves[elsieMove].time -= timeToTake;
		bessieMoves[bessieMove].time -= timeToTake;
		if ((lead != 2) && (lead != compare(elsieLoc, bessieLoc, lead)))
			changes++;
		if (elsieLoc != bessieLoc)
			lead = (elsieLoc > bessieLoc);
		if (bessieMoves[bessieMove].time == 0)
			bessieMove++;
		if (elsieMoves[elsieMove].time == 0)
			elsieMove++;
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", changes);
	fclose(fp);
}

void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	long numOfCows = getNum;
	long maxDistance = getNum;
	long* lastLocation = (long*)calloc(1000002, sizeof(long));
	//unsigned int* cowLineup = (unsigned int*)malloc(numOfCows * sizeof(unsigned int));
	long largestPair = -1;
	long currNum;
	for (long i = 1; i <= numOfCows; i++) {
		currNum = getNum;
		if (currNum > largestPair) {
			if ((lastLocation[currNum]) && (i - lastLocation[currNum] <= maxDistance))
				largestPair = currNum;
			lastLocation[currNum] = i;
		}
	}
	free(lastLocation);
	fclose(fp);
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", largestPair);
	fclose(fp);
}

struct relationship
{
	bool similar;
	int cow;
};
struct cow
{
	relationship* prev_rels;
	int currRelationNum;
	int currBreed;
};
int recursave(cow* cows, unsigned int numOfCows, int currCow)
{
	if (currCow == numOfCows)
		return 1;
	int return_val = 0;
	bool can_be[3] = { 0 };
	for (int j = 0; j < cows[currCow].currRelationNum; j++) {
		if (cows[currCow].prev_rels[j].similar) {
			if (cows[cows[currCow].prev_rels[j].cow].currBreed != 0)
				can_be[0] = 1;
			if (cows[cows[currCow].prev_rels[j].cow].currBreed != 1)
				can_be[1] = 1;
			if (cows[cows[currCow].prev_rels[j].cow].currBreed != 2)
				can_be[2] = 1;
		}
		else
			can_be[cows[cows[currCow].prev_rels[j].cow].currBreed] = 1;
	}
	for (unsigned int i = 0; i < 3; i++) {
		if (!can_be[i]) {
			cows[currCow].currBreed = i;
			return_val += recursave(cows, numOfCows, currCow + 1);
		}
	}
	return return_val;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	cow* cows = (cow*)malloc(sizeof(cow) * numOfCows);
	cows[0] = { NULL, 0, 0 };
	for (unsigned int i = 1; i < numOfCows; i++) {
		cows[i].prev_rels = (relationship*)malloc(i * sizeof(relationship));
		cows[i].currRelationNum = 0;
	}
	unsigned int numOfReationships = getNum;
	for (unsigned int i = 0; i < numOfReationships; i++) {
		bool similar = fgetc(fp) == 'S';
		fgetc(fp);
		int x = getNum - 1;
		int y = getNum - 1;
		if (x > y) {
			cows[x].prev_rels[cows[x].currRelationNum] = { similar, y };
			cows[x].currRelationNum++;
		}
		else {
			cows[y].prev_rels[cows[y].currRelationNum] = { similar, x };
			cows[y].currRelationNum++;
		}
	}
	fclose(fp);
	unsigned int ans = recursave(cows, numOfCows, 1) * 3;
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", ans);
	fclose(fp);
}

int main(void)
{
	//q1("cowrace.in", "cowrace.out");
	//q2("proximity.in", "proximity.out");
	q3("assign.in", "assign.out");
	system("pause");
	return 0;
}