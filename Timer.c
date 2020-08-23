//#include <p18cxxx.h>
//#include<pic18.h>  
#include <xc.h>
#include "Timer.h"
//#include "Ad.h"
#include "Key.h"
#include "PositionControl.h"
#include "Beep.h"
#include"MotorDrive.h"

unsigned char LastNeedleFeedback =0;
unsigned char LastInjectionFeedback =0;
unsigned char flag =0;


//void __interrupt(high_priority) ISR(void)
void __interrupt(high_priority) ISR(void)
{
  //1ms定时中断
  unsigned char i =0;

  if(T0IE && T0IF) // 说明127us定时时间到了
  {
#if 0
	if(AdSampleTaskTime)
	{
		AdSampleTaskTime--;
	}
#endif
	if(KeyScanPeriod)
	{
		KeyScanPeriod--;
	}
//位置检测
    i =NEEDLE_MOTOR_FEEDBACK2;
    if(LastNeedleFeedback != i)
	{
		if(NeedleRunDir)//fan
		{
			NeedleMotorCurrentPosition--;		
		}
		else
		{
			NeedleMotorCurrentPosition++;		
		}
		LastNeedleFeedback = i;
	}

    i =INJECTION_MOTOR_FEEDBACK2;
    if(LastInjectionFeedback != i)
	{
		InjectionMotorCurrentPosition++;
		LastInjectionFeedback = i;
	}

	//工作状态	
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
					if(ContinueWorkTimeCount)
					{
						ContinueWorkTimeCount--;					
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
			if(NEEDLE_MOTOR_LI_POS_PIN ==0 )//碰触到限位开关	
			{
				//if(flag ==0)
				{
					//GIE=0;  // 放在主程序需要 总中断关
					NeedleMotorCurrentPosition =0;
					flag =1;
					//GIE=1;  // 放在主程序需要 总中断开
					//NeedleMotorForwardRun();//减少中断中重复调用函数以下为函数展开			
					CLEAR_L298N_INPUT3_PIN;    			
					SET_L298N_INPUT4_PIN;  			 
					SET_L298N_B_ENABLE_PIN;

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
	
				}
	
			}
			else
			{
				if(flag ==1)
				{
					if((NeedleMotorCurrentPosition > NeedleMotorAimPosition)|| (NeedleMotorCurrentPosition == NeedleMotorAimPosition))
					{
						//NeedleMotorFastStop();//减少中断中重复调用函数以下为函数展开
						SET_L298N_INPUT3_PIN; 			
						SET_L298N_INPUT4_PIN;  			
						SET_L298N_B_ENABLE_PIN;  		
						NeedleMotorFindZeroPosFlag =1;//清空初始化标志
						flag =0;
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
    T0IF=0; // 清空标志位，使CPU能正确响应下次中断
} 

void TimerInit(void)
{
	T0CS=0; // 选择CLKOUT信号为时钟源
	PSA=0; // 预分频器给TIMER0用
	T0PS2=0;
	T0PS1=0;
	T0PS0=0; // 分频比为1:8。FOSC/4/2=2
	T08BIT =1;//配置为8位模式 0.5us*255 =127us  
	T0IF=0; // Timer0中断标志位清空  
	T0IE=1; // Timer0中断使能位置位，允许Timer0中断
	GIE=1;  // 总中断打开
	TMR0=0; // Timer0计数值寄存器清零  
}