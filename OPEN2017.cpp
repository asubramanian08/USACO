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
	FILE* fp = fopen(fin, "r");
	int FJ = getNum;
	int cow = getNum;
	fclose(fp);
	
	unsigned int ans;
	unsigned int goTill = 1;
	bool dir = true;
	int curr = FJ;
	for (ans = 0; curr != cow; ans++) {
		if (dir)
			curr++;
		else
			curr--;
		if (abs(curr - FJ) == goTill) {
			goTill *= 2;
			dir = !dir;
		}
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum, numOfGenes = getNum;
	char ch; char** spotted = (char**)malloc(sizeof(char*) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		spotted[i] = (char*)malloc(sizeof(char) * numOfGenes);
		for (unsigned int j = 0; j < numOfGenes; j++) {
			ch = fgetc(fp);
			if (ch == 'A')
				spotted[i][j] = 0;
			else if (ch == 'G')
				spotted[i][j] = 1;
			else if (ch == 'T')
				spotted[i][j] = 2;
			else
				spotted[i][j] = 3;
		}
		fgetc(fp); //newline
	}
	char** plain = (char**)malloc(sizeof(char*) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		plain[i] = (char*)malloc(sizeof(char) * numOfGenes);
		for (unsigned int j = 0; j < numOfGenes; j++) {
			ch = fgetc(fp);
			if (ch == 'A')
				plain[i][j] = 0;
			else if (ch == 'G')
				plain[i][j] = 1;
			else if (ch == 'T')
				plain[i][j] = 2;
			else
				plain[i][j] = 3;
		}
		fgetc(fp); //newline
	}
	fclose(fp);
	unsigned int ans = 0;
	bool* gene = (bool*)malloc(sizeof(bool) * 4);
	for (unsigned int i = 0; i < numOfGenes; i++) {
		for (unsigned int j = 0; j < 4; j++)
			gene[j] = false;
		for (unsigned int j = 0; j < numOfCows; j++)
			gene[plain[j][i]] = true;
		ans++;
		for (unsigned int j = 0; j < numOfCows; j++)
			if (gene[spotted[j][i]]) {
				ans--;
				break;
			}
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

struct rect
{
	unsigned int high = 0;
	unsigned int low = 100;
	unsigned int left = 100;
	unsigned int right = 0;
};
void q3(const char* fin, const char* fout)
{
	bool* canHappen = (bool*)calloc(10, sizeof(bool));
	rect* rects = (rect*)malloc(10 * sizeof(rect));
	for (unsigned int i = 0; i < 10; i++) {
		rects[i].high = 0;
		rects[i].low = 100;
		rects[i].right = 0;
		rects[i].left = 100;
	}
	FILE* fp = fopen(fin, "r");
	unsigned int sideLen = getNum;
	unsigned int** grid = (unsigned int**)malloc(sizeof(unsigned int*) * sideLen);
	for (unsigned int i = 0; i < sideLen; i++) {
		grid[i] = (unsigned int*)malloc(sizeof(unsigned int) * sideLen);
		for (unsigned int j = 0; j < sideLen; j++) {
			grid[i][j] = fgetc(fp) - '0';
			canHappen[grid[i][j]] = true;
			if (rects[grid[i][j]].high < i)
				rects[grid[i][j]].high = i;
			if (rects[grid[i][j]].low > i)
				rects[grid[i][j]].low = i;
			if (rects[grid[i][j]].left > j)
				rects[grid[i][j]].left = j;
			if (rects[grid[i][j]].right < j)
				rects[grid[i][j]].right = j;
		}
		fgetc(fp);//newline
	}
	fclose(fp);
	for (unsigned int i = 1; i < 10; i++) {
		if (rects[i].low == 100)
			continue;
		for (unsigned int j = rects[i].low; j <= rects[i].high; j++)
			for (unsigned int k = rects[i].left; k <= rects[i].right; k++)
				if (grid[j][k] != i)
					canHappen[grid[j][k]] = false;
	}
	unsigned int ans = 0;
	for (unsigned int i = 1; i < 10; i++)
		ans += canHappen[i];
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

int main(void)
{
	//q1("lostcow.in", "lostcow.out");
	//q2("cownomics.in", "cownomics.out");
	q3("art.in", "art.out");
}