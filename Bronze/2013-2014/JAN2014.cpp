#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
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

//brute force
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfHills = getNum;
	unsigned int* hill_ht = (unsigned int*)malloc(sizeof(unsigned int) * numOfHills);
	for (unsigned int i = 0; i < numOfHills; i++)
		hill_ht[i] = getNum;
	fclose(fp);
	unsigned int lowestCost = ~((unsigned int)0);
	unsigned int curr;
	for (unsigned int i = 17; i <= 100; i++) {
		curr = 0;
		for (unsigned int j = 0; j < numOfHills; j++)
			curr += (pow((i - 17) - hill_ht[j], 2) * (hill_ht[j] < i - 17)) + //less than the min
				(pow(hill_ht[j] - i, 2) * (hill_ht[j] > i)); //greater than then max
		if (curr < lowestCost)
			lowestCost = curr;
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", lowestCost);
	fclose(fp);
}

int compareNum(const void* p1, const void* p2)
{
	return *((unsigned int*)p1) - *((unsigned int*)p2);
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfIntra = getNum;
	unsigned int* distances = (unsigned int*)malloc(sizeof(unsigned int) * (numOfIntra + 1));
	unsigned int* times = (unsigned int*)malloc(sizeof(unsigned int) * numOfIntra);
	bool is_time;
	unsigned int currTimeNum = 0;
	unsigned int currDistNum = 0;
	for (unsigned int i = 0; i < numOfIntra; i++) {
		is_time = fgetc(fp) == 'T';
		fgetc(fp);
		if (is_time) {
			times[currTimeNum] = getNum;
			currTimeNum++;
		}
		else {
			distances[currDistNum] = getNum;
			currDistNum++;
		}
	}
	fclose(fp);
	distances[currDistNum] = 1000;
	unsigned int numOfDists = currDistNum + 1;
	unsigned int numOfTimes = currTimeNum;
	qsort(distances, numOfDists, sizeof(unsigned int), compareNum);
	qsort(times, numOfTimes, sizeof(unsigned int), compareNum);
	currTimeNum = 0; currDistNum = 0;
	double currDist = 0;
	double currTime = 0;
	unsigned int speed = 1;
	while (currDistNum < numOfDists)
		if (!(currTimeNum < numOfTimes) || (times[currTimeNum] > ((distances[currDistNum] - currDist) * speed) + currTime)) { //the distance is sooner
			currTime += (distances[currDistNum] - currDist) * speed;
			currDist = distances[currDistNum];
			currDistNum++;
			speed++;
		}
		else { //doing the time
			currDist += (times[currTimeNum] - currTime) * (1 / (double)speed);
			currTime = times[currTimeNum];
			currTimeNum++;
			speed++;
		}
	currTime = (unsigned int)currTime + (currTime - (unsigned int)currTime >= 0.5);
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", (unsigned int)currTime);
	fclose(fp);
}

struct group
{
	unsigned int total;
	unsigned int numOfCows;
};
unsigned int recursive(group teams[4], unsigned int skills[12], unsigned int currCow)
{
	if (currCow == 12) {
		unsigned int largest = 0;
		unsigned int smallest = 0;
		for (unsigned int i = 1; i < 4; i++)
			if (teams[i].total > teams[largest].total)
				largest = i;
			else if (teams[i].total < teams[smallest].total)
				smallest = i;
		return teams[largest].total - teams[smallest].total;
	}
	unsigned int smallest = ~0;
	unsigned int curr;
	for (unsigned int i = 0; i < 4; i++)
		if (teams[i].numOfCows < 3) {
			teams[i].numOfCows++;
			teams[i].total += skills[currCow];
			curr = recursive(teams, skills, currCow + 1);
			if (curr < smallest)
				smallest = curr;
			teams[i].numOfCows--;
			teams[i].total -= skills[currCow];
		}
	return smallest;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int skills[12];
	for (unsigned int i = 0; i < 12; i++)
		skills[i] = getNum;
	fclose(fp);
	group teams[4] = { { 0,0 }, { 0,0 }, { 0,0 }, { 0,0 } };
	unsigned int ans = recursive(teams, skills, 0);
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", ans);
	fclose(fp);
}

int main(void)
{
	//q1("skidesign.in", "skidesign.out");
	//q2("slowdown.in", "slowdown.out");
	q3("bteams.in", "bteams.out");
	//system("pause");
	return 0;
}