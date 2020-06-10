#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
//#include <curses.h>
#include <unistd.h>
#include <aio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <netdb.h> 
  
#define PORT     0xBAC0 
//#define PORT     60542 
#define MAXLINE  1400 


#define LOG_FILE "bacnet0.log"

#define DIALOG_WIDTH 40
#define DIALOG_HEIGHT 20
#define CONTENT_WIDTH (DIALOG_WIDTH - 2)

uint8_t bqr_whois[]={
		0x81,0x0a,0x00,0x0c,0x01,0x20,
		0xff,0xff,0x00,0xff,0x10,0x08

};


uint8_t brp_im[]={
		0x81,0x0b,0x00,0x19,0x01,0x20,0xff,0xff,0x00,0xff,0x10,0x00,0xc4,0x02,0x00,0x03,
		0xf1,0x22,0x04,0x00,0x91,0x03,0x22,0x01,0x04
};

uint8_t bqr_rp[]={
	0x81,0x0a,0x00,0x11,0x01,0x04,
	0x00,0x03,0x00,0x0c,0x0c,0x02,
	//0x3f,0xff,0xfe,0x19,0x2c
	0x00,0x27,0x19,0x19,0x2c
	//0x00,0x03,0xe8,0x19,0x2c
	//0x00,0x03,0xf0,0x19,0x2c


};


extern int32_t make_internet_address(int8_t * hostname,int32_t port,struct sockaddr_in *addrp);

int sockfd; 
char hname[128]={0};
uint8_t  buffer[MAXLINE]; 
char *hello = "Hello from server"; 
struct sockaddr_in servaddr, cliaddr; 
struct hostent *hent=NULL;


char *sip=NULL;


int stn=0;



// a simple log function, works similar to printf
void bacnet0_log(const char *format, ... ) 
{
	va_list args; // argument list
	static FILE *logfile = NULL; // file pointer to the logfile
	char *fformat; // the modified format of the string which will be written to the logfile
	int length; // length of the format

	if(!(format == NULL && logfile == NULL)) {
		// open the logfile if not already opened
		if(logfile == NULL) {
			logfile = fopen(LOG_FILE, "w");
			// if that doesn't work exit with an error message
			if(logfile == NULL) {
				fprintf(stderr, "Cannot open logfile %s\n", LOG_FILE);
				exit(EXIT_FAILURE);
			}
		}

		// if NULL is given as format, close the opened file
		if(format != NULL) {
			// increase length by 2 (for \n\0
			length = strlen(format) + 2;
			// allocate memory
			fformat = malloc(sizeof(char) * length);
			// copy the format over
			strncpy(fformat, format, length - 2);
			// append \n\0
			//fformat[length - 2] = '\n';
			fformat[length - 2] = '\0';
			fformat[length - 1] = '\0';

			// get the rest of the arguments
			va_start(args, format);

			// use vfprintf() to 
			vfprintf(logfile, fformat, args); 
			// forces the logmessage to be written into the file right now
			fflush(logfile);

			va_end(args);

			// free the allocated memory for the format string
			free(fformat);
		} 
		else 
		{
			// close the logfile
			fclose(logfile);
		}
	}
}



#if defined(UBUNTU) 
void enable_kbd_signals(void)
{

	int fd_flags;

	fcntl(0,F_SETOWN,getpid());
	fd_flags = fcntl(0,F_GETFL);

	fcntl(0,F_SETFL,(fd_flags|O_ASYNC));
	//fcntl(0,F_SETFL,(fd_flags|O_RSYNC));

}
#endif



#if 0
struct aiocb  kbcbuf;
void setup_aio_buffer(void)
{

	static char input[1];

	kbcbuf.aio_fildes = 0;
	kbcbuf.aio_buf = input;
	kbcbuf.aio_nbytes = 1;
	kbcbuf.aio_offset = 0;


	kbcbuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
	kbcbuf.aio_sigevent.sigev_signo = SIGIO;



}
#endif

int8_t cmd_str[1024];

#if defined(UBUNTU) 
void on_input(int signum)
{

	fgets(cmd_str,128,stdin);
	printf("cmd_str is %s\n",cmd_str);

	if(strcmp(cmd_str,"quit\n") == 0)
	{

		exit(EXIT_SUCCESS);
	}

	if(strcmp(cmd_str,"whois\n") ==0)
	{
		make_internet_address("192.168.0.255",PORT,&cliaddr);
		if(sendto(sockfd,bqr_whois,sizeof(bqr_whois),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr)) == -1)
		{
			perror("udp  send failed\n");
			exit(EXIT_FAILURE);		

		}



	}


	memset(cmd_str,0,sizeof(cmd_str));
}

#endif



#if 0
void on_input(int signum)
{

	int c;
	char *cp = (char*)kbcbuf.aio_buf;/*cast to char*/

	if(aio_error(&kbcbuf) != 0)
	{
		perror("reading failed");
	}
	else
	{
		if(aio_return(&kbcbuf) == 1)
		{
			c=*cp;


			if(c == 'q')
			{
				printf("that is it\n");
				exit(EXIT_SUCCESS);

			}

		}

		aio_read(&kbcbuf);

	}

}
#endif

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
//	make_internet_address("192.168.0.255",PORT,&cliaddr);
		//make_internet_address("192.168.1.196",PORT,&cliaddr);
		//make_internet_address("192.168.1.208",PORT,&cliaddr);
		//make_internet_address(argv[2],PORT,&cliaddr);
		make_internet_address(sip,PORT,&cliaddr);
		//if((stn = sendto(sockfd,bqr_whois,sizeof(bqr_whois),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
		if((stn = sendto(sockfd,bqr_rp,sizeof(bqr_rp),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
		{
			perror("udp send failed\n");
			exit(EXIT_FAILURE);		
		}
		vvcnt++;


		if(vvcnt == 100)
		{
			vvcnt=0;

			sleep(100);
		}



		//printf("udp send ok: %d\n",stn);

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



int main(int argc, char* argv[])
{    


	if(argc <2)
	{

		printf("err:parameters\n");
		exit(EXIT_FAILURE);
	}

	sip = argv[2];
	
#if 0
	int sockfd; 
	char hname[128]={0};
	uint8_t  buffer[MAXLINE]; 
	char *hello = "Hello from server"; 
	struct sockaddr_in servaddr, cliaddr; 
	struct hostent *hent=NULL;
#endif


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


	const char localip[]="192.168.2.10";

	// Filling server information 
	servaddr.sin_family    = AF_INET; // IPv4 
	//servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	//servaddr.sin_addr.s_addr = inet_addr(localip); 
	servaddr.sin_port = htons(PORT); 
	//servaddr.sin_port = PORT; 

	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	int len, n; 
	len = sizeof(cliaddr);  //len is value/resuslt 



#if defined(UBUNTU) 
	void on_input(int);
	signal(SIGIO,on_input);
	enable_kbd_signals();
#endif
	//	setup_aio_buffer();
	//	aio_read(&kbcbuf);

	memset(buffer,0,sizeof(buffer));


	int fpid;
	fpid = fork();
	if(fpid == -1)
	{
		perror("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if(fpid == 0)
	{

		//execl("./myudp-tx",0);
		//execl("./myudp-tx.exe","myudp-tx.exe",(char*)0);
		//
		//
#if 1
		struct timespec tp;
		tp.tv_sec =0;
		tp.tv_nsec =500000;
		int cnt=0;	
		//make_internet_address("192.168.2.3",PORT,&cliaddr);
		//make_internet_address("192.168.2.16",PORT,&cliaddr);
		//make_internet_address("192.168.1.196",PORT,&cliaddr);
		//make_internet_address("192.168.1.208",PORT,&cliaddr);
		//make_internet_address(argv[2],PORT,&cliaddr);
		make_internet_address(sip,PORT,&cliaddr);
		//make_internet_address("192.168.2.22",PORT,&cliaddr);
		sleep(3);
		printf("start sending\n");
		//set_timer(10);
		set_timer(atoi(argv[1]));
		signal(SIGALRM,on_timer);
		while(1);
		while(1)	
		{
			if((stn = sendto(sockfd,bqr_rp,sizeof(bqr_rp),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
			{
				perror("udp send failed\n");
				exit(EXIT_FAILURE);		
			}

			bqr_rp[8]++;
			printf("hello udp\n");
			nanosleep(&tp,NULL);
			cnt++;

			if(cnt == 100)
			{
				//sleep(5);
				exit(EXIT_SUCCESS);
			}
		}
#endif

	}

	
#if 0
	//make_internet_address("192.168.0.104",PORT,&cliaddr);
	make_internet_address("192.168.0.255",PORT,&cliaddr);
	if(sendto(sockfd,bqr_whois,sizeof(bqr_whois),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr)) == -1)
	{
		perror("udp  send failed\n");
		exit(EXIT_FAILURE);		

	}
#endif

#if 0
	if(argc > 1)
	{

	printf("argc is %d\n",argc);
		if(strcmp(argv[1],"whois") == 0)
		{

			make_internet_address("192.168.0.255",PORT,&cliaddr);
			if(sendto(sockfd,bqr_whois,sizeof(bqr_whois),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr)) == -1)
			{
				perror("udp send failed\n");
			}
		}


	}
#endif

#if 0
	int pfd[2] = {0};

	if(pipe(pfd) == -1)
	{
		perror("pipe failed\n");
	}


	fpid = fork();
	if(fpid == -1)
	{
		perror("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if(fpid == 0)
	{

		if(dup2(pfd[0],STDIN_FILENO) != STDIN_FILENO)
		{
			perror("dup2 stdin failed\n");
		}

		close(pfd[1]);



		//execl("./myudp-tx",0);
		execl("./myudp-dat-processing","myudp-dat-processing",(char*)0);
	}

	if(dup2(pfd[1],STDOUT_FILENO) != STDOUT_FILENO)
	{
		perror("dup2 stdout failed\n");
	}

	close(pfd[0]);

#endif

	char *ts="hello";
	int xmcnt=0;
	uint32_t bid=0;
	uint32_t acnt=0;
	uint32_t bcnt=0;
	uint32_t ccnt=0;
	uint32_t vcnt=0;
	while(1)
	{
		//pause();
#if 1
		//	printf("waiting on port %d\n",PORT);
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, &len); 
		//	printf("recvfrom timeout\n");
		//	printf("buffer is %s\n",buffer);
		printf("\n==ip %s\n",(char*)inet_ntoa(cliaddr.sin_addr));


#if 0

		printf("\nrevision start\n");
		//for(int x=0;x<12;x++)
		for(xmcnt=0;xmcnt<n;xmcnt++)
		{
			//printf("%x ",buffer[x+16]);
			printf("%x ",buffer[xmcnt]);
		}
		printf("\nrevision end\n");
		//printf("revision is %s\n",buffer);
#endif






		//buffer[n] = '\0'; 
		//	printf("Client : %s\n", buffer); 
		//printf("buffer is %s\n",buffer);

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

			//	printf("I am %d\n",1009);
			//printf("I am %d\n",(uint32_t)(buffer[14]<<16|buffer[15]<<8|buffer[16]));
			//printf("%s %d\n","hello",23);
			//printf("%s\r\n","hello");
			//write(pfd[1],ts,strlen(ts));
#if 0
			time_t it;
			time(&it);
			int8_t * tstr = ctime(&it);
			tstr[strlen(tstr)-1]='\0';
			bacnet0_log("%s\n",tstr);
			//bacnet0_log("I am %d\n",1009);
			bacnet0_log("I am %d\n",(uint32_t)(buffer[14]<<16|buffer[15]<<8|buffer[16]));
			//time(&it);
			//bacnet0_log("%s\tI am %d\n",(uint32_t)(buffer[14]<<16|buffer[15]<<8|buffer[16]),ctime(&it));
#endif

		}
#endif

		if(buffer[10]== 0x10 && buffer[11] == 0x08)
		{

			//printf("I am 5006\n");
		}

		//if(buffer[5] == 0x20)
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





		//if(sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr)) == -1)
		//if(sendto(sockfd,brp_im,sizeof(brp_im),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr)) == -1)




#if 0
		if(strcmp(buffer,"whois\n") == 0)
		{
			printf("whois\n");
			make_internet_address("192.168.0.255",PORT,&cliaddr);
			if(sendto(sockfd,bqr_whois,sizeof(bqr_whois),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr)) == -1)
			{
				perror("udp send failed\n");
				exit(EXIT_FAILURE);		
			}

		}
#endif




		if(strcmp(buffer,"tx-quit\n") == 0)
		{
			printf("good-bye\n");
			exit(EXIT_SUCCESS);		

		}

		memset(buffer,0,sizeof(buffer));
		//	sleep(1);
	}
}
