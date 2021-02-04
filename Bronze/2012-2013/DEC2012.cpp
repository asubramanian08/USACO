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

/*struct move
{
	unsigned int num;
	int dir;
};
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	//fopen_s(&fp, fpIn, "r");
	unsigned int b_instra = getNumInFile(&fp);
	move* bMoves = (move*)malloc(sizeof(move) * b_instra);
	unsigned int e_instra = getNumInFile(&fp);
	move* eMoves = (move*)malloc(sizeof(move) * e_instra);
	for (long i = 0; i < b_instra; i++) {
		bMoves[i].num = getNumInFile(&fp);
		if (fgetc(fp) == 'L')
			bMoves[i].dir = -1;
		else
			bMoves[i].dir = 1;
		fgetc(fp); //the new line char
	}
	for (long i = 0; i < e_instra; i++) {
		eMoves[i].num = getNumInFile(&fp);
		if (fgetc(fp) == 'L')
			eMoves[i].dir = -1;
		else
			eMoves[i].dir = 1;
		fgetc(fp); //the new line char
	}
	fclose(fp);
	unsigned int ans = 0;
	bool prev = 1;
	int bLoc = 0;
	int eLoc = 0;
	unsigned int bNum = 0;
	unsigned int eNum = 0;
	bool bGo = 1;
	bool eGo = 1;
	while (bGo || eGo)
	{
		if (bGo) {
			bLoc += bMoves[bNum].dir;
			bMoves[bNum].num--;
			if (bMoves[bNum].num == 0) {
				bNum++;
				if (bNum == b_instra)
					bGo = 0;
			}
		}
		if (eGo) {
			eLoc += eMoves[eNum].dir;
			eMoves[eNum].num--;
			if (eMoves[eNum].num == 0) {
				eNum++;
				if (eNum == e_instra)
					eGo = 0;
			}
		}
		if (!prev && (eLoc == bLoc)) {
			ans++;
			prev = 1;
		}
		else if(eLoc != bLoc)
			prev = 0;
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	//fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}*/

/*struct name
{
	char* cowName;
	unsigned int orderNum;
};
struct high_low
{
	unsigned int high;
	unsigned int low;
};
int cmpLowFirst(const void* p1, const void* p2) 
{
	return *((char*)p2) - *((char*)p1);
}
int cmpHighFirst(const void* p1, const void* p2)
{
	return *((char*)p1) - *((char*)p2);
}
int cmpStrings(const void* p1, const void* p2)
{
	char* str1 = ((name*)p1)->cowName;
	char* str2 = ((name*)p2)->cowName;
	while ((*str1 != 0) && (*str2 != 0))
	{
		if (*str1 != *str2)
			break;
		str1++;
		str2++;
	}
	if (*str1 == 0)
		return -1;
	else if (*str2 == 0)
		return 1;
	return *str1 - *str2;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	//fopen_s(&fp, fpIn, "r");
	unsigned int numCows = getNumInFile(&fp);
	name* highFirst = (name*)malloc(sizeof(name) * numCows);
	name* lowFirst = (name*)malloc(sizeof(name) * numCows);
	int size;
	for (unsigned int i = 0; i < numCows; i++) {
		highFirst[i].orderNum = i;
		lowFirst[i].orderNum = i;
		highFirst[i].cowName = readStrInFile(&fp, 20, &size);
		lowFirst[i].cowName = (char*)malloc(sizeof(char) * size);
		strcpy(lowFirst[i].cowName, highFirst[i].cowName);
	}
	fclose(fp);
	for (unsigned int i = 0; i < numCows; i++) {
		qsort(lowFirst[i].cowName, strlen(lowFirst[i].cowName), sizeof(char), cmpLowFirst);
		qsort(highFirst[i].cowName, strlen(highFirst[i].cowName), sizeof(char), cmpHighFirst);
	}
	qsort(lowFirst, numCows, sizeof(name), cmpStrings);
	qsort(highFirst, numCows, sizeof(name), cmpStrings);
	high_low* ans = (high_low*)malloc(sizeof(high_low) * numCows);
	unsigned int highLoc = 0;
	unsigned int lowLoc = 0;
	for (highLoc = 0; highLoc < numCows; highLoc++) { //finding highs
		while (strcmp(highFirst[highLoc].cowName, lowFirst[lowLoc].cowName) > 0)
			lowLoc++;
		ans[highFirst[highLoc].orderNum].high = lowLoc + 1;
	}
	for (highLoc = 0, lowLoc = 0; lowLoc < numCows; lowLoc++) { //finding lows
		while ((highLoc < numCows) && (strcmp(highFirst[highLoc].cowName, lowFirst[lowLoc].cowName) <= 0))
			highLoc++;
		ans[lowFirst[lowLoc].orderNum].low = highLoc;
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	//fopen_s(&fp, fpOut, "w");
	for (unsigned int i = 0; i < numCows; i++)
		fprintf(fp, "%d %d\n", ans[i].high, ans[i].low);
	fclose(fp);
}*/

//after dad looking at solution
struct point
{
	unsigned int x;
	unsigned int y;
};
struct readFence
{
	point top_right;
	point bottem_left;
};
readFence* readIn(FILE* fp, point** cowsList, unsigned int* cows, unsigned int* fences, unsigned int *highest_x, unsigned int *highest_y)
{
	unsigned int i; //counting var
	*highest_x = 0;
	*highest_y = 0;
	*fences = getNumInFile(&fp);
	readFence* currFences = (readFence*)malloc(sizeof(readFence) * (*fences));
	*cows = getNumInFile(&fp);
	*cowsList = (point*)malloc(sizeof(point) * (*cows));
	unsigned int dummy_var; //gets thrown around for storage
	//fills in fence structure
	for (i = 0; i < *fences; i++) {
		currFences[i].top_right.x = getNumInFile(&fp);
		currFences[i].top_right.y = getNumInFile(&fp);
		currFences[i].bottem_left.x = getNumInFile(&fp);
		currFences[i].bottem_left.y = getNumInFile(&fp);
		//the fence is verticle and they need to me switched -> change the .y's (.x's are the same)
		if (currFences[i].bottem_left.y > currFences[i].top_right.y) {
			dummy_var = currFences[i].bottem_left.y;
			currFences[i].bottem_left.y = currFences[i].top_right.y;
			currFences[i].top_right.y = dummy_var;
		}
		//the fence is horizantal and they need to me switched -> change the .x's (.y's are the same)
		else if (currFences[i].bottem_left.x > currFences[i].top_right.x) {
			dummy_var = currFences[i].bottem_left.x;
			currFences[i].bottem_left.x = currFences[i].top_right.x;
			currFences[i].top_right.x = dummy_var;
		}
		//help find highest x and y
		if (currFences[i].top_right.y > *highest_y)
			*highest_y = currFences[i].bottem_left.y;
		if (currFences[i].top_right.x > *highest_x)
			*highest_x = currFences[i].bottem_left.x;
	}
	//fills in cows
	for (i = 0; i < *cows; i++) {
		(*cowsList + i)->x = getNumInFile(&fp);
		if ((*cowsList + i)->x > * highest_x) //help find highest
			* highest_x = (*cowsList + i)->x;
		(*cowsList + i)->y = getNumInFile(&fp);
		if ((*cowsList + i)->y > * highest_y)//help find highest
			* highest_y = (*cowsList + i)->y;
	}
	return currFences;
}
unsigned short* compression(unsigned int highest_y, unsigned int highest_x, readFence* currFences, point* cowsList, unsigned int numOfFences, unsigned int numOfCows, unsigned int* endGridRows, unsigned int* endGridCols)
{
	unsigned int i;
	unsigned int* y_scale = (unsigned int*)calloc(highest_y + 1, sizeof(unsigned int));
	unsigned int* x_scale = (unsigned int*)calloc(highest_x + 1, sizeof(unsigned int));
	//fill in the places locations that have important stuff there on the scales
	for (i = 0; i < numOfFences; i++) {
		x_scale[currFences[i].top_right.x] = true;
		y_scale[currFences[i].top_right.y] = true;
		x_scale[currFences[i].bottem_left.x] = true;
		y_scale[currFences[i].bottem_left.y] = true;
	}
	for (i = 0; i < numOfCows; i++) {
		x_scale[cowsList[i].x] = true;
		y_scale[cowsList[i].y] = true;
	}
	//write what certian points convert to
	*endGridCols = 1;
	for (i = 0; i <= highest_x; i++)
		if (x_scale[i]) {
			x_scale[i] = *endGridCols;
			*endGridCols += 2;
		}
	*endGridRows = 1;
	for (i = 0; i <= highest_y; i++)
		if (y_scale[i]) {
			y_scale[i] = *endGridRows;
			*endGridRows += 2;
		}
	unsigned short* grid = (unsigned short*)calloc((*endGridCols) * (*endGridRows), sizeof(unsigned short));
	//convert everything
	for (i = 0; i < numOfFences; i++)
		for (unsigned int j = x_scale[currFences[i].bottem_left.x]; j <= x_scale[currFences[i].top_right.x]; j++)
			for (unsigned int k = y_scale[currFences[i].bottem_left.y]; k <= y_scale[currFences[i].top_right.y]; k++)
				grid[k * (*endGridCols) + j] = 1;
	for (i = 0; i < numOfCows; i++) {
		cowsList[i].x = x_scale[cowsList[i].x];
		cowsList[i].y = y_scale[cowsList[i].y];
		grid[cowsList[i].y * (*endGridCols) + cowsList[i].x] = i + 2;
	}
	//free the HUGE memory spaces(the scales + memStore places)
	free(x_scale);
	free(y_scale);
	free(currFences);
	return grid;
}
unsigned int floodFill(unsigned short* grid, unsigned int rows, unsigned int cols, point start, bool* cowsSeen) 
{
	unsigned int numOfCowsSeen = 0;
	if (grid[start.y * cols + start.x] == 1)
		return 0;
	else if (grid[start.y * cols + start.x] >= 2) {
		numOfCowsSeen++;
		cowsSeen[grid[start.y * cols + start.x] - 2] = true;
	}
	grid[start.y * cols + start.x] = 1;
	if (start.x + 1 < cols) {
		start.x++;
		numOfCowsSeen += floodFill(grid, rows, cols, start, cowsSeen);
		start.x--;
	}
	if (start.x >= 1) {
		start.x--;
		numOfCowsSeen += floodFill(grid, rows, cols, start, cowsSeen);
		start.x++;
	}
	if (start.y + 1 < rows) {
		start.y++;
		numOfCowsSeen += floodFill(grid, rows, cols, start, cowsSeen);
		start.y--;
	}
	if (start.y >= 1) {
		start.y--;
		numOfCowsSeen += floodFill(grid, rows, cols, start, cowsSeen);
		start.y++;
	}
	return numOfCowsSeen;
}
unsigned int maxCowsInCommunity(unsigned short* grid, unsigned int rows, unsigned int cols, point* cowList, unsigned int numOfCows)
{
	bool* cowCheaked = (bool*)calloc(numOfCows, sizeof(bool));
	unsigned int max = 0;
	unsigned int curr;
	unsigned int startLoc = 0;
	unsigned int numOfCowsCheaked = 0;
	while (numOfCowsCheaked < numOfCows) {
		for (startLoc = 0; (startLoc < numOfCows) && (cowCheaked[startLoc]); startLoc++);
		curr = floodFill(grid, rows, cols, cowList[startLoc], cowCheaked);
		numOfCowsCheaked += curr;
		if (curr > max)
			max = curr;
	}
	free(grid);
	free(cowList);
	free(cowCheaked);
	return max;
}
void q3(const char* fpIn, const char* fpOut)
{
	point* cowList;
	unsigned int numOfCows = 0, numOfFences = 0, highest_x = 0, highest_y = 0, gridRows = 0, gridCols = 0;
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	//fopen_s(&fp, fpIn, "r");
	readFence* currFences = readIn(fp, &cowList, &numOfCows, &numOfFences, &highest_x, &highest_y);//read it in & compress
	fclose(fp);
	unsigned short* grid = compression(highest_y, highest_x, currFences, cowList, numOfFences, numOfCows, &gridRows, &gridCols); //get compressed grid
	unsigned int answer = maxCowsInCommunity(grid, gridRows, gridCols, cowList, numOfCows);
	fp = NULL;
	fp = fopen(fpOut, "w");
	//fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%u", answer);
	fclose(fp);
}
int main(void)
{
	//q1("greetings.in", "./greetings.out");
	//q2("scramble.in", "scramble.out");
	q3("crazy.in", "crazy.out");
}