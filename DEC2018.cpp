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
/*void q1(const char* filein, const char* fileout)
{
	FILE* fp = NULL;
	//fopen_s(&fp, filein, "r");
	fp = fopen(filein, "r");
	unsigned long long C1 = getNumInFile(&fp);
	unsigned long long V1 = getNumInFile(&fp);
	unsigned long long C2 = getNumInFile(&fp);
	unsigned long long V2 = getNumInFile(&fp);
	unsigned long long C3 = getNumInFile(&fp);
	unsigned long long V3 = getNumInFile(&fp);
	fclose(fp);
	if (C2 - V2 >= V1)
	{
		V2 = V2 + V1;
		V1 = 0;
	}
	else
	{
		V1 = V1 - (C2 - V2);
		V2 = C2;
	}
	if (C3 - V3 >= V2)
	{
		V3 = V3 + V2;
		V2 = 0;
	}
	else
	{
		V2 = V2 - (C3 - V3);
		V3 = C3;
	}
	if (C1 - V1 >= V3)
	{
		V1 = V1 + V3;
		V3 = 0;
	}
	else
	{
		V3 = V3 - (C1 - V1);
		V1 = C1;
	}
	if (C2 - V2 >= V1)
	{
		V2 = V2 + V1;
		V1 = 0;
	}
	else
	{
		V1 = V1 - (C2 - V2);
		V2 = C2;
	}
	fp = NULL;
	//fopen_s(&fp, fileout, "w");
	fp = fopen(fileout, "w");
	fprintf(fp, "%llu\n%llu\n%llu", V1, V2, V3);
	fclose(fp);
}*/
/*struct byTime
{
	int time;
	int CowNum;
	bool start_stop;
};
int compareFunc(const void* p1, const void* p2)
{
	byTime* a = (byTime*)p1;
	byTime* b = (byTime*)p2;
	return a->time - b->time;
}
byTime* readCowInfo(FILE* fp, int** bucketsNeeded, int* numOfCows)
{
	*numOfCows = getNumInFile(&fp);
	byTime* mainInfo = (byTime*)malloc(sizeof(byTime) * (*numOfCows) * 2);
	memset(mainInfo, 0, sizeof(byTime) * (*numOfCows) * 2);
	*bucketsNeeded = (int*)malloc(sizeof(int) * (*numOfCows));
	memset(mainInfo, 0, sizeof(int) * (*numOfCows));
	for (int i = 0; i < *numOfCows; i++)
	{
		mainInfo[i * 2].CowNum = i;
		mainInfo[i * 2].start_stop = 1;
		mainInfo[i * 2].time = getNumInFile(&fp);

		mainInfo[i * 2 + 1].CowNum = i;
		mainInfo[i * 2 + 1].start_stop = 0;
		mainInfo[i * 2 + 1].time = getNumInFile(&fp);

 		*(*bucketsNeeded + i) = getNumInFile(&fp);
	}
	qsort(mainInfo, (*numOfCows) * 2 , sizeof(byTime), compareFunc);
	return mainInfo;
}
void q2(const char* filein, const char* fileout)
{
	int* bucketsNeeded;
	int numOfCows;
	FILE* fp = NULL;
	//fopen_s(&fp, filein, "r");
	fp = fopen(filein, "r");
	byTime* mainInfo = readCowInfo(fp, &bucketsNeeded, &numOfCows);
	fclose(fp);
	int numOfTimes = numOfCows * 2;
	int currentBuckets = 0, MAX_buckets = 0;
	for (int i = 0; i < numOfTimes; i++)
	{
		if (mainInfo[i].start_stop)
		{
			currentBuckets += bucketsNeeded[mainInfo[i].CowNum];
			if (currentBuckets > MAX_buckets)
				MAX_buckets = currentBuckets;
		}
		else
			currentBuckets -= bucketsNeeded[mainInfo[i].CowNum];
	}
	fp = NULL;
	//fopen_s(&fp, fileout, "w");
	fp = fopen(fileout, "w");
	fprintf(fp, "%d", MAX_buckets);
	fclose(fp);
}*/
/*#define bucketNum 10
#define HighBucketNum 11
void read(int** b1Buckets, int** b2Buckets, bool** totalValues, FILE* fp)
{
	*b1Buckets = (int*)malloc(sizeof(int) * bucketNum);
	memset(*b1Buckets, 0, sizeof(int) * bucketNum);
	*b2Buckets = (int*)malloc(sizeof(int) * HighBucketNum);
	memset(*b2Buckets, 0, sizeof(int) * HighBucketNum);
	*totalValues = (bool*)malloc(sizeof(bool) * 2001);
	memset(*totalValues, 0, sizeof(bool) * 2001);
	for (int i = 0; i < bucketNum; i++)
		* (*b1Buckets + i) = getNumInFile(&fp);
	for (int i = 0; i < bucketNum; i++)
		* (*b2Buckets + i) = getNumInFile(&fp);
}
void blaBla(bool** endings, int* b1, int* b2, int numOfTimes, bool goTo, int curB1, int curB2, int replaceLocation)
{
	int* newB1 = (int*)malloc(sizeof(int) * bucketNum);
	int* newB2 = (int*)malloc(sizeof(int) * HighBucketNum);
	if (numOfTimes == 4)
		*(*endings + curB1) = 1;
	else if (goTo) //one to 2
	{
		for (int i = 0; i < bucketNum; i++)
		{
			b2[replaceLocation] = b1[i];
			memcpy(newB1, b1, sizeof(int) * bucketNum);
			memcpy(newB2, b2, sizeof(int) * HighBucketNum);
			blaBla(endings, newB1, newB2, numOfTimes + 1, !goTo, curB1 - b1[i], curB2 + b1[i], i);
		}
	}
	else //from 2 to 1
	{
		for (int i = 0; i < HighBucketNum; i++)
		{
			b1[replaceLocation] = b2[i];
			memcpy(newB1, b1, sizeof(int) * bucketNum);
			memcpy(newB2, b2, sizeof(int) * HighBucketNum);
			blaBla(endings, newB1, newB2, numOfTimes + 1, !goTo, curB1 + b2[i], curB2 - b2[i], i);
		}

	}
	free(newB1);
	free(newB2);
}
void q3(const char* filein, const char* fileout)
{
	int* b1Buckets;
	int* b2Buckets;
	bool* endings;
	FILE* fp = NULL;
	//fopen_s(&fp, filein, "r");
	fp = fopen(filein, "r");
	read(&b1Buckets, &b2Buckets, &endings, fp);
	fclose(fp);
	blaBla(&endings, b1Buckets, b2Buckets, 0, 1, 1000, 1000, bucketNum);
	int times = 0;
	for (int i = 0; i < 2001; i++)
	{
		if (endings[i])
			times++;
	}
	fp = NULL;
	//fopen_s(&fp, fileout, "w");
	fp = fopen(fileout, "w");
	fprintf(fp, "%d", times);
	fclose(fp);
}*/
int main(void)
{
	//q1("./mixmilk.in", "./mixmilk.out");
	//q1("mixmilk.in", "mixmilk.out");
	//q2("./blist.in", "./blist.out");
	//q3("./backforth.in", "./backforth.out"); //problems: when doing recursve think about copying problems
	//system("pause");
	return 0;
}