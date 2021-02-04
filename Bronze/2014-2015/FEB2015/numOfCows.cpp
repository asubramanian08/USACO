#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
/*
void numberCOWs(const char* filein, const char* fileout)
{
	FILE* input = NULL;
	input = fopen(filein, "r");
	int n = 0;
	char ch;
	while ((ch = fgetc(input)) != '\n')
	{
		n = (n * 10) + ch - '0';
	}
	struct COW { int C; int O; int W; };
	COW *letters = (COW *) malloc(n * (sizeof(COW)));
	int i = 0;
	int C = 0, O = 0, W = 0;

	while ((ch = fgetc(input)) != 'ÿ') //create the letters array
	{
		switch (ch)
		{
		case 'C':
			letters[i].C = ++C;
			letters[i].O = O;
			letters[i].W = W;
			i++;
			break;
		case 'O':
			letters[i].C = C;
			letters[i].O = ++O;
			letters[i].W = W;
			i++;
			break;
		case 'W':
			letters[i].C = C;
			letters[i].O = O;
			letters[i].W = ++W;
			i++;
			break;
		}
	}
	fclose(input);

	O = 0;
	long long total = 0;
	for (int j = 0; j < n; j++) //find the total
	{
		if (letters[j].O > O)
		{
			O++;
			total += (letters[j].C) * (W - letters[j].W);
		}
	}
	free(letters);

	FILE* output = NULL;
	output = fopen(fileout, "w");
	fprintf(output, "%lli", total);
	fclose(output);
}
int main2(void)
{
	numberCOWs("./cow.in", "./cow.out");
	//system("pause");
	return 0;
}*/