#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>

#define MAX_TEXT  512


struct my_msg_st
{
	long int my_msg_type;
	char some_text[BUFSIZ];

};



int main(int argc,char*argv[])
{

	int running =1;
	int msgid;

	char buffer[BUFSIZ];

	struct my_msg_st  some_data;
	long int msg_to_receive =0;

	msgid = msgget((key_t)1234,0666 | IPC_CREAT);

	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error: %d\n",errno);
		exit(EXIT_FAILURE);

	}


	printf("msg id is %d\n",msgid);


	while(running)
	{
		printf("Enter some text: ");
		fgets(buffer,BUFSIZ,stdin);
		some_data.my_msg_type =1;
		strcpy(some_data.some_text,buffer);

		if(msgsnd(msgid,(void*)&some_data,MAX_TEXT,0) == -1)
		{
			fprintf(stderr,"msgsnd failed\n");
			exit(EXIT_FAILURE);

		}


		if(strncmp(buffer,"end",3) == 0)
		{
			running =0;

		}

	}

#if 0
	if(msgctl(msgid,IPC_RMID,0) == -1)
	{
		fprintf(stderr,"msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);

	}

#endif
	exit(EXIT_SUCCESS);


}
