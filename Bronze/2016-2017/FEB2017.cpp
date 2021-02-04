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

void q1(const char* fin, const char* fout)
{
	bool* vis = (bool*)calloc(10, sizeof(bool));
	bool* side = (bool*)calloc(10, sizeof(bool));
	unsigned int cross = 0, currCow;
	FILE* fp = fopen(fin, "r");
	unsigned int numOfInst = getNum;
	for (unsigned int i = 0; i < numOfInst; i++) {
		currCow = getNum - 1;
		if (vis[currCow]) {
			if (side[currCow] != getNum) {
				cross++;
				side[currCow] = !side[currCow];
			}
		}
		else {
			vis[currCow] = true;
			side[currCow] = getNum;
		}
	}
	fclose(fp);
	fp = fopen(fout, "w");
	fprintf(fp, "%d", cross);
	fclose(fp);
}

inline bool works(unsigned int a1, unsigned int a2, unsigned int b1, unsigned int b2)
{
	if (a1 < b1) {
		if ((a2 > b1) && (a2 < b2))
			return true;
		return false;
	}
	else {
		if ((a1 < b2) && (a2 > b2))
			return true;
		return false;
	}
}
void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	char* points = (char*)malloc(sizeof(char) * 52);
	for (unsigned int i = 0; i < 52; i++)
		points[i] = fgetc(fp);
	fclose(fp);
	bool* vis = (bool*)calloc(26, sizeof(bool));
	unsigned int** where_points = (unsigned int**)malloc(sizeof(unsigned int*) * 26);
	for (unsigned int i = 0; i < 26; i++)
		where_points[i] = (unsigned int*)malloc(sizeof(unsigned int) * 2);
	for (unsigned int i = 0; i < 52; i++) {
		where_points[points[i] - 'A'][vis[points[i] - 'A']] = i;
		vis[points[i] - 'A'] = true;
	}
	unsigned int ans = 0;
	for(unsigned int i = 0; i < 26; i++)
		for (unsigned int j = i + 1; j < 26; j++)
			if((i != j) && (works(where_points[i][0], where_points[i][1], where_points[j][0], where_points[j][1])))
				ans++;
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

struct cow
{
	unsigned int start;
	unsigned int qTime;
};
int compareStart(const void* p1, const void* p2)
{
	return ((cow*)p1)->start - ((cow*)p2)->start;
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum;
	cow* cows = (cow*)malloc(sizeof(cow) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].start = getNum;
		cows[i].qTime = getNum;
	}
	fclose(fp);
	qsort(cows, numOfCows, sizeof(cow), compareStart);
	unsigned int ended = 0;
	for (unsigned int i = 0; i < numOfCows; i++)
		ended = _max(ended, cows[i].start) + cows[i].qTime;
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ended);
	fclose(fp);
}

int main(void)
{
	q1("crossroad.in","crossroad.out");
	//q2("circlecross.in","circlecross.out");
	//q3("cowqueue.in","cowqueue.out");
}