#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	//char word[20] = "hi";
	//char textFile[100] = "gherihi\nhiiakjdc\naeojrhii\ngohroihaaiojrg\nhi";
	//printf("first line\nhi\n");
	//printf("bob");
	//printf("xt");
	FILE* input = NULL;
	//char input[]
	//printf("hi");
	//printf("argv[2] = %s", argv[2]);
	input = fopen(argv[1], "r");
	//char textFile[] = fgets(input);
	//printf("second line");
	int inWord = 0;
	int numChars = 0;
	int numLines = 0;
	char *word = argv[2];
	//printf("%d\n", strlen(word));
	printf("%s is in line number:", word);
	char ch = getc(input);
	//printf("%c", ch);
	for(int i = 0; ch != -1; i++)
	{
		//char name1[11] ="";
		numChars++;
		if(ch == '\n')
		{
			numLines++;
		}
		if(ch == word[inWord])
		{
			inWord++;
			//printf("%d%c\n", inWord, word[inWord]);
			//inWord++;
			if(inWord == (strlen(word) - 1))
			{
				inWord = 0;
				printf("%d,", numLines + 1);
			}
		}
		else
		{
			inWord = 0;
		}
	ch = getc(input);
	//printf("%c", ch);
	}
	printf("\nthe number of charactors is %d\nthe number of lines is %d\n", numChars + 1, numLines);
	return 0;
	//ch = getc(input);
}
