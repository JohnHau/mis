//#include<pic18.h>    
#include <xc.h>
//#include "Ad.h"
#include"MotorDrive.h"
#include "Timer.h"
#include "Beep.h"
//#include "Oled.h"
#include "PositionControl.h"
#include "Key.h"
#include "Timer.h"
#include "Oled.h"
#include "bmp.h"
//#include "oledfont.h"
//#include "Display.h"
#include "PositionControl.h"

#pragma config OSC = HS					//Oscillator Selection bits
#pragma config FCMEN = OFF				//Fail-Safe clock Monitor enable bit
#pragma config IESO = OFF				//internal external oscillator switchover bit

#pragma config PWRT = OFF				//Power-up timer enable bit
#pragma config BOREN = OFF 				//Brown-out reset enable bit
#pragma config BORV = 0				//Brown-out reset voltage bit    

#pragma config WDT = OFF 			//Watchdog timer  enable bit
#pragma config WDTPS = 64				//Watchdog timer postscale select bits

#pragma config CCP2MX = PORTC				//ccp2 mux bit
#pragma config PBADEN = OFF				//portb AD enble bit
#pragma config LPT1OSC = OFF				//low-power timer1 oscillator enable bit
#pragma config MCLRE = ON			//mclr pin enable bit

#pragma config STVREN = OFF					//stack full/underfow reset enable bit
#pragma config LVP = OFF 			//single supply icsp enable bit
#pragma config XINST = OFF			//Extended instruction set enable bit

#pragma config CP0 = OFF			//code protection bit
#pragma config CP1 = OFF			//code protection bit
#pragma config CP2 = OFF			//code protection bit
#pragma config CP3 = OFF			//code protection bit

#pragma config CPB = OFF				//Boot block code protection bit
#pragma config CPD = OFF			//data eerom code protection bit

#pragma config WRT0 = OFF				//write protection bit
#pragma config WRT1 = OFF				//write protection bit
#pragma config WRT2 = OFF				//write protection bit
#pragma config WRT3 = OFF				//write protection bit

#pragma config WRTC = OFF				//configuration register write protection bit 
#pragma config WRTB = OFF				//boot block write protection bit 
#pragma config WRTD = OFF				//data eerom write protection bit

#pragma config EBTR0 = OFF				//table read protection bit
#pragma config EBTR1 = OFF				//table read protection bit
#pragma config EBTR2 = OFF				//table read protection bit
#pragma config EBTR3 = OFF				//table read protection bit
#pragma config EBTRB = OFF				//boot block table read protection bit
          


int xn=0;
void main(void)                
{ 

	BeepInit();
    LCD_backlight_init();
    LCD_On();
    
   //delay(2000);
   //delay(2000);
   //delay(2000);
       //buzz();
    //while(1);
    //LCD_Off();
	//MotorDriveInit();
	//PositionCheckInit();
	//KEY_Init();
	//Init_ssd1327();
    Initial_LY096BG30();
   // while(xn<20)
    //LCD_On();
    
#if 0
    //while(0)
    //{
        //BeepOn();
        //delay(300);
        //BeepOff();
        //delay(300);
        
       // LCD_On();
        //delay(10000);
          // delay(10000);
           
           
        //LCD_Off();
        //delay(10000);
         //delay(10000);
        //xn++;
        
    
    //}
    
#endif
    
	//ADInit();
	//TimerInit();
	//OLED_DrawBMP(16,0,96,96,BMP1);
	//OLED_DrawBMP(0,0,128,96,BMP1);
	while(1)               
	{   
		//NeedleFindZeroPosFun();
		//AdSampleTask();
		//KEY_Scan();
		//KeyFuction();
		delay(100);	

	//	OLED_ShowNum(NEEDLE_LENGTH_DISPLAY_X,NEEDLE_LENGTH_DISPLAY_Y,InjectPosition/20,2,24);
	//	OLED_ShowNum(INJECT_DEPTH_DISPLAY_X,INJECT_DEPTH_DISPLAY_Y,NeedlePosition/20,2,24);
	//	OLED_ShowNum(INJECT_TYPE_DISPLAY_X,INJECT_TYPE_DISPLAY_Y,8,2,24);
	//	OLED_ShowNum(VARIABLE_DISPLAY_X,VARIABLE_DISPLAY_Y,4,2,24);

	}
}


 
