#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int removeCows1(const char *filein, const char* fileout)
{
	char article[1000001] = "";
	char censor_wd[1000001] = "";
	char output[1000001] = "";
	FILE* ifp = NULL;
	ifp = fopen(filein, "r");
	fgets(article, sizeof(article), ifp);
	if (sizeof(article) == strlen(article) + 1)
		fgetc(ifp);
	fgets(censor_wd, sizeof(censor_wd), ifp);
	fclose(ifp);

	int censor_wdLen = strlen(censor_wd);
	if (censor_wd[censor_wdLen - 1] == '\n')
		censor_wdLen -= 1;

	int highestItem = censor_wdLen - 1;
	strncpy(output, article, highestItem);
	char* currOutputPtr = output + highestItem;
	char* currArticlePtr = article + highestItem;
	while (*currArticlePtr != '\0') {
		*currOutputPtr = *currArticlePtr;
		if (memcmp(currOutputPtr - highestItem, censor_wd, censor_wdLen) == 0)
			currOutputPtr -= highestItem;
		else
			currOutputPtr++;
		currArticlePtr++;
	}
	*currOutputPtr = '\0';

	FILE* ofp = NULL;
	ofp = fopen(fileout, "w");
	fprintf(ofp, "%s", output);
	fclose(ofp);
	return 0;
}
int main(void)
{
	removeCows1("censor.in", "censor.out");
	//system("pause");
	return 0;
}