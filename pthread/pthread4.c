#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>



//gcc -D_REENTRANT -D_POSIX_C_SOURCE  thread2.c -o thread2.exe   -lpthread


void*thread_function(void*arg);

sem_t bin_sem;

#define WORK_SIZE 1024
char work_area[WORK_SIZE];

char message[] = "Hello World";






void *thread_function(void*arg)
{


	sem_wait(&bin_sem);
	while(strncmp("end",work_area,3) != 0)
	{
		printf("You input %d characters\n",strlen(work_area) -1);
		

		sem_wait(&bin_sem);


	}
	pthread_exit("Thank you for the CPU time\n");

}




int main(int argc ,char* argv[])
{

	int res;
	pthread_t a_thread;
	void* thread_result;



	res = sem_init(&bin_sem,0,0);
	if(res != 0)
	{
		perror("sem init failed\n");
		exit(EXIT_FAILURE);
	}





	res = pthread_create(&a_thread,NULL,thread_function,(void*)message);

	if(res != 0)
	{
		perror("Thread creation failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Input some text, Enter end to finish\n");

	while(strncmp("end",work_area,3) != 0)
	{
		fgets(work_area,WORK_SIZE,stdin);
		sem_post(&bin_sem);

	}




	printf("Waiting for thread t o finish ...\n");

	res = pthread_join(a_thread,&thread_result);


	if(res !=0)
	{
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);

	}


	printf("Thread joined.  it returned %s\n",(char*)thread_result);
	sem_destroy(&bin_sem);
	exit(EXIT_SUCCESS);



}
