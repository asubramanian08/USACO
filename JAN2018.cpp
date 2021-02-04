#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <iostream>
//#include <stdarg.h>
#include <assert.h>
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

struct lifeGaurd
{
	unsigned int cowNum;
	unsigned int time;
	bool is_start;
};
struct gaurdStack
{
	unsigned int gaurd;
	gaurdStack* next;
};
int compareGaurd(const void* p1, const void* p2)
{
	return ((lifeGaurd*)p1)->time - ((lifeGaurd*)p2)->time;
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum;
	lifeGaurd* cows = (lifeGaurd*)malloc(sizeof(lifeGaurd) * numOfCows * 2);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i * 2].cowNum = i;
		cows[i * 2].is_start = true;
		cows[i * 2].time = getNum;

		cows[i * 2 + 1].cowNum = i;
		cows[i * 2 + 1].is_start = false;
		cows[i * 2 + 1].time = getNum;
	}
	fclose(fp);
	qsort(cows, numOfCows * 2, sizeof(lifeGaurd), compareGaurd);
	unsigned int numOfTimes = numOfCows * 2;

	unsigned int totalTime = 0;
	unsigned int cowsActive = 1;
	unsigned int* timeTaken = (unsigned int*)calloc(numOfCows, sizeof(unsigned int));
	bool* is_active = (bool*)calloc(numOfCows, sizeof(bool));
	is_active[cows[0].cowNum] = true;
	gaurdStack* start = (gaurdStack*)malloc(sizeof(gaurdStack));
	start->gaurd = cows[0].cowNum;
	start->next = NULL;
	gaurdStack* temp;
	//enque the first one
	for (unsigned int i = 1; i < numOfTimes; i++) {
		if (cowsActive == 1) {
			while (is_active[start->gaurd] == false) {
				temp = start;
				start = start->next;
				free(temp);
			}
			timeTaken[start->gaurd] += cows[i].time - cows[i - 1].time;
		}
		if (cowsActive != 0)
			totalTime += cows[i].time - cows[i - 1].time;
		if (cows[i].is_start) {
			temp = (gaurdStack*)malloc(sizeof(gaurdStack));
			temp->gaurd = cows[i].cowNum;
			temp->next = start;
			start = temp;
			cowsActive++;
			is_active[cows[i].cowNum] = true;
		}
		else {
			cowsActive--;
			is_active[cows[i].cowNum] = false;
		}
	}

	unsigned int smallestTime = -1;
	for (unsigned int i = 0; i < numOfCows; i++)
		if (timeTaken[i] < smallestTime)
			smallestTime = timeTaken[i];
	fp = fopen(fout, "w");
	fprintf(fp, "%d", totalTime - smallestTime);
	fclose(fp);
}

struct cow
{
	unsigned long long gallons;
	unsigned long long money;
};
struct shop
{
	unsigned long long maxGall;
	unsigned long long money;
};
int compareCows(const void* p1, const void* p2)
{
	return ((cow*)p1)->gallons - ((cow*)p2)->gallons;
}
int compareShops(const void* p1, const void* p2)
{
	return ((shop*)p2)->money - ((shop*)p1)->money;
}
int compareRents(const void* p1, const void* p2)
{
	return *((unsigned long long*)p2) - *((unsigned long long*)p1);
}
void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum, numOfShops = getNum, numOfRents = getNum;
	cow* cows = (cow*)malloc(sizeof(cow) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].money = 0;
		cows[i].gallons = getNum;
	}
	shop* shops = (shop*)malloc(sizeof(shop) * numOfShops);
	for (unsigned int i = 0; i < numOfShops; i++) {
		shops[i].maxGall = getNum;
		shops[i].money = getNum;
	}
	unsigned long long* rents = (unsigned long long*)malloc(sizeof(unsigned long long) * numOfRents);
	for (unsigned int i = 0; i < numOfRents; i++)
		rents[i] = getNum;
	fclose(fp);
	qsort(cows, numOfCows, sizeof(cow), compareCows);
	qsort(shops, numOfShops, sizeof(shop), compareShops);
	qsort(rents, numOfRents, sizeof(unsigned long long), compareRents);
	unsigned long long maxTotal = 0;
	//assing price to cowgallon
	int currCow = numOfCows - 1;
	unsigned int currShop = 0;
	unsigned int minGall;
	while ((currCow >= 0) && (currShop < numOfShops)) {
		minGall = _min(cows[currCow].gallons, shops[currShop].maxGall);
		cows[currCow].money += shops[currShop].money * minGall;
		cows[currCow].gallons -= minGall;
		shops[currShop].maxGall -= minGall;
		if (cows[currCow].gallons == 0) {
			maxTotal += cows[currCow].money;
			currCow--;
		}
		if (shops[currShop].maxGall == 0)
			currShop++;
	}
	if (currCow != -1)
		maxTotal += cows[currCow].money;
	//repace milking with rental
	unsigned long long currTotal = maxTotal;
	for (unsigned int currRent = 0; (currRent < numOfRents) && (currRent < numOfCows); currRent++) {
		currTotal += rents[currRent] - cows[currRent].money;
		if (currTotal > maxTotal)
			maxTotal = currTotal;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%llu", maxTotal);
	fclose(fp);
}

struct stack
{
	unsigned int canGoTo;
	unsigned long rel;
	stack* next;
};
bool* beenTo;
stack** vids;
unsigned int recursive(unsigned int minRel, unsigned int currPoint)
{
	unsigned int total = 0;
	if (beenTo[currPoint])
		return total;
	beenTo[currPoint] = true;
	total++;
	stack* curr = vids[currPoint];
	while (curr) {
		if (curr->rel >= minRel)
			total += recursive(minRel, curr->canGoTo);
		curr = curr->next;
	}
	return total;
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfVids = getNum;
	unsigned int numOfQs = getNum;
	vids = (stack**)calloc(numOfVids, sizeof(stack*));
	unsigned int num1, num2;
	unsigned long rel;
	stack* temp;
	for (unsigned int i = 1; i < numOfVids; i++) {
		num1 = getNum - 1;
		num2 = getNum - 1;
		rel = getNum;

		temp = (stack*)malloc(sizeof(stack));
		temp->next = vids[num1];
		temp->rel = rel;
		temp->canGoTo = num2;
		vids[num1] = temp;

		temp = (stack*)malloc(sizeof(stack));
		temp->next = vids[num2];
		temp->rel = rel;
		temp->canGoTo = num1;
		vids[num2] = temp;
	}

	beenTo = (bool*)malloc(sizeof(bool) * numOfVids);
	FILE* fpOut = fopen(fout, "w");
	unsigned int num;
	for (unsigned int i = 0; i < numOfQs; i++) {
		memset(beenTo, 0, sizeof(bool) * numOfVids);
		rel = getNum;
		num = getNum - 1;
		fprintf(fpOut, "%d\n", recursive(rel, num) - 1);
	}
	fclose(fpOut);
	fclose(fp);
}

int main(void)
{
	q1("lifeguards.in", "lifeguards.out");
	//q2("rental.in", "rental.out");
	//q3("mootube.in", "mootube.out");

	return 0;
}