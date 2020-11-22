
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
#define DELAY_T1_1SEC()  do {delaynus(20*1000);}while(0)







extern uint16_t action_btn_cnt;






extern void TimerInit(void);
extern void Timer1Init(void);
extern void delaynus(uint16_t n);
#endif