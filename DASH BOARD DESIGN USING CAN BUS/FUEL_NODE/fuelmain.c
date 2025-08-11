#include <lpc21xx.h>
#include "types.h"
#include "can.h"
#include "adc.h"
f32 ear;
int curr,i;
unsigned short int dval;
float max=2;
float min=0.3;
float res;
int main(void)
{
      struct CAN_Frame txFrame; 
	    txFrame.ID=1;   
		txFrame.vbf.RTR=0; //data frame 
		txFrame.vbf.DLC=4;   
		txFrame.Data2=0;
    Init_CAN1();
	  Init_ADC();
        while(1)
         {
		           Read_ADC(1,&dval,&ear);
                   res=(((ear-min)/(max-min)))*100;
	      	 	   	 if(res>=0&&res<=100){
						   txFrame.Data1=res;
					         }
					    else if(res<0)
		            {
					      txFrame.Data1=0;

		            }		            
	            	else if(res>100)
		             {
		              txFrame.Data1=100;
				         }	
					  for(i=0;i<120000;i++);
				   	 CAN1_Tx(txFrame);	             
          }
}

