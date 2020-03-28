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
#define MAXLINE  1500 


#define LOG_FILE "bacnet0.log"

#define DIALOG_WIDTH 40
#define DIALOG_HEIGHT 20
#define CONTENT_WIDTH (DIALOG_WIDTH - 2)

uint32_t stn=0;
uint8_t bqr_whois[]={
//	0xba,0xc0,0xba,0xc0,0x00,0x14,0x74,0x4d,
	0x81,0x0a,0x00,0x0c,0x01,0x20,
	0xff,0xff,0x00,0xff,0x10,0x08

};


uint8_t brp_im[]={
		0x81,0x0b,0x00,0x19,0x01,0x20,0xff,0xff,0x00,0xff,0x10,0x00,0xc4,0x02,0x00,0x03,
		0xf1,0x22,0x04,0x00,0x91,0x03,0x22,0x01,0x04
};

extern int32_t make_internet_address(int8_t * hostname,int32_t port,struct sockaddr_in *addrp);

int sockfd; 
char hname[128]={0};
uint8_t  buffer[MAXLINE]; 
char *hello = "Hello from server"; 
struct sockaddr_in servaddr, cliaddr; 
struct hostent *hent=NULL;





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




void on_timer(int signum)
{
	signal(SIGALRM,on_timer);
//	make_internet_address("192.168.0.255",PORT,&cliaddr);
		if((stn = sendto(sockfd,bqr_whois,sizeof(bqr_whois),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
		{
			perror("udp send failed\n");
			exit(EXIT_FAILURE);		
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


int main(int argc, char* argv[])
{    


	//gethostname(hname,sizeof(hname));
	//hent = gethostbyname(hname);

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{ 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 


	int optval =1;
	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST|SO_REUSEADDR,&optval,sizeof(int));




#if defined(UBUNTU) 
	void on_input(int);
	signal(SIGIO,on_input);
	enable_kbd_signals();
#endif
	//	setup_aio_buffer();
	//	aio_read(&kbcbuf);

	memset(buffer,0,sizeof(buffer));




	//signal(SIGALRM,on_timer);

	//set_timer(1000);

	int ffd;
#if 0
	ffd = open("./ufifo",O_RDONLY);


	if(ffd == -1)
	{
		perror("open fifo failed\n");
		exit(EXIT_FAILURE);
	}
#endif
	
	int cnt=0;

	make_internet_address("192.168.0.255",PORT,&cliaddr);


	struct timespec tp;
	tp.tv_sec =1;
	tp.tv_nsec =0;
	while(1)
	{
		if((stn = sendto(sockfd,bqr_whois,sizeof(bqr_whois),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
		{
			perror("udp send failed\n");
			exit(EXIT_FAILURE);		
		}

		printf("hello udp\n");
		nanosleep(&tp,NULL);



	}
	while(1)
	{


		//if(sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr)) == -1)
		//if(sendto(sockfd,brp_im,sizeof(brp_im),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr)) == -1)
		if(strcmp(buffer,"whois\n") == 0)
		{
			printf("got whois\n");
			//make_internet_address("192.168.43.255",PORT,&cliaddr);
			//make_internet_address("10.78.146.1",PORT,&cliaddr);
			//make_internet_address("192.168.0.104",PORT,&cliaddr);
			make_internet_address("192.168.0.108",PORT,&cliaddr);
			//make_internet_address("192.168.0.255",PORT,&cliaddr);
			//make_internet_address("127.0.0.1",PORT,&cliaddr);

			char* test_udp_str = "hello UDP\n";
			//if((stn = sendto(sockfd,test_udp_str,strlen(test_udp_str),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
			if((stn = sendto(sockfd,bqr_whois,strlen(bqr_whois),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
			{
				perror("udp send failed\n");
				exit(EXIT_FAILURE);		
			}

			printf("udp send ok: %d\n",stn);



		}

		if(strcmp(buffer,"quit\n") == 0)
		{


			char *qt = "tx-quit\n";
			if(sendto(sockfd,qt,strlen(qt),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr)) == -1)


			{
				perror("udp send failed\n");
				exit(EXIT_FAILURE);		
			}

			printf("udp send ok\n");


			printf("good-bye\n");
			exit(EXIT_SUCCESS);		

		}



		memset(buffer,0,sizeof(buffer));
#if 0
		//make_internet_address("192.168.0.108",PORT,&cliaddr);
		//make_internet_address("192.168.0.106",PORT,&cliaddr);
		make_internet_address("192.168.0.255",PORT,&cliaddr);
		if((stn = sendto(sockfd,bqr_whois,sizeof(bqr_whois),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
		{
			perror("udp send failed\n");
			exit(EXIT_FAILURE);		
		}

		printf("udp send ok: %d\n",stn);
#endif
		//sleep(1000);

#if 0
		cnt++;
		if(cnt > 10)
			exit(EXIT_SUCCESS);
#endif
	}
}
