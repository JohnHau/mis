#include <p18cxxx.h>
#include <xc.h>
#include "PositionControl.h"

volatile unsigned int InjectionMotorCurrentPosition =0,InjectionMotorAimPosition =0;	//注射电机位置
volatile int NeedleMotorCurrentPosition =0,NeedleMotorAimPosition =0;		//注射出针电机位置
volatile unsigned int NeedleInitPosition =0;		//注射出针电机位置

unsigned int InjectDepthNeedPulseNum=0;//针注射深度需要脉冲数
unsigned int InjectAmountNeedPulseNum=0;//单次注射量需要脉冲数

unsigned char NeedleMotorFindZeroPosFlag =0;//0:进行找零  1:已经找过原点位置 ON->OFF清零 改变针深度重新找零

unsigned int  ContinueWorkTimePeriod =0;
unsigned int  ContinueWorkTimeCount =0;
unsigned char NeedleRunDir =0;//0 正 1反向
unsigned char StartWorkFlag =0,ContinueWorkState =0;
unsigned int  InjectionStepMotorStepPulseNum =0;
unsigned int InjectionStepMotorStepPulseMaxNum =0;
WorkParaType CurrentWorkPara;


#if 0
void NeedleFindZeroPosFun(void)
{
	static unsigned char flag =0;//初始化阶段 0：反向运行到限位 1：正向运行到目标位置
	//初始化
	if(!NeedleMotorFindZeroPosFlag)//初始化电机运行
	{
		if(NEEDLE_MOTOR_LI_POS_PIN ==0)//碰触到限位开关	
		{
			if(CurrentWorkPara.NeedleLength ==4)
			{
				NeedleInitPosition =NEEDLE_LENGTH_4MM_ZERO_PULSE_NUM;
				NeedleMotorAimPosition =NeedleInitPosition;
			}
			else if(CurrentWorkPara.NeedleLength ==6)
			{
				NeedleInitPosition =NEEDLE_LENGTH_6MM_ZERO_PULSE_NUM;
				NeedleMotorAimPosition =NeedleInitPosition;
			}
			else if(CurrentWorkPara.NeedleLength ==13)
			{
				NeedleInitPosition =NEEDLE_LENGTH_13MM_ZERO_PULSE_NUM;
				NeedleMotorAimPosition =NeedleInitPosition;
			}
			else
			{
				NeedleInitPosition =NEEDLE_LENGTH_13MM_ZERO_PULSE_NUM;
				NeedleMotorAimPosition =NeedleInitPosition;
			}
			if(flag ==0)
			{
				//GIE=0;  // 放在主程序需要 总中断关
				NeedleMotorCurrentPosition =0;
				flag =1;
				//GIE=1;  // 放在主程序需要 总中断开
				//NeedleMotorForwardRun();//减少中断中重复调用函数以下为函数展开			
				CLEAR_L298N_INPUT3_PIN;    			
				SET_L298N_INPUT4_PIN;  			 
				SET_L298N_B_ENABLE_PIN;  		 

			}
			else
			{
				if(NeedleMotorCurrentPosition > NeedleMotorAimPosition)|| (NeedleMotorCurrentPosition == NeedleMotorAimPosition)
				{
					//NeedleMotorFastStop();//减少中断中重复调用函数以下为函数展开
					SET_L298N_INPUT3_PIN; 			
					SET_L298N_INPUT4_PIN;  			
					SET_L298N_B_ENABLE_PIN;  		
					NeedleMotorFindZeroPosFlag =0;//清空初始化标志
				}
			}

		}
		else
		{
			//NeedleMotorReverseRun();////减少中断中重复调用函数以下为函数展开
			SET_L298N_INPUT3_PIN; 			  			
			CLEAR_L298N_INPUT4_PIN; 
			SET_L298N_B_ENABLE_PIN;  		

			flag =0;
		}	
	}
}
#endif


//每分钟最少8次否则会出错
void CalContinueWorkTimePeriod(void)
{
	//根据1分钟连续注射多少次计算  计算结果定时器中断个数 127us倍数
	//60 000 000(us)/127(us)/CurrentWorkPara.Variable; 
	ContinueWorkTimePeriod =472441/CurrentWorkPara.Variable; 
}

//计算连续工作模式注液电机单次前进量
void CalContinueWorkModeInjectionStepPulseAndMaxPuse(void)
{
	if(INJECTION_1_ML_TYPE==CurrentWorkPara.InjectType)
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_1_ML_LENGTH;
		InjectionStepMotorStepPulseNum =500;//根据需要填写计算公式
	}
	else if(INJECTION_2_ML_TYPE==CurrentWorkPara.InjectType)
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_2_ML_LENGTH;
		InjectionStepMotorStepPulseNum =70;//根据需要填写计算公式	
	}
	else if(INJECTION_2_5_ML_TYPE==CurrentWorkPara.InjectType)
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_2_5_ML_LENGTH;
		InjectionStepMotorStepPulseNum =70;//根据需要填写计算公式	
	}
	else if(INJECTION_5_ML_TYPE==CurrentWorkPara.InjectType)
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_5_ML_LENGTH;
		InjectionStepMotorStepPulseNum =70;//根据需要填写计算公式	
	}
	else if(INJECTION_10_ML_TYPE==CurrentWorkPara.InjectType)
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_10_ML_LENGTH;
		InjectionStepMotorStepPulseNum =70;//根据需要填写计算公式	
	}
	else
	{
		InjectionStepMotorStepPulseMaxNum =	INJECTION_1_ML_LENGTH;
		InjectionStepMotorStepPulseNum =70;//根据需要填写计算公式
	}
}
//连续模式中57位目前设定定制，具体根据实际情况可添加专用函数计算连续模式下单次步进量
#if 0
void ContinueMode(void)
{
	static unsigned char flag =0;//初始化阶段 0：反向运行到限位 1：正向运行到目标位置
	if(StartWorkFlag ==1)//启动工作状态
	{
		switch(CurrentWorkPara.InjectMode)
		{
			case CONTINUE_WORK_MODE:
					if(ContinueWorkState ==0)//连续工作第一步 正向出针
					{
						NeedleRunDir =0;
						//NeedleMotorForwardRun();			
						CLEAR_L298N_INPUT3_PIN;    			
						SET_L298N_INPUT4_PIN;  			
						SET_L298N_B_ENABLE_PIN;  		
						if((NeedleMotorCurrentPosition > NeedleMotorAimPosition) ||(NeedleMotorCurrentPosition == NeedleMotorAimPosition))
						{
							//NeedleMotorFastStop();
							SET_L298N_INPUT3_PIN; 			
							SET_L298N_INPUT4_PIN;  			
							SET_L298N_B_ENABLE_PIN;  		

							ContinueWorkState =1;
						}
					}
					else if(ContinueWorkState == 1)
					{
						//InjectionMotorForwardRun();
						SET_L298N_INPUT1_PIN;
						CLEAR_L298N_INPUT2_PIN;
						SET_L298N_A_ENABLE_PIN;
 
						if((InjectionMotorCurrentPosition > InjectionMotorAimPosition)||(InjectionMotorCurrentPosition == InjectionMotorAimPosition))
						{
							//InjectionMotorFastStop();
							SET_L298N_INPUT1_PIN;
							SET_L298N_INPUT2_PIN;
							SET_L298N_A_ENABLE_PIN;
  
							ContinueWorkState =2;
						}
					}
					else if(ContinueWorkState == 2)
					{
						NeedleRunDir =1;
				
						if((NeedleMotorCurrentPosition <  NeedleInitPosition)||(NeedleMotorCurrentPosition ==  NeedleInitPosition))
						{
							//NeedleMotorFastStop();
							SET_L298N_INPUT3_PIN; 			
							SET_L298N_INPUT4_PIN;  			
							SET_L298N_B_ENABLE_PIN;  		
 
							ContinueWorkState =3;
						}
						else
						{
							//NeedleMotorReverseRun();	
							SET_L298N_INPUT3_PIN; 			 			
							CLEAR_L298N_INPUT4_PIN; 
							SET_L298N_B_ENABLE_PIN;  		
		
						}			
					}
					else if(ContinueWorkState ==3)
					{
						ContinueWorkState =3;
						if(!ContinueWorkTimeCount)//单次运行时间到
						{
							ContinueWorkTimeCount =ContinueWorkTimePeriod;
							ContinueWorkState =0;
							InjectionMotorAimPosition =InjectionMotorCurrentPosition + InjectionStepMotorStepPulseNum;//
						}
					}
					else
					{
				
					}			
			break;	

			case MICROSCALE_WORK_MODE:
		
			break;
	
			default:

			break;
	
		}
	}
	else  //未按下启动按钮
	{
		//初始化
		if(!NeedleMotorFindZeroPosFlag)//初始化电机运行
		{
			if(NEEDLE_MOTOR_LI_POS_PIN ==0)//碰触到限位开关	
			{
				if(CurrentWorkPara.NeedleLength ==4)
				{
					NeedleInitPosition =NEEDLE_LENGTH_4MM_ZERO_PULSE_NUM;
					NeedleMotorAimPosition =NeedleInitPosition;
				}
				else if(CurrentWorkPara.NeedleLength ==6)
				{
					NeedleInitPosition =NEEDLE_LENGTH_6MM_ZERO_PULSE_NUM;
					NeedleMotorAimPosition =NeedleInitPosition;
				}
				else if(CurrentWorkPara.NeedleLength ==13)
				{
					NeedleInitPosition =NEEDLE_LENGTH_13MM_ZERO_PULSE_NUM;
					NeedleMotorAimPosition =NeedleInitPosition;
				}
				else
				{
					NeedleInitPosition =NEEDLE_LENGTH_13MM_ZERO_PULSE_NUM;
					NeedleMotorAimPosition =NeedleInitPosition;
				}
				if(flag ==0)
				{
					//GIE=0;  // 放在主程序需要 总中断关
					NeedleMotorCurrentPosition =0;
					flag =1;
					//GIE=1;  // 放在主程序需要 总中断开
					//NeedleMotorForwardRun();//减少中断中重复调用函数以下为函数展开			
					CLEAR_L298N_INPUT3_PIN;    			
					SET_L298N_INPUT4_PIN;  			 
					SET_L298N_B_ENABLE_PIN;  		 
	
				}
				else
				{
					if(NeedleMotorCurrentPosition > NeedleMotorAimPosition)|| (NeedleMotorCurrentPosition == NeedleMotorAimPosition)
					{
						//NeedleMotorFastStop();//减少中断中重复调用函数以下为函数展开
						SET_L298N_INPUT3_PIN; 			
						SET_L298N_INPUT4_PIN;  			
						SET_L298N_B_ENABLE_PIN;  		
						NeedleMotorFindZeroPosFlag =0;//清空初始化标志
					}
				}
	
			}
			else
			{
				//NeedleMotorReverseRun();////减少中断中重复调用函数以下为函数展开
				SET_L298N_INPUT3_PIN; 			  			
				CLEAR_L298N_INPUT4_PIN; 
				SET_L298N_B_ENABLE_PIN;  		
	
				flag =0;
			}	
		}
		else
		{
			//NeedleMotorFastStop();
			SET_L298N_INPUT3_PIN; 			
			SET_L298N_INPUT4_PIN;  			
			SET_L298N_B_ENABLE_PIN;
			//InjectionMotorFastStop();
			SET_L298N_INPUT1_PIN;
			SET_L298N_INPUT2_PIN;
			SET_L298N_A_ENABLE_PIN; 		
		}
 
	}
}
#endif
void InJectionOnceRunPulseCal(void)
{
	
}
void NeedleOnceRunPulseCal(void)
{
	
}

void MotorRunControl(void)
{

}
void PositionCheckInit(void)
{
	DDRCbits.RC0  =1;	//Needle
	DDRBbits.RB2  =1;	//

	DDRAbits.RA4  =1;	//Injection
	DDRDbits.RD1  =1;	//

	InjectionMotorCurrentPosition =0;
	InjectionMotorAimPosition =0;
	NeedleMotorCurrentPosition =0;
	NeedleInitPosition =0;		//注射出针电机位置
	NeedleMotorAimPosition =0 + NeedleInitPosition;		//注射出针电机位置
	
	CurrentWorkPara.InjectMode =CONTINUE_WORK_MODE;
	CurrentWorkPara.InjectType =INJECTION_1_ML_TYPE;
	CurrentWorkPara.NeedleLength =INJECTION_LENGTH_4MM;
	CurrentWorkPara.InjectDepth =1;//1MM
	CurrentWorkPara.Variable =100;

	CalContinueWorkTimePeriod();
	CalContinueWorkModeInjectionStepPulseAndMaxPuse();

}