#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<stdint.h>
#include<termios.h>
#include<sys/stat.h>
#include<sys/select.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>


#include <termios.h>

//#define BLEN  128 
#define BLEN  BUFSIZ 

int main(int argc, char** argv)
{
	int fd;
	int wfd;
	int rfd;

	
	fd_set fds;
	struct timeval tv={5,0};
	int retval;


	int scnt=0;

	int nread,i;
	int tnread;
	int nwrite=0;
	int cnt=0;
	int s=0;
	int tlen=0;

	char wbuff[64] = "Hello\n";
	uint8_t recbuf[BLEN]={0};
	uint8_t *precbuf=recbuf;
	int cnt_rec=0;
	int c;

	char rbuff[BLEN] = {0};

//	tv.tv_sec =5;
//	tv.tv_usec = 500000;

//	fd = open("/dev/ttyUSB0",O_RDWR|O_NOCTTY|O_NDELAY);
//	fd = open("/dev/ttyUSB0",O_RDWR|O_NOCTTY);
	//fd = open("/dev/ttyUSB0",O_RDONLY);
	fd = open("/dev/ttyUSB0",O_RDWR);
//	fd = open("/dev/ttyS8",O_RDWR);
//	fd = open("/dev/ttyS4",O_RDWR);

//	wfd = open("acom.log",O_WRONLY);
//	rfd = open(argv[1],O_RDONLY);

	if(fd == -1)
	{	
		perror("can not open serial port failed\n");
		exit(EXIT_FAILURE);
	}

	printf("fd is %d\n",fd);

	//tcflush(fd,TCIFLUSH);
	tcflush(fd,TCIOFLUSH);

	cnt_rec=0;

	char cmd[128] = "dht11";

	//tlen = write(fd,cmd,6);
#if 0
	tlen = write(fd,"d",1);
	tlen = write(fd,"h",1);
	tlen = write(fd,"t",1);
	tlen = write(fd,"1",1);
	tlen = write(fd,"1",1);
	//sleep(1);
#endif
//	printf("tx:the amount is %d\n",tlen);

	memset(recbuf,0,sizeof(recbuf));
	tlen = write(fd,cmd,5);
	while(1)
	{

		FD_ZERO(&fds);
		FD_SET(fd,&fds);
		
		tv.tv_sec =5;
		tv.tv_usec = 500000;
		//sleep(1);

	//	tlen = write(fd,cmd,5);
		retval = select(fd+1,&fds,NULL,NULL,&tv);
		//retval = select(fd+1,&fds,NULL,NULL,NULL);

		if(retval == -1)
		{
			printf("error:select\n");
			close(fd);
			exit(EXIT_FAILURE);

		}
		else if(retval)
		{
			if(FD_ISSET(fd,&fds))
			{
			//	memset(recbuf,0,sizeof(recbuf));
				tlen =read(fd,precbuf,BLEN);	
			//	printf("m is %s\n",precbuf);
			//	printf("mlen is %d\n",tlen);
				precbuf +=tlen;
				//tlen =read(fd,recbuf,8);	
#if 0
				printf("rx:the amount is %d\n",tlen);
				printf("%d\n",recbuf[0]);
				printf("tlen is %d\n",tlen);
#endif
			//	printf("message is %s\n",recbuf);
				//printf("msg is %c %c %c %c\n",recbuf[0],recbuf[1],recbuf[2],recbuf[3]);


				//	tlen = write(fd,cmd,6);
				
			}
		}
#if 1
		else
		{

			precbuf = recbuf;
			printf("message is %s\n",precbuf);
#if 0
			int i=0;
			for(i=0;i<128;i++)
				printf("%c",precbuf[i]);
			printf("\n");
#endif
			memset(recbuf,0,sizeof(recbuf));
			precbuf = recbuf;
			tlen = write(fd,cmd,6);

			printf("send cmd %d\n",scnt++);
			//printf("tlen is %d\n",tlen);

			//exit(EXIT_FAILURE);
		}
#endif


	}











#if 0
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
#endif
	close(fd);
	printf("done\n");
	return 0;
}
