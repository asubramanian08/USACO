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

void q1(const char* fin, const char* fout)
{
	int lowestPoint = 0;
	unsigned int locOfLowPoint = 0;
	int currVal = 0;
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum;
	unsigned int* rooms = (unsigned int*)malloc(sizeof(unsigned int) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		rooms[i] = getNum;
		currVal += rooms[i] - 1;
		if (currVal <= lowestPoint) {
			locOfLowPoint = i + 1;
			lowestPoint = currVal;
		}
	}
	fclose(fp);
	unsigned int* cowsFrom = (unsigned int*)malloc(sizeof(unsigned int) * (numOfCows + 1));
	unsigned int* start = cowsFrom, *end = cowsFrom;
	unsigned int ans = 0;
	unsigned int currPoint;
	for (unsigned int i = 0; i < numOfCows; i++) {
		currPoint = (i + locOfLowPoint) % numOfCows;
		for (unsigned int j = 0; j < rooms[currPoint]; j++) {
			*end = i;
			end++;
		}
		ans += (i - *start) * (i - *start);
		start++;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

struct point
{
	unsigned int x;
	unsigned int y;
	bool greaterThanX;
};
int compareFuncX(const void* p1, const void* p2)
{
	return (**((point * *)p1)).x - (**((point * *)p2)).x;
}
int compareFuncY(const void* p1, const void* p2)
{
	return (**((point * *)p1)).y - (**((point * *)p2)).y;
}
void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	unsigned int numOfCows = getNum;
	point* cows = (point*)malloc(sizeof(point) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].x = getNum;
		cows[i].y = getNum;
		cows[i].greaterThanX = true;
	}
	fclose(fp);
	point** byX = (point * *)malloc(sizeof(point*) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++)
		byX[i] = &cows[i];
	qsort(byX, numOfCows, sizeof(point*), compareFuncX);
	point** byY = (point * *)malloc(sizeof(point*) * numOfCows);
	memcpy(byY, byX, sizeof(point*) * numOfCows);
	qsort(byY, numOfCows, sizeof(point*), compareFuncY);
	unsigned int quadrents[4] = { 0, numOfCows, 0, 0 };
	unsigned int ans = numOfCows;
	unsigned int curr;
	for (unsigned int x = 0; x < numOfCows; x++) {
		byX[x]->greaterThanX = false;
		quadrents[1]--;
		quadrents[0]++;
		if ((x + 1 < numOfCows) && (byX[x]->x == byX[x + 1]->x))
			continue;
		for (unsigned int y = 0; y < numOfCows; y++) {
			if (byY[y]->greaterThanX) {
				quadrents[1]--;
				quadrents[3]++;
			}
			else {
				quadrents[0]--;
				quadrents[2]++;
			}
			if ((y + 1 < numOfCows) && (byY[y]->y == byY[y + 1]->y))
				continue;
			curr = _max(_max(quadrents[0], quadrents[1]), _max(quadrents[2], quadrents[3]));
			if (curr < ans)
				ans = curr;
		}
		quadrents[0] += quadrents[2];
		quadrents[1] += quadrents[3];
		quadrents[2] = 0;
		quadrents[3] = 0;
	}
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

unsigned int pail1, pail2, maxDepth;
int idealSum;
bool* alreadyDid;
struct queue
{
	unsigned int depth;
	int conts1, conts2;
	queue* next;
};
queue* enque(unsigned int depth, int conts1, int conts2, queue* end)
{
	end->next = (queue*)malloc(sizeof(queue));
	end->next->next = NULL;
	end->next->depth = depth;
	end->next->conts1 = conts1;
	end->next->conts2 = conts2;
	return end->next;
}
unsigned int BFS(void)
{
	queue* start = (queue*)malloc(sizeof(queue));
	queue* end = start;
	queue* temp;
	start->conts1 = 0;
	start->conts2 = 0;
	start->depth = 0;
	start->next = NULL;
	unsigned int smallestDiff = idealSum;
	unsigned int currDiff;
	while (start) {
		if ((start->depth == maxDepth) || (alreadyDid[(start->conts2 * (pail1 + 1)) + start->conts1])) {
			currDiff = abs(idealSum - (start->conts1 + start->conts2));
			if (currDiff < smallestDiff)
				smallestDiff = currDiff;
		}
		else {
			if (start->conts1 != pail1)
				end = enque(start->depth + 1, pail1, start->conts2, end);
			if (start->conts2 != pail2)
				end = enque(start->depth + 1, start->conts1, pail2, end);
			if (start->conts1 != 0)
				end = enque(start->depth + 1, 0, start->conts2, end);
			if (start->conts2 != 0)
				end = enque(start->depth + 1, start->conts1, 0, end);
			if ((start->conts1 != pail1) && (start->conts2 != 0)) {
				if (pail1 - start->conts1 < start->conts2)
					end = enque(start->depth + 1, pail1, start->conts2 - (pail1 - start->conts1), end);
				else
					end = enque(start->depth + 1, start->conts1 + start->conts2, 0, end);
			}
			if ((start->conts2 != pail2) && (start->conts1 != 0)) {
				if (pail2 - start->conts2 < start->conts1)
					end = enque(start->depth + 1, start->conts1 - (pail2 - start->conts2), pail2, end);
				else
					end = enque(start->depth + 1, 0, start->conts1 + start->conts2, end);
			}
		}
		
		alreadyDid[(start->conts2 * (pail1 + 1)) + start->conts1] = true;
		temp = start;
		start = start->next;
		free(temp);
	}
	return smallestDiff;
}
void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	pail1 = getNum; pail2 = getNum; maxDepth = getNum; idealSum = getNum;
	fclose(fp);
	alreadyDid = (bool*)calloc((pail1 + 1) * (pail2 + 1), sizeof(bool));
	unsigned int ans = BFS();
	fp = fopen(fout, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

int main(void)
{
	//q1("cbarn.in", "cbarn.out");
	//q2("balancing.in", "balancing.out");
	q3("pails.in", "pails.out");

	//system("pause");
	return 0;
}