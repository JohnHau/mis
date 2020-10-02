#ifndef BEEP_H
#define BEEP_H

#include <stdint.h>

//==============================================================================
#define TEST_LED_ON()      LATDbits.LD5 =0
#define TEST_LED_OFF()     LATDbits.LD5 =1


//==============================================================================









extern void BeepInit(void);
extern void BeepOn(void);
extern void BeepOff(void);
void buzz(void);




void uart_init(void);
void put_byte_uart(uint8_t n);
void put_bytes_uart(uint8_t *arr,uint8_t n);






#endif