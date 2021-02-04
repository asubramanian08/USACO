#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
int removeCows1(const char* filename, const char* fileout);


int main(void)
{
	removeCows1("./Debug/censor.in", "./Debug/censor.out");
	//numberCOWs("./cow.in", "./cow.out");
	//hopstoch("./hopscotch.in", "./hopscotch.out");
	//system("pause");
	/*int i = 1;
	FILE* in = NULL;
	in = fopen("./censor.out", "r");
	FILE* out = NULL;
	out = fopen("./8.out", "r");
	char In;
	char Out;
	for (In = getc(in), Out = getc(out); In == Out; i++, Out = getc(out), In = getc(in))
	{
		
	}
	printf("what letter number %d, 8.out: %c, censor.out: %c", i, Out, In);*/
	system("pause");
	return 0;
}