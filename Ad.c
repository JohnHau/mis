#include <p18cxxx.h>
#include "Ad.h"

unsigned char AdSampleTaskTime =0;

unsigned int InjectionMotorAdAverageValue =0;//注射电机Ad平均值
unsigned int NeedleMotorAdAverageValue =0;
unsigned int BatteryVoltAdAverageValue =0;

unsigned int InJectionCrrentAdArray[ARRAY_LENGTH]={0,0,0,0,0};//注射电机电流Ad值
unsigned int NeedleCrrentAdArray[ARRAY_LENGTH]={0,0,0,0,0};//注射出针电机电流Ad值
unsigned int BatteryAdArray[ARRAY_LENGTH]={0,0,0,0,0};//电池电压Ad值

//volatile unsigned int BatteryVolt =0;//电池电压
unsigned int InjectionMotorCurrent =0;//注射电机电流
unsigned int NeedleMotorCurrent =0;//出针电机电流

void EnableAd(void)
{
	ADCON0 =ADCON0 | 0x01;
}

void CloseAd(void)
{
	ADCON0 =ADCON0 & 0xfe;
}

void SetAdChanel(unsigned char ch)
{
	ADCON0 =(ch <<2) | (ADCON0 & 0x3);
}

void StartAdConvert(void)
{
	ADCON0 =ADCON0 | 0x01;
}


unsigned int StartAndReadAdValue(unsigned char ch)
{
	unsigned int delay =1000;
	unsigned int value =0; 

	SetAdChanel(ch);
	StartAdConvert();
	while(delay-- && (ADCON0 & 0x2));
	
	value=((unsigned int)ADRESH <<2)|value; 
		
	return(value);	
}

//*pData 指向Ad值数组  *pPar返回值变量
void CalAdAverage(unsigned int *pData,unsigned int *pPar)
{
	unsigned char Index =0;
	unsigned long aver =0;
	unsigned long sum =0;
	
	for(Index = 0;Index <ARRAY_LENGTH ;Index++)
	{
		sum += *(pData + Index );
 	}		

	*pPar = (unsigned int)((unsigned long)sum/ARRAY_LENGTH);	
}

//value 需增加的新值  pData数据缓冲区

void AddDataToBuff(unsigned int *pData,unsigned int value)
{
	unsigned char Index =0;
	
	for(Index = ARRAY_LENGTH-1;Index > 0;Index--)
	{
		*(pData+Index) =*(pData+Index-1);
	}	
	*pData = value;
}

//配置为查询方式
void ADInit(void)
{
	unsigned char delay=100;

	ADCON0=0x01; /*选择RA0通道，AD 模块使能*/
  	ADCON1=0x0c; /*参考电压为系统VDD和GND，所有通道均为模拟输入*/ 
    ADCON2=0x09; /*转换结果左对齐，AD 采集时间=2TAD，系统时钟Fosc/8*/	
  	while(delay--); /*延时n个机器周期*/
    EnableAd();
}
void CalVoltValue(void)
{
	BatteryVolt =(unsigned long)VOLT_AD_1_TO_VOLT *BatteryVoltAdAverageValue/10;
}
void InJectionCrrentValue(void)
{
	InjectionMotorCurrent =(unsigned long)INJECTION_MOTOR_AD_1_TO_CURRENT *InjectionMotorAdAverageValue/10;
}

void NeedleCrrentValue(void)
{
	NeedleMotorCurrent =(unsigned long)NEEDLE_MOTOR_AD_1_TO_CURRENT *NeedleMotorAdAverageValue/10;
}

void AdSampleTask(void)
{
	static unsigned char counter =0;
	unsigned int value =0;
	if(!AdSampleTaskTime)
	{
		AdSampleTaskTime =AD_SAMPLE_PERIOD;
		switch(counter)
		{
			case 0:
					value = StartAndReadAdValue(INJECTION_MOTOR_CHANNEL);
					AddDataToBuff(&InJectionCrrentAdArray[0],value);
					CalAdAverage(&InJectionCrrentAdArray[0],&InjectionMotorAdAverageValue);
					InJectionCrrentValue();
					break;
			case 1:
					value = StartAndReadAdValue(NEEDLE_MOTOR_CHANNEL);
					AddDataToBuff(&NeedleCrrentAdArray[0],value);
					CalAdAverage(&NeedleCrrentAdArray[0],&NeedleMotorAdAverageValue);
					NeedleCrrentValue();
					break;
			case 2:
					value = StartAndReadAdValue(BAT_VOLT_CHANNEL);
					AddDataToBuff(&BatteryAdArray[0],value);
					CalAdAverage(&BatteryAdArray[0],&BatteryVoltAdAverageValue);
					CalVoltValue();
					break;
			case 3:
						
					break;
			default:

					break;
	
		}
		if(++counter > 4)
		{
			counter =0;
		}
	}
}




