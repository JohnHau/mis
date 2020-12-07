#ifndef __OLED_H
#define __OLED_H
#include<stdint.h>		  	 


#define EEPROM_I2C_WR	0		
#define EEPROM_I2C_RD	1		




#define  MODE_NORMAL     0
#define  MODE_REVERSE    0x80
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



#define ORIGINAL  1
//#define LTEMP  1

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





//==============================================================================
//==============================================================================


#define COL_PAGE0_PATTERN_A   71
#define COL_PAGE1_PATTERN_A   71
#define WIDTH_PATTERN_A       27




#define MLENGTH    23

#define COL_PAGE0_MDROPS   (COL_PAGE0_PATTERN_A + 2)



#define COL_PAGE0_PATTERN_B   35
#define COL_PAGE1_PATTERN_B   35
#define WIDTH_PATTERN_B       27



#define COL_PAGE0_MEM   (COL_PAGE0_PATTERN_B + 2)




#define COL_PAGE0_PATTERN_C   0
#define COL_PAGE1_PATTERN_C   0
#define WIDTH_PATTERN_C       27


#define COL_PAGE0_BAT   (COL_PAGE0_PATTERN_C + 2)



#define COL_PAGE0_PATTERN_D   49
#define COL_PAGE1_PATTERN_D   49
#define WIDTH_PATTERN_D       48


#define DEFG_LENGTH    19
#define COL_PAGE0_DN   (COL_PAGE0_PATTERN_D + 14)





#define COL_PAGE0_PATTERN_E   0
#define COL_PAGE1_PATTERN_E   0
#define WIDTH_PATTERN_E       48


#define COL_PAGE0_EN   (COL_PAGE0_PATTERN_E + 14)


#define COL_PAGE0_PATTERN_F   49
#define COL_PAGE1_PATTERN_F   49
#define WIDTH_PATTERN_F       48


#define COL_PAGE0_FN   (COL_PAGE0_PATTERN_F + 14)


#define COL_PAGE0_PATTERN_G   0
#define COL_PAGE1_PATTERN_G   0
#define WIDTH_PATTERN_G       48



#define COL_PAGE0_GN   (COL_PAGE0_PATTERN_G + 14)


#define COL_PAGE0_PATTERN_H   0
#define COL_PAGE1_PATTERN_H   0
#define WIDTH_PATTERN_H       48


#define COL_PAGE0_HN   (COL_PAGE0_PATTERN_H + 17)

//#define COL_PAGE0_HN   (COL_PAGE0_PATTERN_H + 14)








#define NUM_0     0
#define NUM_1     1
#define NUM_2     2
#define NUM_3     3
#define NUM_4     4
#define NUM_5     5
#define NUM_6     6
#define NUM_10    10
#define NUM_13    13
#define NUM_100   100

#define NUM_150   101
#define NUM_200   102
#define NUM_250   103
#define NUM_300   104

#define NUM_1P5   105
#define NUM_2P5   106


#define MIDDLE   0
#define BOTTOM   3


#define LEFT     1
#define RIGHT    2


#define TYPE_F     1
#define TYPE_G     2
#define TYPE_H     3
#define TYPE_I     4






extern interface_t interface_x;

extern uint8_t write_buf[256];
extern uint8_t read_buf[256];


void i2c_CfgGpio(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);







	
#define EEPROM_DEV_ADDR			0x78	
//#define EEPROM_DEV_ADDR			0x7a
//#define EEPROM_DEV_ADDR			0x7c
//#define EEPROM_DEV_ADDR			0x7e
		



uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize);
//uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint8_t _usAddress, uint16_t _usSize);


uint8_t ee_CheckDevice(uint8_t _Address);
void ee_Erase(void);
uint8_t ee_WaitStandby(void);
uint8_t ee_Test(void) ;


void Initial_LY096BG30(void);
void display_logo(void);


void LCD_backlight_init(void);
void LCD_On(void);
void LCD_Off(void);
void LCD_Blink(void);
uint8_t ee_CheckDevice(uint8_t _Address);


#define LCD_ON()     LATEbits.LE0 =1

#define LCD_OFF()    LATEbits.LE0 =0


#define LCD_BLINK() do{\
                        LCD_ON();\
                        delaynus(50);delaynus(50);\
                        delaynus(50);delaynus(50);\
                        delaynus(50);delaynus(50);\
                        LCD_OFF();\
                        }while(0)




uint8_t AD_init(void);
uint16_t get_AD_vaule(void);
uint16_t get_SenseA_AD_vaule(void);
uint16_t get_SenseB_AD_vaule(void);
uint8_t display_pattern(uint8_t num,uint8_t sub,uint8_t mode);
uint8_t hg_interface(void);
void delay(unsigned int  x);


//==============================================================================




void display_cmode(uint8_t y,uint8_t x,uint8_t mode);
void display_drops(uint8_t y,uint8_t x,uint8_t mode);
void display_drop(uint8_t y,uint8_t x,uint8_t mode);
void display_blank_mode_pa(uint8_t y,uint8_t x,uint8_t mode);




void display_mem(uint8_t y,uint8_t x,uint8_t mode);
void display_bat(uint8_t y,uint8_t x,uint8_t mode);
void display_bat_blank(uint8_t y,uint8_t x,uint8_t mode);

uint8_t display_frame_abc(uint8_t y,uint8_t x, uint8_t mode);
uint8_t display_frame_de(uint8_t y,uint8_t x, uint8_t mode);
uint8_t display_frame_fghi(uint8_t y,uint8_t x, uint8_t mode);


uint8_t display_n_blank(uint8_t y,uint8_t x, uint8_t mode);


uint8_t display_num(uint8_t y,uint8_t x, uint8_t mode);

void initial_ui_setting(void);


void check_bat(void);


void delay_nms(uint32_t n);
void delay_ms(unsigned int ms);
void delay_pwm(uint32_t  n);
void delay_f(uint32_t n);



#endif  
	 



