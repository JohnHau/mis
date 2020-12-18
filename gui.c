#include <xc.h>
#include <stdio.h>
#include "Beep.h"
#include "Oled.h"
#include "Key.h"
#include "gui.h"
#include "MotorDrive.h"
#include "Timer.h"
uint8_t focus =0;
uint8_t flip =0;
int8_t work_mode =0;

uint8_t work_mode_choice =0;


uint8_t needle_len =4;

uint8_t test_mode =0;
uint8_t flag_test_mode_break =0;


uint8_t flag_blink =0;



MENU menu[8]={0};

HG_OP  hg_op={0};

void HG_device_init(void)
{
    
    #if HG_DEBUG
    uart_init();
    #endif
    
    AD_init();
    MotorDriveInit();
    Timer1Init();
    
    
    //=============================================================
    
    BeepInit();
    LCD_backlight_init();
    //LCD_On();
    LCD_Off();
    
    Initial_LY096BG30();
    init_menu();
    KEY_Init();

    TimerInit();
    
    
}



void menu0_MsgHandlle(uint8_t key)
{
    switch(key)
    {
        case KEY_UP_PRESSED:     
            if(menu[0].mode == MODE_BLINK)
            {    
                work_mode ++;
                if(work_mode == 3)
                {
                    work_mode = WORK_MODE_C;    
                }
                
                
                 display_frame_abc(LEFT,COL_PAGE0_PATTERN_A, menu[0].mode);
                 
                    if(work_mode == WORK_MODE_C)
                    {
                        display_cmode(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }
                    else if(work_mode == WORK_MODE_DROPS)
                    {
                        display_drops(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }
                    else if(work_mode == WORK_MODE_DROP)
                    {
                        display_drop(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }    
                 
                 
                    menu[0].cur_mode = menu[0].mode;  
            }
            else
            {
                if(focus == 1)
                {         
                    menu[0].mode = MODE_REVERSE;
                }
                else
                {
                    menu[0].mode = MODE_NORMAL;
                }
                
                
                if(menu[0].cur_mode != menu[0].mode)
                {
                    display_frame_abc(LEFT,COL_PAGE0_PATTERN_A, menu[0].mode);
                                    
                    if(work_mode == WORK_MODE_C) 
                    {
                        display_cmode(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }
                    else if(work_mode == WORK_MODE_DROP) 
                    {
                        display_drop(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }
                    else if(work_mode == WORK_MODE_DROPS)
                    {
                        display_drops(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }
                    
                    
                    
                    menu[0].cur_mode = menu[0].mode;
                    
                    
                }
                
                
            }    
            
            break;
            
        case KEY_DOWN_PRESSED:
            if(menu[0].mode == MODE_BLINK)   
            {
                
                work_mode --;

                if(work_mode== -1)
                {
                    work_mode = WORK_MODE_DROP;    
                }
                
                
                 display_frame_abc(LEFT,COL_PAGE0_PATTERN_A, menu[0].mode);
                 
                    if(work_mode == WORK_MODE_C)
                    {
                        display_cmode(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }
                    else if(work_mode == WORK_MODE_DROPS)
                    {
                        display_drops(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }
                    else if(work_mode == WORK_MODE_DROP)
                    {
                        display_drop(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }    
                 
                 
                    menu[0].cur_mode = menu[0].mode;  
            }
            else
            {
                if(focus == 1)
                {         
                    menu[0].mode = MODE_REVERSE;
                }
                else
                {
                    menu[0].mode = MODE_NORMAL;
                }
                
                
                if(menu[0].cur_mode != menu[0].mode)
                {
                    display_frame_abc(LEFT,COL_PAGE0_PATTERN_A, menu[0].mode);
                    
                   
                    if(work_mode == WORK_MODE_C) 
                    {
                        display_cmode(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }
                    else if(work_mode == WORK_MODE_DROP) 
                    {
                        display_drop(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }
                    else if(work_mode == WORK_MODE_DROPS)
                    {
                        display_drops(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                    }
                    
                    
                    
                    menu[0].cur_mode = menu[0].mode;
                    
                    
                }
                
                
            }    
            
               
            
            break;
            
        case KEY_V_PRESSED:
            
            if(menu[0].mode == MODE_REVERSE)
            {    
                menu[0].mode = MODE_BLINK;      
                flip = 1;
            }
            else if(menu[0].mode == MODE_BLINK)
            {
          
                
                if(work_mode == WORK_MODE_DROPS)
                {                 
#if 1
                    display_frame_fghi(TYPE_H,COL_PAGE0_PATTERN_H, MODE_NORMAL);
                    //display_num(BOTTOM,COL_PAGE0_HN, NUM_300);
                    display_num(BOTTOM,COL_PAGE0_HN, NUM_250);
                    
                    menu[6].value = NUM_250;
                    
                    menu[0].value = WORK_MODE_DROPS;
                    hg_op.work_freq = DROPS_MODE_250_FREQ;
#endif
                  
                }
                else if(work_mode == WORK_MODE_DROP)
                {
                    //==========================================================
                    display_frame_fghi(TYPE_I,COL_PAGE0_PATTERN_H, MODE_NORMAL);
                    display_num(BOTTOM,COL_PAGE0_GN, NUM_0);
                    //==========================================================     
                    menu[6].value = NUM_0;
                    
                    menu[0].value = WORK_MODE_DROP;
                    hg_op.stay_time_drop = 0;//0 sec
                }
                else if(work_mode == WORK_MODE_C)
                {
                    menu[0].value = WORK_MODE_C;
                }
                
               menu[0].mode = MODE_NORMAL;     
               
            }
            
             if(menu[0].cur_mode != menu[0].mode)
             //if(1)
             {
                 if(menu[0].mode == MODE_NORMAL)
                 {
                    display_frame_abc(LEFT,COL_PAGE0_PATTERN_A, menu[0].mode);
                    if(work_mode == WORK_MODE_C)
                    {
                        display_cmode(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                        
                        display_frame_fghi(TYPE_G,COL_PAGE0_PATTERN_H, MODE_NORMAL);
                        display_num(BOTTOM,COL_PAGE0_GN, NUM_3);
                        menu[6].value = NUM_3;
                                                
                        
                        
                        //hg_op.working_mode = WORK_MODE_C;
                        hg_op.cur_working_mode = WORK_MODE_C;
                    }
                    else if(work_mode == WORK_MODE_DROPS)
                    {
                        display_drops(LEFT,COL_PAGE0_MDROPS, menu[0].mode);   
                        //
                        //
                        //
                        //hg_op.working_mode = WORK_MODE_DROPS;
                        hg_op.cur_working_mode = WORK_MODE_DROPS;
                    }
                    else if(work_mode == WORK_MODE_DROP)
                    {
                        display_drop(LEFT,COL_PAGE0_MDROPS, menu[0].mode);
                        //
                        //
                        //
                        //hg_op.working_mode = WORK_MODE_DROP;
                        hg_op.work_counter_drop =0;
                        hg_op.cur_working_mode = WORK_MODE_DROP;
                    }      
                    
                 }
                    menu[0].cur_mode = menu[0].mode;
                    
                    
              }
            
            
            
            
            
            
            
            break;   
    }
    
    
    

}




void menu1_MsgHandlle(uint8_t key)
{
    switch(key)
    {
        case KEY_UP_PRESSED:
        
           if(menu[1].mode == MODE_BLINK)
            {
                
            }
            else
            {
                if(focus == 2)
                {       
                    menu[1].mode = MODE_REVERSE;
                }
                else
                {
                    menu[1].mode = MODE_NORMAL;
                }
                
                 if(menu[1].cur_mode != menu[1].mode)
                 {
                    //display_frame_abc(LEFT,COL_PAGE0_PATTERN_B, menu[1].mode);
                    //display_mem(LEFT,COL_PAGE0_MEM,menu[1].mode);
                    //menu[1].cur_mode = menu[1].mode;
                 }
                
            }

            break;
            
        case KEY_DOWN_PRESSED:
            
            
            if(menu[1].mode == MODE_BLINK)
            {
                
            }
            else
            {
                if(focus == 2)
                {       
                    menu[1].mode = MODE_REVERSE;
                }
                else
                {
                    menu[1].mode = MODE_NORMAL;
                }
                
                 if(menu[1].cur_mode != menu[1].mode)
                 {
                    //display_frame_abc(LEFT,COL_PAGE0_PATTERN_B, menu[1].mode);
                    //display_mem(LEFT,COL_PAGE0_MEM,menu[1].mode);
                   // menu[1].cur_mode = menu[1].mode;
                 }
                
            }
            
            break;
            
        case KEY_V_PRESSED:
            break;   
    }


}




void menu2_MsgHandlle(uint8_t key)
{

    switch(key)
    {
        case KEY_UP_PRESSED:
      
            
            if(menu[2].mode == MODE_BLINK)
            {
                
            }
            else
            {
                if(focus ==3)
                {     
                    menu[2].mode = MODE_REVERSE;
                }
                else
                {
                    menu[2].mode = MODE_NORMAL;
                }
            }
            
             if(menu[2].cur_mode != menu[2].mode)
             {
                //display_frame_abc(LEFT,COL_PAGE0_PATTERN_C, menu[2].mode);
                //display_bat(LEFT,COL_PAGE0_BAT,menu[2].mode);
                //menu[2].cur_mode = menu[2].mode;
             }
            break;
            
        case KEY_DOWN_PRESSED:
            
            
                    
            if(menu[2].mode == MODE_BLINK)
            {
                
            }
            else
            {
                if(focus ==3)
                {     
                    menu[2].mode = MODE_REVERSE;
                }
                else
                {
                    menu[2].mode = MODE_NORMAL;
                }
            }
            
             if(menu[2].cur_mode != menu[2].mode)
             {
                //display_frame_abc(LEFT,COL_PAGE0_PATTERN_C, menu[2].mode);
                //display_bat(LEFT,COL_PAGE0_BAT,menu[2].mode);
                //menu[2].cur_mode = menu[2].mode;
             }
            
            
            
            
            
            break;
            
        case KEY_V_PRESSED:
            break;   
    }

}




void menu3_MsgHandlle(uint8_t key)
{

    switch(key)
    {
        case KEY_UP_PRESSED:
        
            
            if(menu[3].mode == MODE_BLINK)
            {
                menu[3].parameter ++;  
                if(menu[3].parameter == 3) menu[3].parameter = 0;//4 6 13
            }
            else
            {
                if(focus == 4)
                {
                    menu[3].mode = MODE_REVERSE;
                }
                else
                {
                    menu[3].mode = MODE_NORMAL;
                }
                
                
                 if(menu[3].cur_mode != menu[3].mode)
                 {
                    display_frame_de(LEFT,COL_PAGE0_PATTERN_D, menu[3].mode);
                    
                    
                    if( menu[3].parameter == 0)
                    {
                      
                      display_num(MIDDLE,COL_PAGE0_DN, menu[3].mode | NUM_4);
                    }
                    else if( menu[3].parameter == 1)
                    {
                      
                      display_num(MIDDLE,COL_PAGE0_DN, menu[3].mode | NUM_6);
                    }
                    else if( menu[3].parameter == 2)
                    {
                        display_num(MIDDLE,COL_PAGE0_DN, menu[3].mode | NUM_13);
                    }
                    
                    menu[3].cur_mode = menu[3].mode;
                 }
            }
            
            
            break;
            
        case KEY_DOWN_PRESSED:
            
                        
            if(menu[3].mode == MODE_BLINK)
            {
                menu[3].parameter --;  
                if(menu[3].parameter == -1) menu[3].parameter = 2;
            }
            else
            {
                if(focus == 4)
                {
                    menu[3].mode = MODE_REVERSE;
                }
                else
                {
                    menu[3].mode = MODE_NORMAL;
                }
                
                
                 if(menu[3].cur_mode != menu[3].mode)
                 {
                    display_frame_de(LEFT,COL_PAGE0_PATTERN_D, menu[3].mode);
                    
                    
                    if( menu[3].parameter == 0)
                    {
                      
                      display_num(MIDDLE,COL_PAGE0_DN, menu[3].mode | NUM_4);
                    }
                    else if( menu[3].parameter == 1)
                    {
                    
                      display_num(MIDDLE,COL_PAGE0_DN, menu[3].mode | NUM_6);
                    }
                    else if( menu[3].parameter == 2)
                    {
                        display_num(MIDDLE,COL_PAGE0_DN, menu[3].mode | NUM_13);
                    }
                    
                    menu[3].cur_mode = menu[3].mode;
                 }
            }

            break;
            
        case KEY_V_PRESSED:
              
            if(menu[3].mode == MODE_REVERSE)
            {    
                menu[3].mode = MODE_BLINK;      
                flip = 1;
            }
            else if(menu[3].mode == MODE_BLINK)
            {   
               menu[3].mode = MODE_NORMAL;     
            }
            
             if(menu[3].cur_mode != menu[3].mode)
             {
                 if(menu[3].mode == MODE_NORMAL)
                 {
                    display_frame_de(LEFT,COL_PAGE0_PATTERN_D,MODE_NORMAL);
                    if(menu[3].parameter == 0)
                    {
                        display_num(MIDDLE,COL_PAGE0_DN, menu[3].mode | NUM_4);
                        menu[3].value = NUM_4;
                        // needle_len = 4;
                        hg_op.needle_len = NEEDLE_LEN_4_MM;
                        hg_op.cnt_target_posrst = POS_4_RST; 
                        hg_op.need_reset =1;
                    }
                    else if(menu[3].parameter == 1)
                    {
                        display_num(MIDDLE,COL_PAGE0_DN, menu[3].mode | NUM_6);
                        menu[3].value = NUM_6;
                        //needle_len = 6;
                        hg_op.needle_len = NEEDLE_LEN_6_MM;
                         
                        hg_op.cnt_target_posrst = POS_6_RST; 
                        hg_op.need_reset =1;
                         

                        
                    }
                     else if(menu[3].parameter == 2)
                     {
                        display_num(MIDDLE,COL_PAGE0_DN, menu[3].mode | NUM_13);
                        menu[3].value = NUM_13;
                        //needle_len = 13;
                        hg_op.needle_len = NEEDLE_LEN_13_MM;
                         
                        hg_op.cnt_target_posrst = POS_13_RST; 
                        hg_op.need_reset =1;
                         
                        //
                        //
                        //
                         
                         
                     }
                    
                 }
                    menu[3].cur_mode = menu[3].mode;
                    
                    
              }
            
            
            
            break;   
    }

}




void menu4_MsgHandlle(uint8_t key)
{

    switch(key)
    {
        case KEY_UP_PRESSED:
        
            
            if(menu[4].mode == MODE_BLINK)
            {
                  menu[4].parameter ++;  
                if(menu[4].parameter == 3) menu[4].parameter = 0;
            }
            else
            {
                if(focus ==5)
                {     
                    menu[4].mode = MODE_REVERSE;
                }
                else
                {
                    menu[4].mode = MODE_NORMAL;
                }
                
                 if(menu[4].cur_mode != menu[4].mode)
                 {
                    display_frame_de(RIGHT,COL_PAGE0_PATTERN_E, menu[4].mode);
                    
                    if( menu[4].parameter == 0)
                    {
                    
                      display_num(MIDDLE,COL_PAGE0_EN, menu[4].mode | NUM_1);
                    }
                    else if( menu[4].parameter == 1)
                    {
                      
                      display_num(MIDDLE,COL_PAGE0_EN, menu[4].mode | NUM_2);
                    }
                    else if( menu[4].parameter == 2)
                    {
                      
                      display_num(MIDDLE,COL_PAGE0_EN, menu[4].mode | NUM_0);
                    }
                    
                    
                    menu[4].cur_mode = menu[4].mode;
                 }
                
                
            }

            break;
            
        case KEY_DOWN_PRESSED:
            
                        
            if(menu[4].mode == MODE_BLINK)
            {
                  menu[4].parameter --;  
                if(menu[4].parameter == -1) menu[4].parameter = 1;
            }
            else
            {
                if(focus ==5)
                {     
                    menu[4].mode = MODE_REVERSE;
                }
                else
                {
                    menu[4].mode = MODE_NORMAL;
                }
                
                 if(menu[4].cur_mode != menu[4].mode)
                 {
                    display_frame_de(RIGHT,COL_PAGE0_PATTERN_E, menu[4].mode);
                    
                    if( menu[4].parameter == 0)
                    {
                    
                      display_num(MIDDLE,COL_PAGE0_EN, menu[4].mode | NUM_1);
                    }
                    else if( menu[4].parameter == 1)
                    {
                      
                      display_num(MIDDLE,COL_PAGE0_EN, menu[4].mode | NUM_2);
                    }
                    else if( menu[4].parameter == 2)
                    {
                      
                      display_num(MIDDLE,COL_PAGE0_EN, menu[4].mode | NUM_0);
                    }
                    
                    menu[4].cur_mode = menu[4].mode;
                 }
                
                
            }
            
            break;
            
        case KEY_V_PRESSED:
            
            if(menu[4].mode == MODE_REVERSE)
            {    
                menu[4].mode = MODE_BLINK;      
                flip = 1;
            }
            else if(menu[4].mode == MODE_BLINK)
            {   
               menu[4].mode = MODE_NORMAL;     
            }
            
             if(menu[4].cur_mode != menu[4].mode)
             //if(1)
             {
                 if(menu[4].mode == MODE_NORMAL)
                 {
                    display_frame_de(RIGHT,COL_PAGE0_PATTERN_E,MODE_NORMAL);
                    if(menu[4].parameter == 0)
                    {
                        
                       display_num(MIDDLE,COL_PAGE0_EN, menu[4].mode | NUM_1);
                       menu[4].value = NUM_1;
                       
                       
                        //needle_len = 4;
                        // hg_op.needle_len = LEN_4_MM;
                        // hg_op.cnt_target_posrst = POS_4_RST; 
                         // hg_op.need_reset =1;
                       
                       hg_op.cnt_pos_nmm_target = POS_1MM_TARGET;
                       hg_op.cnt_pos_nmm =0;
                       
                       hg_op.inject_len = INJECT_LEN_1_MM;
                       
                    }
                    else if(menu[4].parameter == 1)
                    {
                       
                        display_num(MIDDLE,COL_PAGE0_EN, menu[4].mode | NUM_2);
                        menu[4].value = NUM_2;
                        
                        
                        hg_op.cnt_pos_nmm_target = POS_2MM_TARGET;
                        hg_op.cnt_pos_nmm =0;
                        
                        
                        
                        hg_op.inject_len = INJECT_LEN_2_MM;
                        //needle_len = 13;
                        // hg_op.needle_len = LEN_13_MM;
                         
                         //hg_op.cnt_target_posrst = POS_13_RST; 
                         //hg_op.need_reset =1;
                         
                        //
                        //
                        //
                        
                        
                    }
                     else if(menu[4].parameter == 2)
                     {
                        display_num(MIDDLE,COL_PAGE0_EN, menu[4].mode | NUM_0);
                        menu[4].value = NUM_0;
                        
                        
                        hg_op.cnt_pos_nmm_target = POS_0MM_TARGET;
                        hg_op.cnt_pos_nmm =0;
                           
                        hg_op.inject_len = INJECT_LEN_0_MM;
                     }
                    
                 }
                    menu[4].cur_mode = menu[4].mode;  
              }

            break;   
    }

}




void menu5_MsgHandlle(uint8_t key)
{

    switch(key)
    {
        case KEY_UP_PRESSED:
       
            
            if(menu[5].mode == MODE_BLINK)
            {
                menu[5].parameter ++;  
                if(menu[5].parameter == 3) menu[5].parameter = 0;
            }
            else
            {
                if(focus ==6)
                {      
                    menu[5].mode = MODE_REVERSE;
                }
                else
                {
                    menu[5].mode = MODE_NORMAL;
                }
                
                 if(menu[5].cur_mode != menu[5].mode)
                 {
                    
                    display_frame_fghi(TYPE_F,COL_PAGE0_PATTERN_F, menu[5].mode);
    
                    
                    if( menu[5].parameter == 0)
                    {          
                      //display_num(BOTTOM,COL_PAGE0_FN, menu[5].mode | NUM_2P5);
                      display_num(BOTTOM,COL_PAGE0_FN, menu[5].mode | NUM_1);
                    }
                    else if( menu[5].parameter == 1)
                    {  
                      //display_num(BOTTOM,COL_PAGE0_FN, menu[5].mode | NUM_1P5);
                      display_num(BOTTOM,COL_PAGE0_FN, menu[5].mode | NUM_2P5);
                    }
                     else if( menu[5].parameter == 2)
                     {
                        display_num(BOTTOM,COL_PAGE0_FN, menu[5].mode | NUM_5);
                     }
                    
                    menu[5].cur_mode = menu[5].mode;
                 }
                
            }
            
            break;
            
        case KEY_DOWN_PRESSED:
            
                        
            if(menu[5].mode == MODE_BLINK)
            {
                menu[5].parameter --;  
                if(menu[5].parameter == -1) menu[5].parameter = 2;
            }
            else
            {
                if(focus ==6)
                {      
                    menu[5].mode = MODE_REVERSE;
                }
                else
                {
                    menu[5].mode = MODE_NORMAL;
                }
                
                 if(menu[5].cur_mode != menu[5].mode)
                 {
                    
                    display_frame_fghi(TYPE_F,COL_PAGE0_PATTERN_F, menu[5].mode);
    
                    
                    if( menu[5].parameter == 0)
                    {     
                      //display_num(BOTTOM,COL_PAGE0_FN, menu[5].mode | NUM_2P5);
                      display_num(BOTTOM,COL_PAGE0_FN, menu[5].mode | NUM_1);
                    }
                    else if( menu[5].parameter == 1)
                    { 
                      //display_num(BOTTOM,COL_PAGE0_FN, menu[5].mode | NUM_1P5);
                      display_num(BOTTOM,COL_PAGE0_FN, menu[5].mode | NUM_2P5);
                    }
                    else if( menu[5].parameter == 2)
                    {
                       display_num(BOTTOM,COL_PAGE0_FN, menu[5].mode | NUM_5);
                    }
                        
                    
                    
                    menu[5].cur_mode = menu[5].mode;
                 }
                
            }
            
            
            break;
            
        case KEY_V_PRESSED:
            
            if(menu[5].mode == MODE_REVERSE)
            {    
                menu[5].mode = MODE_BLINK;      
                flip = 1;
            }
            else if(menu[5].mode == MODE_BLINK)
            {   
               menu[5].mode = MODE_NORMAL;     
            }
            
             if(menu[5].cur_mode != menu[5].mode)
             //if(1)
             {
                 if(menu[5].mode == MODE_NORMAL)
                 {
                   
                    display_frame_fghi(TYPE_F,COL_PAGE0_PATTERN_F, MODE_NORMAL);
                    if(menu[5].parameter == 0)
                    {
                        
                        //display_num(BOTTOM,COL_PAGE0_FN,NUM_2P5);
                        display_num(BOTTOM,COL_PAGE0_FN,NUM_1);
                        menu[5].value = NUM_1;
                        //needle_len = 4;
                        // hg_op.needle_len = LEN_4_MM;
                         //hg_op.cnt_target_posrst = POS_4_RST; 
                          //hg_op.need_reset =1;
                        if(hg_op.cur_working_mode == WORK_MODE_DROPS)
                        {
                            hg_op.push_len = VOL_TUBE_1ML_PUSH_DROPS;//140;
                        }
                        else  if(hg_op.cur_working_mode == WORK_MODE_C)
                        {
                            hg_op.push_len = VOL_TUBE_1ML_PUSH_C;
                        }
                        else  if(hg_op.cur_working_mode == WORK_MODE_DROP)
                        {
                            hg_op.push_len = VOL_TUBE_1ML_PUSH_DROP;
                        }
                    }
                    else if(menu[5].parameter == 1)
                    {
                       
                        
                        //display_num(BOTTOM,COL_PAGE0_FN,NUM_1P5);
                        display_num(BOTTOM,COL_PAGE0_FN,NUM_2P5);
                        menu[5].value = NUM_2P5;
                        //needle_len = 13;
                         //hg_op.needle_len = LEN_13_MM;
                         
                         //hg_op.cnt_target_posrst = POS_13_RST; 
                         //hg_op.need_reset =1;
                        
                        
                        if(hg_op.cur_working_mode == WORK_MODE_DROPS)
                        {
                          hg_op.push_len = VOL_TUBE_2P5ML_PUSH_DROPS;//130;
                        }
                        else  if(hg_op.cur_working_mode == WORK_MODE_C)
                        {
                             hg_op.push_len = VOL_TUBE_2P5ML_PUSH_C;
                        }
                        else  if(hg_op.cur_working_mode == WORK_MODE_DROP)
                        {
                             hg_op.push_len = VOL_TUBE_2P5ML_PUSH_DROP;
                        }
                        //
                        //
                        //
                        
                        
                    }
                     else if(menu[5].parameter == 2)
                     {
                          display_num(BOTTOM,COL_PAGE0_FN,NUM_5);
                          menu[5].value = NUM_5;
                          
                          
                           if(hg_op.cur_working_mode == WORK_MODE_DROPS)
                           {
                                hg_op.push_len = VOL_TUBE_5ML_PUSH_DROPS;//160;
                           }
                           else  if(hg_op.cur_working_mode == WORK_MODE_C)
                           {
                                hg_op.push_len = VOL_TUBE_5ML_PUSH_C;
                           }
                           else  if(hg_op.cur_working_mode == WORK_MODE_DROP)
                           {
                                 hg_op.push_len = VOL_TUBE_5ML_PUSH_DROP;
                           }
                     }
                    
                 }
                    menu[5].cur_mode = menu[5].mode;
                    
                    
              }
            
            
            break;   
    }

}




void menu6_MsgHandlle(uint8_t key)
{

    switch(key)
    {
        case KEY_UP_PRESSED:
        
            if(menu[6].mode == MODE_BLINK)
            {
                menu[6].parameter ++;  
                if(menu[6].parameter == 3) menu[6].parameter = 0;
            }
            else
            {
                if(focus == 7)
                {
                    menu[6].mode = MODE_REVERSE;
                }
                else
                {
                    menu[6].mode = MODE_NORMAL;
                }
                
                
                 if(menu[6].cur_mode != menu[6].mode)
                 {
                    
                     //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                     if(work_mode == WORK_MODE_C) 
                     {
                        display_frame_fghi(TYPE_G,COL_PAGE0_PATTERN_G, menu[6].mode);
                     }
                     else if(work_mode == WORK_MODE_DROPS)  
                     {
                         display_frame_fghi(TYPE_H,COL_PAGE0_PATTERN_G, menu[6].mode);
                     }
                     else if(work_mode == WORK_MODE_DROP)  
                     {
                          display_frame_fghi(TYPE_I,COL_PAGE0_PATTERN_G, menu[6].mode);
                     }
                     
                     
                    if( menu[6].parameter == 0)
                    {
                      //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                      if(work_mode == WORK_MODE_C) 
                      {
                        display_num(BOTTOM,COL_PAGE0_GN, menu[6].mode | NUM_3);
                      }
                      else if(work_mode == WORK_MODE_DROPS) 
                      {
                        display_num(BOTTOM,COL_PAGE0_HN, menu[6].mode | NUM_250);
                      }
                      else if(work_mode == WORK_MODE_DROP)   
                      {
                          display_num(BOTTOM,COL_PAGE0_GN, menu[6].mode | NUM_0);
                      }
                    }
                    else if( menu[6].parameter == 1)
                    {
                      //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                      if(work_mode == WORK_MODE_C) 
                      {
                         display_num(BOTTOM,COL_PAGE0_GN, menu[6].mode | NUM_3);
                      }
                      else if(work_mode == WORK_MODE_DROPS) 
                      {
                          display_num(BOTTOM,COL_PAGE0_HN, menu[6].mode | NUM_200);
                      }
                      else if(work_mode == WORK_MODE_DROP) 
                      {
                          display_num(BOTTOM,COL_PAGE0_HN, menu[6].mode | NUM_1);
                      }
                      
                      
                    }
                    else if( menu[6].parameter == 2) 
                    {
                        
                      //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                      if(work_mode == WORK_MODE_C) 
                      {
                         display_num(BOTTOM,COL_PAGE0_GN, menu[6].mode | NUM_3);
                      }
                      else if(work_mode == WORK_MODE_DROPS) 
                      {
                          display_num(BOTTOM,COL_PAGE0_HN, menu[6].mode | NUM_150);
                      }
                      else if(work_mode == WORK_MODE_DROP)  
                      {
                          display_num(BOTTOM,COL_PAGE0_HN, menu[6].mode | NUM_2);
                      }
                    }
                    
                    
                    menu[6].cur_mode = menu[6].mode;
                 }
            }
            
            break;
            
        case KEY_DOWN_PRESSED:
            
            if(menu[6].mode == MODE_BLINK)
            {
                menu[6].parameter --;  
                if(menu[6].parameter == -1) menu[6].parameter = 2;
            }
            else
            {
                if(focus == 7)
                {
                    menu[6].mode = MODE_REVERSE;
                }
                else
                {
                    menu[6].mode = MODE_NORMAL;
                }
                
                
                 if(menu[6].cur_mode != menu[6].mode)
                 {
                    
                     //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                     if(work_mode == WORK_MODE_C) 
                     {
                        display_frame_fghi(TYPE_G,COL_PAGE0_PATTERN_G, menu[6].mode);
                     }
                     else if(work_mode == WORK_MODE_DROPS)  
                     {
                         display_frame_fghi(TYPE_H,COL_PAGE0_PATTERN_G, menu[6].mode);
                     }
                     else if(work_mode == WORK_MODE_DROP)  
                     {
                         display_frame_fghi(TYPE_I,COL_PAGE0_PATTERN_G, menu[6].mode);
                     }
       
                    if( menu[6].parameter == 0)
                    {
                      //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                      if(work_mode == WORK_MODE_C) 
                      {
                        display_num(BOTTOM,COL_PAGE0_GN, menu[6].mode | NUM_3);
                      }
                      else if(work_mode == WORK_MODE_DROPS) 
                      {
                           display_num(BOTTOM,COL_PAGE0_HN, menu[6].mode | NUM_250);
                      }
                      else if(work_mode == WORK_MODE_DROP) 
                      {
                          display_num(BOTTOM,COL_PAGE0_GN, menu[6].mode | NUM_0);
                      }
                    }
                    else if( menu[6].parameter == 1)
                    {
                      //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                      if(work_mode == WORK_MODE_C) 
                      {
                         display_num(BOTTOM,COL_PAGE0_GN, menu[6].mode | NUM_3);
                      }
                      else if(work_mode == WORK_MODE_DROPS) 
                      {
                          display_num(BOTTOM,COL_PAGE0_HN, menu[6].mode | NUM_200);
                      }
                      else if(work_mode == WORK_MODE_DROP) 
                      {
                          display_num(BOTTOM,COL_PAGE0_GN, menu[6].mode | NUM_1);
                      }
                      
                      
                      
                      
                    }
                    else if( menu[6].parameter == 2)
                    {
                      //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                      if(work_mode == WORK_MODE_C) 
                      {
                         display_num(BOTTOM,COL_PAGE0_GN, menu[6].mode | NUM_3);
                      }
                      else if(work_mode == WORK_MODE_DROPS) 
                      {
                          display_num(BOTTOM,COL_PAGE0_HN, menu[6].mode | NUM_150);
                      }
                      else if(work_mode == WORK_MODE_DROP) 
                      {
                          display_num(BOTTOM,COL_PAGE0_GN, menu[6].mode | NUM_2);
                      }
                    }
                    
                    
                    menu[6].cur_mode = menu[6].mode;
                 }
            }
            
            
            break;
            
        case KEY_V_PRESSED:
            
                      
            if(menu[6].mode == MODE_REVERSE)
            {    
                menu[6].mode = MODE_BLINK;      
                flip = 1;
            }
            else if(menu[6].mode == MODE_BLINK)
            {   
               menu[6].mode = MODE_NORMAL;     
            }
            
             if(menu[6].cur_mode != menu[6].mode)
             //if(1)
             {
                 if(menu[6].mode == MODE_NORMAL)
                 {

                    //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                    if(work_mode == WORK_MODE_C)
                    {
                        display_frame_fghi(TYPE_G,COL_PAGE0_PATTERN_G,MODE_NORMAL);
                    }
                    else if(work_mode == WORK_MODE_DROPS) 
                    {
                        display_frame_fghi(TYPE_H,COL_PAGE0_PATTERN_G,MODE_NORMAL);
                    }
                    else if(work_mode == WORK_MODE_DROP) 
                    {
                         display_frame_fghi(TYPE_I,COL_PAGE0_PATTERN_G,MODE_NORMAL);
                    }
                    
                    if(menu[6].parameter == 0)
                    {
                       
                        //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                        if(work_mode == WORK_MODE_C) 
                        {
                           display_num(BOTTOM,COL_PAGE0_GN,NUM_3);
                           menu[6].value = NUM_3;
                        }
                        else if(work_mode == WORK_MODE_DROPS) 
                        {
                             display_num(BOTTOM,COL_PAGE0_HN, menu[7].mode | NUM_250);
                             menu[6].value = NUM_250;
                             hg_op.work_freq = DROPS_MODE_250_FREQ;
                        }
                        else if(work_mode == WORK_MODE_DROP) 
                        {
                             display_num(BOTTOM,COL_PAGE0_HN, menu[7].mode | NUM_0);
                             menu[6].value = NUM_0;
                             hg_op.stay_time_drop = 0;
                        }
                        //needle_len = 4;
                        // hg_op.needle_len = LEN_4_MM;
                        // hg_op.cnt_target_posrst = POS_4_RST; 
                         // hg_op.need_reset =1;
                    }
                    else if(menu[6].parameter == 1)
                    {
                        
                         //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                         if(work_mode == WORK_MODE_C) 
                         {
                            display_num(BOTTOM,COL_PAGE0_GN,NUM_3);
                            menu[6].value = NUM_3;
                         }
                        else if(work_mode == WORK_MODE_DROPS) 
                        {
                            display_num(BOTTOM,COL_PAGE0_HN, menu[7].mode | NUM_200);
                            menu[6].value = NUM_200;
                             hg_op.work_freq = DROPS_MODE_200_FREQ;
                            
                        }
                        else if(work_mode == WORK_MODE_DROP) 
                        {
                            display_num(BOTTOM,COL_PAGE0_HN, menu[7].mode | NUM_1);
                            menu[6].value = NUM_1;
                            hg_op.stay_time_drop =1;
                        }
                        
                        //needle_len = 13;
                        // hg_op.needle_len = LEN_13_MM;
                         
                         //hg_op.cnt_target_posrst = POS_13_RST; 
                         //hg_op.need_reset =1;
                         
                        //
                        //
                        //
                        
                        
                    }
                     else if(menu[6].parameter == 2)
                     {
                         
                         //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                         if(work_mode == WORK_MODE_C) 
                         {
                            display_num(BOTTOM,COL_PAGE0_GN,NUM_3);
                            menu[6].value = NUM_3;
                         }
                        else if(work_mode == WORK_MODE_DROPS) 
                        {
                            display_num(BOTTOM,COL_PAGE0_HN, menu[7].mode | NUM_150);
                            menu[6].value = NUM_150;
                             hg_op.work_freq = DROPS_MODE_150_FREQ;
                        }
                        else if(work_mode == WORK_MODE_DROP) 
                        {
                           display_num(BOTTOM,COL_PAGE0_HN, menu[7].mode | NUM_2);
                           menu[6].value = NUM_2;   
                           
                           hg_op.stay_time_drop =2;
                        }
                         
                     }
                    
                 }
                 

                    menu[6].cur_mode = menu[6].mode;
                    
                    
              }
            
            break;   
    }

}





void menu7_MsgHandlle(uint8_t key)
{
    switch(key)
    {
        case KEY_UP_PRESSED:
                
            if(menu[7].mode == MODE_BLINK)
            {
                menu[7].parameter ++;  
                if(menu[7].parameter == 2) menu[7].parameter = 0;
            }
            else
            {
                if(focus == 8)
                {
                    menu[7].mode = MODE_REVERSE;
                }
                else
                {
                    menu[7].mode = MODE_NORMAL;
                }
                
                
                 if(menu[7].cur_mode != menu[7].mode)
                 {
                    
                    display_frame_fghi(TYPE_H,COL_PAGE0_PATTERN_G,menu[7].mode);
                    
                    if( menu[7].parameter == 0)
                    {
                      //display_n250(0,COL_PAGE0_GN, menu[7].mode);
                      display_num(BOTTOM,COL_PAGE0_HN, menu[7].mode | NUM_250);
                    }
                    else if( menu[7].parameter == 1)
                    {
                      //display_n200(0,COL_PAGE0_GN, menu[7].mode);
                      display_num(BOTTOM,COL_PAGE0_HN, menu[7].mode | NUM_200);
                    }
                    
                    
                    menu[7].cur_mode = menu[7].mode;
                 }
            }
            
            
            
            break;
            
        case KEY_DOWN_PRESSED:
            
            
            
            
            
            
            
            
            
            
            break;
            
        case KEY_V_PRESSED:
            
            if(menu[7].mode == MODE_REVERSE)
            {    
                menu[7].mode = MODE_BLINK;      
                flip = 1;
            }
            else if(menu[7].mode == MODE_BLINK)
            {   
               menu[7].mode = MODE_NORMAL;     
            }
            
             if(menu[7].cur_mode != menu[7].mode)
             //if(1)
             {
                 if(menu[7].mode == MODE_NORMAL)
                 {
                   
                    display_frame_fghi(TYPE_H,COL_PAGE0_PATTERN_G, MODE_NORMAL);
                    if(menu[7].parameter == 0)
                    {
                        //display_n2P5(0,COL_PAGE0_DN, MODE_NORMAL);
                        display_num(BOTTOM,COL_PAGE0_HN,NUM_250);
                        //needle_len = 4;
                        // hg_op.needle_len = LEN_4_MM;
                         //hg_op.cnt_target_posrst = POS_4_RST; 
                          //hg_op.need_reset =1;
                    }
                    else if(menu[7].parameter == 1)
                    {
                       
                        //display_n1P5(0,COL_PAGE0_DN, MODE_NORMAL);
                        display_num(BOTTOM,COL_PAGE0_HN,NUM_200);
                        //needle_len = 13;
                         //hg_op.needle_len = LEN_13_MM;
                         
                         //hg_op.cnt_target_posrst = POS_13_RST; 
                         //hg_op.need_reset =1;
                         
                        //
                        //
                        //
                        
                        
                    }
                    
                 }
                    menu[7].cur_mode = menu[7].mode;
                    
                    
              }
            
            break;   
    }


}

void init_menu(void)
{
   
    
    menu[0].menu_no=0;
    menu[0].frame=0;
    menu[0].mode = MODE_NORMAL;
    menu[0].cur_mode =menu[0].mode;
    menu[0].value = 0;
    menu[0].parameter =0;
    menu[0].MsgHandlle = menu0_MsgHandlle;
    
    
    menu[1].menu_no=0;
    menu[1].frame=0;
    menu[1].mode = MODE_NORMAL;
    menu[1].cur_mode =menu[1].mode;
    menu[1].value = 0;
    menu[1].parameter =0;
    menu[1].MsgHandlle = menu1_MsgHandlle;
    
    menu[2].menu_no=0;
    menu[2].frame=0;
    menu[2].mode = MODE_NORMAL;
    menu[2].cur_mode =menu[2].mode;
    menu[2].value = 0;
    menu[2].parameter =0;
    menu[2].MsgHandlle = menu2_MsgHandlle;
    
    
    menu[3].menu_no=0;
    menu[3].frame=0;
    menu[3].mode = MODE_NORMAL;
    menu[3].cur_mode =menu[3].mode;
    menu[3].value = 0;
    menu[3].parameter =0;
    menu[3].MsgHandlle = menu3_MsgHandlle;
    
    
    menu[4].menu_no=0;
    menu[4].frame=0;
    menu[4].mode = MODE_NORMAL;
    menu[4].cur_mode =menu[4].mode;
    menu[4].value = 0;
    menu[4].parameter =0;
    menu[4].MsgHandlle = menu4_MsgHandlle;
    
    menu[5].menu_no=0;
    menu[5].frame=0;
    menu[5].mode = MODE_NORMAL;
    menu[5].cur_mode =menu[5].mode;
    menu[5].value = 0;
    menu[5].parameter =0;
    menu[5].MsgHandlle = menu5_MsgHandlle;
    
    
    menu[6].menu_no=0;
    menu[6].frame=0;
    menu[6].mode = MODE_NORMAL;
    menu[6].cur_mode =menu[6].mode;
    menu[6].value = 0;
    menu[6].parameter =0;
    menu[6].MsgHandlle = menu6_MsgHandlle;
    
    menu[7].menu_no=0;
    menu[7].frame=0;
    menu[7].mode = MODE_NORMAL;
    menu[7].cur_mode =menu[0].mode;
    menu[7].value = 0;
    menu[7].parameter =0;
    menu[7].MsgHandlle = menu7_MsgHandlle;
    
    focus =0;
    flip =0;
    work_mode = WORK_MODE_C;
    
}


void update_focus(uint8_t key)
{

uint8_t i = 0;
for(i=0;i<8;i++)
    if(menu[i].mode == MODE_BLINK) key = KEY_NOT_PRESSED;
    
    switch(key)
       {
           case KEY_UP_PRESSED:
#if 0    
               if(focus == 7)
               {
                   focus =1;
               }
               else
#endif
               {
                    if(focus == 1)
                    {
                       focus += 3;//skip 2 options
                    }
                    else
                    {
                        focus ++;
                         if(focus == 8)focus =1;
                    }
               }
               break;

           case KEY_DOWN_PRESSED:
           
#if 0
               if(focus==0)
               {
                   focus =7;
               }
               else
#endif
               {
                   if(focus == 4)
                   {
                     focus -= 3;//skip 2 options
                   }
                   else
                   {
                       focus --;
                       if(focus==0) focus =7;
                   }
                }
               break;
#if 0
           case KEY_V_PRESSED:
               break;   
#endif
       }

}



void HG_interface(void)
{
    uint8_t kv = 0;
    kv = KEY_Scan();
    update_focus(kv); 
    
#if 1
    if(kv)
    {
                menu0_MsgHandlle(kv);
                menu1_MsgHandlle(kv);
                menu2_MsgHandlle(kv);
                menu3_MsgHandlle(kv);
                menu4_MsgHandlle(kv);
                menu5_MsgHandlle(kv);
                menu6_MsgHandlle(kv);
                //menu7_MsgHandlle(kv);

    }
#endif


}



void enter_sleep(void)
{
    uint8_t temp=0;
       
#if 1
        if( hg_op.status_powerup == STATUS_SLEEP)
        //if(0)
        {
#if 1 
            if(hg_op.needle_len == NEEDLE_LEN_13_MM)
            {
                FORWARD_RUN_B();
                //hg_op.cnt_posrst =0;
                temp =0;
                //while(hg_op.cnt_posrst < 200)
                while(temp < 200)
                {
                    while(READ_PHB_MB() == 0);
                    //hg_op.cnt_posrst ++;
                    temp ++;
                    while(READ_PHB_MB() == 1);
                    //hg_op.cnt_posrst ++;
                    temp ++;
                    
                }
                STOP_B();
                delaynus(50*1000);     
            }
#endif 
            
            
#if 1
            STOP_A();
            STOP_B();
            
            ENABLE_AL();   
            ENABLE_BL(); 
            
         
             
            hg_op.needle_len = NEEDLE_LEN_4_MM;
            //printf("sleep mode\r\n");
#endif
            
            
            DISABLE_ENCODER_PHB_MB();
            NOP();NOP();NOP();NOP();
            
            
            
            while(hg_op.status_powerup == STATUS_SLEEP)
            {
                NOP();NOP();NOP();NOP();
                SLEEP();
                NOP();NOP();NOP();NOP();
                
                
                check_wake_button();
                
                
            }
            
#if 1
            
            //TEST_LED_BLINK();
            //hg_op.need_reset =0;
            
#endif
           
        }
#if 0
        else if( hg_op.status_powerup == STATUS_SLEEP)
        {
            
        }
#endif
    
#endif 
    
}



void initial_para_setting(void)
{
    
        //hg_op.need_reset =1;
    hg_op.need_reset =0;
    //hg_op.cur_working_mode = WORK_MODE_DROPS;//now we assume working in DROPS ;
    hg_op.cur_working_mode = WORK_MODE_C;
    hg_op.cnt_target_posrst = POS_4_RST;     //len=4mm
    hg_op.needle_len = NEEDLE_LEN_4_MM;
    hg_op.status_powerup = STATUS_SLEEP;
    hg_op.working_mode = WORK_MODE_STOP;
   
    hg_op.status_hit_lp = 0;
        
    hg_op.cnt_pos_1mm =0;
    hg_op.cnt_pos_nmm = 0;
    hg_op.cnt_pos_nmm_target = POS_1MM_TARGET;
    hg_op.inject_len = INJECT_LEN_1_MM;
    
}



void check_ui_status(void)
{
    static uint32_t cnt_ui_check =0;
    if(menu[0].mode != MODE_NORMAL)
    {
        cnt_ui_check ++;
        //printf("cnt_ui_check is %d\r\n",cnt_ui_check);
        if(cnt_ui_check > PERIORD_DYNAMIC_UI)
        {
                display_frame_abc(LEFT,COL_PAGE0_PATTERN_A, MODE_NORMAL);
                if(menu[0].value == WORK_MODE_C)
                {
                    display_cmode(LEFT,COL_PAGE0_MDROPS,MODE_NORMAL);
                }
                else if(menu[0].value == WORK_MODE_DROP)
                {
                    display_drop(LEFT,COL_PAGE0_MDROPS,MODE_NORMAL);
                }
                else if(menu[0].value == WORK_MODE_DROPS)
                {
                    display_drops(LEFT,COL_PAGE0_MDROPS,MODE_NORMAL);
                }
                menu[0].mode = MODE_NORMAL;
                cnt_ui_check =0;
                //focus --;
                work_mode = menu[0].value ;
                
                
        }
    }
    else if(menu[1].mode != MODE_NORMAL)
    {
        menu[1].mode = MODE_NORMAL;
    }
    else if(menu[2].mode != MODE_NORMAL)
    {
        menu[2].mode = MODE_NORMAL;
    }
    else if(menu[3].mode != MODE_NORMAL)
    {
       
        cnt_ui_check ++;
        if(cnt_ui_check > PERIORD_DYNAMIC_UI)
        {
        
           display_frame_de(LEFT,COL_PAGE0_PATTERN_D, MODE_NORMAL);
           display_num(MIDDLE,COL_PAGE0_DN, MODE_NORMAL|menu[3].value);
           //0 1 2
           //4 6 13
           
           if(menu[3].value == NUM_4)
           {
               menu[3].parameter =0;
           }
           else if(menu[3].value == NUM_6)
           {
                menu[3].parameter =1;
           }
           else if(menu[3].value == NUM_13)   
           {
                menu[3].parameter =2;
           }
           
           menu[3].mode = MODE_NORMAL;
           cnt_ui_check =0;
           
        }
    }
    else if(menu[4].mode != MODE_NORMAL)
    {
        
        cnt_ui_check ++;
        if(cnt_ui_check > PERIORD_DYNAMIC_UI)
        {      
            display_frame_de(RIGHT,COL_PAGE0_PATTERN_E, MODE_NORMAL);
            display_num(MIDDLE,COL_PAGE0_EN, MODE_NORMAL|menu[4].value);
            
           if(menu[4].value == NUM_1)
           {
               menu[4].parameter =0;
           }
           else if(menu[4].value == NUM_2)
           {
                menu[4].parameter =1;
           }
           else if(menu[4].value == NUM_0)
           {
                menu[4].parameter =2;
           }
            
            menu[4].mode = MODE_NORMAL;
            cnt_ui_check =0;
        }
    }
    else if(menu[5].mode != MODE_NORMAL)
    {
        
        cnt_ui_check ++;
        if(cnt_ui_check > PERIORD_DYNAMIC_UI)
        {
            display_frame_fghi(TYPE_F,COL_PAGE0_PATTERN_F, MODE_NORMAL);
            display_num(BOTTOM,COL_PAGE0_FN, MODE_NORMAL|menu[5].value);
            
            
           if(menu[5].value == NUM_1)
           {
               menu[5].parameter =0;
           }
           else if(menu[5].value == NUM_2P5)
           {
                menu[5].parameter =1;
           }
           else if(menu[5].value == NUM_5)   
           {
                menu[5].parameter =2;
           }
            
            
            
            
            menu[5].mode = MODE_NORMAL;
            cnt_ui_check =0;
        }
    }
    else if(menu[6].mode != MODE_NORMAL)
    {
        cnt_ui_check ++;
        if(cnt_ui_check > PERIORD_DYNAMIC_UI)
        {
            
          if(hg_op.cur_working_mode == WORK_MODE_C)
          {
            display_frame_fghi(TYPE_G,COL_PAGE0_PATTERN_G, MODE_NORMAL);
            display_num(BOTTOM,COL_PAGE0_GN, MODE_NORMAL|menu[6].value);
          }
          else if(hg_op.cur_working_mode == WORK_MODE_DROPS)
          {
            display_frame_fghi(TYPE_H,COL_PAGE0_PATTERN_H, MODE_NORMAL);
            display_num(BOTTOM,COL_PAGE0_HN, MODE_NORMAL|menu[6].value);
            
            if(menu[6].value == NUM_250)
            {
                menu[6].parameter =0;
            }
            else if(menu[6].value == NUM_200)
            {
                 menu[6].parameter =1;
            }
            else if(menu[6].value == NUM_150)   
            {
                 menu[6].parameter =2;
            }
            
            
          }
          else if(hg_op.cur_working_mode == WORK_MODE_DROP)
          {
                display_frame_fghi(TYPE_I,COL_PAGE0_PATTERN_H, MODE_NORMAL);
                display_num(BOTTOM,COL_PAGE0_HN, MODE_NORMAL|menu[6].value);
              
              
                if(menu[6].value == NUM_0)
                {
                    menu[6].parameter =0;
                }
                else if(menu[6].value == NUM_1)
                {
                     menu[6].parameter =1;
                }
                else if(menu[6].value == NUM_2)   
                {
                     menu[6].parameter =2;
                }
              
              
              
          }
          
          menu[6].mode = MODE_NORMAL;
          cnt_ui_check =0;
        }
    }
    else
    {
        cnt_ui_check =0;
    }


}


void shut_device(void)
{
    
    hg_op.status_powerup = STATUS_SLEEP;
                               
    LCD_Off();

    clear_screen();
    
    
    write_buf[0]=0x25;  
    ee_WriteBytes(write_buf, 0x00, 1);

    STOP_A();
    STOP_B();

    //hg_op.needle_len = NEEDLE_LEN_4_MM;
    //hg_op.need_reset =1;

    hg_op.working_mode = WORK_MODE_STOP;
    hg_op.need_reset =0;

    //printf("sleep\r\n");
    
    
}



void check_device_idle(void)
{
    
    
   if(hg_op.working_mode == WORK_MODE_STOP)
   {
        hg_op.cnt_device_idle ++;
        delay_nms(1);
        if(hg_op.cnt_device_idle > (100000))
        {
            hg_op.cnt_device_idle = 0;
            shut_device();
        }
   }
   else
   {
       hg_op.cnt_device_idle = 0;
   }
    
    
}



void check_shut_device(void)
{
    if(hg_op.flag_shut_device == 1)
    {
        //----------------------------------------------------------------------     
#if 1
        if(KEY_WAKE  == 0  && KEY_UP == 1 && KEY_DOWN ==1 && KEY_V ==1)
        {
            delay_nms(4);
            if(KEY_WAKE  == 0  && KEY_UP == 1 && KEY_DOWN ==1 && KEY_V ==1)
            {
                //buzz();
                test_mode =0;

                if(hg_op.status_powerup == STATUS_WAKE)
                {  
                    //delay_pwm(120*1000);
                    delay_pwm(400000);//about 3 seconds
                     if(KEY_WAKE  == 0 && KEY_UP == 1 && KEY_DOWN ==1 && KEY_V ==1)
                     {
                           
                        shut_device();
                        
                        while(KEY_WAKE  == 0);
                        
                        
                        
                        
                         
#if 0 
                        hg_op.status_powerup = STATUS_SLEEP;
                               
                        LCD_Off();

                        write_buf[0]=0x25;  
                        ee_WriteBytes(write_buf, 0x00, 1);

                        STOP_A();
                        STOP_B();

                        //hg_op.needle_len = NEEDLE_LEN_4_MM;
                        //hg_op.need_reset =1;

                        hg_op.working_mode = WORK_MODE_STOP;
                        hg_op.need_reset =0;

                        //printf("sleep\r\n");
#endif
                     }
                }
            }
            
        }
#endif
        
      hg_op.flag_shut_device = 0;  
        
    }
    
    
}





void check_wake_button(void)
{
    if(hg_op.flag_wake_device == 1)
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
                   //printf("wake up\r\n");
                   hg_op.status_hit_lp = 0;
                   hg_op.need_reset =1;
                   hg_op.in_reset =0;
                   hg_op.needle_len = NEEDLE_LEN_4_MM;
                   hg_op.inject_len = INJECT_LEN_1_MM;
                   
                   menu[0].parameter = 0;
                   menu[1].parameter = 0;
                   menu[2].parameter = 0;
                   menu[3].parameter = 0;
                   menu[4].parameter = 0;
                   menu[5].parameter = 0;
                   menu[6].parameter = 0;
                   focus =0;
                   work_mode = WORK_MODE_C; 
                   
                   
                   //Initial_LY096BG30();
                   
                   config_LCD();
                   initial_ui_setting();
                   ENABLE_ENCODER_PHB_MB();
                   
                }
                
                
#if 0
                else if(hg_op.status_powerup == STATUS_WAKE)
                {
                    
                     delay_pwm(120*1000);
                    
                     if(KEY_WAKE  == 0)
                     {
                            hg_op.status_powerup = STATUS_SLEEP;
                            LCD_Off();

                            write_buf[0]=0x25;  
                            ee_WriteBytes(write_buf, 0x00, 1);

                            STOP_A();
                            STOP_B();

                            //hg_op.needle_len = NEEDLE_LEN_4_MM;
                            //hg_op.need_reset =1;

                            hg_op.working_mode = WORK_MODE_STOP;
                            hg_op.need_reset =0;

                            //printf("sleep\r\n");
                     }
                }
                
#endif
            }
            
        }
#endif
        
      hg_op.flag_wake_device = 0;  
        
    }
    
    
}








void blink_mode(void)
{
                //printf("timer\n");
#if 0
            if(STATUS_CHARGE == 0)
            {
                //printf("charging\r\n");
            }
            else
            {
                //printf("not charging\r\n");
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
                    else if(menu[4].parameter == 2)
                    {
                        display_num(MIDDLE,COL_PAGE0_EN, MODE_REVERSE | NUM_0);
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
                        display_num(BOTTOM,COL_PAGE0_FN, MODE_REVERSE | NUM_1);
                    }
                    else if(menu[5].parameter == 1)
                    {
                        //display_num(BOTTOM,COL_PAGE0_FN, MODE_REVERSE | NUM_1P5);
                        display_num(BOTTOM,COL_PAGE0_FN, MODE_REVERSE | NUM_2P5);
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
                       //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                       if(work_mode == WORK_MODE_C) 
                       {
                           display_num(BOTTOM,COL_PAGE0_GN, MODE_REVERSE | NUM_3);
                       }
                       else if(work_mode == WORK_MODE_DROPS) 
                       {
                           display_num(BOTTOM,COL_PAGE0_HN, MODE_REVERSE | NUM_250);
                       }
                       else if(work_mode == WORK_MODE_DROP) 
                       {
                           display_num(BOTTOM,COL_PAGE0_GN, MODE_REVERSE | NUM_0);
                       }
                    }
                    else if(menu[6].parameter == 1)
                    {
                         //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                         if(work_mode == WORK_MODE_C) 
                         {
                             display_num(BOTTOM,COL_PAGE0_GN, MODE_REVERSE | NUM_3);
                         }
                         else if(work_mode == WORK_MODE_DROPS) 
                         {
                              display_num(BOTTOM,COL_PAGE0_HN, MODE_REVERSE | NUM_200);
                          }
                         else if(work_mode == WORK_MODE_DROP) 
                         {
                             display_num(BOTTOM,COL_PAGE0_GN, MODE_REVERSE | NUM_1);
                         }
                    }
                    else if(menu[6].parameter == 2)
                    {
                         //if(work_mode == WORK_MODE_C ||  work_mode == WORK_MODE_DROP) 
                         if(work_mode == WORK_MODE_C) 
                         {
                           display_num(BOTTOM,COL_PAGE0_GN, MODE_REVERSE | NUM_3);
                         }
                         else if(work_mode == WORK_MODE_DROPS) 
                         {
                              display_num(BOTTOM,COL_PAGE0_HN, MODE_REVERSE | NUM_150);
                          }
                          else if(work_mode == WORK_MODE_DROP) 
                          {
                              display_num(BOTTOM,COL_PAGE0_GN, MODE_REVERSE | NUM_2);
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
    
    
    
    
}





void check_ui_blink(void)
{
    
#if 1
            if(flag_blink)
            {
                blink_mode();
                flag_blink =0;
            }     
#endif
    
    
}