#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <aio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <pthread.h> 
  
#define PORT    1997  
#define MAXLINE  1500 


int stn=0;


uint8_t bqr_rp[]="hello loopback";




uint8_t is_ready_object_list =0;
uint32_t cnt_object_list =0;



extern int32_t make_internet_address(int8_t * hostname,int32_t port,struct sockaddr_in *addrp);

int sockfd; 
char hname[128]={0};
uint8_t  buffer[MAXLINE]; 
char *hello = "Hello from server"; 
struct sockaddr_in servaddr, cliaddr; 
struct hostent *hent=NULL;


char *sip=NULL;

int8_t cmd_str[1024];


int32_t make_internet_address(int8_t * hostname,int32_t port,struct sockaddr_in *addrp)
{

	struct hostent *hp;

	bzero((void*)addrp,sizeof(struct sockaddr_in));


	hp = gethostbyname(hostname);

	if(hp == NULL)
		return -1;

	bcopy((void*)hp->h_addr,(void*)&addrp->sin_addr,hp->h_length);
	addrp->sin_port = htons(port);
	addrp->sin_family= AF_INET;

	return 0;


}


uint32_t vvcnt=0;
void on_timer(int signum)
{
	signal(SIGALRM,on_timer);
	make_internet_address(sip,PORT,&cliaddr);
#if 0
	if((stn = sendto(sockfd,bqr_rp,sizeof(bqr_rp),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
	{
		perror("udp send failed\n");
		exit(EXIT_FAILURE);		
	}
#endif
	vvcnt++;


	if(vvcnt == 100)
	{
		vvcnt=0;

		sleep(100);
	}


	//printf("hello timer\n");

}

int set_timer(uint32_t nms)
{

	struct itimerval ts;

	ts.it_interval.tv_sec = nms/1000;
	ts.it_interval.tv_usec = (nms%1000)*1000L;


	ts.it_value.tv_sec = nms/1000;
	ts.it_value.tv_usec = (nms%1000)*1000L;


	return setitimer(ITIMER_REAL,&ts,NULL);
}

//=========================================================================================
//

uint8_t list_array[1024][4]={0};

void *read_udp(void *arg_r)
{


	int n=0;
	int len=0; 
	uint32_t bid=0;
	uint32_t acnt=0;
	uint32_t bcnt=0;
	uint32_t ccnt=0;
	uint32_t vcnt=0;


	len = sizeof(cliaddr);  //len is value/resuslt 


	FILE *fp;
	fp = fopen("object-list.log","w");


	if(fp == NULL)
	{

		printf("failed open object-list.log");
		exit(EXIT_FAILURE);

	}




	while(1)
	{
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, &len); 
		//n = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, sizeof(struct sockaddr)); 



		//printf("==========rec len is %d\n",n);
		//printf("\n==ip %s\n",(char*)inet_ntoa(cliaddr.sin_addr));




		printf("\n==rec len is %d\n",n);
		printf("\n==buffer is %s\n",buffer);



#if 0
		if((stn = sendto(sockfd,segment_ack,sizeof(segment_ack),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
		{
			perror("udp send failed\n");
			exit(EXIT_FAILURE);		
		}
#endif



		if(strcmp(buffer,"tx-quit\n") == 0)
		{
			printf("good-bye\n");
			exit(EXIT_SUCCESS);		

		}





		memset(buffer,0,sizeof(buffer));
		//		sleep(1);
	}

}


uint8_t cmd_buf[128]={0};

void *write_udp(void *arg_w)
{

	int nrcmd=0;
	int fd;
	int m=0;
	make_internet_address(sip,PORT,&cliaddr);
	fd = open("udp-fifo",O_RDONLY | O_NONBLOCK);

	while(1)
	{



		//nrcmd = read(fd,cmd_buf,sizeof(cmd_buf));
		nrcmd = read(fd,cmd_buf,PIPE_BUF);

		//printf("====== nrcmd is %d\n",nrcmd);
		//printf("cmd_buf is %s\n",cmd_buf);
		//
		//
		if(nrcmd == 0)
		{
			//	sleep(1);
		}

		if(nrcmd >0)
		{

			printf("===nrcmd is %d\r\n",nrcmd);
		}

		if(strcmp(cmd_buf,"send rv\n") == 0)
		{


			if((stn = sendto(sockfd,bqr_rp,sizeof(bqr_rp),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
			{
				perror("udp send failed\n");
				exit(EXIT_FAILURE);		
			}

			printf("-------send rv\n");
			m++;
#if 0
			if(m>100)
				exit(0);
#endif
			//	sleep(3);

		}


		if(strcmp(cmd_buf,"send rol\n") == 0)
		{

			//printf("-------send rol\n");


		}



		memset(cmd_buf,0,sizeof(cmd_buf));
		//sleep(1);

	}

}


//=========================================================================================

int main(int argc, char* argv[])
{    

#if 1
	if(argc <2)
	{

		printf("err:parameters\n");
		exit(EXIT_FAILURE);
	}
#endif

	sip = argv[2];

	gethostname(hname,sizeof(hname));
	hent = gethostbyname(hname);

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{ 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 


	int optval =1;
	//setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST|SO_REUSEADDR,&optval,sizeof(int));

	struct timeval timeout;
	timeout.tv_sec = 6;
	timeout.tv_usec = 0;
	//setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));

	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 


	//const char localip[]="192.168.2.10";
	const char localip[]="127.0.0.1";

	// Filling server information 
	servaddr.sin_family    = AF_INET; // IPv4 
	//servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
//	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_addr.s_addr = inet_addr(localip); 
	servaddr.sin_port = htons(PORT); 
	//servaddr.sin_port = PORT; 

	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 


#if 0
	set_timer(atoi(argv[1]));
	signal(SIGALRM,on_timer);
#endif

	memset(buffer,0,sizeof(buffer));

	pthread_t thread_id_read;
	pthread_t thread_id_write;
	pthread_create(&thread_id_read,NULL,read_udp,NULL);
	pthread_create(&thread_id_write,NULL,write_udp,NULL);



	pthread_join(thread_id_read,NULL);
	pthread_join(thread_id_write,NULL);


	printf("after thread\r\n");


	exit(0);


	//==================================================================================================================
#if 0
	int fpid;
	int n=0;
	fpid = fork();
	if(fpid == -1)
	{
		perror("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if(fpid == 0)
	{

		//execl("./myudp-tx.exe","myudp-tx.exe",(char*)0);
#if 1
		struct timespec tp;
		tp.tv_sec =0;
		tp.tv_nsec =500000;
		int cnt=0;	
		make_internet_address(sip,PORT,&cliaddr);
		//make_internet_address("192.168.2.22",PORT,&cliaddr);
		//

#if 0
		if((stn = sendto(sockfd,req_read_object_list,sizeof(req_read_object_list),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
		{
			perror("udp send failed\n");
			exit(EXIT_FAILURE);		
		}

		sleep(300);
#endif

		sleep(3);

		printf("start sending\n");
		set_timer(atoi(argv[1]));
		signal(SIGALRM,on_timer);
		while(1);
#endif

	}


#endif
	//============================================================================================================================================








	//===========================================================================================================================================
#if 0
	char *ts="hello";
	int xmcnt=0;
	int rcnt=0;
	uint32_t bid=0;
	uint32_t acnt=0;
	uint32_t bcnt=0;
	uint32_t ccnt=0;
	uint32_t vcnt=0;
	while(1)
	{
#if 1
		rcnt = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, &len); 
		//n = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, sizeof(struct sockaddr)); 

		printf("\n==ip %s\n",(char*)inet_ntoa(cliaddr.sin_addr));
		printf("\n==rec len is %d\n",rcnt);


		if(buffer[12]== 0xc4 && buffer[13] == 0x02)
		{
			bid=(uint32_t)(buffer[14]<<16|buffer[15]<<8|buffer[16]);


			if(bid == 4194302)
			{
				acnt++;
				printf("I am %d\t%d\n",bid,acnt);
			}

			if(bid == 12)
			{
				bcnt++;
				printf("I am %d\t%d\n",bid,bcnt);
			}
			if(bid == 1000)
			{
				ccnt++;
				printf("I am %d\t%d\n",bid,ccnt);
			}


			printf("I am %d\n",bid);
			bid=0;

		}
#endif

		if(buffer[10]== 0x10 && buffer[11] == 0x08)
		{

			//printf("I am 5006\n");
		}

		if(strcmp(buffer,"whois\n") == 0)
		{

			//printf("I am: %d\n",1009);
			//printf("%s\r\n","world");
			//write(pfd[1],ts,strlen(ts));
		}


		if(buffer[16] == 0x3e  && buffer[27]==0x3f)
		{
			vcnt++;

			printf("%c%c%c%c%c%c%c\t%d\n",buffer[20],buffer[21],buffer[22],buffer[23],buffer[24],buffer[25],buffer[26],vcnt);
		}


		if(strcmp(buffer,"tx-quit\n") == 0)
		{
			printf("good-bye\n");
			exit(EXIT_SUCCESS);		

		}





		memset(buffer,0,sizeof(buffer));
		//	sleep(1);
	}

#endif
//======================================================================================================================================










}
