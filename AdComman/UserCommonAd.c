#include "usr_Prototype.h"
#include "UserCommonAd.h"

void AddDataToBuff(ADSensorType *pAddr,ADUint16 data)
{
	ADUint8 Index =0;
	
	for(Index = AD_BUFF_LENGTH-1;Index > 0;Index--)
	{
		pAddr->Buff[Index] =pAddr->Buff[Index-1];
	}	
	pAddr->Buff[Index] = data;
}
ADUint16 GetHexMax(ADSensorType *pAddr)
{
	ADUint8 Index;
	ADUint16 Max = 0;

	for(Index = 0;Index < AD_BUFF_LENGTH;Index ++)
	{
		if(Max < pAddr->Buff[Index])
			Max = pAddr->Buff[Index];
	}		
	return (Max);
}

ADUint16 GetHexMin(ADSensorType *pAddr)
{
	ADUint8 Index;
	ADUint16 Min =0;
	for(Index = 0;Index < AD_BUFF_LENGTH;Index ++)
	{
		if(Min < pAddr->Buff[Index])
			Min = pAddr->Buff[Index];
	}		
	return (Min);
}

ADUint16 GetHexAverage(ADSensorType *pAddr)
{
	ADUint8 Index;
	unsigned long sum =0;
	ADUint8 i =0;
	
	for(Index = 0;Index <AD_BUFF_LENGTH ;Index++)
	{
		sum += pAddr->Buff[Index];
 	}		

	pAddr->HexAverage = (uint16_t)(sum/AD_BUFF_LENGTH);	
	return (pAddr->HexAverage);
}

void Translate(ADSensorType *pAddr)
{
	uint8_t delay =100;
	uint16_t value =0;
	
	SetAdChannel(pAddr->Channel);
	ADIF =0;
	NOP();
	R_ADC_Start();
	while(!ADIF)
	{
	 NOP();
	}
	R_ADC_Get_Result(&value);
	AddDataToBuff(pAddr,value);
}
