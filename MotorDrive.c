#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include"MotorDrive.h"
#include"Timer.h"
#include"Key.h"
#include"gui.h"
#include"Oled.h"
//needle length         pos 
//  4mm                 9.7mm
//  9mm                 4.7mm
//  13mm                0.7mm


uint8_t prev_state_phb_ma =0;
uint8_t cur_state_phb_ma =0;

uint32_t cnt_ma =0;
uint32_t cnt_mb =0;


uint32_t cnt_mb_sa =0;
uint32_t cnt_mb_sb =0;

uint8_t flag_mreset =1;
uint8_t flag_mreset_hit_lp =0;

uint8_t flag_inject =0;

uint8_t flag_inject_sa =0;
uint8_t flag_inject_sb =0;

uint8_t flag_push =0;

uint8_t flag_action =0;

uint8_t flag_go_to_sleep =1;

uint8_t flag_wake_up =1;

uint8_t flag_action_button =0;
        
uint8_t flag_do_reset_in_drops_mode =0;  
        




void MotorDriveInit(void)
{
	
       //===========================================================
#if 0
    //CCPR2= 99;
    PR2= 99;
    CCPR1L= 100;
    //CCP1CON = 
    TRISCbits.RC2 =0;//enable A
    T2CONbits.T2CKPS = 1;//prescaler is 4
    CCP1CONbits.CCP1M = 0x0c;//pwm mode
    TMR2 = 0;
    T2CONbits.TMR2ON =1;
#endif
    //===========================================================
    
    TRISAbits.RA5 =0;//motor power on
    
    
    TRISCbits.RC2 =0;//enable A
    TRISDbits.RD0 =0;//input1
    TRISDbits.RD1 =0;//input2
    
    TRISCbits.RC1 =1;//PHA_MA
    TRISAbits.RA4 =1;//PHB_MA  works
    
    
    TRISCbits.RC0 =1;//PHA_MB
    TRISBbits.RB2 =1;//PHB_MB  
    
    
    
    TRISDbits.RD4 =0;//enable B
    TRISDbits.RD2 =0;//input3
    TRISDbits.RD3 =0;//input4
    
    
    
    
    MPON();
    STOP_A();
    STOP_B();
    ENABLE_AH();   
    ENABLE_BH();   

    
    
    //=========================================================
#if 1
    INTCON2bits.INTEDG2 = 0;//falling edge
    INTCON3bits.INT2IF =0;
    INTCON3bits.INT2E = 1;//PHB_MB  
    
#endif
    //=========================================================
    
    
 
    
    
    
}


uint16_t brake_MB(void)
{
    uint16_t ths,tls;
    uint8_t temp;
#if 1
                                ths =0;
                                tls =0;
                                while(1)
                                {
                                    temp = READ_PHB_MB();
                                    START();
                                    while(temp == READ_PHB_MB());
                                    STOP();
                                    
                                    if(temp ==0)
                                    {
                                        tls = TMR1;
                                    }
                                    else if(temp ==1)
                                    {
                                        ths = TMR1;
                                    }
                                    
                                   //if(TMR1 > INTV)
                                   if(tls > INTV && ths > INTV)
                                   //if((ls + hs) >  SINTV)
                                    {
                                        STOP_B();
                                        break;
                                        //return tls;
                                    }
                                    
                                }
                                
#endif

                                return tls;

}




void hg_reset(void)
{
    
            if(LP_BUTTON == 0)
            //if(0)//bug to fix
            { 
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                hg_op.cnt_target_posrst = 600; 
                //while(hg_op.posrst == 0)
                REVERSE_RUN_B();
                while(hg_op.cnt_posrst < 300)
                {
                    INPUT3_BH();
                    delaynus(10); delaynus(10); delaynus(10); delaynus(10); delaynus(10);
                    INPUT3_BL();
                    delaynus(10);
                }
                
               STOP_B(); 
               delaynus(50 * 1000);
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                
                printf("lp away\n");
                  
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
            
          
            
            
            hg_op.status_hit_lp = 0;
            ENABLE_BH();INPUT3_BL();
            while(hg_op.status_hit_lp == 0)// search for  lp point
            {
                INPUT4_BH();
                delaynus(10); delaynus(10); delaynus(10); delaynus(10); delaynus(10);
                INPUT4_BL();
                delaynus(10);
                
            }
            
            
            F_RUNNING_BRAKE_MB();  
            //delaynus(50*1000);
            
            
            if(hg_op.needle_len == NEEDLE_LEN_13_MM)
            {
                hg_op.need_reset =0;
            }
            else
            {
                ENABLE_BH();INPUT4_BL();
                hg_op.posrst = 0;
                hg_op.cnt_posrst =0;
                hg_op.in_reset = 1;
                while(hg_op.cnt_posrst < hg_op.cnt_target_posrst)
                {
                    INPUT3_BH();
                    delaynus(10); delaynus(10); delaynus(10); delaynus(10); delaynus(10);
                    printf("r%d\n",hg_op.cnt_posrst);
                    INPUT3_BL();
                    delaynus(10);
                    
                }
                
                
         
            R_RUNNING_BRAKE_MB();                      
            //delaynus(5*1000);
           //delaynus(15*1000);              
                                
                                
            printf("A-reset len is %d\r\n",hg_op.cnt_posrst);
            delaynus(50 * 1000);
               
            printf("B-reset len is %d\r\n",hg_op.cnt_posrst);    
            hg_op.need_reset =0;
            hg_op.status_hit_lp =0;
            hg_op.cnt_posrst =0;
            hg_op.posrst =0;
             
            
            //hg_op.cnt_pos_1mm =0; 
            ENABLE_TIMER();     
        }
    
}


void drops_routine(void)
{
    uint16_t cnt_push =0;
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
                                hg_op.cnt_posa =0;
                                FORWARD_RUN_B();
                                printf("start\n");
                                while(hg_op.cnt_posa < POS_13MM_SA);
                                STOP_B();
                                printf("end\n");
                                delaynus(50 * 1000);
                                
                            }
                            else
                            {
                                STOP_B();                         
                                ENABLE_BH();INPUT4_BL();INPUT3_BH();

                               while(hg_op.cnt_pos_1mm < 150);//300
                               R_RUNNING_BRAKE_MB();
                               printf("333-hg_op.cnt_posa is %d\r\n", hg_op.cnt_pos_1mm );
                          
                                //delaynus(hg_op.work_freq * 1000);

                               DELAY_T1_1SEC(); DELAY_T1_1SEC();

                                printf("444-hg_op.cnt_posa is %d\r\n", hg_op.cnt_pos_1mm );
                           
                            }
                            
                                hg_op.drops_sa = 0;
                                hg_op.drops_sb = 0;
                                hg_op.drops_push = 1;
                            
                            
                            
                    }//end drops_sa
                    else if(hg_op.drops_push == 1)
                    {
                            //prev_edge =0;
                            //cur_edge =0;
                            cnt_push =0;

                            FORWARD_RUN_A();                  
                            //while(cnt_push < 140)//146
                            while(cnt_push < hg_op.push_len)//146
                            //while(cnt_push < 200)//146
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
                                
                              
                                REVERSE_RUN_B();
                                while(LP_BUTTON == 1);
                                STOP_B();
                                delaynus(50 * 1000);
                               
                            }
                            else
                            {
                                ENABLE_BH();INPUT3_BL();INPUT4_BH();
                                while(hg_op.cnt_pos_1mm > 0);//300    
                                
                                F_RUNNING_BRAKE_MB();

                            }
             
                           
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
    
    
    
    
}



void c_routine(void)
{
    uint16_t cnt_push =0;
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



void test_routine(void)
{
    uint16_t cnt_push =0;
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


void check_acting(void)
{
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
          
          
}