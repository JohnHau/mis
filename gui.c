#include <xc.h>
#include "Beep.h"
#include "Oled.h"
#include "Key.h"
#include "gui.h"

uint8_t focus =0;
MENU menu[8]={0};



void HG_init(void)
{
    BeepInit();
    LCD_backlight_init();
    LCD_On();
    
    Initial_LY096BG30();
    init_menu();
    KEY_Init();

   
    
    
    
    
#if 0
    MotorDriveInit();
    
    ENABLE_AH();
    ENABLE_BH();
    
    
    FORWARD_RUN_A();   
    FORWARD_RUN_B();   
    
	//PositionCheckInit();
	
#endif
    
}



void menu0_MsgHandlle(uint8_t key)
{
    
    switch(key)
    {
        case KEY_UP_PRESSED:
                 
            if(menu[0].mode == MODE_BLINK)
            {
                
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
                    display_frame_abc(0,COL_PAGE0_PATTERN_A, menu[0].mode);
                    display_cmode(0,COL_PAGE0_MDROPS, menu[0].mode);
                    menu[0].cur_mode = menu[0].mode;
                    
                    
                }
                
                
            }
            
            
            
            break;
            
        case KEY_DOWN_PRESSED:
            break;
            
        case KEY_V_PRESSED:
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
                display_frame_abc(0,COL_PAGE0_PATTERN_B, menu[1].mode);
                display_mem(0,COL_PAGE0_MEM,menu[1].mode);
                
                menu[1].cur_mode = menu[1].mode;
                 }
                
            }
            
            
            
            
            
            break;
            
        case KEY_DOWN_PRESSED:
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
            display_frame_abc(0,COL_PAGE0_PATTERN_C, menu[2].mode);
            display_bat(0,COL_PAGE0_BAT,menu[2].mode);
            menu[2].cur_mode = menu[2].mode;
             }
            break;
            
        case KEY_DOWN_PRESSED:
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
                
            }
            else
            {
                if(focus ==4)
                {
                    menu[3].mode = MODE_REVERSE;
                }
                else
                {
                    menu[3].mode = MODE_NORMAL;
                }
                
                
                 if(menu[3].cur_mode != menu[3].mode)
                 {
                display_frame_de(1,COL_PAGE0_PATTERN_D, menu[3].mode);
                display_n4(0,COL_PAGE0_DN, menu[3].mode);
                menu[3].cur_mode = menu[3].mode;
                 }
            }
            
            
            break;
            
        case KEY_DOWN_PRESSED:
            break;
            
        case KEY_V_PRESSED:
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
            }
            
            display_frame_de(1,COL_PAGE0_PATTERN_E, menu[4].mode);
            display_n4(0,COL_PAGE0_EN, menu[4].mode);
            
            break;
            
        case KEY_DOWN_PRESSED:
            break;
            
        case KEY_V_PRESSED:
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
                
                display_frame_fghi(2,COL_PAGE0_PATTERN_F, menu[5].mode);
                 display_n5(0,COL_PAGE0_FN, menu[5].mode);
                
                
            }
            
            break;
            
        case KEY_DOWN_PRESSED:
            break;
            
        case KEY_V_PRESSED:
            break;   
    }

}




void menu6_MsgHandlle(uint8_t key)
{

    switch(key)
    {
        case KEY_UP_PRESSED:
            break;
            
        case KEY_DOWN_PRESSED:
            break;
            
        case KEY_V_PRESSED:
            break;   
    }

}





void menu7_MsgHandlle(uint8_t key)
{
    switch(key)
    {
        case KEY_UP_PRESSED:
            break;
            
        case KEY_DOWN_PRESSED:
            break;
            
        case KEY_V_PRESSED:
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
    menu[0].MsgHandlle = menu0_MsgHandlle;
    
    
    menu[1].menu_no=0;
    menu[1].frame=0;
    menu[1].mode = MODE_NORMAL;
    menu[1].cur_mode =menu[1].mode;
    menu[1].value = 0;
    menu[1].MsgHandlle = menu1_MsgHandlle;
    
    menu[2].menu_no=0;
    menu[2].frame=0;
    menu[2].mode = MODE_NORMAL;
    menu[2].cur_mode =menu[2].mode;
    menu[2].value = 0;
    menu[2].MsgHandlle = menu2_MsgHandlle;
    
    
    menu[3].menu_no=0;
    menu[3].frame=0;
    menu[3].mode = MODE_NORMAL;
    menu[3].cur_mode =menu[3].mode;
    menu[3].value = 0;
    menu[3].MsgHandlle = menu3_MsgHandlle;
    
    
    menu[4].menu_no=0;
    menu[4].frame=0;
    menu[4].mode = MODE_NORMAL;
    menu[4].cur_mode =menu[4].mode;
    menu[4].value = 0;
    menu[4].MsgHandlle = menu4_MsgHandlle;
    
    menu[5].menu_no=0;
    menu[5].frame=0;
    menu[5].mode = MODE_NORMAL;
    menu[5].cur_mode =menu[5].mode;
    menu[5].value = 0;
    menu[5].MsgHandlle = menu5_MsgHandlle;
    
    
    menu[6].menu_no=0;
    menu[6].frame=0;
    menu[6].mode = MODE_NORMAL;
    menu[6].cur_mode =menu[6].mode;
    menu[6].value = 0;
    menu[6].MsgHandlle = menu6_MsgHandlle;
    
    menu[7].menu_no=0;
    menu[7].frame=0;
    menu[7].mode = MODE_NORMAL;
    menu[7].cur_mode =menu[0].mode;
    menu[7].value = 0;
    menu[7].MsgHandlle = menu7_MsgHandlle;
    
    
    
    
}


void update_focus(uint8_t key)
{

    
uint8_t i = 0;
for(i=0;i<8;i++)
    if(menu[i].mode == MODE_BLINK) key = KEY_NOT_PRESSED;
    
    switch(key)
       {
           case KEY_UP_PRESSED:
               
               if(focus == 8)
                   focus =1;
               else
                   focus++;
               
               
               
               
               
               
               break;

           case KEY_DOWN_PRESSED:
               if(focus==0)
                   focus =7;
               else
                   focus --;
               
               
               break;

           case KEY_V_PRESSED:
               break;   
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
                //menu4_MsgHandlle(kv);
                //menu5_MsgHandlle(kv);
                //menu6_MsgHandlle(kv);
                //menu7_MsgHandlle(kv);




        


    }
#endif


}