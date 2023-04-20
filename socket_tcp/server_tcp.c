#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int sockfd;

void sig_handler(int signo)
{
	if(signo == SIGINT)
	{
		printf("farewell server\n");
		exit(EXIT_FAILURE);
	}

}



int main(int argc,char* argv[])
{
	if(argc < 2)
	{
		printf("usage: %s port",argv[0]);
		exit(EXIT_FAILURE);

	}

	if(signal(SIGINT,sig_handler) == SIG_ERR)
	{
		perror("signal failed\n");
		exit(EXIT_FAILURE);
	}

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if(sockfd < 0)
	{
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[1]));
	serveraddr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
	{
		perror("bind failed\n");
		exit(EXIT_FAILURE);
	}

	if(listen(sockfd,10) < 0)
	{
		perror("listen failed\n");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in clientaddr;
	socklen_t clientaddr_len;

	while(1)
	{
		int fd = accept(sockfd,(struct sockaddr*)&clientaddr,&clientaddr_len);

		char ip[16] = {0};
		int port = 0;
		inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ip,sizeof(ip));
		port = ntohs(clientaddr.sin_port);

		printf("client ip is %s\n",ip);
		printf("client port is %d\n",port);


		for(int i=0; i< 3; i++)
		{
			time_t t = time(NULL);
			char* st = ctime(&t);
			write(fd,st,strlen(st));
			sleep(1);
		}

		close(fd);

	}

	return 0;


}
