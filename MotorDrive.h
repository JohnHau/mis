#ifndef   MOTO_DRIVE_H
#define   MOTO_DRIVE_H

//电机电源控制PIN
#define SET_MOTOR_VCC_CONTROL_PIN_DIR_OUT		(DDRAbits.RA5  =0)	//输出		
#define SET_MOTOR_VCC_CONTROL_PIN  				(PORTAbits.RA5 =0)  /*电机驱动芯片电源控制脚*/
#define CLEAR_MOTOR_VCC_CONTROL_PIN  			(PORTAbits.RA5 =1)  /*电机驱动芯片电源控制脚*/

//L298N 
#define SET_L298N_A_ENABLE_PIN_DIR_OUT			(DDREbits.RE0  =0)	//输出
#define SET_L298N_A_ENABLE_PIN  				(PORTEbits.RE0 =1)  /*L298N ENABLE A*/
#define CLEAR_L298N_A_ENABLE_PIN   				(PORTEbits.RE0 =0)  /*L298N ENABLE A*/

#define SET_L298N_INPUT1_PIN_DIR_OUT			(DDREbits.RE1  =0)	//输出
#define SET_L298N_INPUT1_PIN 					(PORTEbits.RE1 =1)  /*L298N INPUT1*/
#define CLEAR_L298N_INPUT1_PIN    				(PORTEbits.RE1 =0)  /*L298N INPUT1*/

#define SET_L298N_INPUT2_PIN_DIR_OUT			(DDREbits.RE2  =0)	//输出
#define SET_L298N_INPUT2_PIN  					(PORTEbits.RE2 =1)  /*L298N INPUT2*/
#define CLEAR_L298N_INPUT2_PIN    				(PORTEbits.RE2 =0)  /*L298N INPUT2*/

//
#define SET_L298N_B_ENABLE_PIN_DIR_OUT			(DDRCbits.RC1  =0)	//输出
#define SET_L298N_B_ENABLE_PIN  				(PORTCbits.RC1 =1)  /*L298N ENABLE B*/
#define CLEAR_L298N_B_ENABLE_PIN   				(PORTCbits.RC1 =0)  /*L298N ENABLE B*/

#define SET_L298N_INPUT3_PIN_DIR_OUT			(DDRCbits.RC2  =0)	//输出
#define SET_L298N_INPUT3_PIN  					(PORTCbits.RC2 =1)  /*L298N INPUT3*/
#define CLEAR_L298N_INPUT3_PIN    				(PORTCbits.RC2 =0)  /*L298N INPUT3*/

#define SET_L298N_INPUT4_PIN_DIR_OUT			(DDRDbits.RD2  =0)	//输出
#define SET_L298N_INPUT4_PIN  					(PORTDbits.RD2 =1)  /*L298N INPUT4*/
#define CLEAR_L298N_INPUT4_PIN    				(PORTDbits.RD2 =0)  /*L298N INPUT4*/

//出针深度限位开关
#define SET_L298N_INPUT4_PIN_DIR_IN				(DDRBbits.RB0  =1)	//输入
#define NEEDLE_MOTOR_LI_POS_PIN  				 PORTBbits.RB0  	/*出针深度电机限位开关*/

//电机电流

extern void MotorDriveInit(void);

extern void OpenMotorPower(void);

extern void CloseMotorPower(void);

extern void NeedleMotorForwardRun(void);
extern void NeedleMotorReverseRun(void);
extern void NeedleMotorFastStop(void);
extern void NeedleMotorFreeStop(void);

extern void InjectionMotorForwardRun(void);
extern void InjectionMotorReverseRun(void);
extern void InjectionMotorFastStop(void);
extern void InjectionMotorFreeStop(void);

#endif