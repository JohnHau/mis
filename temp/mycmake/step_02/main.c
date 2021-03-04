#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tutorialconfig.h"
#include "MathFunctions.h"
int main(int argc,char*argv[])
{

	printf("hello cmake\n");
	printf("version major is %d\n",TUTORIAL_VERSION_MAJOR);
	printf("sqrt 2 is %f\n",mysqrt(2.0));


	return 1;

}
