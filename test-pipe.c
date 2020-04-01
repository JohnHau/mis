#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<unistd.h>



int main(int argc, char*argv[])
{

	int pid;
	int pip[2]={0};
	if(pipe(pip) == -1)
	{
		perror("pipe failed\n");
		exit(EXIT_FAILURE);

	}


	pid=fork();

	if(pid == -1)
	{
		perror("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		dup2(pip[0],STDIN_FILENO);
		execl("./dp.exe","dp.exe",(char*)0);

	}




	dup2(pip[1],STDOUT_FILENO);

	char*buffer="hellou\n";
	//write(STDOUT_FILENO,buffer,strlen(buffer));
	//write(pip[1],buffer,strlen(buffer));
	//
	//
	printf("%s",buffer);
	fflush(stdout);
	//fprintf(stdout,"%s\n",buffer);

	sleep(100);

	return 0;

}
