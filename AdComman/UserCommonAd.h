#ifndef _USER_COMMON_AD_H
#define _USER_COMMON_AD_H

typedef unsigned int ADUint16;
typedef unsigned char ADUint8;

#define SHORT_ERROR_AD_VALUE               	0x03
#define OPEN_ERROR_AD_VALUE                 	0xfc

#define OK_STATE_CODE             		0x00 
#define SHORT_STATE_CODE          		0x01 
#define OPEN_STATE_CODE           		0x02  


#define AD_MAX_CHANNEL_NUM  10  

#define AD_BUFF_LENGTH 5  

typedef ADUint16 (*Fuction)();

typedef struct ADSensorType
{
	ADUint8  Channel;	
	ADUint16 Buff[AD_BUFF_LENGTH];

	ADUint16 HexAverage;      			
	signed int DisplayValue;   		 
	ADUint8  ErrState;
	
	ADUint16 (*GetHexAverage)(struct ADSensorType *pAddr);
	ADUint16 (*GetHexMax)(struct ADSensorType *pAddr);
	ADUint16 (*GetHexMin)(struct ADSensorType *pAddr);
	void (*CalDisplay)(struct ADSensorType *pAddr,ADUint16 data);
	signed int (*GetDisplayValue)(struct ADSensorType *pAddr);
	ADUint8  (*GetErrState)(struct ADSensorType *pAddr);
	void (*Translate)(struct ADSensorType *pAddr);
	
}ADSensorType;

extern ADUint8 JudgeBuffEmpty(const ADSensorType *pAddr);
extern ADUint8 JudgeBuffFull(const ADSensorType *pAddr);
extern void CleanBuff( ADSensorType *pAddr);
extern void AddDataToBuff(ADSensorType *pAddr,ADUint16 data);
extern ADUint16 ReadDataFromBuff(ADSensorType *pAddr);
extern ADUint16 GetHexMax(ADSensorType *pAddr);
extern ADUint16 GetHexMin(ADSensorType *pAddr);
extern ADUint16 GetHexAverage(ADSensorType *pAddr);
extern void Translate(ADSensorType *pAddr);

#endif 
