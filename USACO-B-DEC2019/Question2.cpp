#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
/*void Q2(const char* filein, const char* fileout)
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
	char* used = (char*)malloc(sizeof(char) * total);
	memset(used, 0, total);
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
	for (i = 0; i < total + 1; i++)
	{
		if (used[i] == 0)
		{
			count = 1;
			memset(starts, 0, 100);
			int numStarts;
			starts[0] = strchr(road, road[i]) - road + 1;
			for (numStarts = 1; (location = strchr(road + starts[numStarts - 1], road[i])) && (location != NULL); numStarts++) {
				starts[numStarts] = location - road + 1;
				used[starts[numStarts] - 1] = 1;
			}
				//starts[numStarts] = location;
			used[i] = 1;
			if (numStarts > 1)
				go = 1;
			else
				go = 0;
			int j;
			for (j = 0; go; j++)// find if next letter matches
			{
				char letter = road[i + 1 + j];
				int letter1 = 0;
				int letter2 = 0;
				//for loop to find and evorve starts - if letter2 == 1 then used becomes 0;
				int k;
				for (k = 0; k < numStarts; k++) //cheak if the starts continue and witch have to stop
				{
					if (starts[k] != 0)
					{
						used[starts[k] + j] = 1;
						if (road[starts[k] + j] == letter)
							letter1++;
						else
						{
							letter2++;
							if (letter2 >= 2)
								used[starts[k] - 1] = 0;
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
	}
	FILE* output = NULL;
	output = fopen(fileout, "w");
	//fopen_s(&output, fileout, "w");

	fprintf(output, "%d", oldcount + 1);
	fclose(output);
}*/
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
int main(void)
{
	Q2("./whereami.in", "./whereami.out");
	//system("pause");
	return 0;
}

/*int main(void)
{
	Q2("./Debug/whereami.in", "./Debug/whereami.out");
	//system("pause");
	return 0;
}
int recursave(char* in, int* starts, int count)
{
	int i;
	int j;
	int stop = 0;
	int alpha[26] = { 0 };
	for (i = 0; stop == 0; i++)
	{
		memset(alpha, 0, 26);
		for (j = 0; j < sizeof(starts); j++) //finding the next letter
		{
			if (starts[j] == 0)
				break;
			in[starts[j] + 1]; 
		}
	}
}*/
/*void Q2(const char* filein, const char* fileout)
{
	int numOfChars = 0;
	char ch;
	FILE* input = NULL;
	//input = fopen(filein, "r");
	fopen_s(&input, filein, "r");
	//char ch = getc(input);
	while ((ch = getc(input)) != '\n')
	{
		numOfChars = (numOfChars * 10) + ch - '0';
	}
	char* in = (char*)malloc(sizeof(char) * numOfChars);
	char* used = (char*)malloc(sizeof(char) * numOfChars);
	memset(used, 0, numOfChars);
	int k = 0;
	while ((ch = getc(input)) != '\n')
	{
		in[k] = ch;
		k++;
	}

	int i;
	int stop = 1;
	char* starts = (char*)malloc(sizeof(char) * numOfChars);
	memset(starts, 0, numOfChars);
	int numOfStarts;
	int output = 0;
	for (i = 0; i < numOfChars; i++)
	{
		if (used[i] == 0)
		{
			stop = 0;
		}
		int j;
		for (j = 0; stop == 0; j++) //loop for each time it moves to next number in same start
		{
			//for loop to find witch starts need to be taken off //make it used //increment output //end of line?
			//if therea e more than one tings wiht 2 or more variations then enter loop for each - remake/copy starts and continue like normal
			//or recursive that handels (just?no) fork and call itself for the fork of fork etc. or calls itelf every time it has to repeat if or if not fork, nothing special starts, in has to be given to recursive

		}
	}


	FILE* out = NULL;
	//output = fopen(fileout, "w");
	fopen_s(&out, fileout, "w");

	fclose(out);
}
int main2(void)
{
	Q2("", "");
	//system("pause");
	return 0;
}*/