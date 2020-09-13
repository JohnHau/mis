#ifndef __OLED_H
#define __OLED_H
#include<stdint.h>		  	 

void delay_ms(unsigned int ms);


#define EEPROM_I2C_WR	0		
#define EEPROM_I2C_RD	1		




#define  MODE_NORMAL     1
#define  MODE_REVERSE    2
#define  MODE_BLINK      3
#define  MODE_BLANK      4


#define WMD_C          0x55
#define WMD_S_DROP     0x56
#define WMD_M_DROP     0x57







//#define EEPROM_GPIO_PORT_I2C	GPIOA			
//#define EEPROM_RCC_I2C_PORT 	RCC_APB2Periph_GPIOA		
#define EEPROM_GPIO_PORT_I2C			
#define EEPROM_RCC_I2C_PORT 	


//#define EEPROM_I2C_SCL_PIN		GPIO_Pin_2			
//#define EEPROM_I2C_SDA_PIN		GPIO_Pin_3			
#define EEPROM_I2C_SCL_PIN			
#define EEPROM_I2C_SDA_PIN	


//#define ORIGINAL  1
#define LTEMP  1

#if defined(ORIGINAL)
#define EEPROM_I2C_SCL_1()  	 LATCbits.LC3 =1
#define EEPROM_I2C_SCL_0()  	 LATCbits.LC3 =0
	
#define EEPROM_I2C_SDA_1()  	LATCbits.LC4 =1
#define EEPROM_I2C_SDA_0()  	LATCbits.LC4 =0

#elif defined(LTEMP)


#define EEPROM_I2C_SCL_1()  	 LATCbits.LC4 =1
#define EEPROM_I2C_SCL_0()  	 LATCbits.LC4 =0
	
#define EEPROM_I2C_SDA_1()  	LATCbits.LC3 =1
#define EEPROM_I2C_SDA_0()  	LATCbits.LC3 =0

#endif









	
//#define EEPROM_I2C_SDA_READ()  	  (PORTCbits.RC4)


#if defined(ORIGINAL)
#define EEPROM_I2C_SDA_READ()  	  (PORTC & 0x10)

#elif defined(LTEMP)

#define EEPROM_I2C_SDA_READ()  	  (PORTC & 0x08)
#endif



//4 seconds
#define TIMOUT_BLINK   1000

typedef struct action_profile
{

    uint8_t  inject_mode;
    uint8_t  para[8];
}action_profile_t;

typedef struct interface
{
   
    uint8_t focus;
    uint8_t mode;
    uint8_t sub_old;
    uint8_t sub;
    uint8_t sub_lmt[8];
    uint16_t cnt_blink;
    action_profile_t  profile;
}interface_t;





#define COL_PAGE0_PATTERN_A   71
#define COL_PAGE1_PATTERN_A   71
#define WIDTH_PATTERN_A       27


#define COL_PAGE0_PATTERN_B   35
#define COL_PAGE1_PATTERN_B   35
#define WIDTH_PATTERN_B       27



#define COL_PAGE0_PATTERN_C   0
#define COL_PAGE1_PATTERN_C   0
#define WIDTH_PATTERN_C       27


#define COL_PAGE0_PATTERN_D   49
#define COL_PAGE1_PATTERN_D   49
#define WIDTH_PATTERN_D       48


#define COL_PAGE0_PATTERN_E   0
#define COL_PAGE1_PATTERN_E   0
#define WIDTH_PATTERN_E       48


#define COL_PAGE0_PATTERN_F   49
#define COL_PAGE1_PATTERN_F   49
#define WIDTH_PATTERN_F       48


#define COL_PAGE0_PATTERN_G   0
#define COL_PAGE1_PATTERN_G   0
#define WIDTH_PATTERN_G       48


#define COL_PAGE0_PATTERN_H   0
#define COL_PAGE1_PATTERN_H   0
#define WIDTH_PATTERN_H       48




















extern interface_t interface_x;

void delay_nms(uint32_t n);



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
void LCD_Blink(void);
uint8_t ee_CheckDevice(uint8_t _Address);


uint8_t AD_ch0_init(void);
uint16_t get_AD_vaule(void);
uint16_t get_SenseA_AD_vaule(void);
uint16_t get_SenseB_AD_vaule(void);
uint8_t display_pattern(uint8_t num,uint8_t sub,uint8_t mode);
uint8_t hg_interface(void);
void delay(unsigned int  x);














#endif  
	 



