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

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

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

	char udp_buf[64] = {0};
	struct sockaddr_in clientaddr;

	socklen_t clientaddr_len;

	if(recvfrom(sockfd,udp_buf,sizeof(udp_buf),0,(struct sockaddr*)&clientaddr,&clientaddr_len) < 0)
	{
		perror("recvfrom failed\n");
		exit(EXIT_FAILURE);
	}

	printf("got message %s\n",udp_buf);

	close(sockfd);
	return 0;


}
