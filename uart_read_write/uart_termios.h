#ifndef __UART_TERMIOS_H__ 
#define __UART_TERMIOS_H__ 
enum COM_PORT {
	USER_COM0,
	USER_COM1,
	USER_COM2,
	USER_COM3,
	USER_COM4,
	USER_COM5,
	USER_COM6,
	USER_COM7,
	USER_COM8,
	USER_COM9,
	USER_COM10,
	USER_COM11,
	USER_COM12,
	USER_COM13,
	USER_COM14,
	USER_COM15,
	USER_COM16,
	USER_COM17,
	USER_COM18,
	USER_COM19,
	USER_COM20,
	USER_COM21,
	USER_COM22,
	USER_COM23,
	USER_COM24,
	USER_COM25,
	USER_COM26,
	USER_COM27,
	USER_COM28,
	USER_COM29,
	USER_COM30
};


//#define DEV_NAME    "/dev/ttymxc3"    ///< 串口设备
//#define DEV_NAME    "/dev/ttyS19"    ///< 串口设备
//#define DEV_NAME    "/dev/ttyS26"    ///< 串口设备
#define DEV_NAME    "/dev/ttyS9"    ///< 串口设备

extern int32_t init_com_port(enum COM_PORT port,uint32_t baudrate);
extern int com_recv(int fd, char *rcv_buf, int data_len, int timeout);
extern int com_send(int fd, char *send_buf, int data_len);



#endif
