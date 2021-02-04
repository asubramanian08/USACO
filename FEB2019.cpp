#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <stdarg.h>
//#include <assert.h>
int getNumInFile(FILE** fp)
{
	char ch = fgetc(*fp);
	int total = 0;
	while ((ch != ' ') && (ch != '\n'))
	{
		total = total * 10 + ch - '0';
		ch = fgetc(*fp);
	}
	return total;
}

/*void readFile(FILE* fp, int* cow1, int* cow2, int* cow3)
{
	*cow1 = getNumInFile(&fp);
	*cow2 = getNumInFile(&fp);
	*cow3 = getNumInFile(&fp);
}
int compare(const void* p1, const void* p2)
{
	int* a = (int*)p1;
	int* b = (int*)p2;
	if (*a > * b)
		return 1;
	else
		return -1;
}
void herding(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	int cows[3] = { 0 };
	readFile(fp, cows, cows + 1, cows + 2);
	qsort(cows, 3, sizeof(int), compare);
	fclose(fp);
	int distance1 = cows[1] - cows[0] - 1;
	int distance2 = cows[2] - cows[1] - 1;
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	if (distance1 == 0 && distance2 == 0)//for the minumum
		fprintf(fp, "0\n0");
	else if (distance1 == 1 || distance2 == 1)
		fprintf(fp, "1\n");
	else
		fprintf(fp, "2\n");
	if (distance1 != 0 || distance2 != 0) //maximum
	{
		if (distance1 > distance2)
			fprintf(fp, "%d", distance1);
		else
			fprintf(fp, "%d", distance2);
	}
	fclose(fp);
}*/

/*void placeNum(int** originalPtr, int numToSort, int whereToPlace)
{
	int* firstOfThree = *originalPtr;
	firstOfThree += (whereToPlace - 1) * 3;
	for (int i = 0; i < 3; i++)
	{
		if (firstOfThree[i] == 0)
		{
			*(*originalPtr + ((whereToPlace - 1) * 3) + i) = numToSort;
			i = 3;
		}
	}
}
int* read_Sort(FILE* fp, int* numFeilds, int* numCows)
{
	*numFeilds = getNumInFile(&fp);
	*numCows = getNumInFile(&fp);
	int* sortThing = (int*)malloc(sizeof(int) * (*numFeilds) * 3);
	memset(sortThing, 0, sizeof(int) * (*numFeilds) * 3);
	int num1, num2;
	for (int i = 0; i < *numCows; i++)
	{
		num1 = getNumInFile(&fp);
		num2 = getNumInFile(&fp);
		if (num1 > num2)
			placeNum(&sortThing, num2, num1);
		else
			placeNum(&sortThing, num1, num2);
	}
	return sortThing;
}
int numToPut(int num1, int num2, int num3)
{
	if (num1 != 1 && num2 != 1 && num3 != 1)
		return 1;
	else if (num1 != 2 && num2 != 2 && num3 != 2)
		return 2;
	else if (num1 != 3 && num2 != 3 && num3 != 3)
		return 3;
	else
		return 4;
}
int* findSequence(int numOfFeilds, int numOfCows, int* sortThing)
{
	int* finalSequence = (int*)malloc(sizeof(int) * (numOfFeilds + 1));
	memset(finalSequence, 0, sizeof(int) * (numOfFeilds +1));
	for (int i = 1; i <= numOfFeilds; i++)
		finalSequence[i] = numToPut(finalSequence[sortThing[(i - 1) * 3]], finalSequence[sortThing[(i - 1) * 3 + 1]], finalSequence[sortThing[(i - 1) * 3 + 2]]);
	return finalSequence;
}
void cyclingFood(const char* fpIn, const char* fpOut)
{
	int numFields, numCows;
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	int* sortThing = read_Sort(fp, &numFields, &numCows);
	fclose(fp);
	int* finalSequence = findSequence(numFields, numCows, sortThing);
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	for (int i = 1; i <= numFields; i++)
		fprintf(fp, "%d", finalSequence[i]);
	fclose(fp);
}*/

struct range
{
	int on_off_none;
	int high;
	int low;
};
bool on_off(FILE** fp)
{
	bool onOrOff = 0;
	if (fgetc(*fp) == 'n')
		onOrOff = 1;
	while (fgetc(*fp) != ' ');
	return onOrOff;
}
range* read(FILE * fp, int *setPoints)
{
	*setPoints = getNumInFile(&fp);
	range* ranges = (range*)malloc(sizeof(range) * (*setPoints + 2));
	memset(ranges, 0, sizeof(range) * (*setPoints + 2));
	for (int i = 1; i <= *setPoints; i++)
	{
		if (fgetc(fp) == 'n') //none
		{
			on_off(&fp); //to get rid of extra
			ranges[i].on_off_none = 3;
		}
		else if (on_off(&fp)) //on
			ranges[i].on_off_none = 1;
		else //off
			ranges[i].on_off_none = 2;
		ranges[i].low = getNumInFile(&fp);
		ranges[i].high = getNumInFile(&fp);
	}
	return ranges;
}
range* findLast(range* ranges, int setPointsNum)
{
	for (int i = 1; i <= setPointsNum; i++)
	{
		if (ranges[i].on_off_none == 3) //none
		{
			if (ranges[setPointsNum + 1].low)
			{
				if (ranges[i].low > ranges[setPointsNum + 1].low)
					ranges[setPointsNum + 1].low = ranges[i].low;
				if (ranges[i].high < ranges[setPointsNum + 1].high)
					ranges[setPointsNum + 1].high = ranges[i].high;
			}
			else
			{
				ranges[setPointsNum + 1].high = ranges[i].high;
				ranges[setPointsNum + 1].low = ranges[i].low;
			}
		}
		else if (ranges[i].on_off_none == 1) //on
		{
			if (ranges[setPointsNum + 1].low)
			{
				ranges[setPointsNum + 1].low += ranges[i].low;
				ranges[setPointsNum + 1].high += ranges[i].high;
			}
		}
		else //off
		{
			if (ranges[setPointsNum + 1].low)
			{
				ranges[setPointsNum + 1].low -= ranges[i].high;
				if (ranges[setPointsNum + 1].low < 0)
					ranges[setPointsNum + 1].low = 0;
				ranges[setPointsNum + 1].high -= ranges[i].low;
				if (ranges[setPointsNum + 1].high < 0)
					ranges[setPointsNum + 1].high = 0;
			}
		}
	}
	ranges[setPointsNum + 1].on_off_none = 3;
	return ranges;
}
range* findFirst(range* ranges, int setPointsNum)
{
	for (int i = setPointsNum + 1; i > 0; i--)
	{
		if (ranges[i].on_off_none == 3) //none
		{
			if (ranges[0].low)
			{
				if (ranges[i].low > ranges[0].low)
					ranges[0].low = ranges[i].low;
				if (ranges[i].high < ranges[0].high)
					ranges[0].high = ranges[i].high;
			}
			else
			{
				ranges[0].high = ranges[i].high;
				ranges[0].low = ranges[i].low;
			}
		}
		else if (ranges[i].on_off_none == 1) //on
		{
			//ranges[setPointsNum + 1].low += ranges[i].low;
			//ranges[setPointsNum + 1].high += ranges[i].high;
			ranges[0].low -= ranges[i].high;
			if (ranges[0].low < 0)
				ranges[0].low = 0;
			ranges[0].high -= ranges[i].low;
			if (ranges[0].high < 0)
				ranges[0].high = 0;
		}
		else //off
		{
			ranges[0].low += ranges[i].low;
			ranges[0].high += ranges[i].high;
		}
	}
	ranges[0].on_off_none = 3;
	return ranges;
}
void traffic(const char* fpIn, const char* fpOut)
{
	int setPoints;
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	range* ranges = read(fp, &setPoints);
	fclose(fp);
	ranges = findLast(ranges, setPoints);
	ranges = findFirst(ranges, setPoints);
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d %d\n%d %d", ranges[0].low, ranges[0].high, ranges[setPoints + 1].low, ranges[setPoints + 1].high);
	fclose(fp);
}
int main(void)
{
	//herding("./Debug/herding.in", "./Debug/herding.out");
	//herding("herding.in", "herding.out");
	//cyclingFood("./Debug/revegetate.in", "./Debug/revegetate.out");
	//cyclingFood("revegetate.in", "revegetate.out");
	//traffic("./Debug/traffic.in", "./Debug/traffic.out"); //mistake: didn't think throgugh the cases well enough(got only the first one right)
	traffic("traffic.in", "traffic.out");
	system("pause");
	return 0;
}