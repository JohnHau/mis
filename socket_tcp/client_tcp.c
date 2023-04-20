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


	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("socket failed\n");
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

	char cbuf[32] = {0};

	fd_set rfds;
	int retval;

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 5000;
	
	while(1)
	{

		FD_ZERO(&rfds);
		FD_SET(sockfd,&rfds);

		retval = select(sockfd + 1,&rfds,NULL,NULL,NULL);

		memset(cbuf,0,sizeof(cbuf));
		if(retval == -1)
		{
			perror("select error");
		}
		else if(retval)
		{
			if(FD_ISSET(sockfd,&rfds))
			{

				size_t rsize = read(sockfd,cbuf,30);

				if(rsize == 0)
				{
					printf("server fd closed\n");
					exit(EXIT_FAILURE);
				}

				printf("message is %s\n",cbuf);
			}

		}
		else
		{
			printf("select nnnnnn\n");
		}

	}



	return 0;

}
