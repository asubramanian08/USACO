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

void q1(const char* fpIn, const char* fpOut)
{
	int total = 0;
	int change = 0;
	int curr;
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfStack = getNumInFile(&fp);
	int* stackNums = (int*)malloc(sizeof(int) * numOfStack);
	for (int i = 0; i < numOfStack; i++)
	{
		curr = getNumInFile(&fp);
		total += curr;
		stackNums[i] = curr;
	}
	fclose(fp);
	for (int i = 0; i < numOfStack; i++)
		change += abs((total / numOfStack) - stackNums[i]);
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", change / 2);
	fclose(fp);
}

int numOfCows;
int* listPtr;
int compareFunc(const void* p1, const void* p2)
{
	int num1 = 0;
	int num2 = 0;
	int watch1 = *(int*)p1;
	int watch2 = *(int*)p2;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < numOfCows; j++)
		{
			if ((listPtr[i * numOfCows + j] == watch1) || (listPtr[i * numOfCows + j] == watch2))
			{
				if (listPtr[i * numOfCows + j] == watch1)
					num1++;
				else
					num2++;
				break;
			}
		}
	}
	return num2 - num1;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	numOfCows = getNumInFile(&fp);
	listPtr = (int*)malloc(sizeof(int) * 5 * numOfCows);
	int numOfElements = numOfCows * 5;
	for (int i = 0; i < numOfElements; i++)
		listPtr[i] = getNumInFile(&fp);
	fclose(fp);
	qsort(listPtr, numOfCows, sizeof(int), compareFunc);
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	for (int i = 0; i < numOfCows; i++)
		fprintf(fp, "%d\n", listPtr[i]);
	fclose(fp);
}

struct weight
{
	unsigned long num;
	unsigned long pow;
};
weight getNum_pow(FILE** fp)
{
	weight cow;
	cow.num = 0;
	cow.pow = 1;
	char ch = fgetc(*fp);
	while((ch != ' ') && (ch != '\n'))
	{
		cow.num = (cow.num * 10) + ch - '0';
		cow.pow *= 10;
		ch = fgetc(*fp);
	}
	return cow;
}
bool carryOver(weight newCow, weight ornl)
{
	unsigned long biggestPow = newCow.pow;
	if (ornl.pow > biggestPow)
		biggestPow = ornl.pow;
	for (unsigned long i = 1; i <= biggestPow; i *= 10)
	{
		if (((newCow.num / i) % 10) + ((ornl.num / i) % 10) > 9)
			return 1;
	}
	return 0;
}
int recursave(int numOfCows, weight* cows, int currCow, weight curr)
{
	if (currCow == numOfCows)
		return 0;
	int total = recursave(numOfCows, cows, currCow + 1, curr);
	if (carryOver(cows[currCow], curr) == 0)
	{
		if (curr.pow < cows[currCow].pow)
			curr.pow = cows[currCow].pow;
		curr.num += cows[currCow].num;
		int two = recursave(numOfCows, cows, currCow + 1, curr) + 1;
		if (total < two)
			total = two;
	}
	return total;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfCows = getNumInFile(&fp);
	weight* cows = (weight*)malloc(sizeof(weight) * numOfCows);
	for (int i = 0; i < numOfCows; i++)
		cows[i] = getNum_pow(&fp);
	fclose(fp);
	weight curr;
	curr.num = 0;
	curr.pow = 1;
	int total = recursave(numOfCows, cows, 0, curr);
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", total);
	fclose(fp);
}

int main()
{
	//q1("./haybales.in", "./haybales.out");
	q2("./photo.in", "./photo.out");
	//q3("./escape.in", "./escape.out");
}