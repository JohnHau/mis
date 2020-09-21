#include <xc.h>
#include <stdint.h>
#include"MotorDrive.h"


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
        
void OpenMotorPower(void)
{
	//SET_MOTOR_VCC_CONTROL_PIN;
}
void CloseMotorPower(void)
{
	//CLEAR_MOTOR_VCC_CONTROL_PIN;
}

void NeedleMotorForwardRun(void)
{
	//SET_L298N_INPUT3_PIN; 			
	//CLEAR_L298N_INPUT3_PIN;    			
	
	//SET_L298N_INPUT4_PIN;  			
	//CLEAR_L298N_INPUT4_PIN;  

	//SET_L298N_B_ENABLE_PIN;  		
	//CLEAR_L298N_B_ENABLE_PIN;   		
}
void NeedleMotorReverseRun(void)
{
  		
	//SET_L298N_INPUT3_PIN; 			
	//CLEAR_L298N_INPUT3_PIN;    			
	
	//SET_L298N_INPUT4_PIN;  			
	//CLEAR_L298N_INPUT4_PIN; 

	//SET_L298N_B_ENABLE_PIN;  		
	//CLEAR_L298N_B_ENABLE_PIN; 	
}
void NeedleMotorFastStop(void)
{	
	//SET_L298N_INPUT3_PIN; 			
	//CLEAR_L298N_INPUT3_PIN;    			
	
	//SET_L298N_INPUT4_PIN;  			
	//CLEAR_L298N_INPUT4_PIN; 

	//SET_L298N_B_ENABLE_PIN;  		
	//CLEAR_L298N_B_ENABLE_PIN;   		

}
void NeedleMotorFreeStop(void)
{
	//SET_L298N_B_ENABLE_PIN;  		
	//CLEAR_L298N_B_ENABLE_PIN;   		
	
	//SET_L298N_INPUT3_PIN; 			
	//CLEAR_L298N_INPUT3_PIN;    			
	
	//SET_L298N_INPUT4_PIN;  			
	//CLEAR_L298N_INPUT4_PIN; 
}

void InjectionMotorForwardRun(void)
{
	
	//SET_L298N_INPUT1_PIN;
	//CLEAR_L298N_INPUT1_PIN;
	
	//SET_L298N_INPUT2_PIN;
	//CLEAR_L298N_INPUT2_PIN;

	//SET_L298N_A_ENABLE_PIN;
	//CLEAR_L298N_A_ENABLE_PIN;  	
}

void InjectionMotorReverseRun(void)
{	
	//SET_L298N_INPUT1_PIN;
	//CLEAR_L298N_INPUT1_PIN;
	
	//SET_L298N_INPUT2_PIN;
	//CLEAR_L298N_INPUT2_PIN;

	//SET_L298N_A_ENABLE_PIN;
	//CLEAR_L298N_A_ENABLE_PIN;	     		
}

void InjectionMotorFastStop(void)
{	
	//SET_L298N_INPUT1_PIN;
	//CLEAR_L298N_INPUT1_PIN;
	
	//SET_L298N_INPUT2_PIN;
	//CLEAR_L298N_INPUT2_PIN;

	//SET_L298N_A_ENABLE_PIN;
	//CLEAR_L298N_A_ENABLE_PIN;   		

}
void InjectionMotorFreeStop(void)
{
	//SET_L298N_INPUT1_PIN;
	//CLEAR_L298N_INPUT1_PIN;
	
	//SET_L298N_INPUT2_PIN;
	//CLEAR_L298N_INPUT2_PIN;

	//SET_L298N_A_ENABLE_PIN;
	//CLEAR_L298N_A_ENABLE_PIN;  
}

void MotorDriveInit(void)
{
	
       //===========================================================
#if 0
    //CCPR2= 99;
    PR2= 99;
    CCPR1L= 10;
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
    
    
    ENABLE_AL();   
    INPUT1_AL(); 
    INPUT2_AL(); 
    
    ENABLE_BL();   
    INPUT3_BL(); 
    INPUT4_BL(); 
    
    MPON();
    //=========================================================
#if 1
    INTCON2bits.INTEDG2 = 0;//falling edge
    INTCON3bits.INT2IF =0;
    INTCON3bits.INT2E = 1;//PHB_MB  
    
#endif
    //=========================================================
    
    
 
    
    
    
}

