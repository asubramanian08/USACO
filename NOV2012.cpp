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

/*void q1(const char* fpIn, const char* fpOut) //dir = 0 mean '(', dir = 1 maens ')'
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	//fopen_s(&fp,fpIn, "r");
	char currChar = fgetc(fp);
	bool dir = 0;
	if (currChar == '(')
		dir = 1;

	unsigned long left = 0, right = 0, subtract = 0;
	while (currChar != '\n')
	{
		if ((currChar == '(') && (dir == 0)) {
			left++;
			subtract += right;
		}
		else if ((currChar == ')') && (dir == 1))
			right++;

		if (currChar == '(')
			dir = 0;
		else
			dir = 1;
		currChar = fgetc(fp);
	}
	fclose(fp);
	fp = NULL;
	fp = fopen(fpOut, "w");
	//fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%lu", (left * right) - subtract);
	fclose(fp);
}*/

//this is original
/*bool* checks;
bool check(char* str, unsigned int length)
{
	int toClose = 0;
	for (unsigned int i = 0; i < length; i++)
		if (str[i] == ')') {
			toClose--;
			if (toClose == -1)
				break;
		}
		else if (str[i] == '(')
			toClose++;
	if (toClose == 0)
		return 1;
	return 0;
}
void recursaveStart(char* str, unsigned int length, unsigned int curr)
{
	while (str[curr] == 'a')
		curr++;
	if (str[curr] == ')')  //base case
		return;
	
	if (str[length - 1] == '(') { //base case
		str[length - 1] = ')';
		if (check(str, length))
			checks[length - 1] = 1;
		str[length - 1] = '(';
		return;
	}
	str[curr] = 'a';
	for (unsigned int i = curr + 1; i < length; i++)
	{
		if (str[i] == ')') {
			str[i] = 'a';
			recursaveStart(str, length, curr + 1);
			str[i] = ')';
		}
	}
	str[curr] = '(';
}
void q2(const char* fpIn, const char* fpOut)
{
	char str[100000];
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	//fopen_s(&fp,fpIn, "r");
	unsigned int i;
	char ch = fgetc(fp);
	unsigned int curr = 0;
	for (i = 0; ch != '\n'; i++) {
		str[i] = ch;
		if (ch == '(')
			curr++;
		else
			curr--;
		ch = fgetc(fp);
	}
	fclose(fp);
	str[i] = 0; //null
	unsigned int length = i;
	checks = (bool*)malloc(sizeof(bool) * length);
	memset(checks, 0, sizeof(bool) * length);
	unsigned int total  =0;
	*if ((curr != 2) && (curr != -2))
		total = 0;
	else if (curr == 2) {
		for (unsigned int i = 0; i < length; i++)
			if (str[i] == '(') {
				str[i] = ')';
				if (check(str, length))
					total++;
				str[i] = '(';
			}
	}
	else {
		for (unsigned int i = 0; i < length; i++)
			if (str[i] == ')') {
				str[i] = '(';
				if (check(str, length))
					total++;
				str[i] = ')';
			}
	}*

	if ((curr == 2) || (curr == -2))
		recursaveStart(str, length, 0);
	for (int i = 0; i < length; i++)
		total += checks[i];
	fp = NULL;
	fp = fopen(fpOut, "w");
	//fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%lu", total);
	fclose(fp);
}*/

//redo (with way to do it)
void q2(const char* fpIn, const char* fpOut)
{
	char str[100001];
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	//fopen_s(&fp,fpIn, "r");
	unsigned int answer = 0;
	char ch = fgetc(fp);
	unsigned int length;
	int currVal = 0;
	for (length = 0; ch != '\n'; length++) {
		str[length] = ch;
		if (ch == ')')
			currVal--;
		else
			currVal++;
		ch = fgetc(fp);
	}
	fclose(fp);
	if (currVal == 2) { //too many opens
		currVal = 0;
		for (unsigned int i = 0; i < length; i++) {
			if (str[i] == ')')
				currVal--;
			else {
				currVal++;
				answer++;
			}
			if (currVal <= 1)
				answer = 0;
			if (currVal < 0) 
				break;
		}
	}
	else if (currVal == -2) { //too many closes
		currVal = 0;
		for (unsigned int i = 0; i < length; i++){
			if (str[i] == ')')
				currVal--;
			else {
				currVal++;
				answer++;
			}
			if (currVal < 0)
				break;
		}
		answer++;
	}

	fp = NULL;
	fp = fopen(fpOut, "w");
	//fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%lu", answer);
	fclose(fp);
}

/*unsigned int end(char* grid, int dimentions, int rowNum, int colNum, unsigned int currNum)
{
	if (currNum == 0)
		return 1;
	char* newGrid = (char*)malloc(sizeof(char) * dimentions * dimentions);
	if ((colNum + 1 < dimentions) && (grid[rowNum * dimentions + colNum + 1] == ')')){
		memcpy(newGrid, grid, sizeof(char) * dimentions * dimentions);
		newGrid[rowNum * dimentions + colNum + 1] = 0;
		if (end(newGrid, dimentions, rowNum, colNum + 1, currNum - 1)) {
			free(newGrid);
			return 1;
		}
	}
	if ((rowNum + 1 < dimentions) && (grid[(rowNum + 1) * dimentions + colNum] == ')')){
		memcpy(newGrid, grid, sizeof(char) * dimentions * dimentions);
		newGrid[(rowNum + 1) * dimentions + colNum] = 0;
		if (end(newGrid, dimentions, rowNum + 1, colNum, currNum - 1)) {
			free(newGrid);
			return 1;
		}
	}
	if ((rowNum - 1 >= 0) && (grid[(rowNum - 1) * dimentions + colNum] == ')')){
		memcpy(newGrid, grid, sizeof(char) * dimentions * dimentions);
		newGrid[(rowNum - 1) * dimentions + colNum] = 0;
		if(end(newGrid, dimentions, rowNum - 1, colNum, currNum - 1)) {
			free(newGrid);
			return 1;
		}
	}
	if ((colNum - 1 >= 0) && (grid[rowNum * dimentions + colNum - 1] == ')')){
		memcpy(newGrid, grid, sizeof(char) * dimentions * dimentions);
		newGrid[rowNum * dimentions + colNum - 1] = 0;
		if(end(newGrid, dimentions, rowNum, colNum - 1, currNum - 1)) {
			free(newGrid);
			return 1;
		}
	}
	free(newGrid);
	return 0;
}
unsigned int start(char* grid, int dimentions, int rowNum, int colNum, unsigned int currNum)
{
	char* newGrid = (char*)malloc(sizeof(char) * dimentions * dimentions);
	unsigned int highest = 0;
	unsigned int trial;
	if ((colNum + 1 < dimentions) && (grid[rowNum * dimentions + colNum + 1] != 0))
	{
		memcpy(newGrid, grid, sizeof(char) * dimentions * dimentions);
		newGrid[rowNum * dimentions + colNum + 1] = 0;
		if (grid[rowNum * dimentions + colNum + 1] == '(') 
			trial = start(newGrid, dimentions, rowNum, colNum + 1, currNum + 1);
		else
			trial = end(newGrid, dimentions, rowNum, colNum + 1, currNum - 1) * currNum;
		if (trial > highest)
			highest = trial;
	}
	if ((rowNum + 1 < dimentions) && (grid[(rowNum + 1) * dimentions + colNum] != 0))
	{
		memcpy(newGrid, grid, sizeof(char) * dimentions * dimentions);
		newGrid[(rowNum + 1) * dimentions + colNum] = 0;
		if (grid[(rowNum + 1) * dimentions + colNum] == '(')
			trial = start(newGrid, dimentions, rowNum + 1, colNum, currNum + 1);
		else
			trial = end(newGrid, dimentions, rowNum + 1, colNum, currNum - 1) * currNum;
		if (trial > highest)
			highest = trial;
	}
	if ((rowNum - 1 >= 0) && (grid[(rowNum - 1) * dimentions + colNum] != 0))
	{
		memcpy(newGrid, grid, sizeof(char) * dimentions * dimentions);
		newGrid[(rowNum - 1) * dimentions + colNum] = 0;
		if (grid[(rowNum - 1) * dimentions + colNum] == '(')
			trial = start(newGrid, dimentions, rowNum - 1, colNum, currNum + 1);
		else
			trial = end(newGrid, dimentions, rowNum - 1, colNum, currNum - 1) * currNum;
		if (trial > highest)
			highest = trial;
	}
	if ((colNum - 1 >= 0) && (grid[rowNum * dimentions + colNum - 1] != 0))
	{
		memcpy(newGrid, grid, sizeof(char) * dimentions * dimentions);
		newGrid[rowNum * dimentions + colNum - 1] = 0;
		if (grid[rowNum * dimentions + colNum - 1] == '(')
			trial = start(newGrid, dimentions, rowNum, colNum - 1, currNum + 1);
		else
			trial = end(newGrid, dimentions, rowNum, colNum - 1, currNum - 1) * currNum;
		if (trial > highest)
			highest = trial;
	}
	free(newGrid);
	return highest;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fp = fopen(fpIn, "r");
	//fopen_s(&fp,fpIn, "r");
	int dimentions = getNumInFile(&fp);
	char* grid = (char*)malloc(sizeof(char) * dimentions * dimentions);
	int j;
	for (int i = 0; i < dimentions; i++){
		for (j = 0; j < dimentions; j++)
			grid[i * dimentions + j] = fgetc(fp);
		fgetc(fp); // it is a '\n'
	}
	fclose(fp);
	unsigned long total;
	if (grid[0] == '(') {
		grid[0] = 0;
		total = start(grid, dimentions, 0, 0, 1);
	}
	else
		total = 0;

	fp = NULL;
	fp = fopen(fpOut, "w");
	//fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%lu", 2 * total);
	fclose(fp);
}*/

int main(void)
{
	//q1("./cowfind.in", "./cowfind.out");
	q2("./typo.in", "./typo.out");
	//q3("./hshoe.in", "./hshoe.out");
	//system("pause");
	return 0;
}