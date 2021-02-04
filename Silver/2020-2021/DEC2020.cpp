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
char* readStr(int size, int* endSize)
{
	char ch = getchar();
	char* str = (char*)malloc(sizeof(char) * (size + 1));
	int i = 0;
	while ((ch != ' ') && (ch != '\n')) {
		str[i] = ch;
		i++;
		ch = getchar();
	}
	str[i] = '\0';
	*endSize = i + 1;
	str = (char*)realloc(str, sizeof(char) * (i + 1));
	return str;
}
long long getNum()
{
	char ch = getchar();
	if (ch == '-')
		return -1 * getNum();
	else {
		long long total = ch - '0';
		ch = getchar();
		while ((ch != ' ') && (ch != '\n')) {
			total = total * 10 + ch - '0';
			ch = getchar();
		}
		return total;
	}
}

unsigned int minPow(unsigned int num)
{
	unsigned int pow = 0;
	unsigned int comp = 1;
	while (comp < num) {
		pow++;
		comp *= 2;
	}
	return pow;
}
void q1(void)
{
	unsigned int numOfFarms = getNum();
	unsigned int* conns = (unsigned int*)calloc(numOfFarms, sizeof(unsigned int));
	for (unsigned int i = 1; i < numOfFarms; i++) {
		conns[getNum() - 1]++; //farm 1
		conns[getNum() - 1]++; //farm 2
	}
	unsigned int days = minPow(conns[0] + 1);
	for (unsigned int i = 1; i < numOfFarms; i++)
		days += minPow(conns[i]);
	printf("%d", days + (numOfFarms - 1));
}

struct cowLoc
{
	unsigned int x;
	unsigned int y;
};
int compareY(const void* p1, const void* p2)
{
	return ((cowLoc*)p1)->y - ((cowLoc*)p2)->y;
}
void q2(void)
{
	unsigned int numOfCows = getNum();
	cowLoc* cows = (cowLoc*)malloc(sizeof(cowLoc) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].x = getNum();
		cows[i].y = getNum();
	}
	qsort(cows, numOfCows, sizeof(cowLoc), compareY);
	unsigned int numLess, numMore, smallerX, biggerX;
	unsigned long long ans = 0;
	for(unsigned int i = 0; i < numOfCows; i++)
		for (unsigned int j = i; j < numOfCows; j++) {
			numLess = 0; numMore = 0; smallerX = _min(cows[i].x, cows[j].x); biggerX = _max(cows[i].x, cows[j].x);
			for (unsigned int k = i; k <= j; k++) {
				if (cows[k].x <= smallerX)
					numLess++;
				if (cows[k].x >= biggerX)
					numMore++;
				
			}
			ans += numLess * numMore;
		}
	printf("%lld", ans + 1);
}

struct stack
{
	unsigned int blameFrom;
	stack* next;
};
struct cow
{
	bool is_nor;
	bool stopped;
	unsigned long x;
	unsigned long y;
	unsigned int orgLoc;
	stack* getBlames;
	unsigned int blames;
};
cow* cows;
inline bool willCross(unsigned int nor, unsigned int eas)
{
	return ((cows[nor].y <= cows[eas].y) && (cows[nor].x >= cows[eas].x));
}
int compareCow(const void* a, const void* b)
{
	cow* p1 = (cow*)a;
	cow* p2 = (cow*)b;
	if (p1->is_nor - p2->is_nor)
		return p1->is_nor - p2->is_nor;
	if (p1->is_nor)
		return p1->x - p2->x;
	return p1->y - p2->y;
}
int compareLoc(const void* p1, const void* p2)
{
	return ((cow*)p1)->orgLoc - ((cow*)p2)->orgLoc;
}
void fixBlames(unsigned int currCow)
{
	stack* curr = cows[currCow].getBlames;
	while (curr) {
		fixBlames(curr->blameFrom);
		cows[currCow].blames += cows[curr->blameFrom].blames;
		curr = curr->next;
	}
}
void q3(void)
{
	unsigned int numOfCows = getNum();
	cows = (cow*)malloc(sizeof(cow) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		cows[i].is_nor = (getchar() == 'N');
		getchar();//space
		cows[i].x = getNum();
		cows[i].y = getNum();
		cows[i].stopped = false;
		cows[i].orgLoc = i;
		cows[i].getBlames = NULL;
		cows[i].blames = 0;
	}
	qsort(cows, numOfCows, sizeof(cow), compareCow);
	unsigned int switchDir; for (switchDir = 0; cows[switchDir].is_nor == false; switchDir++); //find where it switches
	stack* temp;
	for (unsigned int i = 0; i < switchDir; i++)
		for (unsigned int j = switchDir; j < numOfCows; j++)
			if ((cows[i].stopped == false) && (cows[j].stopped == false) && (willCross(j, i))) {
				temp = (stack*)malloc(sizeof(stack));
				if (cows[j].x - cows[i].x < cows[i].y - cows[j].y) {
					cows[j].stopped = true;
					cows[i].blames++;
					temp->blameFrom = j;
					temp->next = cows[i].getBlames;
					cows[i].getBlames = temp;
				}
				else if (cows[j].x - cows[i].x > cows[i].y - cows[j].y) {
					cows[i].stopped = true;
					cows[j].blames++;
					temp->blameFrom = i;
					temp->next = cows[j].getBlames;
					cows[j].getBlames = temp;
				}
			}
	for (unsigned int i = 0; i < numOfCows; i++)
		if (!cows[i].stopped)
			fixBlames(i);
	qsort(cows, numOfCows, sizeof(cow), compareLoc);
	for (unsigned int i = 0; i < numOfCows; i++)
		printf("%d\n", cows[i].blames);
}

int main(void)
{
	//q1();
	q2();
	//q3();

	//system("pause");
	return 0;
}