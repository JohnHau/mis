 #include <xc.h>
 #include <stdio.h>
 #include <stdlib.h>
#include"MotorDrive.h"
#include "Timer.h"
#include "Beep.h"
#include "Key.h"
#include "Timer.h"
#include "Oled.h"
#include "gui.h"


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
//#pragma config PBADEN = ON				//portb AD enble bit


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
          


uint8_t flag_power_up =0;
//int xn=0;
//int ann=0;
uint8_t prev_edge =0;
uint8_t cur_edge =0;




uint16_t bv =0;
uint16_t cv =10;
uint16_t dv =10;
uint32_t msleep =0;


uint16_t cnta_mb =0;
uint16_t cntb_mb =0;

//uint16_t hs =0;
//uint16_t ls =0;

void main(void)
{
    cur_state_phb_ma=0;
    prev_state_phb_ma=0;
    cnt_ma = 0;
    cnt_mb = 0;
    HG_device_init();
    
   
//==============================================================================    
#if 0
   // FORWARD_RUN_A();
    
    while(1)
    {
        
        bv = get_SenseA_AD_vaule();
        if(bv > 176)                              
        { 
           buzz();                         
        }
        
        //printf("testing string, hello world\r\n");
        delay_nms(100);
        
        
    
    }
#endif
//==============================================================================    
    
    initial_para_setting();
    
    //=================================================
     //hg_op.need_reset =1;
     //hg_op.working_mode = WORK_MODE_DROPS;
    //=================================================
   
    while(1)
    {
        enter_sleep();
  
        if(hg_op.need_reset)
        {
            //TEST_LED_BLINK();            
            hg_reset();
        }
        else
        {
            if(hg_op.working_mode == WORK_MODE_DROPS)
            {
               
                drops_routine();
            }
            
#if 1
            else if(hg_op.working_mode == WORK_MODE_C)
            {
                c_routine();
            }
            else if(hg_op.working_mode == WORK_MODE_DROP)
            {
                drop_routine();     
            }
            else if(hg_op.working_mode == WORK_MODE_TEST)
            {
                test_routine();     
            } 
            else if(hg_op.working_mode == WORK_MODE_STOP)
            {
                if(T0IE == 0 || T0CONbits.TMR0ON == 0)
                {
                    ENABLE_TIMER(); 
                }
      
                 HG_interface();
                 check_bat();
                 check_ui_status();             
                 check_shut_device();
                 //printf("in stop mode\r\n");
            }
            else
            {
                 //printf("out of mode\r\n");
            }
#endif 
             
          
#if 1    
            check_acting();
#endif
            
  
#if 1             
           check_ui_blink();
#endif     

#if 1
            check_device_idle();     
#endif    
            
            
            
            
        }
    }//end while
       
}//end main
