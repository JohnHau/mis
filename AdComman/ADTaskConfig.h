#ifndef AD_TASK_CONFIG_H 
#define AD_TASK_CONFIG_H 

#define COMAND_AD_0             					_00_AD_INPUT_CHANNEL_0  
#define VALVE_SENSOR_AD_CHANNEL                         		_01_AD_INPUT_CHANNEL_1
#define RIGHT_MIX_MOTOR_SENSOR_AD_CHANNEL                         	_05_AD_INPUT_CHANNEL_5
#define LEFT_MIX_MOTOR_SENSOR_AD_CHANNEL                        	 _02_AD_INPUT_CHANNEL_2
#define BLOWER_MOTOR_SENSOR_AD_CHANNEL                        		 _07_AD_INPUT_CHANNEL_7

#define Timer_AdTaskPeriod 2

//#define AD_RESUTLT_BIT_N_8  8   //MCU配置为xxx位AD转换结果
#define AD_RESUTLT_BIT_N_10  10   //MCU配置为xxx位AD转换结果
//#define AD_RESUTLT_BIT_N_12  12   //MCU配置为xxx位AD转换结果

extern void ADTaskInit(void);
extern void ADTask(void);

#endif
