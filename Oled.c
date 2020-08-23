//#include<pic18.h> 
#include<xc.h> 
#include "oled.h"
#include "oledfont.h"  	 
#include "Beep.h"
//==============================================================================
//==============================================================================
//==============================================================================

void delay(unsigned int  x)
{
  	unsigned int  i,j;
    for(i=0;i<x;i++)
       for(j=0;j<10;j++);
}

static void i2c_Delay(void)
{
	uint32_t i;
	for (i = 0; i < 5; i++);
    
    
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
}


uint8_t i2c_WaitAck(void)
{
	uint8_t re;

	EEPROM_I2C_SDA_1();	
	i2c_Delay();
	EEPROM_I2C_SCL_1();
   // DDRCbits.RC4 =1;//====================sda input mode
    TRISCbits.RC4 =1;
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
     TRISCbits.RC4 =0;
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
    
#if 0
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(EEPROM_RCC_I2C_PORT, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN | EEPROM_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	
	GPIO_Init(EEPROM_GPIO_PORT_I2C, &GPIO_InitStructure);

	i2c_Stop();
    
#endif
    

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
  LATEbits.LATE1=0;

    
    //PORTCbits.RC3 =1;//SCL
    //PORTCbits.RC4 =1;//SDA
    //i2c_Stop();
     
}






//==============================================================================
//==============================================================================
//==============================================================================













	   
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

void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCL_Clr();
		if(dat&0x80)
		{
		 OLED_SDA_Set();
		}
		else
		{
		 OLED_SDA_Clr();
		}
	  OLED_SCL_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 

//******************************************************************************
//    oˉêy?μ?÷￡oOLED??ê?áDμ??eê????1μ??·
//    è??úêy?Y￡oa  áDμ??eê?μ??·
//              b  áDμ????1μ??·
//    ·μ???μ￡o  ?T
//******************************************************************************
void Column_Address(u8 a, u8 b)
{
	OLED_WR_Byte(0x15,OLED_CMD);			    // Set Column Address
	OLED_WR_Byte(a,OLED_CMD);				//   Default => 0x00
	OLED_WR_Byte(b,OLED_CMD);				//   Default => 0x77
}

//******************************************************************************
//    oˉêy?μ?÷￡oOLED??ê?DDμ??eê????1μ??·
//    è??úêy?Y￡oa  DDμ??eê?μ??·
//              b  DDμ????1μ??·
//    ·μ???μ￡o  ?T
//******************************************************************************
void Row_Address(u8 a, u8 b)
{
	OLED_WR_Byte(0x75,OLED_CMD);			// Set Row Address
	OLED_WR_Byte(a,OLED_CMD);				//   Default => 0x00
	OLED_WR_Byte(b,OLED_CMD);				//   Default => 0x3F
}

//******************************************************************************
//    oˉêy?μ?÷￡oOLED???á??ê?
//    è??úêy?Y￡o?T
//    ·μ???μ￡o  ?T
//******************************************************************************
void OLED_Clear(u8 x1,u8 y1,u8 x2,u8 y2,u8 color)
{
	u8 i,m=0;
	x1/=2;x2/=2;
	Column_Address(x1,x2-1);
	Row_Address(y1,y2-1);
	for (m=0;m<y2-y1;m++) 
	{ 
		for (i=0;i<x2-x1;i++)
		{
			 OLED_WR_Byte(color,OLED_DATA);
		}
	}
}


void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey)
{
	u8 i,j,c,k;
	u8 data1,data2,DATA1=0;
	c=chr-' ';
	for(i=0;i<sizey/8;i++)
	{
	  Column_Address(x/2,x/2+sizey/4-1);//éè??áDμ??·
	  Row_Address(y+i*8,y+i*8+7);//éè??DDμ??·
		for(j=0;j<sizey/4;j++)
		{
			if(sizey==16)//8x16 ASCII??
			{
				data1=F8X16[c][2*j+i*sizey/2+0];
				data2=F8X16[c][2*j+i*sizey/2+1];
			}
			else if(sizey==24)//12x24 ASCII??
			{
				data1=F12X24[c][2*j+i*sizey/2+0];
				data2=F12X24[c][2*j+i*sizey/2+1];

			}
			else if(sizey==32)//16x32 ASCII??
			{
				data1=F16X32[c][2*j+i*sizey/2+0];
				data2=F16X32[c][2*j+i*sizey/2+1];
			}
			for(k=0;k<8;k++)
			{
				if(data1&(0x01<<k))
				{
					DATA1=0xf0;
				}
				if(data2&(0x01<<k))
				{
					DATA1|=0x0f;
				}
				OLED_WR_Byte(DATA1,OLED_DATA);
				DATA1=0;
			}
		}
	}
}


void OLED_ShowString(u8 x,u8 y,u8 *dp,u8 sizey)
{
	while(*dp!='\0')
	{
	  OLED_ShowChar(x,y,*dp,sizey);
		dp++;
		x+=sizey/2;
	}
}



u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)result*=m;    
	return result;
}



void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey)
{         	
	u8 t,temp;
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(sizey/2)*t,y,' ',sizey);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(sizey/2)*t,y,temp+'0',sizey); 
	}
}


void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 sizey)
{
	u8 i,j,k;
	u8 data1,data2,DATA1=0;
	for(i=0;i<sizey/8;i++)
	{
	  Column_Address(x/2,x/2+sizey/2-1);//éè??áDμ??·
	  Row_Address(y+i*8,y+i*8+7);//éè??DDμ??·
		for(j=0;j<sizey/2;j++)
		{
			if(sizey==16)//8x16 ASCII??
			{
				data1=Hzk16x16[num][2*j+i*sizey+0];
				data2=Hzk16x16[num][2*j+i*sizey+1];
			}
			else if(sizey==24)//12x24 ASCII??
			{
				data1=Hzk24x24[num][2*j+i*sizey+0];
				data2=Hzk24x24[num][2*j+i*sizey+1];

			}
			else if(sizey==32)//16x32 ASCII??
			{
				data1=Hzk32x32[num][2*j+i*sizey+0];
				data2=Hzk32x32[num][2*j+i*sizey+1];
			}
			for(k=0;k<8;k++)
			{
				if(data1&(0x01<<k))
				{
					DATA1=0xf0;
				}
				if(data2&(0x01<<k))
				{
					DATA1|=0x0f;
				}
				OLED_WR_Byte(DATA1,OLED_DATA);
				DATA1=0;
			}
		}
	}
}

void OLED_DrawBMP(u8 x,u8 y,u8 width,u8 height,const u8 *BMP)
{
	u16 k,num;
	x/=2;width/=2;
	Column_Address(x,x+width-1);
	Row_Address(y,y+height-1);
	num=width*height;
	for (k=0;k<num;k++) 
	{ 
		 OLED_WR_Byte(BMP[k],OLED_DATA);
	}
}	

void OledIoInit(void)
{
	DDRCbits.RC3  =0;
	DDRCbits.RC4  =0;
	DDRCbits.RC5  =0;
	DDRCbits.RC6  =0;
	DDRCbits.RC7  =0;

	//PORTCbits.RC3  =1;
	//PORTCbits.RC4  =0;

//	PORTCbits.RC5  =1;
//	PORTCbits.RC6  =0;

//	PORTCbits.RC6  =1;

}

		    
void Init_ssd1327(void)
{
	OledIoInit();

	OLED_RES_Clr();
  	delay_ms(100);
	OLED_RES_Set();
	
	OLED_WR_Byte(0xae,OLED_CMD);//Set display off
	OLED_WR_Byte(0xa0,OLED_CMD);//Set re-map
	if(USE_HORIZONTAL){OLED_WR_Byte(0x66,OLED_CMD);}
	else{OLED_WR_Byte(0x55,OLED_CMD);}
	OLED_WR_Byte(0xa1,OLED_CMD);//Set display start line
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xa2,OLED_CMD);//Set display offset
	if(USE_HORIZONTAL)OLED_WR_Byte(0x60,OLED_CMD);
	else OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xa4,OLED_CMD);//Normal Display
	OLED_WR_Byte(0xa8,OLED_CMD);//Set multiplex ratio
	OLED_WR_Byte(0x7f,OLED_CMD);
	OLED_WR_Byte(0xab,OLED_CMD);//Function Selection A
	OLED_WR_Byte(0x01,OLED_CMD);//Enable internal VDD regulator
	OLED_WR_Byte(0x81,OLED_CMD);//Set contrast
	OLED_WR_Byte(0x77,OLED_CMD);
	OLED_WR_Byte(0xb1,OLED_CMD);//Set Phase Length
	OLED_WR_Byte(0x31,OLED_CMD);
	OLED_WR_Byte(0xb3,OLED_CMD);//Set Front Clock Divider /Oscillator Frequency
	OLED_WR_Byte(0xb1,OLED_CMD);
    OLED_WR_Byte(0xb5,OLED_CMD);//
    OLED_WR_Byte(0x03,OLED_CMD);//0X03 enable
	OLED_WR_Byte(0xb6,OLED_CMD);//Set Second pre-charge Period
	OLED_WR_Byte(0x0d,OLED_CMD);
	OLED_WR_Byte(0xbc,OLED_CMD);//Set Pre-charge voltage
	OLED_WR_Byte(0x07,OLED_CMD);
	OLED_WR_Byte(0xbe,OLED_CMD);//Set VCOMH
	OLED_WR_Byte(0x07,OLED_CMD);
	OLED_WR_Byte(0xd5,OLED_CMD);//Function Selection B
	OLED_WR_Byte(0x02,OLED_CMD);//Enable second pre-charge
	OLED_Clear(0,0,128,96,0x00);
	OLED_WR_Byte(0xaf,OLED_CMD);//Display on
}



void Init_LCD(void)
{
	OledIoInit();

	OLED_RES_Clr();
  	delay_ms(100);
	OLED_RES_Set();
	
	OLED_WR_Byte(0xae,OLED_CMD);//Set display off
	OLED_WR_Byte(0xa0,OLED_CMD);//Set re-map
	if(USE_HORIZONTAL){OLED_WR_Byte(0x66,OLED_CMD);}
	else{OLED_WR_Byte(0x55,OLED_CMD);}
	OLED_WR_Byte(0xa1,OLED_CMD);//Set display start line
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xa2,OLED_CMD);//Set display offset
	if(USE_HORIZONTAL)OLED_WR_Byte(0x60,OLED_CMD);
	else OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xa4,OLED_CMD);//Normal Display
	OLED_WR_Byte(0xa8,OLED_CMD);//Set multiplex ratio
	OLED_WR_Byte(0x7f,OLED_CMD);
	OLED_WR_Byte(0xab,OLED_CMD);//Function Selection A
	OLED_WR_Byte(0x01,OLED_CMD);//Enable internal VDD regulator
	OLED_WR_Byte(0x81,OLED_CMD);//Set contrast
	OLED_WR_Byte(0x77,OLED_CMD);
	OLED_WR_Byte(0xb1,OLED_CMD);//Set Phase Length
	OLED_WR_Byte(0x31,OLED_CMD);
	OLED_WR_Byte(0xb3,OLED_CMD);//Set Front Clock Divider /Oscillator Frequency
	OLED_WR_Byte(0xb1,OLED_CMD);
    OLED_WR_Byte(0xb5,OLED_CMD);//
    OLED_WR_Byte(0x03,OLED_CMD);//0X03 enable
	OLED_WR_Byte(0xb6,OLED_CMD);//Set Second pre-charge Period
	OLED_WR_Byte(0x0d,OLED_CMD);
	OLED_WR_Byte(0xbc,OLED_CMD);//Set Pre-charge voltage
	OLED_WR_Byte(0x07,OLED_CMD);
	OLED_WR_Byte(0xbe,OLED_CMD);//Set VCOMH
	OLED_WR_Byte(0x07,OLED_CMD);
	OLED_WR_Byte(0xd5,OLED_CMD);//Function Selection B
	OLED_WR_Byte(0x02,OLED_CMD);//Enable second pre-charge
	OLED_Clear(0,0,128,96,0x00);
	OLED_WR_Byte(0xaf,OLED_CMD);//Display on
}


//=============================================================================================
//=============================================================================================


uint8_t ee_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;
	
	i2c_Start();		

	
	i2c_SendByte(_Address | EEPROM_I2C_WR);
	ucAck = i2c_WaitAck();	

	i2c_Stop();			

	i2c_NAck();	
	
	return ucAck;
}



uint8_t ee_WaitStandby(void)
{
	uint32_t wait_count = 0;
	
	while(ee_CheckDevice(EEPROM_DEV_ADDR))
	{
	
		if(wait_count++>0xFFFF)
		{
			return 1;
		}
	}
	return 0;
}


uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize)
{
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


void ee_Erase(void)
{
	uint16_t i;
	uint8_t buf[EEPROM_SIZE];
	

	for (i = 0; i < EEPROM_SIZE; i++)
	{
		buf[i] = 0xFF;
	}
	
	
	if (ee_WriteBytes(buf, 0, EEPROM_SIZE) == 0)
	{
		//printf("擦除eeprom出错！\r\n");
		return;
	}
	else
	{
		//printf("擦除eeprom成功！\r\n");
	}
}






uint8_t write_buf[EEPROM_SIZE];
uint8_t read_buf[EEPROM_SIZE];

uint8_t ee_Test(void) 
{
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
}








//============================================================================
//============================================================================




/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
	
	#if 0
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
   Write_IIC_Byte(0x00);			//write command
   Write_IIC_Byte(IIC_Command); 
   IIC_Stop();
	
	#endif
	
	
	
	
	
	
	
	
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
	#if 0
   IIC_Start();
   Write_IIC_Byte(0x78);			
   Write_IIC_Byte(0x40);			//write data
   Write_IIC_Byte(IIC_Data);
   IIC_Stop(); 
	
	
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

uint8_t ms = 0x66;
uint8_t ss=0;
uint8_t css=0;
uint8_t rcnt=0;
uint8_t page=0;
void Initial_LY096BG30(void)
{

    

    
i2c_CfgGpio();
  


//delay(2000);


//PORTEbits.RE1 =0;
 //LATEbits.LE1 =0;
 LATEbits.LATE1=0;
delay(1);
//delay(2000);
//delay(2000);

//PORTEbits.RE1 =1;
//LATEbits.LE1 =1;
LATEbits.LATE1=1;
delay(1);
//delay(2000);
//delay(2000);

  // while(1);


    //ms =  ee_CheckDevice(EEPROM_DEV_ADDR);  
    
    //while(1);
   // if(ms == 0)buzz(); 
    //while(1);
    //delay(2000);
//delay(2000);
//delay(2000);
   
    
    //function set
    // 0 0 1 MX MY PD V H
    // 0 0 1 0   0 0  0 1
	//write_buf[0]=0x00;
    //write_buf[1]=0x21;
    write_buf[0]=0x21;//------------------------------------------------------01
    //write_buf[0]=0x29; 
     //write_buf[0]=0x39; 
    //write_buf[0]=0x31;
	ee_WriteBytes(write_buf, 0x00, 1);
    //ee_WriteBytes(write_buf, 0x80, 1);
	
 //while(1);
    
	//set Bias system
	//write_buf[0]=0x10;
    //write_buf[0]=0x11;
    //write_buf[0]=0x12;
     //write_buf[0]=0x13;
      //write_buf[0]=0x14;
       write_buf[0]=0x15;
      // write_buf[0]=0x16;
      //  write_buf[0]=0x17;
       
    ee_WriteBytes(write_buf, 0x00, 1);
	//ee_WriteBytes(write_buf, 0x80, 1);

    //set DO
    write_buf[0]=0x08;//MSB on top
    //write_buf[0]=0x0c;//LSB on top
	ee_WriteBytes(write_buf, 0x00, 1);
    //ee_WriteBytes(write_buf, 0x80, 1);

    //set VOP
    write_buf[0]=0x9f;
     //write_buf[0]=0xaf;
    //  write_buf[0]=0xb0;
    //write_buf[0]=0x90;
    //write_buf[0]=0xc0;
     //write_buf[0]=0x8f;
	ee_WriteBytes(write_buf, 0x00, 1);
    //ee_WriteBytes(write_buf, 0x80, 1);
    

    
    
	//function set
    // 0 0 1 MX MY PD V H
    // 0 0 1 0   0 0  0 0
	//write_buf[0]=0x00;
    //write_buf[1]=0x20;
    write_buf[0]=0x20;//----------------------------------------------------------02
	ee_WriteBytes(write_buf, 0x00, 1);
    //ee_WriteBytes(write_buf, 0x80, 1);
    
   // Set VLCD Range(PRS)
    //write_buf[0]=0x04;
    write_buf[0]=0x05;
	ee_WriteBytes(write_buf, 0x00, 1);
    //ee_WriteBytes(write_buf, 0x80, 1);
    //Display control D=1  E=0
    //write_buf[0]=0x0c;
	//ee_WriteBytes(write_buf, 0x00, 1);
    
    //write_buf[0]=0x09;//all display segments on
    write_buf[0]=0x0c;//normal
     //write_buf[0]=0x08;//blank
   // write_buf[0]=0x0d;//reverse
	ee_WriteBytes(write_buf, 0x00, 1);
    //ee_WriteBytes(write_buf, 0x80, 1);
    //write_buf[0]=0x0d;//inverse mode
	//ee_WriteBytes(write_buf, 0x00, 1);
    
    
    write_buf[0]=0x80;//X address
    //write_buf[0]=0x88;//X address
	ee_WriteBytes(write_buf, 0x00, 1);
    //ee_WriteBytes(write_buf, 0x80, 1);
    
    //set X Y address
    write_buf[0]=0x40;//Y address
    //write_buf[0]=0x48;//Y address
	ee_WriteBytes(write_buf, 0x00, 1);
    //ee_WriteBytes(write_buf, 0x80, 1);

    
    
   // ee_ReadBytes(&ss, 0x80, 1);
   // css = ss;   
    
      // delay(2000);
 //  delay(2000);
  // delay(2000);
    //  delay(2000);
   //delay(2000);
  // delay(2000);
  // buzz();
    //while(1);
    
    //write data
    write_buf[0]=0x00;
#if 1
    
    
    for(page=0;page<8;page++)
    {
        for(rcnt=0;rcnt<102;rcnt++)
        {
            ee_WriteBytes(write_buf, 0x40, 1);
        }

    }
    
    
    write_buf[0]=0x88;//X address
	ee_WriteBytes(write_buf, 0x00, 1);
 
    write_buf[0]=0x44;//Y address
	ee_WriteBytes(write_buf, 0x00, 1);
    
    
     write_buf[0]=0xaa;
     ee_WriteBytes(write_buf, 0x40, 1);
    
    
    
#endif
    
#if 0
    //ee_WriteBytes(write_buf, 0xc0, 1);
ee_WriteBytes(write_buf, 0xc0, 1);
ee_WriteBytes(write_buf, 0xc0, 1);
ee_WriteBytes(write_buf, 0xc0, 1);
ee_WriteBytes(write_buf, 0xc0, 1);
ee_WriteBytes(write_buf, 0xc0, 1);
ee_WriteBytes(write_buf, 0xc0, 1);
ee_WriteBytes(write_buf, 0xc0, 1);
ee_WriteBytes(write_buf, 0xc0, 1);
ee_WriteBytes(write_buf, 0xc0, 1);
ee_WriteBytes(write_buf, 0xc0, 1);

#endif
    

     
    
   //=========================================================================== 
    
#if 0
    
    
    
	#if 1
	write_buf[0]=0x20;
	ee_WriteBytes(write_buf, 0x00, 1);
	#endif
	
	write_buf[0]=0x10;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	write_buf[0]=0xb0;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	write_buf[0]=0xc8;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	write_buf[0]=0x00;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	
	
	write_buf[0]=0x10;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	write_buf[0]=0x40;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	write_buf[0]=0x81;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	
	write_buf[0]=0x7f;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	write_buf[0]=0xa1;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	write_buf[0]=0xa6;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	
	write_buf[0]=0xa8;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	write_buf[0]=0x3f;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	write_buf[0]=0xa4;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	write_buf[0]=0xd3;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	write_buf[0]=0x00;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	
	
	write_buf[0]=0xd5;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	
	write_buf[0]=0xf0;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	write_buf[0]=0xd9;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	write_buf[0]=0x22;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	
	
	
	write_buf[0]=0xda;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	write_buf[0]=0x12;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	
	write_buf[0]=0xdb;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	write_buf[0]=0x20;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	write_buf[0]=0x8d;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	
	
	write_buf[0]=0x14;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
	write_buf[0]=0xaf;
	ee_WriteBytes(write_buf, 0x00, 1);
	
	
#endif
	//==============================================================================
	
	
		
	#if 0
	Write_IIC_Command(0xAE);   //display off
	Write_IIC_Command(0x20);	//Set Memory Addressing Mode	
	Write_IIC_Command(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	Write_IIC_Command(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	Write_IIC_Command(0xc8);	//Set COM Output Scan Direction
	Write_IIC_Command(0x00);//---set low column address
	Write_IIC_Command(0x10);//---set high column address
	Write_IIC_Command(0x40);//--set start line address
	Write_IIC_Command(0x81);//--set contrast control register
	Write_IIC_Command(0x7f);
	Write_IIC_Command(0xa1);//--set segment re-map 0 to 127
	Write_IIC_Command(0xa6);//--set normal display
	Write_IIC_Command(0xa8);//--set multiplex ratio(1 to 64)
	Write_IIC_Command(0x3F);//
	Write_IIC_Command(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	Write_IIC_Command(0xd3);//-set display offset
	Write_IIC_Command(0x00);//-not offset
	Write_IIC_Command(0xd5);//--set display clock divide ratio/oscillator frequency
	Write_IIC_Command(0xf0);//--set divide ratio
	Write_IIC_Command(0xd9);//--set pre-charge period
	Write_IIC_Command(0x22); //
	Write_IIC_Command(0xda);//--set com pins hardware configuration
	Write_IIC_Command(0x12);
	Write_IIC_Command(0xdb);//--set vcomh
	Write_IIC_Command(0x20);//0x20,0.77xVcc
	Write_IIC_Command(0x8d);//--set DC-DC enable
	Write_IIC_Command(0x14);//
	Write_IIC_Command(0xaf);//--turn on oled panel 
	
	#endif
	
	
	
	
	
	
	
}




void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		//Write_IIC_Command(0xb0+m);		//page0-page1
		//Write_IIC_Command(0x00);		//low column start address
		//Write_IIC_Command(0x10);		//high column start address
		
		
		write_buf[0]=0xb0+m;
	  ee_WriteBytes(write_buf, 0x00, 1);
	
		
		write_buf[0]=0x00;
	  ee_WriteBytes(write_buf, 0x00, 1);
		
		write_buf[0]=0x10;
	  ee_WriteBytes(write_buf, 0x00, 1);
		
		
		
		
		
		
		for(n=0;n<128;n++)
			{
				//Write_IIC_Data(fill_Data);
				
				write_buf[0]=fill_Data;
	      ee_WriteBytes(write_buf, 0x40, 1);
				
				
				
				
			}
	}
}

const unsigned char  show1[]=
{
0x00,0x06,0x0A,0xFE,0x0A,0xC6,0x00,0xE0,0x00,0xF0,0x00,0xF8,0x00,0x00,0x00,0x00,
0x00,0x00,0xFE,0x7D,0xBB,0xC7,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xC7,0xBB,0x7D,
0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
0x0C,0xFE,0xFE,0x0C,0x08,0x20,0x60,0xFE,0xFE,0x60,0x20,0x00,0x00,0x00,0x78,0x48,
0xFE,0x82,0xBA,0xBA,0x82,0xBA,0xBA,0x82,0xBA,0xBA,0x82,0xBA,0xBA,0x82,0xFE,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,
0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFF,0xFF,0x00,0x00,0xFE,0xFF,0x03,
0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFF,0xFE,0x00,0x00,0x00,0x00,0xC0,0xC0,
0xC0,0x00,0x00,0x00,0x00,0xFE,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0xFF,0xFE,0x00,0x00,0xFE,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFF,
0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x0C,
0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFF,0xFF,0x00,0x00,0x00,0x00,0xE1,0xE1,
0xE1,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x0F,0x00,0x00,0x0F,0x1F,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x1F,0x0F,0x00,0x00,0x0F,0x1F,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,
0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xE2,0x92,0x8A,0x86,0x00,0x00,0x7C,0x82,0x82,0x82,0x7C,
0x00,0xFE,0x00,0x82,0x92,0xAA,0xC6,0x00,0x00,0xC0,0xC0,0x00,0x7C,0x82,0x82,0x82,
0x7C,0x00,0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0xC0,0xC0,0x00,0x7C,0x82,0x82,0x82,
0x7C,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x24,0xA4,0x2E,0x24,0xE4,0x24,0x2E,0xA4,0x24,0x00,0x00,0x00,0xF8,0x4A,0x4C,
0x48,0xF8,0x48,0x4C,0x4A,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x20,0x10,0x10,
0x10,0x10,0x20,0xC0,0x00,0x00,0xC0,0x20,0x10,0x10,0x10,0x10,0x20,0xC0,0x00,0x00,
0x00,0x12,0x0A,0x07,0x02,0x7F,0x02,0x07,0x0A,0x12,0x00,0x00,0x00,0x0B,0x0A,0x0A,
0x0A,0x7F,0x0A,0x0A,0x0A,0x0B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x40,0x40,
0x40,0x50,0x20,0x5F,0x80,0x00,0x1F,0x20,0x40,0x40,0x40,0x50,0x20,0x5F,0x80,0x00,
};



void picture_1(void)
{
  unsigned char x,y;
  unsigned int i=0;
  for(y=0;y<8;y++)
    {
      //Write_IIC_Command(0xb0+y);
      //Write_IIC_Command(0x00);
      //Write_IIC_Command(0x10);
			
			
					write_buf[0]=0xb0+y;
	  ee_WriteBytes(write_buf, 0x00, 1);
	
		
		write_buf[0]=0x00;
	  ee_WriteBytes(write_buf, 0x00, 1);
		
		write_buf[0]=0x10;
	  ee_WriteBytes(write_buf, 0x00, 1);
		
			
			
			
			
			
			
      for(x=0;x<128;x++)
        {
          //Write_IIC_Data(show1[i++]);
					
					write_buf[0]=show1[i++];
	        ee_WriteBytes(write_buf, 0x40, 1);
					
					
        }
    }
}



const unsigned char ASCII_16_Dot[  ] = {

#if 1
/*"   CHAR_22 */
0x00,0x00,0x00,0x00,0x00,0x78,0x0c,0x7c,
0xcc,0xcc,0xcc,0x76,0x00,0x00,0x00,0x00,
#endif
	
	//0x0e,0x5f,0x51,0x51,0x7e,0x3f,0x01,0x00,

};



void xdelay(uint32_t x)
{
uint32_t m,n;
	while(x)
	{
	for(m=0;m<1000;m++)
		for(n=0;n<1000;n++);
		
		x--;
	}

}

void oled_096_print(uint8_t col, uint8_t row, int8_t*str)
{
  unsigned char x,y;
  unsigned int i=0;
	y=0;
  for(y=0;y<8;y++)
    {
      //Write_IIC_Command(0xb0+y);
      //Write_IIC_Command(0x00);
      //Write_IIC_Command(0x10);
			
			
		write_buf[0]=0xb0+7-y;
	  ee_WriteBytes(write_buf, 0x00, 1);
	
		
		write_buf[0]=0x00;
	  ee_WriteBytes(write_buf, 0x00, 1);
		
		write_buf[0]=0x10;
	  ee_WriteBytes(write_buf, 0x00, 1);
		
			
			
			
			
			
			
      //for(x=0;x<128;x++)
			for(x=0;x<16;x++)
        {
          //Write_IIC_Data(show1[i++]);
					
					write_buf[0]=ASCII_16_Dot[i++];
					
					if(i==16)i=0;
					//write_buf[0]=0xff;
	        ee_WriteBytes(write_buf, 0x40, 1);
					
					
        }
				
				xdelay(20);
				
    }
}

