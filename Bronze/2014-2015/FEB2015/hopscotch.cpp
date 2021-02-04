#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
/*
int rHopstoch(int lookat, int columns, bool* grid, bool colortofind, int* output)
{
	int total = 0;
	int i = (lookat / columns) - 1;
	for(; i >= 0; i--) //number of rows
	{
		int j = (lookat % columns) - 1;
		for(; j >= 0; j--) //number of columns
		{
			if ((output[(i * columns) + j] >= 0) && (grid[(i * columns) + j] == colortofind)) //if it is already  found before
			{
				total = total + output[(i * columns) + j];
			}
			else if (grid[(i * columns) + j] == colortofind) //if it is the color that i want to find look in to it //call recursive
			{
				output[(i * columns) + j] = rHopstoch((i * columns) + j, columns, grid, !colortofind, output);
				total += output[(i * columns) + j];
			}
		}
	}
	return total;
}

void hopstoch(const char* filein, const char* fileout)
{
	FILE* input = NULL;
	input = fopen(filein, "r");
	char ch;
	int rowlen = 0;
	int colLen = 0;
	while ((ch = fgetc(input)) != ' ') //finding row len
	{
		rowlen = (rowlen * 10) + ch - '0';
	}
	while ((ch = fgetc(input)) != '\n')// finding column len
	{
		colLen = (colLen * 10) + ch - '0';
	}
	bool* grid = (bool*)malloc(rowlen * colLen * sizeof(bool));
	int* output = (int*)malloc(rowlen * colLen * sizeof(int));
	output[0] = 1;
	int i = 1;
	while (i < rowlen * colLen) //initializing output
	{
		output[i] = -1;
		i++;
	}
	ch = fgetc(input);
	char one = ch;
	grid[0] = 1;
	ch = fgetc(input);
	i = 1;
	for(; ch != 'ÿ'; ch = fgetc(input)) //making grid
	{
		if (ch == one)
		{
			grid[i] = 1;
			i++;
		}
		else if (ch != '\n')
		{
			grid[i] = 0;
			i++;
		}
	}
	fclose(input);
	FILE* out = NULL;
	out = fopen(fileout, "w");
	fprintf(out, "%d\n", rHopstoch(i - 1, colLen, grid, !grid[i - 1], output)); //calling function
	free(grid);
	free(output);
	fclose(out);
}
int main(void)
{
	hopstoch("hopscotch.in", "hopscotch.out");
	//system("pause");
	return 0;
}*/