#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

void Q3(const char* filein, const char* fileout)
{
	char index[8][10] = { "Beatrice", "Belinda", "Bella", "Bessie", "Betsy", "Blue", "Buttercup", "Sue" };
	int output[8] = {0};
	int withwho[8] = {0};
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
int main3(void)
{
	Q3("./lineup.in", "./lineup.out");
	//system("pause");
	return 0;
}