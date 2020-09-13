#ifndef BEEP_H
#define BEEP_H


//==============================================================================
#define TEST_LED_ON()      LATDbits.LD5 =0
#define TEST_LED_OFF()     LATDbits.LD5 =1


//==============================================================================









extern void BeepInit(void);
extern void BeepOn(void);
extern void BeepOff(void);
void buzz(void);

#endif