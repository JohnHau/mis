#ifndef BEEP_H
#define BEEP_H

#include <stdint.h>

//==============================================================================
#define TEST_LED_ON()      LATDbits.LD5 =0
#define TEST_LED_OFF()     LATDbits.LD5 =1


//==============================================================================




extern uint8_t flag_power_up;




void BeepInit(void);
void BeepOn(void);
void BeepOff(void);
void buzz(void);

#define  BEEP_ON()    LATEbits.LE2 =1
#define  BEEP_OFF()   LATEbits.LE2 =0



void uart_init(void);
void put_byte_uart(uint8_t n);
void put_bytes_uart(uint8_t *arr,uint8_t n);






#endif