#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>


uint8_t buffer[16*1024]={0};

int main(int argc, char* argv[])
{


	//read(stdin,buffer,1024);
	read(0,buffer,1024);

	//write(stdout,buffer,10);
	write(1,buffer,10);




	return 0;

}
