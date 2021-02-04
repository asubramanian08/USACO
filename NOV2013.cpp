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
//#include <errno.h> 
//#include <signal.h> 
//#include <setjmp.h>
//_CRT_SECURE_NO_WARNINGS;
#define getNum getNumInFile(&fp)
char* readStrInFile(FILE** fp, int size, int* endSize)
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
	*endSize = i + 1;
	str = (char*)realloc(str, sizeof(char) * (i + 1));
	return str;
}
long long getNumInFile(FILE * *fp)
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

//my first atempt
/*void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	int numOfDials = getNum;
	int FJ[3] = { getNum, getNum, getNum };
	int masterLoc[3] = { getNum, getNum, getNum };
	fclose(fp);
	unsigned int commen = 1;
	unsigned int curr = 0;
	int temp;
	for (unsigned int i = 0; i < 3; i++) {
		curr = 0;
		for (int j = -2; j < 3; j++) {
			temp = FJ[i] + j;
			if (temp <= 0) {
				temp = numOfDials + temp;
			if (temp > numOfDials) {
				temp = numOfDials + temp;
			if ((abs(masterLoc[i] - temp) <= 2) || (abs((masterLoc[i] + numOfDials) - temp) <= 2) || (abs((masterLoc[i] - numOfDials) - temp) <= 2))
				curr++;
			}
		}
		commen *= curr;
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", 250 - commen);
	fclose(fp);
}*/
//brute force works
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	int numOfDials = getNum;
	int FJ[3] = { getNum, getNum, getNum };
	int masterLoc[3] = { getNum, getNum, getNum };
	fclose(fp);
	unsigned long ans = 0;
	for (int i = 1; i <= numOfDials; i++)
		for (int j = 1; j <= numOfDials; j++)
			for (int k = 1; k <= numOfDials; k++)
				if ((((abs(i - FJ[0]) <= 2) || (abs(i - FJ[0]) >= numOfDials - 2)) &&
					((abs(j - FJ[1]) <= 2) || (abs(j - FJ[1]) >= numOfDials - 2)) &&
					((abs(k - FJ[2]) <= 2) || (abs(k - FJ[2]) >= numOfDials - 2))) ||
					(((abs(i - masterLoc[0]) <= 2) || (abs(i - masterLoc[0]) >= numOfDials - 2)) &&
					((abs(j - masterLoc[1]) <= 2) || (abs(j - masterLoc[1]) >= numOfDials - 2)) &&
						((abs(k - masterLoc[2]) <= 2) || (abs(k - masterLoc[2]) >= numOfDials - 2))))
					ans++;
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

struct time
{
	bool start;
	long time;
};
int compareFunc(const void* p1, const void* p2)
{
	return ((time*)p1)->time - ((time*)p2)->time;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	int cold = getNum;
	int toPerfect = getNum - cold;
	int toHot = getNum - (toPerfect + cold);
	time* cowTimes = (time*)malloc(sizeof(time) * numOfCows * 2);
	for (long i = 0; i < numOfCows; i++) {
		cowTimes[i * 2].start = true;
		cowTimes[i * 2].time = getNum;
		cowTimes[i * 2 + 1].start = false;
		cowTimes[i * 2 + 1].time = getNum + 1;
	}
	fclose(fp);
	qsort(cowTimes, numOfCows * 2, sizeof(time), compareFunc);
	long currTime = cowTimes[0].time;
	long currMilk = numOfCows * cold;
	long mostMilk = currMilk;
	unsigned int numOfItems = numOfCows * 2;
	for (unsigned int i = 0; i < numOfItems; i++) {
		if (cowTimes[i].time != currTime) {
			currTime = cowTimes[i].time;
			if (currMilk > mostMilk)
				mostMilk = currMilk;
		}
		if (cowTimes[i].start)
			currMilk += toPerfect;
		else
			currMilk += toHot;
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", mostMilk);
	fclose(fp);
}

void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int cowsNotWith = getNum;
	unsigned int cowK = getNum;
	fpos_t startPos;
	fgetpos(fp, &startPos);
	fseek(fp, 0, SEEK_END);
	long fileSize = ftell(fp);
	fsetpos(fp, &startPos);
	char* file = (char*)malloc(fileSize * sizeof(char));
	fread(file, sizeof(char), fileSize, fp);
	fclose(fp);
	fp = NULL;
	fp = fopen(fpOut, "w");

	fclose(fp);
}

int main(void)
{
	//q1("combo.in", "combo.out");
	//q2("milktemp.in", "milktemp.out");
	q3("nocow.in", "nocow.out");
	//system("pause");
	return 0;
}