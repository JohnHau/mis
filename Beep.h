#ifndef BEEP_H
#define BEEP_H

#include <stdint.h>




#define  HG_DEBUG   1





//==============================================================================
#define TEST_LED_ON()      LATDbits.LD5 =0
#define TEST_LED_OFF()     LATDbits.LD5 =1

#define TEST_LED_BLINK()  do{TEST_LED_ON();delaynus(50*1000);delaynus(50*1000);\
                                           delaynus(50*1000);delaynus(50*1000);\
                                           delaynus(50*1000);delaynus(50*1000);\
                                           delaynus(50*1000);delaynus(50*1000);\
                                           TEST_LED_OFF();\
                                           delaynus(50*1000);delaynus(50*1000);\
                                           delaynus(50*1000);delaynus(50*1000);\
                                           delaynus(50*1000);delaynus(50*1000);\
                                           delaynus(50*1000);delaynus(50*1000);\
                                           }while(0) 
//==============================================================================




extern uint8_t flag_power_up;


#define  BEEP_ON()    LATEbits.LE2 =1
#define  BEEP_OFF()   LATEbits.LE2 =0

void BeepInit(void);
void buzz(void);





void uart_init(void);
void put_byte_uart(uint8_t n);
void put_bytes_uart(uint8_t *arr,uint8_t n);






#endif