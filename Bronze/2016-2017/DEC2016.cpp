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
//#define _min(a,b) a<b

void q1(const char* fpIn, const char* fpOut)
{
	FILE * fp = fopen(fpIn, "r");
	unsigned int squareLowX = getNum, squareLowY = getNum, squareHighX = getNum, squareHighY = getNum;
	unsigned int curr;
	if ((curr = getNum) < squareLowX)
		squareLowX = curr;
	if ((curr = getNum) < squareLowY)
		squareLowY = curr;
	if ((curr = getNum) > squareHighX)
		squareHighX = curr;
	if ((curr = getNum) > squareHighY)
		squareHighY = curr;
	unsigned int ans = squareHighY - squareLowY;
	if (squareHighY - squareLowY < squareHighX - squareLowX)
		ans = squareHighX - squareLowX;
	fclose(fp);
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", ans * ans);
	fclose(fp);
}

void q2(const char* fpIn, const char* fpOut)
{
	unsigned int* lettersNeeded = (unsigned int*)calloc(26, sizeof(unsigned int));
	unsigned int* wrd1 = (unsigned int*)malloc(sizeof(unsigned int) * 26);
	unsigned int* wrd2 = (unsigned int*)malloc(sizeof(unsigned int) * 26);
	int numOfChars;
	char* wordStr;
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfBoards = getNum;
	for (unsigned int i = 0; i < numOfBoards; i++) {
		memset(wrd1, 0, sizeof(unsigned int) * 26);
		wordStr = readStrInFile(&fp, 10, &numOfChars);
		numOfChars--;
		for (unsigned int i = 0; i < numOfChars; i++)
			wrd1[wordStr[i] - 'a']++;

		memset(wrd2, 0, sizeof(unsigned int) * 26);
		wordStr = readStrInFile(&fp, 10, &numOfChars);
		numOfChars--;
		for (unsigned int i = 0; i < numOfChars; i++)
			wrd2[wordStr[i] - 'a']++;

		for (unsigned int i = 0; i < 26; i++)
			if (wrd1[i] > wrd2[i])
				lettersNeeded[i] += wrd1[i];
			else
				lettersNeeded[i] += wrd2[i];
	}
	fclose(fp);
	fp = fopen(fpOut, "w");
	for (unsigned int i = 0; i < 26; i++)
		fprintf(fp, "%d\n", lettersNeeded[i]);
	fclose(fp);
}

void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int rows = getNum;
	unsigned int cols = getNum;
	unsigned int amplify = getNum;
	char** signal = (char**)malloc(sizeof(char*) * rows);
	for (unsigned int i = 0; i < rows; i++) {
		signal[i] = (char*)malloc(sizeof(char) * cols);
		for (unsigned int j = 0; j < cols; j++)
			signal[i][j] = fgetc(fp);
		fgetc(fp); //newline
	}
	fclose(fp);
	fp = fopen(fpOut, "w");
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < amplify; j++) {
			for (unsigned int k = 0; k < cols; k++) {
				for (unsigned int l = 0; l < amplify; l++) {
					fprintf(fp, "%c", signal[i][k]);
				}
			}
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

int main(void)
{
	//q1("square.in", "square.out");
	//q2("blocks.in", "blocks.out");
	q3("cowsignal.in", "cowsignal.out");

	//system("pause");
	return 0;
}