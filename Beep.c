#include <xc.h>
#include <stdio.h>
#include "Beep.h"
#include "Oled.h"




void uart_init(void)
{

    TRISCbits.RC7 =1;//RX  input mode
    TRISCbits.RC6 =0;//TX  output mode

    SPBRG = 25;

    RCSTAbits.SPEN =1;
    //RCSTAbits.CREN =1;//
    
    //TXSTAbits.BRGH =1;
    
   TXSTAbits.TXEN =1;

    

}

void put_byte_uart(uint8_t n)
{
    
    PIR1bits.TXIF =0;
    TXREG = n;
    
    while( TXSTAbits.TRMT ==0);
    
    while( PIR1bits.TXIF ==0);
     PIR1bits.TXIF =0;
}

void put_bytes_uart(uint8_t *arr,uint8_t n)
{
    
    uint8_t i=0;
    for(i=0;i<n;i++)
    {
        put_byte_uart(arr[i]);
    }
    
    
    
}




void putch(uint8_t c)
{
     TXREG = c;
    
    while( TXSTAbits.TRMT ==0);
    
    
    
}













void BeepInit(void)
{
	//PORTBbits.RB1 =0;	//colse	
	//DDRBbits.RB1  =0;	//dir=out
    
   // PORTEbits.RE2 =0;
   // DDREbits.RE2 =0;
    
    
    TRISEbits.RE2 =0;
    LATEbits.LE2 =0;
    
    
    TRISDbits.RD5 =0;//test led
    LATDbits.LD5 =1;//test led off
    
}
void BeepOn(void)
{
	//PORTBbits.RB1 =1;	//colse	
    
    // PORTEbits.RE2 =1;
     
     LATEbits.LE2 =1;
     
     
}
void BeepOff(void)
{
	//PORTBbits.RB1 =0;	//colse	
   // PORTEbits.RE2 =0;
    
    LATEbits.LE2 =0;
}


void buzz(void)
{
    
    
    	//unsigned int  i,j;
//PORTEbits.RE2 =1;
LATEbits.LE2 =1;
  
    //for(i=0;i<200;i++)
       //for(j=0;j<100;j++);
       
       
        delay_nms(1);
       
//PORTEbits.RE2 =0;
LATEbits.LE2 =0;
  //for(i=0;i<200;i++)
      // for(j=0;j<100;j++);

}