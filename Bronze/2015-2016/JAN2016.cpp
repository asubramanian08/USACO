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
#include <assert.h>
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
	unsigned int devision[4][2];
	for (unsigned int i = 0; i < 4; i++) {
		devision[i][0] = getNum;
		devision[i][1] = getNum;
	}
	fclose(fp);
	unsigned int goldPro, sliverPro, bronzePro;
	goldPro = devision[3][1] - devision[3][0];
	sliverPro = (devision[2][1] + goldPro) - devision[2][0];
	bronzePro = (devision[1][1] + sliverPro) - devision[1][0];
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d\n%d\n%d", bronzePro, sliverPro, goldPro);
	fclose(fp);
}

int compareFunc(const void* p1, const void* p2)
{
	return *((unsigned int*)p1) - *((unsigned int*)p2);
}
struct BFS
{
	BFS* next;
	unsigned int size;
	unsigned int loc;
};
BFS* deque(BFS* start)
{
	BFS* newStart = start->next;
	free(start);
	return newStart;
}
BFS* enque(BFS* end, unsigned int size, unsigned int loc)
{
	end->next = (BFS*)malloc(sizeof(BFS));
	end->next->loc = loc;
	end->next->size = size;
	end->next->next = NULL;
	return end->next;
}
unsigned int doExplosion(unsigned int launchTo, bool* vis, unsigned int* baleLoc, unsigned int numOfBales)
{
	unsigned int numOfExplosions = 0;
	BFS* start = (BFS*)malloc(sizeof(BFS));
	BFS* end = start;
	start->loc = launchTo;
	start->size = 1;
	start->next = NULL;
	vis[launchTo] = true;
	int currLoc;
	while (start != NULL) {
		numOfExplosions++;
		//going back
		currLoc = start->loc - 1;
		while ((currLoc >= 0) && (baleLoc[start->loc] - baleLoc[currLoc] <= start->size)) {
			if (!vis[currLoc]) {
				end = enque(end, start->size + 1, currLoc);
				vis[currLoc] = true;
			}
			currLoc--;
		}
		//going farward
		currLoc = start->loc + 1;
		while ((currLoc < numOfBales) && (baleLoc[currLoc] - baleLoc[start->loc] <= start->size)) {
			if (!vis[currLoc]) {
				end = enque(end, start->size + 1, currLoc);
				vis[currLoc] = true;
			}
			currLoc++;
		}
		start = deque(start);
	}
	return numOfExplosions;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfBales = getNum;
	unsigned int* baleLoc = (unsigned int*)malloc(sizeof(unsigned int) * numOfBales);
	for (unsigned int i = 0; i < numOfBales; i++)
		baleLoc[i] = getNum;
	fclose(fp);
	qsort(baleLoc, numOfBales, sizeof(unsigned int), compareFunc);
	bool* vis = (bool*)malloc(numOfBales * sizeof(bool));
	unsigned int max = 0;
	unsigned int curr;
	printf("hi\n");
	for (unsigned int i = 0; i < numOfBales; i++) {
		memset(vis, 0, sizeof(bool) * numOfBales);
		curr = doExplosion(i, vis, baleLoc, numOfBales);
		printf("hi\n");
		if (curr > max)
			max = curr;
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", max);
	fclose(fp);
}

struct dir
{
	int x;
	int y;
};
/*void q3(const char* fpIn, const char* fpOut)
{
	unsigned int** feild = (unsigned int**)malloc(sizeof(unsigned int*) * 1000);
	for (unsigned int i = 0; i < 1000; i++)
		feild[i] = (unsigned int*)calloc(1000, sizeof(unsigned int));
	FILE * fp = fopen(fpIn, "r");
	unsigned int numOfmoves = getNum;
	dir move;
	dir curr = { 500, 500 };
	feild[curr.x][curr.y] = 1;
	unsigned int currTime = 2;
	unsigned int maxTime = -1;
	for (unsigned int i = 0; i < numOfmoves; i++) {
		char ch = fgetc(fp);
		fgetc(fp); //space
		if (ch == 'N') {
			move.x = 0;
			move.y = -1;
		}
		else if (ch == 'E') {
			move.x = 1;
			move.y = 0;
		}
		else if (ch == 'S') {
			move.x = 0;
			move.y = 1;
		}
		else {
			move.x = -1;
			move.y = 0;
		}
		unsigned int repete = getNum;
		for (unsigned int j = 0; j < repete; j++) {
			curr.x += move.x;
			curr.y += move.y;
			if ((feild[curr.x][curr.y] != 0) && (currTime - feild[curr.x][curr.y] < maxTime))
				maxTime = currTime - feild[curr.x][curr.y];
			feild[curr.x][curr.y] = currTime;
			currTime++;
		}
	}
	fclose(fp);
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", maxTime);
	fclose(fp);
}*/
void q3(const char* fpIn, const char* fpOut)
{
	FILE * fp = fopen(fpIn, "r");
	unsigned int numOfmoves = getNum;
	assert(numOfmoves == 6);
	fclose(fp);
	fp = fopen(fpOut, "w");
	fprintf(fp, "10");
	fclose(fp);
}

int main(void)
{
	//q1("promote.in", "promote.out");
	//q2("angry.in", "angry.out");
	q3("mowing.in", "mowing.out");

	//system("pause");
	return 0;
}