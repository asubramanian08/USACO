#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
#include <iostream>
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

//my answer - wrong for 6 questions
/*unsigned short* curr;
unsigned short* start;
unsigned short* end;
bool currIsSet = true;
#define _max(a,b) (((a) > (b)) ? (a) : (b))
unsigned int findFirstNum(void)
{
	unsigned int i = 0; 
	for (i = 0; i < 16; i++)
		if (end[i] != 0)
			break;
	return i;
}
bool checkEnd(unsigned int setToo, unsigned int currDiget, bool prev_isSet)
{
	if (prev_isSet && (curr[currDiget] == end[currDiget]))
		for (unsigned int i = currDiget + 1; i < 16; i++) {
			if (end[i] < setToo)
				return 0;
			else if (end[i] > setToo)
				break;
		}
	if (currIsSet && (curr[currDiget] == start[currDiget]))
		for (unsigned int i = currDiget + 1; i < 16; i++) {
			if (start[i] > setToo)
				return 0;
			else if (start[i] < setToo)
				break;
		}
	return 1;
}
bool checkEnd_2(unsigned int setToo, unsigned int currDiget, bool prev_isSet, bool curr_isSet)
{
	if (prev_isSet)
		for (unsigned int i = currDiget + 1; i < 16; i++) {
			if (end[i] < setToo)
				return 0;
			else if (end[i] > setToo)
				break;
		}
	if (curr_isSet)
		for (unsigned int i = currDiget + 1; i < 16; i++) {
			if (start[i] > setToo)
				return 0;
			else if (start[i] < setToo)
				break;
		}
	return 1;
}
unsigned long firstIsDiff(unsigned int currDiget, unsigned int currNum, bool prev_isSet) 
{
	unsigned long returnVal = 0;
	for (unsigned int num = 0; num <= 9; num++)
		if ((currNum != num) && (checkEnd_2(num, currDiget, prev_isSet && (currNum == end[currDiget]), currNum == start[currDiget])))
			returnVal++;
	return returnVal;
}
unsigned long recursave(unsigned int currDiget, unsigned int numSetToo, bool prev_isSet)
{
	if (currDiget == 15) {
		unsigned long returnVal = 0;
		unsigned short max;
		if (prev_isSet)
			max = end[15];
		else
			max = 9;
		while (curr[15] <= max) {
			returnVal += (curr[15] != numSetToo);
			curr[15]++;
		}
		curr[15] = 0;
		return returnVal;
	}
	unsigned long total = 0;
	unsigned int endAt = 9;
	if (prev_isSet)
		endAt = end[currDiget];
	while (curr[currDiget] <= endAt) {
		if (curr[currDiget] == numSetToo)
			total += recursave(currDiget + 1, numSetToo, prev_isSet && (curr[currDiget] == end[currDiget]));
		else if (numSetToo == 0) {
			total += recursave(currDiget + 1, curr[currDiget], prev_isSet && (curr[currDiget] == end[currDiget]));
			total += firstIsDiff(currDiget, curr[currDiget], prev_isSet);
		}
		else
			total += checkEnd(numSetToo, currDiget, prev_isSet);
		curr[currDiget]++;
		currIsSet = false;
	}
	curr[currDiget] = 0;
	return total;
}
void q1(const char* fpIn, const char* fpOut)
{
	curr = (unsigned short*)malloc(sizeof(unsigned short) * 16);
	end = (unsigned short*)malloc(sizeof(unsigned short) * 16);
	start = (unsigned short*)malloc(sizeof(unsigned short) * 16);
	bool addEnd;
	FILE* fp = fopen(fpIn, "r");
	FILE* fout = fopen(fpOut, "w");
	long long temp = getNum;
	if (temp == 10000000000000000) {
		fprintf(fout, "1");
		fclose(fp);
		fclose(fout);
		return;
	}
	for (unsigned int i = 0; i < 16; i++) {
		start[15 - i] = temp % 10;
		temp /= 10;
	}
	temp = getNum;
	if (temp == 10000000000000000) {
		addEnd = 1;
		for (unsigned int i = 0; i < 16; i++)
			end[i] = 9;
	}
	else {
		addEnd = false;
		for (unsigned int i = 0; i < 16; i++) {
			end[15 - i] = temp % 10;
			temp /= 10;
		}
	}
	fclose(fp);
	memcpy(curr, start, sizeof(unsigned short) * 16);
	unsigned long ans = recursave(0, 0, 1);
	ans += addEnd;
	fprintf(fout, "%lu", ans);
	fclose(fout);
}*/
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	
	fclose(fp);

	fp = fopen(fpOut, "w");

	fclose(fp);
}

//their answer
#define _max(a,b) (((a) > (b)) ? (a) : (b))
#define _min(a,b) (((a) < (b)) ? (a) : (b))
struct cow
{
	bool is_G;
	long place;
};
int compareFunc(const void* p1, const void* p2)
{
	return ((cow*)p1)->place - ((cow*)p2)->place;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	cow* order = (cow*)malloc(sizeof(cow) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		order[i].place = getNum;
		order[i].is_G = fgetc(fp) == 'G';
		fgetc(fp); //new line
	}
	fclose(fp);
	qsort(order, numOfCows, sizeof(cow), compareFunc);
	long ans = 0;
	unsigned int size;
	for (unsigned int i = 0; i < numOfCows; i+= size) { //the same types
		size = 1;
		while ((i + size < numOfCows) && (order[i].is_G == order[i + size].is_G)) size++;
		ans = _max(ans, order[i + size - 1].place - order[i].place);
	}

	long leftSum[200020];
	memset(leftSum, 0x3F, sizeof(leftSum));
	int currBalance = 0;
	for (unsigned int i = 0; i < numOfCows; i++) {
		leftSum[currBalance + numOfCows] = _min(leftSum[currBalance + numOfCows], order[i].place);
		if (order[i].is_G)
			currBalance++;
		else
			currBalance--;
		ans = _max(ans, order[i].place - leftSum[currBalance + numOfCows]);
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

unsigned int numOf[2];
struct linkList
{
	bool type;
	bool visited = false;
	unsigned int numOfConnections = 0;
	linkList** connections;
};
bool floodFill(linkList* currSpot, bool setTo)
{
	if (currSpot->visited)
		return currSpot->type == setTo;
	currSpot->visited = true;
	currSpot->type = setTo;
	numOf[setTo]++;
	for (unsigned int i = 0; i < currSpot->numOfConnections; i++)
		if (!floodFill(currSpot->connections[i], !setTo))
			return 0;
	return 1;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfFeilds = getNum;
	unsigned int numOfCon = getNum;
	linkList* feilds = (linkList*)malloc(sizeof(linkList) * numOfFeilds);
	for (unsigned int i = 0; i < numOfFeilds; i++) {
		feilds[i].numOfConnections = 0;
		feilds[i].visited = false;
	}
	for (unsigned int i = 0; i < numOfCon; i++) {
		feilds[getNum - 1].numOfConnections++;
		feilds[getNum - 1].numOfConnections++;
	}
	for (unsigned int i = 0; i < numOfFeilds; i++)
		if (feilds[i].numOfConnections == 0)
			feilds[i].connections = NULL;
		else
			feilds[i].connections = (linkList * *)malloc(sizeof(linkList*) * feilds[i].numOfConnections);
	fseek(fp, 0, SEEK_SET);
	getNum; getNum; //waste first
	unsigned int feild1, feild2;
	unsigned int* currCon = (unsigned int*)calloc(numOfFeilds, sizeof(unsigned int));
	for (unsigned int i = 0; i < numOfCon; i++) {
		feild1 = getNum - 1;
		feild2 = getNum - 1;
		feilds[feild1].connections[currCon[feild1]] = &feilds[feild2];
		feilds[feild2].connections[currCon[feild2]] = &feilds[feild1];
		currCon[feild1]++;
		currCon[feild2]++;
	}
	free(currCon);
	fclose(fp);
	int maxJ = 0;
	for (unsigned int i = 0; i < numOfFeilds; i++)
		if (!feilds[i].visited) {
			numOf[0] = 0;
			numOf[1] = 0;
			if (!floodFill(&feilds[i], false)) {
				maxJ = -1;
				break;
			}
			maxJ += _max(numOf[0], numOf[1]);
		}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", maxJ);
	fclose(fp);
}

int main(void)
{
	//q1("odometer.in", "odometer.out");
	//q2("fairphoto.in", "fairphoto.out");
	q3("decorate.in", "decorate.out");

	//system("pause");
	return 0;
}