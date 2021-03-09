#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#include<mqueue.h>
#include<string.h>
#include<semaphore.h>








FILE *fpw = NULL;
FILE *fpr = NULL;


int fdr,fdw;
int rn=0,wn=0;


sem_t sem1,sem2;







mqd_t  mqd;
struct mq_attr  attr;










void *read_msg(void* arg)
{

	unsigned int prio=0;
	char rbuf[1024]={0};

	printf("thread read message\n");

	//sleep(5);
	while(1)
	{


#if 0

		sem_wait(&sem1);
#if 0

#if 1
		if(mq_receive(mqd,rbuf,8192,&prio) == -1)
		{
			perror("failed receive msg\n");
			exit(EXIT_FAILURE);

		}
#endif

		printf("got message = %s\n",rbuf);
		memset(rbuf,0,sizeof(rbuf));
#endif




		printf("read thread heartbeat\n");



		sem_post(&sem2);
#endif
		sleep(1);


	}


}






char msg[8192]={0};



void *write_msg(void* arg)
{



	//char msg[8192]="add one\n";

	printf("thread write message\n");
#if 0
	fp =fopen("x.log","w");

	if(fp == NULL)
	{

		perror("failed open x.log");
		exit(EXIT_FAILURE);

	}
#endif

//	fprintf(fp,"%s","first line");

	while(1)
	{



		//int n = fprintf(fp,"%s",msg);
		//printf("n is %d\n",n);
		//fflush(fp);

		//fclose(fp);
		//exit(EXIT_SUCCESS);


#if 0
		sem_wait(&sem2);

#if 0
		memset(msg,0,sizeof(msg));

		gets(msg);

		printf("msg is %s\n",msg);

#if 1

		if(mq_send(mqd,msg,strlen(msg),1) == -1)
		{
			perror("failed send msg\n");
			exit(EXIT_FAILURE);

		}
#endif


#endif





		printf("write thread heartbeat\n");



		sem_post(&sem1);
#endif

		sleep(1);
	}


}



int main(int arg,char*argv[])
{





	int err;
	pthread_t  wptid,rptid;


#if 1





#if 0

	//fp =fopen("rx.log","w");
	fpr =fopen("rx.log","r");
	fpw =fopen("wx.log","w");

	if(fpr == NULL)
	{

		perror("failed open rx.log");
		exit(EXIT_FAILURE);

	}


	if(fpw == NULL)
	{

		perror("failed open wx.log");
		exit(EXIT_FAILURE);

	}




	//fprintf(fp,"%s","first line");

	//fflush(fp);

#endif



	fdr=open("rfifo",O_RDONLY | O_NONBLOCK);
	if(fdr == -1)
	{

		perror("failed open rfifo");
		exit(EXIT_FAILURE);

	}




#if 0
	//fdw=open("wfifo",O_WRONLY | O_NONBLOCK);
	fdw=open("wfifo",O_WRONLY);
	if(fdw == -1)
	{

		perror("failed open wfifo");
		exit(EXIT_FAILURE);

	}

#endif











	printf("start\n");

	while(1)
	{



		rn = read(fdr,msg,sizeof(msg));

		printf("rn is %d\n",rn);

		if(rn > 0)
		{
#if 1
			//fdw=open("wfifo",O_WRONLY | O_NONBLOCK);
			fdw=open("wfifo",O_WRONLY);
			if(fdw == -1)
			{

				perror("failed open wfifo");
				exit(EXIT_FAILURE);

			}

#endif



			wn = write(fdw,msg,strlen(msg));


			printf("wn is %d\n",wn);


			close(fdw);

		}

		//fgets(msg,1024,fpr);
		//fputs(msg,fpw);

		//		fputs(msg,fp);
		//fflush(fpw);

		//puts(msg);


		puts("hit it");


		memset(msg,0,1024);
//		sleep(1);

	} 
#endif



#if 0

	sem_init(&sem1,0,0);
	sem_init(&sem2,0,1);
#endif

#if 0
	mqd = mq_open("/mq.q",O_RDWR | O_CREAT);

	if(mqd == -1)
	{
		perror("failed open mq.q\n");
		exit(EXIT_FAILURE);

	}


	mq_getattr(mqd,&attr);

	printf("msg attr: max msg is %ld\n max bytes is %ld\n currently is %ld\n",attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);

#endif

#if 1
	//	err = pthread_create(&wptid,NULL,write_msg,NULL);
	//	err = pthread_create(&rptid,NULL,read_msg,NULL);



	//	pthread_join(wptid,NULL);
	//	pthread_join(rptid,NULL);

#endif


	return 0;





}

