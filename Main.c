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

   // delay_nms(100);
    HG_init();
    uart_init();
    AD_init();
    MotorDriveInit();
    
    
    
    //===============================================


    
    
#if 0
    
          while(1)
                {
                    INPUT3_BH();
                    delay_pwm(300*5);
                    INPUT3_BL();
                    delay_pwm(300*5);//4.8ms
                    
                   
                }
    
    
#endif
    
    
    
    
    
    
    
    
#if 0
    //REVERSE_RUN_A();   
    //FORWARD_RUN_A();  
     T0CONbits.TMR0ON =0;
    while(1)
    {
        
            dv =0;
            dv = get_AD_vaule();
            //printf("dv is %d\r\n",dv);
            
            bv =0;
            bv = get_SenseA_AD_vaule();
            printf("bv is %d\r\n",bv);
            
            cv =0;
            cv = get_SenseB_AD_vaule();
            printf("cv is %d\r\n",cv);
        
        delay_nms(100);
    }
    
#endif
    
    
    //==============================================
    
    
    cur_state_phb_ma=0;
    prev_state_phb_ma=0;
    cnt_ma = 0;
    cnt_mb = 0;
    
    //====================================
#if 0
    //uart_init();delay_nms(10);
    while(1)
    {
#if 0
        put_byte_uart(0x31); //delay_nms(10);
        put_byte_uart(0x32);//delay_nms(10);
        put_byte_uart(0x33);//delay_nms(10);
        put_byte_uart(0x34);//delay_nms(40);
        
        printf("hello pic18\r\n");
        delay_nms(100);
#endif
        
        
       
        
        
    }
    
#endif
    
    
    
    
    
#if defined(TEST_CODER)
    cnt_ma = 0;
    cnt_mb = 0;
    cnt_mb_sa =0;
    cnt_mb_sb =0;
    flag_inject_sa =1;
    REVERSE_RUN_B();
    while(1)
    {
    delay_nms(100);
    
    delay_nms(100);
    delay_nms(100);
    delay_nms(100);
    }
#endif
    //======================================
#if 0
    ENABLE_AH();
    FORWARD_RUN_A();   
    
    while(cnt_ma < 6000)
    {
        cur_state_phb_ma = READ_PHB_MA();
        if(cur_state_phb_ma != prev_state_phb_ma)
        {
           cnt_ma ++;
           prev_state_phb_ma = cur_state_phb_ma;   
        }
    
    }
    
    STOP_A();
    ENABLE_AL();
    
    ENABLE_BH(); 
    FORWARD_RUN_B();   
    
#endif
    
    
    hg_op.need_reset =1;
    hg_op.cur_working_mode = WORK_MODE_DROPS;//now we assume working in DROPS ;
    hg_op.cnt_target_posrst = POS_RST;     //len=9mm
    hg_op.needle_len = LEN_9_MM;
    hg_op.status_powerup = STATUS_SLEEP;
    while(1)
    {
    
        
        #if 1
        if( hg_op.status_powerup == STATUS_SLEEP)
        {
            printf("sleep mode\r\n");
            SLEEP();
           
        }
       #endif
        
        
        
        
        
        

        if(hg_op.need_reset)
        {
           
            if(LP_BUTTON == 0)
            { 
                STOP_B(); 
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                //while(hg_op.posrst == 0)
                while(hg_op.cnt_posrst < 600)
                {
                    INPUT3_BH();
                    delay_pwm(16);
                    INPUT3_BL();
                    delay_pwm(16);
                    
                    hg_op.cnt_posrst ++;
                }
                
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                  
              
                
            }
            
   
            STOP_B(); 
            hg_op.status_hit_lp = 0;
            ENABLE_BH();
            while(hg_op.status_hit_lp == 0)
            {
                INPUT4_BH();
                delay_pwm(128);
                INPUT4_BL();
                delay_pwm(128);        
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
                while(hg_op.posrst == 0)
                {
                    INPUT3_BH();
                    delay_pwm(128);
                    INPUT3_BL();
                    delay_pwm(128);
                }
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
                
                if(ACTION_BUTTON  == 1)
                {
                    STOP_B();
                    hg_op.working_mode = WORK_MODE_STOP; 
                    hg_op.need_reset =1;  
                    
                }
                else
                {
                       
                    
                       if(hg_op.drops_sa == 1)
                        {
                          
                            
                           hg_op.cnt_posa =0;
                           printf("sa begin %d\r\n",hg_op.cnt_posa); 
                            //REVERSE_RUN_B();  
                            //di();
                            //FORWARD_RUN_B(); 
                            
                           ann =0; xn = 0;ENABLE_BH();
                            //while( xn < 1000 && hg_op.cnt_posa < 40)
                            while(hg_op.cnt_posa < 120)
                            {
                                 if(hg_op.cnt_posa  > 110) 
                                 {
                                     ann = STARTUP_PWM +2300;
                                     xn = 300;
                                 }
                                 else if(hg_op.cnt_posa  > 100)
                                 {
                                     ann =STARTUP_PWM +2200;
                                     xn = 300;
                                 }
                                 else if(hg_op.cnt_posa  > 90)
                                 {
                                     ann =STARTUP_PWM +2100;
                                     xn = 300;
                                 }
                                 else if(hg_op.cnt_posa  > 80)
                                 {
                                     ann =STARTUP_PWM +2000;
                                     xn = 300;
                                 }
                                 else if(hg_op.cnt_posa  > 70)
                                 {
                                     ann =STARTUP_PWM +1900;
                                     xn = 260;
                                 }
                                 else if(hg_op.cnt_posa  > 60)
                                 {
                                     ann =STARTUP_PWM +1800;
                                     xn = 180;
                                 }
                                 else if(hg_op.cnt_posa  > 50)
                                 {
                                     ann =STARTUP_PWM +1700;
                                     xn = 170;
                                 }
                                 else if(hg_op.cnt_posa  > 40)
                                 {
                                     ann =STARTUP_PWM +1600;
                                     xn = 160;
                                 }
                                 else if(hg_op.cnt_posa  > 20)
                                 {
                                     ann = STARTUP_PWM + 1500;
                                     xn = 150;
                                 }
                                 else 
                                 {
                                     ann = -STARTUP_PWM;
                                     xn = 0;
                                 } 
                                     
                                INPUT3_BL(); delay_pwm(STARTUP_PWM + ann);
                                INPUT3_BH(); delay_pwm(STARTUP_PWM - xn);

                                //INPUT3_BL(); delay_pwm(STARTUP_PWM);
                                //xn ++;
                            }

                            STOP_B();
                            
                            
                            
                            
                            
                            
                            printf("c===-hg_op.cnt_posa is %d\r\n", hg_op.cnt_posa );
                            //printf("here\r\n");
                             
                             //INPUT3_BH();
                            //while(1);
                            
#if 0
                            xn = 0;
                             while(hg_op.drops_sa == 1 && xn < 1400)
                             {
                                 //delay_pwm(300);//300 is 1ms
                                 delay_pwm(3);//3 is 1/100ms
                                 xn ++;
                             }
                            
                            
                            
                            //delay_pwm(300*15);
                            INPUT3_BL();
                            printf("a-hg_op.cnt_posa is %d\r\n", hg_op.cnt_posa );
                            delay_pwm(300*50);
                            printf("b-hg_op.cnt_posa is %d\r\n", hg_op.cnt_posa );
                            INPUT3_BH();
#endif
                            //while(hg_op.drops_sa == 1);
                            delay_f(INTERVAL_F);
                            printf("c-hg_op.cnt_posa is %d\r\n", hg_op.cnt_posa );
                            hg_op.drops_sa = 0;
                            hg_op.drops_sb = 1;
                            hg_op.drops_push = 1;
                        }
                        else if(hg_op.drops_push == 1)
                        //else if(0)
                        {

                           #if 1

                               prev_edge =0;
                               cur_edge =0;
                               cnt_push =0;

                               FORWARD_RUN_A();   

                               while(cnt_push < 100)
                               {
                                   cur_state_phb_ma = READ_PHB_MA();
                                   if(cur_state_phb_ma != prev_state_phb_ma)
                                   {
                                      cnt_push ++;
                                      prev_state_phb_ma = cur_state_phb_ma;   
                                   }

                               }

                               STOP_A();

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

                            
                            //delay_f(INTERVAL_F);
                            hg_op.drops_push = 0;
                            hg_op.drops_sb = 1;


                        }
                        else if(hg_op.drops_sb == 1)
                        {
                           
                           
                            hg_op.cnt_posb =0;
                            printf("sb begin %d\r\n",hg_op.cnt_posb); 
                             //FORWARD_RUN_B();  
                            //REVERSE_RUN_B();  
                            
                            ann = 0;xn =0; ENABLE_BH();
                            //while( xn < 1000 &&  hg_op.cnt_posb < 40 )
                            while(hg_op.cnt_posb < 120)
                            {
                                 if(hg_op.cnt_posb  > 110) 
                                 {
                                     ann = STARTUP_PWM +2300;
                                     xn = 300;
                                 }
                                 else if(hg_op.cnt_posb  > 100)
                                 {
                                     ann =STARTUP_PWM +2200;
                                     xn = 300;
                                 }
                                 else if(hg_op.cnt_posb  > 90)
                                 {
                                     ann =STARTUP_PWM +2100;
                                     xn = 300;
                                 }
                                 else if(hg_op.cnt_posb  > 80)
                                 {
                                     ann =STARTUP_PWM +2000;
                                     xn = 300;
                                 }
                                 else if(hg_op.cnt_posb  > 70)
                                 {
                                     ann =STARTUP_PWM +1900;
                                     xn = 300;
                                 }
                                 else if(hg_op.cnt_posb  > 60)
                                 {
                                     ann =STARTUP_PWM +1800;
                                     xn = 300;
                                 }
                                 else if(hg_op.cnt_posb  > 50)
                                 {
                                     ann =STARTUP_PWM +1700;
                                     xn = 170;
                                 }
                                 else if(hg_op.cnt_posb  > 40)
                                 {
                                     ann =STARTUP_PWM +1600;
                                     xn = 160;
                                 }
                                 //else if(hg_op.cnt_posb  > 32)
                                 else if(hg_op.cnt_posb  > 28)
                                 //else if(hg_op.cnt_posb  > 24)
                                 {
                                     ann = STARTUP_PWM + 1500;
                                     xn = 150;
                                 }
                                 else 
                                 {
                                     ann = -STARTUP_PWM;
                                     xn = 0;
                                 } 
                                
                                
                                
                                INPUT4_BL(); delay_pwm(STARTUP_PWM + ann);
                                INPUT4_BH(); delay_pwm(STARTUP_PWM - xn);
                                //INPUT4_BL(); delay_pwm(STARTUP_PWM);
                                //xn ++;
                            }
                            
                            STOP_B();
                            printf("z===-hg_op.cnt_posb is %d\r\n", hg_op.cnt_posb);
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
                            delay_f(INTERVAL_F);
                            printf("z-hg_op.cnt_posb is %d\r\n", hg_op.cnt_posb);
                            hg_op.drops_sa = 1;
                            hg_op.drops_sb = 0;
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
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
#if 0
        
        if(flag_mreset ==0 && flag_mreset_hit_lp ==0 )
        {
            if(ACTION_BUTTON  == 1)
            {
                 cnt_mb = 0;
                 
                 flag_action =0;
                 flag_push =0;
                 flag_inject_sa =0;
                 flag_inject_sb =0;
                 STOP_B();

                if(flag_do_reset_in_drops_mode == 0)
                {
                    flag_mreset = 1;
                    flag_mreset_hit_lp = 0;
                }

            }
        }
#endif
        

        //===============================================  
 
        
        
        
        //===============================================
   
#if 0
        if(flag_mreset)
        {
            ENABLE_BH(); 
            //FORWARD_RUN_B();   
            REVERSE_RUN_B();  
        }
        
#endif
        
        
        
        
        
        
        
#if 0  
        //if(flag_push)
              if(0)
        {
            #if 1
                delay_nms(2);
                prev_edge =0;
                cur_edge =0;
                cnt_ma =0;
                
                
                
                ENABLE_AH();
                FORWARD_RUN_A();   

                while(cnt_ma < 100)
                {
                    cur_state_phb_ma = READ_PHB_MA();
                    if(cur_state_phb_ma != prev_state_phb_ma)
                    {
                       cnt_ma ++;
                       prev_state_phb_ma = cur_state_phb_ma;   
                    }

                }
               
                STOP_A();
                //ENABLE_AL();

                #if 0 
               prev_edge =0;
                cur_edge =0;
                cnt_ma =0;
                ENABLE_AH();
                REVERSE_RUN_A();   
                while(cnt_ma < 100)
                {
                    cur_state_phb_ma = READ_PHB_MA();
                    if(cur_state_phb_ma != prev_state_phb_ma)
                    {
                       cnt_ma ++;
                       prev_state_phb_ma = cur_state_phb_ma;   
                    }

                }
                
                STOP_A();
                ENABLE_AL();
                #endif
   
                flag_push = 0;
                flag_inject_sa =0;
                flag_inject_sb =1;
          
#if 1
                cnt_mb = 0;
                
                cnt_mb_sa =0;
                cnt_mb_sb =0;
                ENABLE_BH();
                FORWARD_RUN_B(); 
                
#endif
                
                
                
                //ENABLE_BH(); 
                //FORWARD_RUN_B();   
    
            #endif
        
        
        }
        
#endif
        
        
        HG_interface();
        //printf("heart beat %d\r\n",++msleep);


        
    }
    
	
   
#if 0
    BeepInit();
    BeepOn();
    /elay_nms(100);
    BeepOff();
    
    while(1);
#endif 
    
#if 0
    LCD_backlight_init();
    LCD_On();
#endif
   //delay(2000);
   //delay(2000);
   //delay(2000);
       //buzz();
    //while(1);
    //LCD_Off();
	
#if 0
    MotorDriveInit();
    
    ENABLE_AH();
    ENABLE_BH();
    
    
    FORWARD_RUN_A();   
    FORWARD_RUN_B();   
    
	//PositionCheckInit();
	
#endif
  
#if 0
    KEY_Init();

    Initial_LY096BG30();
    while(1);
    
    //display_frame_abc(0,COL_PAGE0_PATTERN_A, MODE_NORMAL);
    //display_frame_abc(0,COL_PAGE0_PATTERN_A, MODE_REVERSE);
    
    
    //display_frame_abc(0,COL_PAGE0_PATTERN_B, MODE_NORMAL);
    
    //display_frame_abc(0,COL_PAGE0_PATTERN_C, MODE_NORMAL);
    //display_frame_abc(0,COL_PAGE0_PATTERN_C, MODE_REVERSE);
    
    
    //display_frame_abc(0,COL_PAGE0_PATTERN_B, MODE_REVERSE);
    //display_frame_abc(0,COL_PAGE0_PATTERN_B, MODE_NORMAL);
    
    //display_frame_abc(0,COL_PAGE0_PATTERN_C, MODE_REVERSE);
    //display_frame_abc(0,COL_PAGE0_PATTERN_C, MODE_NORMAL);
    
    
    //display_mem(0,COL_PAGE0_MEM,MODE_NORMAL);
    //display_mem(0,COL_PAGE0_MEM,MODE_REVERSE);
    
 
    //display_bat(0,COL_PAGE0_BAT,MODE_NORMAL);
    //display_bat(0,COL_PAGE0_BAT,MODE_REVERSE);
      
    
    //display_drops(0,COL_PAGE0_MDROPS,MODE_NORMAL);
    //display_cmode(0,COL_PAGE0_MDROPS,MODE_NORMAL);
    //display_drop(0,COL_PAGE0_MDROPS,MODE_NORMAL);
    
    //display_cmode(0,COL_PAGE0_MDROPS,MODE_REVERSE);
    ///display_drops(0,COL_PAGE0_MDROPS,MODE_REVERSE);
    
    
    
    
    //display_frame_de(1,COL_PAGE0_PATTERN_D, MODE_NORMAL);delay(30);
    //display_frame_de(1,COL_PAGE0_PATTERN_D, MODE_REVERSE);delay(30);
    //display_frame_de(1,COL_PAGE0_PATTERN_D, MODE_REVERSE);delay(30);
    
    //display_n13(0,COL_PAGE0_DN, MODE_NORMAL);
    //display_n13(0,COL_PAGE0_DN, MODE_REVERSE);
    
    
    
    
    //display_frame_de(2,COL_PAGE0_PATTERN_E, MODE_NORMAL);
    //display_frame_de(2,COL_PAGE0_PATTERN_E, MODE_REVERSE);
    
    
    //display_frame_fghi(1,COL_PAGE0_PATTERN_F, MODE_NORMAL);
    //display_frame_fghi(1,COL_PAGE0_PATTERN_F, MODE_REVERSE);
    
    //display_frame_fghi(1,COL_PAGE0_PATTERN_F, MODE_NORMAL);
     //display_frame_fghi(2,COL_PAGE0_PATTERN_G, MODE_NORMAL);
     display_frame_fghi(2,COL_PAGE0_PATTERN_G, MODE_REVERSE);
     //display_frame_fghi(3,COL_PAGE0_PATTERN_H, MODE_NORMAL);
     //display_frame_fghi(4,COL_PAGE0_PATTERN_H, MODE_NORMAL);
    
     
      //display_n5(0,COL_PAGE0_HN, MODE_NORMAL);delay(20);
      display_n5(0,COL_PAGE0_HN, MODE_REVERSE);delay(20);
     while(1);
    
    //display_frame_fghi(2,COL_PAGE0_PATTERN_G, MODE_NORMAL);
    //display_frame_fghi(2,COL_PAGE0_PATTERN_G, MODE_REVERSE);
    
    
    
    //display_frame_fghi(3,COL_PAGE0_PATTERN_G, MODE_NORMAL);
    //display_frame_fghi(3,COL_PAGE0_PATTERN_G, MODE_REVERSE);
    
    
    
    
    
    
    
    
    
    while(1)
    {
        
        for(bv=0;bv<10;bv++)
        {
        //display_frame_de(1,COL_PAGE0_PATTERN_D, MODE_BLANK);
        //display_frame_de(1,COL_PAGE0_PATTERN_D, MODE_NORMAL);
        //display_frame_de(2,COL_PAGE0_PATTERN_E, MODE_NORMAL);
        //display_frame_fgh(1,COL_PAGE0_PATTERN_F, MODE_NORMAL);
        //display_frame_fgh(2,COL_PAGE0_PATTERN_G, MODE_NORMAL);
        
        display_frame_fghi(3,COL_PAGE0_PATTERN_H, MODE_NORMAL);
        
          //display_n13(0,COL_PAGE0_DN, MODE_NORMAL);delay(20);
          //display_n4(0,COL_PAGE0_DN, MODE_NORMAL);delay(20);
          //display_n4(0,COL_PAGE0_EN, MODE_NORMAL);delay(20);
          //display_n5(0,COL_PAGE0_FN, MODE_NORMAL);delay(20);
        display_n5(0,COL_PAGE0_HN, MODE_NORMAL);delay(20);
          
          //display_n250(0,COL_PAGE0_GN, MODE_NORMAL);delay(20);
        //display_n_blank(0,COL_PAGE0_DN, MODE_NORMAL);delay(20);
        //display_n_blank(2,COL_PAGE0_FN, MODE_NORMAL);delay(20);
        //display_n_blank(2,COL_PAGE0_GN, MODE_NORMAL);delay(20);
        
        display_n_blank(2,COL_PAGE0_HN, MODE_NORMAL);delay(20);
        
        }
        
#if 0
         for(bv=0;bv<10;bv++)
         {
         //display_frame_de(1,COL_PAGE0_PATTERN_D, MODE_BLANK);
        //display_frame_de(2,COL_PAGE0_PATTERN_E, MODE_REVERSE);
         //display_frame_fgh(1,COL_PAGE0_PATTERN_F, MODE_REVERSE);
         
          display_frame_fgh(2,COL_PAGE0_PATTERN_G, MODE_REVERSE);
        //display_n13(0,COL_PAGE0_DN, MODE_REVERSE);delay(20);
        //display_n4(0,COL_PAGE0_EN, MODE_REVERSE);delay(20);
         //display_n5(0,COL_PAGE0_FN, MODE_REVERSE);delay(20);
         display_n250(0,COL_PAGE0_GN, MODE_REVERSE);delay(20);
        //display_n_blank(0,COL_PAGE0_EN, MODE_REVERSE);delay(20);
        //display_n_blank(2,COL_PAGE0_FN, MODE_REVERSE);delay(20);
        display_n_blank(2,COL_PAGE0_GN, MODE_REVERSE);delay(20);
         }
#endif
        
        //display_n13(0,COL_PAGE0_DN, MODE_REVERSE);delay(20);
        //display_n_blank(0,COL_PAGE0_DN, MODE_REVERSE);delay(20);
        
        //display_bat(0,COL_PAGE0_BAT,MODE_NORMAL);delay(20);
        //display_blank_mode_pa(0,COL_PAGE0_BAT,MODE_NORMAL);delay(20);
        
        //display_bat(0,COL_PAGE0_BAT,MODE_REVERSE);delay(20);
        //display_blank_mode_pa(0,COL_PAGE0_BAT,MODE_REVERSE);delay(20);
        
        //display_mem(0,COL_PAGE0_MEM,MODE_REVERSE);delay(30);
        //display_blank_mode_pa(0,COL_PAGE0_MEM,MODE_REVERSE);delay(30);
        
        
        //display_mem(0,COL_PAGE0_MEM,MODE_NORMAL);delay(30);
        //display_blank_mode_pa(0,COL_PAGE0_MEM,MODE_NORMAL);delay(30);
        
        
        
     //display_cmode(0,COL_PAGE0_MDROPS,MODE_REVERSE);delay(30);
     //display_drops(0,COL_PAGE0_MDROPS,MODE_REVERSE);delay(30);    
    //display_drop(0,COL_PAGE0_MDROPS,MODE_REVERSE);delay(30);
    //display_blank_mode_pa(0,COL_PAGE0_MDROPS,MODE_REVERSE);delay(30);
    
    //display_cmode(0,COL_PAGE0_MDROPS,MODE_NORMAL);delay(30);
    //display_drops(0,COL_PAGE0_MDROPS,MODE_NORMAL);delay(30);
     //display_drop(0,COL_PAGE0_MDROPS,MODE_NORMAL);delay(30);
    //display_blank_mode_pa(0,COL_PAGE0_MDROPS,MODE_NORMAL);delay(30);
    }

    
    
    // display_pattern(5,0,MODE_NORMAL);
     while(1);
    //TimerInit();
#endif
   // while(xn<20)
    //LCD_On();
    //while(1);
    
    
    
#if 0
   // TEST_LED_ON(); 
    while(1)
    {
    
           if(STATUS_CHARGE  == 0)
           {
              // buzz();
               TEST_LED_ON(); 
           }
           else
           {
              TEST_LED_OFF(); 
           }
    
    }
    
#endif
    
    
    
#if 0
    AD_ch0_init();
    while(1)
    {
        
        if(STATUS_CHARGE  == 0)
        {
            // buzz();
            TEST_LED_ON(); 
        }
        else
        {
            TEST_LED_OFF(); 
        }
     
        
        
        
    bv = get_AD_vaule();
    //bv = get_SenseA_AD_vaule();
    //bv = get_SenseB_AD_vaule();
    
    
    cv =0;
    //cv = get_AD_vaule();
    cv = get_SenseA_AD_vaule();
    //cv = get_SenseB_AD_vaule();
    
    dv =0;
    //dv = get_AD_vaule();
    //dv = get_SenseA_AD_vaule();
    dv = get_SenseB_AD_vaule();
    }
#endif
    
    
    
    
    

    
#if 0
    ENABLE_AH();
    FORWARD_RUN_A();   
   // delay(100);//delay(2000);//delay(2000);delay(2000);
    
    //ENABLE_BH();
    //FORWARD_RUN_B();     
    while(1)
    {
       // PIR1bits.TMR2IF = 0;
       // while( PIR1bits.TMR2IF == 0);
      
        //REVERSE_RUN_A();        
        //delay(100);//delay(2000);//delay(2000);delay(2000);
        
        
        //FORWARD_RUN_A();   
        delay(100);//delay(2000);//delay(2000);delay(2000);
        
        bv += 10;
         CCPR1L= bv;
         buzz();
    }
    
#endif
    
    
#if 0
    //injector
    TEST_LED_ON(); 
    ENABLE_BH();
    FORWARD_RUN_B();     
    while(1);
#endif
    
    
    
#if 0
    
    while(1)
    {
        
        
           if(STATUS_CHARGE  == 0)
           {
              // buzz();
               TEST_LED_ON(); 
           }
           else
           {
              TEST_LED_OFF(); 
           }
        
        
        
        //hg_interface();
       // if(KEY_WAKE == 0)
      
       
        //if(KEY_WAKE == 0 && KEY_UP == 1 && KEY_V == 1 && KEY_DOWN == 1)//==============
        //if((PORTB &0x10) == 0)
        //    if((LATB &0x10) == 0)
        
        
        if(KEY_WAKE == 0)
        {
            buzz();
        }
            
            
        if(KEY_UP == 0)
        {
            buzz();
        }
        
        
        if(KEY_DOWN == 0)
        {
            buzz();
        }
            
        if(KEY_V == 0)
        {
            buzz();
        }
        
        if(ACTION_BUTTON == 0)
        {
            buzz();
        }
        if(LP_BUTTON == 0)
        {
                //LATB = 0xff;
            //PORTB =0xff;
            //delay(100);
             //if(KEY_WAKE == 0 )
             {
                //buzz();
               // LCD_Blink();
               // break;
             }
             buzz();
        }
    
    }
    
#endif
    
    
    
    
    
    
    
    
    
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
    
    
 #if 0
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
    

#if 0
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
    
    
    
#endif
}


 
