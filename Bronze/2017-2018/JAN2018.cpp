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


//this is my origianl one
/*struct point
{
	int x;
	int y;
};
struct rect
{
	point bottemLeft;
	point topRight;
};
void q1(const char* fpIn, const char* fpOut)
{
	rect lawnMower;
	rect cowFeed;
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	lawnMower.bottemLeft.x = readNon_n_NegativesFromFile(&fp);
	lawnMower.bottemLeft.y = readNon_n_NegativesFromFile(&fp);
	lawnMower.topRight.x = readNon_n_NegativesFromFile(&fp);
	lawnMower.topRight.y = readNon_n_NegativesFromFile(&fp);
	cowFeed.bottemLeft.x = readNon_n_NegativesFromFile(&fp);
	cowFeed.bottemLeft.y = readNon_n_NegativesFromFile(&fp);
	cowFeed.topRight.x = readNon_n_NegativesFromFile(&fp);
	cowFeed.topRight.y = readNon_n_NegativesFromFile(&fp);
	fclose(fp);

	int length_y = lawnMower.topRight.y - lawnMower.bottemLeft.y;
	int with_x = lawnMower.topRight.x - lawnMower.bottemLeft.x;
	if ((cowFeed.bottemLeft.x <= lawnMower.bottemLeft.x) && (cowFeed.topRight.x >= lawnMower.topRight.x)) //if cowFeed encompasses left and right
	{
		if ((cowFeed.topRight.y >= lawnMower.bottemLeft.y) && (cowFeed.bottemLeft.y <= lawnMower.topRight.y))
		{
			if (cowFeed.topRight.y >= lawnMower.topRight.y)
				length_y -= lawnMower.topRight.y - cowFeed.bottemLeft.y;
			else if (cowFeed.bottemLeft.y <= lawnMower.bottemLeft.y)
				length_y -= cowFeed.topRight.y - lawnMower.bottemLeft.y;
		}
	}
	else if ((cowFeed.bottemLeft.y <= lawnMower.bottemLeft.y) && (cowFeed.topRight.y >= lawnMower.topRight.y))
	{
		if ((cowFeed.topRight.x >= lawnMower.bottemLeft.x) && (cowFeed.bottemLeft.x <= lawnMower.topRight.x))
		{
			if (cowFeed.topRight.x >= lawnMower.topRight.x)
				with_x -= lawnMower.topRight.x - cowFeed.bottemLeft.x;
			else if (cowFeed.bottemLeft.x <= lawnMower.bottemLeft.x)
				with_x -= cowFeed.topRight.x - lawnMower.bottemLeft.x;
		}
	}
	if (with_x < 0)
		with_x = 0;
	if (length_y < 0)
		length_y = 0;
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", with_x * length_y);
	fclose(fp);
}*/

/*
this is my original one changed
struct time
{
	int time;
	int cowNum;
	bool start_stop;
};
int compareFunc(const void* p1, const void* p2)
{
	time* a = (time*)p1;
	time* b = (time*)p2;
	return a->time - b->time;
}
time* read(FILE* fp, int* numOfCows)
{
	*numOfCows = getNumInFile(&fp);
	time* info = (time*)malloc(sizeof(time) * (*numOfCows) * 2);
	for (int i = 0; i < *numOfCows; i++)
	{
		info[i * 2].cowNum = i;
		info[i * 2].time = getNumInFile(&fp);
		info[i * 2].start_stop = 1;

		info[i * 2 + 1].cowNum = i;
		info[i * 2 + 1].time = getNumInFile(&fp);
		info[i * 2 + 1].start_stop = 0;
	}
	qsort(info, (*numOfCows) * 2, sizeof(time), compareFunc);
	return info;
}
void q2(const char* fpIn, const char* fpOut)
{
	int numOfCows;
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	//fp = fopen(fpIn, "r");
	time* info = read(fp, &numOfCows);
	fclose(fp);
	int* numOfSingles = (int*)malloc(sizeof(int) * numOfCows);
	memset(numOfSingles, 0, sizeof(int) * numOfCows);
	int totalTime = 0;
	int numOfCowsRunning = 0;
	int* cowsRunning = (int*)malloc(sizeof(int) * numOfCows);
	int j;
	for (int i = 0; i < numOfCows * 2; i++)
	{
		if (info[i].start_stop) //another thing began
		{
			cowsRunning[info[i].cowNum] = 1;
			numOfCowsRunning++;
			if (numOfCowsRunning == 1)
				numOfSingles[info[i].cowNum] += info[i + 1].time - info[i].time - info[i + 1].start_stop;
			totalTime += info[i + 1].time - info[i].time;
		}
		else
		{
			cowsRunning[info[i].cowNum] = 0;
			numOfCowsRunning--;
			if (numOfCowsRunning > 0)
			{
				totalTime += info[i + 1].time - info[i].time;
				if (numOfCowsRunning == 1)
				{
					for (j = 0; 
						cowsRunning[j] != 0;
						j++);
					numOfSingles[info[j].cowNum] += info[j + 1].time - info[j].time - info[j + 1].start_stop;
				}
			}
		}
	}
	int smallest = 1001;
	for (int i = 0; i < numOfCows; i++)
	{
		if (numOfSingles[i] < smallest)
			smallest = numOfSingles[i];
		printf("%d ", i);
	}
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	//fp = fopen(fpOut, "w");
	fprintf(fp, "%d", totalTime - smallest);
	fclose(fp);
}*/

//this is my original one
/*void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	int numOfCows = getNumInFile(&fp);
	int* hights = (int*)malloc(sizeof(int) * numOfCows);
	int bessie = -1;
	int i;
	hights[0] = getNumInFile(&fp);
	for (i = 1; i < numOfCows; i++)
	{
		hights[i] = getNumInFile(&fp);
		if ((bessie == -1) && (hights[i] < hights[i - 1]))
			bessie = i;
	}
	fclose(fp);

	int old = -1;
	int count = 0;
	if ((bessie != -1) && (bessie != numOfCows - 1) && (hights[bessie + 1] < hights[bessie -1]))
	{
		bessie--;
		for (int i = bessie + 1; hights[i] < hights[bessie]; i++)
		{
			if (hights[i] != old)
			{
				old = hights[i];
				count++;
			}
		}
	}
	else
	{
		for (i = 0; i < bessie; i++)
		{
			if (hights[i] > hights[bessie] && hights[i] != old)
			{
				old = hights[i];
				count++;
			}
		}
	}
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", count);
	fclose(fp);
}*/

//this is a repeat of number 2
/*int* loop(int* times, int start, int end, int cowNum)
{
	for (int i = start + 1; i <= end; i++)
	{
		if (!times[i])
			times[i] = cowNum;
		else
			times[i] = -1;
	}
	return times;
}
void q2(const char* fpIn, const char* fpOut)
{
	int* doneBy = (int*)malloc(sizeof(int) * 1001);
	memset(doneBy, 0, sizeof(int) * 1001);
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	int numOfGaurds = getNumInFile(&fp);
	int start;
	int end;
	for (int i = 1; i <= numOfGaurds; i++)
	{
		start = getNumInFile(&fp);
		end = getNumInFile(&fp);
		doneBy = loop(doneBy, start, end, i);
	}
	fclose(fp);

	int total = 0;
	int* values = (int*)malloc(sizeof(int) * numOfGaurds);
	memset(values, 0, sizeof(int) * numOfGaurds);
	for (int i = 0; i < 1000; i++)
	{
		if (doneBy[i] != 0)
		{
			total++;
			if (doneBy[i] != -1)
				values[doneBy[i] - 1]++;
		}
	}

	int smallest = 1001;
	for (int i = 0; i < numOfGaurds; i++)
	{
		if (values[i] < smallest)
			smallest = values[i];
	}
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", total - smallest);
	fclose(fp);
}*/
int main(void)
{
	//q1("./billboard.in", "./billboard.out");
	//q2("./lifeguards.in", "./lifeguards.out");
	//q3("./outofplace.in", "./outofplace.out");
	//system("pause");
	return 0;
}