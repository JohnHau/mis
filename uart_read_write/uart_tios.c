#include <stdio.h>      
#include <stdlib.h>    
#include <string.h>       
#include <unistd.h>      
#include <sys/types.h>   
#include <sys/stat.h>  
#include <fcntl.h>      
#include <termios.h>   
#include <errno.h>       
#include <getopt.h>   
#include <time.h>     
#include <sys/select.h>    
#include "uart_tios.h"

int setOpt(int fd)
{
    struct termios newtio, oldtio;

    if (tcgetattr(fd, &oldtio) != 0)
    {
        perror("SetupSerial 1");
        return -1;
    }

    bzero(&newtio, sizeof(newtio));   

    //CLOCAL--忽略 modem 控制线,本地连线, 不具数据机控制功能, CREAD--使能接收标志
    newtio.c_cflag |= CLOCAL | CREAD; 

    // 设置数据位数
    // 清数据位标志
    newtio.c_cflag &= ~CSIZE;   

    //8 bits
    newtio.c_cflag |= CS8;

    //设置校验位
    //无校验
    newtio.c_cflag &= ~PARENB;

    // 设置停止位
    // 1 stop bit:
    newtio.c_cflag &= ~CSTOPB;


    // 设置波特率 B2400/B4800/B9600/B19200/B38400/B57600/B115200/B230400
    //cfsetispeed(&newtio, B115200);
    //cfsetospeed(&newtio, B115200);
    cfsetispeed(&newtio, B38400);
    cfsetospeed(&newtio, B38400);

    // 设置read读取最小字节数和超时时间
    // 读取一个字符等待1*(1/10)s
    newtio.c_cc[VTIME] = 1;

    // 读取字符的最少个数为1
    newtio.c_cc[VMIN] = 1; 

    tcflush(fd,TCIFLUSH); //清空缓冲区

    //激活新设置
    if (tcsetattr(fd, TCSANOW, &newtio) != 0) 
    {
	    perror("SetupSerial 3");
	    return -1;
    }

    //printf("Serial set done!\n");

    return 0;

}


int32_t init_com_port(char* uart_name)
{
	int fdSerial;

	fdSerial = open(uart_name, O_RDWR | O_NOCTTY | O_NDELAY);

	if(fdSerial < 0)
	{
		perror(uart_name);
		return -1;
	}

	// 设置串口阻塞， 0：阻塞， FNDELAY：非阻塞
	//阻塞，即使前面在open串口设备时设置的是非阻塞的

	if (fcntl(fdSerial, F_SETFL, 0) < 0) 
	{
		printf("fcntl failed!\n");
	}
	else
	{
		//printf("fcntl=%d\n", fcntl(fdSerial, F_SETFL, 0));
		 fcntl(fdSerial, F_SETFL, 0);
	}

	if (isatty(fdSerial) == 0)
	{
		perror("standard input is not a terminal device\n");
		close(fdSerial);
		return -1;
	}
	else
	{
		//printf("is a tty success!\n");
	}

	//printf("fd-open=%d\n", fdSerial);

	// 设置串口参数
	if (setOpt(fdSerial)== -1)    //设置8位数据位、1位停止位、无校验
	{
		fprintf(stderr, "Set opt Error\n");
		close(fdSerial);
		return -1;
	}

	tcflush(fdSerial, TCIOFLUSH);    //清掉串口缓存
	fcntl(fdSerial, F_SETFL, 0);    //串口阻塞

	//printf("init_com_port() end\n");

	return fdSerial;
}


