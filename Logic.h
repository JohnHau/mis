#ifndef LOGIC_H
#define LOGIC_H

typedef struct 
{
	unsigned char InjectMode;//注射模式
    unsigned char InjectType;//注射器类型
	unsigned char NeedleLength;//针头长度
	unsigned char InjectDepth;//针头长度
	unsigned char Variable;//每种参数下对应含义不同 注射量、或注射频率
}WorkParaType;

extern WorkParaType CurrentWorkPara;


#endif