#include <LPC21xx.h>
#include"can.h"
#include"types.h"
#include "delay.h"
#include "lcd.h"
#include "rtc.h"
#include "sensor.h"
#define ERROR -1000
int cnt,cnt2;
void  ent0_irq_left(void) __irq;
void  ent1_irq_right(void) __irq;
const u8 fuel[64]={0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
                   0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
				   0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
				   0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,
				   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
				   0x08,0x0c,0x0e,0x0f,0x0f,0x0e,0x0c,0x08,
				   0x02,0x06,0x0e,0x1e,0x1e,0x0e,0x06,0x02,
				   0x0e,0x0a,0x0a,0x0e,0x1f,0x1f,0x1f,0x0e};
void readtemp()
{
int ret;
ret=ReadTemp();
if(ret==ERROR)
{
    cmdLCD(0xcb);
	strLCD("ERROR   ");
}
else{
cmdLCD(0xcb);
ret=ret>>4;
u32LCD(ret);
charLCD(223);
charLCD('C');
charLCD(' ');
}
   BuildCGRAM(fuel,64);
   cmdLCD(0xd3);
   charLCD(7);
}
void get()
{
  
  struct CAN_Frame rxframe;
  s32 yr,mo,dt,flag=0,f=0;
  GetRTCDateInfo(&dt,&mo,&yr);
  DisplayRTCDate(dt,mo,yr);
  cmdLCD(0xc0);
  strLCD("ENG TEMP:");
  
	  readtemp();
  CAN1_Rx(&rxframe);
  if(rxframe.ID==1)
  {
   cmdLCD(0x94);
   strLCD("FUEL(%):");
   cmdLCD(0x9d);
   flag=rxframe.Data1;
   BuildCGRAM(fuel,40);
   cmdLCD(0x9d);
   while(flag>25){
   charLCD(4);
   flag=flag-25;
   f++;
   }
   if(flag>20&&flag<=25)
   {
     charLCD(4);
   }
   else if(flag<=20&&flag>15)
   {
     charLCD(3);
   }
   else if(flag<=15&&flag>10)
   {
	charLCD(2);
   }
   else if(flag<=20&&flag>5)
   {
   charLCD(1);
   }
   else if(flag>0&&flag<=5)
   {
   charLCD(0);
   }
u:   if(f==4)
   {
   goto l;
   }
   else{
   f++;
   charLCD(' ');
   goto u;
   }
   
 l:charLCD(' ');
   if(rxframe.Data1==100)
   {
   cmdLCD(0x9d+5);
   charLCD('1');
   charLCD('0');
   charLCD('0');  
   }
   else{
   cmdLCD(0x9d+5);
   charLCD(((rxframe.Data1)/10)+48); 
   charLCD(((rxframe.Data1)%10)+48);
   charLCD(' ');
   }
   cmdLCD(0x9d+8);
   charLCD('%');       
  }
  else
  {
       cmdLCD(0x94);
    strLCD("FUEL(%):");
    cmdLCD(0x9d);
    strLCD("NODEMISS ");
  }
  cmdLCD(0xd4);
  strLCD("INDICATOR:");
}
s32 hr,mi,se;
main()
{
		u8 j;
		s32 day; 
		int flag=0;
		struct CAN_Frame txleft; 
		        txleft.ID=2;   
		txleft.vbf.RTR=0;    
        txleft.Data1=1; 
		txleft.Data2=0;
      Init_CAN1();
	  RTC_Init(); 
	  initLCD();
      PINSEL1=((PINSEL1&~(3<<(16%16)*2))|(1<<(16%16)*2));
  	  PINSEL0=((PINSEL0&~(3<<(2*14)))|(2<<(2*14)));
      VICIntEnable=1<<14|1<<15;					  
	  VICVectCntl0=1<<5|14;
	  VICVectCntl1=1<<5|15;
	  VICVectAddr1=(u32) ent1_irq_right;
	  VICVectAddr0=(u32) ent0_irq_left;
	  EXTMODE=1<<0|1<<1;
	 BuildCGRAM(fuel,64);
        while(1)
        {
out:		  get();
        GetRTCTimeInfo(&hr,&mi,&se);
       DisplayRTCTime(hr,mi,se);
	  GetRTCDay(&day);
      DisplayRTCDay(day);
	  if(flag==0)
	  {
	   cmdLCD(0xdf);
	   charLCD(6);
	   charLCD(5);
	  }

l:			    if(cnt%2==1)
			   {          
				    txleft.Data1=1;
			    CAN1_Tx(txleft);
			    while(1){
			    for(j=0;j<10;j++)
				 {
				cmdLCD(0xDF);
				charLCD(6);
				charLCD(5);
				GetRTCTimeInfo(&hr,&mi,&se);
                DisplayRTCTime(hr,mi,se);
				if(cnt2%2==1)
				{
			  cmdLCD(0xDf);
				strLCD("  ");
				txleft.Data1=2;
				CAN1_Tx(txleft);
				 cnt=0;
				 goto r;
				}

				if(cnt%2==0)
				{
			    cmdLCD(0xDf);
				strLCD("  ");
				txleft.Data1=2;
				CAN1_Tx(txleft);
				 cnt=0;
				 goto out;
				}
				}
				txleft.Data1=1;
			    CAN1_Tx(txleft);
				get();
				for(j=0;j<120;j++)
				{
				cmdLCD(0xDF);
				 charLCD(' ');
				 if(cnt2%2==1)
				{
			    cmdLCD(0xDf);
				charLCD(6);
				charLCD(5);
				txleft.Data1=2;
				CAN1_Tx(txleft);
                cnt=0;
				 goto r;
				}
				if(cnt%2==0)
				{
			    cmdLCD(0xDf);
				charLCD(6);
				charLCD(5);
				txleft.Data1=2;
				CAN1_Tx(txleft);
				 cnt=0;
				 goto out;
				}
				} 
				}
			  }
r:		   if(cnt2%2==1)
			   {
			   cnt2=1;
			   txleft.Data1=3; 
				CAN1_Tx(txleft);
			   		   while(1){
			    txleft.Data1=3; 
				CAN1_Tx(txleft);
			    for(j=0;j<10;j++)
				{
				 cmdLCD(0xdf);
				 charLCD(6);
				  cmdLCD(0xE0);
			     charLCD(5);
				 GetRTCTimeInfo(&hr,&mi,&se);
                 DisplayRTCTime(hr,mi,se);
				if(cnt%2==1)
				{
			     cmdLCD(0xDf);
				strLCD("  ");
				txleft.Data1=4;
				CAN1_Tx(txleft);
				 cnt2=0;
				 goto l;
				}
				if(cnt2%2==0)
				{
			    cmdLCD(0xDf);
				strLCD("  ");
				txleft.Data1=4; 
				CAN1_Tx(txleft);
				 cnt2=0;
				 goto out;
				}
				}
				txleft.Data1=3; 
				CAN1_Tx(txleft);
				get();
				if(cnt%2==1)
				{
			    cmdLCD(0xDf);
				strLCD("  ");
				txleft.Data1=4;
				CAN1_Tx(txleft);
				 cnt2=0;
				 goto l;
				}
				if(cnt2%2==0)
				{
			    cmdLCD(0xDf);
				strLCD("  ");
				txleft.Data1=4; 
				CAN1_Tx(txleft);
				 cnt2=0;
				 goto out;
				}
				for(j=0;j<120;j++)
				{
				cmdLCD(0xdf+1);
				charLCD(' ');
				 if(cnt%2==1)
				{
			    cmdLCD(0xDf);
				charLCD(6);
				charLCD(5);
				txleft.Data1=4;
				CAN1_Tx(txleft);
                txleft.Data1=1; 
				CAN1_Tx(txleft);
				 cnt2=0;
				 goto l;
				}
				if(cnt2%2==0)
				{
			    cmdLCD(0xDf);
				charLCD(6);
				charLCD(5);
				txleft.Data1=4; 
				CAN1_Tx(txleft);
				 cnt2=0;
				 goto out;
				}
				} 
				}
			   }
        } 
}
void  ent0_irq_left() __irq
{      cnt++;
      VICVectAddr=0;
      EXTINT=1<<0;
}
void  ent1_irq_right() __irq
{
	  cnt2++;
	   VICVectAddr=0;
    EXTINT=1<<1;
} 

