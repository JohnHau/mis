#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>



int main(int argc, char* argv[])
{

	int data_processed;
	int file_pipes[2];
	int xfile_pipes[2];
	int sts =0;

	int nread = 0;

	const char some_data[] = "123";
	char buffer[BUFSIZ +1];
	char rbuffer[BUFSIZ +1];
	pid_t fork_result;

	memset(buffer,'\0',sizeof(buffer));


	if(pipe(file_pipes) == 0 && pipe(xfile_pipes) == 0)
	{

		fork_result = fork();

		if(fork_result == (pid_t)-1)
		{
			fprintf(stderr,"Fork failed");
			exit(EXIT_FAILURE);
		}

		if(fork_result == 0)
		{
#if 0
			sprintf(buffer,"%d",file_pipes[0]);
			(void)execl("pipe4","pipe4",buffer,(char*)0);
#endif

			close(0);
			dup(file_pipes[0]);

			close(file_pipes[0]);
			close(file_pipes[1]);

			close(1);
			dup(xfile_pipes[1]);

			close(xfile_pipes[0]);
			close(xfile_pipes[1]);




			execlp("od","od","-c",(char*)0);



			exit(EXIT_FAILURE);
		}
		else
		{

			close(file_pipes[0]);
			data_processed = write(file_pipes[1],some_data,strlen(some_data));
			close(file_pipes[1]);
			printf("%d - wrote %d bytes\n",getpid(),data_processed);



			close(xfile_pipes[1]);
			nread = read(xfile_pipes[0],rbuffer,1024);
			close(xfile_pipes[0]);
			printf("%d - read %d bytes\n",getpid(),nread);

#if 0
			int i=0;
			for(i=0;i<nread;i++)
			{

				printf("output is %c\n",rbuffer[i]);
			}

#endif			

			//printf("output is %s\n",rbuffer);
			printf("%s\n",rbuffer);


			wait(&sts);
		}
	}

	exit(EXIT_SUCCESS);

}
