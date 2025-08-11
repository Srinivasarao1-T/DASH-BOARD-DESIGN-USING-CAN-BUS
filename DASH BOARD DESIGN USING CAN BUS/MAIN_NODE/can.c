#include <lpc21xx.h>
#include "types.h"
#include"can.h"
#include"can_defines.h"
void Init_CAN1(void)
{
    PINSEL1|=RD1_PIN;    
    C1MOD=1;
    AFMR=2;
    C1BTR=BTR_LVAL;    
    C1MOD=0;
}
void CAN1_Tx(struct CAN_Frame txFrame)
{
     C1MOD=1;
	 C1MOD=0; 
	 if((C1GSR&TBS1_BIT_READ)>0)
	 {
	    goto lable;
	 }
	 else{
	      return;
	 }
lable:C1TID1=txFrame.ID;
    C1TFI1=txFrame.vbf.RTR<<30|txFrame.vbf.DLC<<16;
                
	if(txFrame.vbf.RTR!=1)
    {
         C1TDA1= txFrame.Data1;
      C1TDB1= txFrame.Data2;
                }
     C1CMR=STB1_BIT_SET|TR_BIT_SET;
	  if((C1GSR&TCS1_BIT_READ)==0)
	  {
	       return ;
	  }
}
void CAN1_Rx(struct CAN_Frame *rxFrame)
{
int i=0;
				 for(i=0;i<10000;i++){
				           if(((C1GSR&RBS_BIT_READ)&1==1))
	                   	{
		                 goto label;  
	             	 }
				 
		rxFrame->ID=0;
        rxFrame->vbf.RTR=(C1RFS>>30)&1;
        rxFrame->vbf.DLC=(C1RFS>>16)&0x0f;
        rxFrame->Data1=0;
        rxFrame->Data2=0;
		      C1CMR=RRB_BIT_SET;
		        return;

			}	
label:  rxFrame->ID=C1RID;
        rxFrame->vbf.RTR=(C1RFS>>30)&1;
        rxFrame->vbf.DLC=(C1RFS>>16)&0x0f;
        if(rxFrame->vbf.RTR==0)
  {
    rxFrame->Data1=C1RDA;
    rxFrame->Data2=C1RDB;
  }
      C1CMR=RRB_BIT_SET;

}

