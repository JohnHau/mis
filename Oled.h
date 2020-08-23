#ifndef __OLED_H
#define __OLED_H
#include<stdint.h>		  	 

#define USE_HORIZONTAL 0  //设置显示方向 0：正向显示，1：旋转180度显示

#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned int
	
#define OLED_CMD  0	
#define OLED_DATA 1	

#define OLED_SCL  PORTCbits.RC3	//SCL
#define OLED_SDA  PORTCbits.RC4	//SDA
#define OLED_RES  PORTCbits.RC5	//RES
#define OLED_DC  PORTCbits.RC6	//SDA
#define OLED_CS  PORTCbits.RC7	//RES



#define OLED_SCL_Clr() OLED_SCL=0
#define OLED_SCL_Set() OLED_SCL=1

#define OLED_SDA_Clr() OLED_SDA=0
#define OLED_SDA_Set() OLED_SDA=1

#define OLED_RES_Clr() OLED_RES=0
#define OLED_RES_Set() OLED_RES=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1


void delay_ms(unsigned int ms);
void OLED_WR_Byte(u8 dat,u8 cmd);
void Column_Address(u8 a, u8 b);
void Row_Address(u8 a, u8 b);
void OLED_Clear(u8 x1,u8 y1,u8 x2,u8 y2,u8 color);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey);
void OLED_ShowString(u8 x,u8 y,u8 *dp,u8 sizey);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 sizey);
void OLED_DrawBMP(u8 x,u8 y,u8 width,u8 height,const u8 *BMP);
void Init_ssd1327(void);



//=================================================================================
//=================================================================================



#define EEPROM_I2C_WR	0		
#define EEPROM_I2C_RD	1		



//#define EEPROM_GPIO_PORT_I2C	GPIOA			
//#define EEPROM_RCC_I2C_PORT 	RCC_APB2Periph_GPIOA		
#define EEPROM_GPIO_PORT_I2C			
#define EEPROM_RCC_I2C_PORT 	


//#define EEPROM_I2C_SCL_PIN		GPIO_Pin_2			
//#define EEPROM_I2C_SDA_PIN		GPIO_Pin_3			
#define EEPROM_I2C_SCL_PIN			
#define EEPROM_I2C_SDA_PIN		





//#define EEPROM_I2C_SCL_1()  EEPROM_GPIO_PORT_I2C->BSRR = EEPROM_I2C_SCL_PIN				/* SCL = 1 */
//#define EEPROM_I2C_SCL_0()  EEPROM_GPIO_PORT_I2C->BRR = EEPROM_I2C_SCL_PIN				/* SCL = 0 */
	
//#define EEPROM_I2C_SDA_1()  EEPROM_GPIO_PORT_I2C->BSRR = EEPROM_I2C_SDA_PIN				/* SDA = 1 */
//#define EEPROM_I2C_SDA_0()  EEPROM_GPIO_PORT_I2C->BRR = EEPROM_I2C_SDA_PIN				/* SDA = 0 */
	
//#define EEPROM_I2C_SDA_READ()  ((EEPROM_GPIO_PORT_I2C->IDR & EEPROM_I2C_SDA_PIN) != 0)	

#if 0
#define EEPROM_I2C_SCL_1()  	 PORTCbits.RC3 =1
#define EEPROM_I2C_SCL_0()  	 PORTCbits.RC3 =0
	
#define EEPROM_I2C_SDA_1()  	PORTCbits.RC4 =1
#define EEPROM_I2C_SDA_0()  	PORTCbits.RC4 =0
	
#define EEPROM_I2C_SDA_READ()  	  (PORTCbits.RC4)
#endif

#define EEPROM_I2C_SCL_1()  	 LATCbits.LC3 =1
#define EEPROM_I2C_SCL_0()  	 LATCbits.LC3 =0
	
#define EEPROM_I2C_SDA_1()  	LATCbits.LC4 =1
#define EEPROM_I2C_SDA_0()  	LATCbits.LC4 =0
	
//#define EEPROM_I2C_SDA_READ()  	  (PORTCbits.RC4)
#define EEPROM_I2C_SDA_READ()  	  (PORTC & 0x10)







void i2c_CfgGpio(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);















/* 
 * AT24C02 2kb = 2048bit = 2048/8 B = 256 B
 * 32 pages of 8 bytes each
 *
 * Device Address
 * 1 0 1 0 A2 A1 A0 R/W
 * 1 0 1 0 0  0  0  0 = 0XA0
 * 1 0 1 0 0  0  0  1 = 0XA1 
 */

/* AT24C01/02每页有8个字节 
 * AT24C04/08A/16A每页有16个字节 
 */
	

//#define EEPROM_DEV_ADDR			0xA0		
#define EEPROM_DEV_ADDR			0x78	
//#define EEPROM_DEV_ADDR			0x7a
//#define EEPROM_DEV_ADDR			0x7c
//#define EEPROM_DEV_ADDR			0x7e
#define EEPROM_PAGE_SIZE		  8			  
#define EEPROM_SIZE				  256			



uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize);
//uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint8_t _usAddress, uint16_t _usSize);


uint8_t ee_CheckDevice(uint8_t _Address);
void ee_Erase(void);
uint8_t ee_WaitStandby(void);
uint8_t ee_Test(void) ;


void Initial_LY096BG30(void);
void fill_picture(unsigned char fill_Data);
void picture_1(void);



void oled_096_print(uint8_t col, uint8_t row, int8_t*str);




void LCD_backlight_init(void);
void LCD_On(void);
void LCD_Off(void);

uint8_t ee_CheckDevice(uint8_t _Address);

void delay(unsigned int  x);














#endif  
	 



