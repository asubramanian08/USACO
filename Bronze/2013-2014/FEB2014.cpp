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
long long getNumInFile(FILE** fp)
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

//it couldn't be forever
bool maze[1000][1000];
int numOfRows;
int numOfCols;
int followThrough(int currRow, int currCol, int dirRow, int dirCol)
{
	int hitCount = 0;
	int temp;
	while (((currRow < numOfRows) && (currRow >= 0)) &&
		((currCol < numOfCols) && (currCol >= 0))) {
		hitCount++;
		if (maze[currRow][currCol]) {
			temp = dirCol;
			dirCol = dirRow;
			dirRow = temp;
		}
		else {
			temp = dirCol;
			dirCol = -dirRow;
			dirRow = -temp;
		}
		currRow -= dirRow;
		currCol += dirCol;
	}
	return hitCount;
}
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	numOfRows = getNum;
	numOfCols = getNum;
	for (int i = 0; i < numOfRows; i++) {
		for (int j = 0; j < numOfCols; j++)
			maze[i][j] = (fgetc(fp) == '/');
		fgetc(fp); //newLine
	}
	fclose(fp);
	int biggest = 0;
	int curr = 0;
	for (int i = 0; i < numOfRows; i++) {
		curr = followThrough(i, 0, 0, 1);
		if (curr > biggest)
			biggest = curr;
		curr = followThrough(i, numOfCols - 1, 0, -1);
		if (curr > biggest)
			biggest = curr;
	}
	for (int i = 0; i < numOfCols; i++) {
		curr = followThrough(0, i, -1, 0);
		if (curr > biggest)
			biggest = curr;
		curr = followThrough(numOfRows - 1, i, 1, 0);
		if (curr > biggest)
			biggest = curr;
	}
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", biggest);
	fclose(fp);
}

//too much memory / memory overload
/*struct genericStr
{
	char* str;
	bool is_par;
	unsigned int refNum;
};
struct partial
{
	unsigned int compNum;
	unsigned int refNum;
};
int compareFunc(const void* p1, const void* p2)
{
	int wdComp = strcmp(((const genericStr*)p1)->str, ((const genericStr*)p2)->str);
	if (wdComp)
		return wdComp;
	return ((genericStr*)p2)->is_par - ((genericStr*)p1)->is_par;
}
bool isPart(char* subStr, char* str)
{
	while (*subStr == *str) {
		subStr++; str++;
		if (*subStr == '\0')
			return false;
	}
	return true;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOf_wd = getNum;
	unsigned int numOf_par = getNum;
	unsigned int numOf_gen = numOf_par + numOf_wd;
	genericStr* dict = (genericStr*)malloc(sizeof(genericStr) * (numOf_gen + 1));
	partial* par_input = (partial*)malloc(sizeof(partial) * numOf_par);
	int temp;
	for (unsigned int i = 0; i < numOf_wd; i++) {
		dict[i].is_par = false;
		dict[i].refNum = i + 1;
		dict[i].str = readStrInFile(&fp, 1000000, &temp);
	}
	for (unsigned int i = 0; i < numOf_par; i++) {
		dict[numOf_wd +  i].is_par = true;
		dict[numOf_wd + i].refNum = i;
		par_input[i].compNum = getNum;
		dict[numOf_wd + i].str = readStrInFile(&fp, 10000, &temp);
	}
	fclose(fp);
	dict[numOf_gen].is_par = true;
	dict[numOf_gen].str = (char*)calloc(1, sizeof(char));
	qsort(dict, numOf_gen, sizeof(genericStr), compareFunc);
	for (unsigned int i = 0; i < numOf_gen; i++) {
		if (dict[i].is_par)
			par_input[dict[i].refNum].refNum = i;
	}
	fp = fopen(fpOut, "w");
	for (unsigned int i = 0; i < numOf_par; i++) {
		unsigned int j = par_input[i].refNum;
		unsigned int passed = 0; 
		while (passed < par_input[i].compNum) {
			j++;
			if (isPart(dict[par_input[i].refNum].str, dict[j].str))
				break;
			if (!dict[j].is_par)
				passed++;
		}
		if (passed != par_input[i].compNum)
			fprintf(fp, "-1\n");
		else
			fprintf(fp, "%d\n", dict[j].refNum);
	}
	fclose(fp);
}*/

//using a tree (also too much mem.)
/*struct tree
{
	unsigned int endNum = 0;
	tree* nextLetter[26] = { NULL };
	unsigned int numOfPar = 0;
};
inline tree* formTree(FILE** fp, unsigned int numOfWd)
{
	char ch; tree* wdTree = (tree*)calloc(1, sizeof(tree)); tree* currStr;
	for (unsigned int i = 0; i < numOfWd; i++) {
		currStr = wdTree;
		while ((ch = fgetc(*fp)) != '\n') {
			currStr->numOfPar++;
			if (!currStr->nextLetter[ch - 'a'])
				currStr->nextLetter[ch - 'a'] = (tree*)calloc(1, sizeof(tree));
			currStr = currStr->nextLetter[ch - 'a'];
		}
		currStr->endNum = i + 1;
		currStr->numOfPar++;
	}
	return wdTree;
}
inline void findPartials(FILE* fp, FILE* fout, unsigned int numOfPar, tree* wdTree)
{
	char ch; tree* currStr; unsigned int depth, currDepth, currLetter; bool stillWorks;
	for (unsigned int i = 0; i < numOfPar; i++) {
		currStr = wdTree; depth = getNum; stillWorks = true;
		while (((ch = fgetc(fp)) != '\n') && (stillWorks = (currStr->nextLetter[ch - 'a'] != NULL))) //get the the incomplete part
			currStr = currStr->nextLetter[ch - 'a'];

		currDepth = 0;
		while ((currDepth < depth) && stillWorks) { //go to the nth version of it
			currLetter = 0; currDepth += currStr->endNum > 0;
			while ((currDepth < depth) && (currLetter < 26)) {
				if (currStr->nextLetter[currLetter])
					currDepth += currStr->nextLetter[currLetter]->numOfPar;
				currLetter++;
			}
			if ((stillWorks = !(currDepth < depth)) && (currLetter != 0)) {
				currStr = currStr->nextLetter[currLetter - 1];
				currDepth -= currStr->numOfPar;
			}
		}

		if (stillWorks)
			fprintf(fout, "%d\n", currStr->endNum);
		else
			fprintf(fout, "-1\n");
	}
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfWd = getNum;
	unsigned int numOfPar = getNum;
	FILE* fout = fopen(fpOut, "w");
	findPartials(fp, fout, numOfPar, formTree(&fp, numOfWd));
	fclose(fout);
	fclose(fp);
}*/

//their way
struct word
{
	char* wd;
	unsigned int dictNum;
};
int compareFunc(const void* p1, const void* p2)
{
	return strcmp(((word*)p1)->wd, ((word*)p2)->wd);
}
unsigned int binarySearch(word* dict, unsigned int numOfWd, char* str)
{
	int l = 0, r = numOfWd - 1;
	while (l <= r) {
		int mid = (r - l) / 2 + l;
		if (strcmp(dict[mid].wd, str) < 0)
			l = mid + 1;
		else
			r = mid - 1;
	}
	return l;
}
bool isPart(char* subStr, char* str)
{
	while (*subStr == *str) {
		subStr++; str++;
		if (*subStr == '\0')
			return true;
	}
	return false;
}
void q2(const char* fpIn, const char* fpOut)
{
	int junk;
	FILE* fp = fopen(fpIn, "r");
	unsigned int numOfWd = getNum;
	unsigned int numOfPar = getNum;
	word* dict = (word*)malloc(sizeof(word) * numOfWd);
	for (unsigned int i = 0; i < numOfWd; i++) {
		dict[i].wd = readStrInFile(&fp, 1000000, &junk);
		dict[i].dictNum = i + 1;
	}
	qsort(dict, numOfWd, sizeof(word), compareFunc);

	int* ans = (int*)malloc(sizeof(int) * numOfPar);
	unsigned int dictNum; char* parWord; unsigned int startNum;
	for (unsigned int i = 0; i < numOfPar; i++) {
		dictNum = getNum - 1;
		startNum = binarySearch(dict, numOfWd, parWord = readStrInFile(&fp, 1000, &junk));
		if ((startNum + dictNum < numOfWd) && (isPart(parWord, dict[startNum + dictNum].wd)))
			ans[i] = dict[startNum + dictNum].dictNum;
		else
			ans[i] = -1;
	}
	fclose(fp);
	fp = fopen(fpOut, "w");
	for (unsigned int i = 0; i < numOfPar; i++)
		fprintf(fp, "%d\n", ans[i]);
	fclose(fp);
}

//their way (not hard)
unsigned int recursion(char* str, int strLen)
{
	if (strLen % 2 == 0 || strLen == 1)
		return 1;
	unsigned int ans = 1;
	//front goes to back
	if (strncmp(str, str + (strLen / 2) + 1, strLen / 2) == 0)
		ans += recursion(str, (strLen / 2) + 1);
	//back goes to back
	if (strncmp(str + 1, str + (strLen / 2) + 1, strLen / 2) == 0)
		ans += recursion(str, (strLen / 2) + 1);
	//front goes to front
	if (strncmp(str + (strLen / 2), str, strLen / 2) == 0)
		ans += recursion(str + (strLen / 2), (strLen / 2) + 1);
	//back goes to front
	if (strncmp(str + (strLen / 2) + 1, str, strLen / 2) == 0)
		ans += recursion(str + (strLen / 2), (strLen / 2) + 1);
	return ans;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = fopen(fpIn, "r");
	int strLen;
	char* str = readStrInFile(&fp, 100, &strLen);
	fclose(fp);
	unsigned int ans = recursion(str, strLen - 1) - 1;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

int main(void)
{
	//q1("mirror.in", "mirror.out");
	//q2("auto.in", "auto.out");
	q3("scode.in", "scode.out");
	return 0;
}