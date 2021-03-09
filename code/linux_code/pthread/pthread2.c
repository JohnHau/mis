#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>



//gcc -D_REENTRANT -D_POSIX_C_SOURCE  thread2.c -o thread2.exe   -lpthread


void*thread_function(void*arg);

char message[] = "Hello World";






void *thread_function(void*arg)
{

	printf("thread function is running. Argument was %s\n",(char*)arg);

	sleep(3);
	strcpy(message,"Bye");

	pthread_exit("Thank you for the CPU time\n");

}




int main(int argc ,char* argv[])
{

	int res;
	pthread_t a_thread;

	void* thread_result;

	res = pthread_create(&a_thread,NULL,thread_function,(void*)message);

	if(res != 0)
	{
		perror("Thread creation failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Waiting for thread to finish ... \n");

	res = pthread_join(a_thread,&thread_result);


	if(res !=0)
	{
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);

	}


	printf("Thread joined.  it returned %s\n",(char*)thread_result);
	printf("message is now %s\n",message);

	exit(EXIT_SUCCESS);



}
