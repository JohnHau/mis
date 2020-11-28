
#ifndef TIMER_H
#define TIMER_H




#define  SA_T_BRAKE_S     (4 * 1000)
#define  SB_T_BRAKE_S     (4 * 1000)

#define  SA_T_BRAKE     (1 * 100)
#define  SB_T_BRAKE     (1 * 100)
#define  RST_T_BRAKE    (2 * 1000)

#if 0
#define DELAY_T1_1SEC()  do {delaynus(50*1000);delaynus(50*1000);\
                             delaynus(50*1000);delaynus(50*1000);\
                             delaynus(50*1000);delaynus(50*1000);\
                             delaynus(50*1000);delaynus(50*1000);\
                             delaynus(50*1000);delaynus(50*1000);\
                             delaynus(50*1000);delaynus(50*1000);\
                             delaynus(50*1000);delaynus(50*1000);\
                             delaynus(50*1000);delaynus(50*1000);\
                             delaynus(50*1000);delaynus(50*1000);\
                             delaynus(50*1000);delaynus(50*1000);\
                             }while(0)

#endif



//#define DELAY_T1_1SEC()  do {delaynus(50*1000);delaynus(50*1000);delaynus(50*1000);}while(0)
//#define DELAY_T1_1SEC()  do {delaynus(50*1000);}while(0)
//#define DELAY_T1_1SEC()  do {delaynus(20*1000);}while(0)

//#define DELAY_T1_1SEC()  do {delaynus(2*1000);}while(0)
#define DELAY_T1_1SEC()  

#define DISABLE_TIMER()   do{T0IE=0;T0IF = 0;T0CONbits.TMR0ON =0;}while(0)
#define ENABLE_TIMER()   do{T0IE=1;T0CONbits.TMR0ON =1;}while(0)
#define INTV   1006
//#define INTV   2013

#define START()   do {TMR1 =0;T1CONbits.TMR1ON =1;}while(0)

#define STOP()    T1CONbits.TMR1ON =0





extern uint16_t action_btn_cnt;






extern void TimerInit(void);
extern void Timer1Init(void);
extern void delaynus(uint16_t n);




extern uint16_t tva;
extern uint16_t tvb;

extern uint8_t flag_tv;

extern uint16_t tv_s[10];


#endif