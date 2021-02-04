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

struct cowMilk
{
	unsigned int milk;
	unsigned int refrence;
};
int compareMilk(const void* p1, const void* p2)
{
	return ((cowMilk*)p1)->milk - ((cowMilk*)p2)->milk;
}
void q1(const char* fin, const char* fout)
{
	char* cows[] = { "Bessie", "Elsie", "Daisy", "Gertie", "Annabelle", "Maggie", "Henrietta" };
	cowMilk* values = (cowMilk*)malloc(sizeof(cowMilk) * 7);
	for (unsigned int i = 0; i < 7; i++) {
		values[i].milk = 0;
		values[i].refrence = i;
	}
	FILE* fp = fopen(fin, "r");
	unsigned int numOfInstra = getNum; char ch;
	for (unsigned int i = 0; i < numOfInstra; i++) {
		ch = fgetc(fp);
		while (fgetc(fp) != ' ');
		for (unsigned int i = 0; i < 7; i++)
			if (ch == cows[i][0])
				values[i].milk += getNum;
	}
	fclose(fp);
	qsort(values, 7, sizeof(cowMilk), compareMilk);
	unsigned int first = values[0].milk;
	fp = fopen(fout, "w");
	for(unsigned int i = 0; i < 7; i++)
		if (values[i].milk != first) {
			if ((i == 6) || (values[i].milk != values[i + 1].milk)) {
				fprintf(fp, cows[values[i].refrence]);
				fclose(fp);
				return;
			}
			else {
				fprintf(fp, "Tie");
				fclose(fp);
				return;
			}
		}
	fprintf(fp, "Tie");
	fclose(fp);
}

void q2(const char* fin, const char* fout)
{
	unsigned int clock = 0, anti = 0;
	FILE* fp = fopen(fin, "r");
	unsigned int games = getNum;
	unsigned int num1, num2;
	for (unsigned int i = 0; i < games; i++) {
		num1 = getNum; num2 = getNum;
		if ((num1 == num2 - 1) || ((num1 == 3) && (num2 == 1)))
			clock++;
		else if (num1 != num2)
			anti++;
	}
	fclose(fp);
	fp = fopen(fout, "w");
	fprintf(fp, "%d", _max(clock, anti));
	fclose(fp);
}

void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int sideLen = getNum;
	bool** grid = (bool**)malloc(sizeof(bool*) * sideLen);
	for (unsigned int i = 0; i < sideLen; i++) {
		grid[i] = (bool*)malloc(sizeof(bool) * sideLen);
		for (unsigned int j = 0; j < sideLen; j++)
			grid[i][j] = fgetc(fp) - '0';
		fgetc(fp); //newline
	}
	fclose(fp);
	int pointX;
	int pointY;
	unsigned int startCol;
	unsigned int ans = 0;
	while (++ans) {
		pointX = -1;
		pointY = -1;
		startCol = 0;
		for (unsigned int i = 0; i < sideLen; i++) {
			for (unsigned int j = startCol; j < sideLen; j++)
				if (grid[i][j]) { //is tip
					pointX = i;
					pointY = j;
					startCol = j;
				}
		}
		if ((pointX == -1) && (pointY == -1)) {
			ans--;
			break;
		}
		for (unsigned int i = 0; i <= pointX; i++)
			for (unsigned int j = 0; j <= pointY; j++)
				grid[i][j] = !grid[i][j];
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d\n", ans);
	fclose(fp);
}

int main(void)
{
	//q1("notlast.in", "notlast.out");
	//q2("hps.in", "hps.out");
	q3("cowtip.in", "cowtip.out");
}