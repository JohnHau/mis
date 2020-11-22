#include <xc.h>
#include <stdio.h>
#include "Beep.h"
#include "Oled.h"




void uart_init(void)
{

    TRISCbits.RC7 =1;//RX  input mode
    TRISCbits.RC6 =0;//TX  output mode

    //SPBRG = 25;//9600
    SPBRG = 12;//19200
    RCSTAbits.SPEN =1;
    //RCSTAbits.CREN =1;//
    
    //TXSTAbits.BRGH =1;
    
   TXSTAbits.TXEN =1;

    

}

void put_byte_uart(uint8_t n)
{
    
    PIR1bits.TXIF =0;
    TXREG = n;
    
    while( TXSTAbits.TRMT ==0);
    
    while( PIR1bits.TXIF ==0);
     PIR1bits.TXIF =0;
}

void put_bytes_uart(uint8_t *arr,uint8_t n)
{
    
    uint8_t i=0;
    for(i=0;i<n;i++)
    {
        put_byte_uart(arr[i]);
    }
    
    
    
}




void putch(uint8_t c)
{
     TXREG = c;
    
    while( TXSTAbits.TRMT ==0);
    
    
    
}













void BeepInit(void)
{
	//PORTBbits.RB1 =0;	//colse	
	//DDRBbits.RB1  =0;	//dir=out
    
   // PORTEbits.RE2 =0;
   // DDREbits.RE2 =0;
    
    
    TRISEbits.RE2 =0;
    LATEbits.LE2 =0;
    
    
    TRISDbits.RD5 =0;//test led
    LATDbits.LD5 =1;//test led off
    
}
void BeepOn(void)
{
	//PORTBbits.RB1 =1;	//colse	
    
    // PORTEbits.RE2 =1;
     
     LATEbits.LE2 =1;
     
     
}
void BeepOff(void)
{
	//PORTBbits.RB1 =0;	//colse	
   // PORTEbits.RE2 =0;
    
    LATEbits.LE2 =0;
}


void buzz(void)
{
    
    
    	//unsigned int  i,j;
//PORTEbits.RE2 =1;
LATEbits.LE2 =1;
  
    //for(i=0;i<200;i++)
       //for(j=0;j<100;j++);
       
       
        delay_nms(1);
       
//PORTEbits.RE2 =0;
LATEbits.LE2 =0;
  //for(i=0;i<200;i++)
      // for(j=0;j<100;j++);

}




#if 0

    
#if 0
    LCD_On();
    //display_frame_de(1,COL_PAGE0_PATTERN_D, MODE_NORMAL);delay(30);
    //display_frame_de(1,COL_PAGE0_PATTERN_D, MODE_REVERSE);delay(30);
    //display_frame_de(1,COL_PAGE0_PATTERN_D, MODE_REVERSE);delay(30);
    
    //display_n13(0,COL_PAGE0_DN, MODE_NORMAL);
    //display_n13(0,COL_PAGE0_DN, MODE_REVERSE);
    //display_n6(0,COL_PAGE0_DN, MODE_NORMAL);
    
        //==========================================
     //display_n6(0,COL_PAGE0_DN, MODE_NORMAL);
     //display_n0(0,COL_PAGE0_DN, MODE_NORMAL);
     //display_n1(0,COL_PAGE0_DN, MODE_NORMAL);
     
     //display_n3(0,COL_PAGE0_DN, MODE_NORMAL);
     //display_n10(0,COL_PAGE0_DN, MODE_NORMAL);
     //display_n2(0,COL_PAGE0_DN, MODE_NORMAL);
     
     //display_n200(0,COL_PAGE0_DN, MODE_NORMAL);
     //display_n100(0,COL_PAGE0_DN, MODE_NORMAL);
     //display_n300(0,COL_PAGE0_DN, MODE_NORMAL);
     
    // display_n150(0,COL_PAGE0_DN, MODE_NORMAL);
     
      //display_n1P5(0,COL_PAGE0_DN, MODE_NORMAL);
      display_n2P5(0,COL_PAGE0_DN, MODE_NORMAL);
    //==========================================
    
    
    while(1);
    
    
#endif
    
    
    
    
        
#if 0
    while(1)
    {
       delaynus(50000);delaynus(50000);
        delaynus(50000);delaynus(50000);
         delaynus(50000);delaynus(50000);
          delaynus(50000);delaynus(50000);
           delaynus(50000);delaynus(50000);
           
           TEST_LED_ON();
           
                  delaynus(50000);delaynus(50000);
        delaynus(50000);delaynus(50000);
         delaynus(50000);delaynus(50000);
          delaynus(50000);delaynus(50000);
           delaynus(50000);delaynus(50000);
           
           TEST_LED_OFF();
           
    }
    
#endif
    
      
          
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
     //display_frame_fghi(2,COL_PAGE0_PATTERN_G, MODE_REVERSE);
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
        
        //display_frame_fghi(3,COL_PAGE0_PATTERN_H, MODE_NORMAL);
        
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
         //buzz();
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
            //buzz();
        }
            
            
        if(KEY_UP == 0)
        {
            //buzz();
        }
        
        
        if(KEY_DOWN == 0)
        {
            //buzz();
        }
            
        if(KEY_V == 0)
        {
            //buzz();
        }
        
        if(ACTION_BUTTON == 0)
        {
            //buzz();
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
             //buzz();
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
    //buzz();
    
            
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
    //buzz();
        
#endif   
    
    
    

    
            
            
            
#if 0
    ENABLE_AH();
    FORWARD_RUN_A();
    delay(400);
    STOP_A();
     //buzz();
    REVERSE_RUN_A();
    delay(400);
    STOP_A();
    //buzz();
#endif
    
    
#if 0
    ENABLE_BH();
    FORWARD_RUN_B();
    delay(400);
    STOP_B();
    // buzz();
    REVERSE_RUN_B();
    delay(400);
    STOP_B();
    //buzz();
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
    
    
    
    
             
         
         
         
         
         
         
    //display_pattern(1,0,MODE_NORMAL);
    //display_pattern(1,1,0);
    //display_pattern(1,2,0);
    //display_pattern(1,2,MODE_NORMAL);
    //display_pattern(1,2,MODE_REVERSE);
    //display_pattern(1,2,MODE_BLANK);
    
    //display_pattern(2,0,MODE_NORMAL);
    //display_pattern(2,0,MODE_REVERSE);
    
     //display_pattern(3,0,MODE_NORMAL);
     
     
     //display_pattern(4,0,MODE_NORMAL);
     //display_pattern(4,0,MODE_REVERSE);
      //display_pattern(4,0,MODE_BLANK);
     
     
     //display_pattern(5,0,MODE_NORMAL);
     //display_pattern(5,0,MODE_NORMAL);
     //display_pattern(5,0,MODE_REVERSE);
     //display_pattern(5,0,MODE_BLANK);
     
     
     
     //display_pattern(6,0,MODE_NORMAL);
     //display_pattern(6,0,MODE_NORMAL);
      //display_pattern(6,0,MODE_REVERSE);
      //display_pattern(6,0,MODE_BLANK);
     
     
     //display_pattern(7,0,MODE_NORMAL);
     //display_pattern(7,1,0);
      //display_pattern(7,2,0);
       //display_pattern(7,2,MODE_REVERSE);
       
        //display_pattern(7,2,MODE_BLANK);
   

       
    
    #if 0

    clear_screen();
    for(ss=1;ss<8;ss++)
    {
       
       //display_pattern(ss,0,MODE_NORMAL);
    }
    

#endif    
         
    
    
    
//==============================================================================
#if 0
uint8_t display_frame_fghi_x(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;
     
    
    if(y==1)
    {
    if(mode == MODE_NORMAL)
            {         
           
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
               temp = ptnf_frame[0][ms];
               ee_WriteBytes(&temp, 0x40, 1);
            }
            
            
             setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnf_frame[1][ms];
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             
              setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnf_frame[2][ms];
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnf_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                   
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
            setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnf_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
           
               setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnf_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
             
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    }
    else if (y == 2)
    {
            if(mode == MODE_NORMAL)
            {         
          
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptng_frame[0][ms];
          
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
             setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptng_frame[1][ms];
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
           
              setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptng_frame[2][ms];
             
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptng_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                   
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
            setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptng_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
          
               setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptng_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    }
    else if(y == 3)
    {
      if(mode == MODE_NORMAL)
            {         
          
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnh_frame[0][ms];
          
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
             setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnh_frame[1][ms];
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
           
              setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnh_frame[2][ms];
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
          
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnh_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                  
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
          
            setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnh_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
          
               setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnh_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
            
                ee_WriteBytes(&temp, 0x40, 1);
             }

            }
    }
    else if(y == 4)
    {
      if(mode == MODE_NORMAL)
            {         
            
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptni_frame[0][ms];
           
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
        
             setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptni_frame[1][ms];
                
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
              setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptni_frame[2][ms];
                
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
           
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptni_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                    //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
            setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptni_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
               setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptni_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
                
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

    }

}

#endif

    
    
    
    
    
#if 0

uint8_t display_n0(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_0_m[0][ms];
          
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_0_m[1][ms];
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
           
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_0_m[2][ms];
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
           
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_0_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
         
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_0_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
           
               setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_0_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}

#endif




#if 0

uint8_t display_n1(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_1_m[0][ms];
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_1_m[1][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                temp = n_1_m[2][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
           
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_1_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_1_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
         
               setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_1_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}

#endif




#if 0
uint8_t display_n2(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_2_m[0][ms];
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                temp = n_2_m[1][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_2_m[2][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_2_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_2_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
               setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_2_m[2][ms];
                 tori = temp;
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}


#endif






#if 0
uint8_t display_n3(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_3_m[0][ms];
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                temp = n_3_m[1][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_3_m[2][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_3_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_3_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_3_m[2][ms];
                 tori = temp;
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}

#endif




#if 0
uint8_t display_n4(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_4_m[0][ms];
            
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
          
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_4_m[1][ms];
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_4_m[2][ms];
                
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_4_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
          
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_4_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
               setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_4_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}
#endif



#if 0
uint8_t display_n5(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
          
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_5_m[0][ms];
            
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
         
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_5_m[1][ms];
                
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
         
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_5_m[2][ms];
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
          
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_5_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_5_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
          
               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_5_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}
#endif



#if 0
uint8_t display_n6(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
            
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_6_m[0][ms];
           
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
          
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_6_m[1][ms];
             
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_6_m[2][ms];
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_6_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_6_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
               setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_6_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}

#endif




#if 0
uint8_t display_n10(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
          
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_10_m[0][ms];
           
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
          
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_10_m[1][ms];
             
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_10_m[2][ms];
             
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
           
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_10_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
       
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_10_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
               setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_10_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}


#endif





#if 0
uint8_t display_n1P5(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
  
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_1P5_m[0][ms];
           
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_1P5_m[1][ms];
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
          
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_1P5_m[2][ms];
             
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
          
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_1P5_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_1P5_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
          
               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_1P5_m[2][ms];
                 tori = temp;

                 
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}

#endif



#if 0
uint8_t display_n2P5(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
     
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_2P5_m[0][ms];
          
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
        
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_2P5_m[1][ms];
            
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
       
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_2P5_m[2][ms];
            
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_2P5_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_2P5_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_2P5_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}

#endif







#if 0
uint8_t display_n100(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_100_m[0][ms];
           
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
          
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                temp = n_100_m[1][ms];
                
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_100_m[2][ms];
             
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
          
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_100_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
        
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_100_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            

               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_100_m[2][ms];
                 tori = temp;
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}
#endif




#if 0
uint8_t display_n150(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
        
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_150_m[0][ms];
          
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
        
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_150_m[1][ms];
          
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
        
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_150_m[2][ms];
             
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
       
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_150_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_150_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
         
               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_150_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}

#endif



#if  0
uint8_t display_n200(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
   
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_200_m[0][ms];
         
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
        
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_200_m[1][ms];
             
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
           
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_200_m[2][ms];
  
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
   
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_200_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_200_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_200_m[2][ms];
                 tori = temp;

                 
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}
#endif



#if 0
uint8_t display_n250(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_250_m[0][ms];
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_250_m[1][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
           
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_250_m[2][ms];
               
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
           
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_250_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
           
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_250_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             
               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_250_m[2][ms];
                 tori = temp;
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}
#endif





#if 0
uint8_t display_n300(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
         
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
               temp = n_300_m[0][ms];
               ee_WriteBytes(&temp, 0x40, 1);
            }
            
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_300_m[1][ms];
       
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
           
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_300_m[2][ms];
              
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_300_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_300_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_300_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}

#endif








#if 0
uint8_t display_n13(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_13_m[0][ms];
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_13_m[1][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_13_m[2][ms];
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_13_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_13_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
               setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_13_m[2][ms];
                 tori = temp;

                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}
#endif

    
    
//FORWARD_RUN_B();  
//REVERSE_RUN_B();  
    
    
    
    
    
    #if 0   
                               //while(cnt_push < 140)//146
                               while(cnt_push < hg_op.push_len)//146
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