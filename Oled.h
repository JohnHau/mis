#ifndef __OLED_H
#define __OLED_H
#include<stdint.h>		  	 

void delay_ms(unsigned int ms);


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



void LCD_backlight_init(void);
void LCD_On(void);
void LCD_Off(void);

uint8_t ee_CheckDevice(uint8_t _Address);

void delay(unsigned int  x);














#endif  
	 



