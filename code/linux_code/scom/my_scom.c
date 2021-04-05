#include <stdio.h>        //标准输入输出,如printf、scanf以及文件操
#include <stdlib.h>        //标准库头文件，定义了五种类型、一些宏和通用工具函
#include <unistd.h>        //定义 read write close lseek 等Unix标准函数
#include <sys/types.h>    //定义数据类型，如 ssiz e_t off_t 等
#include <sys/stat.h>    //文件状态
#include <fcntl.h>        //文件控制定义
#include <termios.h>    //终端I/O
#include <errno.h>        //与全局变量 errno 相关的定义
#include <getopt.h>        //处理命令行参数
#include <string.h>        //字符串操作
#include <time.h>        //时间
#include <sys/select.h>    //select函数

//#define DEV_NAME    "/dev/ttymxc3"    ///< 串口设备
#define DEV_NAME    "/dev/ttyS19"    ///< 串口设备


/**@brief   设置串口参数：波特率，数据位，停止位和效验位
 * @param[in]  fd         类型  int      打开的串口文件句柄
 * @param[in]  nSpeed     类型  int     波特率
 * @param[in]  nBits     类型  int     数据位   取值 为 7 或者8
 * @param[in]  nParity     类型  int     停止位   取值为 1 或者2
 * @param[in]  nStop      类型  int      效验类型 取值为N,E,O,,S
 * @return     返回设置结果
 * - 0         设置成功
 * - -1     设置失败
 */
int setOpt(int fd, int nSpeed, int nBits, int nParity, int nStop)
{
    struct termios newtio, oldtio;

    // 保存测试现有串口参数设置，在这里如果串口号等出错，会有相关的出错信息
    if (tcgetattr(fd, &oldtio) != 0)
    {
        perror("SetupSerial 1");
        return -1;
    }

    bzero(&newtio, sizeof(newtio));        //新termios参数清零
    newtio.c_cflag |= CLOCAL | CREAD;    //CLOCAL--忽略 modem 控制线,本地连线, 不具数据机控制功能, CREAD--使能接收标志
    // 设置数据位数
    newtio.c_cflag &= ~CSIZE;    //清数据位标志
    switch (nBits)
    {
        case 7:
            newtio.c_cflag |= CS7;
        break;
        case 8:
            newtio.c_cflag |= CS8;
        break;
        default:
            fprintf(stderr, "Unsupported data size\n");
            return -1;
    }
    // 设置校验位
    switch (nParity)
    {
        case 'o':
        case 'O':                     //奇校验
            newtio.c_cflag |= PARENB;
            newtio.c_cflag |= PARODD;
            newtio.c_iflag |= (INPCK | ISTRIP);
            break;
        case 'e':
        case 'E':                     //偶校验
            newtio.c_iflag |= (INPCK | ISTRIP);
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            break;
        case 'n':
        case 'N':                    //无校验
            newtio.c_cflag &= ~PARENB;
            break;
        default:
            fprintf(stderr, "Unsupported parity\n");
            return -1;
    }
    // 设置停止位
    switch (nStop)
    {
        case 1:
            newtio.c_cflag &= ~CSTOPB;
        break;
        case 2:
            newtio.c_cflag |= CSTOPB;
        break;
        default:
            fprintf(stderr,"Unsupported stop bits\n");
            return -1;
    }
    // 设置波特率 2400/4800/9600/19200/38400/57600/115200/230400
    switch (nSpeed)
    {
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 19200:
            cfsetispeed(&newtio, B19200);
            cfsetospeed(&newtio, B19200);
            break;
        case 38400:
            cfsetispeed(&newtio, B38400);
            cfsetospeed(&newtio, B38400);
            break;
        case 57600:
            cfsetispeed(&newtio, B57600);
            cfsetospeed(&newtio, B57600);
            break;
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        case 230400:
            cfsetispeed(&newtio, B230400);
            cfsetospeed(&newtio, B230400);
            break;
        default:
            printf("\tSorry, Unsupported baud rate, set default 9600!\n\n");
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
    }
    // 设置read读取最小字节数和超时时间
    newtio.c_cc[VTIME] = 1;     // 读取一个字符等待1*(1/10)s
    newtio.c_cc[VMIN] = 1;        // 读取字符的最少个数为1

      tcflush(fd,TCIFLUSH);         //清空缓冲区
      if (tcsetattr(fd, TCSANOW, &newtio) != 0)    //激活新设置
      {
        perror("SetupSerial 3");
          return -1;
     }
      printf("Serial set done!\n");
    return 0;
}

/**@brief 串口读取函数
 * @param[in]  fd         打开的串口文件句柄
 * @param[in]  *rcv_buf 接收缓存指针
 * @param[in]  data_len    要读取数据长度
 * @param[in]  timeout     接收等待超时时间，单位ms
 * @return     返回设置结果
 * - >0      设置成功
 * - 其他      读取超时或错误
 */
int UART_Recv(int fd, char *rcv_buf, int data_len, int timeout)
{
    int len, fs_sel;
    fd_set fs_read;
    struct timeval time;

    time.tv_sec = timeout / 1000;              //set the rcv wait time
    time.tv_usec = timeout % 1000 * 1000;    //100000us = 0.1s

    FD_ZERO(&fs_read);        //每次循环都要清空集合，否则不能检测描述符变化
    FD_SET(fd, &fs_read);    //添加描述符

    // 超时等待读变化，>0：就绪描述字的正数目， -1：出错， 0 ：超时
    fs_sel = select(fd + 1, &fs_read, NULL, NULL, &time);
//    printf("fs_sel = %d\n", fs_sel);
    if(fs_sel)
    {
        len = read(fd, rcv_buf, data_len);
        return len;
    }
    else
    {
//        printf("Sorry,I am wrong!");
        return -1;
    }
}

/**@brief 串口发送函数
 * @param[in]  fd            打开的串口文件句柄
 * @param[in]  *send_buf     发送数据指针
 * @param[in]  data_len     发送数据长度
 * @return     返回结果
 * - data_len    成功
 * - -1            失败
 */
int UART_Send(int fd, char *send_buf, int data_len)
{
    ssize_t ret = 0;

    ret = write(fd, send_buf, data_len);
    if (ret == data_len)
    {
        //printf("send data is %s\n", send_buf);
        return ret;
    }
    else
    {
        printf("write device error\n");
        tcflush(fd,TCOFLUSH);
        return -1;
    }
}


/**@fn main
 * @brief main入口函数
 */
int main (int argc, char *argv[])
{
    int fdSerial;

    // 打开串口设备
    fdSerial = open(DEV_NAME, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fdSerial < 0)
    {
        perror(DEV_NAME);
        return -1;
    }



    // 设置串口阻塞， 0：阻塞， FNDELAY：非阻塞
    if (fcntl(fdSerial, F_SETFL, 0) < 0)    //阻塞，即使前面在open串口设备时设置的是非阻塞的
    {
        printf("fcntl failed!\n");
    }
    else
    {
        printf("fcntl=%d\n", fcntl(fdSerial, F_SETFL, 0));
    }




    if (isatty(fdSerial) == 0)
    {
        printf("standard input is not a terminal device\n");
        close(fdSerial);
        return -1;
    }
    else
    {
        printf("is a tty success!\n");
    }
    printf("fd-open=%d\n", fdSerial);





    // 设置串口参数
    if (setOpt(fdSerial, 115200, 8, 'N', 1)== -1)    //设置8位数据位、1位停止位、无校验
    {
        fprintf(stderr, "Set opt Error\n");
        close(fdSerial);
        exit(1);
    }

    tcflush(fdSerial, TCIOFLUSH);    //清掉串口缓存
    fcntl(fdSerial, F_SETFL, 0);    //串口阻塞


    unsigned char rcv_buf[128]={0};
    unsigned char send_buf[128]={0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x31,0x32,0x33,0x34,0x35,0x36,0x37};
    int len;
    uint32_t ch_cnt =0;

    while(1)    //循环读取数据
    {




	    UART_Send(fdSerial, send_buf, 16);
	    //usleep(300000);


	    UART_Recv(fdSerial, rcv_buf, 128, 1000);


	    if(rcv_buf[0] != send_buf[0]) 
	    {

		    perror("com data error");
		    exit(EXIT_FAILURE);

	    }
	    else
	    {
		    printf("rec is %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %d\n",\
		    rcv_buf[0],rcv_buf[1],rcv_buf[2],rcv_buf[3],rcv_buf[4],rcv_buf[5],rcv_buf[6],rcv_buf[7],\
		    rcv_buf[8],rcv_buf[9],rcv_buf[10],rcv_buf[11],rcv_buf[12],rcv_buf[13],rcv_buf[14],rcv_buf[15],++ch_cnt);
	    }



	    send_buf[0]++;
	    rcv_buf[0]=0;
#if 0

	    len = UART_Recv(fdSerial, rcv_buf, 99, 10000);

	    if(len > 0)
	    {
		    rcv_buf[len] = '\0';
		    printf("receive data is %s\n", rcv_buf);
		    printf("len = %d\n", len);
		    UART_Send(fdSerial, rcv_buf, len);
	    }
	    else
	    {
		    //            printf("cannot receive data\n");
	    }



#endif







	    //usleep(100000);    //休眠100ms
	    usleep(30000);    //休眠10ms
	    //sleep(1);    //休眠1s
    }
}
