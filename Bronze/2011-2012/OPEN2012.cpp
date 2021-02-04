#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <stdarg.h>
//#include <assert.h>
char* readStrInFile(FILE** fp, int size)
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
	return str;
}
long long getNumInFile(FILE** fp)
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

/*int compareFunc(const void* p1, const void* p2)
{
	int* a = (int*)p1;
	int* b = (int*)p2;

	return *a - *b;
}
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfCows = getNumInFile(&fp);
	int* cowsOriginal = (int*)malloc(sizeof(int) * numOfCows);
	for (int i = 0; i < numOfCows; i++)
		cowsOriginal[i] = getNumInFile(&fp);
	fclose(fp);
	//qsort(cows, numOfCows, sizeof(int), compareFunc);
	int* cows = (int*)malloc(sizeof(int) * numOfCows);
	memcpy(cows, cowsOriginal, sizeof(int) * numOfCows);
	qsort(cows, numOfCows, sizeof(int), compareFunc);
	int* types = (int*)malloc(sizeof(int) * numOfCows);
	int numOfTypes = 0;
	int old = -1;
	for (int i = 0; i < numOfCows; i++)
	{
		if (cows[i] != old)
		{
			types[numOfTypes] = cows[i];
			numOfTypes++;
		}
	}
	numOfTypes++;

	int curr = 0;
	int highest = 0;
	int currNum;
	for (int j = 0; j < numOfTypes; j++) {
		currNum = -1;
		curr = 0;
		for (int i = 0; i < numOfCows; i++)
			if (cowsOriginal[i] != types[j]) {
				if (cowsOriginal[i] == currNum)
					curr++;
				else {
					currNum = cowsOriginal[i];
					if (highest < curr)
						highest = curr;
					curr = 1;
				}
			}
		if (highest < curr)
			highest = curr;
	}
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", highest);
	fclose(fp);
	
}*/

/*struct point
{
	long x;
	long y;
};
int yCompareFunc(const void* p1, const void* p2)
{
	point* a = (point*)p1;
	point* b = (point*)p2;
	if (a->y != b->y)
		return a->y - b->y;
	return a->x - b->x;
}
int xCompareFunc(const void* p1, const void* p2)
{
	point* a = (point*)p1;
	point* b = (point*)p2;
	if (a->x != b->x)
		return a->x - b->x;
	return a->y - b->y;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfPoints = getNumInFile(&fp);
	point* xAxis = (point*)malloc(sizeof(point) * numOfPoints);
	for (int i = 0; i < numOfPoints; i++) {
		xAxis[i].x = getNumInFile(&fp);
		xAxis[i].y = getNumInFile(&fp);
	}
	fclose(fp);
	point* yAxis = (point*)malloc(sizeof(point) * numOfPoints);
	memcpy(yAxis, xAxis, sizeof(point) * numOfPoints);
	qsort(yAxis, numOfPoints, sizeof(point), yCompareFunc);
	qsort(xAxis, numOfPoints, sizeof(point), xCompareFunc);
	for (int i = 0; i < 3; i++)
	{
		int xhigest = 0;
		int curr = 0;
		int old = -1;
		int k = 0;
		int yHighest = 0;
		int yHighestNum;
		for (k = 0; (old == -1) && (k < numOfPoints); k++) {
			old = xAxis[k].x;
		}
		int xHigestNum;
		k--;
		if (k == numOfPoints)
			break;
		for (int j = 0; j < numOfPoints; j++)
			if (xAxis[j].x == old)
				curr++;
			else if(xAxis[j].x != -1){
				if (curr > xhigest) {
					xhigest = curr;
					xHigestNum = old;
				}
				old = xAxis[j].x;
				curr = 1;
			}
		if (curr > xhigest) {
			xhigest = curr;
			xHigestNum = old;
		}
		curr = 0;
		old = -1;
		for (k = 0; (old == -1) && (k < numOfPoints); k++) {
			old = yAxis[k].y;
		}
		k--;
		for (int j = 0; j < numOfPoints; j++)
			if (yAxis[j].y == old)
				curr++;
			else if (yAxis[j].y != -1) {
				if (curr > yHighest) {
					yHighest = curr;
					yHighestNum = old;
				}
				old = yAxis[j].y;
				curr = 1;
			}
		if (curr > yHighest) {
			yHighest = curr;
			yHighestNum = old;
		}
		if (yHighest == 0)
			break;
		else if (yHighest > xhigest) {
			for (int j = 0; j < numOfPoints; j++)
				if (xAxis[j].y == yHighestNum){
					xAxis[j].x = -1;
					xAxis[j].y = -1;
				}
			for (int j = 0; j < numOfPoints; j++)
				if (yAxis[j].y == yHighestNum) {
					yAxis[j].x = -1;
					yAxis[j].y = -1;
				}
		}
		else {
			for (int j = 0; j < numOfPoints; j++)
				if (xAxis[j].x == xHigestNum) {
					xAxis[j].x = -1;
					xAxis[j].y = -1;
				}
			for (int j = 0; j < numOfPoints; j++)
				if (yAxis[j].x == xHigestNum) {
					yAxis[j].x = -1;
					yAxis[j].y = -1;
				}
		}

	}
	int j;
	for (j = 0; j < numOfPoints; j++)
		if (xAxis[j].y != -1) 
			break;
	bool answer = 0;
	if (j == numOfPoints)
		answer = 1;
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", answer);
	fclose(fp);
}*/

//origina;
/*struct hill
{
	unsigned long max;
	unsigned long min;
	bool min_max;
};
unsigned long aVal;
unsigned long bVal;
int min_maxCompareFunc(const void* p1, const void* p2)
{
	hill* a = (hill*)p1;
	hill* b = (hill*)p2;
	if (a->min_max == 1)
		aVal = a->max;
	else
		aVal = a->min;
	if (b->min_max == 1)
		bVal = b->max;
	else
		bVal = b->min;
	return aVal - bVal;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfFeilds = getNumInFile(&fp);
	unsigned long* hights = (unsigned long*)malloc(sizeof(unsigned long) * numOfFeilds);
	for (unsigned long i = 0; i < numOfFeilds; i++)
		hights[i] = getNumInFile(&fp);
	fclose(fp);
	hill* hills = (hill*)malloc(sizeof(hill) * (numOfFeilds + 10));
	unsigned long currHill = 0;
	hills[currHill].max = hights[0];
	unsigned long currMin = 0;
	bool currDir = 1;
	for (unsigned long i = 1; i < numOfFeilds; i++)
	{
		if (currDir && (hights[i - 1] > hights[i])) {
			currDir = 0;
			hills[currHill].max = hights[i - 1];
		}
		else if(!currDir && (hights[i - 1] < hights[i])){
			currDir = 1;
			if (hights[i - 1] > currMin)
				currMin = hights[i - 1];
			hills[currHill].min = currMin;
			currHill++;
			currMin = hights[i - 1];
		}
	}
	if (currDir) {
		hills[currHill].min = currMin;
		hills[currHill].max = hights[numOfFeilds - 1];
	}
	else {
		if (hights[numOfFeilds - 1] > currMin)
			currMin = hights[numOfFeilds - 1];
		hills[currHill].min = currMin;
	}
	unsigned long numOfHills = currHill + 1;
	memcpy(hills + numOfHills, hills, sizeof(hill) * numOfHills);
	for (int i = 0; i < numOfHills; i++)
	{
		hills[i].min_max = 0;
		hills[i + numOfHills].min_max = 1;
	}
	qsort(hills, numOfHills * 2, sizeof(hill), min_maxCompareFunc);
	unsigned long currHigh = 0;
	unsigned long curr = 0;
	unsigned long numToGo = numOfHills * 2;
	for (unsigned long i = 0; i < numToGo; i++)
	{

	}
	//unsigned long num;
	*for (unsigned long i = 0; i < numOfHills; i++)
	{
		num = hills[i].min;
		for (unsigned long j = 0; j < numOfHills; j++)
			if ((num >= hills[j].min) && (num < hills[j].max))
				curr++;
		if (curr > currHigh)
			currHigh = curr;
		curr = 0;
	}*
	free(hills);
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", currHigh);
	fclose(fp);
}*/
//redo
/*struct info
{
	unsigned long hight;
	unsigned int place;
};
int compareFunc(const void* p1, const void* p2)
{
	info* a = (info*)p1;
	info* b = (info*)p2;
	return a->hight - b->hight;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfFeilds = getNumInFile(&fp);
	info* byHights = (info*)malloc(sizeof(info) * numOfFeilds);
	for (unsigned long i = 0; i < numOfFeilds; i++) {
		byHights[i].hight = getNumInFile(&fp);
		byHights[i].place = i;
	}
	fclose(fp);
	bool* water = (bool*)calloc(numOfFeilds, sizeof(bool));
	qsort(byHights, numOfFeilds, sizeof(info), compareFunc);
	unsigned long curr = 1;
	unsigned long greatest = 1;
	for (unsigned int i = 0; i < numOfFeilds; i++)
	{
		water[byHights[i].place] = 1;
		if (((byHights[i].place != 0) &&
			(water[byHights[i].place - 1] == 0)) &&
			((byHights[i].place != numOfFeilds - 1) &&
			(water[byHights[i].place + 1] == 0))) 
			curr++;
		else if (((byHights[i].place != 0) &&
			(water[byHights[i].place - 1] == 1)) &&
			((byHights[i].place != numOfFeilds - 1) &&
			(water[byHights[i].place + 1] == 1)))
			curr--;
		if ((greatest < curr) && ((i == numOfFeilds - 1) || (byHights[i].hight != byHights[i + 1].hight))) 
			greatest = curr;
	}
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%lu", greatest);
	fclose(fp);
}*/

struct queue
{
	int* grid;
	queue* next;
};
queue* enque(queue* start, int* grid)
{
	queue* current;
	queue* newEnd = (queue*)malloc(sizeof(queue));
	newEnd->next = NULL;
	newEnd->grid = grid;
	if (start != NULL)
	{
		for (current = start;
			current->next != NULL;
			current = current->next);
		current->next = newEnd;
	}
	else
		start = newEnd;
	return start;
}
int* deque(queue * *start)
{
	int* grid;
	grid = (*start)->grid;
	queue* old = *start;
	(*start) = (*start)->next;
	free(old);
	return grid;
}
int canMoveUp(int* grid, int moveNum)
{
	int returnVal = 2;
	for (int i = 0; i < 81; i++)
	{
		if (grid[i] == moveNum) {
			returnVal = 1;
			if (i < 9)
				grid[i] = 0;
			else if ((grid[i - 9] == 0) || (grid[i - 9] == moveNum)) {
				grid[i] = 0;
				grid[i - 9] = moveNum;
			}
			else 
				return 0;
		}
	}
	return returnVal;
}
void dequeAll()
{

}
bool findWin(int* grid)
{
	queue* start = (queue*)malloc(sizeof(queue));
	start->next = NULL;
	start->grid = grid;
	int* currGrid;
	int state = 0;
	int* holder;
	int* tryOut = (int*)malloc(sizeof(int) * 81);
	int dontGo = 0;
	for (int j = 0; j < 2; j++) {
		while (start != NULL)
		{
			currGrid = deque(&start);
			memcpy(tryOut, currGrid, sizeof(int) * 81);
			for (int i = 1; i <= 3; i++) {
				if (i == dontGo)
					continue;
				while ((state = canMoveUp(tryOut, i)) == 1)
				{
					holder = (int*)malloc(sizeof(int) * 81);
					memcpy(holder, tryOut, sizeof(int) * 81);
					start = enque(start, tryOut);
					tryOut = holder;
				}
				if (state == 2) {
					dequeAll();
					break;
				}
				else
					memcpy(tryOut, currGrid, sizeof(int) * 81);

				while ((state = canMoveUp(tryOut, i)) == 1)
				{
					holder = (int*)malloc(sizeof(int) * 81);
					memcpy(holder, tryOut, sizeof(int) * 81);
					start = enque(start, tryOut);
					tryOut = holder;
				}
				if (state == 2) {
					dequeAll();
					break;
				}
				else
					memcpy(tryOut, currGrid, sizeof(int) * 81);

				while ((state = canMoveUp(tryOut, i)) == 1)
				{
					holder = (int*)malloc(sizeof(int) * 81);
					memcpy(holder, tryOut, sizeof(int) * 81);
					start = enque(start, tryOut);
					tryOut = holder;
				}
				if (state == 2) {
					dequeAll();
					break;
				}
				else
					memcpy(tryOut, currGrid, sizeof(int) * 81);

				while ((state = canMoveUp(tryOut, i)) == 1)
				{
					holder = (int*)malloc(sizeof(int) * 81);
					memcpy(holder, tryOut, sizeof(int) * 81);
					start = enque(start, tryOut);
					tryOut = holder;
				}
				if (state == 2) {
					dequeAll();
					break;
				}
				else
					memcpy(tryOut, currGrid, sizeof(int) * 81);

			}
			free(currGrid);
		}
		if (state != 2)
			return 0;
		start = (queue*)malloc(sizeof(queue));
		start->next = NULL;
		start->grid = tryOut;
	}
	currGrid = deque(&start);
	free(currGrid);
	return 1;
}
void q4(const char* fpIn, const char* fpOut)
{
	int* grid = (int*)calloc(81, sizeof(int));
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int fig1Size = getNumInFile(&fp);
	for (int i = 0; i < fig1Size; i++)
		grid[(getNumInFile(&fp) * 9) + getNumInFile(&fp)] = 1;
	int fig2Size = getNumInFile(&fp);
	for (int i = 0; i < fig2Size; i++)
		grid[(getNumInFile(&fp) * 9) + getNumInFile(&fp)] = 2;
	int fig3Size = getNumInFile(&fp);
	for (int i = 0; i < fig3Size; i++)
		grid[(getNumInFile(&fp) * 9) + getNumInFile(&fp)] = 3;
	*int highestNum;
	for (highestNum = 0; highestNum < 81; highestNum++) {
		if (grid[highestNum] != 0)
			break;
	}
	int moveNum = grid[highestNum];*
	
	fclose(fp);

	fp = NULL;
	fopen_s(&fp, fpOut, "w");

	fclose(fp);
}

int main(void)
{
	//q1("./cowrow.in", "./cowrow.out");
	//q2("./3lines.in", "./3lines.out");
	//q3("./islands.in", "./islands.out");
	//q4("./unlock.in", "./unlock.out");

	//system("pause");
	return 0;
}