#ifndef KEY_H
#define KEY_H


#define ON_OFF_BUTTON_PIN 					PORTBbits.RB4  		
#define UP_BUTTON_PIN  						PORTDbits.RD4  		
#define DOWN_BUTTON_PIN  					PORTDbits.RD7  		
#define COMFIRM_BUTTON_PIN  				PORTBbits.RB3  		

#define START_WORK_BUTTON_PIN  				PORTBbits.RB5  		
	 
#define KEY_SCAN_PERIOD_CONST 10 //ms


//==============================================================================

#define KEY_UP                   PORTDbits.RD6

#define KEY_DOWN                 PORTDbits.RD7  	
#define KEY_V                    PORTBbits.RB3 
#define KEY_WAKE                 PORTBbits.RB4	


#define ACTION_BUTTON            PORTBbits.RB5


#define LP_BUTTON                PORTBbits.RB0








//==============================================================================

















extern unsigned char KeyScanPeriod;

typedef struct  
{
	unsigned char NewValue;				//
	unsigned char OldValue;				//
	unsigned char SendValue;			//
	unsigned char SendValueChangeFlag;	//	
	unsigned char FiterTimesCount;		
	unsigned char FiterTimes;			

}KeyType;

extern KeyType OnOffKey,UpKey,DownKey,ConfirmKey,StartInjectKey;

extern void KEY_Init(void);//IO≥ı ºªØ
extern void KEY_Scan(void);	
extern void KeyFuction(void);


#endif