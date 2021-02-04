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
	bool* input = (bool*)malloc(cows * cows * sizeof(bool));
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
	for (; l < cows; l++)
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
void Q2(const char* filein, const char* fileout)
{
	FILE* input = NULL;
	input = fopen(filein, "r");
	//fopen_s(&input, filein, "r");
	char ch = getc(input);
	int total = 0;
	while (ch != '\n')
	{
		total = total * 10 + ch - '0';
		ch = getc(input);
	}
	char* road = (char*)malloc(sizeof(char) * (total + 1));
	//char* used = (char*)malloc(sizeof(char) * total);
	//memset(used, 0, total);
	road[total] = 0;
	ch = getc(input);
	int i;
	for (i = 0; ch != '\n'; i++)
	{
		road[i] = ch;
		ch = getc(input);
	}
	fclose(input);

	bool go;
	int count = 1;
	int oldcount = 0;
	char* location;
	//int location;
	int starts[100] = { 0 };
	for (i = 0; i < total; i++)
	{
		count = 1;
		memset(starts, 0, 100);
		int numStarts;
		starts[0] = strchr(road + i, road[i]) - road + 1;
		for (numStarts = 1; (location = strchr(road + starts[numStarts - 1], road[i])) && (location != NULL); numStarts++) {
			starts[numStarts] = location - road + 1;
			//used[starts[numStarts] - 1] = 1;
		}
		//starts[numStarts] = location;
		//used[i] = 1;
		if (numStarts > 1)
			go = 1;
		else
			go = 0;
		int j;
		for (j = 0; go; j++)// find if next letter matches
		{
			char letter = road[i + 1 + j];
			int letter1 = 0;
			//int letter2 = 0;
			//for loop to find and evorve starts - if letter2 == 1 then used becomes 0;
			int k;
			for (k = 0; k < numStarts; k++) //cheak if the starts continue and witch have to stop
			{
				if (starts[k] != 0)
				{
					//used[starts[k] + j] = 1;
					if (road[starts[k] + j] == letter)
						letter1++;
					else
					{
						//letter2++;
						starts[k] = 0;
					}
				}
			} //c
			if (letter1 > 1)
				count++;
			else
				go = 0;
		}
		if (count > oldcount)
		{
			oldcount = count;
		}
	}
	FILE* output = NULL;
	output = fopen(fileout, "w");
	//fopen_s(&output, fileout, "w");

	fprintf(output, "%d", oldcount + 1);
	fclose(output);
}
void Q3(const char* filein, const char* fileout)
{
	char index[8][10] = { "Beatrice", "Belinda", "Bella", "Bessie", "Betsy", "Blue", "Buttercup", "Sue" };
	int output[8] = { 0 };
	int withwho[8] = { 0 };
	int numOfBond[8] = { 0 };
	bool used[8] = { 0 };
	int i;
	//int j;
	FILE* input = NULL;
	input = fopen(filein, "r");
	//fopen_s(&input, filein, "r");
	int lines = fgetc(input) - '0';
	//char ch = 10;
	fgetc(input); // swallow the new line
	//printf("got passed first bit\n");
	for (i = 0; i < lines; i++)
	{
		int name1 = 0;
		int name2 = 0;
		char cow1[11] = "";
		char cow2[11] = "";

		//for loop to find name number then waste must be milked beside, then find next name number
		fscanf(input, "%s must be milked beside %s", &cow1, &cow2);
		while (memcmp(cow1, index[name1], strlen(cow1)) != 0)
			name1++;
		while (memcmp(cow2, index[name2], strlen(cow2)) != 0)
			name2++;

		withwho[name1] = (withwho[name1] * 10) + name2 + 1;
		withwho[name2] = (withwho[name2] * 10) + name1 + 1;
		numOfBond[name1]++;
		numOfBond[name2]++;
		//printf("line %d compleate\n", i);
	}
	fclose(input);
	int j;
	int previous;
	int addWhere = 0;
	int curr = 0;
	int go = 0;
	for (j = 0; j < 8; j++) //findin something with 1 or 0 bonds
	{
		previous = j;
		if ((numOfBond[j] < 2) && (used[j] == 0))
		{
			if ((numOfBond[j] == 1) && (used[j] != 1))
				go = 1;
			used[j] = 1;
			output[addWhere] = j;
			addWhere++;
		}
		//printf("j is %d\n", j);
		while (go == 1) //finding hte bond that is attaced for example 1 have one bond so finding that one bond, then finding the bonds that that one bond has, if only 1 than move to outer loop
		{
			if (used[(withwho[previous] - 1) % 10] == 0)
			{
				numOfBond[previous]--; //remove
				previous = (withwho[previous] % 10) - 1;
				numOfBond[previous]--; //remove
				used[previous] = 1;
				output[addWhere] = previous;
				addWhere++;
			}
			else if (used[((withwho[previous]) - (withwho[previous] % 10) / 10) - 1] == 0)
			{
				numOfBond[previous]--; //remove
				previous = (((withwho[previous]) - (withwho[previous] % 10)) / 10) - 1;
				numOfBond[previous]--; //remove
				used[previous] = 1;
				output[addWhere] = previous;
				addWhere++;
			}
			if (numOfBond[previous] == 0)
			{
				go = 0;
			}
		}
		go = 0;
	}
	FILE* out = NULL;
	out = fopen(fileout, "w");
	//fopen_s(&out, fileout, "w");
	for (j = 0; j < 8; j++)
	{
		fprintf(out, "%s\n", index[output[j]]);
	}
	fclose(out);
}
int main(void)
{
	//Q1("C://Users//Arjun//Desktop//input.txt", "C://Users//Arjun//Desktop//test.txt");
	//Q2("C://Users//Arjun//Desktop//input.txt", "C://Users//Arjun//Desktop//test.txt");
	//Q3("", "");
	//system("pause");
	return 0;
}