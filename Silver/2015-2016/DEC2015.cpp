//same questions as silver diagnostic



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

struct linkList
{
	unsigned int x;
	unsigned int y;
	linkList* next;
};
struct room
{
	bool is_lit;
	bool vis;
	linkList* start;
	linkList* end;
};
room* grid;
unsigned int sideLen;
inline bool couldGo(unsigned int x, unsigned int y) {
	if ((x >= 1) && (grid[(x - 1) * sideLen + y].vis))
		return 1;
	if ((y >= 1) && (grid[x * sideLen + (y - 1)].vis))
		return 1;
	if ((x < sideLen - 1) && (grid[(x + 1) * sideLen + y].vis))
		return 1;
	if ((y < sideLen - 1) && (grid[x * sideLen + (y + 1)].vis))
		return 1;
	return 0;
}
void recursive(unsigned int x, unsigned int y)
{
	grid[x * sideLen + y].vis = true;
	while (grid[x * sideLen + y].start) { //go thrugh the things that can be lit
		grid[(grid[x * sideLen + y].start->x * sideLen) + grid[x * sideLen + y].start->y].is_lit = true;
		if ((!grid[(grid[x * sideLen + y].start->x * sideLen) + grid[x * sideLen + y].start->y].vis) && //not gone alreay
			couldGo(grid[x * sideLen + y].start->x, grid[x * sideLen + y].start->y)) //it around it was vis
			recursive(grid[x * sideLen + y].start->x, grid[x * sideLen + y].start->y);
		grid[x * sideLen + y].start = grid[x * sideLen + y].start->next;
	}
	//go up, down, left, right
	if ((x >= 1) && ((!grid[(x - 1) * sideLen + y].vis) && grid[(x - 1) * sideLen + y].is_lit))
		recursive(x - 1, y);
	if ((y >= 1) && ((!grid[x * sideLen + (y - 1)].vis) && grid[x * sideLen + (y - 1)].is_lit))
		recursive(x, y - 1);
	if ((x < sideLen - 1) && ((!grid[(x + 1) * sideLen + y].vis) && grid[(x + 1) * sideLen + y].is_lit))
		recursive(x + 1, y);
	if ((y < sideLen - 1) && ((!grid[x * sideLen + (y + 1)].vis) && grid[x * sideLen + (y + 1)].is_lit))
		recursive(x, y + 1);
}
void q1(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");
	sideLen = getNum;
	unsigned int numOfSwitch = getNum;
	grid = (room*)calloc(sideLen * sideLen, sizeof(room));
	unsigned int a, b, c, d;
	for (unsigned int i = 0; i < numOfSwitch; i++) {
		a = getNum - 1; b = getNum - 1; c = getNum - 1; d = getNum - 1;
		if (grid[a * sideLen + b].end == NULL) {
			grid[a * sideLen + b].start = (linkList*)malloc(sizeof(linkList));
			grid[a * sideLen + b].start->x = c;
			grid[a * sideLen + b].start->y = d;
			grid[a * sideLen + b].start->next = NULL;
			grid[a * sideLen + b].end = grid[a * sideLen + b].start;
		}
		else {
			grid[a * sideLen + b].end->next = (linkList*)malloc(sizeof(linkList));
			grid[a * sideLen + b].end->next->x = c;
			grid[a * sideLen + b].end->next->y = d;
			grid[a * sideLen + b].end->next->next = NULL;
			grid[a * sideLen + b].end = grid[a * sideLen + b].end->next;
		}
	}
	fclose(fp);
	grid[0].is_lit = true;
	recursive(0, 0);
	unsigned int ans = 0;
	fp = fopen(fout, "w");
	for (unsigned int i = 0; i < sideLen; i++)
		for (unsigned int j = 0; j < sideLen; j++)
			ans += grid[i * sideLen + j].is_lit;
	fprintf(fp, "%d", ans);
	fclose(fp);
}

void q2(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");

	fclose(fp);


	fp = fopen(fin, "r");

	fclose(fp);
}

void q3(const char* fin, const char* fout)
{
	FILE* fp = fopen(fin, "r");

	fclose(fp);


	fp = fopen(fin, "r");

	fclose(fp);
}

int main(void)
{
	q1("lightson.in", "lightson.out");
	//q2(".in", ".out");
	//q3(".in", ".out");

	//system("pause");
	return 0;
}