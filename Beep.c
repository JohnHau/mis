#include <xc.h>
#include "Beep.h"
#include "Oled.h"
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