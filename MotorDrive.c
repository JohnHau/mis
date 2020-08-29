//#include <p18cxxx.h>
#include <xc.h>
//#include <delays.h>
#include"MotorDrive.h"

void OpenMotorPower(void)
{
	SET_MOTOR_VCC_CONTROL_PIN;
}
void CloseMotorPower(void)
{
	CLEAR_MOTOR_VCC_CONTROL_PIN;
}

void NeedleMotorForwardRun(void)
{
	//SET_L298N_INPUT3_PIN; 			
	CLEAR_L298N_INPUT3_PIN;    			
	
	SET_L298N_INPUT4_PIN;  			
	//CLEAR_L298N_INPUT4_PIN;  

	SET_L298N_B_ENABLE_PIN;  		
	//CLEAR_L298N_B_ENABLE_PIN;   		
}
void NeedleMotorReverseRun(void)
{
  		
	SET_L298N_INPUT3_PIN; 			
	//CLEAR_L298N_INPUT3_PIN;    			
	
	//SET_L298N_INPUT4_PIN;  			
	CLEAR_L298N_INPUT4_PIN; 

	SET_L298N_B_ENABLE_PIN;  		
	//CLEAR_L298N_B_ENABLE_PIN; 	
}
void NeedleMotorFastStop(void)
{	
	SET_L298N_INPUT3_PIN; 			
	//CLEAR_L298N_INPUT3_PIN;    			
	
	SET_L298N_INPUT4_PIN;  			
	//CLEAR_L298N_INPUT4_PIN; 

	SET_L298N_B_ENABLE_PIN;  		
	//CLEAR_L298N_B_ENABLE_PIN;   		

}
void NeedleMotorFreeStop(void)
{
	//SET_L298N_B_ENABLE_PIN;  		
	CLEAR_L298N_B_ENABLE_PIN;   		
	
	//SET_L298N_INPUT3_PIN; 			
	//CLEAR_L298N_INPUT3_PIN;    			
	
	//SET_L298N_INPUT4_PIN;  			
	//CLEAR_L298N_INPUT4_PIN; 
}
//向前走
void InjectionMotorForwardRun(void)
{
	
	SET_L298N_INPUT1_PIN;
	//CLEAR_L298N_INPUT1_PIN;
	
	//SET_L298N_INPUT2_PIN;
	CLEAR_L298N_INPUT2_PIN;

	SET_L298N_A_ENABLE_PIN;
	//CLEAR_L298N_A_ENABLE_PIN;  	
}
//向后走
void InjectionMotorReverseRun(void)
{	
	//SET_L298N_INPUT1_PIN;
	CLEAR_L298N_INPUT1_PIN;
	
	SET_L298N_INPUT2_PIN;
	//CLEAR_L298N_INPUT2_PIN;

	SET_L298N_A_ENABLE_PIN;
	//CLEAR_L298N_A_ENABLE_PIN;	     		
}

void InjectionMotorFastStop(void)
{	
	SET_L298N_INPUT1_PIN;
	//CLEAR_L298N_INPUT1_PIN;
	
	SET_L298N_INPUT2_PIN;
	//CLEAR_L298N_INPUT2_PIN;

	SET_L298N_A_ENABLE_PIN;
	//CLEAR_L298N_A_ENABLE_PIN;   		

}
void InjectionMotorFreeStop(void)
{
	//SET_L298N_INPUT1_PIN;
	//CLEAR_L298N_INPUT1_PIN;
	
	//SET_L298N_INPUT2_PIN;
	//CLEAR_L298N_INPUT2_PIN;

	SET_L298N_A_ENABLE_PIN;
	//CLEAR_L298N_A_ENABLE_PIN;  
}

void MotorDriveInit(void)
{
	
    
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
    
    
#if 0
    //L298N
	SET_L298N_INPUT1_PIN;
	SET_L298N_INPUT1_PIN_DIR_OUT;

	SET_L298N_INPUT2_PIN;
	SET_L298N_INPUT2_PIN_DIR_OUT;
 
	SET_L298N_A_ENABLE_PIN;
	SET_L298N_A_ENABLE_PIN_DIR_OUT;
	
	//
	SET_L298N_INPUT3_PIN;
	SET_L298N_INPUT3_PIN_DIR_OUT;
	
	SET_L298N_INPUT4_PIN;
	SET_L298N_INPUT4_PIN_DIR_OUT;

	SET_L298N_B_ENABLE_PIN;
	SET_L298N_B_ENABLE_PIN_DIR_OUT;
	
	//电机电源控制PIN
	SET_MOTOR_VCC_CONTROL_PIN;
	SET_MOTOR_VCC_CONTROL_PIN_DIR_OUT;	
#endif
}

