#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <mcrypt.h>
#include <openssl/sha.h>
#include <math.h>



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
  
#define PORT     0xBAC0 
#define MAXLINE  1500 


int stn=0;

uint8_t bqr_whois[]={
		0x81,0x0a,0x00,0x0c,0x01,0x20,
		0xff,0xff,0x00,0xff,0x10,0x08

};


uint8_t brp_im[]={
		0x81,0x0b,0x00,0x19,0x01,0x20,0xff,0xff,0x00,0xff,0x10,0x00,0xc4,0x02,0x00,0x03,
		0xf1,0x22,0x04,0x00,0x91,0x03,0x22,0x01,0x04
};

uint8_t bqr_rp[32]={
	0x81,0x0a,0x00,0x11,0x01,0x04,
	0x00,0x03,0x00,0x0c,0x0c,0x02,
	0x00,0x03,0xeb,0x19,0x2c


};


uint8_t s_bqr_rp[32]={0};

#define DEVICE_IDH   bqr_rp[12]
#define DEVICE_IDM   bqr_rp[13]
#define DEVICE_IDL   bqr_rp[14]




MCRYPT td, td2;
int keysize = 16; /* 128 bits */
int buffer_len = 16;

uint8_t key1[32] = {
	0x03, 0x87, 0xb0, 0x67, 0x97,0x51, 0xa7,0x48,0x1f, 0xbe,0x5c,0x32 ,0x7c, 0x17, 0xff, 0xab,
	0x62, 0x1c, 0xc6 ,0x73, 0x3 ,0xe5, 0x28,0x40,0xf1, 0x16,0x84,0xc5 ,0x2d, 0xa4, 0x5d, 0xb3 
};

uint8_t keyAes128[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

uint8_t keyAes256[] = {
	                   'a','a','a','a','a','a','a','a','a','a','a','a','a', 'a','a','a',
	                   'a','a','a','a','a','a','a','a','a','a','a','a','a', 'a','a','a',
};




uint8_t plainAes128[] = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};

uint8_t cipherAes128[] = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97};

uint8_t ive[] =  {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

uint8_t iven[] = {
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35
};

uint8_t plainAes256[] = {
	                   'v','v','a','a','a','a','a','a','a','a','a','a','a', 'a','a','a',
	                   'a','a','a','a','a','a','a','a','a','a','a','a','a', 'a','a','a',
};

uint8_t cipherAes256[] = {
	0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
	0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97
};




int encrypt( void* buffer, int buffer_len, /* Because the plaintext could include null bytes*/ char* IV, char* key, int key_len )
{
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	//MCRYPT td = mcrypt_module_open("rijndael-256", NULL, "cbc", NULL);
	//MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "ecb", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 ){return 1;}

	mcrypt_generic_init(td, key, key_len, IV);
	mcrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);

	return 0;
}

int decrypt( void* buffer, int buffer_len, char* IV, char* key, int key_len )
{
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 ){return 1;}

	mcrypt_generic_init(td, key, key_len, IV);
	mdecrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);

	return 0;
}


int mencrypt( void* buffer, int buffer_len, /* Because the plaintext could include null bytes*/ char* IV, char* key, int key_len )
{
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "ecb", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 ){return 1;}

	mcrypt_generic_init(td, key, key_len, NULL);
	mcrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);

	return 0;
}


int xmain()
{

	//buffer = calloc(1, buffer_len);
	//strncpy(buffer, plaintext, buffer_len);
	//strncpy(buffer, plainAes128, buffer_len);

	//printf("==C==\n");
	//printf("plain:   %s\n", plaintext);
	//	encrypt(buffer, buffer_len, IV, key, keysize); 
	//encrypt(buffer, buffer_len, ive, keyAes128, keysize); 

	//keysize = 32;
	//encrypt(buffer, buffer_len, ive, keyAes256, keysize); 
	//mencrypt(buffer, buffer_len, NULL, keyAes128, keysize); 
	


	//printf("cipher:  "); display(buffer , buffer_len);
	//decrypt(buffer, buffer_len, IV, key, keysize);
	//printf("decrypt: %s\n", buffer);

	return 0;
}























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
uint32_t rv_cnt =0;


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

#if 0
		//		printf("==========rec len is %d\n",n);

		printf("rec data is \r\n");
		for(int i=0;i<n;i++)
		{

			printf("0x%02x ",buffer[i]);

			if((i + 1)%8 == 0)
				printf("\r\n");

		}

		printf("\r\n");

#endif


		//printf("==========rec len is %d\n",n);
		//printf("\n==ip %s\n",(char*)inet_ntoa(cliaddr.sin_addr));




		//printf("\n==rec len is %d\n",n);


		if(buffer[12]== 0xc4 && buffer[13] == 0x02)
		{
			bid=(uint32_t)(buffer[14]<<16|buffer[15]<<8|buffer[16]);

#if 0
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

#endif
			printf("I am %d\n",bid);
			bid=0;

		}
#if 0
		if(buffer[10]== 0x10 && buffer[11] == 0x08)
		{

			//printf("I am 5006\n");
		}
#endif



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


		if(strcmp(cmd_buf,"send rv\n") == 0)
		{


			if((stn = sendto(sockfd,bqr_rp,sizeof(bqr_rp),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
			{
				perror("udp send failed\n");
				exit(EXIT_FAILURE);		
			}

			//	printf("-------send rv\n");
			m++;
#if 0
			if(m>100)
				exit(0);
#endif
			//	sleep(3);

		}



		memset(cmd_buf,0,sizeof(cmd_buf));
		//sleep(1);

	}

}


//=========================================================================================
//msg='a','b','c'
//sha256=ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad



uint8_t hsab[32]={0};
uint8_t sab[]={

'a','b','c'



	/*
	       0x94, 0x00, 0xa8, 0x4a, 0x0f,0x1e, 0x99, 0x1c, 0x9d, 
	       0xd2, 0xd1, 0x83, 0x90, 0x4a,0xfe, 0xbd, 0x21, 0x10, 
	       0x18, 0x52, 0x7c, 0xce, 0xcd,0x62, 0x08, 0x83, 0xac,
	       0xcd, 0x36, 0x57, 0xcc, 0x11,0x00, 0x73, 0xda, 0xd3, 
	       0x0c, 0x16, 0xbb, 0x82, 0xe2,0x87, 0x34, 0xef, 0x98,
	       0x62, 0x96, 0x2e, 0xa8, 0xaf,0x09, 0x6f, 0xa9, 0x58,
	       0x07, 0xfe, 0x89, 0x8f, 0x40,0x6e, 0xfa, 0xfc, 0xb4,
	       0xb7, 0x8b, 0x93, 0xd4, 0x8b,0x1b, 0x63, 0xe7, 0xf9, 
	       0x36, 0x90, 0x09, 0x50, 0x71,0x6d, 0x24, 0x48, 0xd2,
	       0x3d, 0x65, 0xfe, 0x4b, 0xd7,0xff, 0xb4, 0xed, 0xf4, 
	       0x9c, 0x36 ,0x1b, 0x24, 0xe6,0xf5, 0x6e, 0x96, 0xec,
	       0x1a, 0x89, 0x1b, 0xcf, 0xf7,0x63, 0xb4, 0xaa, 0x4a, 
	       0x5e, 0xc3, 0x9d, 0x01, 0xb8,0x63, 0x53 ,0xe8, 0x39,
	       0x5f, 0x1e, 0xf8, 0x4a, 0x99,0xb1, 0x1d, 0x0b ,0x80,
	       0xda ,0x35, 0x29 ,0x68, 0xe6,0xe7, 0x0e, 0xb0, 0x48, 
	       0xc9, 0x92 ,0x87, 0x73, 0x18,0x52, 0x3b, 0x0c, 0x55,
	       0x7f ,0xb2, 0xbe, 0x30 ,0x1c,0x4a, 0x06, 0x19, 0xb9,
	       0xc4, 0xec, 0x18, 0xab, 0x90,0x1e, 0x7e, 0xa6, 0xe9,
	       0x41, 0xe3, 0xfe, 0xea ,0xf6,0xa3, 0xdc, 0x54, 0x3f, 
	       0x1b ,0x3f ,0x0f ,0xf3, 0x17,0x52, 0x08, 0xb8 ,0x00,
	       0x8c, 0xb7, 0xf4, 0x0f, 0x22,0x12, 0x24, 0xb9, 0x3d,
	       0xa2 ,0x39, 0x4, 0x87, 0x1d;
	       */

};



int main(int argc, char* argv[])
{    


	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, sab, 3);
	SHA256_Final(hsab, &ctx);


	printf("==C==\n");
	//encrypt(buffer, buffer_len, ive, keyAes128, keysize); 
	keysize = 32;
	//encrypt(plainAes256, 32, iven, keyAes256, keysize); 
	//
	//
	memcpy(s_bqr_rp,bqr_rp,32);	
	encrypt(s_bqr_rp, 32, iven, keyAes256, keysize); 





	
	for(int is=0;is<32;is++)
	{

		printf("%02x ",plainAes256[is]);
		//printf("%c ",plainAes256[is]);
	}


	printf("\n");
	keysize = 32;
	decrypt(plainAes256, 32, iven, keyAes256, keysize);

	for(int is=0;is<32;is++)
	{

		printf("%02x ",plainAes256[is]);
		//printf("%c ",plainAes256[is]);
	}


	printf("\n");
	


#if 0
	keysize = 16;
	encrypt(plainAes128, 16, NULL, keyAes256, keysize); 
	for(int is=0;is<16;is++)
	{

		//printf("%02x ",hsab[is]);
		printf("%02x ",plainAes128[is]);
	}

#endif


	
	//mencrypt(buffer, buffer_len, NULL, keyAes128, keysize); 

	//printf("cipher:  "); display(buffer , buffer_len);
	//decrypt(buffer, buffer_len, IV, key, keysize);
	//printf("decrypt: %s\n", buffer);


#if 0
	//for(int is=0;is<32;is++)
	for(int is=0;is<16;is++)
	{

		//printf("%02x ",hsab[is]);
		printf("%02x ",plainAes128[is]);
	}


	printf("\n");

#endif
	return 0;



	if(argc <3)
	{

		printf("err:parameters\n");
		exit(EXIT_FAILURE);
	}

	sip = argv[2];
	uint32_t temp_id = atoi(argv[3]);
	DEVICE_IDL= temp_id & 0x000000ff;
	DEVICE_IDM= (temp_id & 0x0000ff00)>>8;
	DEVICE_IDH= (temp_id & 0x00ff0000)>>16;

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

}
