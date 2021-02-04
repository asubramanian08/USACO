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
unsigned long long getNumInFile(FILE** fp)
{
	char ch = fgetc(*fp);
	unsigned long long total = 0;
	while ((ch != ' ') && (ch != '\n'))
	{
		total = total * 10 + ch - '0';
		ch = fgetc(*fp);
	}
	return total;
}
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
long long readNon_n_NegativesFromFile(FILE** fp)
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
/* q1(const char* filein, const char* fileout)
{
	int x, y, pointA, pointB;
	FILE* fp = NULL;
	//fopen_s(&fp, filein, "r");
	fp = fopen(filein, "r");
	pointA = getNumInFile(&fp);
	pointB = getNumInFile(&fp);
	x = getNumInFile(&fp);
	y = getNumInFile(&fp);
	fclose(fp);
	int minDistanceA, minDistanceB;
	if (abs(x - pointA) > abs(y - pointA))
		minDistanceA = abs(y - pointA);
	else
		minDistanceA = abs(x - pointA); 
	if (abs(x - pointB) > abs(y - pointB))
		minDistanceB = abs(y - pointB);
	else
		minDistanceB = abs(x - pointB);
	fp = NULL;
	//fopen_s(&fp, fileout, "w");
	fp = fopen(fileout, "w");
	if(abs(pointA - pointB) > minDistanceA + minDistanceB)
		fprintf(fp, "%d", minDistanceA + minDistanceB);
	else
		fprintf(fp, "%d", abs(pointA - pointB));
	fclose(fp);
}*/
/*int* read(FILE* fp, int* numOfItems)
{
	*numOfItems = getNumInFile(&fp);
	int* mainInfo = (int*)malloc(sizeof(int) * (*numOfItems));
	memset(mainInfo, 0, sizeof(int) * (*numOfItems));
	int lookingAt = 0;
	for (int i = 0; i < *numOfItems; i++)
		mainInfo[i] = getNumInFile(&fp);
	return mainInfo;
}
int compareFunc(const void* p1, const void* p2)
{
	int* a = (int*)p1;
	int* b = (int*)p2;
	return *a - *b;
}
int findAnswer(int* locations, int numOfCows)
{
	qsort(locations, numOfCows, sizeof(int), compareFunc);
	bool* pointsTo = (bool*)malloc(sizeof(bool) * numOfCows);
	memset(pointsTo, 0, sizeof(bool) * numOfCows);
	pointsTo[0] = 1;
	for (int i = 1; i < numOfCows - 1; i++) //fill up pointsTo
	{
		if (locations[i + 1] - locations[i] < locations[i] - locations[i - 1])
			pointsTo[i] = 1;
	}


	int numNotPassedTo = 0;
	if (pointsTo[1] != 0)
		numNotPassedTo++;
	if (pointsTo[numOfCows - 2] != 1)
		numNotPassedTo++;
	for (int i = 1; i < numOfCows - 1; i++) //who is not passed to
	{
		if((pointsTo[i - 1] != 1) && (pointsTo[i + 1] != 0))
			numNotPassedTo++;
	}


	int numOfOccilations = 0;
	bool beforePoints = 0;
	bool occNum1 = 0;
	bool occNum2 = 0;
	for (int i = 0; i < numOfCows; i++) //find num of occilations
	{
		if ((beforePoints != 1) && (occNum1 == 1) && (occNum2 == 0) && (pointsTo[i] != 0))
			numOfOccilations++;
		beforePoints = occNum1;
		occNum1 = occNum2;
		occNum2 = pointsTo[i];
	}
	if (beforePoints != 1 && occNum1 == 1)
		numOfOccilations++;


	return numOfOccilations + numNotPassedTo;
}
void q2(const char* filein, const char* fileout)
{
	bool* getsPassedTo;
	bool* gotPassedTo;
	int numOfCows;
	FILE* fp = NULL;
	//fopen_s(&fp, filein, "r");
	fp = fopen(filein, "r");
	int* mainInfo = read(fp, &numOfCows);
	fclose(fp);
	int answer = findAnswer(mainInfo, numOfCows);
	fp = NULL;
	//fopen_s(&fp, fileout, "w");
	fp = fopen(fileout, "w");
	fprintf(fp, "%d", answer);
	fclose(fp);
}*/
/*int read(FILE* fp, int** log, int** daysBroken)
{
	int numOfDays = getNumInFile(&fp);
	*daysBroken = (int*)malloc(sizeof(int) * numOfDays);
	*log = (int*)malloc(sizeof(int) * numOfDays);
	for (int i = 0; i < numOfDays; i++)
		* (*log + i) = readNon_n_NegativesFromFile(&fp);
	return numOfDays;
}
int findDaysToWaver(int* log, int** daysBroken, int numOfDays)
{
	if (log[0] > 0)
		return -1;
	(*daysBroken)[0] = 1;
	for (int i = 1; i < numOfDays; i++)
		* (*daysBroken + i) = -1;
	for (int i = 1; i < numOfDays; i++)
	{
		if (log[i] != -1)
		{
			*(*daysBroken + i - log[i]) = 1;
			for (int j = i - log[i] + 1; j <= i; j++)
			{
				if ((*daysBroken)[j] == 1)
					return -1;
				(*daysBroken)[j] = 0;
			}
		}
	}
	return 1;
}
void q3(const char* filein, const char* fileout)
{
	int* log;
	int* daysBroken;
	FILE* fp = NULL;
	//fopen_s(&fp, filein, "r");
	fp = fopen(filein, "r");
	int numOfDays = read(fp, &log, &daysBroken);
	fclose(fp);
	fp = NULL;
	//fopen_s(&fp, fileout, "w");
	fp = fopen(fileout, "w");
	if (findDaysToWaver(log, &daysBroken, numOfDays) == -1)
		fprintf(fp, "-1");
	else
	{
		int garenteeded = 0;
		int canChange = 0;
		for (int i = 0; i < numOfDays; i++)
		{
			if (daysBroken[i] == 1)
				garenteeded++;
			else if (daysBroken[i] == -1)
				canChange++;
		}
		fprintf(fp, "%d %d", garenteeded, garenteeded + canChange);
	}
	fclose(fp);
}*/
int main(void)
{
	//q1("./teleport.in", "./teleport.out");
	//q2("./hoofball.in", "./hoofball.out");
	//q3("./taming.in", "./taming.out"); //mistake: understaning the question cost me one test case
	system("pause");
	return 0;
}