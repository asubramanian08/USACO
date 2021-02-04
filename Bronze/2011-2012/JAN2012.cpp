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
char* readStrInFile(FILE** fp, int size)
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
	return str;
}
long long getNumInFile(FILE** fp)
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

struct gift
{
	int price;
	int shipping;
};
int totalCmp(const void* p1, const void* p2)
{
	gift* a = (gift*)p1;
	gift* b = (gift*)p2;
	return (a->price + a->shipping) - (b->price + b->shipping);
}
int incomeCmp(const void* p1, const void* p2)
{
	gift* a = (gift*)p1;
	gift* b = (gift*)p2;
	return a->price - b->price;
}
int cooponCmp(const void* p1, const void* p2)
{
	gift* a = (gift*)p1;
	gift* b = (gift*)p2;
	return ((a->price/2) + a->shipping) - ((b->price/2) + b->shipping);
}
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfCows = getNumInFile(&fp);
	int buget = getNumInFile(&fp);
	gift* cowWants = (gift*)malloc(sizeof(gift) * numOfCows);
	for (int i = 0; i < numOfCows; i++)
	{
		cowWants[i].price = getNumInFile(&fp);
		cowWants[i].shipping = getNumInFile(&fp);
	}
	fclose(fp);
	qsort(cowWants, numOfCows, sizeof(gift), totalCmp);
	int maxGifts = 0;
	int currVal = 0;
	while (currVal <= buget)
	{
		currVal += cowWants[maxGifts].price + cowWants[maxGifts].shipping;
		maxGifts++;
	}
	maxGifts--;
	currVal -= cowWants[maxGifts].price + cowWants[maxGifts].shipping;
	int change = 0;
	int newValChange = currVal;
	if (maxGifts != 0)
	{
		qsort(cowWants, maxGifts, sizeof(gift), incomeCmp);
		newValChange -= cowWants[maxGifts - 1].price / 2;
		while (newValChange <= buget)
		{
			newValChange += cowWants[maxGifts].price + cowWants[maxGifts].shipping;
			change++;
		}
		change--;
		newValChange -= cowWants[maxGifts].price + cowWants[maxGifts].shipping;
	}
	qsort(cowWants + maxGifts, numOfCows - maxGifts, sizeof(gift), cooponCmp);
	if (((cowWants[maxGifts].price / 2) + cowWants[maxGifts].shipping <= buget - currVal) && change == 0)
		maxGifts++;
	maxGifts += change;
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", maxGifts);
	fclose(fp);
}

int compareFunc(const void* p1, const void* p2)
{
	return (*(int*)p1) - (*(int*)p2);
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfStacks = getNumInFile(&fp);
	int numOfInstructions = getNumInFile(&fp);
	int* stacks = (int*)calloc(numOfStacks, sizeof(int));
	for (int i = 0; i < numOfInstructions; i++)
	{
		int j = getNumInFile(&fp) - 1;
		int till = getNumInFile(&fp);
		while (j < till)
		{
			stacks[j]++;
			j++;
		}
	}
	fclose(fp);
	qsort(stacks, numOfStacks, sizeof(int), compareFunc);
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", stacks[numOfStacks / 2]);
	fclose(fp);
}

int mildred(int totalMoves, int mRow, int mCol, int bRow, int bCol, int feild[7][7], int endMoves);
int bessie(int totalMoves, int mRow, int mCol, int bRow, int bCol, int feild[7][7], int endMoves)
{
	int total = 0;
	if (feild[bRow - 1][bCol] != 1)
	{
		feild[bRow - 1][bCol] = 1;
		total += mildred(totalMoves + 1, mRow, mCol, bRow - 1, bCol, feild, endMoves);
		feild[bRow - 1][bCol] = 0;
	}
	if (feild[bRow + 1][bCol] != 1)
	{
		feild[bRow + 1][bCol] = 1;
		total += mildred(totalMoves + 1, mRow, mCol, bRow + 1, bCol, feild, endMoves);
		feild[bRow + 1][bCol] = 0;
	}
	if (feild[bRow][bCol + 1] != 1)
	{
		feild[bRow][bCol + 1] = 1;
		total += mildred(totalMoves + 1, mRow, mCol, bRow, bCol + 1, feild, endMoves);
		feild[bRow][bCol + 1] = 0;
	}
	if (feild[bRow][bCol - 1] != 1)
	{
		feild[bRow][bCol - 1] = 1;
		total += mildred(totalMoves + 1, mRow, mCol, bRow, bCol - 1, feild, endMoves);
		feild[bRow][bCol - 1] = 0;
	}
	return total;
}
int mildred(int totalMoves, int mRow, int mCol, int bRow, int bCol, int feild[7][7], int endMoves)
{
	if (totalMoves == endMoves)
	{
		if (((feild[mRow - 1][mCol] != 1) || (feild[mRow + 1][mCol] != 1) || (feild[mRow][mCol + 1] != 1) || (feild[mRow][mCol - 1] != 1)) &&
			((feild[bRow - 1][bCol] != 1) || (feild[bRow + 1][bCol] != 1) || (feild[bRow][bCol + 1] != 1) || (feild[bRow][bCol - 1] != 1)))
			return 1;
		else
			return 0;
	}
	int total = 0;
	if (feild[mRow - 1][mCol] != 1)
	{
		feild[mRow - 1][mCol] = 1;
		total += bessie(totalMoves, mRow - 1, mCol, bRow, bCol, feild, endMoves);
		feild[mRow - 1][mCol] = 0;
	}
	if (feild[mRow + 1][mCol] != 1)
	{
		feild[mRow + 1][mCol] = 1;
		total += bessie(totalMoves, mRow + 1, mCol, bRow, bCol, feild, endMoves);
		feild[mRow + 1][mCol] = 0;
	}
	if (feild[mRow][mCol + 1] != 1)
	{
		feild[mRow][mCol + 1] = 1;
		total += bessie(totalMoves, mRow, mCol + 1, bRow, bCol, feild, endMoves);
		feild[mRow][mCol + 1] = 0;
	}
	if (feild[mRow][mCol - 1] != 1)
	{
		feild[mRow][mCol - 1] = 1;
		total += bessie(totalMoves, mRow, mCol - 1, bRow, bCol, feild, endMoves);
		feild[mRow][mCol - 1] = 0;
	}
	return total;
}
void q3(const char* fpIn, const char* fpOut)
{
	int feild[7][7] = { {1, 1, 1, 1, 1, 1, 1}, {1, 1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 1}, {1, 1, 1, 1, 1, 1, 1} };
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numTaken = getNumInFile(&fp);
	for (int i = 0; i < numTaken; i++)
		feild[getNumInFile(&fp)][getNumInFile(&fp)] = 1;
	fclose(fp);
	int numWays = mildred(0, 1, 1, 5, 5, feild, ((25 - numTaken)/2) - 1);
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", numWays);
	fclose(fp);
}

int main(void)
{
	//q1("./gifts.in", "./gifts.out");
	q2("./stacking.in", "./stacking.out");
	//q3("./grazing.in", "./grazing.out");
	//system("pause");
	return 0;
}