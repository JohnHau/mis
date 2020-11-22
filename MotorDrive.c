#include <xc.h>
#include <stdio.h>
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
        





#if 0
uint8_t Compute()
{
   if(!inAuto) return false;
   
   unsigned long now = millis();
   unsigned long timeChange = (now - lastTime);
   if(timeChange>=SampleTime)
   {
      /*Compute all the working error variables*/
      double input = *myInput;
      double error = *mySetpoint - input;
      double dInput = (input - lastInput);
      outputSum+= (ki * error);

      /*Add Proportional on Measurement, if P_ON_M is specified*/
      if(!pOnE) outputSum-= kp * dInput;

      if(outputSum > outMax) outputSum= outMax;
      else if(outputSum < outMin) outputSum= outMin;

      /*Add Proportional on Error, if P_ON_E is specified*/
	   double output;
      if(pOnE) output = kp * error;
      else output = 0;

      /*Compute Rest of PID Output*/
      output += outputSum - kd * dInput;

	    if(output > outMax) output = outMax;
      else if(output < outMin) output = outMin;
	    *myOutput = output;

      /*Remember some variables for next time*/
      lastInput = input;
      lastTime = now;
	    return true;
   }
   else return false;
}

#endif






PARAPID  f_motor;
PARAPID  r_motor;


void PID_SetTunings(PARAPID * p)
{
    
#if 0
    p->kp =5.0;
    p->ki =0.2;
    p->kd =30.0;
   
#endif
    
#if 1
    p->kp =16.0;
    p->ki =1.2;
    p->kd =80.0;
   
#endif
    
    
    
    
    p->outMax =3.0;
    p->outMin = 0;
    
    p->outputSum =0;
    
    p->mySetpoint = 100.0;
    
    
    p->lastInput = 0.0;
    p->myInput =0.0;
    
}









uint8_t PID_Compute(PARAPID * p)
{
   //if(!inAuto) return false;
   if(0) return 0;
   
   //unsigned long now = millis();
   //unsigned long timeChange = (now - lastTime);
   //if(timeChange>=SampleTime)
   if(1)
   {
      /*Compute all the working error variables*/
      double input = p->myInput;
      double error = p->mySetpoint - input;
      double dInput = (input - p->lastInput);
      p->outputSum+= (p->ki * error);

      /*Add Proportional on Measurement, if P_ON_M is specified*/
      //if(!pOnE) outputSum-= p->kp * dInput;

      if(p->outputSum > p->outMax) p->outputSum= p->outMax;
      else if(p->outputSum < p->outMin) p->outputSum= p->outMin;

      /*Add Proportional on Error, if P_ON_E is specified*/
	   double output;
      //if(pOnE) output = p->kp * error;
      if(1) output = p->kp * error;  
      else output = 0;

      /*Compute Rest of PID Output*/
      output += p->outputSum - p->kd * dInput;

	    if(output > p->outMax) output = p->outMax;
      else if(output < p->outMin) output = p->outMin;
	    p->myOutput = output;

      /*Remember some variables for next time*/
      p->lastInput = input;
      //lastTime = now;
      

      
      
	    return 1;
   }
   else return 0;
}







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

