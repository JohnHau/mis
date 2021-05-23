#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include"ASC8.h"

void read_ASC16(int key, unsigned char *buf)
{

	unsigned int handle;
	unsigned int address;
//	handle=open("ASC16",O_RDONLY|O_BINARY);
	handle=open("ASC16",O_RDONLY);
	if(handle < 0)
		perror("open ASC16 error\n");

	address=key*16;
	lseek(handle,address,SEEK_SET);
	read(handle,buf,16);
	close(handle);



}



void read_ASC8(int key, unsigned char *buf)
{
	memcpy(buf,font8x8_basic+key,8);
}


void show_ASC8(uint8_t *buf)
{
	//for(int i=0;i<16;i++)
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if((buf[i]>>7-j)&0x01)
			{
				printf("%c ",'1');
			}
			else
			{

				printf("%c ",'0');
			}		


		}
		printf("\n");
	}




}

void show_ASC16(uint8_t *buf)
{
	for(int i=0;i<16;i++)
	//for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if((buf[i]>>7-j)&0x01)
			{
				printf("%c ",'1');
			}
			else
			{

				printf("%c ",'0');
			}		


		}
		printf("\n");
	}




}



int main(int argc,char*argv[])
{

	unsigned char buf[32]={0};
	read_ASC16('T', buf);
	show_ASC16(buf);
	printf("\n");
	read_ASC8('T', buf);
	show_ASC8(buf);

	return 0;

}
