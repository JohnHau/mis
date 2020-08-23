#ifndef AD_H
#define AD_H

#define INJECTION_MOTOR_CHANNEL 	0
#define NEEDLE_MOTOR_CHANNEL 		1
#define BAT_VOLT_CHANNEL 			2

#define ARRAY_LENGTH 5

extern void ADInit(void);
extern void EnableAd(void);
extern void CloseAd(void);
extern void AdSampleTask(void);

extern unsigned int InjectionMotorAdAverageValue ;//注射电机Ad平均值
extern unsigned int NeedleMotorAdAverageValue ;//注射出针电机Ad平均值
extern unsigned int BatteryVoltAdAverageValue ;//电池电压


#define AD_SAMPLE_PERIOD 2  //1ms

#define INJECTION_MOTOR_PROTECT_CURRENT 	1000  //mA
#define NEEDLE_MOTOR_PROTECT_CURRENT 		1000  //mA

extern unsigned char AdSampleTaskTime;

#define VOLT_AD_1_TO_VOLT  					88  //8.837  //每个AD值对应8.837mv 扩大10倍
#define INJECTION_MOTOR_AD_1_TO_CURRENT  	10  //1AD-1.03889ma   扩大10倍
#define NEEDLE_MOTOR_AD_1_TO_CURRENT  		10  //1AD-1.03889ma   扩大10倍

//extern volatile unsigned int BatteryVolt;//电池电压
extern unsigned int InjectionMotorCurrent;//注射电机电流
extern unsigned int NeedleMotorCurrent;//出针电机电流

#endif