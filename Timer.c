#include <xc.h>
#include<stdint.h>	
#include "Timer.h"
//#include "Ad.h"
#include "Key.h"
//#include "PositionControl.h"
#include "Beep.h"
#include "Oled.h"
#include"MotorDrive.h"
#include "gui.h"

unsigned char LastNeedleFeedback =0;
unsigned char LastInjectionFeedback =0;
unsigned char flag =0;

uint16_t mbcnt=0;
uint8_t tflag =1;
uint8_t ttte =0;

//void __interrupt(high_priority) ISR(void)
//void __interrupt(high_priority) ISR(void)
void __interrupt ISR(void)
{
    uint8_t temp;
    static uint32_t tcnt=0;

//===============================
#if 1    
    
    
#if 1
    if(T0IF)
    {
    
        tcnt ++;
            
        //if(tcnt > 500*1000UL)
        if(tcnt > 125)
        {

            //buzz();
            
            if(menu[0].mode == MODE_BLINK)
            {
                
                if(flip == 1)
                {
                    display_blank_mode_pa(0,COL_PAGE0_MDROPS,MODE_REVERSE);
                    flip =0;
                }
                else if(flip == 0)
                {
                    flip =1;
                    if(work_mode == WORK_MODE_C)
                    {
                        display_cmode(0,COL_PAGE0_MDROPS, MODE_REVERSE);
                    }
                    else if(work_mode == WORK_MODE_DROPS)
                    {
                        display_drops(0,COL_PAGE0_MDROPS, MODE_REVERSE);
                    }
                    else if(work_mode == WORK_MODE_DROP)
                    {
                        display_drop(0,COL_PAGE0_MDROPS, MODE_REVERSE);
                    }     
                }
            }  
            else if(menu[3].mode == MODE_BLINK)
            {
                
                if(flip == 1)
                {
                    display_n_blank(1,COL_PAGE0_DN, MODE_REVERSE);
                    flip =0;
                }
                else if(flip == 0)
                {
                    flip =1;
                    if(menu[3].parameter == 0)
                    {
                        display_n4(0,COL_PAGE0_DN, MODE_REVERSE);
                    }
                    else if(menu[3].parameter == 1)
                    {
                        display_n13(0,COL_PAGE0_DN, MODE_REVERSE);
                    }
 
                }
            }
            
            
            

            
            tcnt = 0;
        }

        T0IF = 0;
    
    }
    
    
#endif
    
    
    
    
    
#if 1
    if(INTCONbits.RBIF)
    {
    
       
        if(KEY_WAKE  == 0)
        {
            
             //delay_nms(10);
            
            if(KEY_WAKE  == 0)
            {
                
#if 0
                if(ttte)
                {
                    TEST_LED_ON(); 
                    ttte =0;
                }
                else if (ttte == 0)
                {
                    ttte = 1;
                     TEST_LED_OFF(); 
                }
                
#endif
            }
            //LCD_On();
             //LCD_Blink();
            //buzz();
        }
        
        if(ACTION_BUTTON  == 0)
        {
            buzz();
            ENABLE_BH(); 
            FORWARD_RUN_B();   

        }
        //buzz();
        //temp = PORTB;
        INTCONbits.RBIF=0;
        
        

    }
    
           
     if(INTCONbits.INT0IF)//LP_BUTTON
     {   
            //buzz();
            STOP_B();
            ENABLE_BL();
            
          
            INTCON3bits.INT2IF = 0;////for test
             
            INTCONbits.INT0IF = 0;
            
            
            
     }
        
        
    if(INTCON3bits.INT2IF)
    {
     
      
      //buzz();
      //mbcnt++;
      cnt_ma ++;
     
      
      //if(mbcnt == 30000)
      if(cnt_ma == 600000) 
      {
          cnt_ma = 0;
          STOP_B();
          ENABLE_BL();
      }
      
      
       INTCON3bits.INT2IF = 0;
    }
    
    
    
    
    
#endif

#endif    
//========================================    
    
    
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