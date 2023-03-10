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


	//int fd = init_com_port("/dev/pty2");

	int fd = open("/dev/pty2",O_RDWR);

	if(fd < 0)
	{
		perror("init_com_port failed\n");
		exit(EXIT_FAILURE);
	}


	char tstr[64] = {'h','e','l','l','o','6','\n'};
	if(write(fd,tstr,strlen(tstr)) < 0)
	{
		perror("write failed\n");
		exit(EXIT_FAILURE);

	}

	printf("write success\n");

	//sleep(15);
	//
	//
	fd_set rfds;	
	FD_ZERO(&rfds);
	FD_SET(fd,&rfds);
	select(fd+1,&rfds,NULL,NULL,NULL);	
	char rstr[64] = {0};
	int rrv = read(fd,rstr,16);

	printf("rrv is %d\n",rrv);

	if(rrv < 0)
	{
		perror("read failed\n");
		exit(EXIT_FAILURE);

	}

	printf("rstr is %s\n",rstr);

	close(fd);


	return 0;
}
