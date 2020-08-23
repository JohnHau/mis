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
//��ǰ��
void InjectionMotorForwardRun(void)
{
	
	SET_L298N_INPUT1_PIN;
	//CLEAR_L298N_INPUT1_PIN;
	
	//SET_L298N_INPUT2_PIN;
	CLEAR_L298N_INPUT2_PIN;

	SET_L298N_A_ENABLE_PIN;
	//CLEAR_L298N_A_ENABLE_PIN;  	
}
//�����
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
	
	//�����Դ����PIN
	SET_MOTOR_VCC_CONTROL_PIN;
	SET_MOTOR_VCC_CONTROL_PIN_DIR_OUT;	

}
