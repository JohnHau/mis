#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>



//gcc -D_REENTRANT -D_POSIX_C_SOURCE  thread2.c -o thread2.exe   -lpthread


void*thread_function(void*arg);

char message[] = "Hello World";

int run_now =1;






void *thread_function(void*arg)
{
int print_count2=0;

while(print_count2++ <20)
{
	if(run_now ==2)
	{
		printf("2");
		run_now = 1;

	}
	else
	{
		sleep(1);
	}
}


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



int print_count1=0;

while(print_count1++ <20)
{
	if(run_now ==1)
	{
		printf("1");
		run_now = 2;

	}
	else
	{
		sleep(1);
	}
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
