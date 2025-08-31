#include "types.h"
#include <lpc21xx.h>
//#include "delay.h"
#include "ADC_define.h"
void Read_ADC(u8 chno,u16 *dval,f32 *evar)
{
   //CLEAR PREVIOUS CHANNEL SELECTIO      
	  ADCR&=0XFFFFFFF0;
	  //UPDEATE CHANNEL NO &START ADC CONV
	  ADCR|=(1<<ADC_START_BIT)|(1<<chno);
	  //wait until covstation status
       while(((ADDR>>DONE_BIT)&1)==0);
	  //STOPADCCONV
	  ADCR&=~(1<<ADC_START_BIT);
	  //READ DIGITAL DATA
	  *dval=((ADDR>>DIGITAL_DATA_BITS)&1023);
	  *evar=((3.3/1023)* *dval);

}
void Init_ADC(void)
{
      PINSEL1=(PINSEL1&~(3<<(28%16)*2))|(PIN_FUNC2<<(28%16)*2);
	  ADCR=(1<<PDN_BIT)|(CLCKDIV<<8);
}


