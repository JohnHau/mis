#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<sys/select.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int sockfd;

void sig_handler(int signo)
{
	if(signo == SIGINT)
	{
		printf("farewell client\n");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

}

int main(int argc,char* argv[])
{
	if(argc < 3)
	{
		printf("usage: %s ip port\n",argv[0]);
	}


	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	}

	int opt =1;
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt)) < 0)
	{
		perror("setsockopt failed\n");
		exit(EXIT_FAILURE);
	}


	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET,argv[1],&serveraddr.sin_addr.s_addr);

	if(connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
	{
		perror("connect failed\n");
		exit(EXIT_FAILURE);
	}

	char udp_buf[64] ="client message\n";

	if(send(sockfd,udp_buf,strlen(udp_buf),0) < 0 )
	{
		perror("send failed\n");
		exit(EXIT_FAILURE);
	}


	close(sockfd);


	return 0;

}
