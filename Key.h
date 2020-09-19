#ifndef KEY_H
#define KEY_H
#include <stdint.h>

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
//#define KEY_WAKE                 PORTBbits.RB4	
#define KEY_WAKE                 (PORTB & 0x10)	

#define ACTION_BUTTON            PORTBbits.RB5


#define LP_BUTTON                PORTBbits.RB0


//#define   STATUS_CHARGE                PORTAbits.RA3
#define   STATUS_CHARGE                (PORTA & 0x08)



#define KEY_UP_PRESSED        0xf1
#define KEY_DOWN_PRESSED      0xf2
#define KEY_V_PRESSED         0xf3

#define KEY_NOT_PRESSED         0x00
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

void KEY_Init(void);
uint8_t KEY_Scan(void);	
void KeyFuction(void);


#endif