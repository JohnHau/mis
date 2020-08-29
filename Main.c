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
int ann=0;
uint8_t prev_edge =0;
uint8_t cur_edge =0;
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
	MotorDriveInit();
	//PositionCheckInit();
	//KEY_Init();

    Initial_LY096BG30();
   // while(xn<20)
    //LCD_On();
    
#if 0
    // pusher
    ENABLE_AH();
    FORWARD_RUN_A();        
    
    while(ann < 2000)
    {
        //cur_edge = READ_PHA_MA();
        cur_edge = READ_PHB_MA();
        if(cur_edge != prev_edge)
        {
            
            prev_edge = cur_edge;
            ann++;
        }
    }
    STOP_A();
    ENABLE_AL();
    buzz();
    
            
#endif       
    
    
 #if 1
    //injector
    ENABLE_BH();
    FORWARD_RUN_B();        
    
    while(ann < 2000)
    {
        //cur_edge = READ_PHA_MB();
        cur_edge = READ_PHB_MB();
        if(cur_edge != prev_edge)
        {
            
            prev_edge = cur_edge;
            ann++;
        }
    }
    STOP_B();
    ENABLE_BL();
    buzz();
        
#endif   
    
    
    
    
    
            
            
            
#if 0
    ENABLE_AH();
    FORWARD_RUN_A();
    delay(400);
    STOP_A();
     buzz();
    REVERSE_RUN_A();
    delay(400);
    STOP_A();
    buzz();
#endif
    
    
#if 0
    ENABLE_BH();
    FORWARD_RUN_B();
    delay(400);
    STOP_B();
     buzz();
    REVERSE_RUN_B();
    delay(400);
    STOP_B();
    buzz();
#endif
    
    
    
    
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
	while(1)               
	{   
		//NeedleFindZeroPosFun();
		//AdSampleTask();
		//KEY_Scan();
		//KeyFuction();
		delay(100);	



	}
}


 
