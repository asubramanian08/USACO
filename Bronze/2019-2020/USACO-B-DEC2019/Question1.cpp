#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
void Q1(const char* filein, const char* fileout)
{
	FILE* iPtr = NULL;
	int session = 0;
	int cows = 0;
	int cowNum = 0;
	char ch;
	iPtr = fopen(filein, "r");
	//fopen_s(&iPtr, filein, "r");
	while ((ch = getc(iPtr)) != ' ')
		session = (session * 10) + ch - '0';
	while ((ch = getc(iPtr)) != '\n')
		cows = (cows * 10) + ch - '0';
	bool *input = (bool *)malloc(cows * cows * sizeof(bool));
	memset(input, 0, sizeof(input));
	int* curSess = (int*)malloc(cows * sizeof(int));
	
	int i = 0;
	for (; i < session; i++)
	{
		int j = 0;
		for (; j < cows; j++)
		{
			while (((ch = getc(iPtr)) != ' ') && (ch != '\n'))
				cowNum = (cowNum * 10) + ch - '0';
			curSess[j] = cowNum;
			int k = 0;
			for (; k < j; k++)
				input[(cows * (cowNum - 1)) + (curSess[k] - 1)] = 1;
			cowNum = 0;
		}
	}
	fclose(iPtr);
	
	int count = 0;
	int l = 1;
	for(; l < cows; l++)
	{
		int m = 0;
		for (; m < l; m++)
		{
			if (input[(cows * m) + l] != input[(cows * l) + m])
				count++;
		}
	}

	FILE* oPtr = NULL;
	oPtr = fopen(fileout, "w");
	//fopen_s(&oPtr, fileout, "w");
	fprintf(oPtr, "%d", count);
}
int main1(void)
{
	Q1("./gymnastics.in", "./gymnastics.out");
	//system("pause");
	return 0;
}