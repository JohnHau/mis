#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<termios.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

//#define BLEN  1024 
#define BLEN  BUFSIZ 

int main(int argc, char** argv)
{
	int fd;
	int wfd;
	int rfd;

	int nread,i;
	int tnread;
	int nwrite=0;
	int cnt=0;
	int s=0;

	char wbuff[64] = "Hello\n";
	char recbuf[1024]={0};
	int cnt_rec=0;
	int c;

	char rbuff[BLEN] = {0};

//	fd = open("/dev/ttyUSB0",O_RDWR|O_NOCTTY|O_NDELAY);
//	fd = open("/dev/ttyUSB0",O_RDWR|O_NOCTTY);
	//fd = open("/dev/ttyUSB0",O_RDONLY);
	fd = open("/dev/ttyUSB0",O_RDWR);
//	fd = open("/dev/ttyS8",O_RDWR);

	wfd = open("acom.log",O_WRONLY);
	rfd = open(argv[1],O_RDONLY);

	if(fd == -1)
	{	
		perror("can not open serial port failed\n");
		exit(EXIT_FAILURE);
	}

	printf("fd is %d\n",fd);

	cnt_rec=0;

	while((nread =read(rfd,recbuf,BLEN)) > 0)	
	{

		nwrite= write(fd,recbuf,nread);
		printf("nwrite is %d\n",nwrite);

		tnread=0;
		while(tnread != nwrite)
		{

			printf("---tnread is %d---\n",tnread);

			nread = read(fd,rbuff,BLEN);
			tnread +=nread;
			printf("---nread is %d---\n",nread);
			write(wfd,rbuff,nread);
		}


	}

	close(wfd);
	close(rfd);
	close(fd);
	printf("done\n");
	return 0;
}