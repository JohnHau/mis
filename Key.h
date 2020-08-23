#ifndef KEY_H
#define KEY_H

//按键定义
#define ON_OFF_BUTTON_PIN 					PORTBbits.RB4  		/*开关机按键*/
#define UP_BUTTON_PIN  						PORTDbits.RD4  		/*向上调节按键*/
#define DOWN_BUTTON_PIN  					PORTDbits.RD7  		/*向下调节按键*/
#define COMFIRM_BUTTON_PIN  				PORTBbits.RB3  		/*确认按键*/

#define START_WORK_BUTTON_PIN  				PORTBbits.RB5  		/*此工作模式下开始工作按键*/
	 
#define KEY_SCAN_PERIOD_CONST 10 //ms

extern unsigned char KeyScanPeriod;

typedef struct  
{
	unsigned char NewValue;				//
	unsigned char OldValue;				//
	unsigned char SendValue;			//
	unsigned char SendValueChangeFlag;	//	
	unsigned char FiterTimesCount;		//滤波次数计数
	unsigned char FiterTimes;			//滤波次数

}KeyType;

extern KeyType OnOffKey,UpKey,DownKey,ConfirmKey,StartInjectKey;

extern void KEY_Init(void);//IO初始化
extern void KEY_Scan(void);	
extern void KeyFuction(void);


#endif