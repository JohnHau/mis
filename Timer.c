#include <xc.h>
#include<stdint.h>	
 #include <stdio.h>
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

uint32_t  tmcnt =0;

extern uint16_t bv;
extern uint16_t cv;
extern uint16_t dv;


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
#if 0
            dv =0;
            dv = get_AD_vaule();
            printf("dv is %d\r\n",dv);
            
            bv =0;
            bv = get_SenseA_AD_vaule();
            printf("bv is %d\r\n",bv);
            
            cv =0;
            cv = get_SenseB_AD_vaule();
            printf("cv is %d\r\n",cv);
#endif
            
        
#if 0
            if(STATUS_CHARGE == 0)
            {
                printf("charging\r\n");
            }
            else
            {
                printf("not charging\r\n");
            }
            
#endif
            
            
            
            
            
            
            
            
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
    
       
        if(KEY_WAKE  == 0  && KEY_UP == 1 && KEY_DOWN ==1 && KEY_V ==1)
        {
            
            delay_nms(4);
            if(KEY_WAKE  == 0  && KEY_UP == 1 && KEY_DOWN ==1 && KEY_V ==1)
            {
                buzz();
                if(hg_op.status_powerup == STATUS_SLEEP)
                {
                   hg_op.status_powerup = STATUS_WAKE;
                   LCD_On();
                   hg_op.need_reset =1;
                }
                else if(hg_op.status_powerup == STATUS_WAKE)
                {
                    hg_op.status_powerup = STATUS_SLEEP;
                    LCD_Off();
                }
            }
            
        }
        
        if(ACTION_BUTTON  == 0)
        {
           
             if(hg_op.status_powerup == STATUS_WAKE)
             {
                  buzz();
                  hg_op.drops_sa =1;
                  hg_op.drops_sb =0;
                  hg_op.drops_push =0;
                  
                  hg_op.working_mode = hg_op.cur_working_mode ;
               
      
             }

        }
        //buzz();
        //temp = PORTB;
        INTCONbits.RBIF=0;
        

    }
    
           
     if(INTCONbits.INT0IF)//LP_BUTTON
     {   
            //buzz();     
         STOP_B(); 
         hg_op.status_hit_lp =1;
         

         // INTCON3bits.INT2IF = 0;////for test
             
        INTCONbits.INT0IF = 0;
                      
     }
        
        
    if(INTCON3bits.INT2IF)
    {
        
#if 1
        if(INTCON2bits.INTEDG2 == 0)
         {
             INTCON2bits.INTEDG2 = 1;
         }
         else if(INTCON2bits.INTEDG2 == 1)
         {
              INTCON2bits.INTEDG2 = 0;
         }
#endif
        
        //-> L
        //<- H
         if(hg_op.need_reset)
         {
             
             if(hg_op.status_hit_lp == 1 )
             {
                hg_op.cnt_posrst ++;

              
                    
                //if( hg_op.cnt_posrst == (300 *4 + 0))
                if( hg_op.cnt_posrst == hg_op.cnt_target_posrst)
                {
                    hg_op.posrst =1;
                    STOP_B();

                }
                
                
                
                 if(INTCON2bits.INTEDG2 == 1)
                 {
                    while(READ_PHA_MB() == 0);
                    hg_op.cnt_posrst ++;
                 }
                 else if(INTCON2bits.INTEDG2 == 0)
                 {
                        while(READ_PHA_MB() == 1);
                        hg_op.cnt_posrst ++;
                 }
                  
                  
                 if( hg_op.cnt_posrst == (300 * 4 + 0))
                {
                    hg_op.posrst =1;
                    STOP_B();

                }
                  
                  
                
             }
         }
         else
         {      
                if(hg_op.working_mode == WORK_MODE_DROPS)
                {
                    if(hg_op.drops_sa == 1)
                    {
                        hg_op.cnt_posa ++;
                        
                        if(hg_op.cnt_posa == (100 * 4))
                        {
                                STOP_B();
                                hg_op.drops_sa = 0;
                                hg_op.drops_push =1;;
                        
                        }
                        
                        if(INTCON2bits.INTEDG2 == 1)
                        {
                            while(READ_PHA_MB() == 1);
                            hg_op.cnt_posa ++;
                        }
                        else if(INTCON2bits.INTEDG2 == 0)
                        {
                            while(READ_PHA_MB() == 0);
                            hg_op.cnt_posa ++;
                        }
                        
                        if(hg_op.cnt_posa == (100 * 4))
                        {
                                STOP_B();
                                hg_op.drops_sa = 0;
                                hg_op.drops_push =1;;
                        
                        }
                        
                        
    
                    }
                    else if(hg_op.drops_sb == 1)
                    {
                         hg_op.cnt_posb ++;
                         if(hg_op.cnt_posb == (100 * 4 + 0))
                        {
                                STOP_B();
                                hg_op.drops_sb = 0;
                                hg_op.drops_sa  =1;
                        
                        }
                         
                        if(INTCON2bits.INTEDG2 == 1)
                        {
                           while(READ_PHA_MB() == 0);
                           hg_op.cnt_posb ++;
                        }
                        else if(INTCON2bits.INTEDG2 == 0)
                        {
                               while(READ_PHA_MB() == 1);
                               hg_op.cnt_posb ++;
                        }
                   
                         
                        if(hg_op.cnt_posb == (100 * 4 + 0))
                        {
                                STOP_B();
                                hg_op.drops_sb = 0;
                                hg_op.drops_sa  =1;
                        
                        }
                         
                         
                         
                        
                    }

                }
                else if(hg_op.working_mode == WORK_MODE_DROP)
                {

                }
                else if(hg_op.working_mode == WORK_MODE_C)
                {

                }
                else
                {

                }

             
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
    TMR0=0; // 
    
    
	T0IE=1; // 
	GIE=1;  // 
    T0CONbits.TMR0ON =1;

}