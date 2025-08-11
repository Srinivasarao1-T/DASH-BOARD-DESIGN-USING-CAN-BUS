#include <lpc21xx.h>    
#include "types.h"    
#include"can.h"
#include"can_defines.h"
/*CAN Controller 1 Initialization : (defined in can.c )*/   
void Init_CAN1(void)   
{   
    //cfg p0.25 pin as CAN1_RX pin(RD1),TD1 is exclusive    
    PINSEL1|=RD1_PIN; //using defines from can_defines.h   
                      // #define RD1_PIN 0x00040000 ,    
                      //as RD1/ (i.e CAN1_RX)/p0.25   
    //Reset CAN1 controller   
    C1MOD=1;   
    //All received messages are accepted       
    AFMR=2;    
    //Set baud Rate for CAN   
    C1BTR=BTR_LVAL; //using defines from can_defines.h   
    //Enable CAN1 controller   
    C1MOD=0;    
}
void CAN1_Tx(struct CAN_Frame txFrame)     
{      
  // Checking that the TX buffer is empty in C1GSR   
  C1MOD=1;
  C1MOD=0;  
     while((C1GSR&TBS1_BIT_READ)==0); //if status is 1 then empty    
    
		C1TID1=txFrame.ID;      
       
    C1TFI1=txFrame.vbf.RTR<<30|txFrame.vbf.DLC<<16;     
     
		if(txFrame.vbf.RTR!=1)     
    {      
			C1TDA1= txFrame.Data1;     
      C1TDB1= txFrame.Data2;     
		}
    //Select Tx Buf1 & Start Xmission using       
     C1CMR=STB1_BIT_SET|TR_BIT_SET;      
		//monitor tx status in C1GSR     
     // while((C1GSR&TCS1_BIT_READ)==0);
	 if((C1GSR&TCS1_BIT_READ)==0)
	  {
	       return ;
	  }     
}
