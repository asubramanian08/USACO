#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
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

void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int pointA = getNum, pointB = getNum, flights = getNum;
	unsigned int cost, citys, currCity, leastCost = 1010;
	bool notFound;
	for (unsigned int currFlight = 0; currFlight < flights; currFlight++) {
		cost = getNum;
		citys = getNum;
		notFound = true;
		for (currCity = 0; (currCity < citys) && (getNum != pointA); currCity++);
		currCity++;
		while (currCity < citys) {
			if (getNum == pointB)
				notFound = false;
			currCity++; 
		}
		while (currCity < citys) {
			getNum;
			currCity++;
		}
		if (!notFound && (cost < leastCost))
			leastCost = cost;
	}
	fclose(fp);
	fp = fopen(fpOut, "w");
	if (leastCost == 1010)
		fprintf(fp, "-1");
	else
		fprintf(fp, "%u", leastCost);
	fclose(fp);
}

struct flight
{
	bool isUsed, hasA, hasB;
	unsigned int cost, numOfCitys;
	unsigned int* cityStops;
};
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int pointA = getNum, pointB = getNum, numOfFlights = getNum;
	unsigned int currCity, leastCost = ~((unsigned int)0);
	unsigned int* fromPointA = (unsigned int*)calloc(10000, sizeof(unsigned int));
	flight* bolivia = (flight*)malloc(sizeof(flight) * numOfFlights);
	for (unsigned int currFlight = 0; currFlight < numOfFlights; currFlight++) {
		bolivia[currFlight].cost = getNum;
		bolivia[currFlight].numOfCitys = getNum;
		bolivia[currFlight].isUsed = false;
		bolivia[currFlight].hasA = 0;
		bolivia[currFlight].hasB = 0;
		bolivia[currFlight].cityStops = (unsigned int*)malloc(sizeof(unsigned int) * bolivia[currFlight].numOfCitys);
		for (currCity = 0; currCity < bolivia[currFlight].numOfCitys; currCity++) {
			if ((bolivia[currFlight].cityStops[currCity] = getNum) == pointA) {
				bolivia[currFlight].hasA = true;
				break;
			}
			else if (bolivia[currFlight].cityStops[currCity] == pointB) {
				bolivia[currFlight].hasB = true;
				break;
			}
		}
		currCity++;
		while (currCity < bolivia[currFlight].numOfCitys) {
			if ((bolivia[currFlight].cityStops[currCity] = getNum) == pointB)
				bolivia[currFlight].isUsed = true;
			else if (bolivia[currFlight].cityStops[currCity] == pointA)
				bolivia[currFlight].hasA = true;
			if (bolivia[currFlight].hasA) {
				if ((fromPointA[bolivia[currFlight].cityStops[currCity] - 1] == 0) || (bolivia[currFlight].cost < fromPointA[bolivia[currFlight].cityStops[currCity] - 1]))
					fromPointA[bolivia[currFlight].cityStops[currCity] - 1] = bolivia[currFlight].cost;
			}
			currCity++;
		}
		if (bolivia[currFlight].isUsed && (bolivia[currFlight].cost < leastCost))
			leastCost = bolivia[currFlight].cost;
	}
	fclose(fp);
	unsigned int currCost;
	for (unsigned int i = 0; i < numOfFlights; i++) {
		if (bolivia[i].hasB && !bolivia[i].isUsed) {
			currCost = ~((unsigned int)0);
			for (unsigned int j = 0; (j < bolivia[i].numOfCitys) && (bolivia[i].cityStops[j] != pointB); j++) {
				if ((fromPointA[bolivia[i].cityStops[j] - 1] != 0) && (fromPointA[bolivia[i].cityStops[j] - 1] < currCost))
					currCost = fromPointA[bolivia[i].cityStops[j] - 1];
			}
			if((currCost != ~((unsigned int)0)) && (currCost + bolivia[i].cost < leastCost))
				leastCost = currCost + bolivia[i].cost;
		}
	}
	fp = fopen(fpOut, "w");
	if (leastCost == ~((unsigned int)0))
		fprintf(fp, "-1");
	else
		fprintf(fp, "%u", leastCost);
	fclose(fp);
}

//dad told me
#define numVal(numPtr, base) (((numPtr[0] * base) + numPtr[1]) * base + numPtr[2])
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	FILE* fout = fopen(fpOut, "w");
	unsigned int numOfCases = getNum;
	unsigned short* nums = (unsigned short*)malloc(sizeof(unsigned short) * 6);
	for (unsigned int i = 0; i < numOfCases; i++) {
		nums[0] = fgetc(fp) - '0';
		nums[1] = fgetc(fp) - '0';
		nums[2] = fgetc(fp) - '0';
		fgetc(fp); //space
		nums[3] = fgetc(fp) - '0';
		nums[4] = fgetc(fp) - '0';
		nums[5] = fgetc(fp) - '0';
		fgetc(fp); //newline
		unsigned short* num1 = nums;
		unsigned short* num2 = &nums[3];
		bool flip = false;
		if (numVal(num1, 10) > numVal(num2, 10)) {
			unsigned short* temp = num1;
			num1 = num2;
			num2 = temp;
			flip = true;
		}
		unsigned int base2 = 9, base1;
		do {
			base2++;
			for (base1 = base2 + 1; numVal(num1, base1) < numVal(num2, base2); base1++);
		} while (numVal(num1, base1) != numVal(num2, base2));
		if (flip)
			fprintf(fout, "%d %d\n", base2, base1);
		else
			fprintf(fout, "%d %d\n", base1, base2);
	}
	fclose(fp);
	fclose(fout);
}

struct time
{
	bool is_connect;
	unsigned int bessie;
	unsigned int elsie;
};
unsigned int* bessieTimes;
unsigned int* elsieTimes;
unsigned int currPathNum = 0;
void recursive(unsigned int bessieTime, unsigned int elsieTime, time** conections, unsigned int numOfFeilds, unsigned int currFeild)
{
	if (conections[currFeild] == NULL) {
		bessieTimes[currPathNum] = bessieTime;
		elsieTimes[currPathNum] = elsieTime;
		currPathNum++;
	}
	else {
		unsigned int maxCons = numOfFeilds - currFeild - 1;
		for (unsigned int i = 0; i < maxCons; i++)
			if (conections[currFeild][i].is_connect)
				recursive(bessieTime + conections[currFeild][i].bessie, elsieTime + conections[currFeild][i].elsie, conections, numOfFeilds, currFeild + i + 1);
	}
}
int compareFunc(const void* p1, const void* p2) {
	return *((unsigned int*)p1) - *((unsigned int*)p2);
}
void q4(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfFeilds = getNum;
	unsigned int numOfConnections = getNum;
	time** conections = (time * *)malloc(sizeof(time*) * numOfFeilds);
	for (unsigned int i = 0; i < numOfFeilds - 1; i++)
		conections[i] = (time*)calloc(numOfFeilds - i - 1, sizeof(time));
	conections[numOfFeilds - 1] = NULL;
	unsigned int start, end;
	for (unsigned int i = 0; i < numOfConnections; i++) {
		start = getNum;
		end = getNum;
		conections[start - 1][end - start - 1].is_connect = true;
		conections[start - 1][end - start - 1].bessie = getNum;
		conections[start - 1][end - start - 1].elsie = getNum;
	}
	fclose(fp);
	bessieTimes = (unsigned int*)malloc(sizeof(unsigned int) * 32768);
	elsieTimes = (unsigned int*)malloc(sizeof(unsigned int) * 32768);
	recursive(0, 0, conections, numOfFeilds, 0);
	qsort(bessieTimes, currPathNum, sizeof(unsigned int), compareFunc);
	qsort(elsieTimes, currPathNum, sizeof(unsigned int), compareFunc);
	unsigned int bessieNum = 0;
	unsigned int elsieNum = 0;
	long ans = -1;
	while ((elsieNum < currPathNum) && (bessieNum < currPathNum)) {
		if (bessieTimes[bessieNum] == elsieTimes[elsieNum]) {
			ans = bessieTimes[bessieNum];
			break;
		}
		else if (bessieTimes[bessieNum] < elsieTimes[elsieNum])
			bessieNum++;
		else
			elsieNum++;
	}
	fp = fopen(fpOut, "w");
	if (ans == -1)
		fprintf(fp, "IMPOSSIBLE");
	else
		fprintf(fp, "%d", ans);
	fclose(fp);
}

int main(void)
{
	//q1("cowroute.in", "cowroute.out");
	//q2("cowroute.in", "cowroute.out");
	q3("whatbase.in", "whatbase.out");
	//q4("meeting.in", "meeting.out");
	
	//system("puase");
	return 0;
}