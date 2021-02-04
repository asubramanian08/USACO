#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <stdarg.h>
//#include <assert.h>
int getNumInFile(FILE** fp)
{
	char ch = fgetc(*fp);
	int total = 0;
	while ((ch != ' ') && (ch != '\n'))
	{
		total = total * 10 + ch - '0';
		ch = fgetc(*fp);
	}
	return total;
}
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
/*void ballInCupGame(const char* fpIn, const char* fpOut)
{
	int placement[3] = { 1, 2, 3 };
	int timesCalled[3] = { 0 };
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	int numOfSwitches = getNumInFile(&fp);
	int switchNumOne;
	int switchNumTwo;
	for (int i = 0; i < numOfSwitches; i++)
	{
		switchNumOne = getNumInFile(&fp) - 1;
		switchNumTwo = getNumInFile(&fp) - 1;
		placement[switchNumOne] += placement[switchNumTwo];
		placement[switchNumTwo] = placement[switchNumOne] - placement[switchNumTwo];
		placement[switchNumOne] -= placement[switchNumTwo];
		timesCalled[placement[getNumInFile(&fp) - 1] - 1]++;
	}
	fclose(fp);
	int greatest = 0;
	if (timesCalled[0] > greatest)
		greatest = timesCalled[0];
	if (timesCalled[1] > greatest)
		greatest = timesCalled[1];
	if (timesCalled[2] > greatest)
		greatest = timesCalled[2];
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", greatest);
	fclose(fp);
}*/
/*int* readOrder(FILE* fp, int* cowsNum)
{
	*cowsNum = getNumInFile(&fp);
	int* orderCows = (int*)malloc(sizeof(int) * (*cowsNum));
	for (int i = 0; i < *cowsNum; i++)
		orderCows[i] = getNumInFile(&fp);
	return orderCows;
}
int findTimesToMove(int* orderCowsArray, int numOfCows)
{
	int i = numOfCows - 2;
	int timesIncremented = 0;
	for (int currentNum = orderCowsArray[numOfCows - 1]; i >= 0; i--)
	{
		if (currentNum >= orderCowsArray[i])
			currentNum = orderCowsArray[i];
		else
			break;
		timesIncremented++;
	}
	return numOfCows - timesIncremented - 1;
}
void lineUpCows(const char* fpIn, const char* fpOut)
{
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	int cowsNum;
	int* orderCows = readOrder(fp, &cowsNum);
	fclose(fp);
	int timesToMove = findTimesToMove(orderCows, cowsNum);
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", timesToMove);
	fclose(fp);
}*/
/*int* read(FILE* fp, int* numOfTraits, int* numOfAnimals)
{
	*numOfAnimals = getNumInFile(&fp);
	char** traits = (char**)malloc(sizeof(char*) * 100);
	int* toReturn = (int*)malloc(sizeof(int) * 101 * 100);
	memset(toReturn, 0, sizeof(int) * 101 * 100);
	*numOfTraits = 0;
	int numOfTraitsToRead;
	char* current;
	for (int i = 0; i < *numOfAnimals; i++) //every animal
	{
		readStrInFile(&fp, 20);
		numOfTraitsToRead = getNumInFile(&fp);
		for (int j = 0; j < numOfTraitsToRead; j++) //every trait of animal
		{
			current = readStrInFile(&fp, 20);
			int k;
			for (k = 0; k < *numOfTraits; k++)
			{
				if (strcmp(current, traits[k]) == 0)
					break;
			}
			if (k == *numOfTraits)
			{
				traits[k] = current;
				(*numOfTraits)++;
			}
			toReturn[k * 101 + i] = 1;
		}
	}
	return toReturn;
}
int findAnswer(int numOfAnimals, int numOfTraits, int* helpDirectedByTraits*starts with how many items are after it*)
{
	int greatest = 0;
	int greatestInToCheak = 0;
	int currentWithBuddy = 0;
	int** listOfWhereToCheakIs = (int**)malloc(sizeof(int*) * 100);
	for (int toCheak = 0; toCheak < numOfAnimals; toCheak++)
	{
		memset(listOfWhereToCheakIs, 0, sizeof(int*) * 100);
		int numOfPlacesWhereToCheakIs = 0;
		for (int i = 0; i < numOfTraits; i++) //find where the places where toCheak is;
		{
			if (helpDirectedByTraits[i * 101 + toCheak])
			{
				listOfWhereToCheakIs[numOfPlacesWhereToCheakIs] = helpDirectedByTraits + i * 101;
				numOfPlacesWhereToCheakIs++;
			}
		}
		for (int accomanyPal = toCheak + 1; accomanyPal < numOfAnimals; accomanyPal++) //every possible value that keeps with it till the end
		{
			for (int curTrait = 0; curTrait < numOfPlacesWhereToCheakIs; curTrait++) //every trait toCheak is in
			{
				if (*(listOfWhereToCheakIs[curTrait] + accomanyPal))
					currentWithBuddy++;
			}
			if (currentWithBuddy > greatestInToCheak)
				greatestInToCheak = currentWithBuddy;
			currentWithBuddy = 0;
		}
		if (greatestInToCheak > greatest)
			greatest = greatestInToCheak;
		greatestInToCheak = 0;
	}
	return greatest + 1;
	
}
void q3(const char* fpIn, const char* fpOut)
{
	int numOfTraits, numOfAnimals;
	FILE* fp = NULL;
	//fopen_s(&fp, fpIn, "r");
	fp = fopen(fpIn, "r");
	int* helpArray = read(fp, &numOfTraits, &numOfAnimals);
	fclose(fp);
	
	int answer = findAnswer(numOfAnimals, numOfTraits, helpArray);
	fp = NULL;
	//fopen_s(&fp, fpOut, "w");
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", answer);
	fclose(fp);
}*/
int main(void)
{
	//ballInCupGame("./Debug/shell.in", "./Debug/shell.out");
	//ballInCupGame("shell.in", "shell.out");
	//lineUpCows("./Debug/sleepy.in", "./Debug/sleepy.out");
	//lineUpCows("sleepy.in", "sleepy.out");
	//q3("./Debug/guess.in", "./Debug/guess.out");
	//q3("guess.in", "guess.out");
	//system("pause");
	return 0;
}