#include<xc.h> 
#include "Oled.h"	 
#include "Beep.h"
#include "Key.h"	

void delay_nms(uint32_t n)
{
    uint16_t i=0;
    while(n)
    {
    
        for(i=0;i<5000;i++)
            NOP();
        
        n--;
    }



}






void delay(unsigned int  x)
{
  	unsigned int  i,j;
    for(i=0;i<x;i++)
       for(j=0;j<10000;j++);
}

static void i2c_Delay(void)
{
	uint32_t i;
	//for (i = 0; i < 10; i++);
    
    
      	//unsigned int  i,j;
    //for(i=0;i<100;i++)
       //for(j=0;j<100;j++);
    
    
    
    
    
}

void i2c_Start(void)
{

	EEPROM_I2C_SDA_1();
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	EEPROM_I2C_SDA_0();
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();
}


void i2c_Stop(void)
{
	
	EEPROM_I2C_SDA_0();
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	EEPROM_I2C_SDA_1();
}


void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			EEPROM_I2C_SDA_1();
		}
		else
		{
			EEPROM_I2C_SDA_0();
		}
		i2c_Delay();
		EEPROM_I2C_SCL_1();
		i2c_Delay();	
		EEPROM_I2C_SCL_0();
		if (i == 7)
		{
			 EEPROM_I2C_SDA_1(); 
		}
		_ucByte <<= 1;	
		i2c_Delay();
	}
}


uint8_t i2c_ReadByte(void)
{
#if 0
	uint8_t i;
	uint8_t value;
    
    //DDRCbits.RC4 =1;//====================input mode
    TRISCbits.RC4 =1;
    
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		EEPROM_I2C_SCL_1();
		i2c_Delay();
		if (EEPROM_I2C_SDA_READ())
		{
			value++;
		}
        //DDRCbits.RC4 =0;//====================come back to output mode
		EEPROM_I2C_SCL_0();
		i2c_Delay();
	}
    // DDRCbits.RC4 =0;//====================come back to output mode
     TRISCbits.RC4 =1;
	return value;
#endif
}


uint8_t i2c_WaitAck(void)
{
	uint8_t re;

	EEPROM_I2C_SDA_1();	
	i2c_Delay();
	EEPROM_I2C_SCL_1();
   // DDRCbits.RC4 =1;//====================sda input mode
    
#if defined(ORIGINAL)
    TRISCbits.RC4 =1;//original
    
#elif defined(LTEMP)
    TRISCbits.RC3 =1;//temp
#endif
    
	i2c_Delay();
	if (EEPROM_I2C_SDA_READ())	
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
   
	EEPROM_I2C_SCL_0();
    // DDRCbits.RC4 =0;//====================come back to output mode

     #if defined(ORIGINAL)
    TRISCbits.RC4 =0;//original
    
    #elif defined(LTEMP)
        TRISCbits.RC3 =0;//temp
    #endif
     
     
     
	i2c_Delay();
    
	return re;
}


void i2c_Ack(void)
{
	EEPROM_I2C_SDA_0();	
	i2c_Delay();
	EEPROM_I2C_SCL_1();	
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();
	EEPROM_I2C_SDA_1();
}


void i2c_NAck(void)
{
	EEPROM_I2C_SDA_1();	
	i2c_Delay();
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();	
}


void i2c_CfgGpio(void)
{
    
    //PORTCbits.RC3 =1;//SCL
    //DDRCbits.RC3 =0;
    TRISCbits.RC3 =0;
    LATCbits.LC3 =0;
       
    
    //PORTCbits.RC4 =1;
    //DDRCbits.RC4 =0;//SDA
    TRISCbits.RC4 =0;
    LATCbits.LC4 =0;
    
   
    
     
    //PORTEbits.RE1 =1;
    //DDREbits.RE1 =0;//res
    TRISEbits.RE1 =0;
    //LATEbits.LE1 =1;
    // LATEbits.LATE1=1;
  //LATEbits.LATE1=0;
  LATEbits.LATE1=0;
  //delay(500);
  //delay(2);
    //PORTCbits.RC3 =1;//SCL
    //PORTCbits.RC4 =1;//SDA
    //i2c_Stop();
     
}



	   
void delay_ms(unsigned int ms)
{                         
	unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}
//================================================================================
//AD converter  Battery
//================================================================================



unsigned int StartAndReadAdValue(unsigned char ch)
{
#if 0
	unsigned int delay =1000;
	unsigned int value =0; 

	//SetAdChanel(ch);
	//StartAdConvert();
	while(delay-- && (ADCON0 & 0x2));
	
	value=((unsigned int)ADRESH <<2)|value; 
		
	return(value);	
#endif
}



uint8_t AD_ch0_init(void)
{
    
    TRISAbits.RA0 =1;//AD0
    TRISAbits.RA1 =1;//Motor sense A
    TRISAbits.RA2 =1;//Motor sense B
    
    
    ADCON0bits.CHS = 0;//choose channel 0
    ADCON0bits.ADON = 1;


    return 1;
}








uint16_t get_AD_vaule(void)
{
    
   uint8_t hv=0; 
   uint8_t lv=0; 
    uint8_t ts=0; 
   uint16_t rv=0;
   ADCON0bits.GO =1;
   while(ADCON0bits.GO);

   
   hv = ADRESH;
   lv = ADRESL;
   
   rv = ((uint16_t)(hv<<8 | lv) >>6)& 0x03ff;
   
   //ts = rv;
   return rv;




}




uint16_t get_SenseA_AD_vaule(void)
{
    
   uint8_t hv=0; 
   uint8_t lv=0; 
    uint8_t ts=0; 
   uint16_t rv=0;
    ADCON0bits.CHS = 1;//choose channel 1
   ADCON0bits.GO =1;
   while(ADCON0bits.GO);

   
   hv = ADRESH;
   lv = ADRESL;
   
   rv = ((uint16_t)(hv<<8 | lv) >>6)& 0x03ff;
   
   //ts = rv;
   return rv;




}



uint16_t get_SenseB_AD_vaule(void)
{
    
   uint8_t hv=0; 
   uint8_t lv=0; 
    uint8_t ts=0; 
   uint16_t rv=0;
    ADCON0bits.CHS = 2;//choose channel 1
   ADCON0bits.GO =1;
   while(ADCON0bits.GO);

   
   hv = ADRESH;
   lv = ADRESL;
   
   rv = ((uint16_t)(hv<<8 | lv) >>6)& 0x03ff;
   
   //ts = rv;
   return rv;




}










//=============================================================================================
//=============================================================================================


uint8_t ee_CheckDevice(uint8_t _Address)
{
    
#if 1
	uint8_t ucAck;
	
	i2c_Start();		

	
	i2c_SendByte(_Address | EEPROM_I2C_WR);
	ucAck = i2c_WaitAck();	

	i2c_Stop();			

	i2c_NAck();	
	
	return ucAck;
    
    
#endif
}



uint8_t ee_WaitStandby(void)
{
    
#if 0
	uint32_t wait_count = 0;
	
	while(ee_CheckDevice(EEPROM_DEV_ADDR))
	{
	
		if(wait_count++>0xFFFF)
		{
			return 1;
		}
	}
	return 0;
    
#endif
}


uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize)
{
    
#if 0
	uint16_t i;
	
	
	
	
	i2c_Start();
	
	
	i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_WR);	
	 
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	
	}

	
	i2c_SendByte((uint8_t)_usAddress);
	
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	
	}
	
	
	i2c_Start();
	
	
	i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_RD);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	
	}	
	
	
	for (i = 0; i < _usSize; i++)
	{
		_pReadBuf[i] = i2c_ReadByte();	
		
		
		if (i != _usSize - 1)
		{
			i2c_Ack();	
		}
		else
		{
			i2c_NAck();	
		}
	}
	
	i2c_Stop();
	return 1;	

cmd_fail: 
	i2c_Stop();
	return 0;
    
    
    
    
#endif
}

//uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize)
uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint8_t _usAddress, uint16_t _usSize)
{
	uint16_t i,m;
	//uint16_t usAddr;
    uint8_t usAddr;

	usAddr = _usAddress;	
	//for (i = 0; i < _usSize; i++)
	{
		//if ((i == 0) || (usAddr & (EEPROM_PAGE_SIZE - 1)) == 0)
		{
			//i2c_Stop();
			
			//for (m = 0; m < 1000; m++)
            //for (m = 0; m < 1; m++)
			{				
				i2c_Start();
				
				i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_WR);	
				
				if (i2c_WaitAck() == 0)
				{
                    
                    //buzz();
					//break;
				}
                else
                {
                     //buzz();
                }
			}
			if (m  == 1000)
			{
				//goto cmd_fail;	
			}
		
			i2c_SendByte(usAddr);
			
			if (i2c_WaitAck() != 0)
			{
                //buzz();
				//goto cmd_fail;	
			}
		}
	
		//i2c_SendByte(_pWriteBuf[i]);
	    i2c_SendByte(_pWriteBuf[0]);
		if (i2c_WaitAck() != 0)
		{
            //buzz();
			//goto cmd_fail;	
		}

		//usAddr++;
	}
	
	i2c_Stop();
	
	//if(ee_WaitStandby() == 1)
		//goto cmd_fail;
	
	return 1;

cmd_fail: 
	i2c_Stop();
   // buzz();
	return 0;
}





uint8_t write_buf[EEPROM_SIZE];
uint8_t read_buf[EEPROM_SIZE];

uint8_t ee_Test(void) 
{
    
    
#if 0
  uint16_t i;

  
/*-----------------------------------------------------------------------------------*/  
  if (ee_CheckDevice(EEPROM_DEV_ADDR) == 1)
	{
		
		//printf("没有检测到串行EEPROM!\r\n");
				
		return 0;
	}
/*------------------------------------------------------------------------------------*/  

	for (i = 0; i < EEPROM_SIZE; i++)
	{		
		write_buf[i] = i;
	}
/*------------------------------------------------------------------------------------*/  
  if (ee_WriteBytes(write_buf, 0, EEPROM_SIZE) == 0)
	{
		//printf("写eeprom出错！\r\n");
		return 0;
	}
	else
	{		
		//printf("写eeprom成功！\r\n");
	}  

/*-----------------------------------------------------------------------------------*/
  if (ee_ReadBytes(read_buf, 0, EEPROM_SIZE) == 0)
	{
		//printf("读eeprom出错！\r\n");
		return 0;
	}
	else
	{		
		//printf("读eeprom成功，数据如下：\r\n");
	}
/*-----------------------------------------------------------------------------------*/  
  for (i = 0; i < EEPROM_SIZE; i++)
	{
		if(read_buf[i] != write_buf[i])
		{
			//printf("0x%02X ", read_buf[i]);
			//printf("错误:EEPROM读出与写入的数据不一致");
			return 0;
		}
    //printf(" %02X", read_buf[i]);
		
		if ((i & 15) == 15)
		{
			//printf("\r\n");	
		}		
	}
  //printf("eeprom读写测试成功\r\n");
  return 1;
  
  
#endif
}







void LCD_backlight_init(void)
{
	//PORTBbits.RB1 =0;	//colse	
	//DDRBbits.RB1  =0;	//dir=out
    
    //PORTEbits.RE0 =0;
   // DDREbits.RE0 =0;
    TRISEbits.RE0 =0;
    LATEbits.LE0 =0;
    
    
}

void LCD_On(void)
{
	//PORTBbits.RB1 =1;	//colse	
    
     //PORTEbits.RE0 =1;
      LATEbits.LE0 =1;
     
     
     
}
void LCD_Off(void)
{
	//PORTBbits.RB1 =0;	//colse	
    //PORTEbits.RE0 =0;
    LATEbits.LE0 =0;
    
 
}

void LCD_Blink(void)
{
	//PORTBbits.RB1 =0;	//colse	
    //PORTEbits.RE0 =0;
       
     LATEbits.LE0 =1;
     delay(50);
     LATEbits.LE0 =0;
     //delay(50);
}


uint8_t setYX_LCD(uint8_t py,uint8_t px)
{


   write_buf[0]=0x80 + px;//X address
	ee_WriteBytes(write_buf, 0x00, 1);
    
   
    write_buf[0]=0x40 + py;//Y address
	ee_WriteBytes(write_buf, 0x00, 1);
    
    return 1;
   
    
    
    
    

}













uint8_t ms = 0x66;
uint8_t ss=0;
uint8_t css=0;
uint8_t rcnt=0;
uint8_t page=0;
uint16_t xtt=0;



const uint8_t blank_m[2][23]={
    0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
    0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01
};




const uint8_t c_m[2][23]= {
  
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x98, 0xb8, 0xb0, 0xb0, 0xb0, 0xb8, 0x9f, 
    0x8f, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,

    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x19, 0x1d, 0x0d, 0x0d, 0x0d, 0x1d, 0xf9, 
    0xf1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,

    
};





const uint8_t drops_m [2][23]={
    
0x80, 0x83, 0x8f, 0xbf, 0x8f, 0x83, 0x80, 0x80, 
0x80, 0x83, 0x8f, 0xbf, 0x8f, 0x83, 0x80, 0x80, 
0x80, 0x83, 0x8f, 0xbf, 0x8f, 0x83, 0x80,


   0xf1, 0xf9, 0xfd, 0xfd, 0xfd, 0xf9, 0xf1, 0x01, 
   0xf1, 0xf9, 0xfd, 0xfd, 0xfd, 0xf9, 0xf1, 0x01,
   0xf1, 0xf9, 0xfd, 0xfd, 0xfd, 0xf9, 0xf1,
 

  
};




const uint8_t drop_m[2][23] ={
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81,
    0x83, 0x86, 0x9d, 0xbd, 0x9d, 0x86, 0x83, 0x81, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    
    
    
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf1,
    0xf9, 0xcd, 0xb5, 0xb5, 0xb5, 0x6d, 0xf9, 0xf1, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,


};

//==============================================================================


const uint8_t mem_m [2][23]={
    0x9f, 0x9f, 0x90, 0x9f, 0x9f, 0x90, 0x9f, 0x9f, 
    0x80, 0x9d, 0x95, 0x95, 0x9f, 0x8e, 0x80, 0xbf, 
    0xbf, 0x90, 0x88, 0x90, 0xbf, 0xbf, 0x80,
    
    0x01, 0x01, 0x01, 0x01, 0x01, 0x51, 0x7d, 0x3d, 
    0x01, 0x51, 0x7d, 0x3d, 0x01, 0x39, 0x7d, 0x45, 
    0x7d, 0x39, 0x01, 0x01, 0x01, 0x01, 0x01,

    

};

const uint8_t bat_m[2][23]={
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x8f, 
    0x8b, 0xbb, 0xa3, 0xa3, 0xa3, 0xbb, 0x8b, 0x8f, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xfd, 
    0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,


};



const uint8_t n_blank_m[3][19]={
  
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20,

    
    
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00,

    
    
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10

    
    
    
};



const uint8_t n_4_m[3][19]={
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x27, 0x27, 
0x20, 0x20, 0x20, 0x27, 0x27, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20,


0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
0x60, 0x60, 0x60, 0xe0, 0xe0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00,


0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10



};





const uint8_t n_5_m[3][19]={

0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x26, 0x26, 
0x26, 0x26, 0x26, 0x27, 0x27, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20,


0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x7f, 
0x63, 0x63, 0x63, 0xe3, 0xe3, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00,

0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10

};









const uint8_t n_13_m[3][19]={
  
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x23, 0x27, 
0x26, 0x26, 0x27, 0x23, 0x20, 0x20, 0x20, 0x27, 
0x27, 0x23, 0x20,

    
    
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xde, 0xff,
0x63, 0x63, 0x07, 0x06, 0x00, 0x00, 0x03, 0xff, 
0xff, 0x03, 0x00,

    
    
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10

    
    
    
};





const uint8_t n_250_m[3][19]={
  
    0x23, 0x27, 0x26, 0x27, 0x23, 0x20, 0x26, 0x26, 
    0x26, 0x27, 0x27, 0x20, 0x23, 0x27, 0x26, 0x26, 
    0x27, 0x23, 0x20,
    
    0xfe, 0xff, 0x03, 0xff, 0xfe, 0x00, 0x3e, 0x7f, 
    0x63, 0xe3, 0xc3, 0x00, 0x83, 0xc3, 0x63, 0x33, 
    0x1f, 0x0f, 0x00,

     0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x10,0x10,0x10
    

    
    
    
};







uint8_t display_n_blank(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;
    if(y==1)
    {
            if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_blank_m[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_blank_m[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_blank_m[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_blank_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_blank_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_blank_m[2][ms];
                 tori = temp;
                 //temp = ~temp;
                 //temp |= tori;
                 //temp &= 0xe0;
                 
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    }
    else if(y ==2)
    {
    
            if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_blank_m[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_blank_m[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_blank_m[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_blank_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_blank_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_blank_m[2][ms];
                 tori = temp;
                 //temp = ~temp;
                 //temp |= tori;
                 //temp &= 0xe0;
                 
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    
    
    }

}


uint8_t display_n4(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_4_m[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_4_m[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_4_m[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_4_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_4_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_4_m[2][ms];
                 tori = temp;
                 //temp = ~temp;
                 //temp |= tori;
                 //temp &= 0xe0;
                 
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}



uint8_t display_n5(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_5_m[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_5_m[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_5_m[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_5_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_5_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_5_m[2][ms];
                 tori = temp;
                 //temp = ~temp;
                 //temp |= tori;
                 //temp &= 0xe0;
                 
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}



uint8_t display_n250(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_250_m[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_250_m[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_250_m[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_250_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(6,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_250_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(7,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_250_m[2][ms];
                 tori = temp;
                 //temp = ~temp;
                 //temp |= tori;
                 //temp &= 0xe0;
                 
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}











uint8_t display_n13(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;

            if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_13_m[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_13_m[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_13_m[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(2,x);
            for(ms=0;ms<DEFG_LENGTH;ms++)
            {
                temp = n_13_m[0][ms];
                tori = temp;
                
                temp = ~temp;
                temp &= 0x3f;
  
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(3,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                  temp = n_13_m[1][ms];
                  tori = temp;

                  temp = ~temp;

                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(4,x);
             for(ms=0;ms<DEFG_LENGTH;ms++)
             {
                 temp = n_13_m[2][ms];
                 tori = temp;
                 //temp = ~temp;
                 //temp |= tori;
                 //temp &= 0xe0;
                 
                 temp = 0xf0;
                
                    
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

}








void display_bat(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =bat_m[0][ms];
                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = bat_m[1][ms];
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = bat_m[0][ms];
                    tori = temp;
                    
                    temp = ~temp;
                    //temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = bat_m[1][ms];
                     tori =temp;

                     temp = ~temp;
                    // temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                 }

            break;    

    }

}


void display_mem(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =mem_m[0][ms];
                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = mem_m[1][ms];
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = mem_m[0][ms];
                    tori = temp;
                    
                    temp = ~temp;
                    //temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = mem_m[1][ms];
                     tori =temp;

                     temp = ~temp;
                    // temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                 }

            break;    

    }

}












void display_blank_mode_pa(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =blank_m[0][ms];
                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = blank_m[1][ms];
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = blank_m[0][ms];
                    tori = temp;
                    
                    temp = ~temp;
                    //temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = blank_m[1][ms];
                     tori =temp;

                     temp = ~temp;
                    // temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                 }

            break;    

    }

}








void display_cmode(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =c_m[0][ms];
                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = c_m[1][ms];
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = c_m[0][ms];
                    tori = temp;
                    
                    temp = ~temp;
                    //temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = c_m[1][ms];
                     tori =temp;

                     temp = ~temp;
                    // temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                 }

            break;    

    }

}











void display_drops(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =drops_m[0][ms];
                    ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = drops_m[1][ms];
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = drops_m[0][ms];
                    tori = temp;
                    temp = ~temp;
                    //temp |= tori;
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = drops_m[1][ms];
                     tori =temp;

                        temp = ~temp;
                        //temp |= tori;

                    
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
             
             
            break;    
            
    
    
    
    
    }



}



void display_drop(uint8_t y,uint8_t x,uint8_t mode)
{

  uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {
                    
                    temp =drop_m[0][ms];
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = drop_m[1][ms];
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<MLENGTH;ms++)
                {

                    temp = drop_m[0][ms];
                    tori = temp;
                    


                        temp = ~temp;
                        //temp |= tori;

                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<MLENGTH;ms++)
                 {
                     temp = drop_m[1][ms];
                     tori =temp;
                     temp = ~temp;
                      //temp |= tori;
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
             
             
            break;    
            
    
    
    
    
    }



}


//==============================================================================
//==============================================================================

const uint8_t ptna_frame[2][WIDTH_PATTERN_A]=
{
0x3f, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x40, 0x3f,

    
0xfc, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x02, 0xfc,

  
};

const uint8_t ptnd_frame[3][WIDTH_PATTERN_D]=
{
 0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
 0x21, 0x23, 0x2f, 0x27, 0x23, 0x21, 0x10, 0x0f,
 
 
 
 0xff, 0x00, 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00,
 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0xe0, 
 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xff,
 
 
 0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,

  
};



const uint8_t ptne_frame[3][WIDTH_PATTERN_D]=
{
0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x2f, 0x27, 0x23, 0x21, 0x10, 0x0f,


0xff, 0x00, 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00,
0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x04, 0x06, 0x07, 0x07, 0x70, 0x88, 0x88, 0x88,
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,


0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x90, 0x10, 0x10, 0x10, 0x10, 
0xd0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,


    
    
    
};









const uint8_t ptnf_frame[3][WIDTH_PATTERN_D]={
    
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 
    0x22, 0x21, 0x2a, 0x24, 0x22, 0x20, 0x10, 0x0f,
    
    
    0xff, 0x00, 0x00, 0x00, 0x01, 0x01, 0x1f, 0x00,
    0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x1c, 0x24, 0x44, 0x88, 0x10, 
    0x20, 0x40, 0x80, 0x40, 0x00, 0x00, 0x00, 0xff,
    
    
    0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,


    

    
    };



const uint8_t ptng_frame[3][WIDTH_PATTERN_D]={

   0x0f, 0x10, 0x20, 0x20, 0x20, 0x2f, 0x20, 0x2f, 
    0x24, 0x22, 0x24, 0x2f, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x29, 0x2f, 
    0x2f, 0x29, 0x28, 0x20, 0x21, 0x23, 0x10, 0x0f,
    
    
    
    0xff, 0x00, 0x23, 0xa2, 0xa3, 0xa0, 0x2b, 0xa0,
    0x2f, 0x24, 0x26, 0xa4, 0x2f, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7a, 0xf9, 0xc0, 0xc0, 0xe0, 0xf0, 
    0xf0, 0xe0, 0xc0, 0xc0, 0xe0, 0xf0, 0x00, 0xff,

    
    0xc0, 0x20, 0x90, 0x10, 0x90, 0x10, 0x90, 0x10, 
    0x90, 0x10, 0x10, 0x10, 0x90, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x90, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,
};



const uint8_t ptnh_frame[3][WIDTH_PATTERN_D]={

0x0f, 0x10, 0x20, 0x25, 0x25, 0x27, 0x20, 0x27,
0x25, 0x27, 0x20, 0x24, 0x24, 0x27, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x26, 
0x26, 0x26, 0x26, 0x26, 0x27, 0x27, 0x10, 0x0f,


0xff, 0x00, 0x10, 0xd1, 0x51, 0x51, 0x10, 0x15, 
0x10, 0xd7, 0x12, 0x51, 0x52, 0xd7, 0x10, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x60, 0x60, 0x60, 0x60, 0xff, 0xff, 0x00, 0xff,


0xc0, 0x20, 0x10, 0xd0, 0x10, 0xd0, 0x10, 0xd0, 
0x10, 0xd0, 0x10, 0x10, 0x10, 0xd0, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x10, 0x90, 0x90, 0x20, 0xc0,





};


const uint8_t ptni_frame[3][WIDTH_PATTERN_D]={
    
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x24, 0x27, 0x24, 0x24, 
    0x24, 0x24, 0x24, 0x27, 0x24, 0x20, 0x10, 0x0f,
    
    
    0xff, 0x00, 0x00, 0x00, 0x00, 0x13, 0x24, 0x24, 
    0x24, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x8b, 0xd3,
    0xe3, 0xd3, 0x8b, 0x07, 0x00, 0x00, 0x00, 0xff,

    
    0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x90, 0x90, 
    0x90, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x90, 0x90, 0x90, 0x90, 
    0x90, 0x90, 0x90, 0x90, 0x90, 0x10, 0x20, 0xc0,

    
    
    
    };






uint8_t display_frame_abc(uint8_t y,uint8_t x, uint8_t mode)
{
    
    uint8_t temp =0;
    uint8_t tori =0;
    switch(mode)
    {
    
        case MODE_NORMAL:
            
             // setYX_LCD(0,COL_PAGE0_PATTERN_A);
                setYX_LCD(0,x);
                for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                {
                    
                    temp =ptna_frame[0][ms];
                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                 {
                     temp = ptna_frame[1][ms];
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            
            break;
            
         case MODE_REVERSE:
             
             //setYX_LCD(0,COL_PAGE0_PATTERN_A);
              setYX_LCD(0,x);
                for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                {

                    temp = ptna_frame[0][ms];
                    tori = temp;
                    
                    if(ms ==0 || ms == (WIDTH_PATTERN_A -1))
                    {
                        temp = ~temp;
                        temp  |= tori;
                        temp  &= 0x3f;
                        
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_A -2))
                    {
                        temp = ~temp;
                        temp |= tori;
                        temp  &= 0x7f;;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp |= tori;
                        
                    }

                     ee_WriteBytes(&temp, 0x40, 1);
                }

                //setYX_LCD(1,COL_PAGE1_PATTERN_A);
                setYX_LCD(1,x);
                 for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                 {
                     temp = ptna_frame[1][ms];
                     tori =temp;
                    if(ms ==0  || ms == (WIDTH_PATTERN_A -1))
                    {
                        temp = ~temp; 
                        temp |= tori;
                        temp  &= 0xfc;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_A -2))
                    {
                       
                        temp = ~temp;
                        temp |= tori;
                        temp  &= 0xfe;
                                   
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp |= tori;
                    }
                     
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
             
             
            break;    
             
    
    }





}




uint8_t display_frame_de(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;
     
    if (y == 1)
    {
            if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(2,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnd_frame[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(3,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnd_frame[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(4,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnd_frame[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(2,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnd_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                    //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(3,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnd_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(4,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnd_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    }
    else if(y == 2)
    {
      if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(2,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptne_frame[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(3,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptne_frame[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(4,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptne_frame[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(2,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptne_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                    //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(3,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptne_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(4,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptne_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

    }

}





uint8_t display_frame_fghi(uint8_t y,uint8_t x, uint8_t mode)
{
    uint8_t temp =0;
    uint8_t tori =0;
     
    
    if(y==1)
    {
    if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnf_frame[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnf_frame[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnf_frame[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnf_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                    //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnf_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnf_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    }
    else if (y == 2)
    {
            if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptng_frame[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptng_frame[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptng_frame[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptng_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                    //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptng_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptng_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    }
    else if(y == 3)
    {
      if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnh_frame[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnh_frame[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnh_frame[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptnh_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                    //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptnh_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptnh_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

    }
    else if(y == 4)
    {
      if(mode == MODE_NORMAL)
            {         
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptni_frame[0][ms];
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
             setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptni_frame[1][ms];
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
              setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptni_frame[2][ms];
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            //setYX_LCD(2,COL_PAGE0_PATTERN_D);
             setYX_LCD(5,x);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = ptni_frame[0][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                    //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
            //setYX_LCD(3,COL_PAGE1_PATTERN_D);
            setYX_LCD(6,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = ptni_frame[1][ms];
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             //setYX_LCD(4,COL_PAGE1_PATTERN_D);
               setYX_LCD(7,x);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = ptni_frame[2][ms];
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
    

    }

}








const uint8_t pata[3][2][WIDTH_PATTERN_A]={

    
    0x3f, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x98, 0xb8, 0xb0, 0xb0, 0xb0, 0xb0, 
    0xb8, 0x9c, 0x8f, 0x83, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x40, 0x3f,
    
    
    0xfc, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x31, 0x39, 0x19, 0x19, 0x19, 0x19,
    0x39, 0x71, 0xe1, 0x81, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x02, 0xfc,


    
    //--------------------------------------
    
    
    
    
    
    
    
    
0x3f, 0x40, 0x80, 0x83, 0x8f, 0xbf, 0x8f, 0x83, 
0x80, 0x80, 0x80, 0x83, 0x8f, 0xbf, 0x8f, 0x83, 
0x80, 0x80, 0x80, 0x83, 0x8f, 0xbf, 0x8f, 0x83, 
0x80, 0x40, 0x3f,



0xfc, 0x02, 0xf1, 0xf9, 0xfd, 0xfd, 0xfd, 0xf9,
0xf1, 0x01, 0xf1, 0xf9, 0xfd, 0xfd, 0xfd, 0xf9, 
0xf1, 0x01, 0xf1, 0xf9, 0xfd, 0xfd, 0xfd, 0xf9, 
0xf1, 0x02, 0xfc,





//----------------------------------------------

0x3f, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x81, 0x83, 0x86, 0x9d, 0xbd, 0x9d, 0x86,
    0x83, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x40, 0x3f,



0xfc, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0xf1, 0xf9, 0xcd, 0xb5, 0xb5, 0xb5, 0x6d,
    0xf9, 0xf1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x02, 0xfc,




};

const uint8_t patb[5][2][WIDTH_PATTERN_B]={

    
    0x3f, 0x40, 0x9f, 0x9f, 0x90, 0x9f, 0x9f, 0x90,
    0x9f, 0x9f, 0x80, 0x8d, 0x95, 0x95, 0x95, 0x8e,
    0x80, 0xbf, 0x9f, 0x88, 0x84, 0x88, 0x9f, 0xbf,
    0x80, 0x40, 0x3f,
    
    
    
    0xfc, 0x02, 0x01, 0x01, 0x01, 0x01, 0x51, 0x7d,
    0x3d, 0x01, 0x51, 0x7d, 0x3d, 0x01, 0x39, 0x7d, 
    0x45, 0x7d, 0x39, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x02, 0xfc,



    
    
    
    
    
    
    

};

const uint8_t patc[5][2][WIDTH_PATTERN_C]={
    
   0x3f, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
   0x80, 0x8f, 0x88, 0xb8, 0xa0, 0xa0, 0xa0, 0xb8, 
   0x88, 0x8f, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
   0x80, 0x40, 0x3f,


   0xfc, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
   0x01, 0xfd, 0x7d, 0x7d, 0x7d, 0x7d, 0x7d, 0x7d, 
   0x7d, 0xfd, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
   0x01, 0x02, 0xfc,


    
    
};



const uint8_t patd [5][3][WIDTH_PATTERN_D]={

    
    //---------------------------------------------------------------------
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x23, 0x23,
    0x20, 0x20, 0x20, 0x23, 0x23, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x21, 0x23, 0x2f, 0x27, 0x23, 0x21, 0x10, 0x0f,
    
    
    
    0xff, 0x00, 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00,
    0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
    0x30, 0x30, 0x30, 0xf0, 0xf0, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0xe0,
    0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xff,
    
    
    0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,


    


//---------------------------------------------------------------    
    
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x21, 0x23,
    0x23, 0x23, 0x23, 0x23, 0x21,0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20,0x20, 0x20, 0x20, 0x20, 
    0x21, 0x23, 0x2f, 0x27, 0x23, 0x21, 0x10, 0x0f,

    
0xff, 0x00, 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 
    0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xbf, 
    0x33, 0x33, 0x33, 0xff, 0xfe, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0xe0, 
    0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xff,

    

0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,

    

    //--------------------------------------------------------------------------
    
    
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x21, 0x23, 0x23, 0x23, 0x23, 
    0x21, 0x20, 0x20, 0x23, 0x23, 0x21, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x21, 0x23, 0x2f, 0x27, 0x23, 0x21, 0x10, 0x0f,
    
    
    
    0xff, 0x00, 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 
    0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0xde, 0xff, 0x33, 0x33, 0x87, 
    0x86, 0x00, 0x03, 0xff, 0xff, 0x83, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0xe0, 
    0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xff,
    
    
    0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,

    


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

};



const uint8_t pate[5][3][WIDTH_PATTERN_E]={
    
    
    
    //-----------------------------------------------------------
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x23, 0x23, 0x21, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x2f, 0x27, 0x23, 0x21, 0x10, 0x0f,

    
    0xff, 0x00, 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00,
    0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0x83, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x06, 0x07, 0x07, 0x70, 0x88, 0x88, 0x88, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
    
    
    0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x90, 0x10, 0x10, 0x10, 0x10, 
    0xd0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,


    
    
    
    
    //-----------------------------------------------------------
    
    
    
    
  0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
  0x20, 0x20, 0x2f, 0x27, 0x23, 0x21, 0x10, 0x0f,
  
  
  
  0xff, 0x00, 0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00,
  0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
  0x18, 0x18, 0x18, 0xf8, 0xf8, 0x00, 0x00, 0x00,
  0x04, 0x06, 0x07, 0x07, 0x70, 0x88, 0x88, 0x88, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,

  
  0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
  0x10, 0x10, 0x10, 0x90, 0x10, 0x10, 0x10, 0x10, 
  0xd0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,

  
};


const uint8_t patf[5][3][WIDTH_PATTERN_F]={
    
    
    
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x25, 
    0x22, 0x21, 0x2a, 0x24, 0x22, 0x20, 0x10, 0x0f,
    
    
    0xff, 0x00, 0x00, 0x00, 0x01, 0x01, 0x1f, 0x00,
    0x1f, 0x08, 0x04, 0x08, 0x1f, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
    0x18, 0x18, 0x18, 0xf8, 0xf8, 0x00, 0x00, 0x00, 
    0x00, 0x01, 0x0e, 0x12, 0x22, 0x44, 0x88, 0x10, 
    0x20, 0x40, 0x80, 0x40, 0x00, 0x00, 0x00, 0xff,
    
    
    
    0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,


    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    


  
  
  
};


const uint8_t patg[5][3][WIDTH_PATTERN_G]={
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x2f, 0x20, 0x2f, 
    0x24, 0x22, 0x24, 0x2f, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x29, 0x2f, 
    0x2f, 0x29, 0x28, 0x20, 0x21, 0x23, 0x10, 0x0f,
    
    
    
    0xff, 0x00, 0x23, 0xa2, 0xa3, 0xa0, 0x2b, 0xa0,
    0x2f, 0x24, 0x26, 0xa4, 0x2f, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
    0x18, 0x18, 0x18, 0xf8, 0xf8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7a, 0xf9, 0xc0, 0xc0, 0xe0, 0xf0, 
    0xf0, 0xe0, 0xc0, 0xc0, 0xe0, 0xf0, 0x00, 0xff,

    
    0xc0, 0x20, 0x90, 0x10, 0x90, 0x10, 0x90, 0x10, 
    0x90, 0x10, 0x10, 0x10, 0x90, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x90, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0,

    
    
    
    
    
    //------------------------------------------------------------------fcs
    0x0f, 0x10, 0x20, 0x20, 0x25, 0x25, 0x27, 0x20,
    0x27, 0x25, 0x27, 0x20, 0x24, 0x24, 0x27, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x21, 0x23, 0x23, 0x23, 
    0x21, 0x20, 0x21, 0x23, 0x23, 0x23, 0x21, 0x20, 
    0x21, 0x23, 0x23, 0x23, 0x23, 0x21, 0x20, 0x26, 
    0x26, 0x26, 0x26, 0x26, 0x27, 0x27, 0x10, 0x0f,

    
    0xff, 0x00, 0x00, 0x10, 0xd1, 0x51, 0x51, 0x10, 
    0x15, 0x10, 0xd7, 0x12, 0x51, 0x52, 0xd7, 0x10, 
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x81, 0xff, 
    0xff, 0x00, 0xff, 0xff, 0x01, 0xff, 0xff, 0x00, 
    0xcf, 0xff, 0x31, 0x31, 0x83, 0x83, 0x00, 0x00, 
    0x60, 0x60, 0x60, 0x60, 0xff, 0xff, 0x00, 0xff,

    0xc0, 0x20, 0x10, 0x10, 0xd0, 0x10, 0xd0, 0x10, 
    0xd0, 0x10, 0xd0, 0x10, 0x10, 0x10, 0xd0, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x90, 0x90, 0x90, 
    0x10, 0x10, 0x10, 0x90, 0x90, 0x90, 0x10, 0x10, 
    0x10, 0x90, 0x90, 0x90, 0x90, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x90, 0x90, 0x20, 0xc0,

    
    //--------------------------------------------//sec
    
    0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x21, 0x23, 0x23, 0x23, 0x23, 0x23, 0x21, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20,0x20, 0x20, 0x20, 0x24, 0x27, 0x24, 0x24, 
    0x24, 0x24, 0x24, 0x27, 0x24, 0x20, 0x10, 0x0f,
    
    
    
    0xff, 0x00, 0x00, 0x00, 0x00, 0x13, 0x24, 0x24,
    0x24, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xff, 0xff, 0x01, 0x01, 0x01, 0xff, 0xff, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x8b, 0xd3, 
    0xe3, 0xd3, 0x8b, 0x07, 0x00, 0x00, 0x00, 0xff,


    
    0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x90, 0x90,
    0x90, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x90, 0x90, 0x90, 0x90, 0x90, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x90, 0x90, 0x90, 0x90, 
    0x90, 0x90, 0x90, 0x90, 0x90, 0x10, 0x20, 0xc0,

    
    
    
    
    
    
    

    
    
    
    
    

};
const uint8_t path[5][3][WIDTH_PATTERN_H]={0};

//3
//3
//7
//5
//3



//2





uint8_t display_pattern(uint8_t num,uint8_t sub,uint8_t mode)
{
    
    uint8_t temp=0;
    
    
    switch(num)
    {
        case 1:       
            
            if(mode == MODE_NORMAL)
            {
                setYX_LCD(0,COL_PAGE0_PATTERN_A);
                for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                {
                    
                    temp = *(pata[sub][0] + ms);
                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                setYX_LCD(1,COL_PAGE1_PATTERN_A);
                 for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                 {
                     temp = *(pata[sub][1] + ms);
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            }
            else if(mode == MODE_REVERSE)
            {
                setYX_LCD(0,COL_PAGE0_PATTERN_A);
                for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                {

                    temp = *(pata[sub][0] + ms);
                    
                    if(ms ==0 || ms == (WIDTH_PATTERN_A -1))
                    {
                        temp =0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_A -2))
                    {
                        temp = 0x3f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                    }

                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                setYX_LCD(1,COL_PAGE1_PATTERN_A);
                 for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                 {
                     temp = *(pata[sub][1] + ms);
                    if(ms ==0  || ms == (WIDTH_PATTERN_A -1))
                    {
                        temp =0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_A -2))
                    {
                        temp = 0xfc;
                       
                    }
                    else
                    {
                    
                        temp = ~temp;
                    }
                     
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
            
            }
            else if(mode == MODE_BLANK)
            {
                               setYX_LCD(0,COL_PAGE0_PATTERN_A);
                for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                {

                    temp = *(pata[sub][0] + ms);
                    
                    if(ms ==0 || ms == (WIDTH_PATTERN_A -1))
                    {
                        temp =0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_A -2))
                    {
                        temp = 0x3f;
                        //temp = 0x1f;
                    }
                    else
                    {
                    
                        //temp = ~temp;
                        temp = 0x7f;
                    }

                     //ee_WriteBytes(pata[sub][0] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                }

                setYX_LCD(1,COL_PAGE1_PATTERN_A);
                 for(ms=0;ms<WIDTH_PATTERN_A;ms++)
                 {
                     temp = *(pata[sub][1] + ms);
                    if(ms ==0  || ms == (WIDTH_PATTERN_A -1))
                    {
                        temp =0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_A -2))
                    {
                        temp = 0xfc;
                       
                    }
                    else
                    {
                    
                        //temp = ~temp;
                        temp = 0xfe;
                    }
                     
                     //ee_WriteBytes(pata[sub][1] + ms, 0x40, 1);
                     ee_WriteBytes(&temp, 0x40, 1);
                 }
                
            }
                
            
            
            break;
        case 2:
            
            if(mode == MODE_NORMAL)  
            {
            setYX_LCD(0,COL_PAGE0_PATTERN_B);
            for(ms=0;ms<WIDTH_PATTERN_B;ms++)
            {
                temp = *(patb[sub][0] + ms);
                //ee_WriteBytes(patb[sub][0] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(1,COL_PAGE1_PATTERN_B);
             for(ms=0;ms<WIDTH_PATTERN_B;ms++)
             {
                temp = *(patb[sub][1] + ms);
                //ee_WriteBytes(patb[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
                
            setYX_LCD(0,COL_PAGE0_PATTERN_B);
            for(ms=0;ms<WIDTH_PATTERN_B;ms++)
            {
                temp = *(patb[sub][0] + ms);
                    if(ms ==0 || ms == (WIDTH_PATTERN_B -1))
                    {
                        temp =0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_B -2))
                    {
                        temp = 0x3f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                    }
                    
                //ee_WriteBytes(patb[sub][0] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(1,COL_PAGE1_PATTERN_B);
             for(ms=0;ms<WIDTH_PATTERN_B;ms++)
             {
                temp = *(patb[sub][1] + ms);
                    if(ms ==0 || ms == (WIDTH_PATTERN_B -1))
                    {
                        temp =0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_B -2))
                    {
                        temp = 0xfc;
                    }
                    else
                    {
                    
                        temp = ~temp;
                    }
                    
                //ee_WriteBytes(patb[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
                
                
                
                
            }
            
            break;
        case 3:
            
            
            
            setYX_LCD(0,COL_PAGE0_PATTERN_C);
            for(ms=0;ms<WIDTH_PATTERN_C;ms++)
            ee_WriteBytes(patc[sub][0] + ms, 0x40, 1);
            
            
            setYX_LCD(1,COL_PAGE1_PATTERN_C);
             for(ms=0;ms<WIDTH_PATTERN_C;ms++)
            ee_WriteBytes(patc[sub][1] + ms, 0x40, 1);
            

            
            
            
            
                
            
            
            break;
        case 4:
            
            if(mode == MODE_NORMAL)
            {         
            setYX_LCD(2,COL_PAGE0_PATTERN_D);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = *(patd[sub][0] + ms);
            //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,COL_PAGE1_PATTERN_D);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = *(patd[sub][1] + ms);
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,COL_PAGE1_PATTERN_D);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = *(patd[sub][2] + ms);
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
            
            setYX_LCD(2,COL_PAGE0_PATTERN_D);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = *(patd[sub][0] + ms);
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
                    //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,COL_PAGE1_PATTERN_D);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = *(patd[sub][1] + ms);
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,COL_PAGE1_PATTERN_D);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = *(patd[sub][2] + ms);
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            }
            else if(mode == MODE_BLANK)
            {
                            
            setYX_LCD(2,COL_PAGE0_PATTERN_D);
            for(ms=0;ms<WIDTH_PATTERN_D;ms++)
            {
                temp = *(patd[sub][0] + ms);
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                       
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        //temp = ~temp;
                        //temp &= 0x3f;
                        
                        //temp =0x3f;
                        temp =0x1f;
                        
                        
                        
                        
                    }
                    //ee_WriteBytes(patd[sub][0] + ms, 0x40, 1);
                    ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,COL_PAGE1_PATTERN_D);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                  temp = *(patd[sub][1] + ms);
                  
                  if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  //temp = ~temp;
                  temp =0xff;
                  }
                //ee_WriteBytes(patd[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,COL_PAGE1_PATTERN_D);
             for(ms=0;ms<WIDTH_PATTERN_D;ms++)
             {
                 temp = *(patd[sub][2] + ms);
                    if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        //temp = ~temp;
                        //temp &= 0xf0;
                        //temp |= 0x10;
                        
                        temp = 0xf0;
                    }
                //ee_WriteBytes(patd[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
                
                
                
                
                
                
                
                
            }
            
            
            
            
            
            break;
        case 5:
            
            
            if(mode == MODE_NORMAL)
            {
            setYX_LCD(2,COL_PAGE0_PATTERN_E);
            for(ms=0;ms<WIDTH_PATTERN_E;ms++)
            {
                temp =*(pate[sub][0] + ms);
               
            //ee_WriteBytes(pate[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,COL_PAGE1_PATTERN_E);
             for(ms=0;ms<WIDTH_PATTERN_E;ms++)
             {
                 temp =*(pate[sub][1] + ms);
                
                //ee_WriteBytes(pate[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,COL_PAGE1_PATTERN_E);
             for(ms=0;ms<WIDTH_PATTERN_E;ms++)
             {
                 temp =*(pate[sub][2] + ms);
                //ee_WriteBytes(pate[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
                      setYX_LCD(2,COL_PAGE0_PATTERN_E);
            for(ms=0;ms<WIDTH_PATTERN_E;ms++)
            {
                temp =*(pate[sub][0] + ms);
                  if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
            //ee_WriteBytes(pate[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,COL_PAGE1_PATTERN_E);
             for(ms=0;ms<WIDTH_PATTERN_E;ms++)
             {
                 temp =*(pate[sub][1] + ms);
                   if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
                //ee_WriteBytes(pate[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,COL_PAGE1_PATTERN_E);
             for(ms=0;ms<WIDTH_PATTERN_E;ms++)
             {
                 temp =*(pate[sub][2] + ms);
                  if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
                //ee_WriteBytes(pate[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
            
            
            }
            else if(mode == MODE_BLANK)
            {
                
                 setYX_LCD(2,COL_PAGE0_PATTERN_E);
            for(ms=0;ms<WIDTH_PATTERN_E;ms++)
            {
                temp =*(pate[sub][0] + ms);
                  if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        //temp = ~temp;
                        //temp &= 0x3f;
                        //temp = 0x3f;
                        temp = 0x1f;
                    }
            //ee_WriteBytes(pate[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(3,COL_PAGE1_PATTERN_E);
             for(ms=0;ms<WIDTH_PATTERN_E;ms++)
             {
                 temp =*(pate[sub][1] + ms);
                   if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  //temp = ~temp;
                       temp = 0xff;
                  }
                //ee_WriteBytes(pate[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(4,COL_PAGE1_PATTERN_E);
             for(ms=0;ms<WIDTH_PATTERN_E;ms++)
             {
                 temp =*(pate[sub][2] + ms);
                  if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        //temp = ~temp;
                        //temp &= 0xf0;
                        //temp |= 0x10;
                        
                        temp = 0xf0;
                        
                    }
                //ee_WriteBytes(pate[sub][2] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
            
                
            }
            
            
            break;
        case 6:
            
            if(mode == MODE_NORMAL)
            {
            setYX_LCD(5,COL_PAGE0_PATTERN_F);
            for(ms=0;ms<WIDTH_PATTERN_F;ms++)
            {
                temp =*(patf[sub][0] + ms);
            //ee_WriteBytes(patf[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(6,COL_PAGE1_PATTERN_F);
             for(ms=0;ms<WIDTH_PATTERN_F;ms++)
             {
                 temp = *(patf[sub][1] + ms);
                //ee_WriteBytes(patf[sub][1] + ms, 0x40, 1);
                ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(7,COL_PAGE1_PATTERN_F);
             for(ms=0;ms<WIDTH_PATTERN_F;ms++)
             {
                 temp =*(patf[sub][2] + ms);
               //ee_WriteBytes(patf[sub][2] + ms, 0x40, 1);
               ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
                 setYX_LCD(5,COL_PAGE0_PATTERN_F);
            for(ms=0;ms<WIDTH_PATTERN_F;ms++)
            {
                temp = *(patf[sub][0] + ms);
                if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
            //ee_WriteBytes(patf[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(6,COL_PAGE1_PATTERN_F);
             for(ms=0;ms<WIDTH_PATTERN_F;ms++)
             {
                 temp = *(patf[sub][1] + ms);
                    if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
            //ee_WriteBytes(patf[sub][1] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(7,COL_PAGE1_PATTERN_F);
             for(ms=0;ms<WIDTH_PATTERN_F;ms++)
             {
                 temp = *(patf[sub][2] + ms);
                  if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
            //ee_WriteBytes(patf[sub][2] + ms, 0x40, 1);
             ee_WriteBytes(&temp, 0x40, 1);
            
             }
            
            
            }
            else if(mode == MODE_BLANK)
            {
            
                       setYX_LCD(5,COL_PAGE0_PATTERN_F);
            for(ms=0;ms<WIDTH_PATTERN_F;ms++)
            {
                temp = *(patf[sub][0] + ms);
                if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                       // temp = ~temp;
                       // temp &= 0x3f;
                        
                        //temp = 0x3f;
                        temp = 0x1f;
                    }
            //ee_WriteBytes(patf[sub][0] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(6,COL_PAGE1_PATTERN_F);
             for(ms=0;ms<WIDTH_PATTERN_F;ms++)
             {
                 temp = *(patf[sub][1] + ms);
                    if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                 // temp = ~temp;
                  temp = 0xff;
                  }
            //ee_WriteBytes(patf[sub][1] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(7,COL_PAGE1_PATTERN_F);
             for(ms=0;ms<WIDTH_PATTERN_F;ms++)
             {
                 temp = *(patf[sub][2] + ms);
                  if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        //temp = ~temp;
                        //temp &= 0xf0;
                        //temp |= 0x10;
                        
                        
                        temp = 0xf0;
                        
                        
                    }
            //ee_WriteBytes(patf[sub][2] + ms, 0x40, 1);
             ee_WriteBytes(&temp, 0x40, 1);
            
             }
            
            
            
            }
            
            break;
        case 7:
            
            if(mode == MODE_NORMAL)
            {
            setYX_LCD(5,COL_PAGE0_PATTERN_G);
            for(ms=0;ms<WIDTH_PATTERN_G;ms++)
            {
                temp =*(patg[sub][0] + ms);
           
            //ee_WriteBytes(patg[sub][0] + ms, 0x40, 1);
             ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(6,COL_PAGE1_PATTERN_G);
             for(ms=0;ms<WIDTH_PATTERN_G;ms++)
             {
                 temp = *(patg[sub][1] + ms);
            //ee_WriteBytes(patg[sub][1] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(7,COL_PAGE1_PATTERN_G);
             for(ms=0;ms<WIDTH_PATTERN_G;ms++)
             {
                 temp = *(patg[sub][2] + ms);
            //ee_WriteBytes(patg[sub][2] + ms, 0x40, 1);
             ee_WriteBytes(&temp, 0x40, 1);
             }
            }
            else if(mode == MODE_REVERSE)
            {
                    setYX_LCD(5,COL_PAGE0_PATTERN_G);
            for(ms=0;ms<WIDTH_PATTERN_G;ms++)
            {
                temp =*(patg[sub][0] + ms);
                     if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0x3f;
                    }
            //ee_WriteBytes(patg[sub][0] + ms, 0x40, 1);
             ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(6,COL_PAGE1_PATTERN_G);
             for(ms=0;ms<WIDTH_PATTERN_G;ms++)
             {
                 temp = *(patg[sub][1] + ms);
                    if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  temp = ~temp;
                  }
            //ee_WriteBytes(patg[sub][1] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(7,COL_PAGE1_PATTERN_G);
             for(ms=0;ms<WIDTH_PATTERN_G;ms++)
             {
                 temp = *(patg[sub][2] + ms);
                 
                  if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        temp = ~temp;
                        temp &= 0xf0;
                        temp |= 0x10;
                    }
            //ee_WriteBytes(patg[sub][2] + ms, 0x40, 1);
             ee_WriteBytes(&temp, 0x40, 1);
             }
            
            }
            else if(mode == MODE_BLANK)
            {
                
                
                setYX_LCD(5,COL_PAGE0_PATTERN_G);
            for(ms=0;ms<WIDTH_PATTERN_G;ms++)
            {
                temp =*(patg[sub][0] + ms);
                     if(ms ==0 || ms == (WIDTH_PATTERN_D -1))
                    {
                        temp =0x0f;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0x1f;
                    }
                    else
                    {
                    
                        //temp = ~temp;
                        //temp &= 0x3f;
                        
                         //temp = 0x3f;
                          temp = 0x1f;
                        
                    }
            //ee_WriteBytes(patg[sub][0] + ms, 0x40, 1);
             ee_WriteBytes(&temp, 0x40, 1);
            }
            
            setYX_LCD(6,COL_PAGE1_PATTERN_G);
             for(ms=0;ms<WIDTH_PATTERN_G;ms++)
             {
                 temp = *(patg[sub][1] + ms);
                    if(ms == 0  || ms == (WIDTH_PATTERN_D - 1))
                  {
                      temp = 0xff;
                  }
                  else
                  {
                  //temp = ~temp;
                  temp = 0xff;
                  }
            //ee_WriteBytes(patg[sub][1] + ms, 0x40, 1);
            ee_WriteBytes(&temp, 0x40, 1);
             }
            
             setYX_LCD(7,COL_PAGE1_PATTERN_G);
             for(ms=0;ms<WIDTH_PATTERN_G;ms++)
             {
                 temp = *(patg[sub][2] + ms);
                 
                  if(ms ==0 || ms == (WIDTH_PATTERN_D -1) )
                    {
                        temp =0xe0;
                    }
                    else if(ms ==1 || ms == (WIDTH_PATTERN_D -2))
                    {
                        temp = 0xf0;
                    }
                    else
                    {
                    
                        //temp = ~temp;
                        //temp &= 0xf0;
                        //temp |= 0x10;
                        
                        
                        temp =0xf0;
                        
                    }
            //ee_WriteBytes(patg[sub][2] + ms, 0x40, 1);
             ee_WriteBytes(&temp, 0x40, 1);
             }
                
                
                
                
                
                
                
                
            }
            
            break;
        default:
            break;
    }



    return 1;
}


uint8_t clear_device(void)
{
    
    
    uint8_t page,col;
  for(page=0;page<9;page++)  
  {
    setYX_LCD(page,0);
    write_buf[0] =0x00;
       for(col=0;col<99;col++)
        {
            ee_WriteBytes(write_buf, 0x40, 1);
        }
  }



}

void Initial_LY096BG30(void)
{


i2c_CfgGpio();
  
//delay(2000);

#if 1
//PORTEbits.RE1 =0;
 //LATEbits.LE1 =0;
 LATEbits.LATE1=0;
 delay(1);//=====================
//delay(2000);
//delay(2000);

//PORTEbits.RE1 =1;
//LATEbits.LE1 =1;
LATEbits.LATE1=1;
delay(1);

#endif

    write_buf[0]=0x21;  
	ee_WriteBytes(write_buf, 0x00, 1);//delay(10);
    //ee_WriteBytes(write_buf, 0x80, 1);
	
    write_buf[0]=0x15;
    ee_WriteBytes(write_buf, 0x00, 1);//delay(10);

    write_buf[0]=0x08;
	ee_WriteBytes(write_buf, 0x00, 1);//delay(10);

    write_buf[0]=0x9f;
	ee_WriteBytes(write_buf, 0x00, 1);//delay(10);
    
    write_buf[0]=0x20;
	ee_WriteBytes(write_buf, 0x00, 1);//delay(10);
    
    write_buf[0]=0x05;
	ee_WriteBytes(write_buf, 0x00, 1);//delay(10);

    write_buf[0]=0x0c;//normal
     //write_buf[0]=0x08;//blank
   // write_buf[0]=0x0d;//reverse
	ee_WriteBytes(write_buf, 0x00, 1);//delay(10);
    
    clear_device();
#if 1
    display_frame_abc(0,COL_PAGE0_PATTERN_A, MODE_NORMAL);
    display_cmode(0,COL_PAGE0_MDROPS,MODE_NORMAL);
    
    display_frame_abc(0,COL_PAGE0_PATTERN_B, MODE_NORMAL);
    display_mem(0,COL_PAGE0_MEM,MODE_NORMAL);
    
    
    display_frame_abc(0,COL_PAGE0_PATTERN_C, MODE_NORMAL);
    display_bat(0,COL_PAGE0_BAT,MODE_NORMAL);
    
    
    display_frame_de(1,COL_PAGE0_PATTERN_D, MODE_NORMAL);
    display_n4(0,COL_PAGE0_DN, MODE_NORMAL);
    
    display_frame_de(2,COL_PAGE0_PATTERN_E, MODE_NORMAL);
    display_n4(0,COL_PAGE0_EN, MODE_NORMAL);
    
    
    
    display_frame_fghi(1,COL_PAGE0_PATTERN_F, MODE_NORMAL);
    display_n5(0,COL_PAGE0_FN, MODE_NORMAL);
    
    
    display_frame_fghi(2,COL_PAGE0_PATTERN_G, MODE_NORMAL);
    display_n5(0,COL_PAGE0_GN, MODE_NORMAL);
    
    
#endif
    
#if 0

    clear_device();
    for(ss=1;ss<8;ss++)
    {
       
       display_pattern(ss,0,MODE_NORMAL);
    }
    

#endif    
         
         
         
         
         
         
         
         
         
         
         
    //display_pattern(1,0,MODE_NORMAL);
    //display_pattern(1,1,0);
    //display_pattern(1,2,0);
    //display_pattern(1,2,MODE_NORMAL);
    //display_pattern(1,2,MODE_REVERSE);
    //display_pattern(1,2,MODE_BLANK);
    
    //display_pattern(2,0,MODE_NORMAL);
    //display_pattern(2,0,MODE_REVERSE);
    
     //display_pattern(3,0,MODE_NORMAL);
     
     
     //display_pattern(4,0,MODE_NORMAL);
     //display_pattern(4,0,MODE_REVERSE);
      //display_pattern(4,0,MODE_BLANK);
     
     
     //display_pattern(5,0,MODE_NORMAL);
     //display_pattern(5,0,MODE_NORMAL);
     //display_pattern(5,0,MODE_REVERSE);
     //display_pattern(5,0,MODE_BLANK);
     
     
     
     //display_pattern(6,0,MODE_NORMAL);
     //display_pattern(6,0,MODE_NORMAL);
      //display_pattern(6,0,MODE_REVERSE);
      //display_pattern(6,0,MODE_BLANK);
     
     
     //display_pattern(7,0,MODE_NORMAL);
     //display_pattern(7,1,0);
      //display_pattern(7,2,0);
       //display_pattern(7,2,MODE_REVERSE);
       
        //display_pattern(7,2,MODE_BLANK);
   

       
}


//c mode
//4  6  13                 //0  1  2  3  4
//1  2  2.5  5  10         //3


//m drop
//4  6  13                // 0  1  2  3  4
//1  2  2.5  5  10        //100   150  200  250   300


//s  drop
//4  6  13                //0  1  2  3  4
//1  2  2.5  5  10        //0  1  2  3








interface_t interface_x ={0};

uint8_t hg_interface(void)
{
    
    uint8_t key_value = KEY_NOT_PRESSED;
    
    key_value = KEY_Scan();
    
    
    switch(key_value)
    {
    
        case KEY_UP_PRESSED:
            
            if(interface_x.mode == MODE_BLINK)
            {
               interface_x.cnt_blink = TIMOUT_BLINK;//4s
               //to do
               //update parameters
               
               interface_x.sub ++;
               
               
               
               if(interface_x.focus ==1)
               {
                    if(interface_x.sub == 3)        
                             interface_x.sub = 0;
               }
               
               
                if(interface_x.focus ==2 || interface_x.focus ==3)
               {
                    if(interface_x.sub == 5)        
                             interface_x.sub = 0;
               }
               
               
               
               
               
               
            }
            else
            {
                
                
                if(interface_x.focus)//turn back the previous snap
                {
                   display_pattern(interface_x.focus,interface_x.sub_old,MODE_NORMAL);
                }
                
            
                interface_x.focus ++;

                if(interface_x.profile.inject_mode == 2 && interface_x.focus == 2)
                {
                   interface_x.focus ++;
                }


                if(interface_x.focus == 8)
                    interface_x.focus =1;

                interface_x.mode = MODE_REVERSE;

            }
            
            
            
            
            break;
            
        case KEY_DOWN_PRESSED:
            
             if(interface_x.mode == MODE_BLINK)
             {
                 interface_x.cnt_blink = TIMOUT_BLINK;//4s
                 
                 //to do
                 //update parameters
                 
             }
             else
             {
                 
                if(interface_x.focus)//turn back the previous snap
                {
                   display_pattern(interface_x.focus,interface_x.sub_old,MODE_NORMAL);
                }
                 
                 
                 
                    if(interface_x.focus ==1)
                    {
                         if(interface_x.sub == 3)        
                                  interface_x.sub = 0;
                    }


                     if(interface_x.focus ==2 || interface_x.focus ==3)
                    {
                         if(interface_x.sub == 5)        
                                  interface_x.sub = 0;
                    }
                 
                    
                    if(interface_x.focus == 0)
                    {
                         interface_x.focus = 8;
                    }
                    else
                    {
                        interface_x.focus --;
                    }
                    
                    
                    if(interface_x.profile.inject_mode == 2 && interface_x.focus == 2)
                    {
                       interface_x.focus --;
                    }


                    if(interface_x.focus == 0)
                        interface_x.focus =7;

                    interface_x.mode = MODE_REVERSE;
            
            
             }
            
            
            
            
            
            
            break;
            
        case KEY_V_PRESSED:
            
            if(interface_x.focus)
            {
              if(interface_x.mode == MODE_REVERSE)
              {
                interface_x.mode = MODE_BLINK;
                interface_x.cnt_blink = TIMOUT_BLINK;//4s
                
                
                
                
              }
              else if(interface_x.mode == MODE_BLINK)
              {
              
                  
                  if(interface_x.focus ==1)
                  {
                        
                      if(interface_x.profile.inject_mode == WMD_C)
                      {
                      //update sub limit
                        interface_x.sub_lmt[0] =5;
                      }
                      else if(interface_x.profile.inject_mode == WMD_S_DROP)
                      {
                         //update sub limit
                        interface_x.sub_lmt[0] =5;
                      }
                      else if(interface_x.profile.inject_mode == WMD_M_DROP)
                      {
                        //update sub limit
                        interface_x.sub_lmt[0] =5;
                      
                      
                      }
                      
                      
                      
                      
                  }
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
               interface_x.mode = MODE_NORMAL;
               interface_x.focus =0;
              
              }
            
            
            }
            
            break;  
            
                     
    }
    
    
    
     if(interface_x.mode == MODE_BLINK)
     {
          if(interface_x.cnt_blink == 0)
          {
             interface_x.mode = MODE_NORMAL;
             //display_pattern(interface_x.focus,interface_x.sub,interface_x.mode);
             display_pattern(interface_x.focus,interface_x.sub_old,interface_x.mode);
             
             interface_x.sub = interface_x.sub_old;
             interface_x.focus =0;
          }
     
     }
      
    
    if(interface_x.mode == MODE_NORMAL || interface_x.mode == MODE_REVERSE)
    {
           display_pattern(interface_x.focus,interface_x.sub,interface_x.mode);
    }
    
    
    
    
    return 1;
}
