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
int xn=0;
int ann=0;
uint8_t prev_edge =0;
uint8_t cur_edge =0;
uint16_t cnt_push =0;



uint16_t bv =0;
uint16_t cv =10;
uint16_t dv =10;
uint32_t msleep =0;


uint16_t cnta_mb =0;
uint16_t cntb_mb =0;



void main(void)
{
    flag_power_up  =1;
    uart_init();
    AD_init();
    
    HG_init();
  
    MotorDriveInit();
    
    Timer1Init();

    
    cur_state_phb_ma=0;
    prev_state_phb_ma=0;
    cnt_ma = 0;
    cnt_mb = 0;

    //hg_op.need_reset =1;
    hg_op.need_reset =0;
    hg_op.cur_working_mode = WORK_MODE_DROPS;//now we assume working in DROPS ;
    //hg_op.cur_working_mode = WORK_MODE_C;
    hg_op.cnt_target_posrst = POS_4_RST;     //len=4mm
    hg_op.needle_len = NEEDLE_LEN_4_MM;
    hg_op.status_powerup = STATUS_SLEEP;
    hg_op.working_mode = WORK_MODE_STOP;
   
    hg_op.status_hit_lp = 0;
     

    
    hg_op.cnt_pos_1mm =0;
    
    
    //hg_op.working_mode = WORK_MODE_DROPS;
    
    while(1)
    {
        

        if( hg_op.status_powerup == STATUS_SLEEP)
        //if(0)
        {
            printf("sleep mode\r\n");
            NOP();NOP();NOP();
            SLEEP();
            NOP();NOP();NOP();
            
           
        }


        if(hg_op.need_reset)
        {
            if(LP_BUTTON == 0)
            //if(0)//bug to fix
            { 
                STOP_B(); 
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                hg_op.cnt_target_posrst = 600;//max  
                //while(hg_op.posrst == 0)
                while(hg_op.cnt_posrst < 300)
                {
                    INPUT3_BH();
                    delay_pwm(16*2);
                    INPUT3_BL();
                    delay_pwm(16);
                }
               
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                  
            }
            
            
                   
            if(hg_op.needle_len == NEEDLE_LEN_4_MM)
            {
                 hg_op.cnt_target_posrst = 300;//600;//600;//300;//600;//100;//600//POS_4_RST;//1200;POS_4_RST;  
            }
            else if(hg_op.needle_len == NEEDLE_LEN_6_MM)
            {
                 hg_op.cnt_target_posrst = POS_6_RST;  
            }
            else if(hg_op.needle_len == NEEDLE_LEN_13_MM)
            {
                 hg_op.cnt_target_posrst = POS_13_RST;  
            }
            
            STOP_B(); 
            
            
            hg_op.status_hit_lp = 0;
            ENABLE_BH();
            while(hg_op.status_hit_lp == 0)// search for  lp point
            {
                INPUT4_BH();
                delaynus(10);
                INPUT4_BL();
                delaynus(10);
                
            }
            
            STOP_B();    
            if(hg_op.needle_len == NEEDLE_LEN_13_MM)
            {
                hg_op.need_reset =0;
            }
            else
            {
                ENABLE_BH();
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                hg_op.in_reset = 1;
                while(hg_op.cnt_posrst < hg_op.cnt_target_posrst)
                {
                    INPUT3_BH();
                    delaynus(10);
                    INPUT3_BL();
                    delaynus(10);
                }
                
                INPUT3_BL();
                INPUT4_BH();
                //delaynus(15*1000);
                bv = READ_PHB_MB();
                START(); 
                while(bv == READ_PHB_MB());
                STOP();
                if(TMR1 > INTV)
                {
                    STOP_B();
                    break;
                }

                STOP_B(); 
            }
           
            
            printf("A-reset len is %d\r\n",hg_op.cnt_posrst);
            delaynus(50 * 1000);
               
            printf("B-reset len is %d\r\n",hg_op.cnt_posrst);    
            hg_op.need_reset =0;
            hg_op.status_hit_lp =0;
            hg_op.cnt_posrst =0;
            hg_op.posrst =0;
            
            ENABLE_TIMER();     
        }
        else
        {
            /*******************************************************************************/       

            if(hg_op.working_mode == WORK_MODE_DROPS)
            {
                //printf("in in drops mode\r\n");
                //if(ACTION_BUTTON  == 1)
                if(0)
                {
                        STOP_B();
                        REVERSE_RUN_A();   
                        //delay_pwm(300 * 16);
                        STOP_A();
                        hg_op.acting_flag =0;
                        hg_op.working_mode = WORK_MODE_STOP; 
                        hg_op.need_reset =1;  
                }
                else
                {
                    if(hg_op.drops_sa == 1)
                    {
                        //printf("in sa drops\n");   
                       
                            if( hg_op.needle_len == NEEDLE_LEN_13_MM)   
                            {
                                ENABLE_BH();INPUT3_BH();
                                while(hg_op.cnt_pos_1mm < POS_13MM_SA);
                            }
                            else
                            {
                                STOP_B();                         
                                ENABLE_BH();
                                INPUT4_BL();
                                INPUT3_BH();

                                while(hg_op.cnt_pos_1mm < 150);//300
                                
                                
                              
                                INPUT4_BH();
                                INPUT3_BL();
                                delaynus(15*1000);
#if 0
                                while(1)
                                {
                                    
                                    
                                    bv = READ_PHB_MB();
                                    START();
                                    while(bv == READ_PHB_MB());
                                    STOP();
                                   if(TMR1 > INTV)
                                    {
                                        STOP_B();
                                        break;
                                    }
                                    
                                }
                                
#endif
                                
                                
                               STOP_B();                        
                            
                               printf("333-hg_op.cnt_posa is %d\r\n", hg_op.cnt_pos_1mm );
                          
                                //delaynus(hg_op.work_freq * 1000);

                               DELAY_T1_1SEC(); DELAY_T1_1SEC();

                                printf("444-hg_op.cnt_posa is %d\r\n", hg_op.cnt_pos_1mm );
                                hg_op.drops_sa = 0;
                                hg_op.drops_sb = 0;
                                hg_op.drops_push = 1;
                            }
                    }//end drops_sa
                    else if(hg_op.drops_push == 1)
                    {
                            //prev_edge =0;
                            //cur_edge =0;
                            cnt_push =0;

                            FORWARD_RUN_A();                           
                            //while(cnt_push < 140)//146
                            while(cnt_push < hg_op.push_len)//146
                               //while(0)//146
                            {
                                   while(READ_PHB_MA() == 0);
                                   cnt_push ++;
                                   while(READ_PHB_MA() == 1);
                                   cnt_push ++;

                            }
                               

                            STOP_A();

                            //delaynus(hg_op.work_freq * 1000);

                            hg_op.drops_sa = 0;
                            hg_op.drops_push = 0;
                            hg_op.drops_sb = 1;


                    }//end drops_push            
                    else if(hg_op.drops_sb == 1)
                    {
                           
                           
                            //hg_op.cnt_posb =0;
                            
                            //printf("sb begin %d\r\n",hg_op.cnt_posb); 

                            if(hg_op.needle_len == NEEDLE_LEN_13_MM)
                            {
                                ENABLE_BH();INPUT4_BH();
                                while(LP_BUTTON == 1);
                            }
                            else
                            {
                                ENABLE_BH();
                                INPUT3_BL();
                                INPUT4_BH();
                                while(hg_op.cnt_pos_1mm > 0);//300         
                                INPUT3_BH();
                                INPUT4_BL();                              
                                 
                                delaynus(15*1000);
#if 0
                                while(1)
                                {
                                    bv = READ_PHB_MB();
                                    START(); 
                                    while(bv == READ_PHB_MB());
                                    STOP();
                                   if(TMR1 > INTV)
                                    {
                                        STOP_B();
                                        break;
                                    }         
                                }                           
#endif
                                
                            }
             
                            STOP_B();   
                            printf("888-hg_op.cnt_posb is %d\r\n", hg_op.cnt_pos_1mm);

                            //delaynus(hg_op.work_freq * 1000);
                            DELAY_T1_1SEC(); DELAY_T1_1SEC();
                            printf("999-hg_op.cnt_posb is %d\r\n=======\r\n", hg_op.cnt_pos_1mm);
                          
                       
                             if(ACTION_BUTTON  == 1)
                             {
                                    STOP_B();
                                    STOP_A();

                                   REVERSE_RUN_A();   
                                   //delaynus(30* 1000);
                                   
                                   while(cnt_push < 260)
                                   {
                                        while(READ_PHB_MA() == 0);
                                        cnt_push ++;
                                        while(READ_PHB_MA() == 1);
                                        cnt_push ++;

                                    }
                                   
                                   STOP_A();

                                    hg_op.drops_sa = 0;
                                    hg_op.drops_sb = 0;
                                    hg_op.drops_push = 0;
                                    
                                    
                                    hg_op.acting_flag =0;
                                    //hg_op.working_mode = WORK_MODE_STOP; 
                                    
                                     if(hg_op.needle_len == NEEDLE_LEN_13_MM)
                                     {
                                       hg_op.need_reset =0;  
                                     }
                                     else
                                     {
                                       hg_op.need_reset =1;  
                                     }
                                    
                                      hg_op.working_mode = WORK_MODE_STOP;
                    
                             }
                             else if(ACTION_BUTTON  == 0)
                             {
                                  hg_op.drops_sb = 0;
                                  hg_op.drops_push =0;
                                  hg_op.drops_sa = 1;
                             }
                    }
                    
                    
                    
                    
                    
                }
            }//end WORK_MODE_DROPS
#if 1
            else if(hg_op.working_mode == WORK_MODE_C)
            {
                 printf("in in C mode\r\n");
                //if(ACTION_BUTTON  == 1)
                if(0)
                {
                        STOP_B();
                        //==========================================================
                        REVERSE_RUN_A();   
                        delaynus(30 * 1000);
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
                            
                            if( hg_op.needle_len == NEEDLE_LEN_13_MM)   
                            {
                                
                                ENABLE_BH();INPUT3_BH();
                                while(hg_op.cnt_posa < POS_13MM_SA);
                            }
                            else
                            {
                                 ENABLE_BH();INPUT3_BH();
                                 delaynus(14 * 1000);
                                 
                            }
                           STOP_B();

                            delaynus(50 * 1000);
                            delaynus(50 * 1000);
                            printf("c-hg_op.cnt_posa is %d\r\n", hg_op.cnt_posa );
                            hg_op.drops_sa = 0;
                            hg_op.drops_sb = 0;
                            hg_op.drops_push = 1;
                        }
                       
                       
                        if(hg_op.drops_push == 1)
                        {

                             //FORWARD_RUN_A();   
                             //delay_pwm(300 * 30);
                             //STOP_A();
                             

                               //prev_edge =0;
                               //cur_edge =0;
                            
                               //cnt_push =0;
                               //FORWARD_RUN_A();    
                               while(ACTION_BUTTON == 0)
                               {
                                       cnt_push =0;
                                       FORWARD_RUN_A();    
                                       //while(cnt_push < hg_op.push_len)//146
                                       while(cnt_push < 146)//146
                                       {
                                            while(READ_PHB_MA() == 0);
                                            cnt_push ++;
                                            while(READ_PHB_MA() == 1);
                                            cnt_push ++;

                                       }
                                       STOP_A();
                                       delaynus(50 * 1000);

                                   printf("cycle push\r\n");
                               }
                               
                                printf("should be here\r\n");
                               STOP_A();
                           
                            delaynus(50* 1000);
                            hg_op.drops_sa = 0;
                            hg_op.drops_push = 0;
                            hg_op.drops_sb = 1;
                        }
                       
                        if(hg_op.drops_sb == 1)
                        { 
                            hg_op.cnt_posb =0;
                            //printf("sb begin %d\r\n",hg_op.cnt_posb); 
                         
                            if(hg_op.needle_len == NEEDLE_LEN_13_MM)
                            {
                                ENABLE_BH();INPUT4_BH();
                                while(LP_BUTTON == 1);
                            }
                            else
                            {
                                ENABLE_BH();
                                INPUT4_BH();
                                
                                delaynus(STARTUP_CNT_SB_MB * 1000);
                            }
                            STOP_B();

                            //printf("z===-hg_op.cnt_posb is %d\r\n", hg_op.cnt_posb);
                            //INPUT4_BH();
                            

                            //delaynus(hg_op.work_freq * 1000);
                            delay_pwm(hg_op.work_freq * 300);
                            printf("z-hg_op.cnt_posb is %d\r\n", hg_op.cnt_posb);
                           
                             if(ACTION_BUTTON  == 1)
                             {
                                   delaynus(15 * 1000);
                                    if(ACTION_BUTTON  == 1)
                                    {
                                    STOP_B();
                                    STOP_A();


                                   REVERSE_RUN_A();   
                                   //delaynus(30* 1000);
                                   cnt_push = 0;
                                   //while(cnt_push < 14)
                                   while(cnt_push < 120)
                                   {
                                        while(READ_PHB_MA() == 0);
                                        cnt_push ++;
                                        while(READ_PHB_MA() == 1);
                                        cnt_push ++;

                                    }
                                   
                                   STOP_A();

                                    hg_op.drops_sa = 0;
                                    hg_op.drops_sb = 0;
                                    hg_op.drops_push = 0;
                                    
                                    
                                    hg_op.acting_flag =0;
                                    //hg_op.working_mode = WORK_MODE_STOP; 
                                    
                                     if(hg_op.needle_len == NEEDLE_LEN_13_MM)
                                     {
                                       hg_op.need_reset =0;  
                                     }
                                     else
                                     {
                                       hg_op.need_reset =1;  
                                     }
                                    
                                     hg_op.working_mode = WORK_MODE_STOP;
                             }
                             
                        }
                 
                }
                
                }
            }
                 
                
            
#endif
            
#if 0
            else if(hg_op.working_mode == WORK_MODE_DROP)
            {
 
            }
#endif
            
            
            
                
#if 1
            else if(hg_op.working_mode == WORK_MODE_TEST)
            {
                //printf("in in test mode\r\n");
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
                            
                            if( hg_op.needle_len == NEEDLE_LEN_13_MM)   
                            {
                                
                                INPUT3_BH();
                                ENABLE_BH();
                                
                                while(hg_op.cnt_posa < POS_13MM_SA);
                            }
                            else
                            {
                                INPUT3_BH(); 
                                ENABLE_BH();
                                 //delay_pwm(300 * STARTUP_CNT_MA);
                                 //delaynus(STARTUP_CNT_MA_TEST * 1000);
                                 
                                while(hg_op.cnt_posa < 20)
                                {
                                    //delaynus(330);
                                    //INPUT3_BH(); 
                                    //delaynus(330);
                                    //INPUT3_BL(); 
                                    
                                   while(READ_PHB_MB() == 0);
                                   hg_op.cnt_posa ++;
                                   while(READ_PHB_MB() == 1);
                                   hg_op.cnt_posa ++;
                                
                                }
                            }
                           STOP_B();
                           
                            //delaynus(hg_op.work_freq * 1000);
                             delay_pwm(hg_op.work_freq * 300);
                            //printf("c-hg_op.cnt_posa is %d\r\n", hg_op.cnt_posa );
                            hg_op.drops_sa = 0;
                            hg_op.drops_sb = 0;
                            hg_op.drops_push = 1;
                        }
                        else if(hg_op.drops_push == 1)
                        {
                           #if 1

                               //prev_edge =0;
                               //cur_edge =0;
                               cnt_push =0;

                               FORWARD_RUN_A();                           

                               //while(cnt_push < 140)//146
                               while(cnt_push < hg_op.push_len)//146
                               {
                                   while(READ_PHB_MA() == 0);
                                   cnt_push ++;
                                   while(READ_PHB_MA() == 1);
                                   cnt_push ++;

                               }

                               
                               STOP_A();
                               
                           #endif

                            //delaynus(hg_op.work_freq * 1000);
                             delay_pwm(hg_op.work_freq * 300);
                            hg_op.drops_sa = 0;
                            hg_op.drops_push = 0;
                            hg_op.drops_sb = 1;


                        }
                        else if(hg_op.drops_sb == 1)
                        {
                            hg_op.cnt_posb =0;

                            if(hg_op.needle_len == NEEDLE_LEN_13_MM)
                            {
                                INPUT4_BH();
                                ENABLE_BH();
                                while(LP_BUTTON == 1);
                            }
                            else
                            {
                                INPUT4_BH();
                                ENABLE_BH();
                                
                                //delay_pwm(300 * STARTUP_CNT_MB);
                                // delaynus(STARTUP_CNT_MB_TEST * 1000);
                                 
                                while(hg_op.cnt_posb < 20)
                                {
                                    //delaynus(330);
                                    //INPUT4_BL();
                                    //delaynus(330);
                                    //INPUT4_BH();
                                    
                                    
                                   while(READ_PHB_MB() == 0);
                                   hg_op.cnt_posb ++;
                                   while(READ_PHB_MB() == 1);
                                   hg_op.cnt_posb ++;
                                    
                                    
                                    
                                }
                                 
                                 
                                 
                                 
                            }
                            STOP_B();

                            //delaynus(hg_op.work_freq * 1000);
                             delay_pwm(hg_op.work_freq * 300);
                            //printf("z-hg_op.cnt_posb is %d\r\n", hg_op.cnt_posb);
                           printf("in test mode\r\n");
                             //if(ACTION_BUTTON  == 1)
                             if(action_btn_cnt%2 == 0)
                             {
                                    STOP_B();
                                    STOP_A();

                                   REVERSE_RUN_A();   
                                   //delaynus(30* 1000);
                                   
                                   while(cnt_push < 14)
                                   {
                                        while(READ_PHB_MA() == 0);
                                        cnt_push ++;
                                        while(READ_PHB_MA() == 1);
                                        cnt_push ++;

                                    }
                                   
                                   STOP_A();

                                    hg_op.drops_sa = 0;
                                    hg_op.drops_sb = 0;
                                    hg_op.drops_push = 0;
                                    
                                    
                                    hg_op.acting_flag =0;
                               
                                    
                                     if(hg_op.needle_len == NEEDLE_LEN_13_MM)
                                     {
                                       hg_op.need_reset =0;  
                                     }
                                     else
                                     {
                                       hg_op.need_reset =1;  
                                     }
                    
                             }
                             //else if(ACTION_BUTTON  == 0)
                             else
                             {
                                  hg_op.drops_sb = 0;
                                  hg_op.drops_push =0;
                                  hg_op.drops_sa = 1;
                             }
                           
                        }
                 
                }
                  
                
                
            }
            
#endif        
            
            
            
            
            
            
            
            
            
            
                  
#if 1
            if(hg_op.acting_flag)
            {
                delaynus(20 * 1000);
                  if(ACTION_BUTTON  == 0)
                  {
                        DISABLE_TIMER();
                        buzz();

                        //if(hg_op.status_powerup == STATUS_WAKE)
                        if(1)
                        {
                            //printf("action\r\n");
                            //if(hg_op.acting_flag ==0)
                            if(hg_op.cur_working_mode == WORK_MODE_DROPS)
                            {
                                //printf("drops mode\r\n");
                               hg_op.acting_flag =0;

                               hg_op.drops_sa =1;
                               hg_op.drops_sb =0;
                               hg_op.drops_push =0;

                               hg_op.working_mode = hg_op.cur_working_mode;
                            }
                            else if(hg_op.cur_working_mode == WORK_MODE_C)
                            {
                               //printf("c mode\r\n");
                               hg_op.drops_sa =1;
                               hg_op.drops_sb =0;
                               hg_op.drops_push =0;

                               hg_op.working_mode = hg_op.cur_working_mode;
                               hg_op.working_mode = WORK_MODE_C;
                            }
                             else if(hg_op.cur_working_mode == WORK_MODE_TEST)
                             {
                               action_btn_cnt ++;
                               //printf("test mode\r\n");
                               hg_op.drops_sa =1;
                               hg_op.drops_sb =0;
                               hg_op.drops_push =0;

                               hg_op.working_mode = hg_op.cur_working_mode;

                               //printf("action test mode\r\n");


                             }

                        }

                  }
                  else
                  {
                       ENABLE_TIMER();
                  }
                
                
                
                hg_op.acting_flag = 0;
                
            }
        
        
#endif
            
          
            
            
#if 1
            else if(hg_op.working_mode == WORK_MODE_STOP)
            {
                             
                #if 0
                if(T0IE == 0  || T0CONbits.TMR0ON == 0)
                {
                    T0CONbits.TMR0ON =1;
                    T0IE=1; // 
                }
                #endif
                
                //printf("in stop mode\r\n");
            }
            else
            {
            
                 //printf("out of mode\r\n");
            
            }
#endif
            
            if(hg_op.working_mode == WORK_MODE_STOP)
            {
                HG_interface();
            }
            
/********************************************************************************/
                       
            
            

                }
    }//end while
    
    
}//end main
