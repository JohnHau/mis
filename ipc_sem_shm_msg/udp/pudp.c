#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>



int main(int argc,char*argv[])
{


	int sock_id;
	struct sockaddr_in saddr;


	sock_id = socket(AF_INET,SOCK_DGRAM,0);

	if(sock_id < 0 )
	{

		fprintf(stderr,"error: socket\n");
		exit(EXIT_FAILURE);
	}


	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8989);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);


	printf("sock_id is %d\n",sock_id);



	if(bind(sock_id,(struct sockaddr*)&saddr,sizeof(saddr)) != 0)
	{
		fprintf(stderr,"error: bind\n");
		exit(EXIT_FAILURE);

	}


	char buf[BUFSIZ];
	int len = sizeof(saddr);
	int msglen = recvfrom(sock_id,buf,BUFSIZ,0,(struct sockaddr*)&saddr,&len);

	buf[msglen]='\0';


	printf("msglen is %d\n",msglen);
	printf("buf is %s\n",buf);

	return 0;


}
