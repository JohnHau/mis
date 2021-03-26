#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t cal_crc(uint8_t *data, int len)
{
    uint8_t crc = 0x0;
    int i, j;
    for (i = 0; i < len; i++) 
    {
        crc = crc^data[i];
        for (j = 0; j < 8; j++) 
        {
            if ((crc & 0x80) != 0)
            {
              crc = (uint8_t)((crc << 1) ^ 0x07);
             
            }
            else
            { 
              crc <<= 1;
            }
        }
    }
    return crc;
} 
   


int main(int argc,char* argv[])
{

	uint8_t vcrc =0xff;

	uint8_t td[3]={0xa5,0x00,0x04};

	vcrc = cal_crc(td, 3);


	printf("vcrc is %x\n",vcrc);

}
