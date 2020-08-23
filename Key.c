
#include <p18cxxx.h>

#include "Key.h"
#include "PositionControl.h"

KeyType OnOffKey={0},UpKey={0},DownKey={0},ConfirmKey={0},StartInjectKey={0};

unsigned char KeyScanPeriod =0;

//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
	DDRBbits.RB4 	=1;  	
	DDRDbits.RD4  	=1;			
	DDRDbits.RD7  	=1;			
	DDRBbits.RB3  	=1;			
	DDRBbits.RB5  	=1;			
	
	OnOffKey.NewValue =1;
	OnOffKey.OldValue =1;
	OnOffKey.SendValue =1;
	OnOffKey.SendValueChangeFlag =0;
	OnOffKey.FiterTimes =3;
	OnOffKey.FiterTimesCount =OnOffKey.FiterTimes;
	
	UpKey.NewValue =1;
	UpKey.OldValue =1;
	UpKey.SendValue =1;
	UpKey.SendValueChangeFlag =0;
	UpKey.FiterTimes =3;
	UpKey.FiterTimesCount =UpKey.FiterTimes;
	
	DownKey.NewValue =1;
	DownKey.OldValue =1;
	DownKey.SendValue =1;
	DownKey.SendValueChangeFlag =0;
	DownKey.FiterTimes =3;
	DownKey.FiterTimesCount =DownKey.FiterTimes;

	ConfirmKey.NewValue =1;
	ConfirmKey.OldValue =1;
	ConfirmKey.SendValue =1;
	ConfirmKey.SendValueChangeFlag =0;
	ConfirmKey.FiterTimes =3;
	ConfirmKey.FiterTimesCount =ConfirmKey.FiterTimes;

	StartInjectKey.NewValue =1;
	StartInjectKey.OldValue =1;
	StartInjectKey.SendValue =1;
	StartInjectKey.SendValueChangeFlag =0;
	StartInjectKey.FiterTimes =3;
	StartInjectKey.FiterTimesCount =StartInjectKey.FiterTimes;
}

void KEY_Scan(void)
{	
	if(!KeyScanPeriod)
	{
		KeyScanPeriod =KEY_SCAN_PERIOD_CONST;	

			if(OnOffKey.NewValue !=ON_OFF_BUTTON_PIN)
			{
				OnOffKey.FiterTimesCount =OnOffKey.FiterTimes;
				OnOffKey.NewValue =ON_OFF_BUTTON_PIN;
			}
			else
			{
					if(OnOffKey.NewValue ==ON_OFF_BUTTON_PIN)
					{
						if(OnOffKey.FiterTimesCount)//ȥ����������δ��
						{
							OnOffKey.FiterTimesCount--;
						}
						else//ȥ������������
						{
							OnOffKey.OldValue =OnOffKey.NewValue;
						}
					}
					if(OnOffKey.OldValue!=OnOffKey.SendValue)
					{
						OnOffKey.SendValue=OnOffKey.OldValue;
						OnOffKey.SendValueChangeFlag =1;
					}
					else
					{

					}
				}
		/////TM003_RESET
			if(UpKey.NewValue !=UP_BUTTON_PIN)
			{
				UpKey.FiterTimesCount =UpKey.FiterTimes;
				UpKey.NewValue =UP_BUTTON_PIN;
			}
			else
			{
					if(UpKey.NewValue ==UP_BUTTON_PIN)
					{
						if(UpKey.FiterTimesCount)//ȥ����������δ��
						{
							UpKey.FiterTimesCount--;
						}
						else//ȥ������������
						{
							UpKey.OldValue =UpKey.NewValue;
						}
					}
					if(UpKey.OldValue!=UpKey.SendValue)
					{
						UpKey.SendValue=UpKey.OldValue;
						UpKey.SendValueChangeFlag =1;
					}
					else
					{

					}
			}
		/////
			if(DownKey.NewValue !=DOWN_BUTTON_PIN)
			{
				DownKey.FiterTimesCount =DownKey.FiterTimes;
				DownKey.NewValue =DOWN_BUTTON_PIN;
			}
			else
			{
					if(DownKey.NewValue ==DOWN_BUTTON_PIN)
					{
						if(DownKey.FiterTimesCount)//ȥ����������δ��
						{
							DownKey.FiterTimesCount--;
						}
						else//ȥ������������
						{
							DownKey.OldValue =DownKey.NewValue;
						}
					}
					if(DownKey.OldValue!=DownKey.SendValue)
					{
						DownKey.SendValue=DownKey.OldValue;
						DownKey.SendValueChangeFlag =1;
					}
					else
					{

					}
				}	



		//CleanKey.NewValue= TM003_RESET;
			if(ConfirmKey.NewValue !=COMFIRM_BUTTON_PIN)
			{
				ConfirmKey.FiterTimesCount =ConfirmKey.FiterTimes;
				ConfirmKey.NewValue =COMFIRM_BUTTON_PIN;
			}
			else
			{
					if(ConfirmKey.NewValue ==COMFIRM_BUTTON_PIN)
					{
						if(ConfirmKey.FiterTimesCount)//ȥ����������δ��
						{
							ConfirmKey.FiterTimesCount--;
						}
						else//ȥ������������
						{
							ConfirmKey.OldValue =ConfirmKey.NewValue;
						}
					}
					if(ConfirmKey.OldValue!=ConfirmKey.SendValue)
					{
						ConfirmKey.SendValue=ConfirmKey.OldValue;
						ConfirmKey.SendValueChangeFlag =1;
					}
					else
					{

					}
				}

		//CleanKey.NewValue= TM003_RESET;
			if(StartInjectKey.NewValue !=START_WORK_BUTTON_PIN)
			{
				StartInjectKey.FiterTimesCount =StartInjectKey.FiterTimes;
				StartInjectKey.NewValue =START_WORK_BUTTON_PIN;
			}
			else
			{
					if(StartInjectKey.NewValue ==START_WORK_BUTTON_PIN)
					{
						if(StartInjectKey.FiterTimesCount)//ȥ����������δ��
						{
							StartInjectKey.FiterTimesCount--;
						}
						else//ȥ������������
						{
							StartInjectKey.OldValue =StartInjectKey.NewValue;
						}
					}
					if(StartInjectKey.OldValue!=StartInjectKey.SendValue)
					{
						StartInjectKey.SendValue=StartInjectKey.OldValue;
						StartInjectKey.SendValueChangeFlag =1;
					}
					else
					{

					}
				}
			
			}

			if(StartInjectKey.OldValue ==0)
			{
				StartWorkFlag =1;			
			}
			else
			{
				StartWorkFlag =0;				
			}
}
void KeyFuction(void)
{
	static unsigned char store_key =0;
	if(OnOffKey.SendValueChangeFlag && (OnOffKey.SendValue==0))//����������,�л���������� ʵʱ��ʾ����
	{
		OnOffKey.SendValueChangeFlag =0;
		OnOffKey.FiterTimes=OnOffKey.FiterTimes;
		
		//OnOffKey.NewValue=1;
		//OnOffKey.OldValue =1;
		OnOffKey.SendValue =1;
		OnOffKey.SendValueChangeFlag =0;
	}
	else
	{

	}

	if(UpKey.SendValueChangeFlag && (UpKey.SendValue==0))//����������,�л���������� ʵʱ��ʾ����
	{
		UpKey.SendValueChangeFlag =0;
		UpKey.FiterTimes=OnOffKey.FiterTimes;
		
		//UpKey.NewValue=1;
		//UpKey.OldValue =1;
		UpKey.SendValue =1;
		UpKey.SendValueChangeFlag =0;
	}
	else
	{

	}

	if(DownKey.SendValueChangeFlag && (DownKey.SendValue==0))//����������,�л���������� ʵʱ��ʾ����
	{
		DownKey.SendValueChangeFlag =0;
		DownKey.FiterTimes=DownKey.FiterTimes;
		
		//DownKey.NewValue=1;
		//DownKey.OldValue =1;
		DownKey.SendValue =1;
		DownKey.SendValueChangeFlag =0;
	}
	else
	{

	}

	if(ConfirmKey.SendValueChangeFlag && (ConfirmKey.SendValue==0))//����������,�л���������� ʵʱ��ʾ����
	{
		ConfirmKey.SendValueChangeFlag =0;
		ConfirmKey.FiterTimes=ConfirmKey.FiterTimes;
		
		//ConfirmKey.NewValue=1;
		//ConfirmKey.OldValue =1;
		ConfirmKey.SendValue =1;
		ConfirmKey.SendValueChangeFlag =0;
	}
	else
	{

	}

	if(StartInjectKey.SendValueChangeFlag && (StartInjectKey.SendValue==0))//����������,�л���������� ʵʱ��ʾ����
	{
		StartInjectKey.SendValueChangeFlag =0;
		StartInjectKey.FiterTimes=StartInjectKey.FiterTimes;
		
		//StartInjectKey.NewValue=1;
		//StartInjectKey.OldValue =1;
		StartInjectKey.SendValue =1;
		StartInjectKey.SendValueChangeFlag =0;
	}
	else
	{

	}
}