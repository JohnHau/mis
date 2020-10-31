 #include <xc.h>
 #include <stdio.h>
//#include "Ad.h"
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
          












int xn=0;
int ann=0;
uint8_t prev_edge =0;
uint8_t cur_edge =0;
uint16_t cnt_push =0;



uint16_t bv =0;
uint16_t cv =10;
uint16_t dv =10;
uint32_t msleep =0;
void main(void)                
{ 

    
    uart_init();
    AD_init();
    
    HG_init();
  
    MotorDriveInit();
    Timer1Init();
    

    
//==========================================
    while(1)
    {
        HG_interface();
    }

    
//==========================================
    
    
    
    

    
    //==============================================
    
    
    cur_state_phb_ma=0;
    prev_state_phb_ma=0;
    cnt_ma = 0;
    cnt_mb = 0;
    

    
    
    

    
    
    //hg_op.need_reset =1;
    hg_op.need_reset =0;
    hg_op.cur_working_mode = WORK_MODE_DROPS;//now we assume working in DROPS ;
    hg_op.cnt_target_posrst = POS_4_RST;     //len=4mm
    hg_op.needle_len = LEN_9_MM;
    hg_op.status_powerup = STATUS_SLEEP;
    
    
    while(1)
    {
    
        
        #if 1
        if( hg_op.status_powerup == STATUS_SLEEP)
        {
            printf("sleep mode\r\n");
            //SLEEP();
           
        }
       #endif
        

        if(hg_op.need_reset)
        {
           
            //if(LP_BUTTON == 0)
            if(0)//bug to fix
            { 
                STOP_B(); 
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                //while(hg_op.posrst == 0)
                while(hg_op.cnt_posrst < 600)
                {
                    INPUT3_BH();
                    delay_pwm(16*5);
                    INPUT3_BL();
                    delay_pwm(16);
                    
                    //hg_op.cnt_posrst ++;
                }
                
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                  
            }
            
   
            STOP_B(); 
            hg_op.status_hit_lp = 0;
            ENABLE_BH();
            while(hg_op.status_hit_lp == 0)// search for  lp point
            {
                INPUT4_BH();
                delay_pwm(16*7);
                INPUT4_BL();
                delay_pwm(16);        
            }
            
            STOP_B();    
            
            if(hg_op.needle_len == LEN_13_MM)
            {
                hg_op.need_reset =0;
                //STOP_B();
            }
            else
            {
                ENABLE_BH();
                
                
#if 1      
              
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                while(hg_op.posrst == 0)
                {
                    INPUT3_BH();
                    delay_pwm(16*7);
                    INPUT3_BL();
                    delay_pwm(16);
                }
#endif
                
              
       
                
                
                STOP_B(); 
            }
           
            hg_op.need_reset =0;
            hg_op.status_hit_lp =0;
            hg_op.cnt_posrst =0;
            hg_op.posrst =0;
        }
        
#if 0  
        if(hg_op.status_hit_lp == 1)
        {
            hg_op.need_reset =1;  
            hg_op.status_hit_lp =0;
            hg_op.cnt_posa =0;
            hg_op.posa =0;
        }
#endif
        else
        {
       //=================================================
#if 0
            if(LP_BUTTON == 0)
            { 
                STOP_B(); 
                hg_op.cur_working_mode = WORK_MODE_STOP;
                hg_op.need_reset =1;
                
             }
#endif
            
            
        //================================================    
            
            if(hg_op.working_mode == WORK_MODE_DROPS)
            {
                
                //if(ACTION_BUTTON  == 1)
                if(0)
                {
                        STOP_B();
                        //==========================================================
                        REVERSE_RUN_A();   
                        //delay_pwm(300 * 16);
                        delay_pwm(300 * 30);
                        STOP_A();

                        //==========================================================

                        hg_op.acting_flag =0;
                        hg_op.working_mode = WORK_MODE_STOP; 
                        hg_op.need_reset =1;  
                    
                    
                }
                else
                {
                       
                    
                       if(hg_op.drops_sa == 1)
                        {
                           
                           
                           hg_op.cnt_posa =0;
                           //printf("sa begin %d\r\n",hg_op.cnt_posa); 
                            //REVERSE_RUN_B();  
                            //di();
                            //FORWARD_RUN_B(); 
                            
                            if( hg_op.needle_len == LEN_13_MM)   
                            {
                                
                                ENABLE_BH();INPUT3_BH();
                                while(hg_op.cnt_posa < POS_13MM_SA);
                            }
                            else
                            {
                           
                                // ann =0; xn = 0;
                                 ENABLE_BH();INPUT3_BH();
                                 delay_pwm(300 * STARTUP_CNT_MA);/*delay_pwm(STARTUP_PWM_MA * STARTUP_CNT_MA);*/  
                            }
                           STOP_B();
                           //while( xn < 1000 && hg_op.cnt_posa < 40)
                            //while(hg_op.cnt_posa < 120)
       
                            
                            //printf("c===-hg_op.cnt_posa is %d\r\n", hg_op.cnt_posa );
                            //printf("here\r\n");
                             
                             //INPUT3_BH();
                            //while(1);
                            

                            //while(hg_op.drops_sa == 1);
                            //delay_f(INTERVAL_F);
                             delay_pwm(300 * INTERVAL_F);
                            printf("c-hg_op.cnt_posa is %d\r\n", hg_op.cnt_posa );
                            hg_op.drops_sa = 0;
                            hg_op.drops_sb = 0;
                            hg_op.drops_push = 1;
                        }
                        else if(hg_op.drops_push == 1)
                        //else if(0)
                        {

                            
                            
                             //FORWARD_RUN_A();   
                             //delay_pwm(300 * 30);
                             //STOP_A();
                             
                             
                           #if 1

                               prev_edge =0;
                               cur_edge =0;
                               cnt_push =0;

                               FORWARD_RUN_A();   
                               
#if 0
                               delay_pwm(300 * 33);
                               STOP_A();
                               
#endif
                               
                                
#if 1   
                               while(cnt_push < 140)//146
                               {
                                   while(READ_PHB_MA() == 0);
                                   cnt_push ++;
                                   while(READ_PHB_MA() == 1);
                                   cnt_push ++;

                               }
#endif
                               
#if 0
                               while(cnt_push < 20)
                               {
                                   cur_state_phb_ma = READ_PHB_MA();
                                   if(cur_state_phb_ma != prev_state_phb_ma)
                                   {
                                      cnt_push ++;
                                      prev_state_phb_ma = cur_state_phb_ma;   
                                   }

                               }
#endif
                               STOP_A();
                               
                               
                               
                               
#if 0
                              prev_edge =0;
                              cur_edge =0;
                              cnt_push =0;

                               REVERSE_RUN_A();   
                               while(cnt_push < 10)
                               {
                                   cur_state_phb_ma = READ_PHB_MA();
                                   if(cur_state_phb_ma != prev_state_phb_ma)
                                   {
                                      cnt_push ++;
                                      prev_state_phb_ma = cur_state_phb_ma;   
                                   }

                               }

                               STOP_A();
#endif
                           #endif

                            
                            //delay_f(INTERVAL_F);
                            delay_pwm(300 * INTERVAL_F);
                            hg_op.drops_sa = 0;
                            hg_op.drops_push = 0;
                            hg_op.drops_sb = 1;


                        }
                        else if(hg_op.drops_sb == 1)
                        {
                           
                           
                            hg_op.cnt_posb =0;
                            //printf("sb begin %d\r\n",hg_op.cnt_posb); 
                             //FORWARD_RUN_B();  
                            //REVERSE_RUN_B();  
                            
                            
                            if(hg_op.needle_len == LEN_13_MM)
                            {
                                ENABLE_BH();INPUT4_BH();
                                //while( hg_op.cnt_posb < POS_13MM_SB);
                                
                                while(LP_BUTTON == 1);
                                
                                
                            }
                            else
                            {
                                //ann = 0;xn =0; 
                                ENABLE_BH();INPUT4_BH();delay_pwm(300 * STARTUP_CNT_MB);
                            }
                            STOP_B();
                            //while( xn < 1000 &&  hg_op.cnt_posb < 40 )
                            //while(hg_op.cnt_posb < 120)

                            
                            //printf("z===-hg_op.cnt_posb is %d\r\n", hg_op.cnt_posb);
                            //INPUT4_BH();
                            
                            
#if 0
                             xn =0;
                              while(hg_op.drops_sb == 1  && xn <1400)
                              {
                                  //delay_pwm(300);
                                  delay_pwm(3);
                                  xn ++;
                              }
                            //delay_pwm(300*15);
                            INPUT4_BL();
                            printf("x-hg_op.cnt_posb is %d\r\n", hg_op.cnt_posb);
                            delay_pwm(300*12);
                            printf("y-hg_op.cnt_posb is %d\r\n", hg_op.cnt_posb);
                            INPUT4_BH();
                           
#endif
                            
                            //while(hg_op.drops_sb == 1);
                            delay_pwm(300 * INTERVAL_F);
                            printf("z-hg_op.cnt_posb is %d\r\n", hg_op.cnt_posb);
                           
                            //hg_op.drops_sb = 0;
                            //hg_op.drops_push =0;
                            //hg_op.drops_sa = 1;
                            
                           //===================================================
                             if(ACTION_BUTTON  == 1)
                             {
                        
                                    STOP_B();
                                    STOP_A();
                                //==========================================================
                                   REVERSE_RUN_A();   
                                   //delay_pwm(300 * 16);
                                   //delay_pwm(300 * 30);
                                   delaynus(30* 1000);
                                   STOP_A();

                               //==========================================================
                                    
     

                                    hg_op.drops_sa = 0;
                                    hg_op.drops_sb = 0;
                                    hg_op.drops_push = 0;
                                    
                                    
                                    hg_op.acting_flag =0;
                                    hg_op.working_mode = WORK_MODE_STOP; 
                                    hg_op.need_reset =0;  
                    
                    
                             }
                             else if(ACTION_BUTTON  == 0)
                             {
                                  hg_op.drops_sb = 0;
                                  hg_op.drops_push =0;
                                  hg_op.drops_sa = 1;
                             }
                           
                            
                           //===================================================
                            
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
        
        //HG_interface();

    }
    
}


 
