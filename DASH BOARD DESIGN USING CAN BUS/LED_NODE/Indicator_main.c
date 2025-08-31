#include <LPC21xx.h>   
#include"can.h"  
const unsigned int LUT[8]={1,2,4,8,16,32,64,128}; 
int i,j;
main()   
{   
	  struct CAN_Frame rxFrame;   
      Init_CAN1();
	  IODIR0|=255<<0;
	  IOPIN0|=0Xff<<0; 
	while(1)   
	{   
				   while(1){
					
out:while(1)
			{
		                	CAN1_Rx(&rxFrame);
							 if(rxFrame.ID==2&&(rxFrame.Data1==2||rxFrame.Data1==4))
							 {
							      continue;
							 }
							 else{
							 break;
							 }

			}        
			l:			if(rxFrame.ID==2&&rxFrame.Data1==1)
							 {
	
			         while(1){
							 for(i=7;i>=0;i--)
	              {
							IOPIN0=((IOPIN0&~(255<<0))|((LUT[i]^0xff)<<0));
	            for(j=0;j<30000;j++){
               CAN1_Rx(&rxFrame);
							 if(rxFrame.ID==2&&rxFrame.Data1==3)
							 {
							  goto r;
							 }
							 if(rxFrame.ID==2&&(rxFrame.Data1==2||rxFrame.Data1==4))
							 {
							 IOCLR0=0XFf<<0;
							 IOSET0=0xff<<0;
							   goto out;
							 }
							 } 
							}
							}
							}
			
       r:     			 if(rxFrame.Data1==3 && rxFrame.ID==2)
							{
							while(1){
							 for(i=0;i<8;i++)
	                        {
								IOPIN0=((IOPIN0&~(255<<0))|((LUT[i]^0xff)<<0));
	             for(j=0;j<30000;j++){      
							 CAN1_Rx(&rxFrame);
							 if(rxFrame.ID==2&&rxFrame.Data1==1)
							 {
							  goto l;
							 }
							 if(rxFrame.ID==2&&(rxFrame.Data1==2||rxFrame.Data1==4))
							 {
							 IOCLR0=0XFf<<0;
							 IOSET0=0xff<<0;
							   goto out;
							 }
							 } 
							}
							}
				   }   
				   }
		}
}


