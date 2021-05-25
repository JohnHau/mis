#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"config.h"

int main(int argc,char*argv[])
{
	printf("hello world\n");
#if USE_A
	printf("hello A");
#endif

	return 0;
}
