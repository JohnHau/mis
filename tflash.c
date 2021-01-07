#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>


#define SECTOR_NUM               2048
#define PAGE_NUM_PER_SECTOR      16 
#define PAGE_LEN                 256

#define TOP_ADDR                 (2048*16*256) 

uint8_t fv[SECTOR_NUM][PAGE_NUM_PER_SECTOR][PAGE_LEN]={0};
uint8_t *start_addr = &fv[0][0][0];



uint8_t flash_read_data(uint32_t addr,uint8_t* buffer,uint32_t len)
{
	if(addr < TOP_ADDR)	
	{
		uint32_t i = 0;

		while((addr + len) < TOP_ADDR)
		{
			
			buffer[i] = *(start_addr + i);
			i++;

			if(i == len)
				break;
		}

		return 1;

	}
	else
	{
		return -1;
	}

}

uint8_t rbuf[1024]={0};

int main(int argc,char*argv[])
{

	int i =0;


	flash_read_data(100,rbuf,8);


	for(i=0;i<8;i++)
		printf("value is %d\n",rbuf[i]);


}
