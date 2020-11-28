#include <xc.h>
#include<stdint.h>	
 #include <stdio.h>
#include "Timer.h"
#include "Key.h"
#include "Beep.h"
#include "Oled.h"
#include"MotorDrive.h"
#include "gui.h"

unsigned char flag =0;


uint16_t tva=0;
uint16_t tvb=0;
uint8_t flag_tv =0xff;

uint16_t tv_s[10]={0};

uint8_t  tv_cnt =0;

uint8_t old_c = 0;

uint16_t mbcnt=0;
uint8_t tflag =1;
uint8_t ttte =0;

uint32_t  tmcnt =0;

extern uint16_t bv;
extern uint16_t cv;
extern uint16_t dv;


uint16_t action_btn_cnt =0;

#if defined (TEST_MODE)     
    static uint32_t test_mode_cnt=0;
    static uint32_t test_mode_break_cnt=0;
#endif

//void __interrupt(high_priority) ISR(void)
//void __interrupt(high_priority) ISR(void)
void __interrupt ISR(void)
{
    uint8_t temp;
    static uint32_t tcnt=0;
    static uint8_t cnt_action_btn =0;
    


//===============================
#if 1    
    
    
    
    if(INTCON3bits.INT2IF)
    {
        INTCON3bits.INT2IF = 0;
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
        //====================================================================== 
        //PID
        //======================================================================   
#if 0
        if( INTCON2bits.INTEDG2 == 1)//falling edge
        {
                 if(READ_PHA_MB() == 0)  //falling   
                 {
                   r_motor.myInput ++;
                 }
                 else if(READ_PHA_MB() == 1)
                 {
                   r_motor.myInput --;
                 }

        }
        else if( INTCON2bits.INTEDG2 == 0)//rising edge
        {

                 if(READ_PHA_MB() == 0)  //falling   
                 {
                   r_motor.myInput --;
                 }
                 else if(READ_PHA_MB() == 1)
                 {
                    r_motor.myInput ++;
                 }                  
        }

#endif
        //======================================================================
        
        
        //-> L
        //<- H
         if(hg_op.need_reset)
         {
             
             //if(hg_op.status_hit_lp == 1 )
             if(1)
             {
                 
                //hg_op.cnt_posrst ++;
                                  
                    if(hg_op.in_reset == 1)
                    {
                       
                        
                        hg_op.cnt_posrst ++;  
//==============================================================================   
#if 0
                       if( INTCON2bits.INTEDG2 == 1)//falling edge
                       {
                                if(READ_PHA_MB() == 0)  //falling   
                                {
                                 hg_op.cnt_posrst ++;  
                                }
                                else if(READ_PHA_MB() == 1)
                                {
                                  hg_op.cnt_posrst --;
                                }
                       
                       
                       
                       }
                       else if( INTCON2bits.INTEDG2 == 0)//rising edge
                       {
                           
                                if(READ_PHA_MB() == 0)  //falling   
                                {
                                 hg_op.cnt_posrst --;
                                }
                                else if(READ_PHA_MB() == 1)
                                {
                                  hg_op.cnt_posrst ++;       
                                }                  
                       }
#endif
//==============================================================================                       
    
                    }
                 
                         
                if( hg_op.cnt_posrst == hg_op.cnt_target_posrst)
                {
                    //hg_op.posrst =1;
                    //hg_op.in_reset =0;
                    //STOP_B();

                }
                              
#if 0          
                 if(INTCON2bits.INTEDG2 == 1)
                 {
                     //temp = READ_PHA_MB();
                     //while(READ_PHA_MB() == temp);
                     while(READ_PHA_MB() == 1);
                    hg_op.cnt_posrst ++;
                 }
                 else if(INTCON2bits.INTEDG2 == 0)
                 {
                    // temp = READ_PHA_MB();   
                     //while(READ_PHA_MB() == temp);
                     while(READ_PHA_MB() == 0);
                        hg_op.cnt_posrst ++;
                 }
#endif
           
#if 0            
                   temp = READ_PHA_MB();   
                   while(READ_PHA_MB() == temp);
                   hg_op.cnt_posrst ++;
                
#endif
                        
                
                
#if 0       
                 //if( hg_op.cnt_posrst == (300 * 4 + 0))
                 if( hg_op.cnt_posrst == hg_op.cnt_target_posrst)
                {
                    hg_op.posrst =1;
                    STOP_B();

                }
                  
#endif
                   
             }
         }
         else
         {      
                if(hg_op.working_mode == WORK_MODE_DROPS)
                {
                    if(hg_op.drops_sa == 1)
                    {
                       
                       //hg_op.cnt_pos_1mm ++; 

                       //======================================================= 
#if 0 
                       if(READ_PHA_MB() == 0)  //falling   
                       {
                        hg_op.cnt_posa ++;
                        //printf("ax");
                       }
                       else
                       {
                         hg_op.cnt_posa --;
                         printf("***************************ay\r\n");
                       }
#endif
                      
                       
                       
                       
                       
                       
                       
                       
                       
#if 1         
                       if( INTCON2bits.INTEDG2 == 1)//falling edge
                       {
                                if(READ_PHA_MB() == 0)  //falling   
                                {
                                 
                                  
                                   hg_op.cnt_pos_1mm ++; 
                                }
                                else if(READ_PHA_MB() == 1)
                                {
                                  
                                   hg_op.cnt_pos_1mm --; 
                                }
                       
                       
                       
                       }
                       else if( INTCON2bits.INTEDG2 == 0)//rising edge
                       {
                           
                                if(READ_PHA_MB() == 0)  //falling   
                                {
                                  
                                  
                                    hg_op.cnt_pos_1mm --; 
                                }
                                else if(READ_PHA_MB() == 1)
                                {
                                   hg_op.cnt_pos_1mm ++; 
                                }
                           
                           
                       }
                       
#endif
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       //if( hg_op.cnt_posa  == (43*2))STOP_B();
                       
                       //=======================================================
                       
                       
                       
                        //if( hg_op.drops_sa == 1)
                        if(0)
                        {
#if 0
                        if(INTCON2bits.INTEDG2 == 1)
                        {
                            while(READ_PHA_MB() == 0);
                            hg_op.cnt_posa ++;
                        }
                        else if(INTCON2bits.INTEDG2 == 0)
                        {
                            while(READ_PHA_MB() == 1);
                            hg_op.cnt_posa ++;
                        }
#endif
                        
#if 0         
                   temp = READ_PHA_MB();   
                   //printf("temp-sa is %d\r\n",temp);
                   while(READ_PHA_MB() == temp);
                   hg_op.cnt_posa ++;
                
#endif
                        
#if 0   
                        if(hg_op.cnt_posa >= POS_INJECT_F)
                        {
                                STOP_B();
                                hg_op.drops_sa = 0;
                                hg_op.drops_push =1;;
                        
                        }
#endif
                        }
    
                    }
                    else if(hg_op.drops_sb == 1)
                    {
                        
                          //hg_op.cnt_pos_1mm --;
#if 0
                        temp = READ_PHB_MB();
                        if(temp  !=  old_c)
                        {
                            old_c = temp;
                            hg_op.cnt_pos_1mm --;
                        }
#endif
                        
                        //hg_op.cnt_posb ++;
                        //hg_op.cnt_pos_1mm --;
                       //=======================================================  
#if 0
                       if(READ_PHA_MB() == 0)     //falling edge
                       {
                        hg_op.cnt_posb --;
                         printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&by\r\n");
                       }
                       else
                       {
                         hg_op.cnt_posb ++;
                         
                        
                       }
#endif
                       
                       
                       
                       //hg_op.cnt_posb ++;
                        //r_motor.myInput ++;
#if 1
                       if( INTCON2bits.INTEDG2 == 1)//falling edge
                       {
                                if(READ_PHA_MB() == 0)  //falling   
                                {
                                
                                  tvb--;
                                  hg_op.cnt_pos_1mm ++;
                                }
                                else if(READ_PHA_MB() == 1)
                                {
                                  //tvb++;
                                  hg_op.cnt_pos_1mm --;
                                 
                                }
                       
                       
                       }
                       else if( INTCON2bits.INTEDG2 == 0)//rising edge
                       {
                           
                                if(READ_PHA_MB() == 0)  //falling   
                                {
                                  
                                  //tvb++;
                                  hg_op.cnt_pos_1mm --;
                                }
                                else if(READ_PHA_MB() == 1) 
                                {
                                  tvb--;
                                  hg_op.cnt_pos_1mm ++;
                                }
                           
                           
                       }
                       
#endif
                       
                       
                         
                         
                         
                         
                         //if(hg_op.drops_sb == 1)
                         if(0)
                         {
               
#if 0
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
#endif
                         
#if 0            
                   temp = READ_PHA_MB();   
                   while(READ_PHA_MB() == temp);
                   hg_op.cnt_posb ++;
                
#endif
          
#if 0
                     if(hg_op.cnt_posb >= POS_INJECT_R)
                        {
                                STOP_B();
                                hg_op.drops_sb = 0;
                                hg_op.drops_sa  =1;
                        
                        }
#endif
                         
                         }
                         
                        
                    }

                }
                else if(hg_op.working_mode == WORK_MODE_DROP)
                {

                }
                else if(hg_op.working_mode == WORK_MODE_C)
                {
                    if(hg_op.drops_sa == 1)
                    {
                        hg_op.cnt_posa ++;
                    }
                    else if(hg_op.drops_sb == 1)
                    {
                         hg_op.cnt_posb ++;
                    }
                }
                else if(hg_op.working_mode == WORK_MODE_TEST)
                {
                    if(hg_op.drops_sa == 1)
                    {
                        hg_op.cnt_posa ++;
                    }
                    else if(hg_op.drops_sb == 1)
                    {
                         hg_op.cnt_posb ++;
                    }
                 }
                else
                {

                }

             
         }
          
         
         

         
       //INTCON3bits.INT2IF = 0;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
#if 0
    if(T0IF)
    {
    
        tcnt ++;

        //if(tcnt > 500*1000UL)
        //if(tcnt > 125)//4ms
        if(tcnt > 500)//1ms
        {
        
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
                        display_num(MIDDLE,COL_PAGE0_DN, MODE_REVERSE | NUM_4);
                    }
                    else if(menu[3].parameter == 1)
                    {
                        display_num(MIDDLE,COL_PAGE0_DN, MODE_REVERSE | NUM_6);
                    }
                    else if(menu[3].parameter == 2)
                    {
                        display_num(MIDDLE,COL_PAGE0_DN, MODE_REVERSE | NUM_13);
                    }
 
                }
            }
            else if(menu[4].mode == MODE_BLINK)
            {
                
                if(flip == 1)
                {
                    display_n_blank(1,COL_PAGE0_EN, MODE_REVERSE);
                    flip =0;
                }
                else if(flip == 0)
                {
                    flip =1;
                    if(menu[4].parameter == 0)
                    {
                        display_num(MIDDLE,COL_PAGE0_EN, MODE_REVERSE | NUM_1);
                    }
                    else if(menu[4].parameter == 1)
                    {
                        display_num(MIDDLE,COL_PAGE0_EN, MODE_REVERSE | NUM_2);
                    }
 
                }
            }
            else if(menu[5].mode == MODE_BLINK)
            {
                
                if(flip == 1)
                {
                    display_n_blank(2,COL_PAGE0_FN, MODE_REVERSE);
                    flip =0;
                }
                else if(flip == 0)
                {
                    flip =1;
                    if(menu[5].parameter == 0)
                    {
                        //display_num(BOTTOM,COL_PAGE0_FN, MODE_REVERSE | NUM_2P5);
                        display_num(BOTTOM,COL_PAGE0_FN, MODE_REVERSE | NUM_2);
                    }
                    else if(menu[5].parameter == 1)
                    {
                        //display_num(BOTTOM,COL_PAGE0_FN, MODE_REVERSE | NUM_1P5);
                        display_num(BOTTOM,COL_PAGE0_FN, MODE_REVERSE | NUM_3);
                    }
                    else if(menu[5].parameter == 2)
                    {
                        display_num(BOTTOM,COL_PAGE0_FN, MODE_REVERSE | NUM_5);
                    }
                }
            }
            else if(menu[6].mode == MODE_BLINK)
            {
                
                if(flip == 1)
                {
                    
                    
                    if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                    {
                        display_n_blank(2,COL_PAGE0_GN, MODE_REVERSE);
                    }
                     else if(work_mode == WORK_MODE_DROPS) 
                     {
                         display_n_blank(2,COL_PAGE0_HN, MODE_REVERSE);
                     }
                    flip =0;
                }
                else if(flip == 0)
                {
                    flip =1;
                    if(menu[6].parameter == 0)
                    {
                       if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                       {
                        display_num(BOTTOM,COL_PAGE0_GN, MODE_REVERSE | NUM_3);
                       }
                       else if(work_mode == WORK_MODE_DROPS) 
                       {
                           display_num(BOTTOM,COL_PAGE0_HN, MODE_REVERSE | NUM_250);
                       }
                    }
                    else if(menu[6].parameter == 1)
                    {
                         if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                         {
                           display_num(BOTTOM,COL_PAGE0_GN, MODE_REVERSE | NUM_3);
                         }
                         else if(work_mode == WORK_MODE_DROPS) 
                         {
                              display_num(BOTTOM,COL_PAGE0_HN, MODE_REVERSE | NUM_100);
                          }
                    }
                    else if(menu[6].parameter == 2)
                    {
                         if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                         {
                           display_num(BOTTOM,COL_PAGE0_GN, MODE_REVERSE | NUM_3);
                         }
                         else if(work_mode == WORK_MODE_DROPS) 
                         {
                              display_num(BOTTOM,COL_PAGE0_HN, MODE_REVERSE | NUM_200);
                          }
                    }
 
                }
            }
#if 0
            else if(menu[7].mode == MODE_BLINK)
            {
                
                if(flip == 1)
                {
                    display_n_blank(2,COL_PAGE0_HN, MODE_REVERSE);
                    flip =0;
                }
                else if(flip == 0)
                {
                    flip =1;
                    if(menu[7].parameter == 0)
                    {
                        //display_n1(0,COL_PAGE0_HN, MODE_REVERSE);
                        display_num(BOTTOM,COL_PAGE0_HN, MODE_REVERSE | NUM_250);
                    }
                    else if(menu[7].parameter == 1)
                    {
                        //display_n2(0,COL_PAGE0_HN, MODE_REVERSE);
                        display_num(BOTTOM,COL_PAGE0_HN, MODE_REVERSE | NUM_200);
                    }
 
                }
            }
#endif
            tcnt = 0;
        }

        T0IF = 0;
    
    }
    
    
#endif
    
    
    
    
    
#if 1
    if(INTCONbits.RBIF)
    {
        
        //----------------------------------------------------------------------
#if 0
        if(KEY_WAKE  == 0  && KEY_UP == 1 && KEY_DOWN ==1 && KEY_V ==1)
        {
            delay_nms(4);
            if(KEY_WAKE  == 0  && KEY_UP == 1 && KEY_DOWN ==1 && KEY_V ==1)
            {
                buzz();
                test_mode =0;

                if(hg_op.status_powerup == STATUS_SLEEP)
                {
                   hg_op.status_powerup = STATUS_WAKE;
                   LCD_On();
                   STOP_A();
                   STOP_B();
                   ENABLE_AH();   
                   ENABLE_BH(); 
                   printf("wake up\r\n");
                   hg_op.status_hit_lp = 0;
                   hg_op.need_reset =1;
                   hg_op.in_reset =0;
                   
                   hg_op.cnt_posa_std =0;
                   hg_op.cnt_posb_std =0;
                   
                   //Initial_LY096BG30();
                   config_LCD();
                   initial_ui_setting();
                   
                   #if 1
                    T0IE=1; // 
                    T0CONbits.TMR0ON =1;
                   #endif
                   
                }
                else if(hg_op.status_powerup == STATUS_WAKE)
                {
                    hg_op.status_powerup = STATUS_SLEEP;
                    LCD_Off();
                    
                    
                     write_buf[0]=0x25;  
	                 ee_WriteBytes(write_buf, 0x00, 1);
                     
                     
                    STOP_A();
                    STOP_B();
                    
                    ENABLE_AL();   
                    ENABLE_BL(); 
                    
                    
                    
                    
                    hg_op.need_reset =0;
                    printf("sleep\r\n");
                    
                }
            }
            
        }
#endif
        //----------------------------------------------------------------------
        
        
        
        
        
        
        
        
        
        if(ACTION_BUTTON  == 0)
        {
          
            //delaynus(50 * 1000);
            hg_op.acting_flag = 1;
            printf("act\n");
        }
        //buzz();
        //temp = PORTB;
        INTCONbits.RBIF=0;
        

    }
    
           
     if(INTCONbits.INT0IF)//LP_BUTTON
     {   
            //buzz();  
         //STOP_B(); 
        
         hg_op.status_hit_lp =1;
         printf("lp\r\n");
         // INTCON3bits.INT2IF = 0;////for test
             
        INTCONbits.INT0IF = 0;
                      
     }
        
        

#endif

#endif    
//========================================    
    
    
} 

void TimerInit(void)
{
	T0CS=0; //
	PSA=0; // 
    
#if 0
	T0PS2=1;
	T0PS1=0;
	T0PS0=1; // 4ms
#endif
    
    T0PS2=0;
	T0PS1=1;
	T0PS0=1; // 1ms
    
    
    
	T08BIT =1;//
	T0IF=0; // 
    TMR0=0; // 
    
    
	T0IE=0; // 
	GIE=1;  // 
    T0CONbits.TMR0ON =0;

}

void Timer1Init(void)
{
	
    
    T1CONbits.T1CKPS = 2;//scale 4
    T1CONbits.RD16 =1;
    T1CONbits.TMR1ON =0;
    
    
    
    //===============================
#if 0
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
#endif

}








void delaynus(uint16_t n)
{
 
    TMR1 =0;
    T1CONbits.TMR1ON =1;
    
    while(TMR1 < n);
    
    T1CONbits.TMR1ON =0;
    
    
}

