//Also in alpha star day 5 q1

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
//_CRT_SECURE_NO_WARNINGS;
#define getNum getNumInFile(&fp)
char *readStrInFile(FILE **fp, int size, int *endSize)
{
	char ch = fgetc(*fp);
	char *str = (char *)malloc(sizeof(char) * (size + 1));
	int i = 0;
	while ((ch != ' ') && (ch != '\n'))
	{
		str[i] = ch;
		i++;
		ch = fgetc(*fp);
	}
	str[i] = '\0';
	*endSize = i + 1;
	str = (char *)realloc(str, sizeof(char) * (i + 1));
	return str;
}
long long getNumInFile(FILE **fp)
{
	char ch = fgetc(*fp);
	if (ch == '-')
		return -1 * getNumInFile(fp);
	else
	{
		long long total = ch - '0';
		ch = fgetc(*fp);
		while ((ch != ' ') && (ch != '\n'))
		{
			total = total * 10 + ch - '0';
			ch = fgetc(*fp);
		}
		return total;
	}
}

struct point
{
	int x;
	int y;
};
void q1(const char *fpIn, const char *fpOut)
{
	point legs[4] = {{0, 0},  //BL
					 {1, 0},  //BR
					 {0, 1},  //FL
					 {1, 1}}; //FR
	int highestX = 1, highestY = 1, lowestX = 0, lowestY = 0;
	point dir = {0, 1};
	int currLeg;
	FILE *fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfMoves = getNum;
	for (unsigned int i = 0; i < numOfMoves; i++)
	{
		currLeg = ((fgetc(fp) == 'F') * 2) + (fgetc(fp) == 'R');
		switch (fgetc(fp))
		{
		case 'F':
			legs[currLeg] = {legs[currLeg].x + dir.x, legs[currLeg].y + dir.y};
			if (legs[currLeg].x > highestX)
				highestX = legs[currLeg].x;
			else if (legs[currLeg].x < lowestX)
				lowestX = legs[currLeg].x;
			else if (legs[currLeg].y > highestY)
				highestY = legs[currLeg].y;
			else if (legs[currLeg].y < lowestY)
				lowestY = legs[currLeg].y;
			for (unsigned int i = 0; i < 4; i++)
			{
				if (((legs[currLeg].x == legs[i].x) && (legs[currLeg].y == legs[i].y)) && (currLeg != i))
				{
					currLeg = -1;
					break;
				}
			}
			break;
		case 'B':
			legs[currLeg] = {legs[currLeg].x - dir.x, legs[currLeg].y - dir.y};
			if (legs[currLeg].x > highestX)
				highestX = legs[currLeg].x;
			else if (legs[currLeg].x < lowestX)
				lowestX = legs[currLeg].x;
			else if (legs[currLeg].y > highestY)
				highestY = legs[currLeg].y;
			else if (legs[currLeg].y < lowestY)
				lowestY = legs[currLeg].y;
			for (unsigned int i = 0; i < 4; i++)
			{
				if (((legs[currLeg].x == legs[i].x) && (legs[currLeg].y == legs[i].y)) && (currLeg != i))
				{
					currLeg = -1;
					break;
				}
			}
			break;
		case 'L':
			legs[currLeg] = {legs[currLeg].x - dir.y, legs[currLeg].y + dir.x};
			if (legs[currLeg].x > highestX)
				highestX = legs[currLeg].x;
			else if (legs[currLeg].x < lowestX)
				lowestX = legs[currLeg].x;
			else if (legs[currLeg].y > highestY)
				highestY = legs[currLeg].y;
			else if (legs[currLeg].y < lowestY)
				lowestY = legs[currLeg].y;
			for (unsigned int i = 0; i < 4; i++)
			{
				if (((legs[currLeg].x == legs[i].x) && (legs[currLeg].y == legs[i].y)) && (currLeg != i))
				{
					currLeg = -1;
					break;
				}
			}
			break;
		case 'R':
			legs[currLeg] = {legs[currLeg].x + dir.y, legs[currLeg].y - dir.x};
			if (legs[currLeg].x > highestX)
				highestX = legs[currLeg].x;
			else if (legs[currLeg].x < lowestX)
				lowestX = legs[currLeg].x;
			else if (legs[currLeg].y > highestY)
				highestY = legs[currLeg].y;
			else if (legs[currLeg].y < lowestY)
				lowestY = legs[currLeg].y;
			for (unsigned int i = 0; i < 4; i++)
			{
				if (((legs[currLeg].x == legs[i].x) && (legs[currLeg].y == legs[i].y)) && (currLeg != i))
				{
					currLeg = -1;
					break;
				}
			}
			break;
		default:
			for (unsigned int i = 0; i < 4; i++)
			{
				legs[i] = {legs[currLeg].x - (legs[currLeg].y - legs[i].y), legs[currLeg].y + (legs[currLeg].x - legs[i].x)};
				if (legs[i].x > highestX)
					highestX = legs[i].x;
				else if (legs[i].x < lowestX)
					lowestX = legs[i].x;
				if (legs[i].y > highestY)
					highestY = legs[i].y;
				else if (legs[i].y < lowestY)
					lowestY = legs[i].y;
			}
			dir = {dir.y, -dir.x};
			break;
		}
		fgetc(fp); //get the '/n'
		if (currLeg == -1)
			break;
	}
	fclose(fp);
	int ans = -1;
	if (currLeg != -1)
		ans = (highestX - lowestX + 1) * (highestY - lowestY + 1);
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", ans);
	fclose(fp);
}

//answer was told to me -> not my answer
unsigned int getBianary(FILE **fp, unsigned int numOfLights)
{
	unsigned int total = 0;
	for (unsigned int i = 0; i < numOfLights; i++)
	{
		total = (total << 1) + (fgetc(*fp) - '0');
		fgetc(*fp); //get rid of '\n'
	}
	return total;
}
void q2(const char *fpIn, const char *fpOut)
{
	FILE *fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfLights = getNum;
	unsigned long long timesToRepete = getNum;
	unsigned int startLights = getBianary(&fp, numOfLights);
	fclose(fp);
	unsigned long *lightingCheaked = (unsigned long *)calloc(1 << numOfLights, sizeof(unsigned long));
	unsigned long timesDone = 0;
	unsigned int currLights = startLights;
	lightingCheaked[currLights] = 1;
	unsigned int currLightNum;
	unsigned int temp = 0;
	do
	{
		temp = currLights >> 1;
		temp |= (currLights & 1) << (numOfLights - 1);
		currLights ^= temp;
		currLights = currLights % (1 << numOfLights);
		timesDone++;
		if (lightingCheaked[currLights])
			break;
		else
			lightingCheaked[currLights] = timesDone + 1;
	} while (timesDone < timesToRepete);
	if (timesDone != timesToRepete)
	{
		lightingCheaked[currLights]--;
		timesToRepete = (timesToRepete - lightingCheaked[currLights]) % (timesDone - lightingCheaked[currLights]);
		for (timesDone = 0; timesDone < timesToRepete; timesDone++)
		{
			temp = currLights >> 1;
			temp |= currLights << (numOfLights - 1);
			currLights ^= temp;
			currLights = currLights % (1 << numOfLights);
		}
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	for (int i = numOfLights - 1; i >= 0; i--)
	{
		bool a = currLights & 1 << i;
		fprintf(fp, "%d\n", a);
	}
	fclose(fp);
}

struct pair
{
	unsigned int smaller;
	unsigned int larger;
};
int compare(const void *a, const void *b)
{
	if (((pair *)a)->smaller == ((pair *)b)->smaller)
		return ((pair *)a)->larger - ((pair *)b)->larger;
	return ((pair *)a)->smaller - ((pair *)b)->smaller;
}
void q3(const char *fpIn, const char *fpOut)
{
	FILE *fp = NULL;
	fp = fopen(fpIn, "r");
	//unsigned long numOfCows = getNum;
	getNum; //get rid on num of cows
	unsigned long numOfPairs = getNum;
	unsigned int smaller;
	unsigned int larger;
	pair *pairs = (pair *)malloc(sizeof(pair) * numOfPairs);
	for (unsigned int i = 0; i < numOfPairs; i++)
	{
		smaller = getNum;
		larger = getNum;
		if (smaller > larger)
			pairs[i] = {larger, smaller};
		else
			pairs[i] = {smaller, larger};
	}
	fclose(fp);
	qsort(pairs, numOfPairs, sizeof(pair), compare);
	unsigned int endingAt = 1;
	unsigned int numOfPics = 0;
	for (unsigned int currPair = 0; currPair < numOfPairs; currPair++)
	{
		if (pairs[currPair].smaller >= endingAt)
		{
			numOfPics++;
			endingAt = pairs[currPair].larger;
		}
		else if (pairs[currPair].larger < endingAt)
			endingAt = pairs[currPair].larger;
	}
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%d", numOfPics + 1);
	fclose(fp);
}

//in test, brute focre method
struct cow
{
	int friend1;
	int friend2;
	int friend3;
};
//dads pruning
/*unsigned long recursive(unsigned int currCowNum, unsigned int numOfCows, int* cows, int* stables, cow* friends, unsigned long soFar)
{
	static unsigned long allTimeSmallest = ~0;
	if (numOfCows == currCowNum) {
		if (soFar < allTimeSmallest)
			allTimeSmallest = soFar;
		return soFar;
	}
	unsigned long smallest = ~0, curr;
	for (unsigned int i = currCowNum % 2; i < numOfCows; i++) {
		if (stables[i] >= currCowNum) {
			stables[i] = currCowNum;
			cows[currCowNum] = i;
			curr = 0;
			if (friends[currCowNum].friend1 - 1 < currCowNum)
				curr += abs((int)i - cows[friends[currCowNum].friend1 - 1]);
			if (friends[currCowNum].friend2 - 1 < currCowNum)
				curr += abs((int)i - cows[friends[currCowNum].friend2 - 1]);
			if (friends[currCowNum].friend3 - 1 < currCowNum)
				curr += abs((int)i - cows[friends[currCowNum].friend3 - 1]);
			if (soFar + curr <= allTimeSmallest) {
				curr += recursive(currCowNum + 1, numOfCows, cows, stables, friends, soFar + curr);
				if (curr < smallest)
					smallest = curr;
			}
			stables[i] = numOfCows;
		}
	}
	if (!currCowNum)
		return allTimeSmallest;
	return smallest;
}*/
//solution pruning
unsigned long allTimeSmallest = ~0;
void recursive(unsigned int currPlace, unsigned int numOfCows, int *cowPos, cow *friends, unsigned long cost_soFar,
			   unsigned int pendingLinks, unsigned long pendingLink_cost)
{
	if (numOfCows == currPlace)
	{
		if (cost_soFar < allTimeSmallest)
			allTimeSmallest = cost_soFar;
		return;
	}
	if (cost_soFar + pendingLink_cost >= allTimeSmallest)
		return;
	unsigned long addedCost;
	int newPendingLinks;
	for (unsigned int i = 0; i < numOfCows; i++)
	{
		if (cowPos[i] == 0)
		{
			cowPos[i] = currPlace + 1;
			addedCost = 0;
			newPendingLinks = 3;
			if (cowPos[friends[i].friend1])
			{
				addedCost += currPlace - (cowPos[friends[i].friend1] - 1);
				newPendingLinks -= 2;
			}
			if (cowPos[friends[i].friend2])
			{
				addedCost += currPlace - (cowPos[friends[i].friend2] - 1);
				newPendingLinks -= 2;
			}
			if (cowPos[friends[i].friend3])
			{
				addedCost += currPlace - (cowPos[friends[i].friend3] - 1);
				newPendingLinks -= 2;
			}

			recursive(currPlace + 1, numOfCows, cowPos, friends, cost_soFar + addedCost,
					  pendingLinks + newPendingLinks, pendingLink_cost + (pendingLinks + newPendingLinks) - addedCost);
			cowPos[i] = 0;
		}
	}
}
void q4(const char *fpIn, const char *fpOut)
{
	FILE *fp = NULL;
	fp = fopen(fpIn, "r");
	unsigned int numOfCows = getNum;
	//int* stables = (int*)malloc(numOfCows * sizeof(int));
	int *cows = (int *)calloc(numOfCows, sizeof(int));
	cow *friends = (cow *)malloc(sizeof(cow) * numOfCows);
	for (unsigned int i = 0; i < numOfCows; i++)
	{
		friends[i].friend1 = getNum - 1;
		friends[i].friend2 = getNum - 1;
		friends[i].friend3 = getNum - 1;
		//cows[i] = numOfCows;
		//stables[i] = numOfCows;
	}
	fclose(fp);
	//unsigned long ans = recursive(0, numOfCows, cows, stables, friends, 0);
	recursive(0, numOfCows, cows, friends, 0, 0, 0);
	unsigned long ans = allTimeSmallest;
	fp = NULL;
	fp = fopen(fpOut, "w");
	fprintf(fp, "%u", ans);
	fclose(fp);
}

int main(void)
{
	//q1("ballet.in", "ballet.out");
	//q2("blink.in", "blink.out");
	//q3("photo.in", "photo.out");
	q4("haywire.in", "haywire.out");

	return 0;
}