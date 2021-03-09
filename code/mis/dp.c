#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>

#include<unistd.h>



int main(int argc, char* argv[])
{

	char msg[1024]={0};
	scanf("%s",msg);
	//read(STDIN_FILENO,msg,sizeof(msg));

	printf("the message is %s\n",msg);

	return 0;



}
