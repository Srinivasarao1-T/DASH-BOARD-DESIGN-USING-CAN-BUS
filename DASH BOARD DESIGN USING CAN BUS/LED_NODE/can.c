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
void CAN1_Rx(struct CAN_Frame *rxFrame)        
{        
//wait for CAN frame recv status        

	int i,flag=0;
pos:
	for(i=0;i<20;i++){
	  if((C1GSR&RBS_BIT_READ)!=0)
	  {
	  goto label;
	  }      
	}
	return;
	  //read 11-bit CANid of recvd frame.         
label:	rxFrame->ID=C1RID;        
// read & extract data/remote frame status        
	rxFrame->vbf.RTR=(C1RFS>>30)&1;        
//read & extract data length        
	rxFrame->vbf.DLC=(C1RFS>>16)&0x0f;        
//check if recvd frame is data frame,extract data bytes        
	if(rxFrame->vbf.RTR==0)        
  {         
//read 1-4 bytes from C1RDA        
		rxFrame->Data1=C1RDA;        
//read 5-8 bytes from C1RDB        
    rxFrame->Data2=C1RDB;        
}        

// Release receive buffer         

      C1CMR=RRB_BIT_SET;  
	  if(rxFrame->ID!=2&&flag==0)
	  {
	  flag=1;
	  goto pos;
	  }       

}        



