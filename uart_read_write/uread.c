#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"uart_tios.h"

int main(int argc,char* argv)
{

	//int fd = init_com_port("/dev/pty1");
	
	int fd = open("/dev/pty1",O_RDWR);
	printf("fd is %d\n",fd);

	if(fd < 0 )
	{
		perror("init_com_port failed\n");
		exit(EXIT_FAILURE);
	}


	char tstr[64] = {0};

	if(read(fd,tstr,16) < 0)
	{
		perror("read error!\n");
		exit(EXIT_FAILURE);

	}

	printf("read success\n");
	printf("read tstr is %s\n",tstr);


	char wstr[32] = "echo echo\n";
	if(write(fd,wstr,10) < 0)
	{
		perror("write error!\n");
		exit(EXIT_FAILURE);

	}


	close(fd);

	printf("read end\n");


	return 0;
}
