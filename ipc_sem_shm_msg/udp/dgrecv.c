#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define HOSTLEN   256
#define oops(m,x)  {perror(m);exit(x);}


int make_dgram_server_socket(int);
int get_internet_address(char*,int,int*,struct sockaddr_in*);

void say_who_called(struct sockaddr_in*);




int make_internet_address(char* hostname,int port,struct sockaddr_in *addrp)
{

#if 1
	struct hostent *hp;

	bzero((void*)addrp,sizeof(struct sockaddr_in));

	hp = gethostbyname(hostname);

	if(hp == NULL)
		return -1;

	bcopy((void*)hp->h_addr,(void*)&addrp->sin_addr,hp->h_length);

	addrp->sin_port = htons(port);
	addrp->sin_family = AF_INET;


//	addrp->sin_addr.s_addr = htonl(INADDR_ANY);
#endif




#if 0
	addrp->sin_port = htons(port);
	addrp->sin_family = AF_INET;
	addrp->sin_addr.s_addr = htonl(INADDR_ANY);

#endif



	return 0;


}


int get_internet_address(char*host,int len, int* portp,struct sockaddr_in *addrp)
{

	strncpy(host,inet_ntoa(addrp->sin_addr),len);

	*portp = ntohs(addrp->sin_port);
	return 0;

}



void say_who_called(struct sockaddr_in * addrp)
{
	char host[BUFSIZ];
	int port;

	get_internet_address(host,BUFSIZ,&port,addrp);


	printf("from: %s: %d\n",host,port);

}


#if 1
int make_dgram_server_socket(int portnum)
{

	struct sockaddr_in saddr;
	char hostname[HOSTLEN];

	int sock_id;

	//sock_id = socket(PF_INET,SOCK_DGRAM,0);//get a socket
	sock_id = socket(AF_INET,SOCK_DGRAM,0);//get a socket

	if(sock_id == -1)
	{
		fprintf(stderr,"error socket\n");
		return -1;
	}
#if 1
	printf("sock_id is %d\n",sock_id);
	gethostname(hostname,HOSTLEN);

	printf("hostname is %s\n",hostname);

	make_internet_address(hostname,portnum,&saddr);
	//make_internet_address("127.0.0.1",portnum,&saddr);
#endif


#if 0
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_port = htons(portnum);
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

#endif




	if(bind(sock_id,(struct sockaddr*)&saddr,sizeof(saddr)) != 0)
	{
		fprintf(stderr,"binding failed\n");
		return -1;
	}
	return sock_id;


}

#endif


#if 0
int make_dgram_server_socket(int portnum)
{

	struct sockaddr_in saddr;
	int sock_id;

	//sock_id = socket(PF_INET,SOCK_DGRAM,0);//get a socket
	sock_id = socket(AF_INET,SOCK_DGRAM,0);//get a socket

	if(sock_id == -1)
	{
		fprintf(stderr,"error socket\n");
		return -1;
	}
	
	memset(&saddr,0,sizeof(saddr));
	//saddr.sin_port = htons(portnum);
	saddr.sin_port = htons(8888);

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);


	if(bind(sock_id,(struct sockaddr*)&saddr,sizeof(saddr)) != 0)
	{
		fprintf(stderr,"binding failed\n");
		return -1;
	}



	printf("sock_id is %d\n",sock_id);
	return sock_id;


}
#endif









int main(int ac, char*av[])
{

	int port;
	int sock;
	char buf[BUFSIZ];
	ssize_t msglen;
	struct sockaddr_in saddr;
	socklen_t saddrlen;


#if 0
	char hn[HOSTLEN];
	gethostname(hn,HOSTLEN);


	printf("host name is %s\n",hn);
	return 1;
#endif


	if(ac ==1 || (port = atoi(av[1])) <= 0)
	{

		fprintf(stderr,"usage: dgrecv  portnumber\n");
		exit(EXIT_FAILURE);
	}


/*get a socket and assign it a port number*/

	if((sock = make_dgram_server_socket(port)) == -1)
	{
		oops("can not make socket",2);

	}

	printf("sock is %d\n",sock);

	saddrlen = sizeof(saddr);


	while((msglen = recvfrom(sock,buf,BUFSIZ,0,(struct sockaddr*)&saddr,&saddrlen)) > 0)
	//msglen = recvfrom(sock,buf,BUFSIZ,0,(struct sockaddr*)&saddr,&saddrlen);
	{

		printf("msglen is %d\n",msglen);
		buf[msglen] = '\0';

		printf("dgrecv: got a message: %s\n",buf);
		say_who_called(&saddr);

	//break;
	}


	close(sock);


	return 0;


}
