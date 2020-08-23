#include "usr_Prototype.h"
#include "UserCommonAd.h"
#include "ADTaskConfig.h"

#include "NtcSensorMidLayer.h"
#include "ActuatorSensorMidLayer.h"

uint8_t Timer_AdTask_Id=0;
////1ms///
void ADTask(void)
{
	static uint8_t index =0;
	unsigned int data =0;
	ADSensorType *pAddr=(void*)0;
	static uint8_t count_5ms =0;
	
	ActuatorSensorSampleTask(&LeftMixActuatorSensor);
	ActuatorSensorSampleTask(&RightMixActuatorSensor);
	ActuatorSensorSampleTask(&ValveActuatorSensor);
	ActuatorSensorSampleTask(&BlowerActuatorSensor);
	if(!PeriodSoftTimerArray[Timer_AdTask_Id].TimerCount)
	{
		PeriodSoftTimerArray[Timer_AdTask_Id].TimerCount = Timer_AdTaskPeriod;	
		index++;
		//Ntc every 5ms sample
		count_5ms++;
		if(count_5ms==5)
		{
			count_5ms =0;
		}
		switch(count_5ms)
		{
			case 0:
				//Set4051Channel(4);
				//NtcSensorSampleTask(&EvapSensor);			 
				break;
			case 1:
				//Set4051Channel(3);
				//NtcSensorSampleTask(&CarOutTSensor);			
				break;
			case 2:
				//Set4051Channel(0);
				//NtcSensorSampleTask(&CarInTSensor);		
				break;
			case 3:
				//Set4051Channel(4);
				//NtcSensorSampleTask(&EvapSensor);			
				break;
			case 4:
				//Set4051Channel(4);
				//NtcSensorSampleTask(&EvapSensor);		
				break;			
			default:
			
				break;
		}
	}
}
void ADTaskInit(void)
{
	NtcSensorInit();
	ActuatorSensorInit();

	Timer_AdTask_Id =CreatPeriodSoftTimer();
	if(Timer_AdTask_Id ==CREAT_FAIL)
	{

	}	
}
