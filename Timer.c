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
                       
                        
                        //hg_op.cnt_posrst ++;  
//==============================================================================   
#if 1
                       if( INTCON2bits.INTEDG2 == 1)//falling edge
                       {
                                if(READ_PHA_MB() == 0)  //falling   
                                {
                                 hg_op.cnt_posrst ++;  //ori
                               
                                }
                                else if(READ_PHA_MB() == 1)
                                {
                                  hg_op.cnt_posrst --;//ori
                                 
                                }
                       
                       
                       
                       }
                       else if( INTCON2bits.INTEDG2 == 0)//rising edge
                       {
                           
                                if(READ_PHA_MB() == 0)  //falling   
                                {
                                 hg_op.cnt_posrst --;//ori
                                 
                                }
                                else if(READ_PHA_MB() == 1)
                                {
                                  hg_op.cnt_posrst ++;  //ori
                                  
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
                                   hg_op.cnt_posa ++;
                                }
                                else if(READ_PHA_MB() == 1)
                                {
                                  
                                   hg_op.cnt_pos_1mm --; 
                                   hg_op.cnt_posa --;
                                }
                       
                       }
                       else if( INTCON2bits.INTEDG2 == 0)//rising edge
                       {
                           
                                if(READ_PHA_MB() == 0)  //falling   
                                {
                                    hg_op.cnt_pos_1mm --; 
                                    hg_op.cnt_posa --;
                                }
                                else if(READ_PHA_MB() == 1)
                                {
                                   hg_op.cnt_pos_1mm ++; 
                                   hg_op.cnt_posa ++;
                                }
                           
                           
                       }
                       
#endif
                       
                       
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
                                       
                         }
                         
                        
                    }
                    //return ;
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
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
#if 1
    if(T0IF)
    {
    
        tcnt ++;

        //if(tcnt > 500*1000UL)
        if(tcnt > 125)//4ms
        //if(tcnt > 500)//1ms
        {
            flag_blink =1;
            tcnt = 0;
        }

        T0IF = 0;
    
    }
    
    
#endif
    
    
    
    
    
#if 1
    if(INTCONbits.RBIF)
    {
        
        //----------------------------------------------------------------------
#if 1
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
                   hg_op.needle_len = NEEDLE_LEN_4_MM;
                   //Initial_LY096BG30();
                   
                   config_LCD();
                   initial_ui_setting();
                   ENABLE_ENCODER_PHB_MB();
                   
                }
                else if(hg_op.status_powerup == STATUS_WAKE)
                {
                    hg_op.status_powerup = STATUS_SLEEP;
                    LCD_Off();
                    
                    write_buf[0]=0x25;  
	                ee_WriteBytes(write_buf, 0x00, 1);
                      
                    STOP_A();
                    STOP_B();
                    
                    //hg_op.needle_len = NEEDLE_LEN_4_MM;
                    //hg_op.need_reset =1;
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
         //printf("lp\r\n");
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
    
#if 1
	T0PS2=1;
	T0PS1=0;
	T0PS0=1; // 4ms
#endif
    
#if 0
    T0PS2=0;
	T0PS1=1;
	T0PS0=1; // 1ms
    
#endif
    
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

