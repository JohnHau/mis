#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<termios.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//#define BLEN  1024 
#define BLEN  BUFSIZ 

int fd;


int flag=0;


char rbuf[BLEN] = {0};
char wbuf[BLEN] = {0};


void *read_com(void *ptr)
{
	int nread=0;
	int tnread=0;
	int cnt=0;
	while(1)
	{
		if(flag ==1)
		{

			printf("read com\r\n");
			nread = read(fd,rbuf,sizeof(rbuf)-2);
		//	printf("nread is %d\r\n",nread);
			printf("rbuf is %s\r\n",rbuf);
			memset(rbuf,sizeof(rbuf),0);

			if(nread)
			{
				tnread += nread;
				nread =0;

			//	printf("tnread is %d\r\n",tnread);
			}
			flag=0;

		}
	}


}



void *write_com(void *ptr)
{
	int nwrite=0;

	int cnt=0;
	wbuf[0] = 'h';
	wbuf[1] = 'e';
	wbuf[2] = 'l';
	wbuf[3] = 'l';
	wbuf[4] = 'o';
	wbuf[5] = '\r';
	wbuf[6] = '\n';
	wbuf[7] = '\0';
	while(1)
	{

		printf("write com\r\n");
		nwrite= write(fd,wbuf,strlen(wbuf));
		//printf("nwrite is %d\r\n",nwrite);
		memset(wbuf,sizeof(wbuf),0);
		flag =1;
		sleep(6);
		cnt++;
		if(cnt > 3)
		{
			//cnt=0;
			//fsync(fd);
			sleep(6);
			break;
		}
	}

}







int main(int argc, char** argv)
{


	fd = open("/dev/ttyS7",O_RDWR);



	if(fd == -1)
	{	
		perror("can not open serial port failed\n");
		exit(EXIT_FAILURE);
	}

	printf("fd is %d\n",fd);


	pthread_t  thread1,thread2;
	int iret1,iret2;

	iret1 = pthread_create(&thread1,NULL,read_com,NULL);	
	iret2 = pthread_create(&thread2,NULL,write_com,NULL);	


	pthread_join(thread1,NULL);
	pthread_join(thread1,NULL);


	printf("thread 1 returns %d\n",iret1);
	printf("thread 2 returns %d\n",iret2);

	close(fd);
	printf("done\n");
	return 0;
}