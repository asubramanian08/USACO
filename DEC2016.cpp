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
//#include <assert.h>
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

int compareFunc(const void* p1, const void* p2)
{
	return *((unsigned int* )p1) - *((unsigned int*) p2);
}
bool onPoint;
unsigned int bSearch(unsigned int point, unsigned int* haybales, unsigned int numOfHaybales, bool isA)
{
	unsigned int low = 0, high = numOfHaybales - 1;
	while (high - low > 1) {
		if (haybales[(high + low) / 2] > point)
			high = (high + low) / 2;
		else if (haybales[(high + low) / 2] < point)
			low = (high + low) / 2;
		else
			return (high + low) / 2;
	}
	if (isA) {
		if (point <= haybales[low])
			return low;
		return high;
	}
	if (point >= haybales[high])
		return high;
	return low;
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfHaybale = getNum;
	unsigned int numOfQs = getNum;
	unsigned int* haybales = (unsigned int*)malloc(sizeof(unsigned int) * numOfHaybale);
	for (unsigned int i = 0; i < numOfHaybale; i++)
		haybales[i] = getNum;
	FILE* fpout = fopen(fout, "w");
	qsort(haybales, numOfHaybale, sizeof(unsigned int), compareFunc);
	unsigned int pointA, pointB, spotA, spotB;
	for (unsigned int i = 0; i < numOfQs; i++){
		pointA = getNum;
		pointB = getNum;
		spotA = bSearch(pointA, haybales, numOfHaybale, true);
		spotB = bSearch(pointB, haybales, numOfHaybale, false);
		/*bool add = (((pointA <= haybales[spotA]) && (haybales[spotA] <= pointB)) && ((pointA <= haybales[spotB]) && (haybales[spotB] <= pointB)));
		fprintf(fpout, "%d\n", spotB - spotA + add);*/
		if((spotA == spotB) && (!((pointA <= haybales[spotA]) && (haybales[spotA] <= pointB))))
			fprintf(fpout, "0\n");
		else
			fprintf(fpout, "%d\n", spotB - spotA + 1);
	}
	fclose(fpout);
	fclose(fp);
}

struct place
{
	char l1, l2;
	unsigned int cityNum;
	bool isState;
	bool on;
};
int compareFuncCities(const void* p1, const void* p2)
{
	int returnVal;
	place** a = (place * *)p1;
	place** b = (place * *)p2;
	if (returnVal = (*a)->l1 - (*b)->l1)
		return returnVal;
	if (returnVal = (*a)->l2 - (*b)->l2)
		return returnVal;
	returnVal = (*b)->isState - (*a)->isState;
	return returnVal;
}
struct stack
{
	unsigned int statePoint;
	stack* next;
};
void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCitys = getNum;
	place* cities = (place*)malloc(sizeof(place) * numOfCitys);
	place* states = (place*)malloc(sizeof(place) * numOfCitys);
	place** bigsort = (place * *)malloc(sizeof(place*) * numOfCitys * 2);
	for (unsigned int i = 0; i < numOfCitys; i++) {
		cities[i].cityNum = i;
		cities[i].isState = false;
		cities[i].on = true;
		cities[i].l1 = fgetc(fp);
		cities[i].l2 = fgetc(fp);
		while (fgetc(fp) != ' ');
		states[i].cityNum = i;
		states[i].isState = true;
		states[i].on = true;
		states[i].l1 = fgetc(fp);
		states[i].l2 = fgetc(fp);
		fgetc(fp); //newline
		bigsort[i * 2] = &cities[i];
		bigsort[i * 2 + 1] = &states[i];
		if ((states[i].l1 == cities[i].l1) && (states[i].l2 == cities[i].l2)) {
			states[i].on = false;
			cities[i].on = false;
		}
	}
	fclose(fp);
	qsort(bigsort, numOfCitys * 2, sizeof(place*), compareFuncCities);
	unsigned int bigSum = numOfCitys * 2;
	stack* start = NULL;
	stack* temp;
	unsigned int ans = 0;
	bool wasCity = false;
	for (unsigned int i = 0; i < bigSum; i++) {
		if (!bigsort[i]->on)
			continue;
		if (bigsort[i]->isState) {
			if (wasCity) {
				while (start) {
					temp = start;
					start = start->next;
					free(temp);
				}
			}
			temp = (stack*)malloc(sizeof(stack));
			temp->next = start;
			temp->statePoint = bigsort[i]->cityNum;
			start = temp;
			wasCity = false;
		}
		else if (start != NULL) {
			if ((bigsort[i]->l1 == states[start->statePoint].l1) && (bigsort[i]->l2 == states[start->statePoint].l2)) {
				temp = start;
				while (temp) {
					if ((states[bigsort[i]->cityNum].l1 == cities[temp->statePoint].l1) && (states[bigsort[i]->cityNum].l2 == cities[temp->statePoint].l2))
						ans++;
					temp = temp->next;
				}
			}
			else {
				while (start) {
					temp = start;
					start = start->next;
					free(temp);
				}
			}
			wasCity = true;
		}
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans / 2);
	fclose(fp);
}

struct cow
{
	unsigned int x;
	unsigned int y;
	unsigned int power;
};
bool* goneTo;
bool* goTo;
unsigned int numOfCows;
void recursion(unsigned int cowNum)
{
	goneTo[cowNum] = true;
	for (unsigned int i = 0; i < numOfCows; i++)
		if ((!goneTo[i]) && goTo[cowNum * numOfCows + i])
			recursion(i);
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	numOfCows = getNum;
	cow* cows = (cow*)malloc(sizeof(cow) * numOfCows);
	goTo = (bool*)malloc(sizeof(bool) * numOfCows * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].x = getNum;
		cows[i].y = getNum;
		cows[i].power = getNum;
	}
	fclose(fp);
	for (unsigned int i = 0; i < numOfCows; i++)
		for (unsigned int j = 0; j < numOfCows; j++)
			goTo[i * numOfCows + j] = (cows[i].power * cows[i].power >= ((cows[i].x - cows[j].x) * (cows[i].x - cows[j].x)) + ((cows[i].y - cows[j].y) * (cows[i].y - cows[j].y)));
	goneTo = (bool*)malloc(sizeof(bool) * numOfCows);
	unsigned int max = 0, curr;
	for (unsigned int i = 0; i < numOfCows; i++) {
		memset(goneTo, 0, sizeof(bool) * numOfCows);
		curr = 0;
		recursion(i);
		for (unsigned int i = 0; i < numOfCows; i++)
			curr += goneTo[i];
		if (curr > max)
			max = curr;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", max);
	fclose(fp);
}

int main(void)
{
	q1("haybales.in", "haybales.out");
	//q2("citystate.in", "citystate.out");
	//q3("moocast.in", "moocast.out");
	
	//system("pause");
	return 0;
}