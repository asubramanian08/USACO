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

//original
/*unsigned long long getBi(FILE** fp, int* count)
{
	unsigned long long total = 0;
	char ch = fgetc(*fp);
	while ((ch != ' ') && (ch != '\n'))
	{
		total = total * 2 + ch - '0';
		ch = fgetc(*fp);
		(*count)++;
	}
	return total;
}
unsigned long long myPow(int base, int pow)
{
	unsigned long long total = 1;
	for (int i = 0; i < pow; i++)
		total *= base;
	return total;
}
void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	int count = 0;
	fopen_s(&fp, fpIn, "r");
	unsigned long long bianary = getBi(&fp, &count);
	fclose(fp);
	count += 4;
	bianary *= 17;
	if (bianary / (myPow(2, count)) != 1)
		count--;
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	while (count >= 0)
	{
		fprintf(fp, "%d", (unsigned long long)(bianary / (myPow(2, count))));
		bianary = bianary % (unsigned long long)(myPow(2, count));
		count--;
	}
	fclose(fp);
}*/
//redo
/*void q1(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	bool* num = (bool*)malloc(sizeof(bool) * 1005);
	num[0] = 0;
	int count = 1;
	char ch = fgetc(fp);
	while (ch != '\n')
	{
		num[count] = ch - '0';
		count++;
		ch = fgetc(fp);
	}
	fclose(fp);
	for (int i = 0; i < 4; i++)
		num[count + i] = 0;
	bool* newNum = (bool*)malloc(sizeof(bool) * (count - 1));
	memcpy(newNum, num + 1, (count - 1) * sizeof(bool));
	bool carry;
	int j;
	for (int i = count - 2; i >= 0; i--)
	{
		carry = newNum[i];
		j = i;
		while (carry)
		{
			if (num[j + 5] == 0)
				carry = 0;
			num[j + 5] = !num[j + 5];
			j--;
		}
	}
	count = count + 4;
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	if (num[0])
		fprintf(fp, "1");
	for (int i = 1; i < count; i++)
		fprintf(fp, "%d", num[i]);
	fclose(fp);
}*/

struct point
{
	int x;
	int y;
};
int findWays(point* cows, int numOfCows, int currDepth, int row, int col, int dirRow, int dirCol)
{
	int currDirRow = 0;
	int currDirCol = 0;
	int total = 0;
	if (currDepth == numOfCows)
	{
		if (row == 0)
		{
			currDirRow = 0;
			if (col > 0)
				currDirCol = -1;
			else
				currDirCol = 1;
		}
		else
		{
			currDirCol = 0;
			if (row > 0)
				currDirRow = -1;
			else
				currDirRow = 1;
		}
		if (((dirCol && (currDirCol != dirCol)) || (dirRow && (dirRow != currDirRow))) && ((row == 0) || (col == 0)))
			total = 1;
	}
	else
	{
		point* trial = (point*)malloc(sizeof(point) * numOfCows);
		memcpy(trial, cows, sizeof(point) * numOfCows);
		for (int i = 0; i < numOfCows; i++)
			if ((col == cows[i].x) || (row == cows[i].y))
			{
				if (row == cows[i].y)
				{
					currDirRow = 0;
					if (col > cows[i].x)
						currDirCol = -1;
					else
						currDirCol = 1;
				}
				else
				{
					currDirCol = 0;
					if (row > cows[i].y)
						currDirRow = -1;
					else
						currDirRow = 1;
				}
				if ((dirCol && (currDirCol != dirCol )) || (dirRow && (dirRow != currDirRow)))
				{
					trial[i].x = 1001;
					trial[i].y = 1001;
					total += findWays(trial, numOfCows, currDepth + 1, cows[i].y, cows[i].x, currDirRow, currDirCol);
					trial[i].x = cows[i].x;
					trial[i].y = cows[i].y;
				}
			}
	}
	return total;
}
void q2(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	fopen_s(&fp, fpIn, "r");
	int numOfCows = getNumInFile(&fp);
	point* cows = (point*)malloc(sizeof(point) * numOfCows);
	for (int i = 0; i < numOfCows; i++)
	{
		cows[i].x = getNumInFile(&fp);
		cows[i].y = getNumInFile(&fp);
	}
	fclose(fp);
	int total = findWays(cows, numOfCows, 0, 0, 0, 2, 2);
	fp = NULL;
	fopen_s(&fp, fpOut, "w");
	fprintf(fp, "%d", total);
	fclose(fp);
}

/*struct point
{
	int x;
	int y;
};
char* str_n_size(FILE** fp, int size, int* realSize)
{
	char ch = fgetc(*fp);
	char* str = (char*)malloc(sizeof(char) * (size + 1));
	*realSize = 0;
	while ((ch != ' ') && (ch != '\n'))
	{
		str[*realSize] = ch;
		(*realSize)++;
		ch = fgetc(*fp);
	}
	str[*realSize] = '\0';
	char* newStr = (char*)malloc(sizeof(char) * ((*realSize) + 1));
	memcpy(newStr, str, sizeof(int) * ((*realSize) + 1));
	free(str);
	return newStr;
}
point* findEnds(int numOfInstructions, char* instructions, point end)
{
	point* endLocations = (point*)malloc(sizeof(point) * numOfInstructions * 2);
	point curr;
	curr.x = 0;
	curr.y = 0;
	point currDir;
	currDir.x = 0;
	currDir.y = 1;
	bool temp;
	for (int i = 0; i < numOfInstructions; i++)
	{
		if (instructions[i] == 'F') //move forward
		{
			endLocations[i * 2].x = curr.x + (end.y - curr.y); //right x val
			endLocations[i * 2].y = curr.y + (curr.x - end.x); //right y val
			endLocations[i * 2 + 1].x = curr.x - (end.y - curr.y); //left x val
			endLocations[i * 2 + 1].y = curr.y - (curr.x - end.x); //left y val
			curr.x = curr.x + currDir.x;
			curr.y = curr.y + currDir.y;
		}
		else if (instructions[i] == 'R') //turn right
		{
			endLocations[i * 2].x = (curr.y - end.y) + curr.x + currDir.x; //forward x val
			endLocations[i * 2].y = (end.x - curr.x) + currDir.y + curr.y; //forward y val
			endLocations[i * 2 + 1].x = curr.x - (end.x - curr.x); //left x val
			endLocations[i * 2 + 1].y = curr.y - (end.y - curr.y); //left y val
			temp = currDir.x;
			currDir.x = currDir.y;
			currDir.y = -1 * temp;
		}
		else //turn left
		{
			endLocations[i * 2].x = (curr.y - end.y) + curr.x + currDir.x; //forward x val
			endLocations[i * 2].y = (end.x - curr.x) + currDir.y + curr.y; //forward y val
			endLocations[i * 2 + 1].x = curr.x - (end.x - curr.x); //right x val
			endLocations[i * 2 + 1].y = curr.y - (end.y - curr.y); //right y val
			temp = currDir.x;
			currDir.x = -1 * currDir.y;
			currDir.y = temp;
		}
	}
	return endLocations;
}
int compareFunc(const void* p1, const void* p2)
{
	point* a = (point*)p1;
	point* b = (point*)p2;
	if (a->x != b->x)
		return a->x - b->x;
	return a->y - b->y;
}
int findAnswer(point* ends, int numOfInstructions)
{
	qsort(ends, numOfInstructions, sizeof(point), compareFunc);
	int numOfEnds = 2 * numOfInstructions;
	int answer = 1;
	point curr = ends[0];
	for (int i = 1; i < numOfEnds; i++)
	{
		if ((curr.x == ends[i].x) && (curr.y == ends[i].y))
		{
			answer++;
			curr = ends[i];
		}
	}
	return answer;
}
void q3(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	int numOfInstuctions;
	char* insturctions = str_n_size(&fp, 100000, &numOfInstuctions);
	fclose(fp);
	point end = { 0, 0 };
	point currDir = { 0, 1 };
	int temp;
	for (int i = 0; i < numOfInstuctions; i++) //find the end
	{
		if (insturctions[i] == 'F')
		{
			end.x += currDir.x;
			end.y += currDir.y;
		}
		else if (insturctions[i] == 'R')
		{
			temp = currDir.x;
			currDir.x = currDir.y;
			currDir.y = -1 * temp;
		}
		else
		{
			temp = currDir.x;
			currDir.x = -1 * currDir.y;
			currDir.y = temp;
		}
	}
	point* ends = findEnds(numOfInstuctions, insturctions, end);
	int answer = findAnswer(ends, numOfInstuctions);
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", answer);
	fclose(fp);
}*/

int main(void)
{
	//q1("./times17.in", "./times17.out");
	q2("./connect.in", "./connect.out");
	//q3("./wrongdir.in", "./wrongdir.out");
	//system("pause");
	return 0;
}