#ifndef   MOTO_DRIVE_H
#define   MOTO_DRIVE_H

#include <stdint.h>



#define SET_MOTOR_VCC_CONTROL_PIN_DIR_OUT		(DDRAbits.RA5  =0)	
#define SET_MOTOR_VCC_CONTROL_PIN  				(PORTAbits.RA5 =0)  
#define CLEAR_MOTOR_VCC_CONTROL_PIN  			(PORTAbits.RA5 =1)  

//L298N 
#define SET_L298N_A_ENABLE_PIN_DIR_OUT			(DDREbits.RE0  =0)	
#define SET_L298N_A_ENABLE_PIN  				(PORTEbits.RE0 =1)  
#define CLEAR_L298N_A_ENABLE_PIN   				(PORTEbits.RE0 =0)  

#define SET_L298N_INPUT1_PIN_DIR_OUT			(DDREbits.RE1  =0)	
#define SET_L298N_INPUT1_PIN 					(PORTEbits.RE1 =1)  
#define CLEAR_L298N_INPUT1_PIN    				(PORTEbits.RE1 =0)  

#define SET_L298N_INPUT2_PIN_DIR_OUT			(DDREbits.RE2  =0)	
#define SET_L298N_INPUT2_PIN  					(PORTEbits.RE2 =1)  
#define CLEAR_L298N_INPUT2_PIN    				(PORTEbits.RE2 =0)  

//
#define SET_L298N_B_ENABLE_PIN_DIR_OUT			(DDRCbits.RC1  =0)	
#define SET_L298N_B_ENABLE_PIN  				(PORTCbits.RC1 =1)  
#define CLEAR_L298N_B_ENABLE_PIN   				(PORTCbits.RC1 =0) 

#define SET_L298N_INPUT3_PIN_DIR_OUT			(DDRCbits.RC2  =0)	
#define SET_L298N_INPUT3_PIN  					(PORTCbits.RC2 =1)  
#define CLEAR_L298N_INPUT3_PIN    				(PORTCbits.RC2 =0)  

#define SET_L298N_INPUT4_PIN_DIR_OUT			(DDRDbits.RD2  =0)	
#define SET_L298N_INPUT4_PIN  					(PORTDbits.RD2 =1)  
#define CLEAR_L298N_INPUT4_PIN    				(PORTDbits.RD2 =0)  


#define SET_L298N_INPUT4_PIN_DIR_IN				(DDRBbits.RB0  =1)	
#define NEEDLE_MOTOR_LI_POS_PIN  				 PORTBbits.RB0  	


//==============================================================================

#define  MPON()      LATAbits.LA5 =1
#define  MPOFF()     LATAbits.LA5 =0

#define  ENABLE_AH()    LATCbits.LC2 =1
#define  ENABLE_AL()    LATCbits.LC2 =0

#define INPUT1_AH()    LATDbits.LD0 =1
#define INPUT1_AL()    LATDbits.LD0 =0

#define INPUT2_AH()    LATDbits.LD1 =1
#define INPUT2_AL()    LATDbits.LD1 =0

//#define STOP_A()      do{INPUT1_AL();INPUT2_AL(); ENABLE_AL();}while(0)
#define STOP_A()      do{INPUT1_AL();INPUT2_AL();}while(0)

#define FORWARD_RUN_A()   do{STOP_A();INPUT1_AH();INPUT2_AL(); ENABLE_AH(); }while(0)
#define REVERSE_RUN_A()   do{STOP_A();INPUT1_AL();INPUT2_AH(); ENABLE_AH();}while(0)




#define READ_PHA_MA()    PORTCbits.RC1
#define READ_PHB_MA()    PORTAbits.RA4    // works

#define READ_PHA_MB()    PORTCbits.RC0
#define READ_PHB_MB()    PORTBbits.RB2
//------------------------------------------------------------------------------

#define  ENABLE_BH()    LATDbits.LD4 =1
#define  ENABLE_BL()    LATDbits.LD4 =0

#define INPUT3_BH()    LATDbits.LD2 =1
#define INPUT3_BL()    LATDbits.LD2 =0

#define INPUT4_BH()    LATDbits.LD3 =1
#define INPUT4_BL()    LATDbits.LD3 =0

//#define STOP_B()      do{INPUT3_BL();INPUT4_BL(); ENABLE_BL(); }while(0)
#define STOP_B()      do{ENABLE_BH();INPUT3_BL();INPUT4_BL();}while(0)
//#define STOP_B()      do{ENABLE_BH();INPUT3_BH();INPUT4_BH();}while(0)


//#define FORWARD_RUN_B()   do{STOP_B();INPUT3_BH();INPUT4_BL(); ENABLE_BH();}while(0)
//#define REVERSE_RUN_B()   do{STOP_B();INPUT3_BL();INPUT4_BH(); ENABLE_BH();}while(0)

#define FORWARD_RUN_B()   do{INPUT3_BH();INPUT4_BL(); ENABLE_BH();}while(0)
#define REVERSE_RUN_B()   do{INPUT3_BL();INPUT4_BH(); ENABLE_BH();}while(0)







#define DAYNAMIC_BRAKE

#if defined(DAYNAMIC_BRAKE)
#define F_RUNNING_BRAKE_MB()  do{FORWARD_RUN_B();brake_MB();STOP_B();}while(0)
#define R_RUNNING_BRAKE_MB()  do{REVERSE_RUN_B();brake_MB();STOP_B();}while(0)

#else
#define F_RUNNING_BRAKE_MB()  do{FORWARD_RUN_B();delaynus(15*1000);STOP_B();}while(0)
#define R_RUNNING_BRAKE_MB()  do{REVERSE_RUN_B();delaynus(15*1000);STOP_B();}while(0)

#endif







extern uint8_t prev_state_phb_ma;
extern uint8_t cur_state_phb_ma;

extern uint32_t cnt_ma;
extern uint32_t cnt_mb;


extern uint32_t cnt_mb_sa;
extern uint32_t cnt_mb_sb;




extern uint8_t flag_inject;

extern uint8_t flag_mreset;
extern uint8_t flag_mreset_hit_lp;

extern uint8_t flag_inject_sa;
extern uint8_t flag_inject_sb;

extern uint8_t flag_push;

extern uint8_t flag_action;


extern uint8_t flag_go_to_sleep;

extern uint8_t flag_wake_up;

extern uint8_t flag_do_reset_in_drops_mode;  

extern uint8_t flag_action_button;


void MotorDriveInit(void);

uint16_t brake_MB(void);

void hg_reset(void);

void drops_routine(void);
void c_routine(void);
void test_routine(void);


void check_acting(void);

#endif