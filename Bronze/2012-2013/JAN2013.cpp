#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <stdarg.h>
//#include <assert.h>
//_CRT_SECURE_NO_WARNINGS;

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

//didn't get
struct point
{
	int x;
	int y;
};
struct linkList;
struct mirror
{
	char tilt_house;
	point loc;
	linkList* by_xLoc;
	linkList* by_yLoc;
	unsigned int orderNum;
	bool important = 0;
	bool vis;
	int dir;
};
struct linkList
{
	linkList* prev;
	linkList* next;
	unsigned int mirrorOrderNum;
};
int compareByX(const void* p1, const void* p2)
{
	mirror* a = (mirror*)p1;
	mirror* b = (mirror*)p2;
	if (a->loc.x - b->loc.x)
		return a->loc.x - b->loc.x;
	return a->loc.y - b->loc.y;
}
int compareByY(const void* p1, const void* p2)
{
	mirror* a = (mirror*)p1;
	mirror* b = (mirror*)p2;
	if (a->loc.y - b->loc.y)
		return a->loc.y - b->loc.y;
	return a->loc.x - b->loc.x;
}
int compareByOrder(const void* p1, const void* p2)
{
	mirror* a = (mirror*)p1;
	mirror* b = (mirror*)p2;
	return a->orderNum - b->orderNum;
}
bool findImportant(mirror* startOrder, unsigned int firstMirror){
	unsigned int currLoc = firstMirror;
	int dir = 1;
	while (true) { //loop through the view
		if ((startOrder[currLoc].vis) && (startOrder[currLoc].dir == dir))
			return 0;
		startOrder[currLoc].vis = 1;
		startOrder[currLoc].dir = dir;
		if (startOrder[currLoc].tilt_house == 'B')
			return 1;
		else if (startOrder[currLoc].tilt_house == '/') {
			if ((dir) && (startOrder[currLoc].by_xLoc->next != NULL))
				currLoc = startOrder[currLoc].by_xLoc->next->mirrorOrderNum;
			else if ((!dir) && (startOrder[currLoc].by_xLoc->prev != NULL))
				currLoc = startOrder[currLoc].by_xLoc->prev->mirrorOrderNum;
			else
				return 0;
		}
		else { //going like '\'
			if ((dir) && (startOrder[currLoc].by_xLoc->prev != NULL))
				currLoc = startOrder[currLoc].by_xLoc->prev->mirrorOrderNum;
			else if ((!dir) && (startOrder[currLoc].by_xLoc->next != NULL))
				currLoc = startOrder[currLoc].by_xLoc->next->mirrorOrderNum;
			else 
				return 0;
			dir = !dir;
		}
		startOrder[currLoc].important = 1;

		if ((startOrder[currLoc].vis) && (startOrder[currLoc].dir == dir + 2))
			return 0;
		startOrder[currLoc].vis = 1;
		startOrder[currLoc].dir = dir + 2;
		if (startOrder[currLoc].tilt_house == 'B')
			return 1;
		else if (startOrder[currLoc].tilt_house == '/') {
			if ((dir) && (startOrder[currLoc].by_yLoc->next != NULL))
				currLoc = startOrder[currLoc].by_yLoc->next->mirrorOrderNum;
			else if ((!dir) && (startOrder[currLoc].by_yLoc->prev != NULL))
				currLoc = startOrder[currLoc].by_yLoc->prev->mirrorOrderNum;
			else
				return 0;
		}
		else { //going like '\'
			if ((dir) && (startOrder[currLoc].by_yLoc->prev != NULL))
				currLoc = startOrder[currLoc].by_yLoc->prev->mirrorOrderNum;
			else if ((!dir) && (startOrder[currLoc].by_yLoc->next != NULL))
				currLoc = startOrder[currLoc].by_yLoc->next->mirrorOrderNum;
			else
				return 0;
			dir = !dir;
		}
		startOrder[currLoc].important = 1;
	}
}
bool cheak(mirror* startOrder, unsigned int firstMirror)
{
	unsigned int currLoc = firstMirror;
	bool dir = 1;
	while (true) { //loop through the view
		if ((startOrder[currLoc].vis) && (startOrder[currLoc].dir == dir))
			return 0;
		startOrder[currLoc].vis = 1;
		startOrder[currLoc].dir = dir;
		if (startOrder[currLoc].tilt_house == 'B')
			return 1;
		else if (startOrder[currLoc].tilt_house == '/') {
			if ((dir) && (startOrder[currLoc].by_xLoc->next != NULL))
				currLoc = startOrder[currLoc].by_xLoc->next->mirrorOrderNum;
			else if ((!dir) && (startOrder[currLoc].by_xLoc->prev != NULL))
				currLoc = startOrder[currLoc].by_xLoc->prev->mirrorOrderNum;
			else
				return 0;
		}
		else { //going like '\'
			if ((dir) && (startOrder[currLoc].by_xLoc->prev != NULL))
				currLoc = startOrder[currLoc].by_xLoc->prev->mirrorOrderNum;
			else if ((!dir) && (startOrder[currLoc].by_xLoc->next != NULL))
				currLoc = startOrder[currLoc].by_xLoc->next->mirrorOrderNum;
			else
				return 0;
			dir = !dir;
		}

		if ((startOrder[currLoc].vis) && (startOrder[currLoc].dir == dir + 2))
			return 0;
		startOrder[currLoc].vis = 1;
		startOrder[currLoc].dir = dir + 2;
		if (startOrder[currLoc].tilt_house == 'B')
			return 1;
		else if (startOrder[currLoc].tilt_house == '/') {
			if ((dir) && (startOrder[currLoc].by_yLoc->next != NULL))
				currLoc = startOrder[currLoc].by_yLoc->next->mirrorOrderNum;
			else if ((!dir) && (startOrder[currLoc].by_yLoc->prev != NULL))
				currLoc = startOrder[currLoc].by_yLoc->prev->mirrorOrderNum;
			else
				return 0;
		}
		else { //going like '\'
			if ((dir) && (startOrder[currLoc].by_yLoc->prev != NULL))
				currLoc = startOrder[currLoc].by_yLoc->prev->mirrorOrderNum;
			else if ((!dir) && (startOrder[currLoc].by_yLoc->next != NULL))
				currLoc = startOrder[currLoc].by_yLoc->next->mirrorOrderNum;
			else
				return 0;
			dir = !dir;
		}
	}
}
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfImp_points = getNumInFile(&fp) +1;
	mirror* startOrder = (mirror*)malloc(sizeof(mirror) * numOfImp_points);
	startOrder->tilt_house = 'B';
	startOrder->loc.x = getNumInFile(&fp);
	startOrder->loc.y = getNumInFile(&fp);
	startOrder->orderNum = 0;
	for (unsigned int i = 1; i < numOfImp_points; i++) {
		startOrder[i].loc.x = getNumInFile(&fp);
		startOrder[i].loc.y = getNumInFile(&fp);
		startOrder[i].tilt_house = fgetc(fp);
		startOrder[i].orderNum = i;
		startOrder[i].important = false;
		fgetc(fp); //get rid of the new line
	}
	fclose(fp);
	//start set up
	fp = NULL;
	fp = fopen(fpOut, "w");
	qsort(startOrder, numOfImp_points, sizeof(mirror), compareByX);
	unsigned int numOf_x = 0;
	int curr = startOrder[0].loc.x;
	unsigned int fisrtMirror;
	bool found = 0;
	for (unsigned int i = 0; i < numOfImp_points; i++) { //counting numOf_x
		if (startOrder[i].loc.x != curr) {
			curr = startOrder[i].loc.x;
			numOf_x++;
		}
		if (!found && ((startOrder[i].loc.y == 0) && (startOrder[i].loc.x > 0))) {
			fisrtMirror = startOrder[i].orderNum;
			found = 1;
		}
		startOrder[i].loc.x = numOf_x; //scaling down
	}
	if (found == 0) {
		fprintf(fp, "-1");
		return;
	}
	numOf_x++;
	linkList** by_x = (linkList * *)malloc(sizeof(linkList*) * numOf_x);
	unsigned int currLoc = 0;
	linkList* currLink;
	linkList* prev;
	for (unsigned int i = 0; i < numOf_x; i++) {
		curr = startOrder[currLoc].loc.x;
		by_x[i] = (linkList*)malloc(sizeof(linkList));
		prev = by_x[i];
		prev->prev = NULL;
		prev->mirrorOrderNum = startOrder[currLoc].orderNum;
		startOrder[currLoc].by_xLoc = prev;
		currLoc++;
		while ((currLoc < numOfImp_points) && (startOrder[currLoc].loc.x == curr)) {
			prev->next = (linkList*)malloc(sizeof(linkList));
			currLink = prev->next;
			currLink->mirrorOrderNum = startOrder[currLoc].orderNum;
			currLink->prev = prev;
			startOrder[currLoc].by_xLoc = currLink;
			currLoc++;
			prev = currLink;
		}
		prev->next = NULL;
	}

	qsort(startOrder, numOfImp_points, sizeof(mirror), compareByY);
	unsigned int numOf_y = 0;
	curr = startOrder[0].loc.y;
	for (unsigned int i = 0; i < numOfImp_points; i++) { //counting numOf_y
		if (startOrder[i].loc.y != curr) {
			curr = startOrder[i].loc.y;
			numOf_y++;
		}
		startOrder[i].loc.y = numOf_y; //scaling down
	}
	numOf_y++;
	linkList** by_y = (linkList * *)malloc(sizeof(linkList*) * numOf_y);
	currLoc = 0;
	for (unsigned int i = 0; i < numOf_y; i++) {
		curr = startOrder[currLoc].loc.y;
		by_y[i] = (linkList*)malloc(sizeof(linkList));
		prev = by_y[i];
		prev->prev = NULL;
		prev->mirrorOrderNum = startOrder[currLoc].orderNum;
		startOrder[currLoc].by_yLoc = prev;
		currLoc++;
		while ((currLoc < numOfImp_points) && (startOrder[currLoc].loc.y == curr)) {
			prev->next = (linkList*)malloc(sizeof(linkList));
			currLink = prev->next;
			currLink->mirrorOrderNum = startOrder[currLoc].orderNum;
			currLink->prev = prev;
			startOrder[currLoc].by_yLoc = currLink;
			currLoc++;
			prev = currLink;
		}
		prev->next = NULL;
	}
	//setup end

	qsort(startOrder, numOfImp_points, sizeof(mirror), compareByOrder);
	for (unsigned int i = 0; i < numOfImp_points; i++)
		startOrder[i].vis = 0;
	if (findImportant(startOrder, fisrtMirror)) //if he can already see it
		fprintf(fp, "0");
	else {
		for (unsigned int i = 0; i < numOfImp_points; i++)
			startOrder[i].vis = 0;
		unsigned int ans;
		for (ans = 1; ans < numOfImp_points; ans++) {
			if (startOrder[ans].important) {
				if(startOrder[ans].tilt_house == '/') //toggle it
					startOrder[ans].tilt_house = '\\';
				else
					startOrder[ans].tilt_house = '/';
				if (cheak(startOrder, fisrtMirror))
					break;
				for (unsigned int i = 0; i < numOfImp_points; i++)
					startOrder[i].vis = 0;
				if (startOrder[ans].tilt_house == '/') //togle back
					startOrder[ans].tilt_house = '\\';
				else
					startOrder[ans].tilt_house = '/';
			}
		}
		if (ans == numOfImp_points)
			fprintf(fp, "-1");
		else
			fprintf(fp, "%u", ans);
	}
	fclose(fp);
}

//didn't get: think data sTructures
/*struct line
{
	long start;
	long end;
};
int compareFunc(const void* p1, const void* p2)
{
	line* a = (line*)p1;
	line* b = (line*)p2;
	if (a->start - b->start)
		return a->start - b->start;
	return a->end - b->end;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfInstactions = getNumInFile(&fp);
	line* lineSegments = (line*)malloc(sizeof(line) * numOfInstactions); //being safe with memory
	long currLoc = 0;
	int move;
	unsigned int numOfSegments = 0;
	for (unsigned int i = 0; i < numOfInstactions; i++) {
		move = getNumInFile(&fp);
		if (fgetc(fp) == 'L')
			move *= -1;
		fgetc(fp);
		if ((currLoc > 0) && (move < 0)) {
			lineSegments[numOfSegments].end = currLoc;
			currLoc += move;
			if (currLoc < 0)
				lineSegments[numOfSegments].start = 0;
			else
				lineSegments[numOfSegments].start = currLoc;
			numOfSegments++;
		}
		else if ((currLoc < 0) && (move > 0)) {
			lineSegments[numOfSegments].start = currLoc;
			currLoc += move;
			if (currLoc > 0)
				lineSegments[numOfSegments].end = 0;
			else
				lineSegments[numOfSegments].end = currLoc;
			numOfSegments++;
		}
		else
			currLoc += move;
	}
	fclose(fp);
	qsort(lineSegments, numOfSegments, sizeof(line), compareFunc);
	unsigned int ans = 0;
	bool findingSegment = 0;
	long start;
	long end;
	for (unsigned int i = 0; i < numOfSegments; i++) {
		if (!findingSegment) {
			start = lineSegments[i].start;
			end = lineSegments[i].end;
		}
		else if (lineSegments[i].end > end)
			end = lineSegments[i].end;
		if ((i + 1 < numOfSegments) && (lineSegments[i + 1].start <= end)) //I need to continue
			findingSegment = 1;
		else {
			findingSegment = 0;
			ans += end - start;
		}
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", ans);
	fclose(fp);
	free(lineSegments);
}*/

/*struct cow
{
	unsigned int cowRelation;
	bool if_diff;
};
bool set(unsigned int numOfCows, cow* list, unsigned int from, unsigned int to, bool changeBit)
{
	if (list[from].cowRelation == list[to].cowRelation) {
		if ((list[from].if_diff == list[to].if_diff) == changeBit)
			return 1;
		return 0;
	}
	changeBit = changeBit ^ (list[from].if_diff ^ list[to].if_diff);
	unsigned int changeFrom = list[from].cowRelation;
	unsigned int changeTo = list[to].cowRelation;
	for (unsigned int i = 0; i < numOfCows; i++){
		if (list[i].cowRelation == changeFrom) {
			list[i].cowRelation = changeTo;
			list[i].if_diff = changeBit ^ list[i].if_diff;
		}
	}
	return 0;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNumInFile(&fp);
	unsigned int numOfClaims = getNumInFile(&fp);
	//cow* list = (cow*)calloc(numOfCows, sizeof(cow));
	//unsigned int* numbers = (unsigned int*)calloc(numOfCows, sizeof(unsigned int));
	cow* list = (cow*)malloc(sizeof(cow) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++) {
		list[i].cowRelation = i + 1;
		list[i].if_diff = 0;
	}
	unsigned int ans;
	unsigned int from;
	unsigned int to;
	for (ans = 0; ans < numOfClaims; ans++) {
		from = getNumInFile(&fp) - 1;
		to = getNumInFile(&fp) - 1;
		if (set(numOfCows, list, from, to, fgetc(fp) == 'L'))
			break;
		fgetc(fp); //junk the newLine
	}
	fclose(fp);
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", ans);
	fclose(fp);
}
*/

int main(void)
{
	//q3("truth.in", "truth.out");
	//q2("paint.in", "paint.out");
	q1("mirrors.in", "mirrors.out");
	//system("pause");
	return 0;
}