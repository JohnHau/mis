#include <xc.h>
//#include <p18cxxx.h>

#include "Key.h"
//#include "PositionControl.h"

KeyType OnOffKey={0},UpKey={0},DownKey={0},ConfirmKey={0},StartInjectKey={0};

unsigned char KeyScanPeriod =0;

#if 1
void KEY_Init(void) //
{ 
   
#if 1
    //LATB = 0;
   // PORTB = 0;
   // ADCON1 = 0x07;
    
    //ADCON0 = 0x00;
   // ADCON1 = 0x0f;

    TRISBbits.RB3 =1;//KEY_V
    TRISBbits.RB4 =1;//KEY_WAKE
    
    
    
    TRISBbits.RB5 =1;//ACTION_BUTTON
    
    TRISDbits.RD6 =1;//KEY_UP
    TRISDbits.RD7 =1;//KEY_DOWN
    
    TRISBbits.RB0 =1;//LP_BUTTON

    
    TRISAbits.RA3 =1;//STATUS_CHARGE
    //TRISB = 0xff;
    
#endif
    
    
#if 0
    //RCONbits.IPEN = 1;
    
    INTCON2bits.INTEDG0 =0;//falling edge
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0E = 1;//int0 enabled
     
     
    //TRISB = 0xff;
    INTCONbits.RBIE =1;
    INTCONbits.PEIE =1;
    INTCONbits.GIE =1;
    
#endif
    
    
    

    
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
}

void KEY_Scan(void)
{


#if 0	
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
						if(OnOffKey.FiterTimesCount)//去除抖动次数未到
						{
							OnOffKey.FiterTimesCount--;
						}
						else//去除抖动次数到
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
						if(UpKey.FiterTimesCount)//去除抖动次数未到
						{
							UpKey.FiterTimesCount--;
						}
						else//去除抖动次数到
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
						if(DownKey.FiterTimesCount)//去除抖动次数未到
						{
							DownKey.FiterTimesCount--;
						}
						else//去除抖动次数到
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
						if(ConfirmKey.FiterTimesCount)//去除抖动次数未到
						{
							ConfirmKey.FiterTimesCount--;
						}
						else//去除抖动次数到
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
						if(StartInjectKey.FiterTimesCount)//去除抖动次数未到
						{
							StartInjectKey.FiterTimesCount--;
						}
						else//去除抖动次数到
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
    
    
#endif
}
void KeyFuction(void)
{
    
#if 0
	static unsigned char store_key =0;
	if(OnOffKey.SendValueChangeFlag && (OnOffKey.SendValue==0))//按键被按下,切换到最初界面 实时显示数据
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

	if(UpKey.SendValueChangeFlag && (UpKey.SendValue==0))//按键被按下,切换到最初界面 实时显示数据
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

	if(DownKey.SendValueChangeFlag && (DownKey.SendValue==0))//按键被按下,切换到最初界面 实时显示数据
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

	if(ConfirmKey.SendValueChangeFlag && (ConfirmKey.SendValue==0))//按键被按下,切换到最初界面 实时显示数据
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

	if(StartInjectKey.SendValueChangeFlag && (StartInjectKey.SendValue==0))//按键被按下,切换到最初界面 实时显示数据
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
#endif
}


#endif