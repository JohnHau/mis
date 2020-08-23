
#ifndef POSITION_CONTROL_H
#define POSITION_CONTROL_H

#define NEEDLE_MOTOR_FEEDBACK1 (PORTCbits.RC0)
#define NEEDLE_MOTOR_FEEDBACK2 (PORTBbits.RB2)

#define INJECTION_MOTOR_FEEDBACK1 (PORTAbits.RA4)
#define INJECTION_MOTOR_FEEDBACK2 (PORTDbits.RD1)

//Needle Motor: 1 Pulse = (15.783/电机减速比*电机一圈输出脉冲数) mm
//15.783 mm 外部看电机转1圈螺杆走过的距离
//用41:1
#define NEEDLE_ONE_PULSE_TO_MM							24	//1个脉冲对应um

#define NEEDLE_LENGTH_4MM_ZERO_PULSE_NUM				491				
#define NEEDLE_LENGTH_6MM_ZERO_PULSE_NUM			    408	
#define NEEDLE_LENGTH_13MM_ZERO_PULSE_NUM			    116	

//针长度
#define INJECTION_LENGTH_4MM								0 //4MM
#define INJECTION_LENGTH_6MM								1 //6MM
#define INJECTION_LENGTH_13MM								2 //14MM

//Injection Motor:1 Pulse = (螺距/（外部减速比*电机减速比）*电机一圈输出脉冲数) mm
//15.783 mm 外部看电机转1圈螺杆走过的距离
//注液电机用22:1
#define INJECTION_ONE_PULSE_TO_MM						3	//1个脉冲对应um数

#define INJECTION_1_ML_TYPE								0			//1ml注射器
#define INJECTION_2_ML_TYPE								1			//2ml注射器
#define INJECTION_2_5_ML_TYPE							2			//2.5ml注射
#define INJECTION_5_ML_TYPE								3			//5ml注射器
#define INJECTION_10_ML_TYPE							4			//10ml注射器


#define INJECTION_1_ML_LENGTH							57639			//1ml注射器有效长度 um
#define INJECTION_2_ML_LENGTH							32004			//2ml注射器有效长度 um
#define INJECTION_2_5_ML_LENGTH							40005			//2.5ml注射器有效长度 um
#define INJECTION_5_ML_LENGTH							41005			//5ml注射器有效长度 um
#define INJECTION_10_ML_LENGTH							57505			//10ml注射器有效长度 um

//定义具有工作模式 待继续添加
#define CONTINUE_WORK_MODE								0				//连续工作模式
#define MICROSCALE_WORK_MODE							1				//连续工作模式



typedef struct 
{
	unsigned char InjectMode;//注射模式
    unsigned char InjectType;//注射器类型
	unsigned char NeedleLength;//针头长度
	unsigned char InjectDepth;//针头长度
	unsigned char Variable;//每种参数下对应含义不同 注射量、或注射频率
}WorkParaType;

extern WorkParaType CurrentWorkPara;

extern volatile unsigned int InjectionMotorCurrentPosition,InjectionMotorAimPosition;	//注射电机位置
extern volatile  int NeedleMotorCurrentPosition,NeedleMotorAimPosition;		//注射出针电机位置
extern volatile unsigned int NeedleInitPosition;
extern unsigned char NeedleMotorFindZeroPosFlag;

extern unsigned int  ContinueWorkTimePeriod ;
extern unsigned int  ContinueWorkTimeCount;
extern unsigned char NeedleRunDir;
extern unsigned char StartWorkFlag,ContinueWorkState ;
extern unsigned int  InjectionStepMotorStepPulseNum;
extern unsigned int InjectionStepMotorStepPulseMaxNum ;


extern void PositionCheckInit(void);
extern void NeedleFindZeroPosFun(void);
extern void CalContinueWorkTimePeriod(void);


#endif