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

struct point
{
	int x;
	int y;
};
struct rect
{
	point lowerLeft;
	point upperRight;
};
void q1(const char* fpIn, const char* fpOut)
{
	rect food1;
	rect food2;
	rect truck;
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	food1.lowerLeft.x = getNumInFile(&fp);
	food1.lowerLeft.y = getNumInFile(&fp);
	food1.upperRight.x = getNumInFile(&fp);
	food1.upperRight.y = getNumInFile(&fp);
	food2.lowerLeft.x = getNumInFile(&fp);
	food2.lowerLeft.y = getNumInFile(&fp);
	food2.upperRight.x = getNumInFile(&fp);
	food2.upperRight.y = getNumInFile(&fp);
	truck.lowerLeft.x = getNumInFile(&fp);
	truck.lowerLeft.y = getNumInFile(&fp);
	truck.upperRight.x = getNumInFile(&fp);
	truck.upperRight.y = getNumInFile(&fp);
	fclose(fp);
	rect int1;
	rect int2;
	
	if ((truck.lowerLeft.y <= food1.upperRight.y) && (truck.lowerLeft.y >= food1.lowerLeft.y))
		int1.lowerLeft.y = truck.lowerLeft.y;
	else if (truck.lowerLeft.y > food1.upperRight.y)
		int1.lowerLeft.y = food1.upperRight.y;
	else
		int1.lowerLeft.y = food1.lowerLeft.y;
	if ((truck.upperRight.y <= food1.upperRight.y) && (truck.upperRight.y >= food1.lowerLeft.y))
		int1.upperRight.y = truck.upperRight.y;
	else if (truck.upperRight.y > food1.upperRight.y)
		int1.upperRight.y = food1.upperRight.y;
	else
		int1.upperRight.y = food1.lowerLeft.y;

	if ((truck.lowerLeft.x <= food1.upperRight.x) && (truck.lowerLeft.x >= food1.lowerLeft.x))
		int1.lowerLeft.x = truck.lowerLeft.x;
	else if (truck.lowerLeft.x > food1.upperRight.x)
		int1.lowerLeft.x = food1.upperRight.x;
	else
		int1.lowerLeft.x = food1.lowerLeft.x;
	if ((truck.upperRight.x <= food1.upperRight.x) && (truck.upperRight.x >= food1.lowerLeft.x))
		int1.upperRight.x = truck.upperRight.x;
	else if (truck.upperRight.x > food1.upperRight.x)
		int1.upperRight.x = food1.upperRight.x;
	else
		int1.upperRight.x = food1.lowerLeft.x;


	if ((truck.lowerLeft.y <= food2.upperRight.y) && (truck.lowerLeft.y >= food2.lowerLeft.y))
		int2.lowerLeft.y = truck.lowerLeft.y;
	else if (truck.lowerLeft.y > food2.upperRight.y)
		int2.lowerLeft.y = food2.upperRight.y;
	else
		int2.lowerLeft.y = food2.lowerLeft.y;
	if ((truck.upperRight.y <= food2.upperRight.y) && (truck.upperRight.y >= food2.lowerLeft.y))
		int2.upperRight.y = truck.upperRight.y;
	else if (truck.upperRight.y > food2.upperRight.y)
		int2.upperRight.y = food2.upperRight.y;
	else
		int2.upperRight.y = food2.lowerLeft.y;

	if ((truck.lowerLeft.x <= food2.upperRight.x) && (truck.lowerLeft.x >= food2.lowerLeft.x))
		int2.lowerLeft.x = truck.lowerLeft.x;
	else if (truck.lowerLeft.x > food2.upperRight.x)
		int2.lowerLeft.x = food2.upperRight.x;
	else
		int2.lowerLeft.x = food2.lowerLeft.x;
	if ((truck.upperRight.x <= food2.upperRight.x) && (truck.upperRight.x >= food2.lowerLeft.x))
		int2.upperRight.x = truck.upperRight.x;
	else if (truck.upperRight.x > food2.upperRight.x)
		int2.upperRight.x = food2.upperRight.x;
	else
		int2.upperRight.x = food2.lowerLeft.x;

	int area1 = (int1.upperRight.y - int1.lowerLeft.y) * (int1.upperRight.x - int1.lowerLeft.x);
	int area2 = (int2.upperRight.y - int2.lowerLeft.y) * (int2.upperRight.x - int2.lowerLeft.x);
	int areaFood1 = (food1.upperRight.y - food1.lowerLeft.y) * (food1.upperRight.x - food1.lowerLeft.x);
	int areaFood2 = (food2.upperRight.y - food2.lowerLeft.y) * (food2.upperRight.x - food2.lowerLeft.x);
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", (areaFood1 - area1) + (areaFood2 - area2));
	fclose(fp);
}

/*void q2(const char* fpIn, const char* fpOut)
{
	int numOfCows;
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	numOfCows = getNumInFile(&fp);
	int* lineUp = (int*)malloc(sizeof(int) * numOfCows);
	for (int i = 0; i < numOfCows; i++)
		lineUp[i] = i;

	int* newLineUp = (int*)malloc(sizeof(int) * numOfCows);
	memcpy(newLineUp, lineUp, sizeof(int) * numOfCows);

	int* goTo = (int*)malloc(sizeof(int) * numOfCows);
	for (int i = 0; i < numOfCows; i++)
		goTo[getNumInFile(&fp) - 1] = i;

	int* ID_Nums = (int*)malloc(sizeof(int) * numOfCows);
	for (int i = 0; i < numOfCows; i++)
		ID_Nums[i] = getNumInFile(&fp);
	fclose(fp);

	for (int i = 0; i < 3; i++) //happens three times
	{
		for (int j = 0; j < numOfCows; j++)
			newLineUp[goTo[j]] = lineUp[j];
		memcpy(lineUp, newLineUp, sizeof(int) * numOfCows);
	}
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	for (int i = 0; i < numOfCows; i++)
		fprintf(fp, "%d\n", ID_Nums[lineUp[i]]);
	fclose(fp);
}*/

/*struct cowLogs
{
	int day;
	int cowNum;
	int change;
};
int findName(char* name)
{
	if (strncmp("Mildred", name, 8) == 0)
		return 0;
	else if (strncmp("Bessie", name, 8) == 0)
		return 1;
	return 2;
}
int compareFunc(const void* p1, const void* p2)
{
	cowLogs* a = (cowLogs*)p1;
	cowLogs* b = (cowLogs*)p2;
	return a->day - b->day;
}
bool findRank(int* highest, int* values, int* numOfHighest)
{
	int newHighest[3] = { 0 };
	int newNum = 0;
	int highestValue = values[0];
	if (values[1] > highestValue)
		highestValue = values[1];
	if (values[2] > highestValue)
		highestValue = values[2];
	for (int i = 0; i < 3; i++)
	{
		if (values[i] == highestValue)
		{
			newHighest[newNum] = i;
			newNum++;
		}
	}
	if (*numOfHighest != newNum)
	{
		*numOfHighest = newNum;
		memcpy(highest, newHighest, newNum);
		return 1;
	}
	else if (memcmp(newHighest, highest, newNum) != 0)
	{
		memcpy(highest, newHighest, newNum);
		return 1;
	}
	return 0;
}
void q3(const char* fpIn, const char* fpOut)
{
	int cowValues[3] = { 7, 7, 7 };
	int* highest = (int*)malloc(sizeof(int) * 3);
	highest[0] = 0;
	highest[1] = 1;
	highest[2] = 2;
	int numOfHighest = 3;
	int numOfChanges = 0;
	bool isChange;
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	int numOfLogs = getNumInFile(&fp);
	cowLogs* logs = (cowLogs*)malloc(sizeof(cowLogs) * numOfLogs);
	for (int i = 0; i < numOfLogs; i++)
	{
		logs[i].day = getNumInFile(&fp);
		logs[i].cowNum = findName(readStrInFile(&fp, 8));
		logs[i].change = getNumInFile(&fp);
	}
	fclose(fp);
	qsort(logs, numOfLogs, sizeof(cowLogs), compareFunc);

	for (int i = 0; i < numOfLogs; i++)
	{
		cowValues[logs[i].cowNum] += logs[i].change;
		isChange = findRank(highest, cowValues, &numOfHighest);
		numOfChanges += isChange;
	}
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", numOfChanges);
	fclose(fp);
}*/
int main(void)
{
	//q1("./billboard.in", "./billboard.out");
	//q2("./shuffle.in", "./shuffle.out");
	//q3("./measurement.in", "./measurement.out");
	system("pause");
	return 0;
}