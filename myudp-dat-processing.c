#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
//#include <curses.h>
#include <unistd.h>
#include <aio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <netdb.h> 
  
#define PORT     0xBAC0 
#define MAXLINE  1500 


#define LOG_FILE "bacnet0.log"

#define DIALOG_WIDTH 40
#define DIALOG_HEIGHT 20
#define CONTENT_WIDTH (DIALOG_WIDTH - 2)




// a simple log function, works similar to printf
void bacnet0_log(const char *format, ... ) 
{
	va_list args; // argument list
	static FILE *logfile = NULL; // file pointer to the logfile
	char *fformat; // the modified format of the string which will be written to the logfile
	int length; // length of the format

	if(!(format == NULL && logfile == NULL)) {
		// open the logfile if not already opened
		if(logfile == NULL) {
			logfile = fopen(LOG_FILE, "w");
			// if that doesn't work exit with an error message
			if(logfile == NULL) {
				fprintf(stderr, "Cannot open logfile %s\n", LOG_FILE);
				exit(EXIT_FAILURE);
			}
		}

		// if NULL is given as format, close the opened file
		if(format != NULL) {
			// increase length by 2 (for \n\0
			length = strlen(format) + 2;
			// allocate memory
			fformat = malloc(sizeof(char) * length);
			// copy the format over
			strncpy(fformat, format, length - 2);
			// append \n\0
			//fformat[length - 2] = '\n';
			fformat[length - 2] = '\0';
			fformat[length - 1] = '\0';

			// get the rest of the arguments
			va_start(args, format);

			// use vfprintf() to 
			vfprintf(logfile, fformat, args); 
			// forces the logmessage to be written into the file right now
			fflush(logfile);

			va_end(args);

			// free the allocated memory for the format string
			free(fformat);
		} 
		else 
		{
			// close the logfile
			fclose(logfile);
		}
	}
}


int val=0;
char mystr[1024]={0};
int main(int argc, char* argv[])
{    

#if 1
	if(setvbuf(stdin,NULL,_IOLBF,0) != 0)
	{
		perror("setvbuf failed\n");
	}
#endif

	while(1)
	{

		scanf("%s %d",mystr,&val);
		printf("dat is %s %d\n",mystr,val);
		//fgets(mystr,strlen(mystr),stdin);

		//read(STDIN_FILENO,mystr,sizeof(mystr));
		if(strcmp(mystr,"quit") == 0)
		{
			bacnet0_log("%s\n",mystr); 
			exit(EXIT_SUCCESS);

		}
		//fgets(mystr,sizeof(mystr),stdin);
		//read(STDIN_FILENO,mystr,sizeof(mystr));

		//		printf("%s %d",mystr,val+1);
		bacnet0_log("%s\n",mystr); 

		memset(mystr,0,sizeof(mystr));


	}
}
