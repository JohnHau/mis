#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc,char*argv[])
{


	int fd;
	char *myfifo="/tmp/myfifo";
	mkfifo(myfifo,0666);

	char arr1[80];
	char arr2[80];

	while(1)
	{

		fd =open(myfifo,O_RDONLY);


		read(fd,arr1,sizeof(arr1));


		printf("User2: %s\n",arr1);


		close(fd);
		exit(EXIT_SUCCESS);

	}



	return 0;

}
