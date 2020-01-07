#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// a simple log function, works similar to printf
void hlog(const char *name,const char *format, ... )
{

  va_list args; // argument list
  static FILE *logfile = NULL; // file pointer to the logfile
  char *fformat; // the modified format of the string which will be written to the logfile
  int length; // length of the format

      logfile = fopen(name, "a");
      // if that doesn't work exit with an error message
      if(logfile == NULL)
      {
        //fprintf(stderr, "Cannot open logfile %s\n", LOG_FILE);
        fprintf(stderr, "Cannot open logfile %s\n", name);
        exit(EXIT_FAILURE);
      }

      // increase length by 2 (for \n\0
      length = strlen(format) + 2;
      // allocate memory
      fformat = malloc(sizeof(char) * length);
      // copy the format over
      strncpy(fformat, format, length - 2);
      // append \n\0
      fformat[length - 2] = '\n';
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
      fclose(logfile);

}



int main(int argc, char*argv[])
{

	hlog("x.log","%d\t%s\n",93,"second");
	hlog("x.log","%d\t%s\n",73,"third");

	hlog("y.log","%d\t%s\n",33,"second");
	hlog("y.log","%d\t%s\n",43,"third");

	return 0;

}