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

int compareFunc(const void* p1, const void* p2)
{
	int* a = (int*)p1;
	int* b = (int*)p2;
	return (*a - *b);
}
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfKnots = getNumInFile(&fp);
	getNumInFile(&fp);
	int* knots = (int*)malloc(sizeof(int) * numOfKnots);
	for (int i = 0; i < numOfKnots; i++)
		knots[i] = getNumInFile(&fp);
	fclose(fp);
	qsort(knots, numOfKnots, sizeof(int), compareFunc);
	int* distances = (int*)malloc(sizeof(int) * (numOfKnots - 1));
	distances[0] = knots[0];
	for (int i = 1; i < numOfKnots; i++)
		distances[i - 1] = knots[i] - knots[i - 1];

	int total = 0;
	int numOfDistances = numOfKnots - 1;
	int high;
	int low;
	bool pass = 1;
	for (int i = 1; i < numOfDistances; i++) //between two knots/on a distance
	{
		high = i + 1;
		low = i - 1;
		while((low >= 0) && (high < numOfDistances))
			if (distances[low] != distances[high])
			{
				pass = 0;
				break;
			}
			else
			{
				high++;
				low--;
			}
		total += pass;
		pass = 1;
	}
	for (int i = 0; i < numOfDistances; i++) //on a knot/between a distance
	{
		high = i + 1;
		low = i;
		while ((low >= 0) && (high < numOfDistances))
			if (distances[low] != distances[high])
			{
				pass = 0;
				break;
			}
			else
			{
				high++;
				low--;
			}
		total += pass;
		pass = 1;
	}

	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", total);
	fclose(fp);
}

struct point
{
	int x;
	int y;
};
struct rect
{
	point low_left;
	point high_right;
};
rect intersection(rect r1, rect r2)
{
	rect intersection;
	if ((r1.low_left.y >= r2.high_right.y) || 
		(r1.low_left.x >= r2.high_right.x) || 
		(r1.high_right.y <= r2.low_left.y) || 
		(r1.high_right.x <= r2.low_left.x))
	{
		intersection.high_right.y = -1001;
		intersection.high_right.x = -1001;
		intersection.low_left.y = -1001;
		intersection.low_left.x = -1001;
	}
	else
	{
		if (r1.high_right.y <= r2.high_right.y)
			intersection.high_right.y = r1.high_right.y;
		else
			intersection.high_right.y = r2.high_right.y;

		if (r1.low_left.y >= r2.low_left.y)
			intersection.low_left.y = r1.low_left.y;
		else
			intersection.low_left.y = r2.low_left.y;


		if (r1.high_right.x <= r2.high_right.x)
			intersection.high_right.x = r1.high_right.x;
		else
			intersection.high_right.x = r2.high_right.x;

		if (r1.low_left.x >= r2.low_left.x)
			intersection.low_left.x = r1.low_left.x;
		else
			intersection.low_left.x = r2.low_left.x;
	}
	return intersection;
}
long long findtotal(int numOfRects, rect currRect, rect* list, bool multiplier, int startAt)
{
	long long total = 0;
	static int multiply[2] = { -1, 1 };
	rect saveInfo; //change name
	for (int i = startAt; i < numOfRects; i++)
	{
		saveInfo = intersection(currRect, list[i]);
		total += multiply[multiplier] * 
			((saveInfo.high_right.y - saveInfo.low_left.y)/*length*/ * 
			(saveInfo.high_right.x - saveInfo.low_left.x)/*with*/);
		total += findtotal(numOfRects, saveInfo, list, !multiplier, i + 1);
	}
	return total;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfRects = getNumInFile(&fp);
	rect* grassy = (rect*)malloc(sizeof(rect) * numOfRects);
	long long total = 0;
	for (int i = 0; i < numOfRects; i++)
	{
		grassy[i].low_left.x = getNumInFile(&fp);
		grassy[i].high_right.y = getNumInFile(&fp);
		grassy[i].high_right.x = getNumInFile(&fp);
		grassy[i].low_left.y = getNumInFile(&fp);
		total += (grassy[i].high_right.y - grassy[i].low_left.y) * (grassy[i].high_right.x - grassy[i].low_left.x);
	}
	fclose(fp);
	for (int i = 0; i < numOfRects; i++)
		total += findtotal(numOfRects, grassy[i], grassy, 0, i + 1);
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%lld", total);
	fclose(fp);
}

void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	unsigned long long charNum = getNumInFile(&fp) - 1;
	fclose(fp);
	unsigned long long curr = 3;
	int depth = 0;
	while (charNum >= curr) //find the setNum and distance within it
	{
		depth++;
		curr = (curr * 2) + depth + 3;
	}
	int moreThanHalf;
	char answer;
	while (1) //siplyfy set
	{
		moreThanHalf = (curr - 2 - depth) / 2;
		if (charNum > moreThanHalf + 2 + depth)
			charNum -= moreThanHalf + 3 + depth;
		else if (charNum >= moreThanHalf)
		{
			if (charNum == moreThanHalf)
				answer = 'm';
			else
				answer = 'o';
			break;
		}
		depth--;
		curr = moreThanHalf;
	}
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fputc(answer, fp);
	fclose(fp);
}

int main(void)
{
	//q1("./folding.in", "./folding.out");
	//q2("./planting.in", "./planting.out");
	q3("./moo.in", "./moo.out");
	//system("pause");
	return 0;
}