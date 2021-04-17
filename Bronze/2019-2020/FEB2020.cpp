//taken for real -> 0/3

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
int readNumInFile(FILE **fp)
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
//this is the set of bronse questions for febuary 2020
/*struct point
{
	long x;
	long y;
};
long readNum(FILE** fp)
{
	char ch = fgetc(*fp);
	if (ch == EOF)
		return -1;
	long num = 0;
	if (ch == '-') //it is negitive
	{
		ch = fgetc(*fp);
		while ((ch != ' ') && (ch != '\n'))
		{
			if (num != -1) {
				num = num * 10 + ch - '0';
				ch = fgetc(*fp);
			}
			else
				num = -1 * (ch - '0');
		}
		return num * (-1);
	}
	else { //it is positive
		while ((ch != ' ') && (ch != '\n'))
		{
			if (num != -1) {
				num = num * 10 + ch - '0';
				ch = fgetc(*fp);
			}
			else
				num = -1 * (ch - '0');
		}
		return num;
	}
}
point* readPoints(FILE* fp, int *pointLen)
{
	*pointLen = readNum(&fp);
	point* postCordanates = (point*)malloc(sizeof(point) * (*pointLen));
	long Num;
	int count = 0;
	while(1)
	{
		Num = readNum(&fp);
		if (Num == -1)
			return postCordanates;
		postCordanates[count].x = Num;
		Num = readNum(&fp);
		postCordanates[count].y = Num;
		count++;
	}
}
int compare_y(const void* p, const void* q)
{
	point* a = (point*)p;
	point* b = (point*)q;
	if (a[0].y > b[0].y)
		return 1;
	else if (a[0].y < b[0].y)
		return -1;
	else
		return 0;
}
int compare_x(const void* p, const void* q)
{
	point* a = (point*)p;
	point* b = (point*)q;
	if (a[0].x > b[0].x)
		return 1;
	else if (a[0].x < b[0].x)
		return -1;
	else
		return 0;
}
long find_y(point* cordancates_y, int arraySize, int xValue, int yValue)
{
	int halfValue = arraySize / 2;
	int exponent = 2;
	while ((cordancates_y[halfValue].y + 5 < yValue) || (cordancates_y[halfValue].y - 5 > yValue)) //while i am not 10 away from it
	{
		if (cordancates_y[halfValue].y < yValue)
			halfValue = halfValue + (arraySize/pow(2, exponent));
		else
			halfValue = halfValue - (arraySize / pow(2, exponent));
		exponent++;
		if (exponent > 6) //nothing is five away from this value
			return 0;
	}
	
	long bigest = 0;
	FILE* fpOut = NULL;
	fpOut = fopen("triangles.out", "w");
	if (cordancates_y[halfValue].y > yValue) {
		while ((cordancates_y[halfValue].y >= yValue) && (halfValue >= 0))
		{
			if ((cordancates_y[halfValue].y == yValue) && (abs(cordancates_y[halfValue].x - xValue) > bigest))
				bigest = abs(cordancates_y[halfValue].x - xValue);
			halfValue--;
		}
	}
	else if (cordancates_y[halfValue].y < yValue) {
		while ((cordancates_y[halfValue].y <= yValue) && (halfValue <= arraySize))
		{
			if ((cordancates_y[halfValue].y == yValue) && (abs(cordancates_y[halfValue].x - xValue) > bigest))
			{
				bigest = abs(cordancates_y[halfValue].x - xValue);
			}
			halfValue++;
		}
	}
	else
	{
		int replace = halfValue;
		while ((cordancates_y[halfValue].y <= yValue) && (halfValue <= arraySize)) //cheak down
		{
			if ((cordancates_y[halfValue].y == yValue) && (abs(cordancates_y[halfValue].x - xValue) > bigest))
			{
				bigest = abs(cordancates_y[halfValue].x - xValue);
			}
			halfValue++;
		}
		while ((cordancates_y[replace].y >= yValue) && (replace >= 0)) //cheak up
		{
			if ((cordancates_y[replace].y == yValue) && (abs(cordancates_y[replace].x - xValue) > bigest))
			{
				bigest = abs(cordancates_y[replace].x - xValue);
			}
			replace--;
		}
	}
	return bigest;
}
long findMaxArea(point* cordanates_y, point* cordanates_x *not the begining, where the x value i am looking at starts*, int numOfPoints, int *j)
{
	long maxArea = 0;
	int i;
	int startingValue = *j;
	int currentLen;
	int numToLookAt = cordanates_x[*j].x;
	while (cordanates_x[*j].x == numToLookAt)
	{
		currentLen = find_y(cordanates_y, numOfPoints, cordanates_x[*j].x, cordanates_x[*j].y);
		if (!currentLen)
		{
			*j = *j + 1;
			continue;
		}
		i = startingValue;
		while (cordanates_x[i].x == numToLookAt)
		{
			int numToPlace = abs(cordanates_x[*j].y - cordanates_x[i].y) * currentLen;
			if (maxArea < numToPlace)
				maxArea = numToPlace;
			i++;
		}
		(*j)++;
	}
	return maxArea;
}
void q1(const char* fileIn, const char* fileOut)
{
	FILE* fp = NULL;
	//fopen_s(&fp, fileIn, "r");
	fp = fopen(fileIn, "r");
	//fopen_s(&fpOut, fileOut, "w");
	FILE* fpOut = fopen(fileOut, "w");

	int numOfPoints;
	point* coordanates_y = readPoints(fp, &numOfPoints); //works
	point* coordanates_x = (point*)malloc(sizeof(point) * numOfPoints);
	fclose(fp);

	memcpy(coordanates_x, coordanates_y, numOfPoints * sizeof(point));
	qsort(coordanates_y, numOfPoints, sizeof(point), compare_y);
	qsort(coordanates_x, numOfPoints, sizeof(point), compare_x);


	int maxArea = 0;
	int test;
	int howFarIn = 0;
	while (howFarIn < numOfPoints)
	{
		test = findMaxArea(coordanates_y, coordanates_x, numOfPoints, &howFarIn);
		if (test > maxArea)
			maxArea = test;
	}
	
	fp = NULL;
	fprintf(fpOut, "%d", maxArea);
	fclose(fpOut);

}*/

/*int readStrings(FILE* fp, char** original, char** ruined)
{
	int fileLen = readNumInFile(&fp);
	*original = (char*)malloc(sizeof(char) * fileLen);
	*ruined = (char*)malloc(sizeof(char) * fileLen);
	memset(*original, 0, sizeof(char) * fileLen);
	memset(*ruined, 0, sizeof(char) * fileLen);
	char ch = fgetc(fp);
	for(int i = 0; i < fileLen, ch != '\n'; i++)
	{
		*(*original + i) = ch;
		ch = fgetc(fp);
	}
	ch = fgetc(fp);
	for (int i = 0; i < fileLen, ch != '\n'; i++)
	{
		*(*ruined + i) = ch;
		ch = fgetc(fp);
	}
	return fileLen;
}
int timesToSwitch(int fileLen, char* original, char* ruined)
{
	int timesSwitched = 0;
	bool isSwitch = 0;
	for (int i = 0; i < fileLen; i++)
	{
		if(isSwitch == (original[i] == ruined[i]))
		{
			isSwitch = !isSwitch;
			timesSwitched++;
		}
	}
	return timesSwitched / 2;
}
void q2(const char* fileIn, const char* fileOut)
{
	FILE* fp = NULL;
	//fopen_s(&fp, fileIn, "r");
	fp = fopen(fileIn, "r");
	char* original;
	char* ruined;
	int filelen = readStrings(fp, &original, &ruined);
	fclose(fp);
	int toReturn = timesToSwitch(filelen, original, ruined);
	//printf("%d", toReturn);
	fp = NULL;
	//fopen_s(&fp, fileOut, "w");
	fp = fopen(fileOut, "w");
	fprintf(fp, "%d", toReturn);
	fclose(fp);
}*/
void readNumbers(FILE *fp, int *NumOfCows, long *timesToSwitch, int *A1, int *A2, int *B1, int *B2)
{
    *NumOfCows = readNumInFile(&fp);
    *timesToSwitch = readNumInFile(&fp);
    *A1 = readNumInFile(&fp);
    *A2 = readNumInFile(&fp);
    *B1 = readNumInFile(&fp);
    *B2 = readNumInFile(&fp);
}
/*int findLocation(int timesToSwitch, int A1, int A2, int B1, int B2, int cowNumber)
{
	int currentLocation = cowNumber;
	for (int i = 0; i < timesToSwitch; i++)
	{
		if ((currentLocation >= A1) && (currentLocation <= A2))
			currentLocation = A2 - currentLocation + A1;
		if ((currentLocation >= B1) && (currentLocation <= B2))
			currentLocation = B2 - currentLocation + B1;
	}
	return currentLocation;
}*/
int findLocation(const long timesToSwitch, int A1, int A2, int B1, int B2, int cowNumber)
{
    //int locationsArray[timesToSwitch] = { cowNumber };
    int *locationsArray = (int *)malloc(timesToSwitch / 10000 + 16);
    locationsArray[0] = cowNumber;
    int currentLocation = cowNumber;
    for (int i = 0; i < timesToSwitch; i++)
    {
        if ((currentLocation >= A1) && (currentLocation <= A2))
            currentLocation = A2 - currentLocation + A1;
        if ((currentLocation >= B1) && (currentLocation <= B2))
            currentLocation = B2 - currentLocation + B1;
        if (cowNumber == 11)
            printf("%d\n", currentLocation);
        if (currentLocation == cowNumber)
            return locationsArray[timesToSwitch % (i + 1)];
        locationsArray[i + 1] = currentLocation;
    }
    return currentLocation;
}
void q3(const char *fileIn, const char *fileOut)
{
    FILE *fp = NULL;
    int NumOfCows, A1, A2, B1, B2;
    long timesToSwitch;
    fopen_s(&fp, fileIn, "r");
    //fp = fopen(fileIn, "r");
    readNumbers(fp, &NumOfCows, &timesToSwitch, &A1, &A2, &B1, &B2);
    fclose(fp);
    int *resultOrder = (int *)malloc(sizeof(int) * NumOfCows);
    for (int i = 1; i <= NumOfCows; i++)
        resultOrder[findLocation(timesToSwitch, A1, A2, B1, B2, i) - 1] = i;

    fp = NULL;
    fopen_s(&fp, fileOut, "w");
    //fp = fopen(fileOut, "w");
    for (int i = 0; i < NumOfCows; i++)
        fprintf(fp, "%d\n", resultOrder[i]);
    fclose(fp);
}
int main(void)
{
    //q1("./Debug/triangles.in", "Debug/triangles.out"); //took to long to figure out, took help - idk what
    //q1("triangles.in", "triangles.out");
    //q2("./Debug/breedflip.in", "./Debug/breedflip.out");// asked about what the question ment - if you can filp something, and then something inside of that
    //q2("breedflip.in", "breedflip.out");
    q3("./Debug/swap.in", "./Debug/swap.out"); //miskate: didn't try to figere out a patteern and went starait to caluclating where everything would end up the whole way throguh
    //q3("swap.in", "swap.out");
    //q3 credit for idea: dad
    system("pause");
    return 0;
}