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

struct uni
{
	unsigned int time;
	unsigned int numOfCows;
};
int compareUni(const void* p1, const void* p2)
{
	return ((uni*)p1)->time - ((uni*)p2)->time;
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfUni = getNum;
	uni* unis = (uni*)malloc(sizeof(uni) * numOfUni);
	for (unsigned int i = 0; i < numOfUni; i++) {
		unis[i].numOfCows = getNum;
		unis[i].time = getNum;
	}
	fclose(fp);
	qsort(unis, numOfUni, sizeof(uni), compareUni);
	unsigned int maxTime = 0, low = 0, high = numOfUni - 1;
	while (low < high) {
		if (maxTime < unis[low].time + unis[high].time)
			maxTime = unis[low].time + unis[high].time;
		if (unis[low].numOfCows < unis[high].numOfCows) {
			unis[high].numOfCows -= unis[low].numOfCows;
			unis[low].numOfCows = 0;
			low++;
		}
		else if (unis[low].numOfCows > unis[high].numOfCows) {
			unis[low].numOfCows -= unis[high].numOfCows;
			unis[high].numOfCows = 0;
			high--;
		}
		else {
			unis[low].numOfCows = 0;
			unis[high].numOfCows = 0;
			low++;
			high--;
		}
	}
	if ((low == high) && (maxTime < unis[low].time + unis[high].time))
		maxTime = unis[low].time + unis[high].time;
	fp = fopen(fout, "w");
	fprintf(fp, "%d", maxTime);
	fclose(fp);
}

void q2(const char* fin, const char* fout)
{
	bool* beenBefore = (bool*)malloc(sizeof(bool) * 4 * 4 * 4);
	bool gain;
	int waste;
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum;
	unsigned int numOfChars = getNum;
	char** spotty = (char**)malloc(sizeof(char*) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++)
		spotty[i] = readStrInFile(&fp, numOfChars, &waste);
	char** plain = (char**)malloc(sizeof(char*) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++)
		plain[i] = readStrInFile(&fp, numOfChars, &waste);
	for (unsigned int i = 0; i < numOfCows; i++) {
		for (unsigned int j = 0; j < numOfChars; j++) {
			if (spotty[i][j] == 'A')
				spotty[i][j] = 0;
			else if(spotty[i][j] == 'C')
				spotty[i][j] = 1;
			else if (spotty[i][j] == 'G')
				spotty[i][j] = 2;
			else
				spotty[i][j] = 3;

			if (plain[i][j] == 'A')
				plain[i][j] = 0;
			else if (plain[i][j] == 'C')
				plain[i][j] = 1;
			else if (plain[i][j] == 'G')
				plain[i][j] = 2;
			else
				plain[i][j] = 3;
		}
	}
	fclose(fp);
	unsigned int ans = 0;
	for (unsigned int i = 0; i < numOfChars; i++)
		for(unsigned int j  = i + 1; j < numOfChars; j++)
			for (unsigned int k = j + 1; k < numOfChars; k++) {
				gain = true;
				memset(beenBefore, 0, sizeof(bool) * 4 * 4 * 4);
				for (unsigned int l = 0; l < numOfCows; l++)
					beenBefore[((4 * ((4 * (plain[l][i])) + plain[l][j])) + plain[l][k])] = true;
				for (unsigned int l = 0; l < numOfCows; l++)
					if (beenBefore[((4 * ((4 * (spotty[l][i])) + spotty[l][j])) + spotty[l][k])] == true) {
						gain = false;
						break;
					}
				ans += gain;
			}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

char** pic;
bool* vis;
unsigned int sideLen;
bool* doneBefore;
void flood(unsigned int lowX, unsigned int lowY, unsigned int highX, unsigned int highY, unsigned int currX, unsigned int currY)
{
	if (vis[currX * sideLen + currY] == true)
		return;
	vis[currX * sideLen + currY] = true;
	if ((currX > lowX) && (pic[currX - 1][currY] == pic[currX][currY]))
		flood(lowX, lowY, highX, highY, currX - 1, currY);
	if ((currX < highX) && (pic[currX + 1][currY] == pic[currX][currY]))
		flood(lowX, lowY, highX, highY, currX + 1, currY);
	if ((currY > lowY) && (pic[currX][currY - 1] == pic[currX][currY]))
		flood(lowX, lowY, highX, highY, currX, currY - 1);
	if ((currY < highY) && (pic[currX][currY + 1] == pic[currX][currY]))
		flood(lowX, lowY, highX, highY, currX, currY + 1);
}
bool works(unsigned int lowX, unsigned int lowY, unsigned int highX, unsigned int highY)
{
	memset(vis, 0, sideLen * sideLen * sizeof(bool));
	char ch1 = pic[lowX][lowY], ch2 = '\0';
	unsigned int numOfCh1 = 0, numOfCh2 = 0;
	for (unsigned int i = lowX; i <= highX; i++)
		for (unsigned int j = lowY; j <= highY; j++)
			if (!vis[i * sideLen + j]) {
				if (pic[i][j] != ch1) {
					if (ch2 == '\0')
						ch2 = pic[i][j];
					else if (pic[i][j] != ch2)
						return false;
					numOfCh2++;
				}
				else
					numOfCh1++;
				if ((numOfCh1 <= 1) || (numOfCh2 <= 1))
					flood(lowX, lowY, highX, highY, i, j);
				else
					return false;
			}
	return ((numOfCh1 > 1) || (numOfCh2 > 1));
}
struct queue
{
	unsigned int lowX, lowY, highX, highY, canDo;
	queue* next;
};
queue* deque(queue* start) {
	queue* temp = start;
	start = start->next;
	free(temp);
	return start;
}
queue* enqueue(queue* end, unsigned int lowX, unsigned int lowY, unsigned int highX, unsigned int highY, unsigned int canDo)
{
	end->next = (queue*)malloc(sizeof(queue));
	end = end->next;
	end->canDo = canDo; end->highX = highX; end->lowX = lowX; end->highY = highY; end->lowY = lowY; end->next = NULL;
	return end;
}
#define findRect(lowX, lowY, highX, highY) ((((((sideLen * lowX) + lowY) * sideLen) + highX) * sideLen) + highY)
unsigned int BFS()
{
	queue* start = (queue*)malloc(sizeof(queue));
	queue* end = start;
	start->canDo = 0; start->highX = sideLen - 1; start->lowX = 0; start->highY = sideLen - 1; start->lowY = 0; start->next = NULL;

	unsigned int returnVal = 0;
	while (start != NULL) {
		if (((start->highX == start->lowX) || (start->highY == start->lowY)) ||
			((start->lowX > 0) && doneBefore[findRect(start->lowX - 1, start->lowY, start->highX, start->highY)]) ||
			((start->lowY > 0) && doneBefore[findRect(start->lowX, start->lowY - 1, start->highX, start->highY)]) ||
			((start->highX < sideLen - 1) && doneBefore[findRect(start->lowX, start->lowY, start->highX + 1, start->highY)]) ||
			((start->highY < sideLen - 1) && doneBefore[findRect(start->lowX, start->lowY, start->highX, start->highY + 1)])) {
			start = deque(start);
			doneBefore[findRect(start->lowX, start->lowY, start->highX, start->highY)] = true;
			continue;
		}
		if (works(start->lowX, start->lowY, start->highX, start->highY)) {
			returnVal++;
			start = deque(start);
			doneBefore[findRect(start->lowX, start->lowY, start->highX, start->highY)] = true;
			continue;
		}
		switch (start->canDo) {
		case 0:
			end = enqueue(end, start->lowX + 1, start->lowY, start->highX, start->highY, 0);
		case 1:
			end = enqueue(end, start->lowX, start->lowY + 1, start->highX, start->highY, 1);
		case 2:
			end = enqueue(end, start->lowX, start->lowY, start->highX - 1, start->highY, 2);
		case 3:
			end = enqueue(end, start->lowX, start->lowY, start->highX, start->highY - 1, 3);
		}
		start = deque(start);
	}
	return returnVal;
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	sideLen = getNum;
	pic = (char**)malloc(sizeof(char*) * sideLen);
	vis = (bool*)calloc(sideLen * sideLen, sizeof(bool));
	doneBefore = (bool*)calloc(sideLen * sideLen * sideLen * sideLen, sizeof(bool));
	for (unsigned int i = 0; i < sideLen; i++) {
		pic[i] = (char*)malloc(sizeof(char) * sideLen);
		for (unsigned int j = 0; j < sideLen; j++)
			pic[i][j] = fgetc(fp);
		fgetc(fp); //newline
	}
	fclose(fp);
	unsigned int ans = BFS();
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

int main(void)
{
	//q1("pairup.in", "pairup.out");
	q2("cownomics.in", "cownomics.out");
	//q3("where.in", "where.out");
}