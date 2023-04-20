#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"uart_tios.h"

char port[32] = {0};
char jsfile[128] = {0};
char *ptrport = port;
char *ptrjsfile = jsfile;

char jsfile_buf[8*1024] = {0};
char jsfile_res[8*1024] = {0};
size_t jsfile_size =0; 

int fd = 0; 
int jsfd = 0; 

int main(int argc,char* argv[])
{

	if(argc < 3)
	{
		printf("usage %s port file\n",argv[0]);
		exit(EXIT_FAILURE);

	}

	ptrport = argv[1];//port name
        ptrjsfile = argv[2];//json file name

	// fd = init_com_port("/dev/ttyS3");
	
	jsfd = open(ptrjsfile,O_RDONLY);

	if(jsfd < 0)
	{
		perror("open jsfile failed\n");
		exit(EXIT_FAILURE);
	}


	lseek(jsfd,0,SEEK_CUR);
	jsfile_size = lseek(jsfd,0,SEEK_END);

	//printf("size is %d\n",jsfile_size);


	lseek(jsfd,0,SEEK_SET);

	read(jsfd,jsfile_buf,7*1024);
	//printf("read is %s\n",jsfile_buf);
	close(jsfd);

	//return 0;

	fd = init_com_port(ptrport);
	if(fd < 0)
	{
		perror("init_com_port failed\n");
		exit(EXIT_FAILURE);
	}




	if(write(fd,jsfile_buf,jsfile_size) < 0)
	{
		perror("port write failed\n");
		exit(EXIT_FAILURE);

	}

	printf("##################\n");
	printf("write json success\n");


	sleep(3);

#if 1
	int rn =0;
	if((rn = read(fd,jsfile_res,4*1024)) < 0)
	{
		perror("port read failed\n");
		exit(EXIT_FAILURE);
	}
	jsfile_res[rn] = '\n';
	printf("##################\n");
	printf("read json response\n");
	printf("-------------------------------\n");
	printf("%s\n",jsfile_res);
	printf("-------------------------------\n");
#endif

	return 0;
}
