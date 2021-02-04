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

/*void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	//fp = fopen(fpIn, "r");
	int day = getNumInFile(&fp);
	int hour = getNumInFile(&fp);
	int min = getNumInFile(&fp);
	fclose(fp);
	int total = (1440 * (day - 11)) + (60 * (hour - 11)) + (min - 11);
	if (total < 0)
		total = -1;
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	//fp = fopen(fpOut, "w");
	fprintf(fp, "%d", total);
	fclose(fp);
}*/

int works(long long thr, long long trial)
{
	long long change = abs(trial - thr);
	int power;
	for (power = 0; change % 3 == 0; power++)
		change /= 3;
	if (change > 3)
		return -1;
	else
	{
		int currPow = (long long)(thr / pow(3, power)) % 3;
		if (trial - thr < 0)
			change *= -1;
		if ((currPow + change < 3) && (change + currPow >= 0))
			return 1;
		else
			return -1;
	}
}
void q2(const char* fpIn, const char* fpOut)
{
	long long binaray = 0;
	int bi_len = 0;
	int thr_len = 0;
	long long baseThree = 0;
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	//fp = fopen(fpIn, "r");
	char ch = fgetc(fp);
	while (ch != '\n')
	{
		binaray = binaray * 2 + ch - '0';
		bi_len++;
		ch = fgetc(fp);
	}
	ch = fgetc(fp);
	while (ch != '\n')
	{
		baseThree = baseThree * 3 + ch - '0';
		thr_len++;
		ch = fgetc(fp);
	}
	fclose(fp);

	bool found = 0;
	int power = pow(2, bi_len - 1);
	long long trial;
	for (int i = 0; found != 1; i++)
	{
		if ((binaray / power) % 2 == 0)
			trial = binaray + power;
		else
			trial = binaray - power;
		if (works(baseThree, trial) == 1)
			found = 1;
		power /= 2;
	}
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	//fp = fopen(fpOut, "w");
	fprintf(fp, "%d", trial);
	fclose(fp);
}

/*int compare(const void* p1, const void* p2)
{
	int* a = (int*)p1;
	int* b = (int*)p2;
	return *a - *b;
}
int* doThings(int* sequence, int numSequence)
{
	qsort(sequence, numSequence, sizeof(int), compare);
	for (int i = numSequence - 1; i >= 0; i--)
		sequence[i] -= sequence[0];
	return sequence;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	//fp = fopen(fpIn, "r");
	int numFJ_Notes = getNumInFile(&fp);
	int* FJ_Notes = (int*)malloc(sizeof(int) * numFJ_Notes);
	for (int i = 0; i < numFJ_Notes; i++)
		FJ_Notes[i] = getNumInFile(&fp);
	int numSequence = getNumInFile(&fp);
	int* sequence = (int*)malloc(sizeof(int) * numSequence);
	for (int i = 0; i < numSequence; i++)
		sequence[i] = getNumInFile(&fp);
	fclose(fp);

	int* cheak = (int*)malloc(sizeof(int) * numSequence);
	sequence = doThings(sequence, numSequence);
	
	int numOfPoints = 0;
	int* points = (int*)malloc(sizeof(int) * numFJ_Notes);
	for (int i = 0; i <= numFJ_Notes - numSequence; i++)
	{
		memcpy(cheak, FJ_Notes + i, sizeof(int) * numSequence);
		cheak = doThings(cheak, numSequence);
		if (memcmp(cheak, sequence, sizeof(int) * numSequence) == 0)
		{
			points[numOfPoints] = i + 1;
			numOfPoints++;
		}
	}
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	//fp = fopen(fpOut, "w");
	fprintf(fp, "%d\n", numOfPoints);
	for(int i = 0; i < numOfPoints; i++)
		fprintf(fp, "%d\n", points[i]);
	fclose(fp);
}*/

/*char* recursave(char* grid, int lenght, int with, int startRow, int startCol, char value)
{
	if ((startRow != 0) && (grid[(startRow - 1) * with + startCol] == 'X'))
	{
		grid[(startRow - 1) * with + startCol] = value;
		grid = recursave(grid, lenght, with, startRow - 1, startCol, value);
	}
	if ((startCol != 0) && (grid[startRow * with + startCol - 1] == 'X'))
	{
		grid[startRow * with + startCol - 1] = value;
		grid = recursave(grid, lenght, with, startRow, startCol - 1, value);
	}
	if ((startRow != lenght - 1) && (grid[(startRow + 1) * with + startCol] == 'X'))
	{
		grid[(startRow + 1) * with + startCol] = value;
		grid = recursave(grid, lenght, with, startRow + 1, startCol, value);
	}
	if ((startCol != with - 1) && (grid[startRow * with + startCol + 1] == 'X'))
	{
		grid[startRow * with + startCol + 1] = value;
		grid = recursave(grid, lenght, with, startRow, startCol + 1, value);
	}
	return grid;
}
char* sortGrid(char* grid, int length, int with, char value)
{
	int found = 0;
	int loc_row;
	int loc_col;
	for(int i = 0; found != 1; i++)
		for(int j = 0; found != 1; j++)
			if (grid[i * with + j] == 'X')
			{
				found = 1;
				loc_row = i;
				loc_col = j;
				grid[i * with + j] = value;
			}
	grid = recursave(grid, length, with, loc_row, loc_col, value);
	return grid;
}
int closeTwo(char* grid, int lenght, int with, int currRow, int currCol)
{
	int closest = 100000000000;
	int currClosest;
	for(int i = 0; i < lenght; i++)
		for(int j = 0; j < with; j++)
			if (grid[i * with + j] == '2')
			{
				currClosest = abs(currRow - i) + abs(currCol - j);
				if (currClosest < closest)
					closest = currClosest;
			}
	return closest;
}
void q4(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	//fp = fopen(fpIn, "r");
	int length = getNumInFile(&fp);
	int with = getNumInFile(&fp);
	char* grid = (char*)malloc(sizeof(char) * length * with);
	for (int i = 0; i < length; i++) //form grid
	{
		for (int j = 0; j < with; j++)
			grid[i * with + j] = fgetc(fp);
		fgetc(fp);
	}
	fclose(fp);
	grid = sortGrid(grid, length, with, '1');
	grid = sortGrid(grid, length, with, '2'); //or can find all X's and make them '2'
	int closest = 10000000000;
	int currClosest;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < with; j++)
			if (grid[i * with + j] == '1')
			{
				currClosest = closeTwo(grid, length, with, i, j);
				if (currClosest < closest)
					closest = currClosest;
			}
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	//fp = fopen(fpOut, "w");
	fprintf(fp, "%d", closest - 1);
	fclose(fp);
}*/

int main(void)
{
	//q1("./ctiming.in", "./ctiming.out");
	q2("./digits.in", "./digits.out");
	//q3("./moosick.in", "./moosick.out");
	//q4("./pageant.in", "./pageant.out");
	system("pause");
	return 0;
}