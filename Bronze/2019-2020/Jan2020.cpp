#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
int readNumInFile(FILE** fp)
{
	char ch = fgetc(*fp);
	int num = 0;
	while ((ch != '\n') && (ch != ' '))
	{
		num = num * 10 + ch - '0';
		ch = fgetc(*fp);
	}
	return num;
}

/*struct word
{
	char* wordStart;
	int wordLen;
};
word* readFile(FILE *fp, int* numOfWords, int* lineLen, char **essay)
{
	*numOfWords = readNumInFile(&fp);
	*lineLen = readNumInFile(&fp);
	*essay = (char*)malloc(sizeof(char) * (*numOfWords) * 15);
	memset(*essay, 0, sizeof(char) * (*numOfWords) * 15);
	word *words = (word*)malloc(sizeof(word) * (*numOfWords));
	words[0].wordStart = *essay;
	char ch = getc(fp);
	int wordLen = 0;
	int wordNum = 0;
	for (int i = 0; ch != '\n'; i++)
	{
		*(*essay + i) = ch;
		if (ch == ' ')
		{
			words[wordNum].wordLen = wordLen;
			wordLen = -1;
			wordNum++;
			words[wordNum].wordStart = *essay + i + 1;
		}
		wordLen++;
		ch = getc(fp);
	}
	words[wordNum].wordLen = wordLen;
	return words;
}
void essay(const char* fileIn, const char* fileOut) 
{
	FILE *fp = NULL;
	//fopen_s(&fp, fileIn, "r");
	fp = fopen(fileIn, "r");

	int numOfWords, lineLen;
	char* essay;
	word* words = readFile(fp, &numOfWords, &lineLen, &essay);
	//printf("%s", essay);
	fclose(fp);

	fp = NULL;
	//fopen_s(&fp, fileOut, "w");
	fp = fopen(fileOut, "w");
	//fprintf(fp, "sorting done");
	for (int j = 0; j < words[0].wordLen; j++)
		fprintf(fp, "%c", words[0].wordStart[j]);
	int lettersInLine = words[0].wordLen;
	for (int i = 1; i < numOfWords; i++)
	{
		if (lettersInLine + words[i].wordLen <= lineLen)
		{
			lettersInLine += words[i].wordLen;
			fprintf(fp, " ");
		}
		else
		{
			lettersInLine = words[i].wordLen;
			fprintf(fp, "\n");
		}
		for (int j = 0; j < words[i].wordLen; j++)
			fprintf(fp, "%c", words[i].wordStart[j]);
	}
	fclose(fp);
}
*/

/*int readB_List(FILE* fp, int** inputNumsPtr)
{
	int numOfCows = readNumInFile(&fp);
	*inputNumsPtr = (int*)malloc(sizeof(int) * numOfCows);
	memset(*inputNumsPtr, 0, numOfCows * sizeof(int));
	numOfCows--;
	int sumOfB_List = 0;
	for (int i = 0; i < numOfCows; i++)
	{
		*(*inputNumsPtr + i) = readNumInFile(&fp);
		sumOfB_List += *(*inputNumsPtr + i);
	}
	//get me the sum of the first and last number
	numOfCows++;
	*(*inputNumsPtr + numOfCows - 1) = (numOfCows* (numOfCows + 1)) - sumOfB_List;
	return numOfCows;
}
int* findList(int* input, int numOfCows)
{
	int* cowList = (int*)malloc(sizeof(int) * numOfCows);
	memset(cowList, 0, numOfCows * sizeof(int));
	bool* written = (bool*)malloc(sizeof(bool) * numOfCows);
	memset(written, 0, numOfCows * sizeof(bool));
	int j;
	for (int i = 1; i < input[0]; i++)
	{
		if (input[numOfCows - 1] - i < input[numOfCows - 2])
		{
			written[i - 1] = 1;
			cowList[0] = i;
			for (j = 1; j < numOfCows; j++)
			{
				cowList[j] = input[j - 1] - cowList[j - 1];
				if (written[cowList[j] - 1])
				{
					memset(written, 0, numOfCows * sizeof(bool));
					memset(cowList, 0, numOfCows * sizeof(int));
					j = numOfCows;
				}
				else
					written[cowList[j] - 1] = 1;
			}
			if (written[0])
				return cowList;
		}
	}
	return NULL;
}
void printOrder(int *cowList, FILE* fp, int numOfCows) 
{
	fprintf(fp, "%d", cowList[0]);
	for(int i = 1; i < numOfCows; i++)
		fprintf(fp, " %d", cowList[i]);
	fprintf(fp, "\n");
}
void photoLineup(const char* filein, const char* fileout)
{
	FILE* fp = NULL;
	//fopen_s(&fp, filein, "r");
	fp = fopen(filein, "r");
	int* inputNum;
	int numOfCows = readB_List(fp, &inputNum);
	fclose(fp);
	int* cowList = findList(inputNum, numOfCows);
	fp = NULL;
	//fopen_s(&fp, fileout, "w");
	fp = fopen(fileout, "w");
	printOrder(cowList, fp, numOfCows);
	fclose(fp);
}*/
int* readStuff(int* numOfDifferentValues, unsigned long* raceLength, FILE* fp)
{
	*raceLength = readNumInFile(&fp);
	*numOfDifferentValues = readNumInFile(&fp);
	int* speeds = (int*)malloc(sizeof(int) * (*numOfDifferentValues));
	for (int i = 0; i < *numOfDifferentValues; i++)
		speeds[i] = readNumInFile(&fp);
	return speeds;
}
int findSeconds(unsigned long raceLength, int endingSpeed)
{
	unsigned long speedAccontFor = (endingSpeed * (endingSpeed + 1)) / 2;
	int seconds = 0;
	int currentSpeed = 0;
	unsigned long distanceToZero;
	long endUp;
	for (int currentDistence = 0; currentDistence < raceLength; seconds++)
	{
		distanceToZero = ((currentSpeed + 1) * (currentSpeed + 2)) / 2;
		//endUp = testVar - speedAccontFor - raceLength + currentDistence;
		if (speedAccontFor > distanceToZero || distanceToZero - speedAccontFor < raceLength - currentDistence)
		{
			currentSpeed++;
			currentDistence += currentSpeed;
		}
		else if ((currentSpeed * (currentSpeed + 1)) / 2 - speedAccontFor < raceLength - currentDistence)
			currentDistence += currentSpeed;
		else
		{
			currentSpeed--;
			currentDistence += currentSpeed;
		}
	}
	return seconds;
}
void race(const char* filein, const char* fileout)
{
	FILE* fp = NULL;
	//fopen_s(&fp, filein, "r");
	fp = fopen(filein, "r");
	int numOfSpeeds;
	unsigned long raceLength;
	int* speeds = readStuff(&numOfSpeeds, &raceLength, fp);
	fclose(fp);
	fp = NULL;
	//fopen_s(&fp, fileout, "w");
	fp = fopen(fileout, "w");
	for (int i = 0; i < numOfSpeeds; i++)
		fprintf(fp, "%d\n", findSeconds(raceLength, speeds[i]));
	fclose(fp);
}
int main(void)
{
	//essay("./Debug/word.in", "./Debug/word.out");
	//essay("word.in", "word.out");
	//photoLineup("./Debug/photo.in", "./Debug/photo.out"); //mistake: didn't think about the algorithem properly before writing
	//photoLineup("photo.in", "photo.out");
	//race("./Debug/race.in", "./Debug/race.out");
	race("race.in", "race.out");
	system("pause");
	return 0;
}
