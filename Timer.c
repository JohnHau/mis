//#include <p18cxxx.h>
//#include<pic18.h>  
#include <xc.h>
#include<stdint.h>	
#include "Timer.h"
//#include "Ad.h"
#include "Key.h"
//#include "PositionControl.h"
#include "Beep.h"
#include "Oled.h"
#include"MotorDrive.h"

unsigned char LastNeedleFeedback =0;
unsigned char LastInjectionFeedback =0;
unsigned char flag =0;

uint16_t mbcnt=0;
uint8_t tflag =1;

//void __interrupt(high_priority) ISR(void)
//void __interrupt(high_priority) ISR(void)
void __interrupt ISR(void)
{
    uint8_t temp;
    static uint32_t tcnt=0;
    
    
    
#if 1
    if(T0IF)
    {
    
        tcnt ++;
    if(interface_x.mode == MODE_BLINK  && interface_x.cnt_blink)
    {
           interface_x.cnt_blink --;


    } 
        
        
        //if(tcnt > 500*1000UL)
        if(tcnt > 125)
        {

            //buzz();
            
            
            if(tflag)
            {
             //BeepOn();
            // LCD_On();
                
                
                
                 display_pattern(7,2,MODE_BLANK);
                  display_pattern(6,0,MODE_BLANK);
                   display_pattern(5,0,MODE_BLANK);
                    display_pattern(4,0,MODE_BLANK);
                    
                 display_pattern(1,2,MODE_BLANK);
                    
             tflag =0;
            
            }
            else if(tflag == 0)
            {
             //BeepOff();
            // LCD_Off();
                 display_pattern(7,2,MODE_REVERSE);
                  display_pattern(6,0,MODE_REVERSE);
                   display_pattern(5,0,MODE_REVERSE);
                    display_pattern(4,0,MODE_REVERSE);
                          
                  display_pattern(1,2,MODE_REVERSE);
             tflag =1;
            }
            
            
            
            tcnt = 0;
        }

        T0IF = 0;
    
    }
    
    
#endif
    
    
    
    
    
#if 0
    if(INTCONbits.RBIF)
    {
    
        
        if (KEY_WAKE  == 0)
        {
             //LCD_On();
             LCD_Blink();
        }
        
        if (ACTION_BUTTON  == 0)
        {
            //buzz();
             //LCD_Off();
            LCD_Blink();
        }
        
        temp = PORTB;
        INTCONbits.RBIF=0;
        
        
 
        
        
       // buzz();
    }
    
    
    
           
        if(INTCONbits.INT0IF)//LP_BUTTON
        {   
            //buzz();
            //LCD_On();
             LCD_Blink();
            INTCONbits.INT0IF = 0;
        }
        
        
    if (INTCON3bits.INT2IF)
    {
      INTCONbits.INT0IF = 0;
      
      //buzz();
      mbcnt++;
      
      if(mbcnt == 30000)
      {
      
          STOP_B();
          ENABLE_BL();
      }
      
      
      
    }
    
    
    
    
    
#endif

    
    
    
    
} 

void TimerInit(void)
{
	T0CS=0; //
	PSA=0; // 
	T0PS2=1;
	T0PS1=0;
	T0PS0=1; // 4ms
    
    
	T08BIT =1;//
	T0IF=0; // 
	T0IE=1; // 
	GIE=1;  // 
	TMR0=0; // 
}