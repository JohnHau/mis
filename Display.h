#ifndef DISPLAY_H
#define DISPLAY_H

extern unsigned char DisplayTaskTime;

extern void DisplayTask(void);

#define DISPLAY_TASK_PERIOD  100  //100ms

#define INJECT_MODE_DISPLAY_X   1  		//注射模式X坐标位置
#define INJECT_MODE_DISPLAY_Y   1  		//注射模式Y坐标位置

#define DUMP_ENERGY_DISPLAY_X   87  		//剩余电量X坐标位置
#define DUMP_ENERGY_DISPLAY_Y   2  		//剩余电量Y坐标位置

#define INJECT_TYPE_DISPLAY_X   	25  	//注射器类型 X坐标位置
#define INJECT_TYPE_DISPLAY_Y   	71  	//注射器类型 Y坐标位置

#define NEEDLE_LENGTH_DISPLAY_X   	25  	//针头长度 X坐标位置
#define NEEDLE_LENGTH_DISPLAY_Y   	39  	//针头长度 Y坐标位置

#define INJECT_DEPTH_DISPLAY_X   	87  	//注射深度 X坐标位置
#define INJECT_DEPTH_DISPLAY_Y   	39  	//注射深度 Y坐标位置

#define VARIABLE_DISPLAY_X   		88  	//变量 X坐标位置
#define VARIABLE_DISPLAY_Y   		71  	//变量 Y坐标位置

#endif