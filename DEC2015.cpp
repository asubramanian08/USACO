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

#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define __min(a,b) (((a) < (b)) ? (a) : (b))
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int a = getNum, b = getNum, c = getNum, d = getNum, ans;
	if ((d <= b && d >= a) || (c <= b && c >= a) || (b <= d && b >= c)) //they are overlapping
		ans = __max(b, d) - __min(a, c);
	else
		ans = (d - c) + (b - a);
	fclose(fp);
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

struct seg
{
	int distace;
	int speed;
};
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int copSeg = getNum;
	unsigned int bessieSeg = getNum;
	/*seg* cop = (seg*)malloc(sizeof(seg) * copSeg);
	unsigned int soFar = 0;
	for (unsigned int i = 0; i < copSeg; i++) {
		cop[i].distace = soFar;
		soFar += getNum;
		cop[i].speed = getNum;
	}
	soFar = 0;
	seg* bessie = (seg*)malloc(sizeof(seg) * bessieSeg);
	for (unsigned int i = 0; i < bessieSeg; i++) {
		bessie[i].distace = soFar;
		soFar += getNum;
		bessie[i].speed = getNum;
	}
	fclose(fp);
	int maxBroken = 0;
	int bessieSpeed;
	int copSpeed;
	int currBessie = 0;
	int currCop = 0;
	for (unsigned int i = 0; i < 100; i++) {
		if (i == bessie[currBessie].distace) {
			bessieSpeed = bessie[currBessie].speed;
			currBessie++;
		}
		if (i == cop[currCop].distace) {
			copSpeed = cop[currCop].speed;
			currCop++;
		}
		if (maxBroken < bessieSpeed - copSpeed)
			maxBroken = bessieSpeed - copSpeed;
	}*/
	seg* cop = (seg*)malloc(sizeof(seg) * copSeg);
	unsigned int soFar = 0;
	for (unsigned int i = 0; i < copSeg; i++) {
		cop[i].distace = soFar;
		soFar += getNum;
		cop[i].speed = getNum;
	}
	soFar = 0;
	seg* bessie = (seg*)malloc(sizeof(seg) * bessieSeg);
	for (unsigned int i = 0; i < bessieSeg; i++) {
		bessie[i].distace = soFar;
		soFar += getNum;
		bessie[i].speed = getNum;
	}
	fclose(fp);
	int maxBroken = 0;
	int bessieSpeed;
	int copSpeed;
	int currBessie = 0;
	int currCop = 0;
	while ((currBessie < bessieSeg) && (currCop < copSeg)) {
		if (bessie[currBessie].distace < cop[currCop].distace) {
			bessieSpeed = bessie[currBessie].speed;
			currBessie++;
		}
		else if (bessie[currBessie].distace > cop[currCop].distace) {
			copSpeed = cop[currCop].speed;
			currCop++;
		}
		else {
			copSpeed = cop[currCop].speed;
			currCop++;
			bessieSpeed = bessie[currBessie].speed;
			currBessie++;
		}
		if (maxBroken < bessieSpeed - copSpeed)
			maxBroken = bessieSpeed - copSpeed;
	}
	if (currCop < copSeg) {
		copSpeed = cop[currCop].speed;
		if (maxBroken < bessieSpeed - copSpeed)
			maxBroken = bessieSpeed - copSpeed;
	}
	else if (currBessie < bessieSeg) {
		bessieSpeed = bessie[currBessie].speed;
		if (maxBroken < bessieSpeed - copSpeed)
			maxBroken = bessieSpeed - copSpeed;
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", maxBroken);
	fclose(fp);
}

struct drink
{
	unsigned int person;
	unsigned int milk;
	unsigned int time;
};
struct sick
{
	unsigned int person;
	unsigned int time;
};
int compareDrinks(const void* p1, const void* p2)
{
	return ((drink*)p1)->time - ((drink*)p2)->time;
}
int compareSick(const void* p1, const void* p2)
{
	return ((sick*)p1)->time - ((sick*)p2)->time;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfPeople = getNum;
	unsigned int numOfMilk = getNum;
	unsigned int numOfDrinks = getNum;
	unsigned int numSick = getNum;
	drink* drinks = (drink*)malloc(sizeof(drink) * numOfDrinks);
	for (unsigned int i = 0; i < numOfDrinks; i++) {
		drinks[i].person = getNum - 1;
		drinks[i].milk = getNum - 1;
		drinks[i].time = getNum;
	}
	sick* sickPeople = (sick*)malloc(sizeof(sick) * numSick);
	for (unsigned int i = 0; i < numSick; i++) {
		sickPeople[i].person = getNum - 1;
		sickPeople[i].time = getNum;
	}
	fclose(fp);
	qsort(drinks, numOfDrinks, sizeof(drink), compareDrinks);
	qsort(sickPeople, numSick, sizeof(sick), compareSick);
	bool* possibilities = (bool*)malloc(sizeof(bool) * numOfMilk);
	//memset(possibilities, true, sizeof(bool) * numOfMilk);
	for (unsigned int i = 0; i < numOfMilk; i++)
		possibilities[i] = true;
	bool* curr = (bool*)malloc(sizeof(bool) * numOfMilk);
	memset(curr, false, sizeof(bool) * numOfMilk);
	for (unsigned int currSick = 0; currSick < numSick; currSick++) {
		for (unsigned int i = 0; (i < numOfDrinks) && (drinks[i].time < sickPeople[currSick].time); i++) {
			if (drinks[i].person == sickPeople[currSick].person)
				curr[drinks[i].milk] = true;
		}
		for (unsigned int i = 0; i < numOfMilk; i++) {
			possibilities[i] &= curr[i];
			curr[i] = false;
		}
	}
	unsigned int* numOfOccerences = (unsigned int*)calloc(numOfMilk, sizeof(unsigned int));
	bool** occerence = (bool**)malloc(numOfMilk * sizeof(bool*));
	for (unsigned int i = 0; i < numOfMilk; i++)
		occerence[i] = (bool*)calloc(numOfPeople, sizeof(bool));
	for (unsigned int i = 0; i < numOfDrinks; i++)
		occerence[drinks[i].milk][drinks[i].person] = true;
	for (unsigned int i = 0; i < numOfMilk; i++) {
		for (unsigned int j = 0; j < numOfPeople; j++)
			numOfOccerences[i] += occerence[i][j];
	}
	unsigned int highest = 0;
	for (unsigned int i = 0; i < numOfMilk; i++) {
		if (possibilities[i])
			if (highest < numOfOccerences[i])
				highest = numOfOccerences[i];
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", highest);
	fclose(fp);
}

int main(void)
{
	//q1("paint.in", "paint.out");
	q2("speeding.in", "speeding.out");
	//q3("badmilk.in", "badmilk.out"); //did in USACO camp
	return 0;
}